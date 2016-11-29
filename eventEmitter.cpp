#ifndef _WIN32
#include <unistd.h>
#endif
#include <nan.h>

using namespace Nan;
class ExampleObject : public ObjectWrap {
	 public:
		static NAN_MODULE_INIT(Init);

	 private:
		ExampleObject();
		~ExampleObject();

		static NAN_METHOD(New);
		static NAN_METHOD(Listen);
		static Persistent<v8::Function> constructor;
};

struct asyncEventData {
	uv_work_t request;
	char *eventName;
	char *aResult;
};
volatile bool processed = false;

Persistent<v8::Function> ExampleObject::constructor;

ExampleObject::ExampleObject() {}

ExampleObject::~ExampleObject() {}

NAN_MODULE_INIT(ExampleObject::Init) {
	// Prepare constructor template
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New<v8::String>("ExampleObject").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	SetPrototypeMethod(tpl, "listen", Listen);

	constructor.Reset(tpl->GetFunction());
	Set(target, Nan::New("ExampleObject").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(ExampleObject::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("`new` required");
	}

	ExampleObject* obj = new ExampleObject();
	obj->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

ExampleObject* ExampleObjectThreadLoop;

NAN_INLINE void noop_execute (uv_work_t* req) {
	// nothing to do
}

NAN_INLINE void callbackAsyncEvent (uv_work_t* req) {
	Nan::HandleScope scope;//js need it
	// here we are executing in the node thread, so we can call nan and v8 functions
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	asyncEventData* data = static_cast<asyncEventData*>(req->data);

	v8::Local<v8::Value> emit_argv[] = {
		v8::String::NewFromUtf8(isolate, data->eventName),
		Nan::Undefined(),
		v8::String::NewFromUtf8(isolate, data->aResult)
	};

	MakeCallback(ExampleObjectThreadLoop->handle(), "emit", 3, emit_argv);

	delete data;
	processed = true;
}

void emitEvent(char *eventName, char *result) {
	asyncEventData *asyncdata = new asyncEventData();
	asyncdata->request.data = (void *) asyncdata;
	asyncdata->aResult = result;
	asyncdata->eventName = eventName;
	uv_queue_work(uv_default_loop(), &asyncdata->request, noop_execute, reinterpret_cast<uv_after_work_cb>(callbackAsyncEvent));
}

void generateRandomString(char *s) {
	const int length = 10;
	static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < length; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	s[length] = 0;
}

void mainLoop(void *n) {
	char result[16];
	while(true) {
		usleep(200000);//simulate working for 200 ms
		processed = false;
		generateRandomString(result);
		char eventName[16] = "myEventName\0";
		emitEvent(eventName, result);
		while (!processed) {}
	}
}

NAN_METHOD(ExampleObject::Listen) {
	if(ExampleObjectThreadLoop) return ThrowError("it's aleready running");
	uv_thread_t mythread;
	int threadnum = 1;
	ExampleObjectThreadLoop = Nan::ObjectWrap::Unwrap<ExampleObject>(info.Holder());
	uv_thread_create(&mythread, mainLoop, &threadnum);
}

NODE_MODULE(makecallback, ExampleObject::Init)
