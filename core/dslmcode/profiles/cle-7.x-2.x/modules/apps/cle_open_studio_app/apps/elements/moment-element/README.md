[![Build status][travis-image]][travis-url]
[![Published on webcomponents.org][webcomponents-image]][webcomponents-url]

## \<moment-element\>

Polymer element wrapper for the [moment](https://github.com/moment/moment) library.

Example:
<!---
```
<custom-element-demo>
  <template>
    <script src="../webcomponentsjs/webcomponents-lite.js"></script>
    <link rel="import" href="moment-element.html">
    <next-code-block></next-code-block>
    <style is="custom-style">
      moment-element {
        display: block;
      }
    </style>
  </template>
</custom-element-demo>
```
-->
```html
<moment-element></moment-element>
<moment-element datetime="1991-12-31" output-format="MMM DD[,] YYYY"></moment-element>
```

[travis-image]: https://travis-ci.org/abdonrd/moment-element.svg?branch=master
[travis-url]: https://travis-ci.org/abdonrd/moment-element
[webcomponents-image]: https://img.shields.io/badge/webcomponents.org-published-blue.svg
[webcomponents-url]: https://beta.webcomponents.org/element/abdonrd/moment-element
