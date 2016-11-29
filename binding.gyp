{
	"targets": [
		{
			"target_name": "myEventEmitterExample",
			"sources": [ "eventEmitter.cpp" ],
			"include_dirs": [
				"<!(node -e \"require('nan')\")",
			],
		}
	]
}
