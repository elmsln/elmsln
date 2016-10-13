# Grunticon-Lib [![Build Status](https://travis-ci.org/filamentgroup/grunticon-lib.png?branch=master)](https://travis-ci.org/filamentgroup/grunticon-lib)

[![Join the chat at https://gitter.im/filamentgroup/grunticon](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/filamentgroup/grunticon?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

```
         /'
        //
    .  //
    |\//7
   /' " \
  .   . .
  | (    \
  |  '._  '
  /    \'-'

```

[![Filament Group](http://filamentgroup.com/images/fg-logo-positive-sm-crop.png) ](http://www.filamentgroup.com/)

### A mystical CSS icon solution

grunticon is a stand-alone library that powers the one and only
[Grunticon](https://github.com/filamentgroup/grunticon)!


## Getting Started

Install this plugin with this command:

```shell
npm install grunticon-lib --save
```

### To Use:

```JavaScript
var Grunticon = require( 'grunticon-lib' );
var grunticon = new Grunticon( listOfFiles, destination, options );
grunticon.process(callback);
```

### Gulp

If you're a [Gulp](http://gulpjs.com/) user check out [gulpicon](https://github.com/filamentgroup/gulpicon) or simply create your own [task](https://gist.github.com/dcalhoun/e79ad10d518612d70721).

### Required Parameters

#### listOfFiles
Type: `Array`

Grunticon's constructor will either take an array of files you'd like read for its first argument.
These will be the files processed.

#### destination
Type: `String`

Grunticon's constructor will take a string that is the directory you'd like
to output the CSS files, the PNG folder, and the preview HTML for its second
argument.

### Options

#### options.datasvgcss
Type: `String`
Default value: `"icons.data.svg.css"`

The name of the generated CSS file containing SVG data uris.

#### options.datapngcss
Type: `String`
Default value: `"icons.data.png.css"`

The name of the generated CSS file containing PNG data uris

#### options.urlpngcss
Type: `String`
Default value: `"icons.fallback.css"`

The name of the generated CSS file containing external png url references.

#### options.previewhtml
Type: `String`
Default value: `"preview.html"`

The name of the generated HTML file containing PNG data uris.


#### options.loadersnippet
Type: `String`
Default value: `"grunticon.loader.js"`

The name of the generated text file containing the grunticon loading snippet.

#### options.enhanceSVG
Type: `Boolean`
Default value: `False`

Include additional methods in the loader script to offer SVG embedding

#### options.corsEmbed
Type: `Boolean`
Default value: `False`

Include additional methods in the loader script to offer cross-domain SVG embedding. `options.enhanceSVG` must be `true` for this option to be respected.

#### options.pngfolder
Type: `String`
Default value: `"png/"`

 The name of the generated folder containing the generated PNG images.

#### options.pngpath
Type: `String`
Default value: value of `options.pngfolder`

Allows you to specify a custom URL to serve fallback PNGs at.

Example:

```
{
    pngpath: "/assets/icons/png"
}
```

Will generate PNG fallbacks like:

```
.icon-bar {
	background-image: url('/assets/icons/png/bar.png');
	background-repeat: no-repeat;
}
```

#### options.cssprefix
Type: `String`
Default value: `".icon-"`

a string to prefix all icon selectors with (currently only classes or
ids are guaranteed to work with the preview)

#### options.customselectors
Type: `Object`

Allows you to specify custom selectors (in addition to the generated `cssprefix + filename - extension` class) for individual files.

Example:

```JavaScript
{
	"foo": [".icon-bar", ".baz"]
}
```

will produce:

```css
.icon-bar,
.bar,
.icon-foo {
	//css
}
```

You can also use an asterisk in your custom selector!

Examples:

```JavaScript
customselectors: {
  "*": [".icon-$1:before", ".icon-$1-what", ".hey-$1"]
},
cssprefix: ".icon-"
```

Should give the file bear.svg the css
```css
.icon-bear:before,
.icon-bear-what,
.hey-bear,
.icon-bear {
 // CSS THINGS
}
```

And if there are files bear.svg and cat.svg, the css should be like:

```css
.icon-bear:before,
.icon-bear-what,
.hey-bear,
.icon-bear {
 // CSS THINGS
}

.icon-cat:before,
.icon-cat-what,
.hey-cat,
.icon-cat {
 // CSS THINGS
}
```

This should give you more flexibility with your selectors.

#### options.defaultWidth
Type: `String`
Default value: `"400px"`

a string that MUST be defined in px that will be the size of the PNG if there is no width given in the SVG element.

#### options.defaultHeight
Type: `String`
Default value: `"300px"`

similar to defaultWidth, but for height

#### options.previewTemplate
Type: `String`
Default value: Goes to the example/preview.hbs file

Takes a path to the template that will be used for the preview.html. Example of .hbs file contents:

```html
<!doctype HTML>
<html>
  <head>
    <title>Icons Preview!</title>
    <style>
      body {
        background-image: linear-gradient(#eee 25%, transparent 25%, transparent), linear-gradient(#eee 25%, transparent 25%, transparent), linear-gradient(transparent 75%, #eee 75%), linear-gradient(transparent 75%, #eee 75%);
        width: 100%;
        background-size: 10px 10px;
      }
    </style>
    <script>
      {{{loaderText}}}
      grunticon(["icons.data.svg.css", "icons.data.png.css", "icons.fallback.css"]);
    </script>
  <noscript><link href="icons.fallback.css" rel="stylesheet"></noscript>
  </head>
  <body>
    {{#each icons}}
      {{#with this}}
      <pre><code>{{prefix}}{{name}}:</code></pre><div class="{{prefixClass}}{{name}}" style="width: {{width}}px; height: {{height}}px;" ></div><hr/>
      {{/with}}
    {{/each}}
</body>
</html>
```

#### options.tmpPath
Type: `String`
Default value: `os.tmpDir()`

Let's you specify an absolute tmp-path (`options.tmpDir` will still be appended).

#### options.tmpDir
Type: `String`
Default value: `"grunticon-tmp"`

Let's you specify a tmp-folder. Useful when having multiple grunticon tasks and using [grunt-concurrent](https://github.com/sindresorhus/grunt-concurrent "grunt-concurrent on github").

#### options.template
Type: `String`
Default value: `""`

Location of a handlebars template that will allow you to structure your
CSS file the way that you choose. As more data becomes available via
[directory-encoder](https://github.com/filamentgroup/directory-encoder),
more options will be available for you to tap into during templating.


Example of .hbs file contents:

```css
{{#each customselectors}}{{this}},{{/each}}
{{prefix}}{{name}} {
	background-image: url('{{datauri}}');
	background-repeat: no-repeat;
}
```

#### options.compressPNG
Type: `Boolean`
Default value: `false`

Will compress the converted png files using optipng


#### options.optimizationLevel
Type: `Integer`
Default value: `3`

If compress is set to `true`, this will set the optimationLevel for optipng

#### options.colors

Allows you to predefine colors as variables that can be used in filename color configuration.
```js
options: {
	colors: {
		myAwesomeRed: "#fc3d39",
		coolBlue: "#6950ff"
	}
```

#### options.dynamicColorOnly
Type: `Boolean`
Default value: `false`

Allows you to tell directory-colorfy to ignore the original file when
using colors.

For example, if given a file named like so:

```
bear.colors-white.svg
```

And `dynamicColorOnly` is set to `true`:

```js
{
	dynamicColorOnly: true
}
```

Only a single file will be generated:

```
bear-white.svg
```


### Grunticon Loader Methods

With `enhanceSVG` turned on, the Grunticon loader has a few exposed methods and attributes on the `grunticon` object that you can use:

#### href
Type: `String`

The url that is being loaded by Grunticon.

#### method
Type: `String`

Is `"svg"` if the page loaded the SVG-based css.
Is `"datapng"` if the page loaded the png with datauri-based css.
Is `"png"` if the page loaded the plain link to png-based css.

#### loadCSS
See: https://github.com/filamentgroup/loadcss

#### getCSS
Arguments: `String`
Returns: `Object`

Fetch a stylesheet `link` by its `href`.

#### getIcons
Arguments: `String`, `Boolean`?
Returns: `Object`

Takes a stylesheet node (`link` or `style`) and returns all of the icon selectors and the svgs contained within it in an object formatted in this way:
```
{
  grunticon:selector: "SVG Content in String"
}
```

**NOTE** The return value of this function is cached unless `true` is passed as a second argument:

```javascript
var icons = window.grunticon.getIcons(...);
console.log(icons.foo);        // => undefined
icons.foo = "bar";
window.gruntIcon(...);
console.log(icons.foo);        // => bar
window.gruntIcon(..., true);
console.log(icons.foo);        // => undefined
```

#### embedIcons
Arguments: `DOM Element` | `Object`, `Object`?
Returns: `NodeList`

Takes icons in the object format outputted by `getIcons` and then queries the
page for all icons with the `data-grunticon-embed` attribute. For each of these
that it finds, it places the SVG contents associated with the relevant selector
in the icons. It then returns the NodeList of all of the elements that had SVGs
embedded in them.

```javascript
window.grunticon.embedIcons(getIcons(...));
```

This function can also be targeted at a particular DOM node. For example, when scripting in the page replaces DOM nodes that have embedded SVG:

```javascript
window.grunticon.embedIcons(document.querySelector('.replaced'), getIcons(...));
```

#### ready
Arguments: `Function`
Returns: None

An alternative to listening for the `DOMContentLoaded` event. Takes a function as a callback and calls the function
when the DOM is ready.

### svgLoadedCallback

**NOTE** `svgLoadedCallback` has been deprecated in favor of `embedSVG`. 

#### embedSVG
Arguments: `DOM Element` | `Function`, `Function`?
Returns: None

If `embedComplete` is defined, the loader will call it when SVG embedding is
complete. This is true for both local and CORS embedding. So if you need to run
logic after SVG markup is appended to the DOM, just pass a callback to
`grunticon.svgLoadedCallback` or `grunticon.svgLoadedCORSCallback`.

```javascript
window.grunticon.embedSVG(function(){
  console.log("embed complete!");
});
```

Alternately you can target a particular element, for example, when it's replaced
in the DOM:

```javascript
window.grunticon.embedSVG(document.querySelector('.replaced'), function(){
  console.log("embed complete!");
});
```

### Cross-domain SVG Embedding Methods

With `enhanceSVG` and `corsEmbed` turned on, the Grunticon loader has a few exposed 2 more methods and attributes on the `grunticon` object that you can use:

#### ajaxGet
Arguments: `String`, `Function`
Returns: `Object`

First argument is a string reference to a url to request via cross-domain Ajax. Second argument is an optional callback when the request finishes loading. (In the callback, `this` refers to the XHR object).


#### svgLoadedCORSCallback
Arguments: `Function`
Returns: None

Uses the above methods to make SVG embedding work when CSS is hosted on another domain. (CORS must be allowed on the external domain.)


## Warnings
* If your files have `#`, `.`, `>`, or any other css selecting character in their names, they will likely be improperly processed.

## Release History
* Version 1.0.0: First release. Breaking out Grunticon from its previous Grunt.js dependency.
