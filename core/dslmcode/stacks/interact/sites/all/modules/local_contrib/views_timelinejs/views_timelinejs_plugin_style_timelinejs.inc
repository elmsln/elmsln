<?php
/**
 * @file
 * Views Style.
 */

/**
 * Unformatted style plugin.
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  /**
   * Define option defaults.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['timeline_theme']['width'] = array('default' => '100');
    $options['timeline_theme']['width_unit'] = array('default' => '1');
    $options['timeline_theme']['height'] = array('default' => '500');
    $options['timeline_theme']['height_unit'] = array('default' => '0');
    $options['timeline_fields']['caption'] = array('default' => '0');
    $options['timeline_fields']['credit'] = array('default' => '0');
    $options['timeline_fields']['media'] = array('default' => '0');
    $options['timeline_fields']['tag'] = array('default' => '0');
    $options['timeline_fields']['date'] = array('default' => '0');
    $options['timeline_fields']['bodytext'] = array('default' => '0');
    $options['timeline_fields']['headline'] = array('default' => '0');
    $options['timeline_config']['hash_bookmark'] = array('default' => '0');
    $options['timeline_config']['start_zoom_adjust'] = array('default' => '0');
    $options['timeline_config']['link_text'] = array('default' => 'Read more');
    $options['timeline_config']['link_text_enabled'] = array('default' => '0');
    $options['timeline_config']['link_to_entity'] = array('default' => '0');

    return $options;
  }

  /**
   * Define options form.
   */
  function options_form(&$form, &$form_state) {

    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#prefix' => '<div class="error messages">',
        '#markup' => t('You need at least one field before you can configure TimelineJS.'),
        '#suffix' => '</div>',
      );
      return;
    }

    $media_fields = array('0' => t('None'));
    $date_fields = array('0' => t('None'));
    $text_fields = array('0' => t('None'));
    $tag_fields = array('0' => t('None'));

    // Load all date_source plugins.
    ctools_include('plugins');
    $date_sources = ctools_get_plugins('views_timelinejs', 'date_sources');
    $text_sources = ctools_get_plugins('views_timelinejs', 'text_sources');
    $media_sources = ctools_get_plugins('views_timelinejs', 'media_sources');
    $tag_sources = ctools_get_plugins('views_timelinejs', 'tag_sources');

    // Go through all the field handlers to check support.
    foreach ($handlers as $field => $handler) {
      // Get a nice name for the field.
      $field_names[$field] = $handler->ui_name();
      if ($label = $handler->label()) {
        $field_names[$field] .= ' ("' . $label . '")';
      }

      if (isset($handler->definition['field_name'])) {
        $field_name = $handler->definition['field_name'];
        $field_info = field_info_field($field_name);
      }

      // Check if field is supported as a date source.
      foreach ($date_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if ($field_info['type'] == $source['field_type'] || $field == 'created' || $field == 'changed') {
            $date_fields[$field] = $field_names[$field];
          }
        }
      }

      // Check if field is a supported text source.
      foreach ($text_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if ((isset($field_info['type']) && $field_info['type'] == $source['field_type']) || $field == 'title') {
            $text_fields[$field] = $field_names[$field];
          }
        }
      }

      // Check if field is a supported media source.
      foreach ($media_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if (isset($field_info['type']) && $field_info['type'] == $source['field_type']) {
            $media_fields[$field] = $field_names[$field];
          }
        }
      }

      // Check if field is a supported tag source.
      foreach ($tag_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if (isset($field_info['type']) && $field_info['type'] == $source['field_type']) {
            $tag_fields[$field] = $field_names[$field];
          }
        }
      }
    }

    // Timeline general configuration.
    $form['timeline_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('General configuration'),
      '#description' => t('Settings for how the Timeline will behave.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_config']['link_to_entity'] = array(
      '#type' => 'checkbox',
      '#title' => 'Link timeline items to entity',
      '#description' => t('If checked, headlines will be made links to entity.'),
      '#default_value' => $this->options['timeline_config']['link_to_entity'],
    );
    $form['timeline_config']['link_text_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => 'Add a link to entity after bodytext',
      '#description' => t('Append a link to original entity to the end of the bodytext.'),
      '#default_value' => $this->options['timeline_config']['link_text_enabled'],
    );
    $form['timeline_config']['link_text'] = array(
      '#type' => 'textfield',
      '#title' => 'Link text',
      '#description' => t('Text that will be used in the link to entity'),
      '#default_value' => $this->options['timeline_config']['link_text'],
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[timeline_config][link_to_entity]"]' => array('value' => 1),
        ),
      ),
    );
    $form['timeline_config']['hash_bookmark'] = array(
      '#type' => 'select',
      '#title' => 'Hash Bookmarks',
      '#description' => t('On each slide, a # will be added to the end of the url in the url bar. These urls are bookmarkable, so you can share or return to the same place in the timeline later.'),
      '#options' => array(
        '0' => t('No'),
        '1' => t('Yes'),
      ),
      '#default_value' => $this->options['timeline_config']['hash_bookmark'],
    );
    $form['timeline_config']['start_at_end'] = array(
      '#type' => 'select',
      '#title' => 'Start at the end',
      '#description' => t('The most recent event will be shown first.'),
      '#options' => array(
        '0' => t('No'),
        '1' => t('Yes'),
      ),
      '#default_value' => $this->options['timeline_config']['start_at_end'],
    );
    $form['timeline_config']['start_zoom_adjust'] = array(
      '#type' => 'select',
      '#title' => 'Zoom Level',
      '#description' => t('Set the default zoom level.'),
      '#options' => array(
        '0' => t('0'),
        '1' => t('1'),
        '2' => t('2'),
        '3' => t('3'),
        '4' => t('4'),
        '5' => t('5'),
        '6' => t('6'),
        '7' => t('7'),
        '8' => t('8'),
        '9' => t('9'),
      ),
      '#default_value' => $this->options['timeline_config']['start_zoom_adjust'],
    );

    // Field mapping.
    $form['timeline_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field mappings'),
      '#description' => t('Fields used to construct the timeline events.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_fields']['headline'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => t('Headline'),
      '#required' => TRUE,
      '#description' => t('Plain text; a high level summary.'),
      '#default_value' => $this->options['timeline_fields']['headline'],
    );
    $form['timeline_fields']['bodytext'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => t('Body text'),
      '#description' => t('Plain text; a paragraph or two of optional details.'),
      '#default_value' => $this->options['timeline_fields']['bodytext'],
    );
    $form['timeline_fields']['date'] = array(
      '#type' => 'select',
      '#options' => $date_fields,
      '#title' => t('Start and End date'),
      '#required' => TRUE,
      '#description' => t('Required start and optional end of an event; can be a date field or timestamp.'),
      '#default_value' => $this->options['timeline_fields']['date'],
    );
    $form['timeline_fields']['media'] = array(
      '#type' => 'select',
      '#options' => $media_fields,
      '#title' => t('Media URL'),
      '#description' => t('Drupal core image fields and link fields are supported; must contain a raw URL to an image or video.'),
      '#default_value' => $this->options['timeline_fields']['media'],
    );
    $form['timeline_fields']['credit'] = array(
      '#type' => 'select',
      '#title' => t('Media Credit'),
      '#description' => t('Byline naming the author or attributing the source.'),
      '#options' => $text_fields,
      '#default_value' => $this->options['timeline_fields']['credit'],
    );
    $form['timeline_fields']['caption'] = array(
      '#type' => 'select',
      '#title' => t('Media Caption'),
      '#description' => t('Brief explanation of the media content.'),
      '#options' => $text_fields,
      '#default_value' => $this->options['timeline_fields']['caption'],
    );
    $form['timeline_fields']['tag'] = array(
      '#type' => 'select',
      '#options' => $tag_fields,
      '#title' => t('Tag'),
      '#description' => t('Content tagging; maximum of 6 tags.'),
      '#default_value' => $this->options['timeline_fields']['tag'],
    );

    // Timeline display configuration.
    $units = array(0 => 'px', 1 => '%');
    $form['timeline_theme'] = array(
      '#type' => 'fieldset',
      '#title' => t('Display configuration'),
      '#description' => t('Settings for how the Timeline will look.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_theme']['width'] = array(
      '#type' => 'textfield',
      '#title' => 'Width of the timeline',
      '#description' => t('The width of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['width'],
    );
    $form['timeline_theme']['width_unit'] = array(
      '#type' => 'radios',
      '#title' => t('Units for the width'),
      '#description' => t('Choose which units will be used to define the width of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['width_unit'],
      '#options' => $units,
    );
    $form['timeline_theme']['height'] = array(
      '#type' => 'textfield',
      '#title' => 'Height of the timeline',
      '#description' => t('The height of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['height'],
    );
    $form['timeline_theme']['height_unit'] = array(
      '#type' => 'radios',
      '#title' => t('Units for the height'),
      '#description' => t('Choose which units will be used to define the height of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['height_unit'],
      '#options' => $units,
    );
  }

  /**
   * Render the display.
   */
  function render() {
    $view = $this->view;

    // Render fields to trigger rewriting and other field processing.
    $this->view->style_plugin->render_fields($this->view->result);

    $field_mapping = array(
      'startDate' => 'date',
      'endDate' => 'date',
      'headline' => 'headline',
      'text' => 'bodytext',
      'media' => 'media',
      'caption' => 'caption',
      'credit' => 'credit',
      'tag' => 'tag',
    );

    // Determine if required fields are mapped.
    $required_mappings = array(
      'date',
      'headline',
    );

    $has_required_mappings = TRUE;
    foreach ($required_mappings as $field_name) {
      if (!$this->getDefinedUsage($field_name)) {
        $has_required_mappings = FALSE;
      }
    }

    // Render if there's enough mapped fields.
    if ($has_required_mappings) {
      $link_text = isset($this->options['timeline_config']['link_text']) ? $this->options['timeline_config']['link_text'] : t('Read more');
      $rows = array();

      // Build a TimelineJS friendly array from the views data.
      foreach ($this->view->result as $count => $row) {
        $data = array();
        $data['asset'] = array();
        // Build the data we need.
        foreach ($field_mapping as $target_field => $source_field) {
          $tmp = $this->getDefinedUsage($source_field);
          // Don't render fields that haven't been mapped.
          if (!isset($view->field[$tmp['fieldname']])) {
            continue;
          }

          // Headline - plain text input, optional link to entity.
          if ($target_field == 'headline') {
            $v_text = $view->field[$tmp['fieldname']]->get_value($row);
            if (is_array($v_text)) {
              $v_text = array_shift($v_text);
            }
            if (!is_string($v_text)) {
              $v_text = $v_text['value'];
            }
            if ($this->options['timeline_config']['link_to_entity'] && $view->base_table == 'node' && isset($row->_field_data[$view->base_field]['entity'])) {
              $row->uri = entity_uri($row->_field_data[$view->base_field]['entity_type'], $row->_field_data[$view->base_field]['entity']);
              $rows[$count][$target_field] = str_replace('&#039;', '&apos;', l($v_text, $row->uri['path']));
            }
            else {
              $rows[$count][$target_field] = check_plain($v_text);
            }
          }

          // Body - plain text input, optionally append "read more" entity link.
          if ($target_field == 'text') {
            $v_text = strip_tags($view->style_plugin->rendered_fields[$count][$this->options['timeline_fields'][$source_field]]);
            if ($v_text) {
              $rows[$count][$target_field] = $v_text;
              if (isset($this->options['timeline_config']['link_text_enabled']) && $this->options['timeline_config']['link_text_enabled'] && isset($row->uri['path'])) {
                $rows[$count][$target_field] .= theme('views_timelinejs_link_to_entity',
                  array(
                    'uri' => $row->uri['path'],
                    'link_text' => check_plain($link_text),
                  )
                );
              }
            }
          }

          // Tag.
          if ($target_field == 'tag') {
            $value = '';
            // Check if if a tag exists.
            if (isset($view->field[$tmp['fieldname']])) {
              $value = $view->field[$tmp['fieldname']]->get_value($row);
              if (is_array($value)) {
                $value = array_shift($value);
              }

              if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'tag_sources')) {
                $value = call_user_func($conversion_callback, $value, array(
                  'field' => $tmp,
                ));
              }
            }
            $rows[$count][$target_field] = check_plain($value);
          }

          // Start and End date.
          if (in_array($target_field, array('startDate', 'endDate'))) {
            $date = array();
            // Load field data.
            $value = $view->field[$tmp['fieldname']]->get_value($row);
            // If it's a date field, we have an array.
            if (is_array($value)) {
              $value = array_shift($value);
            }

            // Make sure created and changed fields work as date sources.
            if ($tmp['fieldname'] == 'created' || $tmp['fieldname'] == 'changed') {
              $tmp['field_type'] = 'date';
            }

            if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'date_sources')) {
              $date['formatted'] = call_user_func($conversion_callback, $value, 'csv', array('field' => $tmp));
              $date['timestamp'] = call_user_func($conversion_callback, $value, 'timestamp', array('field' => $tmp));
            }

            if (isset($date) && $date) {
              if (is_array($date['formatted'])) {
                if ($target_field == 'startDate') {
                  if ($date['formatted']['value'] != "FALSE") {
                    $rows[$count][$target_field] = check_plain($date['formatted']['value']);
                  } else {
                    drupal_set_message(t("Could not format date for field %field in node @nid. It won't be shown in timeline.", array('@nid' => $row->nid, '%field' => $tmp['fieldname'])), 'error');
                  }
                }
                elseif (($target_field == 'endDate') && isset($date['formatted']['value2'])) {
                  if ($date['formatted']['value'] != "FALSE") {
                    $rows[$count][$target_field] = check_plain($date['formatted']['value2']);
                  } else {
                    drupal_set_message(t("Could not format date for field %field in node @nid. It won't be shown in timeline.", array('@nid' => $row->nid, '%field' => $tmp['fieldname'])), 'error');
                  }
                }
              }
              else {
                $rows[$count][$target_field] = check_plain($date['formatted']);
              }
            }
          }

          // Media URL.
          if ($target_field == 'media') {
            $value = $view->field[$tmp['fieldname']]->get_value($row);
            if (is_array($value)) {
              $value = array_shift($value);
            }
            if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'media_sources')) {
              $media['formatted'] = call_user_func($conversion_callback, $value, array('field' => $tmp));
            }

            if ($media['formatted']) {
              $rows[$count]['asset'][$target_field] = check_plain($media['formatted']);
            }
          }

          // Media Caption, Media Credit - both plain text.
          if (in_array($target_field, array('caption', 'credit'))) {
            if ($tmp['handler'] != NULL) {
              $v_text = $view->field[$tmp['fieldname']]->get_value($row);
              if (is_array($v_text)) {
                $v_text = array_shift($v_text);
              }
              if (!is_string($v_text)) {
                $v_text = $v_text['value'];
              }
              if ($v_text) {
                $rows[$count]['asset'][$target_field] = check_plain($v_text);
              }
            }
          }
        }
      }

      // Allow other modules to alter timeline data before rendering by
      // implementing hook_views_timelinejs_data_alter().
      drupal_alter('views_timelinejs_data', $rows, clone $view);

      // Prepare data array that TimelineJS understands.
      $data = array(
        'timeline' => array(
          'headline' => 'Title',
          'type' => 'default',
          'date' => $rows,
        ),
      );
    }
    // Does not have required mapping.
    else {
      // Populate a fake timeline with instructions.
      $date = new DateTime();
      $data = array(
        'timeline' => array(
          'headline' => t('Insufficient field mapping'),
          'type' => 'default',
          'date' => array(
            array(
              'headline' => t('Please configure the field mapping by going to Format: TimelineJS - Settings.'),
              'startDate' => $date->format('Y,m,d,H,i'),
            ),
          ),
        ),
      );
    }

    // Skip rendering if view is being edited or previewed.
    if (!$view->editing) {
      return theme('views_timelinejs', array(
        'view' => $view,
        'options' => $this->options,
        'rows' => $data,
      ));
    }
    else {
      return '<pre>' . print_r($data, 1) . '</pre>';
    }
  }

  /**
   * Helper function to determine alias, handler, and fieldname of a given type.
   *
   * @param string $type
   *   The type to be parsed.
   *
   * @return array|boolean
   *   An array containing the keys/values for: alias, handler, fieldname,
   *   field_type, date_format, and tz_handling.
   */
  protected function getDefinedUsage($type) {
    $view = $this->view;

    // If it's not mapped at all, don't do anything.
    if (!isset($view->style_options['timeline_fields'])) {
      return FALSE;
    }

    if ($fields = $view->style_options['timeline_fields']) {
      $fieldname = '';
      if (isset($fields[$type])) {
        $fieldname = $fields[$type];
      }
      elseif (isset($fields['advanced'][$type])) {
        $fieldname = $fields['advanced'][$type];
      }

      if (isset($fieldname) && $fieldname != '0') {
        $field_information = array(
          'alias' => $view->field[$fieldname]->field_alias,
          'handler' => $view->field[$fieldname]->definition['handler'],
          'fieldname' => $fieldname,
        );
      }

      if (!empty($view->field[$fieldname]->field_info)) {
        $field_information['field_type'] = $view->field[$fieldname]->field_info['type'];
        $field_information['date_format'] = $field_information['field_type'];

        // If we're dealing with a date-field, get tz_handling and granularity as well.
        if (isset($view->field[$fieldname]->field_info['settings']['tz_handling'])) {
          $field_information['tz_handling'] = $view->field[$fieldname]->field_info['settings']['tz_handling'];
        }
        if (isset($view->field[$fieldname]->field_info['settings']['granularity'])) {
          $field_information['granularity'] = $view->field[$fieldname]->field_info['settings']['granularity'];
        }
      }

      if (!empty($field_information)) {
        return $field_information;
      }
      else {
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }
}
