var exampleObject = new (require('./main'))();

exampleObject.on("myEventName", (err, result) => console.log("Event emitted from C++ with arguments", {err, result}));

exampleObject.listen();

var liveCounter = 2;
var intervalId = setInterval(function () {
	console.log(liveCounter ? 'still live' : 'now die');
	if (!liveCounter--) {
		clearInterval(intervalId);
	}
}, 1000);
