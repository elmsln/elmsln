/*global module:true*/
/*global __dirname:true*/
/*global require:true*/
(function(){
	"use strict";

	var path = require( 'path' );
	var fs = require( 'fs' );

	var RSVP = require( 'rsvp' );

	var Colorfy = require( path.join( __dirname, 'colorfy' ) );
	var ColorfyFromOptions = require( path.join( __dirname, 'colorfy-from-options' ) );
	var dirConvert = require( './directory-convert' );

	var DirectoryColorfy = function( input, output, opts ){
		var files;
		if( typeof input === "string" && fs.lstatSync( input ).isDirectory()){
			files = fs.readdirSync( input ).map( function( file ){
				return path.join( input, file );
			});
		} else if( Array.isArray( input ) ){
			files = input;
		} else {
			throw new Error( "Input must be Array of files or String that is a directory" );
		}

		this.files = files.filter(function( file ){
			return path.extname( file ) === ".svg";
		})
		.filter(function(file){
			return file.match(/\.colors/);
		});
		this.input = input;
		this.output = output;
		this.options = opts || {};
		this.colors = this.options.colors || {};
	};

	DirectoryColorfy.prototype.convert = function() {
        var promises = this.files.map(function(self, file) {
            return new Colorfy(file, self.colors, {
                dynamicColorOnly: self.options.dynamicColorOnly
            });
        }.bind(null, this));

        return new RSVP.Promise(function(self, colorfied, resolve, reject) {
            var filesWritten = [];
            var converted = [];

            var handlers = {
                collect: function(dc, err, output) {
                    if (err) {
                        reject(err);
                    } else {
                        converted.push(output);
                        if (converted.length === colorfied.length) {
                            filesWritten = converted.map(function(col) {
                                    var c = new ColorfyFromOptions(col);
                                    return c.writeFiles(this.output);
                                }, dc)
                                .reduce(function(a, b) {
                                    return a.concat(b);
                                });
                        }
                    }
                }.bind(null, self),

                complete: function() {
                    if (converted.length === colorfied.length) {
                        resolve(filesWritten);
                    }
                }
            };

            if (colorfied.length === 0) {
                resolve(filesWritten);
            } else {
                colorfied.forEach(function(colorfy) {
                    dirConvert(colorfy, handlers);
                });
            }
        }.bind(null, this, promises));
    };


	module.exports = DirectoryColorfy;

}(typeof exports === 'object' && exports || this));
