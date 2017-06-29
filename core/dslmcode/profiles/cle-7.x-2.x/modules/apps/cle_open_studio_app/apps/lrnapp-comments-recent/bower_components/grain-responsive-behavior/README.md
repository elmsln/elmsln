[![Polymer Version](https://img.shields.io/badge/polymer-v2-blue.svg)](https://www.polymer-project.org)

# \<grain-responsive-behavior\>

Every element implementing this behavior do get an attribute for is-mobile, is-tablet, is-desktop when you resize the window.
You can use this information to change styles and/or attributes depending on it.

## Installation

```sh
$ bower install --save daKmoR/grain-responsive-behavior
```

## Getting Started

Import the package.

```html
<link rel="import" href="/bower_components/grain-responsive-behavior/grain-responsive-behavior.html">
```

Create your element using this behavior. You can now access is-mobile, is-tablet, is-desktop.

```js
class GrainResponsiveBehaviorExample extends GrainResponsiveBehavior(Polymer.Element) {
  // your code
}
```


If you wish to have an responsive attribute you should create 3 attributes foo, mobileFoo, tabletFoo and init the Behavior with `this.initResponsiveBehaviorFor('foo');

```js
class GrainResponsiveBehaviorExample extends GrainResponsiveBehavior(Polymer.Element) {
  static get is() { return 'grain-responsive-behavior-example' }

  static get properties() {
    return {
      marked: {
        type: String,
        reflectToAttribute: true,
        value: 'false', // 'true', 'false'
      },
      mobileMarked: { type: String, reflectToAttribute: true },
      tabletMarked: { type: String, reflectToAttribute: true },
    };
  }

  constructor() {
    super();
    this.initResponsiveBehaviorFor('marked');
  }
}
```

*For more information, see the API documentation.*

## Working on the Element

First, make sure you have the [Polymer CLI](https://www.npmjs.com/package/polymer-cli) installed.
* View the Element via `polymer serve`
* Run tests via `polymer test`