/*global require:true*/
/*global phantom:true*/
/*global window:true*/
(function(){
	"use strict";
	var page = require( 'webpage' ).create();
	var system = require( 'system' );
	var uncomment = require( './uncomment' );

	var onError = function(msg, trace) {
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

	phantom.onError = onError;
	page.onError = onError;

	page.onConsoleMessage = function( msg ){
		system.stderr.write( msg + "\n" );
	};

	var fileContents = decodeURI(system.args[1]);
	var name = system.args[2];
	var color = system.args[3];

	page.onLoadFinished = function( status ){
		if( status !== "success" ){
			throw new Error( "Page did not load in Phantom" );
		}
		var svg = page.evaluate(function(name, color){
				var document = window.document;
				var els = document.querySelectorAll( "svg :not([fill=none])" );
				var ret = {};

				Array.prototype.forEach.call(els, function(el){
					el.setAttribute( "fill", color );
				});
				els = document.querySelectorAll( "svg [stroke]:not([stroke=none])" );
				Array.prototype.forEach.call(els, function(el){
					el.setAttribute( "stroke", color );
				});


				ret[ name ] = document.querySelector( ".container" ).innerHTML;
				return ret;
			}, name, color);

		for( var i in svg ){
			if( svg.hasOwnProperty( i ) ){
				svg[i] = uncomment.XMLHeader( svg[i] );
			}
		}
		system.stdout.write(encodeURI(JSON.stringify(svg)));
		phantom.exit(0);

	};

	page.content = "<html><head></head><body><div class='container'>" + fileContents + "</div></body></html>";
}());
