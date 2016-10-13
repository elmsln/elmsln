/*global module:true*/
/*global test:true*/
/*global asyncTest:true*/
/*global expect:true*/
/*global ok:true*/
/*global start:true*/
/*global equal:true*/
(function(window) {
  var document = window.document;
	/*
		======== A Handy Little QUnit Reference ========
		http://api.qunitjs.com/

		Test methods:
			module(name, {[setup][ ,teardown]})
			test(name, callback)
			expect(numberOfAssertions)
			stop(increment)
			start(decrement)
		Test assertions:
			ok(value, [message])
			equal(actual, expected, [message])
			notEqual(actual, expected, [message])
			deepEqual(actual, expected, [message])
			notDeepEqual(actual, expected, [message])
			strictEqual(actual, expected, [message])
			notStrictEqual(actual, expected, [message])
			throws(block, [expected], [message])
	*/

	module( 'Grunticon Loader Setup' );

  var bearSVG = '<svg xmlns="http://www.w3.org/2000/svg" width="100" height="62.905"><path d="M11.068 34.558c-1.585-2.365-2.595-5.098-2.94-8.106-.343.092-.665.16-1.032.16-2.342 0-4.248-1.905-4.248-4.247 0-1.47.758-2.756 1.883-3.514L16.88 10.4c2.55-1.56 5.534-2.525 8.75-2.64l30.148.092L77.82 4.34v-.345C77.82 1.79 79.585 0 81.79 0c2.206 0 3.997 1.79 3.997 3.995 0 .345-.046.712-.138 1.034l2.042.274c2.365.46 4.156 2.55 4.156 5.052 0 .16 0 .298-.022.436l6.544 3.536c.94.368 1.63 1.31 1.63 2.388 0 .367-.068.69-.206 1.01l-1.63 3.697c-.805 1.31-2.182 2.228-3.79 2.41l-15.04 1.792-13.547 15.902 7.738 13.363 5.098 2.365c.803.552 1.354 1.493 1.354 2.55 0 1.698-1.378 3.077-3.1 3.077l-9.806.022c-2.524 0-4.706-1.424-5.808-3.49L52.88 44.26l-18.92.022 6.682 10.287 4.937 2.25c.918.55 1.515 1.537 1.515 2.663 0 1.7-1.378 3.076-3.077 3.076l-9.828.022c-2.388 0-4.5-1.286-5.65-3.215L19.334 44.74l-6.43 6.246-.527 4.087 2.158 1.423c.368.184.69.438.965.758 1.055 1.332.87 3.284-.46 4.34-.574.482-1.286.713-1.975.69l-4.317.022c-1.194-.14-2.273-.758-2.962-1.677l-5.03-8.68C.277 51.032 0 50 0 48.897c0-1.676.62-3.215 1.676-4.387l9.392-9.952z"/></svg>';

	test( 'function grunticon exists', function(){
		expect(2);
		ok( window.grunticon, "grunticon should exist on the window object" );
		ok( typeof window.grunticon === "function", "grunticon should be a function" );
	});

	test( 'loadCSS function exists', function(){
		expect(2);
		ok( window.grunticon.loadCSS, "grunticon.loadCSS should exist on the window object" );
		ok( typeof window.grunticon.loadCSS === "function", "grunticon.loadCSS should be a function" );
	});

	asyncTest( 'loadCSS loads css file', function(){
		expect(1);
		window.grunticon.loadCSS( "./files/loadcss.css" );

		setTimeout(function(){
			ok( Array.prototype.some.call(document.styleSheets, function(ss){
				return ss.href.match(/loadcss/);
			}),"File should load");
			start();
		}, 200);

	});

	test( 'getCSS function exists', function(){
		expect(2);
		ok( window.grunticon.getCSS, "grunticon.getCSS should exist on the window object" );
		ok( typeof window.grunticon.getCSS === "function", "grunticon.getCSS should be a function" );
	});

	test( 'getCSS returns link node', function(){
		expect(2);

		var stylesheet = document.createElement( "link" );
		var href = "files/icons.data.svg.css";
		stylesheet.href = href;
		stylesheet.rel = "stylesheet";
		document.head.appendChild(stylesheet);

		window.grunticon.href = href;

		var link = window.grunticon.getCSS( href );

		equal( link.nodeName, "LINK", "Link object returned" );
		ok( link.href.indexOf( href ) > -1, "Link object returned" );
	});

	test( 'getIcons function exists', function(){
		expect(2);
		ok( window.grunticon.getIcons, "grunticon.getIcons should exist on the window object" );
		ok( typeof window.grunticon.getIcons === "function", "grunticon.getIcons should be a function" );
	});

	test( 'getIcons returns object when passed a stylesheet node', function(){
		expect(1);

		var stylesheet = document.createElement( "link" );
		var href = "files/icons.data.svg.css";
		stylesheet.href = href;
		stylesheet.rel = "stylesheet";
		document.head.appendChild(stylesheet);

		var icons = window.grunticon.getIcons( stylesheet );

		equal( typeof icons, "object", "Type of icons should return 'object'" );
	});

	test( 'getIcons returns object with keys', function(){
		expect(1);

		var stylesheet = document.createElement( "link" );
		var href = "files/icons.data.svg.css";
		stylesheet.href = href;
		stylesheet.rel = "stylesheet";
		document.head.appendChild(stylesheet);

		var icons = window.grunticon.getIcons( stylesheet );

		equal( Object.keys(icons).length, 20, "There should be a number of icon objects returned" );
	});

	test( 'getIcons objects are accessible class with svg string', function(){
		expect(1);
		var stylesheet = document.createElement( "link" );
		var href = "files/icons.data.svg.css";
		stylesheet.href = href;
		stylesheet.rel = "stylesheet";
		document.head.appendChild(stylesheet);

		var icons = window.grunticon.getIcons( stylesheet );
    var svg = bearSVG;
		equal( icons['grunticon:.icon-bear'], svg, "SVG contents should match" );
	});

	test( 'getIcons caches icons object results and refreshes', function(){
		expect(3);
		var stylesheet = document.createElement( "link" );
		var href = "files/icons.data.svg.css";
		stylesheet.href = href;
		stylesheet.rel = "stylesheet";
		document.head.appendChild(stylesheet);

		// there is no test property on the icons object
		var icons = window.grunticon.getIcons( stylesheet );
		ok( !icons.testPreservedProperty );

		// changes to the object ref are preserved
		icons.testPreservedProperty = "foo";
		icons = window.grunticon.getIcons( stylesheet );
		equal( icons.testPreservedProperty, "foo" );

		// changes to the object ref are gone on refesh
		icons = window.grunticon.getIcons( stylesheet, true );
		ok( !icons.testPreservedProperty );
	});

	test( 'embedIcons embeds an icon', function(){
		expect(1);
		var svg = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100\" height=\"62.905\"><path d=\"M11.068 34.558c-1.585-2.365-2.595-5.098-2.94-8.106-.343.092-.665.16-1.032.16-2.342 0-4.248-1.905-4.248-4.247 0-1.47.758-2.756 1.883-3.514L16.88 10.4c2.55-1.56 5.534-2.525 8.75-2.64l30.148.092L77.82 4.34v-.345C77.82 1.79 79.585 0 81.79 0c2.206 0 3.997 1.79 3.997 3.995 0 .345-.046.712-.138 1.034l2.042.274c2.365.46 4.156 2.55 4.156 5.052 0 .16 0 .298-.022.436l6.544 3.536c.94.368 1.63 1.31 1.63 2.388 0 .367-.068.69-.206 1.01l-1.63 3.697c-.805 1.31-2.182 2.228-3.79 2.41l-15.04 1.792-13.547 15.902 7.738 13.363 5.098 2.365c.803.552 1.354 1.493 1.354 2.55 0 1.698-1.378 3.077-3.1 3.077l-9.806.022c-2.524 0-4.706-1.424-5.808-3.49L52.88 44.26l-18.92.022 6.682 10.287 4.937 2.25c.918.55 1.515 1.537 1.515 2.663 0 1.7-1.378 3.076-3.077 3.076l-9.828.022c-2.388 0-4.5-1.286-5.65-3.215L19.334 44.74l-6.43 6.246-.527 4.087 2.158 1.423c.368.184.69.438.965.758 1.055 1.332.87 3.284-.46 4.34-.574.482-1.286.713-1.975.69l-4.317.022c-1.194-.14-2.273-.758-2.962-1.677l-5.03-8.68C.277 51.032 0 50 0 48.897c0-1.676.62-3.215 1.676-4.387l9.392-9.952z\"></path></svg>";
		var name = ".icon-bear";

		var icons = {};
		icons["grunticon:" + name] = svg;

    window.grunticon.embedIcons(icons);
		equal( document.querySelector( name ).innerHTML, svg, "This div should have the bear svg inside of it" );
	});

	test( 'calling grunticon adds the grunticon class to the html element', function(){
		expect(1);

		window.grunticon("foo", "bar", "baz");
		ok( document.documentElement.className.match( "grunticon" ) );
	});

	test( 'ajaxGet function exists', function(){
		expect(2);
		ok( window.grunticon.ajaxGet, "grunticon.ajaxGet should exist on the window object" );
		ok( typeof window.grunticon.ajaxGet === "function", "grunticon.ajaxGet should be a function" );
	});

	asyncTest( 'ajaxGet makes an xhr request and returns callback', function(){
		expect(2);

		var xhr = window.grunticon.ajaxGet( window.location.href, function(){
			ok( this, "xhr request loaded" );
			start();
		} );
		equal( typeof xhr, "object", "ajaxGet returns an object" );
	});

	asyncTest( 'grunticon.embedComplete fires when embedSVG completes its embed', function(){
		expect(1);
		var old;
		var embedComplete = function(){
			ok( true, "Embed complete" );
			window.grunticon.method = old;
			start();
		};

		old = window.grunticon.method;
		window.grunticon.method = "svg";
		window.grunticon.href = "./files/icons.data.svg.css";
		window.grunticon.embedSVG( embedComplete );
	});

	asyncTest( 'grunticon.embedComplete fires when embedSVG completes its embed for particular elements', function(){
		expect(3);
		var old;
		var embedComplete = function(){
			ok( true, "Embed complete" );
			window.grunticon.method = old;
			start();

			var custChildren;

			// elements inside the child-embeds element should get svg
			custChildren = document
				.querySelectorAll(".child-embeds .icon-bear.embed > svg");
			equal(custChildren.length, 1);

			// embeds outside the child-embeds selector should remain untouched
			custChildren = document
				.querySelectorAll("#qunit-fixture > .icon-bear.embed > svg");
			equal(custChildren.length, 0);
		};

		old = window.grunticon.method;
		window.grunticon.method = "svg";
		window.grunticon.href = "./files/icons.data.svg.css";
		window.grunticon.embedSVG( document.querySelector('.child-embeds'), embedComplete );
	});

	test( 'grunticon.embedSVG works without arguments', function(){
		expect(2);
		var old;

		old = window.grunticon.method;
		window.grunticon.method = "svg";
		window.grunticon.href = "./files/icons.data.svg.css";
		window.grunticon.embedSVG();
		window.grunticon.method = old;

		var custChildren;

		// elements inside the child-embeds element should get svg
		custChildren = document
			.querySelectorAll(".child-embeds .icon-bear.embed > svg");
		equal(custChildren.length, 1);

		// embeds outside the child-embeds selector should remain untouched
		custChildren = document
			.querySelectorAll("#qunit-fixture > .icon-bear.embed > svg");
		equal(custChildren.length, 1);
	});


	test( 'icons with custom selector with embed should have an svg element', function() {
		var svg = bearSVG;
		var name = ".custom-selector-icon-bear, .icon-bear";

		var icons = {};
		icons["grunticon:" + name] = svg;

		window.grunticon.embedIcons(icons);

		var custChildren = document.querySelectorAll("#qunit-fixture > .custom-selector-icon-bear.embed > svg");
		equal(custChildren.length, 1);
	});

	test( 'icons with custom selector without embed shouldnt have an svg elements', function() {
		var svg = bearSVG;
		var name = ".custom-selector-icon-bear, .icon-bear";

		var icons = {};
		icons["grunticon:" + name] = svg;

		window.grunticon.embedIcons(icons);

		var normalChildren = document.querySelectorAll("#qunit-fixture > .custom-selector-icon-bear.no-embed > svg");
		equal(normalChildren.length, 0);
	});

	test( 'elements with embed when parent is passed should have an svg element', function() {
		var svg = bearSVG;
		var name = ".custom-selector-icon-bear, .icon-bear";

		var icons = {};
		icons["grunticon:" + name] = svg;

		window.grunticon.embedIcons(document.querySelector('.child-embeds'), icons);

		var custChildren = document.querySelectorAll(".child-embeds .custom-selector-icon-bear.embed > svg");
		equal(custChildren.length, 1);
	});

	/**
	asyncTest( 'grunticon.embedComplete fires when embedSVGCors completes its embed', function(){
		expect(1);
		var embedComplete = function(){
			ok( true, "CORS Embed complete" );
			start();
		};
		grunticon.embedSVGCors( embedComplete );
	});
 */


}(this));
