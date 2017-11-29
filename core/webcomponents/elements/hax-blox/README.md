<!--
```
<custom-element-demo>
  <template>
    <link rel="import" href="hax-blox.html">
    <next-code-block></next-code-block>
  </template>
</custom-element-demo>
```
-->
```html
<hax-blox layout="cols-50">
  <img slot="area1" src="https://btopro.com/data/images/headshot.jpg" width="25%" height="25%" />
  <p slot="area2">Slotted area 2</p>
  <p slot="area3">Slotted area 3</p>
  A bunch of random text here
</hax-blox>
```

[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg)](https://www.webcomponents.org/element/LRNWebComponents/hax-blox)

# \<hax-blox\>

A LRN element for doing layout and design templates in HAX.

## How to create a new template
Let's make an example my-layout layout. Place an empty file in hax-blox/layouts/my-layout.html. In this file put whatever CSS, HTML and Javscript you'd like. In order to use the slotted areas passed down though you'll need to have the following id's used in your template:
- area1
- area2
- area3
- area4
- area5
- area6

for example `<div id="area1">`

### Style scoping
Because of how these templates get injected in place of the previous area, you'll need to do some minor style scoping to avoid global, inline css importing when shadydom is doing processing (this isn't required for shadow). To do this, in your `<style>` block, add the following to correctly scope `area1` as an example of the contents of those layout files.
```
<style>
  #hax-layout-[[model.layout]] #area2 {
    display: block;
  }
  #hax-layout-[[model.layout]] #area2 * {
    float: left;
  }
</style>
<div id="area1">
  <slot name="area1"></slot>
</div>
<div id="area2">
  <slot name="area2"></slot>
</div>
```

For more examples, you can look in the layouts directory of this repo. There's also support for a basePath property which if utilized on your hax-blox will cause it to look elsewhere for the template file. This can be useful when integrating with larger systems or pulling in templates from other locations (like a CMS).

## Install the Polymer-CLI

First, make sure you have the [Polymer CLI](https://www.npmjs.com/package/polymer-cli) installed. Then run `polymer serve` to serve your application locally.

## Viewing Your Application

```
$ polymer serve
```

## Building Your Application

```
$ polymer build
```

This will create a `build/` folder with `bundled/` and `unbundled/` sub-folders
containing a bundled (Vulcanized) and unbundled builds, both run through HTML,
CSS, and JS optimizers.

You can serve the built versions by giving `polymer serve` a folder to serve
from:

```
$ polymer serve build/bundled
```

## Running Tests

```
$ polymer test
```

Your application is already set up to be tested via [web-component-tester](https://github.com/Polymer/web-component-tester). Run `polymer test` to run your application's test suite locally.
