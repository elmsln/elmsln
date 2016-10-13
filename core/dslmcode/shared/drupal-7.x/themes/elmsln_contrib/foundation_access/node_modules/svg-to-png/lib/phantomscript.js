/*
 * grunticon
 * https://github.com/filamentgroup/grunticon
 *
 * Copyright (c) 2012 Scott Jehl, Filament Group, Inc
 * Licensed under the MIT license.
 */

/*global phantom:true*/
/*global require:true*/

/*
phantom args sent from grunticon.js:
	[0] - input directory path
	[1] - output directory path
	[2] - default width
	[3] - default height
*/

(function(){
	"use strict";

	var system = require("system");
	var fs = require( "fs" );

	phantom.onError = function(msg, trace) {
		var msgStack = ['PHANTOM ERROR: ' + msg];
		if (trace && trace.length) {
			msgStack.push('TRACE:');
			trace.forEach(function(t) {
				msgStack.push(' -> ' + (t.file || t.sourceURL) + ': ' + t.line + (t.function ? ' (in function ' + t.function +')' : ''));
			});
		}
		system.stderr.write( msgStack.join('\n') );
		phantom.exit(1);
	};

	var RSVP = require('./rsvp');
	var processor = require('./processor');

	RSVP.on('error', function(reason) {
		throw new Error( reason );
	});

	// alternate syntax for PhantomJS 2.x (system.args) / 1.x (phantom.args)
	var options = (typeof(phantom.args) === "undefined") ? {
		inputFiles: JSON.parse(system.args[1]),
		dest: system.args[2],
		defaultWidth: system.args[3],
		defaultHeight: system.args[4]
	} : {
		inputFiles: JSON.parse(phantom.args[0]),
		dest: phantom.args[1],
		defaultWidth: phantom.args[2],
		defaultHeight: phantom.args[3]
	};

	if( !options.dest.match( fs.separator + '$' ) ){
		options.dest += fs.separator;
	}


	var promises = options.inputFiles.map( function( file ){
		return processor.processFile( file, options );
	});


	RSVP.all( promises )
	.then( function(){
		phantom.exit();
	})
	.catch(function(err){
		throw new Error( err );
	});
})();
