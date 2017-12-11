# pdf-element

[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg)](https://www.webcomponents.org/element/streetturtle/pdf-element)

Web component built with Polymer which allows to view PDF documents.  
Note that this element doesn't use browser's built-in PDF rendered, but rednders PDF using Mozilla's [pdf.js](https://mozilla.github.io/pdf.js/) library, which let's you have more control on how the document is displayed and which actions are available to user. 

Demo: http://pavelmakhov.com/pdf-element/

## Features

- Next/Previous page
- Zoom
- Download (optional)
- Compatible with Polymer 1.0
- Dynamically change document without page reloading
- Looks polymer way :)
- Text selection (optional)
- Works in IE (in progress)

![pdf-element](./screenshot.png)

## Installation

With Bower:

```
bower install -S pdf-element
```

Or just clone this repo and use `pdf-element.html` in your project 

## Contributing

I would really appreciate any help. PR/issues and stars are welcome =)

To run it locally make sure you have [Polymer CLI](https://www.npmjs.com/package/polymer-cli) installed and do the following:

```
git clone https://github.com/streetturtle/pdf-element.git
cd pdf-element
bower install
polymer serve
```

Element's page will be available at [http://localhost:8080/components/pdf-element/](http://localhost:8080/components/pdf-element/)

## Licence

**The MIT License (MIT)** © 2016-2017 Pavel Makhov
