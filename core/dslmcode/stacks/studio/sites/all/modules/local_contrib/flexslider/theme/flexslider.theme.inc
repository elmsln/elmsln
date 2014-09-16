<?php
/**
 * @file
 * Theming functions for the flexslider module.
 * 
 * Preprocessor functions fill variables for templates and helper
 * functions to make theming easier.
 */

/**
 * Template preprocess handler for 'flexslider_container' theme.
 */
function template_preprocess_flexslider_container(&$vars) {
  // Each flexslider instance gets a unique id
  $flexslider_id = &drupal_static('flexslider_id', 0);
  $vars['id'] = ++$flexslider_id;

  // Load the used option set
  if (!empty($vars['settings']['flexslider_optionset'])) {
    $optionset = flexslider_optionset_load($vars['settings']['flexslider_optionset']);
  }
  if (empty($optionset)) {
    // Fall back to 'default' option set
    $optionset = flexslider_optionset_load('default');
  }
  
  // Attach flexslider JavaScript
  flexslider_add($flexslider_id, $optionset);

  // Prepare image elements
  $items = $vars['items'];
  $vars['items'] = array();
  $thumb_style = empty($optionset->imagestyle_thumb) ? 'flexslider_thumb' : $optionset->imagestyle_thumb;
  foreach ($items as $delta => $item) {
    // Get URL for "normal" image
    if (empty($optionset->imagestyle_normal)) {
       $normal_url = file_create_url($item['uri']);
    }
    else {
       $normal_url = image_style_url($optionset->imagestyle_normal, $item['uri']);
    }

    $vars['items'][$delta] = array(
      '#theme' => 'image_formatter',
      '#item' => $item,
      '#image_style' => $optionset->imagestyle_normal,
//      '#path' => array(
//         'path' => $normal_url,
//         'options' => array(),
//      ),
    );
  }
}