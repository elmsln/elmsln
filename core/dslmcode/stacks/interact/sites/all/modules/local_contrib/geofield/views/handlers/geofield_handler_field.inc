<?php

/**
 * @file
 * Distance field implementation.
 */

class geofield_handler_field extends views_handler_field_numeric {
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
        'earth_radius' => $this->options['radius_of_earth'],
      );

      $this->field_alias = $this->query->add_field(NULL, geofield_haversine($haversine_options), $this->table_alias . '_' . $this->field);
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
    
    $options['radius_of_earth'] = array('default' => GEOFIELD_KILOMETERS);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['source'] = array(
      '#type' => 'select',
      '#title' => t('Source of Origin Point'),
      '#description' => t('How do you want to enter your origin point?'),
      '#options' => array(),
      '#default_value' => $this->options['source'],
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'geofield') . '/js/viewsProximityValue.js',
        ),
      ),
    );

    $proximityHandlers = module_invoke_all('proximity_views_handlers');
    foreach ($proximityHandlers as $key => $handler) {
      $form['source']['#options'][$key] = $handler['name'];
      if (class_exists($handler['class'])) {
        $proximityPlugin = new $handler['class']();
        $proximityPlugin->options_form($form, $form_state, $this);
      }
    }

    $form['radius_of_earth'] = array(
      '#type' => 'select',
      '#title' => t('Unit of Measure'),
      '#description' => '',
      '#options' => geofield_radius_options(),
      '#default_value' => $this->options['radius_of_earth'],
    );
  }

  function options_validate(&$form, &$form_state) {
    $proximityPlugin = geofield_proximity_load_plugin($form_state['values']['options']['source']);
    $proximityPlugin->options_validate($form, $form_state, $this);
  }

  function get_value($values, $field = NULL) {
    if (isset($values->{$this->field_alias})) {
      return $values->{$this->field_alias};
    }
  }
}
