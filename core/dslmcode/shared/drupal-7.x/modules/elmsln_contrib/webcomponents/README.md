# Webcomponents module

This family of modules is intended to replace our reliance on the Drupal theme system by instead routing as much as possible through webcomponent architecture. We currently support polymer based elements but it would be easy enough to find and implement others

## Background
Webcomponents currently require a polyfill to get broad browser support beyond Chrome (which has fully implemented the specification). Webcomponent is a combination of 4 W3C agreed upon specifications for how to handle Custom Elements appropriately.

## Install
Enable the module and any submodules you want. We recommend webcomponents_polymer and webcomponents_display_modes. Then go to sites/all/libraries and create a webcomponents directory here. Then inside make two more directories:
-sites/all/libraries
  - webcomponents
    - polymer
    - webcomponentsjs

The polymer directory is where we will place all our custom webcomponents we've gotten from webcomponents.org and elsewhere.

the webcomponentsjs directory is where we'll store the polyfills. You can typically get the right one from copying the contents of a polymer / other webcomponent bower dependency from polymer/{yourelement}/bower_components/webcomponentsjs/

Currently for performance and simplicity, only the webcomponents-lite.min.js file is required if you are going to use this (which is recommended for browser support).

## Usage (with Polymer)
Start installing all new polymer elements into sites/all/libraries/webcomponents/polymer. Blow away your theme cache and places that display modes come into play (node / entity field ui's and views) will start to show up as options where you can map associations between drupal values and webcomponent properties.

You'll also start to be able to use them in tpl files to start hollowing them out significantly.

## A note on Performance
This currently is a rough and dirty "get all the elements to load into scope" methodology. Typically when running polymer in a production environment to reduce the number of assets to load you would vulcanize them (which mashes them into 1 file). Currently this module is focused on getting webcomponents to be entity definitions in Drupal. Future flexibility will allow for importing the definitions without nessecarily importing the elements into every page (though this is typically a 1 time download since they are reused on every page and static html so they can be heavily cached).

