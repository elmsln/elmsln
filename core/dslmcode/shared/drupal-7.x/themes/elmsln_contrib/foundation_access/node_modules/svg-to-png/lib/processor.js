/*global require:true*/
/*global window:true*/

(function(exports) {
	"use strict";
	var fs = require( 'fs' );

	var RSVP = require('./rsvp');
	var ProcessingFile = require( "./processing-file" );


	//TODO - Write test
	// o
	//
	// resolve promise with obj
	// {
	// width: int
	// height: int
	// type: "SVG" || "PNG"
	// }
	exports.getStats = function( gFile , o ){

		return new RSVP.Promise(function(resolve){

			var imagedata = gFile.imagedata,
				data = {};

			// get svg element's dimensions so we can set the viewport dims later
			var frag = window.document.createElement( "div" );
			frag.innerHTML = imagedata;
			var svgelem = frag.querySelector( "svg" );
			var pxre = /([\d\.]+)\D*/;
			var width = svgelem.getAttribute( "width" );
			var height = svgelem.getAttribute( "height" );
			if( width ){
				data.width = width.replace(pxre, "$1px");
			} else {
				data.width = o.defaultWidth;
			}
			if( height ){
				data.height = height.replace(pxre, "$1px");
			} else {
				data.height = o.defaultHeight;
			}
			data.type = "SVG";

			resolve( data );
		});
	}; //getStats


	//TODO - Requires Phantom - No test?
	exports.render = function( gFile , o) {

		var page = require( "webpage" ).create();

		var pngName = gFile.filenamenoext + ".png";
		var filename = gFile.pathdir + fs.separator + gFile.filename;
		// set page viewport size to svg dimensions
		page.viewportSize = {  width: parseFloat(gFile.width), height: parseFloat(gFile.height) };
		// open svg file in webkit to make a png || png to grab base64
		return new RSVP.Promise(function(resolve, reject){
			page.open(  filename, function( status ){
				if( status === "success" ){
					// create tmp file
					page.render( o.dest + pngName );
					var pngimgstring = page.renderBase64( "png" );
					resolve( pngimgstring );
				} else {
					reject( status + ": " + "Phantom had an error opening - " + filename + " - " + "Does it exist? " + fs.exists(filename));
				}
			}); //page.open
		});
	}; // render

	// process an svg file from the source directory
	//TODO - test - integration test?
	//params
	// filename
	// o
	//
	//resolves promise
	exports.processFile = function( filename , o ){
		var self = this;

		return new RSVP.Promise(function( resolve, reject ){
			var pFile;

			try {
				pFile = new ProcessingFile( filename );
				pFile.setImageData();
			} catch( e ){
				reject( e );
			}

			self.getStats( pFile , o )
			.then( function( data ){
				pFile.width = data.width;
				pFile.height = data.height;
				pFile.type = data.type;

				return self.render( pFile , o );
			})
			.then( function(){
				resolve();
			})
			.catch( function(err){
				reject(err);
			});
		});

	}; // end of processFile
}(typeof exports === 'object' && exports || this));

