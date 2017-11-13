&lt;juicy-html&gt; [![Build Status](https://travis-ci.org/Juicy/juicy-html.svg?branch=master)](https://travis-ci.org/Juicy/juicy-html)
==============
> Declarative way for client-side includes

`<juicy-html>` is a custom element that lets you load HTML partials from JS objects and external files into your DOM. It acts more or less, as `include` statement known in many other languages. It also provides a simple data binding, that works for native JS/HTML as well as for Polymer's `dom-bind`.

### External files
To load HTML from external file all you need is:
```html
<template is="juicy-html" href="./path/to/file.html"></template>
```

### Markup provided by attribute
```html
<template is="juicy-html" html="<h1>Hello World</h1>"></template>
```

### Data Binding
`juicy-html` may forward given model object to stamped elements.

```html
<template is="juicy-html"
  html='
    All those nodes will get <code>.model</code> property
    with the reference to the object given in model attribute.
    <template is="dom-bind">
      <p>which can be used by <span>{{model.polymer}}</span></p>
    </template>
    <custom-element>that uses `.model` property<custom-element>
    <script>
      // script that may use
      alert( document.currentScript.model );
    </script>'
  model='{
    "polymer": "Polymer&apos;s dom-bind",
    "vanilla": "as well as by native JS <code>&amp;lt;script&amp;gt;</code> or custom elements"
   }'>
```
HTML may naturally be provided from external file, and `model` can be provided using Polymer's/or any other data-binding as real object (not a string)


## Demo

[Live examples](http://Juicy.github.io/juicy-html)

### Rationale

`juicy-html` provides a way to extend native [`<template>`](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/template)'s feature to be able to load content from outside (external file, data server, etc.).

It was started as an addition to [Polymer](http://www.polymer-project.org/)'s template binding, as there is no built-in way to insert a `<template>`'s model variable as HTML (Polymer inserts every string as plain text), AngularJS has a way to do it ([ngBindHtml](http://docs.angularjs.org/api/ng.directive:ngBindHtml)) so we found it convenient to do so in Polymer.

Currently it plain JavaScript, library agnostic custom element, that should work fine with any kind of binding, or none - as simple way to include HTML content from outside.

### Features

Your HTML partials can contain:
 - regular HTML
 - inline scripts using `<script>//JS code here</script>`
 - inline styles using `<style>/*CSS code here*/</style>`
 - external stylesheets using `<link rel="stylesheet" href="path/to/file.css">`, with `href` value relative to the document
 - external scripts using `<script src="path/relative/to/main/document.js"></script>`

Of course, the 2-way data binding attached within your partials will work as desired.

Please note, that loaded `<script>` and `<style>` will be executed every time HTML content is stamped to your document.


## Usage

1. Import Web Components' polyfill (if needed):

    ```html
    <script src="bower_components/webcomponentsjs/webcomponents.js"></script>
    ```

2. Import Custom Element:

    ```html
    <link rel="import" href="bower_components/juicy-html/juicy-html.html">
    ```

3. Start using it!

	Load HTML partial from a string:

	```html
	<template is="juicy-html" html="<b>some</b> HTML"></template>
	<!-- Or <template is="juicy-html" html="{{var}}"></template> where {{ var }} equals "<b>some</b> HTML" -->
	```

	Load HTML partial from a URL:

	```html
	<template is="juicy-html" href="./path/to/file.html"></template>
	<!-- Or <template is="juicy-html" href="{{var}}"></template>
	     where {{var}} equals "./path/to/file.html", a path relative to the document that must start with / or ./ -->
	```

## Attributes

Attribute           | Options         | Default     | Description
---                 | ---             | ---         | ---
`html`              | *String*		  | `""`	    | Safe HTML code to be stamped. Setting this one will skip any pending request for `href` and remove `href` attribute.
`href`              | *String*		  | `""`	    | Path of a partial to be loaded. Setting this one will remove `html` attribute.
`model`(_optional_) | *Object/String* | `undefined` | Object (or `JSON.stringify`'ied Object) to be attached to every root node of loaded document

## Properties

Property       | Type              | Default     | Description
---            | ---               | ---         | ---
`model`        | *Object*          | `undefined` | See [attributes](#Attributes), plays nice with Polymer data-binding
`html`         | *String*          | `""`	     | See [attributes](#Attributes)
`href`         | *String*          | `""`	     | See [attributes](#Attributes)
`pending`      | *XMLHttpRequest*  |             | pending XHR if any
`stampedNodes` | *Array*           | `[]`        | Array of stamped nodes.

Please note, that properties are available after element is upgraded.
To provide a state before element is upgraded, please use attributes.

## Events

Name      | details             | Description
---       | ---                 | ---
`stamped` | *Array* of *Node* s | Trigger every time content is (re-)stamped, with array of stamped nodes in `event.detail`

## Methods

Name                      | Description
---                       | ---
`skipStampingPendingFile` | Call to disregard currently pending request

### Dependencies

`<juicy-html>` is framework agnostic custom element, so all you need is Web Components support.
However, it plays really nice with [Polymer](http://www.polymer-project.org/) [Auto-binding templates](https://www.polymer-project.org/1.0/docs/devguide/templates.html#dom-bind), or any other binding library, that sets HTML elements' properties and/or attributes. Check our demos and examples.

## Browser compatibility

Name         | Support    | Comments
-------------|------------|---------
Chrome 48    | yes        |
Firefox 43   | yes        |
IE 11        | partially  | `document._currentScript` behaves wrong in inserted scripts
Edge 25      | yes        |
Safari 10-11 | yes        |
Safari 9-    | not tested |

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -m 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## History

For detailed changelog, check [Releases](https://github.com/Juicy/juicy-element/releases).

## License

MIT
