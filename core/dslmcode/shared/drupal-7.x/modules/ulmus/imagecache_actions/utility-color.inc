<?php
/**
 * @file Utility functions for color widgets.
 */

/**
 * Prepares a subform for displaying RGB fields.
 *
 * Helper function to render a common element.
 *
 * Note that any module that re-uses this form also has to declare the theme
 * function in order to ensure it's in the registry.
 *
 * @param array $action
 *
 * @return array
 */
function imagecache_rgb_form($action) {
  if ($action['HEX'] && $deduced = imagecache_actions_hex2rgba($action['HEX'])) {
    $action = array_merge($action, $deduced);
    // With or without # is valid, but the colorpicker expects it always.
    $action['HEX'] = '#' . ltrim($action['HEX'], '#');
  }
  $form = array(
    '#prefix' => '<div class="colorform" >',
    '#suffix' => '</div>',
  );

  $form['colorpicker'] = array(
    '#weight' => -1,
    '#markup' => '<div class="colorpicker" style="float:right;"></div>',
  );
  $form['HEX'] = array(
    '#type' => 'textfield',
    '#title' => t('HEX'),
    '#default_value' => $action['HEX'],
    '#size' => 7,
    '#element_validate' => array('imagecache_rgb_validate'),
    '#attributes' => array('class' => array('colorentry')),
  );

  // Adds the JS that binds the textarea with the farbtastic element.
  // Find each colorpicker placeholder:
  // initialize it,
  // then find the nearby textfield that is of type colorentry
  // and attach the colorpicker behavior to it.
  // This is so we can support more that one per page if neccessary.
  $init_colorpicker_script = "
    (function ($) {
      Drupal.behaviors.attachcolorpicker = {
        attach: function(context) {
          $('.colorpicker').each(function () {
            // Configure picker to be attached to the nearest colorentry field.
            linked_target = $('.colorentry', $(this).closest('.colorform'))
            farb = $.farbtastic($(this), linked_target);
          });
        }
      }
    })(jQuery);
  ";

  // Add Farbtastic color picker.
  $form['HEX']['#attached'] = array(
    'library' => array(
      array('system', 'farbtastic'),
    ),
    'js' => array(
      array(
        'type' => 'inline',
        'data' => $init_colorpicker_script,
      ),
    ),
  );

  return $form;
}

/**
 * Element validate handler to ensure a hexadecimal color value.
 *
 * The core image_effect_color_validate() was not intelligent enough.
 * Actually parse the value in order to see if it is parsable.
 *
 * @param array $element
 * param array $form_state
 *   Not used
 */
function imagecache_rgb_validate($element/*, &$form_state*/) {
  if ($element['#value'] != '') {
    $rgba_value = imagecache_actions_hex2rgba($element['#value']);
    if (!$rgba_value) {
      // Returning NULL means a parse error.
      form_error($element, t('!name must be a hexadecimal color value.', array('!name' => $element['#title'])));
    }
  }
}

/**
 * Displays a chosen color for use in the style summary snippets,
 * by actually rendering the color.
 *
 * @param array $variables
 *
 * @return string
 */
function theme_imagecacheactions_rgb($variables) {
  if (!empty($variables['RGB']['HEX'])) {
    $hex = ltrim($variables['RGB']['HEX'], '#');
    return " <span style=\"width:2em; border:1px solid white; background-color:#{$hex}\" >&nbsp;#{$hex}&nbsp;</span>";
  }
  return ' ' . t('Transparent');
}
