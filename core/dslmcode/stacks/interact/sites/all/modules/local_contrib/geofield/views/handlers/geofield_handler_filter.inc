<?php

/**
 * @file
 * Distance filter implementation.
 */

class geofield_handler_filter extends views_handler_filter_numeric {

    function operators() {
    $operators = array(
      '<' => array(
        'title' => t('Is less than'),
        'method' => 'op_simple',
        'short' => t('<'),
        'values' => 1,
      ),
      '<=' => array(
        'title' => t('Is less than or equal to'),
        'method' => 'op_simple',
        'short' => t('<='),
        'values' => 1,
      ),
      '=' => array(
        'title' => t('Is equal to'),
        'method' => 'op_simple',
        'short' => t('='),
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'method' => 'op_simple',
        'short' => t('!='),
        'values' => 1,
      ),
      '>=' => array(
        'title' => t('Is greater than or equal to'),
        'method' => 'op_simple',
        'short' => t('>='),
        'values' => 1,
      ),
      '>' => array(
        'title' => t('Is greater than'),
        'method' => 'op_simple',
        'short' => t('>'),
        'values' => 1,
      ),
      'between' => array(
        'title' => t('Is between'),
        'method' => 'op_between',
        'short' => t('between'),
        'values' => 2,
      ),
      'not between' => array(
        'title' => t('Is not between'),
        'method' => 'op_between',
        'short' => t('not between'),
        'values' => 2,
      ),
    );

    return $operators;
  }

  function query() {
    $proximityPlugin = geofield_proximity_load_plugin($this->options['source']);
    $options = $proximityPlugin->getSourceValue($this);

    if ($options) {
      $lat_alias = $this->definition['field_name'] . '_lat';
      $lon_alias = $this->definition['field_name'] . '_lon';
      $this->ensure_my_table();

      $info = $this->operators();
      if (!empty($info[$this->operator]['method'])) {
        $haversine_options = array(
          'origin_latitude' => $options['latitude'],
          'origin_longitude' => $options['longitude'],
          'destination_latitude' => $this->table_alias . '.' . $lat_alias,
          'destination_longitude' => $this->table_alias . '.' . $lon_alias,
          'earth_radius' => $this->value['unit'],
        );
        $this->{$info[$this->operator]['method']}($haversine_options);
      }
    }
  }

  function op_between($options) {
    $this->query->add_where_expression($this->options['group'], geofield_haversine($options) . ' ' . strtoupper($this->operator) . ' ' . $this->value['distance'] . ' AND ' . $this->value['distance2']);
  }

  function op_simple($options) {
    $this->query->add_where_expression($this->options['group'], geofield_haversine($options) . ' ' . $this->operator . ' ' . $this->value['distance']);
  }

  function option_definition() {
    $options = parent::option_definition();
    // Data sources and info needed.
    $options['source'] = array('default' => 'manual');
    $options['value'] = array(
      'default' => array(
        'distance' => 100,
        'distance2' => 200,
        'unit' => GEOFIELD_KILOMETERS,
        'origin' => array(),
      ),
    );
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

    $form['source_change'] = array(
      '#type' => 'submit',
      '#value' => 'Change Source Widget',
      '#submit' => array('geofield_views_ui_change_proximity_widget'),
    );

    $proximityHandlers = module_invoke_all('proximity_views_handlers');
    foreach ($proximityHandlers as $key => $handler) {
      // Manually skip 'Exposed Filter', since it wouldn't make any sense in this context.
      if ($key != 'exposed_geofield_filter') {
        $form['source']['#options'][$key] = $handler['name'];
        if (class_exists($handler['class'])) {
          $proximityPlugin = new $handler['class']();
          $proximityPlugin->options_form($form, $form_state, $this);
        }
      }
    }

    // Look for any top-level item with a #proximity_plugin_value_element set. If found, it doesn't
    // belong in this particular field.
    foreach ($form as $key =>$form_item) {
      if (isset($form_item['#proximity_plugin_value_element']) && $form_item['#proximity_plugin_value_element'] == TRUE) {
        unset($form[$key]);
      }
    }
  }

  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);
    $proximityPlugin = geofield_proximity_load_plugin($form_state['values']['options']['source']);
    $proximityPlugin->options_validate($form, $form_state, $this);
  }

  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'geofield_proximity',
      '#title' => t('Proximity Search'),
      '#default_value' => array(
        'distance' => $this->value['distance'],
        'unit' => $this->value['unit'],
        'origin' => (is_string($this->value['origin'])) ? trim($this->value['origin']) : $this->value['origin'],
      ),
      '#origin_options' => array(
        '#attributes' => array(
          'class' => array('geofield-proximity-origin'),
        ),
      ),
    );

    $proximityPlugin = geofield_proximity_load_plugin($this->options['source']);
    $proximityPlugin->value_form($form, $form_state, $this);

    if (in_array($this->operator, array('between', 'not between'))) {
      $form['value']['#geofield_range'] = TRUE;
      $form['value']['#default_value']['distance2'] = $this->value['distance2'];
    }
  }

  function value_validate($form, &$form_state) {
    parent::value_validate($form, $form_state);
    $proximityPlugin = geofield_proximity_load_plugin($form_state['values']['options']['source']);
    $proximityPlugin->value_validate($form, $form_state, $this);
  }

  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    $options = $this->operator_options('short');
    $output = check_plain($options[$this->operator]);
    if (in_array($this->operator, $this->operator_values(2))) {
      $output .= ' ' . t('@min and @max', array('@min' => $this->value['distance'], '@max' => $this->value['distance2']));
    }
    elseif (in_array($this->operator, $this->operator_values(1))) {
      $output .= ' ' . check_plain($this->value['distance']);
    }
    return $output;
  }

  /**
   * Check to see if input from the exposed filters should change
   * the behavior of this filter.
   *   - @TODO: This could be more polished.
   */
  function accept_exposed_input($input) {

    if (empty($this->options['expose']['identifier'])) {
      return TRUE;
    }

    if (!(isset($this->options['expose']) && isset($this->options['expose']['identifier']))) {
      return FALSE;
    }

    $input_id = $this->options['expose']['identifier'];
    if (empty($input[$input_id]) || $input[$input_id]['distance'] === '' || $input[$input_id]['origin'] === '') {
      return FALSE;
    }

    $this->value['distance'] = $input[$input_id]['distance'];
    $this->value['unit'] = $input[$input_id]['unit'];
    $this->value['origin'] = $input[$input_id]['origin'];
    return TRUE;
  }
}

function geofield_views_ui_change_proximity_widget($form, &$form_state) {
  $item = &$form_state['handler']->options;
  $changed = $item['source'] != $form_state['values']['options']['source'];
  $item['source'] = $form_state['values']['options']['source'];

  if ($changed) {
    if ($item['source'] == 'manual') {
      $item['value']['origin'] = array('lat' => '', 'lon' => '');
    }
    else {
      $item['value']['origin'] = '';
    }
  }

  $form_state['view']->set_item($form_state['display_id'], $form_state['type'], $form_state['id'], $item);

  views_ui_cache_set($form_state['view']);
  $form_state['rerender'] = TRUE;
  $form_state['rebuild'] = TRUE;
  $form_state['force_expose_options'] = TRUE;
}
