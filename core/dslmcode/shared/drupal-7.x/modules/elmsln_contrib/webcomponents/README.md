## Usage

This should give you the dependencies you need to get going.
1. Enable the Web components module and any dependencies it requires.
2. The default is to serve JS assets up from a CDN. Should you need to change this


# Front end Developers
You may build Web components from source if needed. We default to use CDNs which will effectively point to
this directory or some mutation of it -- https://github.com/elmsln/HAXcms/tree/master/build

If you want to build everything from source, your welcome to use yarn / npm to do so though our
build routine effectively will end in the same net result.  If you want to do custom build routines
such as rollup or webpack and not use our prebuilt copies / split build approaches, then your welcome
to check the box related to not loading front end assets in the settings page in order to tailor
the build to your specific needs.

## Getting dependencies
You need polymer cli (not polymer but the CLI library) in order to interface with web components in your site. Get polymer cli installed prior to usage of this (and (yarn)[https://yarnpkg.com/lang/en/docs/install/#mac-stable] / an npm client of some kind)
```bash
$ yarn global add polymer-cli
```
Perform this on your computer locally, this doesn't have to be installed on your server.

## Usage

- Find `CopyThisStuff` directory in `/sites/all/modules/webcomponents`.
- create a `/sites/all/libraries/webcomponents` directory
- copy the files from `CopyThisStuff` into `/sites/all/libraries/webcomponents`

Then run the following (from the directory you copied it over to) in order to get dependencies:
```bash
$ yarn install
```
Now run `polymer build` and you'll have files in `build/` which contain everything you'll need to get wired up to web components in your site. Modifying build.js or package.json can be used in order to get new elements and have them be implemented.

### Shouldn't I put web components in my theme?
We don't think so. While it may seem counter intuitive, the theme layer should be effectively implementing what the site is saying is available. If you think of standard HTML tags are being part of this (p, div, a, etc) then it makes a bit more sense. You don't want functional HTML components to ONLY be supplied if your theme is there, you want your theme to implement and leverage the components.

## New to web components?
We built our own tooling to take the guess work out of creating, publishing and testing web components. We highly recommend you use this tooling though it's not required:
- https://open-wc.org - great, simple tooling and open community resource
- https://github.com/elmsln/wcfactory - Build your own web component library
- https://github.com/elmsln/lrnwebcomponents - Our invoking of this tooling to see what a filled out repo looks like

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
  "description": "An app for loading phone numbers and making them searchable",
  "start_url": "/",
  "display": "standalone",
  "title": "Phone Book App",
  "app_integration": {
    "menu": {
      "menu_name": "main-menu",
      "weight": 10
    },
    "endpoints": {
      "api/numbers": {
        "callback": "_custom_phonebook_module_numbers",
        "property": "source-path"
      }
      "api/numbers/%": {
        "callback": "_custom_phonebook_module_number"
        "property": "source-path"
      },
      "api/numbers/%/call": {
        "callback": "_custom_phonebook_module_number_call"
        "property": "source-path"
      },
      "api/numbers/%/text": {
        "callback": "_custom_phonebook_module_number_text"
        "property": "source-path"
      }
    }
  }
}
```
- Note that menu will provide the ability for the app to be visible in Drupal's menu system, in this example the main menu. Weight is the order it falls in that menu.
- If you need a data callback to power your app, then the `endpoints` property is for you. `endpoints` has two parameters, callback and property.
  - `callback` is the php function to call in order to return the data needed. If all goes well, this is probably the most "drupal" specific stuff you have to do today.
  - `property` is the property your webcomponent is looking for data from. For example. if you have a one page tag called `<phone-book>` and phone-book gets data by using `source-path="whatever.json"` then property would be `source-path`.
  - Wildcard routes are supported by using the `%` placeholder when defining your routes. You can access the wildcard value via the `arg()` function your defined callback. For instance, if your route is `api/numbers/%/call` then you would access
  the wildcard value in your function like so:
  ```
  function _custom_phonebook_module_number_call($machine_name, $path, $params, $args) {
    $args = arg();
    $number = arg[2]
    ...
  }
  ```
- Now when you clear your caches and have these files pushed up, the following will happen automatically!
1. A permission called `access phone-book app` will be created
2. A menu path called `apps/phone-book` will be created and will load your element if accessed
3. A menu item called "Phone book" will show up in the main menu that links to `apps/phone-book`
4. For each `endpoint` you have defined menu callback paths will be created and will return your data delivered by the function you've specified. So `apps/phone-book/api/numbers` will be created and fed data via `_custom_phonebook_module_numbers`.
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