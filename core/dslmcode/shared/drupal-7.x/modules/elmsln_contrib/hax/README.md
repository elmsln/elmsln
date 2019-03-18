## Getting dependencies
You need polymer cli (not polymer but the CLI library) in order to interface with web components in grav. Get polymer cli installed prior to usage of this (and (yarn)[https://yarnpkg.com/lang/en/docs/install/#mac-stable] / an npm client of some kind)
```bash
$ yarn global add polymer-cli
# or...
$ npm install -g polymer-cli
```
Perform this on your computer locally, this doesn't have to be installed on your server.

## Usage

Find the `CopyThisStuff` directory in `/sites/all/modues/webcomponents` and copy the files in there over to `/sites/all/libraries/webcomponents`.

Then run the following (from the directory you copied it over to) in order to get dependencies:
```bash
$ yarn install
# or...
$ npm install
```
Now run `polymer build` and you'll have files in `build/` which contain everything you'll need to get wired up to web components in your grav site. Modifying build.js or package.json can be used in order to get new elements and have them be implemented.

### Shouldn't I put web components in my theme?
We don't think so. While it may seem counter intuitive, the theme layer should be effectively implementing what Grav is saying is available. If you think of standard HTML tags are being part of this (p, div, a, etc) then it makes a bit more sense. You don't want functional HTML components to ONLY be supplied if your theme is there, you want your theme to implement and leverage the components.

## New to web components?
We built our own tooling to take the guess work out of creating, publishing and testing web components for HAX and other projects. We highly recommend you use this tooling though it's not required:
- https://github.com/elmsln/wcfactory - Build your own web component library
- https://github.com/elmsln/lrnwebcomponents - Our invoking of this tooling to see what a filled out repo looks like



## Usage

This should give you the dependencies you need to get going.
1. Enable the HAX module and any dependencies it requires.
2. Go to the permissions page to ensure users have the 'use hax' permission
   checked. Once this is checked then people will start to see a 'HAX Authoring'
   local menu item / tab / contextual option show up when they have access to
   edit a node. If you want users to be able to upload files, grant the
   'Upload files via HAX editor' permission.

NOTE on Text Formats: HAX is designed to work with nodes with bodies in the
default Full HTML format where "Limit allowed HTML tags and correct faulty HTML"
is unchecked, or with formats with similarly permissive settings. For this
reason, it is advisable to only allow trusted users to access HAX.

## Settings

The settings page has ways of hooking up youtube, vimeo and more via the "App
store" concept built into HAX. You can also make small tweaks to your needs on
this page.

## End user

Go to the node's hax tab, then hit the pencil in the top right. When your done
editing hit the power button again and it should confirm that it has saved back
to the server. Congratulations on destoying the modules you need to build an
awesome site!

### Developer functions
By default, the auto-loaded elements will append to the page on node view mode
full. To override this, set hax_autoload_element_node_view to false in
settings.php

## Side note on Build routines
If you are looking to use a build routine, that's great! You'll just want to
make sure that you have all the elements in place needed to make HAX run. HAX
paths and interface won't show up unless users have permissions so while not
recommended to include HAX in your build routine, it won't hurt anything either
(other then download size).

## but but but, you don't run it this way do you!?
You are correct. We have a much more advanced methodology of getting
webcomponents into the right place. We're also leveraging the same bundle of
components across multiple distributions of Drupal 7 + static sites + GravCMS.
So while what the ELMS:LN team (who produced this) uses will look a liiiiittttle
bit different if you dig into our file system, ultimately we are just tricking
drupal into loading all the files the way we just described above.

Our build routine ultimately is just smashing together the top 50 or so commonly
used elements in our universe and then tricking webcomponents into thinking all
these elements live in the polymer.html file. By doing this we can cheat on page
delivery as we can send you 1 heavily cached asset after 1st page load which
actually resolves to 50+ elements. When it comes to HAX, we still keep that
separate as that's only supposed to be loaded for users that actually have need
of it.