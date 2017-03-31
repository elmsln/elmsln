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

## Usage / Workflow (with Polymer)
These are your dependencies to get this development workflow going. Install node & npm then run the following:
```
sudo npm install -g bower
sudo npm install -g vulcanize
sudo npm install -g polymer-cli@next

```
@next flag on polymer-cli gets you 2.0 cli (at time of this writing). It allows you to do 1.0 and 2.0 development so don't worry if you are concerned about the version.

Next steps:
- Find some webcomponents you like (in this example we'll use LRNWebcomponents/lrn-icons)
- make a working directory for this drupal project outside drupal:
- `cd ~/git/myproject` then `polymer init`
follow the prompts to get a baseline item created.
- Now do `bower install --save LRNWebcomponents/lrn-icons` (and other you want)
- edit `index.html` and add the component into the requirements
- `<link rel="import" href="../lrn-icons/lrn-icons.html">` (and others you want)
- remove the reference to `webomponents-lite.min.js` and save the file
- now perform a `polymer build`
- `cd build/default` then do `vulcanize index.html > build.html` (build can be whatever you want)
- copy `build.html` to `sites/all/libraries/webcomponents/polymer/`
- Wipe your theme cache in your drupal site
- You are good to go in your quest for TPL-less development!

## A note on Performance
You can add elements directly though it is highly recommended to follow the above workflow because of how many gains in performance there are by removing needless files from version control as well as combining potentially dozens or 100+ html files (1 per element typically) into a single file. This will drastically speed up initial download of your site by doing this. The webcomponent module can discover in multiple nested files if you want to use the raw items as part of your setup.

