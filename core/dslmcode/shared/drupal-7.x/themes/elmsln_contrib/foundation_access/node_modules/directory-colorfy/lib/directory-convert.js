/*global module:true*/
/*global require:true*/
/*global __dirname:true*/
(function(){
	"use strict";
	var path = require( 'path' );
	var Colorfy = require( path.join( __dirname, "colorfy" ) );

	module.exports = function( colorfy, handlers ){
		Colorfy.convert( colorfy,
										colorfy.colors,
										colorfy.originalFilepath,
										colorfy.ofnNoExt,
										colorfy.originalContents,
										handlers );
	};

}());
