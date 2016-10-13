
/*global require:true*/
(function( exports ){

	"use strict";

	var path = require( 'path' );
	var uncomment = require( path.join('..', 'lib', 'uncomment') );
	var commentedHeader = '<!--?xml version="1.0" encoding="UTF-8" standalone="no"?--><svg width="5px" height="3px" viewBox="0 0 5 3" version="1.1" xmlns="http://www.w3.org/2000/svg" xlink="http://www.w3.org/1999/xlink" xmlns:sketch="http://www.bohemiancoding.com/sketch/ns"><!-- Generator: Sketch 3.0.1 (7597) - http://www.bohemiancoding.com/sketch --><title fill="red">Dropdown Arrow</title><description fill="red">Created with Sketch.</description><defs fill="red"></defs><g id="Header" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd" sketch:type="MSPage"><g id="Standby" sketch:type="MSArtboardGroup" transform="translate(-692.000000, -34.000000)" stroke-linecap="round" stroke="red" fill="red"><g id="Header" sketch:type="MSLayerGroup" fill="red"><g id="User" transform="translate(549.000000, 10.000000)" sketch:type="MSShapeGroup" fill="red"><g id="Dropdown-Arrow" transform="translate(143.000000, 24.000000)" fill="red"><path d="M0.5,0.5 L2.5,2.5" id="Line" fill="red"></path><path d="M2.5,2.5 L4.5,0.5" id="Line" fill="red"></path></g></g></g></g></g></svg>\n';
	var uncommentedHeader = '<?xml version="1.0" encoding="UTF-8" standalone="no"?><svg width="5px" height="3px" viewBox="0 0 5 3" version="1.1" xmlns="http://www.w3.org/2000/svg" xlink="http://www.w3.org/1999/xlink" xmlns:sketch="http://www.bohemiancoding.com/sketch/ns"><!-- Generator: Sketch 3.0.1 (7597) - http://www.bohemiancoding.com/sketch --><title fill="red">Dropdown Arrow</title><description fill="red">Created with Sketch.</description><defs fill="red"></defs><g id="Header" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd" sketch:type="MSPage"><g id="Standby" sketch:type="MSArtboardGroup" transform="translate(-692.000000, -34.000000)" stroke-linecap="round" stroke="red" fill="red"><g id="Header" sketch:type="MSLayerGroup" fill="red"><g id="User" transform="translate(549.000000, 10.000000)" sketch:type="MSShapeGroup" fill="red"><g id="Dropdown-Arrow" transform="translate(143.000000, 24.000000)" fill="red"><path d="M0.5,0.5 L2.5,2.5" id="Line" fill="red"></path><path d="M2.5,2.5 L4.5,0.5" id="Line" fill="red"></path></g></g></g></g></g></svg>\n';
	var commentedInSVG = '<?xml version="1.0" encoding="UTF-8" standalone="no"?><svg width="5px" height="3px" viewBox="0 0 5 3" version="1.1" xmlns="http://www.w3.org/2000/svg" xlink="http://www.w3.org/1999/xlink" xmlns:sketch="http://www.bohemiancoding.com/sketch/ns"><!-- Generator: Sketch 3.0.1 (7597) - http://www.bohemiancoding.com/sketch --><!-- SVGs are neat, right?--> <title fill="red">Dropdown Arrow</title><description fill="red">Created with Sketch.</description><defs fill="red"></defs><g id="Header" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd" sketch:type="MSPage"><g id="Standby" sketch:type="MSArtboardGroup" transform="translate(-692.000000, -34.000000)" stroke-linecap="round" stroke="red" fill="red"><g id="Header" sketch:type="MSLayerGroup" fill="red"><g id="User" transform="translate(549.000000, 10.000000)" sketch:type="MSShapeGroup" fill="red"><g id="Dropdown-Arrow" transform="translate(143.000000, 24.000000)" fill="red"><path d="M0.5,0.5 L2.5,2.5" id="Line" fill="red"></path><path d="M2.5,2.5 L4.5,0.5" id="Line" fill="red"></path></g></g></g></g></g></svg>\n';



	exports.xmlheader = {
		setUp: function( done ) {
			done();
		},

		tearDown: function( done ){
			done();
		},

		noargs: function( test ) {
			test.throws( function(){
				uncomment.XMLHeader();
			}, "No args should throw an error" );
			test.done();
		},

		stripHeader: function( test ){
			test.equal( uncomment.XMLHeader( commentedHeader ), uncommentedHeader, "The header's comment should be stripped" );
			test.done();
		},

		svgInternalComment: function( test ){
			test.equal( uncomment.XMLHeader( commentedInSVG ), commentedInSVG, "Comments in the SVG should be left alone" );
			test.done();
		},



	};


}(typeof exports === 'object' && exports || this));

