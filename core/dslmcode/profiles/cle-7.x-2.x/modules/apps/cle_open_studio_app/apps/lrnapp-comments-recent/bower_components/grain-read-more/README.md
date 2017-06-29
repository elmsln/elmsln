[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg)](https://www.webcomponents.org/element/daKmoR/grain-read-more)
[![Polymer Version](https://img.shields.io/badge/polymer-v2-blue.svg)](https://www.polymer-project.org)

# \<grain-read-more\>

Opens more content on click.

## Demo
<!---
```
<custom-element-demo>
  <template>
    <script src="../webcomponentsjs/webcomponents-lite.js"></script>
    <link rel="import" href="grain-read-more.html">
    <next-code-block></next-code-block>
  </template>
</custom-element-demo>
```
-->
```html
<grain-read-more>
  <h3>Read More</h3>
  <div slot="more">
    The Content is only visible if grain-read-more is opened
  </div>
</grain-read-more>
```

## Installation

```sh
$ bower install --save daKmoR/grain-read-more
```

## Getting Started

Import the package.

```html
<link rel="import" href="/bower_components/grain-read-more/grain-read-more.html">
```

Create the element providing a more slot.

```html
<grain-read-more>
  <h3>Read More</h3>
  <div slot="more">
    The Content is only visible if grain-read-more is opened
  </div>
</grain-read-more>
```

* Elements tagged with `slot="more"` will only become visible if grain-read-more is opened.
* Elements tagged with `slot="intro"` will always be visible.
* Elements with no slot attributed will trigger opened to be "true"/"false"

```html
<grain-read-more opened="true">
  <h3>Read More - opened by default</h3>
  <div slot="more">
    The Content is only visible if grain-read-more is opened
  </div>
</grain-read-more>
```

*For more information, see the API documentation.*

## Working on the Element

First, make sure you have the [Polymer CLI](https://www.npmjs.com/package/polymer-cli) installed.
* View the Element via `polymer serve`
* Run tests via `polymer test`
