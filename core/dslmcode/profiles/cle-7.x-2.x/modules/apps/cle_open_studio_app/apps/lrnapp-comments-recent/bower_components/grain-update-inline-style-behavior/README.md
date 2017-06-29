[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg)](https://www.webcomponents.org/element/daKmoR/grain-update-inline-style-behavior)
[![Polymer Version](https://img.shields.io/badge/polymer-v2-blue.svg)](https://www.polymer-project.org)

# \<grain-update-inline-style-behavior\>

In order for inline styles to work with Browsers not supporting CSS Custom Properties you will have to save your style into data-style as well.
This behavior will extend updateStyles() to parse data-style and merge it with your styles.

## Demo
<!---
```
<custom-element-demo>
  <template>
    <script src="../webcomponentsjs/webcomponents-lite.js"></script>
    <link rel="import" href="grain-update-inline-style-behavior-example.html">
    <next-code-block></next-code-block>
  </template>
</custom-element-demo>
```
-->
```html
<grain-update-inline-style-behavior-example style="--background: yellow;" data-style="--background: yellow;">
	I am an element with some inline style. <br />
	My Background will be yellow even on Browsers not supporting CSS Custom Properties. <br />
	For it to work data-style will need to be the same as style in the HTML.
</grain-update-inline-style-behavior-example>
```

## Installation

```sh
$ bower install --save daKmoR/grain-update-inline-style-behavior
```

## Getting Started

Import the package.

```html
<link rel="import" href="/bower_components/grain-update-inline-style-behavior/grain-update-inline-style-behavior.html">
```

Create your element using this behavior.

```js
class GrainUpdateInlineStyleBehaviorExample extends GrainUpdateInlineStyleBehavior(Polymer.Element) {
  // your code
}
```

Insert your element with style and data-style

```html
<grain-update-inline-style-behavior-example style="--background: yellow;" data-style="--background: yellow;">
  Create Element with style AND data-style
</grain-update-inline-style-behavior-example>
```


*For more information, see the API documentation.*

## Working on the Element

First, make sure you have the [Polymer CLI](https://www.npmjs.com/package/polymer-cli) installed.
* View the Element via `polymer serve`
* Run tests via `polymer test`