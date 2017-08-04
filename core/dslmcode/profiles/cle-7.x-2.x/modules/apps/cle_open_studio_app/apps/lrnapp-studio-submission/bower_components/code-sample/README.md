# &lt;code-sample&gt;
[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg?style=flat-square)](https://www.webcomponents.org/element/kcmr/code-sample)

> A wrapper element for [highlight.js](https://highlightjs.org/)

A themeable sample code snippet that uses [highlight.js](https://highlightjs.org/) for syntax highlighting.   
Forget to worry about spaces, indentation, HTML entities, etc.

<!---
```html
<custom-element-demo>
  <template>
    <script src="../webcomponentsjs/webcomponents-lite.js"></script>
    <link rel="import" href="themes/one-dark.html">
    <link rel="import" href="code-sample.html">
    <next-code-block></next-code-block>
  </template>
</custom-element-demo>
```
-->
```html
<code-sample>
  <template>
    <div class="some-class">
      <p>Lorem ipsum dolor…</p>
    </div>
  </template>
</code-sample>
```


## Installation

### Option 1 (preferred): using bower
1. Install the component using Bower:
  ```bash
  $ bower i -S code-sample
  ```
2. Import Web Components polyfill:
  ```html
  <script src="bower_components/webcomponentsjs/webcomponents-lite.js"></script>
  ```
3. Import the theme to be used and the component:
  ```html
  <link rel="import" href="bower_components/code-sample/themes/one-dark.html"> 
  <link rel="import" href="bower_components/code-sample/code-sample.html"> 
  ```

### Option 2: direct import from gh-pages branch
**Warning**: gh-pages branch is used for the demo and it may not be up to date.

1. Import Web Components polyfill, code-sample theme and code-sample:
  ```html
  <script src="https://cdn.rawgit.com/kcmr/code-sample/gh-pages/components/webcomponentsjs/webcomponents-lite.js"></script>
  <link async rel="import" href="https://cdn.rawgit.com/kcmr/code-sample/gh-pages/components/code-sample/themes/one-dark.html">
  <link async rel="import" href="https://cdn.rawgit.com/kcmr/code-sample/gh-pages/components/code-sample/code-sample.html">
  ```

## Usage

The code to highlight must be provided inside a `<template>` tag.

```html
<code-sample>
  <template>
    <p>your code here...</p>
  </template>
</code-sample>
```

When **used inside a custom element** you'll need to add the attribute `preserve-content` to the inner template to prevent Polymer to process the template's content.

```html
<code-sample>
  <template preserve-content>
    <p>your code here...</p>
  </template>
</code-sample>
```

To render the code inside the template, use the boolean attribute `render`.

```html
<code-sample render>
  <template>
    <my-custom-element></my-custom-element>
  </template>
</code-sample>
```

The `type` attribute specifies the language of the sample code (eg.: html, css, js) and is not needed most of the time because it's automatically set. You can use it when your code sample language is not properly detected.

```html
<code-sample type="css">
  <template>
    .some-class {
      @apply --my-mixin;
    }
  </template>
</code-sample>
```

## Themes

The component includes 6 themes that must be imported explicitly.

Example:

```html
<link rel="import" href="../code-sample/themes/one-dark.html">
<link rel="import" href="../code-sample/code-sample.html">
```

### Available themes

- atom-one-ligth.html
- default.html
- github.html
- one-dark.html
- solarized-dark.html
- solarized-light.html

### More themes

You can use another theme by adding one of the [available themes](https://github.com/isagalaev/highlight.js/tree/master/src/styles) for hightlight.js in a shared style ([Polymer Style Module](https://www.polymer-project.org/1.0/docs/devguide/styling#style-modules)) with the id `code-sample-theme`.

Example:

```html
<dom-module id="code-sample-theme">
  <template>
    <style>
    /* your own styles */
    </style>
  </template>
</dom-module>
```

### Styling

The following custom CSS properties are available for styling:

| Custom property                | Description                                                  | Default      |
|:-------------------------------|:-------------------------------------------------------------|:-------------|
| --code-sample-font-family      | font-family applied to `<pre>` and `<code>` elements         | Operator Mono, Inconsolata, Roboto Mono, monaco, consolas, monospace         |
| --code-sample-font-size        | font-size applied to `<pre>` and `<code>` elements           | 14px         |
| --code-sample-demo-padding     | padding applied to the container of the rendered code        | 0 0 20px     |
| --code-sample-demo             | empty mixin applied to the container of the rendered code    | {}           |

_Note:_ The [CSS mixin shim](https://www.polymer-project.org/2.0/docs/upgrade#css-custom-property-shim) is required to use mixins.

Included themes contain custom CSS properties to set the background and text color.   
You may need to add these CSS properties to your own themes.

| Custom property                | Description                             | Default     |
|:-------------------------------|:----------------------------------------|:------------|
| --code-sample-background       | code background color                   | Depends on the theme         |
| --code-sample-color            | code text color                         | Depends on the theme         |



