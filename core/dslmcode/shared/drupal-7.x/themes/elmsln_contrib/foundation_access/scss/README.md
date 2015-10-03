# ELMSLN UI Styleguide

![ELMSLN](https://raw.githubusercontent.com/michael-collins/elmsln-logos/master/png-lowres-solid/lowres_square-color.png "ELMS Learning Network")

## About

This is a living styleguide for the ELMSLN Drupal theme. Here is an [example styleguide](http://yago.github.io/Cortana-example/index.html) for reference.

This is a living styleguide that exists to:

* maintain best practices of responsive web design by building UI componenets modularly
* reduce the barier of entry for designers and themers to participate and contribute
* establish a defined language and naming convention for UI elements
* provide a baseline for user experience, accessiblity, and visual regression testing
* increase the velocity of adding functionality by allowing developers to easily reuse UI components

## Usage

When creating a new component in Sass, you can define the component by adding a docblock to the bottom of your `.scss` file.
	
	/*doc
	---
	title: Component Name
	name: componentname
	category: Components - Component Name
	---

	A breif explanation on how to use this componenet and in what context would be most appropriate to use.

	```html_example
	<div class="componentname">Lorem ipsum Pariatur in ullamco pariatur proident in culpa consequat mollit pariatur occaecat in ea consectetur ad.</p>
	</div>
	```

	*/

## Installation

To contribute to this styleguide you will need to install the front-end stack that supports generating the css and js from the theme as well
as the styleguide itself.

From inside of the [ELMSLN foundation_access theme](https://github.com/elmsln/elmsln/tree/master/core/dslmcode/shared/drupal-7.x/themes/elmsln_contrib/foundation_access), 
install Grunt, Hologram, and Bower globally

```
$ npm install -g grunt-cli grunt-hologram bower
$ gem install bundler
```

Install the dependencies

```
$ npm install
$ bower install
$ bundle install
```

Run the Grunt Server

```
$ grunt styleguide
```

By running `grunt styleguide` the browsersync plugin should open the styleguide automatically.  If it does not then visit this url [http://localhost:3000/styleguide/index.html](http://localhost:3000/styleguide/index.html)