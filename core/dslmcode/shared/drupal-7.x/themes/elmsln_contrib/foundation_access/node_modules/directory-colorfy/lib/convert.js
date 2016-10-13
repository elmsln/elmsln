/*global module:true*/
/*global require:true*/
/*global __dirname:true*/
(function(){
	"use strict";
	var path = require( 'path' );
	var phantomJsPath = require( 'phantomjs-prebuilt' ).path;
	var execFile = require( 'child_process' ).execFile;
	var phantomfile = path.join( __dirname, "phantomscript.js" );

	module.exports = function( contents, name, color, callback ){
			execFile( phantomJsPath,
				[
					phantomfile,
					encodeURI(contents),
					name,
					color
				],
				function(err, stdout){
					var svg = "";
					if( err ){
						callback( err, null );
						return;
					}

					svg = JSON.parse(decodeURI(stdout));

					callback( null, svg );
				}
			);
	};

}());
