[![Build Status](https://img.shields.io/travis/MaritzSTL/mtz-marked-editor/master.svg?style=flat-square)](https://travis-ci.org/MaritzSTL/mtz-marked-editor)
[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg?style=flat-square)](https://www.webcomponents.org/element/MaritzSTL/mtz-marked-editor)

# \<mtz-marked-editor\>
Extends a textarea that can be controlled by UI elements for inserting markdown.

<!-- 
```
<custom-element-demo>
  <template>
    <link rel="import" href="../iron-icons/editor-icons.html">
    <link rel="import" href="mtz-marked-editor.html">
    <link rel="import" href="mtz-marked-control-generic-line.html">
    <link rel="import" href="mtz-marked-control-generic-wrap.html">
    <link rel="import" href="controls/mtz-marked-control-link.html">

    <next-code-block></next-code-block>
  </template>
</custom-element-demo>
```
-->
```html
<mtz-marked-editor>
  <div slot="controls">
    <mtz-marked-control-generic-wrap
      icon="editor:format-bold"
      title="Bold"
      syntax-prefix="**"
      syntax-suffix="**"
      keys="ctrl+b"
    ></mtz-marked-control-generic-wrap>
    <mtz-marked-control-generic-wrap
      icon="editor:format-italic"
      title="Italic"
      syntax-prefix="_"
      syntax-suffix="_"
      keys="ctrl+i"
    ></mtz-marked-control-generic-wrap>
    <mtz-marked-control-generic-line
      icon="editor:format-size"
      title="Heading 1"
      syntax-prefix="# "
    ></mtz-marked-control-generic-line>
    <mtz-marked-control-generic-line
      icon="editor:format-list-numbered"
      title="Ordered List"
      syntax-prefix="1. "
    ></mtz-marked-control-generic-line>
    <mtz-marked-control-generic-line
      icon="editor:format-list-bulleted"
      title="Unordered List"
      syntax-prefix="- "
    ></mtz-marked-control-generic-line>
    <mtz-marked-control-link
      icon="editor:insert-link"
      title="Link"
    ></mtz-marked-control-link>
  </div>
  <textarea slot="textarea"></textarea>
</mtz-marked-editor>
```

## Install the Polymer-CLI

First, make sure you have the [Polymer CLI](https://www.npmjs.com/package/polymer-cli) installed. Then run `polymer serve` to serve your element locally.

## Viewing Your Element

```
$ polymer serve
```

## Running Tests

```
$ polymer test
```

Your application is already set up to be tested via [web-component-tester](https://github.com/Polymer/web-component-tester). Run `polymer test` to run your application's test suite locally.
