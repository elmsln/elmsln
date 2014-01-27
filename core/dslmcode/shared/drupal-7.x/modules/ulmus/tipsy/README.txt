  -----------------------------------------------------------------------------------------
                                    ABOUT THE MODULE
  -----------------------------------------------------------------------------------------
  Plugin homepage: http://onehackoranother.com/projects/jquery/Tipsy/

  Tipsy module provides a Facebook-like balloon tooltip for any element you like on the
  page, it integrates Tipsy jquery plugin (https://github.com/jaz303/Tipsy) by Jason Frame.
  The module is an integration contributed to Drupal by wikikiwis team (http://wikikiwis.com).

  Currently, this module allows tooltips to appear with a textarea, a textfield, or any
  other HTML attribute specified in Tipsy settings page.

  It supplies hover, or focus states, and comes with a bunch of options that is specified
  in the settings page, without the need to dive into jQuery at all.

  -----------------------------------------------------------------------------------------
                                    HOW TO USE TIPSY
  -----------------------------------------------------------------------------------------
  First the modules must be enabled admin/build/modules page.

  Then go to admin/settings/Tipsy to specify and customize Tipsy settings, you will notice that
  you have the option to enable Tipsy on all Drupal forms descriptions inside your site.
  You also have have to specify the position where Tipsy must appear, the delay of the appear and
  disappear in milliseconds, how Tipsy is triggered (hover/focus), the opacity of the tooltip,
  and the offset (number of pixels between the tooltip and the element).

  CUSTOM SELECTORS
  --------------------------------
  In this section you can specify any CSS selectors to apply Tipsy to it.
  The example below applies Tipsy tooltips anchor title on primary navigation inside Drupal site

  1) Our CSS selector will be => "li.leaf a" (without quotes) which means any anchor inside the li
     that has the class leaf.

  2) Specify the options that best suits your selector.

  3) Tooltip content will be the "title" (without quotes) of the anchor that will appear inside
     the Tipsy tooltip (See below for other usage: TOOLTIP CONTENT)

  4) Save your settings.

  Note that you can add as many selectors as needed, to DELETE a selector you only have to
  REMOVE/EMPTY its selector textfield and SAVE.

  TOOLTIP CONTENT
  --------------------------------
  You can chose to pull the tooltip content from two different sources:

  1) HTML Attribute on the matched element, for example:
  <a class="my_selector" title="This is the tooltip">Example</a>
  This is the default (Source: 'HTML attribute', Selector: 'title')

  2) Child element of the matched element:
  <div class="my_selector">
    <div class="contents">Tooltip HTML that can't really fit into an attribute</div>
    Ordinary text that the user sees
  </div>
  The tooltip is pulled with the settings Source: 'Child element', Selector: '.contents'
