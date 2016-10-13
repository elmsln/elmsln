
/*global require:true*/
(function( exports ){
	"use strict";

	var path = require( 'path' );
	var fs = require( 'fs' );
	var DirectoryColorfy = require( path.join( '..', 'lib', 'directory-colorfy' ) );


	exports.constructor = {
		setUp: function( done ) {
			this.dc = new DirectoryColorfy( "test/files" , "test/files" );
			this.dc2 = new DirectoryColorfy( "test/files", "test/files/temp",
																			{ colors: {
																					"blue": "blue"
																				}
																			});
			this.dc3 = new DirectoryColorfy( ["test/files/bear.colors-blue-red.svg"] , "test/files" );
			this.dc4 = new DirectoryColorfy( "test/files", "test/files/temp2",
																			{ colors: {
																					"secondary": "yellow"
																				}
																			});
			done();
		},
		tearDown: function( done ){
			done();
		},
		emptyConstructor: function( test ){
			test.equal( Object.keys( this.dc.options ).length, 0 , "Empty options hash on constructor" );
			test.done();
		},
		constructor: function( test ){
			test.equal( this.dc.files.length , 6, "Amount of files correct" );
			test.equal( this.dc2.input, "test/files", "Input filled in on constuctor" );
			test.equal( this.dc2.output, "test/files/temp", "Output filled in on constuctor" );
			test.equal( Object.keys( this.dc2.options.colors ).length, 1, "Colors filled" );
			test.equal( Object.keys(this.dc2.options.colors)[0], "blue", "Colors filled" );
			test.equal( this.dc3.files.length , 1, "Amount of files correct" );
			test.equal( this.dc4.files.length , 6, "Amount of files correct" );
			test.equal( Object.keys( this.dc4.options.colors ).length, 1, "Colors filled" );
			test.done();
		}
	};
	exports.convertString = {
		setUp: function( done ) {
			this.dc = new DirectoryColorfy( ["test/files/directory-colorfy/cat.colors-primary-secondary.svg"] , path.resolve( path.join( "test", "files", "temp" )),
																		{ colors: {
																				"primary": "green",
																				"secondary": "orange"
																			}
																		});
			done();
		},
		tearDown: function( done ){
			["cat", "cat-primary", "cat-secondary"].forEach( function( base ){
				if( fs.existsSync( "test/files/temp/" + base + ".svg" ) ){
					fs.unlinkSync( "test/files/temp/" + base + ".svg" );
				}
			});
			done();
		},
		convert: function( test ){
			test.expect(3);
			this.dc.convert()
			.then(function(){
				test.ok( fs.existsSync( "test/files/temp/cat.svg" ) , "Cat is there" );
				test.ok( fs.existsSync( "test/files/temp/cat-primary.svg" ) , "Green cat is there" );
				test.ok( fs.existsSync( "test/files/temp/cat-secondary.svg" ) , "Orange cat is there" );
				test.done();
			})
			.catch(function(err){
				console.log(err);
				test.done();
			});
		}
	};

	exports.convertDir = {
		setUp: function( done ) {
			this.dc = new DirectoryColorfy( "test/files/directory-colorfy" , path.resolve( path.join( "test", "files", "temp" )),
																		{ colors: {
																				"primary": "green",
																				"secondary": "orange"
																			}
																		});
			done();
		},
		tearDown: function( done ){
			["bear", "cat", "cat-primary", "cat-secondary"].forEach( function( base ){
				if( fs.existsSync( "test/files/temp/" + base + ".svg" ) ){
					fs.unlinkSync( "test/files/temp/" + base + ".svg" );
				}
			});
			done();
		},
		convert: function( test ){
			test.expect(4);
			this.dc.convert()
			.then(function(){
				test.ok( !fs.existsSync( "test/files/temp/bear.svg" ) , "Bear is not there" );
				test.ok( fs.existsSync( "test/files/temp/cat.svg" ) , "Cat is there" );
				test.ok( fs.existsSync( "test/files/temp/cat-primary.svg" ) , "Green cat is there" );
				test.ok( fs.existsSync( "test/files/temp/cat-secondary.svg" ) , "Orange cat is there" );
				test.done();
			})
			.catch(function(err){
				console.log(err);
				test.done();
			});
		}
	};

	exports.convertDirDynamicOnly = {
		setUp: function( done ) {
			this.dc = new DirectoryColorfy( "test/files/directory-colorfy" , path.resolve( path.join( "test", "files", "temp" )),
																			{ colors: {
																				"primary": "green",
																				"secondary": "orange"
																			},
																			dynamicColorOnly: true
																		});
			done();
		},
		tearDown: function( done ){
			["bear", "cat", "cat-primary", "cat-secondary"].forEach( function( base ){
				if( fs.existsSync( "test/files/temp/" + base + ".svg" ) ){
					fs.unlinkSync( "test/files/temp/" + base + ".svg" );
				}
			});
			done();
		},
		convert: function( test ){
			test.expect(4);
			this.dc.convert()
			.then(function(){
				test.ok( !fs.existsSync( "test/files/temp/bear.svg" ) , "Bear is not there" );
				test.ok( !fs.existsSync( "test/files/temp/cat.svg" ) , "Cat is not there" );
				test.ok( fs.existsSync( "test/files/temp/cat-primary.svg" ) , "Green cat is there" );
				test.ok( fs.existsSync( "test/files/temp/cat-secondary.svg" ) , "Orange cat is there" );
				test.done();
			})
			.catch(function(err){
				console.log(err);
				test.done();
			});
		}
	};

}(typeof exports === 'object' && exports || this));

