# Installation
This is intended to be run prior to being pushed to a server via sftp or git or whatever your workflow is. If you don't currently have bower you can get it via `npm install -g bower`

## no Webcomponents installed yet
Create a directory for webcomponents to live in for the system. This is recommended as:

`mkdir -p sites/all/libraries/webcomponents/polymer`

Copy the `bower.json` included in the hax module over to this directory:

`cp sites/all/modules/hax/bower.json sites/all/libraries/webcomponents/polymer/bower.json`

Run bower install to get dependencies in place:
`cd sites/all/libraries/webcomponents/polymer`
`bower install`

Skip the next heading

## What if I already had webcomponents?
Go to polymer directory :
`cd sites/all/libraries/webcomponents/polymer`

Run the following:
`bower install --save LRNWebComponents/cms-hax`

Answer any questions bearing in mind that hax currently is written against webcomponentsjs 0.7.x and polymer 1.11.x as of this writing. You will have the dependencies needed.

## Usage
This should give you the dependencies you need to get going. Enable the module and go to the permissions page to ensure uses have the 'use hax' permission checked. Once this is checked then people will start to see a 'HAX Authoring' local menu item / tab / contextual option show up when they have access to edit a node.

## Settings

The settings page has ways of hooking up youtube, vimeo and more via the "App store" concept built into HAX. You can also make small tweaks to your needs on this page.

## End user

Go to the node's hax tab, then hit the pencil in the top right. When your done editing hit the power button again and it should confirm that it has saved back to the server. Congratulations on destoying the modules you need to build an awesome site!

### Developer functions
By default, the auto-loaded elements will append to the page on node view mode full. To override this, set hax_autoload_element_node_view to false in settings.php

## Side note on Build routines
If you are looking to use a build routine, that's great! You'll just want to make sure that you have all the elements in place needed to make HAX run. HAX paths and interface won't show up unless users have permissions so while not recommended to include HAX in your build routine, it won't hurt anything either (other then download size).

## but but but, you don't run it this way do you!?
You are correct. We have a much more advanced methodology of getting webcomponents into the right place. We're also leveraging the same bundle of components across multiple distributions of Drupal 7 + static sites + GravCMS. So while what the ELMS:LN team (who produced this) uses will look a liiiiittttle bit different if you dig into our file system, ultimately we are just tricking drupal into loading all the files the way we just described above.

Our build routine ultimately is just smashing together the top 50 or so commonly used elements in our universe and then tricking webcomponents into thinking all these elements live in the polymer.html file. By doing this we can cheat on page delivery as we can send you 1 heavily cached asset after 1st page load which actually resolves to 50+ elements. When it comes to HAX, we still keep that separate as that's only supposed to be loaded for users that actually have need of it.