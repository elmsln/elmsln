[![Published on webcomponents.org][webcomponents-image]][webcomponents-url]

# \<circle-progress\>

Polymer-based web component displaying a circular progress bar.

Inspired by element [\<s-circle-progress\>](https://github.com/StartPolymer/s-circle-progress).

## Demo

[Full demo][webcomponents-demo]

## Usage

<!--
```
<custom-element-demo>
  <template>
    <script src="../webcomponentsjs/webcomponents-lite.js"></script>
    <link rel="import" href="circle-progress.html">
    <next-code-block></next-code-block>
  </template>
</custom-element-demo>
```
-->
```html
<circle-progress value="6" max="10">
  60%
</circle-progress>

<circle-progress value="30" angle="90" stroke-width="8">
  <b>30s</b>
</circle-progress>
```

### Styling

The following custom properties and mixins are available for styling:

Custom property | Description | Default
----------------|-------------|----------
`--circle-progress-bg-stroke-color` | The background color of the circle | `--paper-grey-100`
`--circle-progress-stroke-color` | The stroke color of the circle | `--accent-color`
`--circle-progress-stroke-linecap` | The stroke-linecap svg attribute of the circle | `round`
`--circle-progress-width` | The width of the circle | `64px`
`--circle-progress-height` | The height of the circle | `64px`

## Installation

`bower i circle-progress -S`

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

## License

MIT: [Shah-Parth/license](https://github.com/Shah-Parth/license)

[webcomponents-image]: https://img.shields.io/badge/webcomponents.org-published-blue.svg
[webcomponents-url]: https://beta.webcomponents.org/element/Shah-Parth/circle-progress
[webcomponents-demo]: https://beta.webcomponents.org/element/Shah-Parth/circle-progress/demo/demo/index.html
