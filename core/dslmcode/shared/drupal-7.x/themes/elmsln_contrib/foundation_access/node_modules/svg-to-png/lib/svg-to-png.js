/*
 * svg-to-png
 * https://github.com/filamentgroup/svg-to-png
 *
 * Copyright (c) 2013 Jeffrey Lembeck/Filament Group
 * Licensed under the MIT license.
 */

/*global require:true*/
/*global __dirname:true*/
/*global console:true*/
(function(exports) {

	"use strict";

	var os = require( 'os' );
	var fs = require( 'fs' );
	var path = require( 'path' );

	try {
		var Imagemin = require('imagemin');
	} catch(e) {
		var imageminNotInstalled = true;
	}

	var RSVP = require( './rsvp' );
	var phantomJsPath = require('phantomjs-prebuilt').path;
	var phantomfile = path.join( __dirname, 'phantomscript.js' );
	var execFile = require('child_process').execFile;


	var convertNoCompress = function( files, outputDir, opts ){
		return new RSVP.Promise(function(resolve, reject){
			execFile( phantomJsPath,
				[
					phantomfile,
					JSON.stringify(files),
					outputDir,
					opts.defaultWidth,
					opts.defaultHeight
				],

				function(err, stdout, stderr){
					if( err ){
						console.log("\nSomething went wrong with phantomjs...");
						if( stderr ){
							console.log( stderr );
						}
						reject( err );
					} else {
						console.log( stdout );
						resolve( outputDir );
					}
				});

			});
	};

	var convertCompress = function( files, outputDir, opts ){
		if( imageminNotInstalled ){
			throw "Imagemin dependency is not installed.";
		}

		var tempDir = path.join( os.tmpdir(), "svg-to-png" + (new Date()).getTime() );
		return new RSVP.Promise(function(resolve, reject){
			execFile( phantomJsPath,
				[
					phantomfile,
					JSON.stringify(files),
					tempDir,
					opts.defaultWidth,
					opts.defaultHeight
				],

				function(err, stdout, stderr){
					if( err ){
						console.log("\nSomething went wrong with phantomjs...");
						if( stderr ){
							console.log( stderr );
						}
						reject( err );
					} else {
						console.log( stdout );
						opts = opts || {};
						opts.optimizationLevel = opts.optimizationLevel || 3;

						var imagemin = new Imagemin()
								.src( tempDir + '/*.{gif,jpg,png,svg}' )
								.dest(outputDir)
								.use(Imagemin.optipng(opts));

						imagemin.run(function (err, files) {
							if (err) {
								reject(err);
							}

							resolve(files);
						});
					}
				});

			});
	};

	exports.convert = function( input, output, opts ){
		opts = opts || {};

		var files;
		if( typeof input === "string" && fs.existsSync( input ) && fs.lstatSync( input ).isDirectory()){
			files = fs.readdirSync( input ).map( function( file ){
				return path.join( input, file );
			});
		} else if( typeof input === "string" && fs.existsSync( input ) && fs.lstatSync( input ).isFile() ) {
			files = [ input ];
		} else if( Array.isArray( input ) ){
			files = input;
		} else {
			throw new Error( "Input must be Array of files or String that is a directory" );
		}

		if( !files.every( function( file ){
			return path.extname(file) === ".svg";
		})){
			throw new Error( "All files passed into svg-to-png must be SVG files, that includes all files in a directory" );
		}

		if( !files.length ){
			throw new Error( "Input must be Array of SVG files or String that is a directory that contains some of those" );
		}

		if( typeof output !== "string" ){
			throw new Error( "Output folder must be defined and a String" );
		}


		if( !opts.defaultWidth ){
			opts.defaultWidth = "400px";
		}

		if( !opts.defaultHeight ){
			opts.defaultHeight = "300px";
		}

		// take it to phantomjs to do the rest
		console.log( "svg-to-png now spawning phantomjs..." );
		console.log('(using path: ' + phantomJsPath + ')');

		if( opts.compress ){
			return convertCompress( files, output, opts );
		} else {
			return convertNoCompress( files, output, opts );
		}


	};

}(typeof exports === 'object' && exports || this));
