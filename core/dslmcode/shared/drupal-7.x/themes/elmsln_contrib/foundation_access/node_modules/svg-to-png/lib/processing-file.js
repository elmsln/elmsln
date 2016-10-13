/* Runs in phantom */
/*global module:true*/
/*global require:true*/
(function(){
	"use strict";

	var fs = require( 'fs' );


	var Gfile = function( filename ){
		var svgRegex = /\.svg$/i,
			fArr = filename.split( fs.separator );
		this.filename = fArr.pop();
		this.pathdir = fArr.join( fs.separator );
		if( !fs.exists( this.pathdir + fs.separator + this.filename ) ){
			throw new Error( this.pathdir + fs.separator + this.filename + " does not exist" );
		}
		this.filenamenoext = this.filename.replace( svgRegex , "" );
	};

	Gfile.prototype.setImageData = function(){
		this.imagedata = fs.read( this.pathdir + fs.separator + this.filename ) || "";
	};


	module.exports = Gfile;

}());
