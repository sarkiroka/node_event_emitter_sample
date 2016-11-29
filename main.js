var ExampleObject = require('bindings')('myEventEmitterExample').ExampleObject;
var events = require('events');

inherits(ExampleObject, events);

module.exports = ExampleObject;

// extend prototype
function inherits(target, source) {
  for (var k in source.prototype) {
    if(source.prototype.hasOwnProperty(k)) {
      target.prototype[k] = source.prototype[k];
    }
  }
}
