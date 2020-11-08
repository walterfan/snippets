#  Style

## HTML must pass HTMLHint

## JS must pass ESLint

Declare all global variables and element variables at the top of main.js.

Put all conditional statements in a block, even if only one line.

By default use === and !== for testing equality. This makes equality testing explicit, without coercion.

Put a semicolon at the end of every statement. This is easy to forget with handlers, for example:

	stream.onFoo = function(){...}; // this is a statement

Prefer [] to new Array(), for example:

	const myArray = [];

Prefer dot notation. For example use this:

	pcConfig.iceServers[i].url

...instead of this:

	pcConfig.iceServers[i]['url'];


Double quote string values in HTML, single quote in JavaScript (as per Google style guide).

Variables are camelCase. In general, don't use hyphens in names.

Indent with two spaces. When function calls or tests run onto multiple lines, indent with four spaces: 

	const iceServers = createIceServers(turnServer.uris,
	    turnServer.username, turnServer.password);
	
	alert('Failed to create data channel. ' +
	    'You need Chrome 25 or later with --enable-data-channels flag');
	
	
	
	if (sctpSelect.checked && 
	    (detectedBrowser === 'chrome' && detectedVersion >= 31) ||
	    detectedBrowser === 'firefox') {
	
	...
	
	
	}

## CSS must pass CSSLint
