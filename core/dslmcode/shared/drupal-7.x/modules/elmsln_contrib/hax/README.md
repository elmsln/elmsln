## Usage

This should give you the dependencies you need to get going.
1. Enable the HAX module and any dependencies it requires.
2. Go to the permissions page to ensure users have the 'use hax' permission
   checked. Once this is checked then people will start to see a 'HAX Authoring'
   local menu item / tab / contextual option show up when they have access to
   edit a node. If you want users to be able to upload files, grant the
   'Upload files via HAX editor' permission.
3. The default is to serve JS assets up from a CDN as per the webcomponents module.
   Should you need to change this keep reading into building your own assets.

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

# Front end Developers
You may build HAX from source if needed. HAX defaults to use CDNs which will effectively point to
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

- Find https://github.com/elmsln/unbundled-webcomponents and run the tooling to create your build (`yarn install` then `yarn run build`)
- create a `/sites/all/libraries/webcomponents` directory
- copy the files from https://github.com/elmsln/unbundled-webcomponents into `/sites/all/libraries/webcomponents`

### Shouldn't I put web components in my theme?
We don't think so. While it may seem counter intuitive, the theme layer should be effectively implementing what the site is saying is available. If you think of standard HTML tags are being part of this (p, div, a, etc) then it makes a bit more sense. You don't want functional HTML components to ONLY be supplied if your theme is there, you want your theme to implement and leverage the components.

## New to web components?
We built our own tooling to take the guess work out of creating, publishing and testing web components for HAX and other projects. We highly recommend you use this tooling though it's not required:
- https://open-wc.org - great, simple tooling and open community resource
- https://github.com/elmsln/wcfactory - Build your own web component library
- https://github.com/elmsln/lrnwebcomponents - Our invoking of this tooling to see what a filled out repo looks like