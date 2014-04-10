
# Panels Layouts

  Adaptivetheme includes these 14 layouts for use with the Panels module.

  http://drupal.org/project/panels

  All layouts are responsive and are controlled via theme settings in your
  sub-theme. You can select layout options for each device group - this means
  the layout of the panel can change for tablets or smalltouchs to better
  suit the smaller size of those screens.
  
  Note: regular Panels layouts or those supplied by another theme or module, 
  such as Panels Extra Layouts, will not be responsive with this theme, only
  the Panels layouts supplied with Adaptivetheme are responsive.
  
  # Gpanels
  
  These same 14 layouts are avaialbe as Gpanels (layout snippets) for use in
  your page.tpl.php files. Use Gpanels if you prefer to hold your layout in code
  inside templates rather than using the Panels module. The priciple difference,
  apart from using Panels, Ctools and Page Manager, is that Gpanels do not have
  context avaialbe to them - only what block visibility can provide, unless you
  use the Context module, or Mini Panels.

  # CSS

  Each of the layouts includes an admin CSS file, however the CSS for the front
  end view of the panel comes from Adaptivetheme core and is generated when
  you save the theme settings. This is the main trick in making responsive
  panels work inside this theme - by omitting front end CSS from the actual
  layout plugin and instead wrangling all CSS inside the theme.

  # Markup

  The markup is different from normal Panels layouts. Instead of using the regular
  panels type markup and classes I opted to mimic regular regions. This was done
  to make them identical to Gpanels, so we only need one set of CSS files to
  control both Panels and Gpanel layouts.

  # Usage

  The layouts will appear inside Panels when you select the layout for the Panel
  you are creating, simply choose one of the AT Responsive Panel options.

  You will notice the icons are orange and blue compared to Panels module plain
  grey icons. The orange regions are optional (collapsible) but the blue ones are
  not - they will not collapse if not used.

  Most of the layouts are "stacked" meaning they have top and bottom regions - all
  top and bottom regions are collapsible.

  # Developer Info
  
  Please see the five_5x20 plugin inc file for exstensive docs on the plugin structure
  and various other details you will need to make your own plugin.
 
 
