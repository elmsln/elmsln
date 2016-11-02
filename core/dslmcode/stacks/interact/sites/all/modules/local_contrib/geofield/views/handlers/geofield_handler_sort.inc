<?php

/**
 * @file
 * Distance sort implementation.
 */

class geofield_handler_sort extends views_handler_sort {
  function query() {
    $this->ensure_my_table();
    $lat_alias = $this->table_alias . '.' . $this->definition['field_name'] . '_lat';
    $lon_alias = $this->table_alias . '.' . $this->definition['field_name'] . '_lon';

    $proximityPlugin = geofield_proximity_load_plugin($this->options['source']);
    $options = $proximityPlugin->getSourceValue($this);

    if ($options != FALSE) {
      $haversine_options = array(
        'origin_latitude' => $options['latitude'],
        'origin_longitude' => $options['longitude'],
        'destination_latitude' => $lat_alias,
        'destination_longitude' => $lon_alias,
        'earth_radius' => GEOFIELD_KILOMETERS,
      );

      $this->query->add_orderby(NULL, geofield_haversine($haversine_options), $this->options['order'], $this->table_alias . '_geofield_distance');
    }    
  }

  function option_definition() {
    $options = parent::option_definition();
    // Data sources and info needed.
    $options['source'] = array('default' => 'manual');
    
    $proximityHandlers = module_invoke_all('proximity_views_handlers');
    foreach ($proximityHandlers as $key => $handler) {
      if (class_exists($handler['class'])) {
        $proximityPlugin = new $handler['class']();
        $proximityPlugin->option_definition($options, $this);
      }
    }
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['source'] = array(
      '#type' => 'select',
      '#title' => t('Source of Origin Point'),
      '#description' => t('How do you want to enter your origin point?'),
      '#options' => array(),
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'geofield') . '/js/viewsProximityValue.js',
        ),
      ),
      '#default_value' => $this->options['source'],
    );

    $proximityHandlers = module_invoke_all('proximity_views_handlers');
    foreach ($proximityHandlers as $key => $handler) {
      $form['source']['#options'][$key] = $handler['name'];
      if (class_exists($handler['class'])) {
        $proximityPlugin = new $handler['class']();
        $proximityPlugin->options_form($form, $form_state, $this);
      }
    }
  }

  function options_validate(&$form, &$form_state) {
    $proximityPlugin = geofield_proximity_load_plugin($form_state['values']['options']['source']);
    $proximityPlugin->options_validate($form, $form_state, $this);
  }
}
