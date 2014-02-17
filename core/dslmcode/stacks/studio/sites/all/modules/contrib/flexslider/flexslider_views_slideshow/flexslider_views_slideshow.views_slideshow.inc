<?php

/**
 * @file
 * Describe the file
 *
 * @author Mathew Winstone (minorOffense) <mwinstone@coldfrontlabs.ca>
 */

/**
 * Implements hook_views_slideshow_slideshow_info().
 */
function flexslider_views_slideshow_views_slideshow_slideshow_info() {
  $options = array(
    'flexslider_views_slideshow' => array(
      'name' => t('Flex Slider'),
      'accepts' => array(
//        'goToSlide',
        'nextSlide',
        'pause',
        'play',
        'previousSlide',
      ),
      'calls' => array(
//        'transitionBegin',
//        'transitionEnd',
//        'goToSlide',
        'pause',
        'play',
        'nextSlide',
        'previousSlide',
      ),
    ),
  );

  // @todo figure out which options to add

  return $options;
}

/**
 * Implements hook_views_slideshow_option_definition().
 */
function flexslider_views_slideshow_views_slideshow_option_definition() {
  // Default options for FlexSlider
  $options['flexslider_views_slideshow'] = array(
    'contains' => array(
      'optionset' => array('default' => 'default'),
      'caption_field' => array('none' => 'None'),
    ),
  );
  // @todo figure out which options to define
  // @todo integrate with "optionsets"

  return $options;
}

/**
 * Configuration form within the Views Slideshow settings pane
 */
function flexslider_views_slideshow_views_slideshow_slideshow_type_form(&$form, &$form_state, &$view) {
    // For a full list of options
    // @see http://flex.madebymufffin.com/

    // Load the list of option sets
    $optionsets = flexslider_optionset_load_all();
    // Parse out into key/value pairs
    foreach($optionsets as $key => $optionset) {
      $options[$key] = $optionset->title;
    }
    
    // Add a select field
    $form['flexslider_views_slideshow']['optionset'] = array(
      '#type' => 'select',
      '#title' => t('Option Set'),
      '#multiple' => FALSE,
      '#description' => t('Select a configured option set to use with Flex Slider.'),
      '#options' => $options,
      '#default_value' => $view->options['flexslider_views_slideshow']['optionset'],
    );

    $link_options = array('none' => t('None'));

    foreach ($view->display->handler->get_handlers('field') as $field => $handler) {
      $link_options[$field] = $handler->ui_name();
    }

    $form['flexslider_views_slideshow']['caption_field'] = array(
      '#type' => 'select',
      '#title' => t('Caption Field'),
      '#multiple' => FALSE,
      '#description' => t('Select a field to be used as an image caption.'),
      '#options' => $link_options,
      '#default_value' => $view->options['flexslider_views_slideshow']['caption_field'],
    );
    
}

function flexslider_views_slideshow_views_slideshow_slideshow_type_form_validate(&$form, &$form_state, &$view) {
  // @todo add validation for any fields in the settings form
}
