/*global require:true*/
/*global module:true*/
/*global __dirname:true*/
(function(){
	"use strict";
	var path = require( 'path' );
	var Colorfy = require( path.join( __dirname, "colorfy.js" ) );

	var ColorfyFromOptions = function( options ){
		for( var option in options ){
			if( options.hasOwnProperty( option ) ){
				this[option] = options[option];
			}
		}
	};

	ColorfyFromOptions.prototype = Colorfy.prototype;

	module.exports = ColorfyFromOptions;
}());
