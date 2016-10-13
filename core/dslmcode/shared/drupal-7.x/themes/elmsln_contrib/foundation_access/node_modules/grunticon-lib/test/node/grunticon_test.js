/*global require:true*/
/*global __dirname:true*/
(function( exports ){
	'use strict';

	var path = require( "path" );
	var os = require( "os" );
	var fs = require( "fs-extra" );
	var compare = require( "buffer-compare" );

	var Grunticon = require( path.join( __dirname, "..", "..", "lib", "grunticon-lib.js" ) );
	/*
		======== A Handy Little Nodeunit Reference ========
		https://github.com/caolan/nodeunit

		Test methods:
			test.expect(numAssertions)
			test.done()
		Test assertions:
			test.ok(value, [message])
			test.equal(actual, expected, [message])
			test.notEqual(actual, expected, [message])
			test.deepEqual(actual, expected, [message])
			test.notDeepEqual(actual, expected, [message])
			test.strictEqual(actual, expected, [message])
			test.notStrictEqual(actual, expected, [message])
			test.throws(block, [error], [message])
			test.doesNotThrow(block, [error], [message])
			test.ifError(value)
	*/

	exports.constructor = {
		setUp: function(done) {
			// setup here if necessary
			done();
		},
		noargs: function(test) {
			test.expect(1);

			test.throws(function(){
				new Grunticon();
			}, "No arguments should throw an error" );

			test.done();
		},
		twoargsFirstNotArray: function(test) {
			test.expect(1);

			test.throws(function(){
				new Grunticon("foo", "bar");
			}, "There needs to be two arguments. The first needs to be an Array" );

			test.done();
		},
		twoArgs: function( test ){
			test.expect(22);
			var grunticon = new Grunticon([path.join( __dirname, "files", "bear.svg")], path.join( __dirname, "output" ));

			// Required
			test.equal( grunticon.files[0], path.join( __dirname, "files", "bear.svg" ), "File should be set" );
			test.equal( grunticon.output, path.join( __dirname, "output" ), "Output should be set properly" );

			// Options Defaults
			test.equal( grunticon.options.datasvgcss, "icons.data.svg.css" );
			test.equal( grunticon.options.datapngcss, "icons.data.png.css" );
			test.equal( grunticon.options.urlpngcss, "icons.fallback.css" );
			test.equal( grunticon.options.previewhtml, "preview.html" );
			test.equal( grunticon.options.loadersnippet, "grunticon.loader.js" );
			test.equal( grunticon.options.cssbasepath, path.sep );
			test.equal( grunticon.options.cssprefix, ".icon-" );
			test.equal( grunticon.options.defaultWidth, "400px" );
			test.equal( grunticon.options.defaultHeight, "300px" );
			test.equal( grunticon.options.dynamicColorOnly, false );
			test.equal( grunticon.options.pngfolder, "png" );
			test.equal( grunticon.options.pngpath, "" );
			test.equal( grunticon.options.template, "" );
			test.equal( grunticon.options.tmpPath, os.tmpDir() );
			test.equal( grunticon.options.tmpDir, "grunticon-tmp" );
			test.equal( grunticon.options.previewTemplate, path.join( __dirname, "..", "..", "static", "preview.hbs" ) );
			test.equal( grunticon.options.compressPNG, false );
			test.equal( grunticon.options.optimizationLevel, 3 );
			test.equal( grunticon.options.enhanceSVG, false );
			test.equal( grunticon.options.corsEmbed, false );

			test.done();
		}
	};

	exports.generateLoader = {
		setUp: function( done ){
			done();
		},
		tearDown: function( done ){
			done();
		},
		noArgs: function( test ){
			var loader = Grunticon.generateLoader();

			test.equal(loader.indexOf(".embedSVG"), -1, "embed svg should not be included");
			test.equal(loader.indexOf(".embedSVGCors"), -1, "embed svg cors should not be included");
			test.done();
		},
		enhanceSVG: function( test ){
			var loader = Grunticon.generateLoader({
				enhanceSVG: true
			});

			test.ok(loader.indexOf(".embedSVG") > -1, "embed svg should be included");
			test.equal(loader.indexOf(".embedSVGCors"), -1, "embed svg cors should not be included");
			test.done();
		}
	};

	exports.process = {
		setUp: function(done) {
			// setup here if necessary
			done();
		},
		tearDown: function( done ){
			var output = path.join( __dirname, "output" );
			var files = fs.readdirSync( output )
			.map(function( filename ){
				return path.join( output, filename );
			});

			var notFiles = files.filter(function(file){
				return !fs.lstatSync( file ).isFile();
			});

			files.filter(function(file){
				return fs.lstatSync( file ).isFile();
			})
			.forEach(fs.unlinkSync);

			notFiles.filter(function(file){
				return fs.lstatSync( file ).isDirectory();
			})
			.forEach(fs.removeSync);

			done();
		},
		onefileFilesExist: function( test ){
			test.expect(6);
			var files = [path.join( __dirname, "files", "bear.svg" )];
			var output = path.join( __dirname, "output" );
			var grunticon = new Grunticon( files, output );

			grunticon.process(function(status){
				if( status === false ){
					test.ok( status, "status was bad" );
					test.done();
				}

				test.ok( fs.existsSync( path.join( output, "preview.html" ),        "preview should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "grunticon.loader.js" ), "loader file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "icons.data.svg.css" ),  "icon css file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "icons.data.png.css" ),  "icon css file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "icons.fallback.css" ),  "icon css file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "png", "bear.png" ),     "png file should have been created" ) );

				test.done();
			});
		},
		onefileContents: function( test ){
			test.expect(4);
			var files = [path.join( __dirname, "files", "bear.svg" )];
			var output = path.join( __dirname, "output" );
			var expected = path.join( __dirname, "expected" );

			var expectedContents = {
				preview:     fs.readFileSync( path.join( expected, "preview.html" ) ).toString( "utf-8" ),
				loader:      fs.readFileSync( path.join( expected, "grunticon.loader.js" ) ).toString( "utf-8" ),
				svgcss:      fs.readFileSync( path.join( expected, "icons.data.svg.css" ) ).toString( "utf-8" ),
				pngcss:      fs.readFileSync( path.join( expected, "icons.data.png.css" ) ).toString( "utf-8" ),
				fallbackcss: fs.readFileSync( path.join( expected, "icons.fallback.css" ) ).toString( "utf-8" ),
				png:         fs.readFileSync( path.join( expected, "png", "bear.png" ) )
			};


			var grunticon = new Grunticon( files, output );

			grunticon.process(function(status){
				if( status === false ){
					test.ok( status, "status was bad" );
					test.done();
				}


				var actualContents = {
					preview:     fs.readFileSync( path.join( output, "preview.html" ) ).toString( "utf-8" ),
					loader:      fs.readFileSync( path.join( output, "grunticon.loader.js" ) ).toString( "utf-8" ),
					svgcss:      fs.readFileSync( path.join( output, "icons.data.svg.css" ) ).toString( "utf-8" ),
					pngcss:      fs.readFileSync( path.join( output, "icons.data.png.css" ) ).toString( "utf-8" ),
					fallbackcss: fs.readFileSync( path.join( output, "icons.fallback.css" ) ).toString( "utf-8" ),
					png:         fs.readFileSync( path.join( output, "png", "bear.png" ) )
				};


				//test.deepEqual( actualContents.preview,             expectedContents.preview, "preview should have been created" );
				//test.deepEqual( actualContents.loader,              expectedContents.loader, "loader's contents should match" );
				test.deepEqual( actualContents.svgcss,              expectedContents.svgcss, "icon svg css file should match" );
				test.deepEqual( actualContents.pngcss,              expectedContents.pngcss, "icon png css file should match" );
				test.deepEqual( actualContents.fallbackcss,         expectedContents.fallbackcss, "icon fallback file should match" );
				test.deepEqual( compare( actualContents.png, expectedContents.png ), 0, "png file should match" );


				test.done();
			});
		},
		largeAmount: function( test ){
			test.expect(3);
			var directory = path.join( __dirname, "files", "large" );
			var files = fs.readdirSync( directory )
				.map(function( filename ){
					return path.join( directory, filename );
				});

			var output = path.join( __dirname, "output" );
			var expected = path.join( __dirname, "expected", "large" );

			var expectedContents = {
				preview:     fs.readFileSync( path.join( expected, "preview.html" ) ).toString( "utf-8" ),
				loader:      fs.readFileSync( path.join( expected, "grunticon.loader.js" ) ).toString( "utf-8" ),
				svgcss:      fs.readFileSync( path.join( expected, "icons.data.svg.css" ) ).toString( "utf-8" ),
				pngcss:      fs.readFileSync( path.join( expected, "icons.data.png.css" ) ).toString( "utf-8" ),
				fallbackcss: fs.readFileSync( path.join( expected, "icons.fallback.css" ) ).toString( "utf-8" )
			};


			var grunticon = new Grunticon( files, output );

			grunticon.process(function(status){
				if( status === false ){
					test.ok( status, "status was bad" );
					test.done();
				}


				var actualContents = {
					preview:     fs.readFileSync( path.join( output, "preview.html" ) ).toString( "utf-8" ),
					loader:      fs.readFileSync( path.join( output, "grunticon.loader.js" ) ).toString( "utf-8" ),
					svgcss:      fs.readFileSync( path.join( output, "icons.data.svg.css" ) ).toString( "utf-8" ),
					pngcss:      fs.readFileSync( path.join( output, "icons.data.png.css" ) ).toString( "utf-8" ),
					fallbackcss: fs.readFileSync( path.join( output, "icons.fallback.css" ) ).toString( "utf-8" )
				};


				//test.deepEqual( actualContents.preview,             expectedContents.preview, "preview should have been created" );
				//test.deepEqual( actualContents.loader,              expectedContents.loader, "loader's contents should match" );
				test.deepEqual( actualContents.svgcss,              expectedContents.svgcss, "icon svg css file should match" );
				test.deepEqual( actualContents.pngcss,              expectedContents.pngcss, "icon png css file should match" );
				test.deepEqual( actualContents.fallbackcss,         expectedContents.fallbackcss, "icon fallback file should match" );


				test.done();
			});
		},

		onlyPng: function ( test ) {
			test.expect(6);

			var files = [path.join( __dirname, "files", "bear.png" )];
			var output = path.join( __dirname, "output" );
			var grunticon = new Grunticon( files, output );

			grunticon.process(function(status){
				if( status === false ){
					test.ok( status, "status was bad" );
					test.done();
				}

				test.ok( fs.existsSync( path.join( output, "preview.html" ),        "preview should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "grunticon.loader.js" ), "loader file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "icons.data.svg.css" ),  "icon css file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "icons.data.png.css" ),  "icon css file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "icons.fallback.css" ),  "icon css file should have been created" ) );
				test.ok( fs.existsSync( path.join( output, "png", "bear.png" ),     "png file should have been created" ) );

				test.done();
			});


		}

	};

}(typeof exports === 'object' && exports || this));
