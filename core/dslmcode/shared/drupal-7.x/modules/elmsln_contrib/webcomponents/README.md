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
- copy `build.html` to `sites/all/libraries/webcomponents/polymer/our-build`
- Wipe your theme cache in your drupal site
- You are good to go in your quest for TPL-less development!

## Single Page app development (webcomponents_app sub-module)
You can turbo charge you single page app development workflows with Drupal and the webcomponents_app sub-module! The workflow involving this is that you can do all of your development via a one-page polymer app and then integration into Drupal comes in the form of writing a single data callback function (for simple apps, obviously). So, here's the workflow for an example app called `phone-book`:
- Make a polymer one page app and save it to one of the following:
  - sites/all/libraries/polymer/apps/`phone-book`
  - sites/all/modules/`custom_phonebook_module`/apps/`phone-book` (or any other valid module location in the apps directory)
- Go into your one page app directory, and edit the manifest.json file.
  - Add a property called 'title' and name it what you want it to be called in Drupal
  - (optional but probably what you want) edit your `manifest.json` file so it looks more like this:
```
{
  "name": "phone-book",
  "short_name": "phone-book",
  "title": "Phone book",
  "description": "An app for loading phone numbers and making them searchable",
  "start_url": "/",
  "display": "standalone",
  "drupal": {
    "menu": {
      "menu_name": "main-menu",
      "weight": 10
    },
    "data": {
      "callback": "_custom_phonebook_module_data",
      "property": "source-path"
    }
  }
}
```
- Note that menu will provide the ability for the app to be visible in Drupal's menu system, in this example the main menu. Weight is the order it falls in that menu.
- If you need a data callback to power your app, then the `data` property is for you. `data` has two parameters, callback and property.
  - `callback` is the php function to call in order to return the data needed. If all goes well, this is probably the most "drupal" specific stuff you have to do today.
  - property is the property your webcomponent is looking for data from. For example. if you have a one page tag called `<phone-book>` and phone-book gets data by using `source-path="whatever.json"` then property would be `source-path`.
- Now when you clear your caches and have these files pushed up, the following will happen automatically!
1. A permission called `access phone-book app` will be created
2. A menu path called `apps/phone-book` will be created and will load your element if accessed
3. A menu item called "Phone book" will show up in the main menu that links to `apps/phone-book`
4. A menu callback path called `apps/phone-book/data` will be created and will return your data delivered by the function `_custom_phonebook_module_data`
5. You will be incredibly happy with how little Drupal specific work your front-end designer just had to do!

### A note on data returned by that PHP function
Returned data should look like the following since it gets ripped into json:
```
$phone_book = array(
    array('Joe', 'Cool', '555-867-5309'),
    array('Jill', 'Cool', '554-867-5309'),
);
return array(
  'status' => 200,
  'data' => $phone_book
);
```

## A note on Performance
You can add elements directly though it is highly recommended to follow the above workflow because of how many gains in performance there are by removing needless files from version control as well as combining potentially dozens or 100+ html files (1 per element typically) into a single file. This will drastically speed up initial download of your site by doing this. The webcomponent module can discover in multiple nested files if you want to use the raw items as part of your setup.

