# Example node.js addon for event emitting
This just show an example on how to call JS functions from a C++ addon

## Executing
be sure to have [node-gyp](https://github.com/nodejs/node-gyp) installed

### Initializing:
```bash
./update
```
### Start example
```bash
./startup
```

Example result:

```bash
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
still live
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
still live
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
Event emitted from C++ with arguments { err: undefined, result: 'someArg' }
now die
```
