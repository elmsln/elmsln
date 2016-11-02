<?php

/**
 * @file
 * Extension of the Views Plugin Style for Leaflet Map
 * Adapted from the GeoField Map views module and the OpenLayers Views module.
 */

class leaflet_views_plugin_style extends views_plugin_style {

  /**
   * If this view is displaying an entity, save the entity type and info.
   */
  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->entity_type = $this->options['entity_type'];
    $this->entity_info = entity_get_info($this->entity_type);
    // Fallback for views that do not have entity_type set, for example
    // because the view was created before this option got introduced.
    if (empty($this->entity_type)) {
      $info = $this->getEntityInfoByTable($view->base_table);
      if (!empty($info)) {
        $this->entity_type = $info['entity type'];
        $this->entity_info = $info;
      }
    }
  }

  /**
   * Gets entity information based on the entity table passed in.
   *
   * @param string $table
   *   Table name.
   *
   * @return array
   *   Returns the entity_info array.
   */
  function getEntityInfoByTable($table) {
    $info = entity_get_info();
    foreach($info as $entity_type => &$entity_info) {
      if($entity_info['base table'] == $table) {
        $entity_info['entity type'] = $entity_type;
        return $entity_info;
      }
    }
    return array();
  }

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['entity_type'] = array('default' => '');
    $options['data_source'] = array('default' => '');
    $options['name_field'] = array('default' => '');
    $options['description_field'] = array('default' => '');
    $options['view_mode'] = array('default' => 'full');
    $options['map'] = array('default' => '');
    $options['height'] = array('default' => '400');
    $options['hide_empty'] = array('default' => '');
    $options['popup']['contains'] = array(
      'show' => array('default' => ''),
      'text' => array('default' => ''),
    );
    $options['zoom']['contains'] = array(
      'initialZoom' => array('default' => ''),
      'minZoom' => array('default' => 0),
      'maxZoom' => array('default' => 18),
      'scrollWheelZoom' => array('default' => 1),
    );
    $options['icon']['contains'] = array(
      'iconType' => array('default' => 'marker'),
      'iconUrl' => array('default' => ''),
      'shadowUrl' => array('default' => ''),
      'iconSize' => array(
        'contains' => array(
          'x' => array('default' => ''),
          'y' => array('default' => ''),
        )),
      'iconAnchor' => array(
        'contains' => array(
          'x' => array('default' => ''),
          'y' => array('default' => ''),
        )),
      'shadowAnchor' => array(
        'contains' => array(
          'x' => array('default' => ''),
          'y' => array('default' => ''),
        )),
      'popupAnchor' => array(
        'contains' => array(
          'x' => array('default' => ''),
          'y' => array('default' => ''),
        )),
      'html' => array('default' => ''),
      'iconImageStyle' => array('default' => ''),
      'htmlClass' => array('default' => ''),
    );
    $options['vector_display']['contains'] = array(
      'stroke_override' => array('default' => 0),
      'stroke' => array('default' => 1),
      'color' => array('default' => ''),
      'weight' => array('default' => ''),
      'opacity' => array('default' => ''),
      'dashArray' => array('default' => ''),
      'fill' => array('default' => 1),
      'fillColor' => array('default' => ''),
      'fillOpacity' => array('default' => ''),
      'clickable' => array('default' => 1),
    );
    return $options;
  }

  /**
   * Options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Get list of fields in this view & flag available geodata fields:
    $handlers = $this->display->handler->get_handlers('field');

    $fields = array();
    $fields_data = array();
    foreach ($handlers as $field_id => $handler) {
      $fields[$field_id] = $handler->ui_name();

      if (!empty($handler->field_info['type']) && $handler->field_info['type'] == 'geofield') {
        $fields_data[$field_id] = $handler->ui_name();
      }
    }

    // Check whether we have a geofield we can work with:
    if (!count($fields_data)) {
      $form['error'] = array(
        '#markup' => t('Please add at least one geofield to the view'),
      );
      return;
    }

    // Get available entity types for selection.
    $default_type = empty($this->options['entity_type']) ? '' : $this->options['entity_type'];
    $entity_types = array('');
    foreach (entity_get_info() as $key => $info) {
      $entity_types[$key] = $info['label'];
      if ($this->view->base_table == $info['base table']) {
        // If this entity type matches the view base table, use it.
        $default_type = $key;
      }
    }

    // Entity type selection.
    $form['entity_type'] = array(
      '#type' => 'select',
      '#title' => t('Entity Type'),
      '#description' => t('Which type of entity is this view based on?'),
      '#options' => $entity_types,
      '#default_value' => $default_type,
      '#required' => TRUE,
    );

    // Only allow users to choose the entity type if it cannot be detected.
    if (!empty($default_type)) {
      $form['entity_type']['#access'] = FALSE;
    }

    // Map preset.
    $form['data_source'] = array(
      '#type' => 'select',
      '#title' => t('Data Source'),
      '#description' => t('Which field contains geodata?'),
      '#options' => $fields_data,
      '#default_value' => $this->options['data_source'],
      '#required' => TRUE,
    );

    // Name field.
    $form['name_field'] = array(
      '#type' => 'select',
      '#title' => t('Title Field'),
      '#description' => t('Choose the field which will appear as a title on tooltips.'),
      // '#options' => $fields,
      '#options' => array_merge(array('' => ''), $fields),
      '#default_value' => $this->options['name_field'],
    );

    $desc_options = array_merge(array(
        '' => '',
    ), $fields);

    // Add an option to render the entire entity using a view mode.
    if (isset($this->entity_type)) {
      $desc_options += array(
        '#rendered_entity' => '<' . t('!entity entity', array('!entity' => $this->entity_type)) . '>',
      );
    }

    $form['description_field'] = array(
      '#type' => 'select',
      '#title' => t('Description Content'),
      '#description' => t('Choose the field or rendering method which will appear as a description on tooltips or popups.'),
      '#required' => FALSE,
      '#options' => $desc_options,
      '#default_value' => $this->options['description_field'],
    );

    // Taken from openlayers_views_style_data::options_form().
    // Create view mode options:
    if (isset($this->entity_type)) {

      // Get the labels (human readable) of the view modes:
      $view_mode_options = array();
      foreach ($this->entity_info['view modes'] as $key => $view_mode) {
        $view_mode_options[$key] = $view_mode['label'];
      }

      // Output the form:
      $form['view_mode'] = array(
        '#type' => 'select',
        '#title' => t('View mode'),
        '#description' => t('View modes are ways of displaying entities.'),
        '#options' => $view_mode_options,
        '#default_value' => !empty($this->options['view_mode']) ? $this->options['view_mode'] : 'full',
        '#states' => array(
          'visible' => array(
            ':input[name="style_options[description_field]"]' => array('value' => '#rendered_entity'),
          ),
        ),
      );
    }

    // Choose a map preset:
    $map_options = array();
    foreach (leaflet_map_get_info() as $key => $map) {
      $map_options[$key] = t('@label', array('@label' => $map['label']));
    }

    $form['map'] = array(
      '#title' => t('Map'),
      '#type' => 'select',
      '#options' => $map_options,
      '#default_value' => $this->options['map'] ? $this->options['map'] : '',
      '#required' => TRUE,
    );

    $form['height'] = array(
      '#title' => t('Map height'),
      '#type' => 'textfield',
      '#field_suffix' => t('px'),
      '#size' => 4,
      '#default_value' => $this->options['height'],
      '#required' => FALSE,
    );

    $form['hide_empty'] = array(
      '#title' => t('Hide empty'),
      '#type' => 'checkbox',
      '#description' => t('Hide the Leaflet map if there are no results to display.'),
      '#default_value' => isset($this->options['hide_empty']) ? $this->options['hide_empty'] : TRUE,
    );

    $form['zoom'] = leaflet_form_elements('zoom', $this->options);
    $form['icon'] = leaflet_form_elements('icon', $this->options, array('path' => 'style_options', 'fields' => $fields));
    $form['vector_display'] = leaflet_form_elements('vector_display', $this->options, array('path' => 'style_options'));
    $form['tokens'] = leaflet_form_elements('tokens', $this->options, array('weight' => 998, 'entity_type' => $this->entity_type));
  }

  /**
   * Validate the options form.
   */
  function options_validate(&$form, &$form_state) {
    if (!is_numeric($form_state['values']['style_options']['height']) || $form_state['values']['style_options']['height'] < 0) {
      form_error($form['height'], t('Map height needs to be a positive number'));
    }
  }

  /**
   * Renders view.
   */
  function render() {
    if (!empty($this->view->live_preview)) {
      return t('No preview available.');
    }
    $data = array();
    $map = leaflet_map_get_info($this->options['map']);
    // Is there a geofield selected?
    if ($this->options['data_source']) {
      $name_field = empty($this->options['name_field']) ? NULL : $this->options['name_field'];
      $this->render_fields($this->view->result);
      foreach ($this->view->result as $id => $result) {
        $geofield = $this->get_field_value($id, $this->options['data_source']);

        if (!empty($geofield)) {
          $entity = FALSE;
          // Render the entity with the selected view mode:
          if (is_object($result)) {
            if (!empty($result->{$this->entity_info['entity keys']['id']})) {
              $entity_id = $result->{$this->entity_info['entity keys']['id']};
            }
            elseif ($result->entity) {
              $entity_id = $result->entity;
            }
            $entity = entity_load_single($this->entity_type, $entity_id);
            if ($this->options['description_field'] === '#rendered_entity') {
              $build = entity_view($this->entity_type, array($entity), $this->options['view_mode']);
              $description = drupal_render($build);
            }
            // Normal rendering via fields:
            else {
              $description = '';
              if ($name_field) {
                $description = $this->rendered_fields[$id][$name_field];
              }
              if ($this->options['description_field']) {
                $description .= $this->rendered_fields[$id][$this->options['description_field']];
              }
            }
          }
          $points = leaflet_process_geofield($geofield);
          // Attach pop-ups if we have rendered into $description:
          if (isset($description)) {
            foreach ($points as &$point) {
              $point['popup'] = $description;
            }
          }
          // Attach also titles & entities, they might be used later on.
          if ($name_field) {
            foreach ($points as &$point) {
              if (isset($this->rendered_fields[$id][$name_field])) {
                $point['label'] = htmlspecialchars_decode(strip_tags($this->rendered_fields[$id][$name_field]));
              }
              if ($entity !== FALSE) {
                $point['entity'] = $entity;
              }
            }
          }
          if ($this->options['icon']['iconType'] == 'html') {
            foreach ($points as &$point) {
              $target_field = $this->options['icon']['html'];
              $point['rendered_html'] = isset($this->rendered_fields[$id][$target_field]) ? $this->rendered_fields[$id][$target_field] : '';
            }
          }
          // Let modules modify the points data.
          drupal_alter('leaflet_views_alter_points_data', $result, $points);
          // Merge these points into the $data array for map rendering:
          $data = array_merge($data, $points);
        }
      }
      $entity_type = isset($this->entity_type) ? $this->entity_type : '';
      leaflet_apply_map_settings($map, $data, $this->options, $entity_type);
      if (empty($data) && !empty($this->options['hide_empty'])) {
        return;
      }
      return leaflet_build_map($map, $data, $this->options['height'] . 'px');
    }
    return;
  }
}
