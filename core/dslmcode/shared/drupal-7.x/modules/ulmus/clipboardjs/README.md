INTRODUCTION
------------
Integrates the Clipboard.js library with Drupal.

REQUIREMENTS
------------
 * Libraries module - https://drupal.org/project/libraries
 * jQuery Update (jQuery >= 1.7) - https://drupal.org/project/jquery_update

INSTALLATION
------------
** Use the drush command `drush cbdl` to automatically download the library.

1. Install dependencies and Clipboard.js module as per:
   https://drupal.org/documentation/install/modules-themes/modules-7

2. Visit the media recorder configuration page to set file path,
   etc, at admin/config/media/mediarecorder.

USAGE
-----
The Clipboard.js can be added to any text field by visiting the manage display
page for the entity and and choosing Clipboard.js as the field formatter.

Custom text fields can also use clipboard.js using the form api or in a render
array. There is a helper function to build the form element, for example:

    function example_form($form, $form_state) {
      $form = array();
    
      // Load clipboard.js library.
      libraries_load('clipboard');
    
      // Clipboard settings.
      $text = t('This is the text to be copied...');
      $alert_style = 'tooltip';
      $alert_text = 'Copy was successful!';
      $button_label = 'Click to Copy';
      
      // Build the form or render element using the helper function:
      $form = clipboardjs_build_content($text, $alert_style, $alert_text, $button_label);
    
      return $form;
    }


CREDITS
-------
* Norman Kerr - [kenianbei](https://drupal.org/user/778980)
