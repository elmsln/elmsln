<?php

/**
 * @file
 * Leaflet field formatter functions.
 */

/**
 * Implements hook_field_formatter_info().
 */
function leaflet_field_formatter_info() {
  $formatters = array();

  if (module_exists('geofield')) {
    $formatters['geofield_leaflet'] = array(
      'label' => t('Leaflet'),
      'field types' => array('geofield'),
      'settings' => array(
        'leaflet_map' => '',
        'height' => 400,
        'popup' => array(
          'show' => '',
          'text' => '',
        ),
        'zoom' => array(
          'initialZoom' => '',
          'minZoom' => 1,
          'maxZoom' => 19
        ),
        'icon' => array(
          'iconUrl' => '',
          'shadowUrl' => '',
          'iconSize' => array(
            'x' => '',
            'y' => '',
          ),
          'iconAnchor' => array(
            'x' => '',
            'y' => '',
          ),
          'shadowAnchor' => array(
            'x' => '',
            'y' => '',
          ),
          'popupAnchor' => array(
            'x' => '',
            'y' => '',
          ),
          'html' => '',
          'htmlClass' => '',
        ),
        'vector_display' => array(
          'stroke_override' => 0,
          'stroke' => 1,
          'color' => '',
          'weight' => '',
          'opacity' => '',
          'dashArray' => '',
          'fill' => 1,
          'fillColor' => '',
          'fillOpacity' => '',
          'clickable' => 1,
        ),
      ),
    );
  }

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function leaflet_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $entity_type = $instance['entity_type'];

  $element = array();

  if ($display['type'] == 'geofield_leaflet') {
    $options = array('' => t('-- Select --'));
    foreach (leaflet_map_get_info() as $key => $map) {
      $options[$key] = $map['label'];
    }

    $element['leaflet_map'] = array(
      '#title' => t('Leaflet Map'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $settings['leaflet_map'],
      '#required' => TRUE,
    );

    $element['height'] = array(
      '#title' => t('Map Height'),
      '#type' => 'textfield',
      '#default_value' => $settings['height'],
      '#field_suffix' => t('px'),
      '#element_validate' => array('element_validate_integer_positive'),
    );

    foreach ($form['#fields'] as $fieldname) {
      $field_options[$fieldname] = $fieldname;
    }
    $fieldpath = 'fields[' . $field['field_name'] . '][settings_edit_form][settings]';
    $element['popup'] = leaflet_form_elements('popup', $settings, array('path' => $fieldpath));
    $element['zoom'] = leaflet_form_elements('zoom', $settings);
    $element['icon'] = leaflet_form_elements('icon', $settings, array('path' => $fieldpath, 'fields' => $field_options));
    $element['vector_display'] = leaflet_form_elements('vector_display', $settings, array('path' => $fieldpath));
    // Show the list of available tokens.
    $element['tokens'] = leaflet_form_elements('tokens', $settings, array('weight' => 999, 'entity_type' => $entity_type));
  }

  return $element;
}

/**
 * Validation callback for icon urls.
 */
function leaflet_icon_validate($element, &$form_state, $form) {
  if (!empty($element['#value']) && !valid_url($element['#value'])) {
    form_error($element, t('Icon URL is invalid'));
  }
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function leaflet_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = '';

  if ($display['type'] == 'geofield_leaflet') {
    $summary = t('Leaflet map: @map', array('@map' => $settings['leaflet_map']));
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function leaflet_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  if (count($items) == 0) {
    return '';
  }
  else {
    switch ($display['type']) {
      case 'geofield_leaflet':
        $map = leaflet_map_get_info($settings['leaflet_map']);
        $features = leaflet_process_geofield($items);
        foreach ($features as &$feat) {
          $feat['entity'] = $entity;
        }
        leaflet_apply_map_settings($map, $features, $settings, $entity_type);
        $element[0] = leaflet_build_map($map, $features, $settings['height'] . 'px');
        break;
    }

    return $element;
  }
}

/**
 * Convert a geofield into an array of map points.
 *
 * @param array $items
 *   A collection of geofield values.
 *
 * @return array
 *   Points built for consumption by the leaflet module as expected by
 * leaflet_render_map().
 */
function leaflet_process_geofield($items = array()) {
  $data = array();

  geophp_load();

  foreach ($items as $delta => $item) {
    // Translate linestring to polyline:
    if ($item['geo_type'] == 'multilinestring') {
      $item['geo_type'] = 'multipolyline';
    }
    // Geofield 7.x-2.x compatibility.
    if (!isset($item['wkt']) && isset($item['geom'])) {
      $item['wkt'] = $item['geom'];
    }
    $datum = array('type' => $item['geo_type']);
    switch ($item['geo_type']) {
      case 'point':
        $datum += array(
          'lat' => (float) $item['lat'],
          'lon' => (float) $item['lon'],
        );

        $data[] = $datum;
        break;

      case 'linestring':
        $geom = geoPHP::load($item['wkt'], 'wkt');
        $components = $geom->getComponents();

        foreach ($components as $component) {
          $datum['points'][] = array(
            'lat' => $component->getY(),
            'lon' => $component->getX(),
          );
        }

        $data[] = $datum;
        break;

      case 'polygon':
        $geom = geoPHP::load($item['wkt'], 'wkt');
        $tmp = $geom->getComponents();
        $components = $tmp[0]->getComponents();

        foreach ($components as $component) {
          $datum['points'][] = array(
            'lat' => $component->getY(),
            'lon' => $component->getX(),
          );
        }

        $data[] = $datum;
        break;

      case 'multipoint':
        $geom = geoPHP::load($item['wkt'], 'wkt');
        $points = $geom->getComponents();
        foreach ($points as $point) {
          $data[] = array(
            'type' => 'point',
            'lat' => $point->getY(),
            'lon' => $point->getX(),
          );
        }
        break;

      case 'multipolygon':
        $geom = geoPHP::load($item['wkt'], 'wkt');

        $tmp = $geom->getComponents();
        $components = array();
        foreach ($tmp as $polygon) {
          $polygon_component = $polygon->getComponents();
          foreach ($polygon_component as $linestring) {
            $components[] = $linestring;
          }
        }
        foreach ($components as $key => $component) {
          $subcomponents = $component->getComponents();
          foreach ($subcomponents as $subcomponent) {
            $datum['component'][$key]['points'][] = array(
              'lat' => $subcomponent->getY(),
              'lon' => $subcomponent->getX(),
            );
          }
          unset($subcomponent);
        }

        $data[] = $datum;
        break;

      case 'multipolyline':
        $geom = geoPHP::load($item['wkt'], 'wkt');
        $components = $geom->getComponents();
        foreach ($components as $key => $component) {
          $subcomponents = $component->getComponents();
          foreach ($subcomponents as $subcomponent) {
            $datum['component'][$key]['points'][] = array(
              'lat' => $subcomponent->getY(),
              'lon' => $subcomponent->getX(),
            );
          }
          unset($subcomponent);
        }

        $data[] = $datum;
        break;

      case 'geometrycollection':
        $geom = geoPHP::load($item['wkt'], 'wkt');
        foreach ($geom as $geom_items) {
          foreach ($geom_items as $geom_item) {
            $class = get_class($geom_item);
            switch ($class) {
              case 'Point':
                $datum = array();
                $datum['type'] = 'point';
                $datum += array(
                  'lat' => (float) $geom_item->coords[1],
                  'lon' => (float) $geom_item->coords[0],
                );
                $data[] = $datum;
                break;

              case 'LineString':
                $points = $geom_item->getComponents();
                $datum = array();
                $datum['type'] = 'linestring';
                foreach ($points as $component) {
                  $datum['points'][] = array(
                    'lat' => $component->getY(),
                    'lon' => $component->getX(),
                  );
                }
                $data[] = $datum;
                break;

              case 'Polygon':
                $points = $geom_item->getComponents();
                $components = $points[0]->getComponents();
                $datum = array();
                $datum['type'] = 'polygon';
                foreach ($components as $component) {
                  $datum['points'][] = array(
                      'lat' => $component->getY(),
                      'lon' => $component->getX(),
                  );
                }
                $data[] = $datum;
                break;
            }
          }
        }
        break;
    }
  }

  return $data;
}

/**
 * Universal method for applying map settings from leaflet_form_elements items.
 *
 * @array $map
 *   Leaflet map definition.
 * @array $features
 *   Associative array of map features.
 * @array $map_settings
 *   Map settings returned by a settings form.
 * @string $entity_type
 *   Entity type this map is being displayed for.
 *
 */
function leaflet_apply_map_settings(&$map, &$features, $map_settings, $entity_type) {
  // These are the settings key that will be tokenized by entity:
  $token_by_entity = array(
    'popup',
    'icon',
    'vector_display',
  );

  // Apply zoom settings (will override hook_leaflet_map_info() values):
  if (isset($map_settings['zoom']['initialZoom']) && $map_settings['zoom']['initialZoom'] >= 0) {
    $map['settings']['zoom'] = intval($map_settings['zoom']['initialZoom']);
  }
  if (isset($map_settings['zoom']['minZoom']) && $map_settings['zoom']['minZoom'] >= 0) {
    $map['settings']['minZoom'] = intval($map_settings['zoom']['minZoom']);
  }
  if (isset($map_settings['zoom']['maxZoom']) && $map_settings['zoom']['maxZoom'] >= 0) {
    $map['settings']['maxZoom'] = intval($map_settings['zoom']['maxZoom']);
  }
  if (isset($map_settings['zoom']['scrollWheelZoom'])) {
    $map['settings']['scrollWheelZoom'] = $map_settings['zoom']['scrollWheelZoom'];
  }
  $icon = 'none';
  if (isset($map_settings['icon']['iconType'])) {
    $icon = $map_settings['icon']['iconType'];
    $classes = NULL;
    if ($icon == 'html' && isset($map_settings['icon']['htmlClass'])) {
      // Clean the user-entered classes.
      $classes = explode(' ', $map_settings['icon']['htmlClass']);
      array_walk($classes, 'drupal_html_class');
      $map_settings['icon']['htmlClass'] = implode(' ', $classes);
    }
    elseif (!$map_settings['icon']['iconUrl']) {
      $icon = 'none';
    }
  }

  $vector_settings = FALSE;
  if (!empty($map_settings['vector_display']) && $map_settings['vector_display']['stroke_override']) {
    $vector_settings = TRUE;
  }

  foreach ($features as &$feat) {
    // Apply tokens where relevant:
    $settings = $map_settings;
    $entity = !empty($feat['entity']) ? $feat['entity'] : NULL;
    $token_args = array('data' => array($entity_type => $entity), 'options' => array('clear' => TRUE));
    foreach ($token_by_entity as $key) {
      if (isset($settings[$key]) && is_array($settings[$key])) {
        array_walk_recursive($settings[$key], 'leaflet_token_replace', $token_args);
      }
    }

    if (isset($settings['popup']['show']) && $settings['popup']['show']) {
      $feat['popup'] = trim($settings['popup']['text']);
    }

    // Apply Icon settings:
    if ($icon == 'html') {

      // Maps handled by Views will have rendered HTML already.
      if (isset($feat['rendered_html'])) {
        $feat['html'] = $feat['rendered_html'];
      }
      else {
        $icon_config = array(
          'label' => 'hidden',
          'settings' => array(
            'image_style' => isset($settings['icon']['iconImageStyle']) ? $settings['icon']['iconImageStyle'] : '',
          ),
        );
        $icon_field = field_view_field($entity_type, $feat['entity'], $settings['icon']['html'], $icon_config);
        $feat['html'] = render($icon_field);
      }

      if (!empty($settings['icon']['iconSize']['x']) || !empty($settings['icon']['iconSize']['y'])) {
        // We hand the size off to the API, but the rendered HTML will dictate
        // its own size, so we override that as well.
        // @todo: actually allow the API settings to control this.
        $feat['icon']['iconSize'] = $settings['icon']['iconSize'];
        if (!empty($icon_field)) {
          foreach (element_children($icon_field) as $i) {
            if (!empty($settings['icon']['iconSize']['x'])) {
              $icon_field[$i]['#item']['width'] = $settings['icon']['iconSize']['x'];
              unset($icon_field[$i]['#item']['width']);
            }
            if (!empty($settings['icon']['iconSize']['y'])) {
              $icon_field[$i]['#item']['height'] = $settings['icon']['iconSize']['y'];
              unset($icon_field[$i]['#item']['width']);
            }
          }
        }
      }

      $feat['html_class'] = $settings['icon']['htmlClass'];
      $feat['icon']['iconAnchor'] = $settings['icon']['iconAnchor'];
    }
    if ($icon == 'marker') {
      $feat['icon'] = $settings['icon'];
      unset($feat['icon']['html']);
      unset($feat['icon']['html_class']);
    }

    // Apply vector display settings:
    if ($vector_settings) {
      if ($feat['type'] != 'point') {
        // To avoid overwrite the options with empty values removes all
        // NULL, FALSE and empty Strings and leaves zero values.
        $options = array_filter($settings['vector_display'], 'strlen');
        unset($options['stroke_override']);
        $feat['options'] = $options;
      }
    }
    // Unset the entity here so it does not get returned to the client in JS.
    unset($feat['entity']);
  }
}

/**
 * Replaces all tokens in a given string with appropriate values.
 *
 * This is a wrapper arround token_replace, to apply token_replace only
 * to strings.
 */
function leaflet_token_replace(&$subject, $key, $data = array()) {
  if (is_string($subject) && $subject) {
    $subject = token_replace($subject, $data['data'], $data['options']);
  }
}

/**
 * Helper function to standardize forms between views and field formatters.
 * 
 * $group - String
 *  The name of the group element to generate.
 * 
 * $settings - Array
 *  Current form settings (for defaults, etc)
 * 
 * $options - Array
 *  Special options needed for this form element, if necessary.
 * 
 * Return - A fully loaded form element.
 */
function leaflet_form_elements($group, $settings, $options = NULL) {
  $form_element = NULL;
  switch ($group) {
    case 'popup':
      $form_element = array(
        '#title' => t('Popup Settings'),
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['show'] = array(
        '#title' => t('Popup'),
        '#description' => t('Show a popup when locations are clicked.'),
        '#type' => 'checkbox',
        '#default_value' => $settings[$group]['show'],
      );
      $form_element['text'] = array(
        '#title' => t('Popup text'),
        '#description' => t('Enter the text for the popup. Tokens are supported.'),
        '#type' => 'textfield',
        '#default_value' => $settings[$group]['text'],
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[popup][show]"]' => array('checked' => TRUE),
          ),
        ),
      );
      break;

    case 'zoom':
      // Define zoom options.
      $zoom_options = array(
        -1 => t('Use map defined setting'),
        0 => t('0 - Low/Far'),
        18 => t('18 - High/Close'),
      );
      for ($i = 1; $i < 18; $i++) {
        $zoom_options[$i] = $i;
      }
      ksort($zoom_options);

      $form_element = array(
        '#title' => t('Zoom Settings'),
        '#description' => t("These settings will override the zoom settings defined in the map definition. Low values are 'zoomed out', high values are 'zoomed in'."),
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['initialZoom'] = array(
        '#title' => t('Initial zoom level'),
        '#description' => t('The starting zoom level when this map is rendered.  Restricted by min and max zoom settings.'),
        '#type' => 'select',
        '#options' => $zoom_options,
        '#default_value' => isset($settings[$group]['initialZoom']) ? $settings[$group]['initialZoom'] : -1,
        '#element_validate' => array('leaflet_initial_zoom_validate'),
      );
      $form_element['minZoom'] = array(
        '#title' => t('Minimum zoom level'),
        '#description' => t('The minimum zoom level allowed. (How far away can you view from?)'),
        '#type' => 'select',
        '#options' => $zoom_options,
        '#default_value' => isset($settings[$group]['minZoom']) ? $settings[$group]['minZoom'] : -1,
        '#element_validate' => array('leaflet_min_zoom_validate'),
      );
      $form_element['maxZoom'] = array(
        '#title' => t('Maximum zoom level'),
        '#description' => t('The maximum zoom level allowed. (How close in can you get?).'),
        '#type' => 'select',
        '#options' => $zoom_options,
        '#default_value' => isset($settings[$group]['maxZoom']) ? $settings[$group]['maxZoom'] : -1,
        '#element_validate' => array('leaflet_max_zoom_validate'),
      );
      $form_element['scrollWheelZoom'] = array(
        '#title' => t('Scroll wheel zoom'),
        '#description' => t('Allow map to be zoomed with the mouse wheel.'),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['scrollWheelZoom']) ? $settings[$group]['scrollWheelZoom'] : 1,
      );
      break;

    case 'icon':
      $form_element = array(
        '#title' => t('Point Icon'),
        '#description' => t('These settings will overwrite the icon settings defined in the map definition.'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['iconType'] = array(
        '#type' => 'radios',
        '#title' => t('Icon Source'),
        '#default_value' => isset($settings[$group]['iconType']) ? $settings[$group]['iconType'] : 'marker',
        '#options' => array(
          'marker' => "Icon File",
          'html' => "Field (html DivIcon)",
        ),
      );
      $form_element['iconUrl'] = array(
        '#title' => t('Icon URL'),
        '#description' => t('Can be an absolute or relative URL.'),
        '#type' => 'textfield',
        '#maxlength' => 999,
        '#default_value' => isset($settings[$group]['iconUrl']) ? $settings[$group]['iconUrl'] : '',
        '#element_validate' => array('leaflet_icon_validate'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['shadowUrl'] = array(
        '#title' => t('Icon Shadow URL'),
        '#description' => t('Can be an absolute or relative URL.'),
        '#type' => 'textfield',
        '#maxlength' => 999,
        '#default_value' => isset($settings[$group]['shadowUrl']) ? $settings[$group]['shadowUrl'] : '',
        '#element_validate' => array('leaflet_icon_validate'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['html'] = array(
        '#type' => 'select',
        '#title' => t('Marker field'),
        '#description' => t('Field to use as output for a map marker.'),
        // See [#1796656]
        '#options' => (array)array_merge(array('' => ''), $options['fields']),
        '#default_value' => isset($settings[$group]['html']) ? $settings[$group]['html'] : '',
        '#empty_option' => t('-- Select --'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
          'required' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
        ),
      );
      $form_element['iconImageStyle'] = array(
        '#title' => t('Icon image style'),
        '#type' => 'select',
        '#default_value' => isset($settings[$group]['iconImageStyle']) ? $settings[$group]['iconImageStyle'] : '',
        '#empty_option' => t('None (original image)'),
        '#options' => image_style_options(FALSE, PASS_THROUGH),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
        ),
      );
      $form_element['htmlClass'] = array(
        '#type' => 'textfield',
        '#title' => t('Marker HTML class'),
        '#description' => t('Required class name for the div used to wrap field output. For multiple classes, separate with a space.'),
        '#default_value' => isset($settings[$group]['htmlClass']) ? $settings[$group]['htmlClass'] : 'leaflet_map_icon',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
          'required' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'html'),
          ),
        ),
      );
      $form_element['iconSize'] = array(
        '#title' => t('Icon Size'),
        '#description' => "It is usually preferable to leave this blank and use the image style system to size the icons. Sizes are in pixels.",
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
      );
      $form_element['iconSize']['x'] = array(
        '#title' => t('Width'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconSize']['x']) ? $settings[$group]['iconSize']['x'] : '',
        '#element_validate' => array('element_validate_integer_positive'),
      );
      $form_element['iconSize']['y'] = array(
        '#title' => t('Height'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconSize']['y']) ? $settings[$group]['iconSize']['y'] : '',
        '#element_validate' => array('element_validate_integer_positive'),
      );
      $form_element['iconAnchor'] = array(
        '#title' => t('Icon Anchor'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#description' => t("The coordinates of the 'tip' of the icon (relative to its top left corner). The icon will be aligned so that this point is at the marker's geographical location."),
      );
      $form_element['iconAnchor']['x'] = array(
        '#title' => t('X'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconAnchor']['x']) ? $settings[$group]['iconAnchor']['x'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['iconAnchor']['y'] = array(
        '#title' => t('Y'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['iconAnchor']['y']) ? $settings[$group]['iconAnchor']['y'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['shadowAnchor'] = array(
        '#title' => t('Shadow Anchor'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#description' => t('The point from which the shadow is shown.'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['shadowAnchor']['x'] = array(
        '#title' => t('X'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['shadowAnchor']['x']) ? $settings[$group]['shadowAnchor']['x'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['shadowAnchor']['y'] = array(
        '#title' => t('Y'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['shadowAnchor']['y']) ? $settings[$group]['shadowAnchor']['y'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['popupAnchor'] = array(
        '#title' => t('Popup Anchor'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#description' => t('The point from which the marker popup opens, relative to the anchor point.'),
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[icon][iconType]"]' => array('value' => 'marker'),
          ),
        ),
      );
      $form_element['popupAnchor']['x'] = array(
        '#title' => t('X'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['popupAnchor']['x']) ? $settings[$group]['popupAnchor']['x'] : '',
        '#element_validate' => array('element_validate_number'),
      );
      $form_element['popupAnchor']['y'] = array(
        '#title' => t('Y'),
        '#type' => 'textfield',
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => isset($settings[$group]['popupAnchor']['y']) ? $settings[$group]['popupAnchor']['y'] : '',
        '#element_validate' => array('element_validate_number'),
      );

      break;

    case "vector_display":
      $form_element = array(
        '#title' => t('Vector Display Options'),
        '#description' => t('These settings will overwrite the !options and constants shared between vector overlays (Polygon, Polyline, Circle).', array('!options' => l(t("default options"), 'http://leafletjs.com/reference.html#path'))),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form_element['stroke_override'] = array(
        '#title' => t('Override Defaults'),
        '#description' => t('If checked, the default values will be overridden by these settings.'),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['stroke_override']) ? $settings[$group]['stroke_override'] : 1,
      );
      $form_element['stroke'] = array(
        '#title' => t('Stroke'),
        '#description' => t('Draw an outline around the shape. Uncheck to disable borders on polygons and circles. (Default: True)'),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['stroke']) ? $settings[$group]['stroke'] : 1,
        '#states' => array(
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['color'] = array(
        '#title' => t('Line Color'),
        '#description' => t('Line color. (Default: #00030f)'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['color']) ? $settings[$group]['color'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['weight'] = array(
        '#title' => t('Line Weight'),
        '#description' => t('Line width in pixels. (Default: 5)'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['weight']) ? $settings[$group]['weight'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['opacity'] = array(
        '#title' => t('Line Opacity'),
        '#description' => t('Line opacity. A number between 0 (would make the line invisible) to 1 (no transparency at all). (Default: 0.5)'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['opacity']) ? $settings[$group]['opacity'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['dashArray'] = array(
        '#title' => t('Line Dash Pattern'),
        '#description' => t("A string that defines the line's !url. Depending on your line weight, this can be hard to see. Note that this is ignored by canvas-powered layers (e.g. Android 2). Sample: 5, 5", array('!url' => l(t('dash pattern'), 'https://developer.mozilla.org/en/SVG/Attribute/stroke-dasharray'))),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['dashArray']) ? $settings[$group]['dashArray'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['fill'] = array(
        '#title' => t('Fill'),
        '#description' => t('Fill the shape with color. Default: "!depends"', array('!depends' => l(t("depends"), 'http://leafletjs.com/reference.html#path-fill'))),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['fill']) ? $settings[$group]['fill'] : 1,
        '#states' => array(
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['fillColor'] = array(
        '#title' => t('Fill Color'),
        '#description' => t('Fill color. Default: #00030f'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['fillColor']) ? $settings[$group]['fillColor'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][fill]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['fillOpacity'] = array(
        '#title' => t('Fill Opacity'),
        '#description' => t('Fill opacity. A number between 0 (would make the fill invisible) to 1 (no transparency at all). Default: 0.2'),
        '#type' => 'textfield',
        '#default_value' => isset($settings[$group]['fillOpacity']) ? $settings[$group]['fillOpacity'] : '',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][fill]"]' => array('checked' => TRUE),
          ),
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form_element['clickable'] = array(
        '#title' => t('Clickable'),
        '#description' => t('If disabled, the vector will not emit mouse events, essentially acting as a part of the underlying map. Default: True'),
        '#type' => 'checkbox',
        '#default_value' => isset($settings[$group]['clickable']) ? $settings[$group]['clickable'] : 1,
        '#states' => array(
          'enabled' => array(
            ':input[name="' . $options['path'] . '[' . $group . '][stroke_override]"]' => array('checked' => TRUE),
          ),
        ),
      );
      break;

    case "tokens":
      // See [#2176681]
      $form_element = array(
        '#type' => 'container',
        '#theme' => 'token_tree_link',
        '#token_types' => array($options['entity_type']),
      );
      break;

  }
  return $form_element;
}

/**
 * Validation callback for the initial zoom level.
 */
function leaflet_initial_zoom_validate($element, &$form_state, $form) {
  $input_root = _leaflet_get_form_input_path($form_state['input'], $element['#parents']);
  $min_zoom = (int) $input_root['minZoom'];
  $max_zoom = (int) $input_root['maxZoom'];
  $initial_zoom = (int) $input_root['initialZoom'];
  if (isset($initial_zoom) && $initial_zoom != -1) {
    if (isset($min_zoom)) {
      if ($min_zoom > $initial_zoom) {
        form_error($element, t('The initial zoom level should be greater than the minimum zoom settings'));
      }
    }
    if (isset($max_zoom) && $max_zoom != -1) {
      if ($max_zoom < $initial_zoom) {
        form_error($element, t('The initial zoom level should be less than the maximum zoom settings'));
      }
    }
  }
}

/**
 * Validation callback for min zoom level.
 */
function leaflet_min_zoom_validate($element, &$form_state, $form) {
  $input_root = _leaflet_get_form_input_path($form_state['input'], $element['#parents']);
  $min_zoom = (int) $input_root['minZoom'];
  $max_zoom = (int) $input_root['maxZoom'];
  if (isset($max_zoom) && $max_zoom != "-1" && isset($min_zoom)) {
    if ($min_zoom > $max_zoom) {
      form_error($element, t('The minimum zoom setting must be less than or equal to the maximum zoom setting'));
    }
  }
}
/**
 * Validation callback for max zoom level.
 */
function leaflet_max_zoom_validate($element, &$form_state, $form) {
  $input_root = _leaflet_get_form_input_path($form_state['input'], $element['#parents']);
  $min_zoom = (int) $input_root['minZoom'];
  $max_zoom = (int) $input_root['maxZoom'];
  if (isset($max_zoom) && $max_zoom != "-1" && isset($min_zoom)) {
    if ($min_zoom > $max_zoom) {
      form_error($element, t('The maximum zoom setting must be greater than or equal to the minimum zoom setting'));
    }
  }
}

/**
 * Helper function to find the correct values for input validation.
 */
function _leaflet_get_form_input_path($path, $path_items) {
  array_pop($path_items);
  while ($item = array_shift($path_items)) {
    $path = $path[$item];
  }
  return $path;
}
