<?php

/**
 * @file
 * Provides FormAPI element callbacks for geofield_latlon and geofield_proximity.
 */

/**
 * Diameter of the Earth in kilometers.
 */
define('GEOFIELD_KILOMETERS', 6371);

/**
 * Diameter of the Earth in meters.
 */
define('GEOFIELD_METERS', 6371000);

/**
 * Diameter of the Earth in miles.
 */
define('GEOFIELD_MILES', 3959);

/**
 * Diameter of the Earth in yards.
 */
define('GEOFIELD_YARDS', 6975175);

/**
 * Diameter of the Earth in feet.
 */
define('GEOFIELD_FEET', 20925525);

/**
 * Diameter of the Earth in nautical miles.
 */
define('GEOFIELD_NAUTICAL_MILES', 3444);

/**
 * Implements hook_element_info().
 */

function geofield_element_info() {
  return array(
    'geofield_latlon' => array(
      '#input' => TRUE,
      '#process' => array('geofield_latlon_element_process'),
      '#element_validate' => array('geofield_latlon_element_validate'),
      '#theme' => array('geofield_latlon'),
      '#theme_wrappers' => array('fieldset'),
    ),
    'geofield_bounds' => array(
      '#input' => TRUE,
      '#process' => array('geofield_bounds_element_process'),
      '#element_validate' => array('geofield_bounds_element_validate'),
      '#theme' => array('geofield_bounds'),
      '#theme_wrappers' => array('fieldset'),
    ),
    'geofield_proximity' => array(
      '#input' => FALSE,
      '#tree' => TRUE,
      '#theme_wrappers' => array('geofield_proximity'),
      '#process' => array('geofield_proximity_element_process'),
    ),
  );
}

/**
 * Process function for geofield_latlon.
 */

function geofield_latlon_element_process($element, &$form_values) {
  $element['#tree'] = TRUE;
  $element['#input'] = TRUE;
  $element['lat'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#required' => (!empty($element['#required'])) ? $element['#required'] : FALSE,
    '#default_value' => (!empty($element['#default_value']['lat'])) ? $element['#default_value']['lat'] : '',
    '#attributes' => array(
      'class' => array('geofield-lat'),
    ),
  );

  $element['lon'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#required' => (!empty($element['#required'])) ? $element['#required'] : FALSE,
    '#default_value' => (!empty($element['#default_value']['lon'])) ? $element['#default_value']['lon'] : '',
    '#attributes' => array(
      'class' => array('geofield-lon'),
    ),
  );

  unset($element['#value']);
  // Set this to false always to prevent notices.
  $element['#required'] = FALSE;

  if (!empty($element['#geolocation']) && $element['#geolocation'] == TRUE) {
    $element['#attached']['js'][] = drupal_get_path('module', 'geofield') . '/js/geolocation.js';
    $element['geocode'] = array(
      '#type' => 'button',
      '#value' => t('Find my location'),
      '#name' => 'geofield-html5-geocode-button',
    );
    $element['#attributes']['class'] = array('auto-geocode');
  }

  return $element;
}

/**
 * Element validation function for geofield_latlon.
 */

function geofield_latlon_element_validate($element, &$form_values) {
  $components = array(
    'lat' => array(
      'title' => 'Latitude',
      'range' => 90,
    ),
    'lon' => array(
      'title' => 'Longitude',
      'range' => 180,
    ),
  );

  $allFilled = TRUE;
  $anyFilled = FALSE;
  foreach ($components as $key => $component) {
    if (!empty($element[$key]['#value'])) {
      if (!is_numeric($element[$key]['#value'])) {
        form_error($element[$key], t('@title: @component_title is not numeric.', array('@title' => $element['#title'], '@component_title' => $component['title'])));
      }
      elseif (abs($element[$key]['#value']) > $component['range']) {
        form_error($element[$key], t('@title: @component_title is out of bounds.', array('@title' => $element['#title'], '@component_title' => $component['title'])));
      }
    }
    if ($element[$key]['#value'] == '') {
      $allFilled = FALSE;
    }
    else {
      $anyFilled = TRUE;
    }
  }
  if ($anyFilled && !$allFilled) {
    foreach ($components as $key => $component) {
      if ($element[$key]['#value'] == '') {
        form_error($element[$key], t('@title: @component_title must be filled too.', array('@title' => $element['#title'], '@component_title' => $component['title'])));
      }
    }
  }
}

/**
 * Process function for geofield_bounds.
 */

function geofield_bounds_element_process($element, &$form_values) {
  $element['#tree'] = TRUE;
  $element['top'] = array(
    '#type' => 'textfield',
    '#title' => t('Top'),
    '#required' => (!empty($element['#required'])) ? $element['#required'] : FALSE,
    '#default_value' => (!empty($element['#default_value']['top'])) ? $element['#default_value']['top'] : '',
    '#attributes' => array(
      'class' => array('geofield-top'),
    ),
  );

  $element['right'] = array(
    '#type' => 'textfield',
    '#title' => t('Right'),
    '#required' => (!empty($element['#required'])) ? $element['#required'] : FALSE,
    '#default_value' => (!empty($element['#default_value']['right'])) ? $element['#default_value']['right'] : '',
    '#attributes' => array(
      'class' => array('geofield-right'),
    ),
  );

  $element['bottom'] = array(
    '#type' => 'textfield',
    '#title' => t('Bottom'),
    '#required' => (!empty($element['#required'])) ? $element['#required'] : FALSE,
    '#default_value' => (!empty($element['#default_value']['bottom'])) ? $element['#default_value']['bottom'] : '',
    '#attributes' => array(
      'class' => array('geofield-bottom'),
    ),
  );

  $element['left'] = array(
    '#type' => 'textfield',
    '#title' => t('Left'),
    '#required' => (!empty($element['#required'])) ? $element['#required'] : FALSE,
    '#default_value' => (!empty($element['#default_value']['left'])) ? $element['#default_value']['left'] : '',
    '#attributes' => array(
      'class' => array('geofield-left'),
    ),
  );

  unset($element['#value']);
  // Set this to false always to prevent notices.
  $element['#required'] = FALSE;

  return $element;
}

/**
 * Element validation function for geofield_latlon.
 */

function geofield_bounds_element_validate($element, &$form_values) {
  $components = array(
    'top' => array(
      'title' => 'Top',
      'range' => 90,
    ),
    'right' => array(
      'title' => 'Right',
      'range' => 180,
    ),
    'bottom' => array(
      'title' => 'Bottom',
      'range' => 90,
    ),
    'left' => array(
      'title' => 'Left',
      'range' => 180,
    ),
  );

  $allFilled = TRUE;
  $anyFilled = FALSE;
  foreach ($components as $key => $component) {
    if (!empty($element[$key]['#value'])) {
      if (!is_numeric($element[$key]['#value'])) {
        form_error($element[$key], t('@title: @component_title is not numeric.', array('@title' => $element['#title'], '@component_title' => $component['title'])));
      }
      elseif (abs($element[$key]['#value']) > $component['range']) {
        form_error($element[$key], t('@title: @component_title is out of bounds.', array('@title' => $element['#title'], '@component_title' => $component['title'])));
      }
    }
    if ($element[$key]['#value'] == '') {
      $allFilled = FALSE;
    }
    else {
      $anyFilled = TRUE;
    }
  }
  if ($anyFilled && !$allFilled) {
    foreach ($components as $key => $component) {
      if ($element[$key]['#value'] == '') {
        form_error($element[$key], t('@title: @component_title must be filled too.', array('@title' => $element['#title'], '@component_title' => $component['title'])));
      }
    }
  }
}

/**
 * Process function for the proximity form element
 */
function geofield_proximity_element_process($element, &$form_state, $form) {
  $element['#attributes'] = array('class' => array('clearfix'));
  $element['#tree'] = TRUE;
  $element['#attached']['css'] = array(drupal_get_path('module', 'geofield') . '/css/proximity-element.css');

  //Create the textfield for distance
  $element['distance'] = array(
    '#type' => 'textfield',
    '#title' => t('Distance'),
    '#default_value' => !empty($element['#default_value']['distance']) ? $element['#default_value']['distance'] : '',
    '#title_display' => 'invisible',
    // Allow decimal numbers as distances
    '#element_validate' => array('element_validate_number'),
  );

  // If #geofield_range is TRUE, create second option for range.
  if (!empty($element['#geofield_range']) && $element['#geofield_range'] == TRUE) {
    $element['distance2'] = array(
      '#type' => 'textfield',
      '#title' => t('Distance End'),
      '#default_value' => !empty($element['#default_value']['distance2']) ? $element['#default_value']['distance2'] : '',
      '#title_display' => 'invisible',
      '#element_validate' => array('element_validate_number'),
    );
  }

  //Create dropdown for units
  $element['unit'] = array(
    '#type' => 'select',
    '#options' => geofield_radius_options(),
    '#title' => t('Unit'),
    '#default_value' => !empty($element['#default_value']['unit']) ? $element['#default_value']['unit'] : GEOFIELD_KILOMETERS,
    '#title_display' => 'invisible',
  );

  //Create textfield for geocoded input
  $element['origin'] = array(
    '#type' => (!empty($element['#origin_element'])) ? $element['#origin_element'] : 'textfield',
    '#title' => t('Origin'),
    '#prefix' => '<span class="geofield-proximity-origin-from">' . t('from') . '</span>',
    '#title_display' => 'invisible',
    '#required' => !empty($element['#required']) ? $element['#required'] : FALSE,
    '#default_value' => !empty($element['#default_value']['origin']) ? $element['#default_value']['origin'] : FALSE,
  );

  if (!empty($element['#origin_options'])) {
    $element['origin'] = array_merge($element['origin'], $element['#origin_options']);
  }

  if (isset($element['#element_validate'])) {
    array_push($element['#element_validate'], 'goefield_proximity_search_validate');
  }
  else {
    $element['#element_validate'] = array('geofield_proximity_search_validate');
  }

  return $element;
}

/**
 * Validate the geofield proximity search form item
 */
function geofield_proximity_search_validate($element, &$form_state) {
  //If the origin is set, ensure the distance is set as well
  if (!empty($element['origin']['#value']) && trim($element['origin']['#value']) != '' && empty($element['distance']['#value']))
    form_set_error(implode('][', $element['#array_parents']) . '][distance', t('@title must be set when @origin is specified.', array('@title' => $element['distance']['#title'], '@origin' => $element['origin']['#title'])));
}

function geofield_theme($existing, $type, $theme, $path) {
  return array(
    'geofield_latlon' => array(
      'arguments' => array('element' => NULL),
      'render element' => 'element',
    ),
    'geofield_proximity' => array(
      'render element' => 'element',
    ),
  );
}

/**
 * Theme wrapper for form item
 */
function theme_geofield_proximity($vars) {
  $element = $vars['element'];

  $attributes = !empty($element['#wrapper_attributes']) ? $element['#wrapper_attributes'] : array('class' => array());
  $attributes['class'][] = 'geofield-proximity-field-wrapper';
  $attributes['class'][] = 'clearfix';

  $wrapper_attributes = array();
  $wrapper_attributes['class'][] = 'clearfix';

  if (isset($element['#children']))
    $element['#children'] = '<div id="' . $element['#id'] . '" ' . drupal_attributes($wrapper_attributes) . '>' . $element['#children'] . '</div>';

  $output = '<div ' . drupal_attributes($attributes) . '>' . theme('form_element', $element) . '</div>';

  return $output;
}

function theme_geofield_latlon($vars) {
  return drupal_render($vars['element']['lat']) . drupal_render($vars['element']['lon']) . drupal_render($vars['element']['geocode']);
}

/**
 * Returns options for radius of the Earth.
 */

function geofield_radius_options() {
  return array(
    GEOFIELD_KILOMETERS => t('Kilometers'),
    GEOFIELD_METERS => t('Meters'),
    GEOFIELD_MILES => t('Miles'),
    GEOFIELD_YARDS => t('Yards'),
    GEOFIELD_FEET => t('Feet'),
    GEOFIELD_NAUTICAL_MILES => t('Nautical Miles'),
  );
}
