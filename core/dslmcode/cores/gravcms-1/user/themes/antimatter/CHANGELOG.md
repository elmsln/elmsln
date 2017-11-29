# v2.1.2
## 9/28/2017

1. [](#improved)
    * Added polish and brazilian portuguese translations
    * Allow overriding the slidebar by moving it to its own `sidebar_navigation` block [#110](https://github.com/getgrav/grav-theme-antimatter/pull/110)
1. [](#bugfix)
    * Fix showcase template overlapping when not at top [#99](https://github.com/getgrav/grav-theme-antimatter/pull/99)

# v2.1.1
## 02/26/2017

1. [](#bugfix)
    * Allow to add a `external` class to site.yaml links to work on modular pages [#95](https://github.com/getgrav/grav-theme-antimatter/pull/95)

# v2.1.0
## 01/24/2017

1. [](#new)
    * Updated to FontAwesome 4.7.0 with [Grav icon](http://fontawesome.io/icon/grav/)
1. [](#improved)
    * Added croatian
    * Changed "SimpleSearch" string in the sidebar to "Search"
1. [](#bugfix)
    * Removed unreachable condition [#85](https://github.com/getgrav/grav-theme-antimatter/pull/85)
    * Fixed a typo in the french translation

# v2.0.0
## 07/14/2016

1. [](#new)
    * Added microformats2 support [#64](https://github.com/getgrav/grav-theme-antimatter/pull/64)
1. [](#improved)
    * Updated to FontAwesome 4.6.3
    * Added romanian, russian and ukranian

# v2.0.0-beta.1
## 05/23/2016

1. [](#new)
    * New and improved **dropdown** styling
1. [](#improved)
    * Removed templates from `form` + `snipcart` plugins
    * Added support for search button
    * Updated some translations
    * Automatically add comments if configured
    * Relative path for favicon
    * Slightly modified the blockquote background color
    * Removed unneeded streams from YAML
    * Use common language strings in Blueprint

# v1.8.0
## 11/20/2015

1. [](#new)
    * Added logic to include site.menu items in modular pages
    * Added a configurable lang field for HTML tag
    * Added a `bottom` JS output call
1. [](#improved)
    * Updated to FontAwesome 4.4.0
1. [](#bugfix)
    * Fixed extra `/` in some tag URLs
    * Better support for PECL Yaml parser
    * Fixes for blog page blueprint

# v1.7.6
## 10/07/2015

1. [](#new)
    * Added logic to include site.menu items in modular pages
1. [](#improved)
    * Removed unused `<p>` tags

# v1.7.5
## 09/16/2015

1. [](#improved)
    * Use new form plugin templates

# v1.7.3
## 09/11/2015

1. [](#new)
    * Added SCSS configurable notes colors
1. [](#improved)
    * Various typos

# v1.7.3
## 08/31/2015

1. [](#new)
    * Added header image control and blueprints to admin plugin
1. [](#improved)
    * Use new template field for modular pages

# v1.7.2
## 08/24/2015

1. [](#new)
    * Added support for `login-status` partial in menu

# v1.7.1
## 08/11/2015

1. [](#improved)
    * Use new toggle for item blueprint

# v1.7.0
## 08/06/2015

1. [](#new)
    * Blueprints that work with new admin plugin!
1. [](#bugfix)
    * Favicon with full image URL

# v1.6.1
## 07/24/2015

1. [](#bugfix)
    * Fixed sidebar links when site at root

# v1.6.0
## 07/21/2015

1. [](#new)
    * Added support for `langswitcher` plugin
1. [](#improved)
    * Made sidebar links more robust

# v1.5.0
## 07/14/2015

1. [](#new)
    * Added canonical URL support
1. [](#improved)
    * More improvements for blueprints
1. [](#bugfix)
    * Fixes for multi-language support

# v1.4.0
## 05/09/2015

1. [](#improved)
    * Improved blueprints
1. [](#bugfix)
    * Fix for when page.summary is equal to page.content

# v1.3.9
## 04/13/2015

1. [](#bugfix)
    * Fix for image class in modular template 'text.html.twig`

# v1.3.8
## 04/07/2015

1. [](#improved)
    * Genericized theme_config variable for better inheritance

# v1.3.7
## 03/28/2015

1. [](#bugfix)
    * Rolled back changes that resulted in broken header

# v1.3.6
## 03/24/2015

1. [](#bugfix)
    * Fix for compressed text in `.pure-g` divs

# v1.3.5
## 03/24/2015

1. [](#improved)
    * Keep html,body on height:100%; use body for scroll event
    * Use Footer colors from vars rather than hard-coded
1. [](#bugfix)
    * Load pure grids at all times for better non-flexbox support

# v1.3.4
## 03/01/2015

1. [](#improved)
    * Use new Grav builtin 'jQuery' support

# v1.3.3
## 02/19/2015

1. [](#improved)
    * Implemented new `param_sep` variable from Grav 0.9.18
1. [](#bugfix)
    * Fix for table column widths
    * Force snipcart slider to look in all pages

# v1.3.2
## 02/05/2015

1. [](#improved)
    * Minor typo in assets

# v1.3.1
## 01/23/2015

1. [](#bugfix)
    * Added page title encoding
    * Stop modular pages showing up in dropdown menus
    * Fixed typo in streams setup

# v1.3.0
## 01/09/2015

1. [](#improved)
    * NOTE: BREAKING CHANGE - Fixed references to plugins in `partials/` folder
    * Updated README.md

# v1.2.7
## 12/29/2014

1. [](#bugfix)
    * Removed `Fixed` header image to resolve issues with mobile browsers

# v1.2.6
## 12/21/2014

1. [](#new)
    * Added support for list of custom menu items in `site.yaml`
    * Updated `README.md` with some instructions on how to use some Antimatter features
1. [](#improved)
    * Removed `cache.html.twig` file that was used only for testing
    * Removed unused `color` option in `antimatter.yaml`

# v1.2.5
## 12/15/2014

1. [](#bugfix)
    * Fix for Firefox 34 Flex/Responsiveness issues

# v1.2.4
## 12/12/2014

1. [](#new)
    * Added demo link to blueprints
1. [](#improved)
    * Inverted Previous/Next buttons on blog item template

# v1.2.3
## 12/05/2014

1. [](#improved)
    * Simplified Previous/Next buttons to use Page methods

# v1.2.2
## 12/04/2014

1. [](#new)
    * Added Previous/Next buttons with Collection methods
    * Added Related posts in blog sidebar
1. [](#bugfix)
    * Fix for DaringFireball style link

# v1.2.1
## 11/30/2014

1. [](#improved)
    * Renamed core theme JS file
    * Removed featherlight from Antimatter
1. [](#bugfix)
    * Fixed response code in error template

# v1.2.0
## 11/28/2014

1. [](#new)
    * Added SimpleSearch display in blog sidebar
    * Added reference to `custom.css` file in core
1. [](#improved)
    * Added plugins checks for improved flexibility if plugins are not installed


# v1.1.11
## 11/21/2014

1. [](#new)
    * ChangeLog started...
