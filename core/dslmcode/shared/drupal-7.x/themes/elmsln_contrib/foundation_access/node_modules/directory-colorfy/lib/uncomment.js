(function(exports){
	"use strict";

	var XMLHeader = function( svg ){
		if( typeof svg !== "string" ){
			throw new Error( "Expected a string to be passed in" );
		}

		svg = svg.replace( /<!--\?xml(.*)\?-->/, "<?xml$1?>" );
		return svg;
	};

	exports.XMLHeader = XMLHeader;

}(typeof exports === 'object' && exports || this));
