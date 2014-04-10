

First read this about SASS, its very important!
-----------------------------------------------

There is more information regarding working with SASS in the SASS CSS folder
_README, however, you need to be aware that if you set Compass to watch the
SASS folder or any SCSS file in this theme it will OVERWRITE the CSS file/s in
your sub-themes CSS directory!

To prevent this ever happening you can delete the config.rb file in the
sub-theme root (unless you are actually planning on using SASS, in which case
you will want to keep it).




Working with Responsive Design in Adaptivetheme
-----------------------------------------------

The subtheme is designed to be "mobile first". In short this means to
first load a set of global styles, the progressively add styles for larger
devices using media queries.

Its important to note that you do not have to follow a mobile first approach.
Adaptivetheme can support Desktop first approach as well, which means you will
progressively add styles to override things for mobile, rather than progressively
adding style for larger devices.

You can do both in Adaptivetheme - it's merely a matter of where you place
the majority of your styles, and what theme settings you choose in the
Appearance settings for your sub-theme.

Lets examine the CSS file structure of Adaptivetheme and look at how each
file is loaded. From this you will be able to deduce what approach might work
for you, and where you should be placing your CSS.




Moible First or Desktop First - that is the Question!
-----------------------------------------------

Depending on your approach AT will load the stylesheets in a different order,
indeed it will load different stylesheets.  You MUST make a conscious decision
which to use and set this in theme settings.

Look under CSS settings. By default AT is set to Mobile first, if you want to do
Desktop first you should change this setting.




Global Styles
-------------

The global styles do not target any specific device - they always load for all
devices.

There are two main global stylesheets:

  - global.base.css
  - global.styles.css
  
global.base.css - this holds a few imoportant declarations that should probably
not be removed, however you can modify them, such as gutter width and flexibile
image/media styles.

global.styles.css - includes a slighly modified normalize reset and many empty
selectors for elements and drupal classes and id's. If you prefer you can delete
everything in global.styles.css and start with a clean slate.

The selectors are extensive and you should delete unused selectors before
going live to reduce CSS weight. You can use cleancss.com or a better way is
just use SASS, it does this for you.

Each file includes a lot of comments and documentation, please review each of
the global CSS files for more help.

If you are doing mobile first then you will probably keep things to a minimum
in these files. "Minimum" is relative, this might still be a lot of CSS,
never-the-less its worth keeping in mind the mobile view of the site, and
avoid writing CSS rules that are clearly for larger width devices.




Responsive Styles
-----------------

Adaptivetheme 7.x-3.x has two "modes" - Development mode and Production mode.
Depending on what mode you are in the stylesheets will load differently.

Mode changes automatically depending on CSS aggregation settings. When CSS
aggregation is ON, the its in Production mode.

If you don't know what CSS aggregation is, look here:

  ~/admin/config/development/performance


## Responsive Styles - Development mode

In Development mode (CSS aggregation OFF) the responsive stylesheets will load
in individual link elements with the media query in media attribute.

This allows them to load directly into the browser and you will see your CSS
changes immediately, as per normal CSS development.

There are five of these responsive stylesheets - one for each break point set
in the theme settings:

  - responsive.smalltouch.landscape.css
  - responsive.smalltouch.portrait.css
  - responsive.tablet.landscape.css
  - responsive.tablet.portrait.css
  - responsive.desktop.css

Its important to know that these files DO NOT contain the media queries,
instead they load in the <link> elements media attribute - remember, these
files only load when in Development Mode.


## Responsive Styles - Production mode

When in production mode all the responsive stylesheets are aggregated into one
file and use embedded @media queries. AT Core will automatically aggregate
the CSS from each of the development mode stylesheets and wrap it in the right
media query. This reduces the number of HTTP requests from 5 to 1.

This file is always called:

  - ThemeName.responsive.styles.css

You will find this file at:

  ~/[public files]/adaptivetheme/[ThemeName]/ThemeName.responsive.styles.css

NOTE: please see the section below titled "Relative Paths in Responsive Styles".


## Important Note about CSS Aggregation and Responsive Stylesheets

Once you have CSS aggregation ON if you make changes to any responsive
stylesheet, you MUST re-save the theme settings AND clear the sites cache. AT
Core will re-write the saved files, then clearing the cache tells Drupal to
use the new file.


## Relative Paths in Responsive Stylesheets

When CSS aggregation is ON AT Core will load the production version of your
responsive styles (see above "Production mode"). this file is loading from
Public Files and not from within your theme so special handling is required for
relative assets - AT Core will do this for you.

AT Core will automatically re-write the relative paths to the files so they
are relative to the site root. This is the same functionality as Drupal core
CSS aggregation feature, so paths are not broken.

If you use absolute paths these will not be altered.




Overlapping/Custom Media queries
--------------------------------

By default the media queries in Adaptivetheme are "stacked", meaning they do
not overlap. This makes it very easy to target one set of device width and not
have those styles "leak" over into others. However it can also mean you may
need to duplicate CSS that you would rather have cascade.

To use custom media queries the sub-theme includes a special file called:

  responsive.custom.css

To enable the use of this file in your theme see your theme settings:

  Layout & General Settings > CSS > Custom Media Queries

This file has embedded media queries which means you MUST set them yourself.
Defaults are provided.

Allowing styles to cascade can result in a huge saving on total CSS weight and
speed up development.




Internet Explorer Styles and Scripts
------------------------------------

AT can load conditional stylsheets and scripts from you sub-themes info file.

Please see adaptivetheme_subtheme.info - there are good docs and examples of
how to declare stylesheets and scripts for Internet Explorer.

Adaptivetheme also includes special conditional classes on the HTML element
which allow you to easily target styles at specific version of IE.

These are the classes you can use:

  .iem7 (IE7 Mobile)
  .lt-ie7 (less than IE7)
  .lt-ie8 (less than IE8)
  .lt-ie9 (less than IE9)

Use these if you only have a small number of overrides and do not want to load
a dedicated conditional stylesheet.




Support
-------

Ping me on Skype if you have life/death critical issues to report...

  Skype: jmburnz

Otherwise support my work by joining my theme club, it really does fund my
contrib projects:

  http://adaptivethemes.com

Or, you could get radical and file a support issue, even post a patch (which
makes me very happy):

  http://drupal.org/project/issues/adaptivetheme


