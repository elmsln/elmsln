<?php

/**
 * @file
 * Display Suite module integration.
 */

/**
 * Implements hook_theme_registry_alter().
 *
 * Copied and modified from ds/includes/ds.registry.inc#263
 *
 * @param $theme_registry
 */
function custom_formatters_theme_registry_alter(&$theme_registry) {
  // Inject custom_formatters_ds_entity_variables in all entity theming functions.
  $entity_info = entity_get_info();
  foreach ($entity_info as $entity => $info) {
    if (isset($entity_info[$entity]['fieldable']) && $entity_info[$entity]['fieldable']) {

      // User uses user_profile for theming.
      if ($entity == 'user') {
        $entity = 'user_profile';
      }

      // Only add preprocess functions if entity exposes theme function.
      if (isset($theme_registry[$entity])) {
        $theme_registry[$entity]['preprocess functions'][] = 'custom_formatters_ds_entity_variables';
      }
    }
  }

  // Support for File Entity.
  if (isset($theme_registry['file_entity'])) {
    $theme_registry['file_entity']['preprocess functions'][] = 'custom_formatters_ds_entity_variables';
  }

  // Support for Entity API.
  if (isset($theme_registry['entity'])) {
    $theme_registry['entity']['preprocess functions'][] = 'custom_formatters_ds_entity_variables';
  }
}

/**
 * Implements hook_custom_formatters_fields_alter() on behalf of ds.module.
 *
 * @param $fields
 */
function ds_custom_formatters_fields_alter(&$fields) {
  foreach (array_keys(entity_get_info()) as $entity_type) {
    $ds_fields = module_invoke_all('ds_fields_info', $entity_type);
    if (is_array($ds_fields) && !empty($ds_fields)) {
      foreach ($ds_fields[$entity_type] as $id => $field) {
        if (in_array($field['field_type'], array(
          DS_FIELD_TYPE_PREPROCESS,
          DS_FIELD_TYPE_FUNCTION
        ))) {
          $fields['ds_' . $id] = array(
            'module' => 'ds',
            'label'  => $field['title'],
          );
        }
      }
    }
  }
}

/**
 * Implements hook_ds_fields_info_alter().
 *
 * @param $fields
 * @param $entity_type
 */
function custom_formatters_ds_fields_info_alter(&$fields, $entity_type) {
  $formatters = custom_formatters_crud_load_all();
  foreach ($formatters as $name => $formatter) {
    foreach (drupal_explode_tags($formatter->field_types) as $field_type) {
      if (strpos($field_type, 'ds_') === 0) {
        $field_type = substr($field_type, 3);
        if (isset($fields[$field_type])) {
          switch ($fields[$field_type]['field_type']) {
            case DS_FIELD_TYPE_PREPROCESS:
              if (!isset($fields[$field_type]['properties']['formatters'])) {
                $fields[$field_type]['properties']['formatters'] = array('default' => t('Default'));
              }
              $fields[$field_type]['properties']['formatters']['custom_formatters_' . $formatter->name] = $formatter->label;
              if (isset($formatter->fapi)) {
                ob_start();
                eval($formatter->fapi);
                ob_get_clean();

                if (isset($form)) {
                  foreach ($form as $form_key => $element) {
                    $fields[$field_type]['properties']['default'][$form_key]  = isset($element['#default_value']) ? $element['#default_value'] : '';
                    $fields[$field_type]['properties']['settings'][$form_key] = array(
                      'type'        => $element['#type'],
                      'description' => isset($element['#description']) ? $element['#description'] : '',
                      'options'     => isset($element['#options']) ? $element['#options'] : array(),
                    );
                  }
                }
              }
              break;

            case DS_FIELD_TYPE_FUNCTION:
              if (!isset($fields[$field_type]['#custom_formatters'])) {
                $fields[$field_type]['#original_field']    = $fields[$field_type];
                $fields[$field_type]['#custom_formatters'] = TRUE;
                $fields[$field_type]['function']           = 'custom_formatters_ds_render_field';
              }

              $fields[$field_type]['properties']['formatters']['custom_formatters_' . $formatter->name] = $formatter->label;
              break;
          }
        }
      }
    }
  }
}

/**
 * Format variables on an entity.
 *
 * Copied and modified from ds.module#588
 *
 * @param $vars
 */
function custom_formatters_ds_entity_variables(&$vars) {
  if (isset($vars['elements']) && isset($vars['elements']['#bundle']) && $layout = ds_get_layout($vars['elements']['#entity_type'], $vars['elements']['#bundle'], $vars['elements']['#view_mode'])) {

    $render_container = 'content';
    // User uses user_profile as container.
    if ($vars['elements']['#entity_type'] == 'user') {
      $render_container = 'user_profile';
    }

    // Move any preprocess fields to render container.
    // Inconsitency in taxonomy term naming.
    $object = $vars['elements']['#entity_type'];
    if ($vars['elements']['#entity_type'] == 'taxonomy_term') {
      $object = 'term';
    }

    if (isset($vars[$object]->preprocess_fields)) {
      $fields       = ds_get_fields($object);
      $field_values = ds_get_field_settings($object, $vars['elements']['#bundle'], $layout['view_mode']);
      foreach ($vars[$object]->preprocess_fields as $field) {
        if (isset($field_values[$field]['format']) && strpos($field_values[$field]['format'], 'custom_formatters_') === 0) {

          $field_settings = ds_get_field_settings($vars['elements']['#entity_type'], $vars['elements']['#bundle'], $vars['elements']['#view_mode']);
          $display        = array(
            'type'     => $field_values[$field]['format'],
            'settings' => isset($field_settings[$field]['formatter_settings']) ? $field_settings[$field]['formatter_settings'] : array(),
          );
          $items          = array($vars[$field]);
          $element        = custom_formatters_field_formatter_view($object, $vars[$object], $fields[$field], array(), language_default('language'), $items, $display);
          $vars[$field]   = render($element);
        }
      }
    }
  }
}

/**
 * Display Suite render function for Custom Formatters integration.
 *
 * @param $field
 *
 * @return string
 */
function custom_formatters_ds_render_field($field) {
  if (strpos($field['formatter'], 'custom_formatters_') === 0) {
    $display = array('type' => $field['formatter']);
    foreach (array_keys($field['properties']['formatters']) as $formatter) {
      if (strpos($formatter, 'custom_formatters_') !== 0) {
        $temp_field              = $field;
        $temp_field['formatter'] = $formatter;
        $items[$formatter]       = $field['#original_field']['function']($temp_field);
      }
    }
    $element = custom_formatters_field_formatter_view($field['entity_type'], $field['entity'], $field, array(), language_default('language'), $items, $display);

    return render($element);
  }

  // Pass field back to it's original function.
  return $field['#original_field']['function']($field);
}

/**
 * Implements hook_custom_formatters_form_ctools_export_ui_edit_item_form_alter_alter()
 * on behalf of ds.module.
 *
 * @param $form
 * @param $form_state
 */
function ds_custom_formatters_form_ctools_export_ui_edit_item_form_alter_alter(&$form, $form_state) {
  if (!empty($form['engine']['preview']['bundle']['#options'])) {
    $entity_type = $form['engine']['preview']['entity_type']['#default_value'];
    $bundle      = key($form['engine']['preview']['bundle']['#options']);
    $field_types = $form['engine']['field_types']['#default_value'];
    if (isset($form_state['values'])) {
      $entity_type = $form_state['values']['preview']['entity_type'];
      $bundle      = $form_state['values']['preview']['bundle'];
      $field_types = $form_state['values']['field_types'];
    }
    $field_types = drupal_explode_tags($field_types);

    $ds_fields = module_invoke_all('ds_fields_info', $entity_type);
    foreach ($ds_fields[$entity_type] as $name => $field) {
      if ($field['field_type'] == DS_FIELD_TYPE_FUNCTION && in_array('ds_' . $name, $field_types)) {
        $form['engine']['preview']['field']['#options'][$name] = $field['title'];
        $form['engine']['preview']['field']['#disabled']       = FALSE;
      }
    }
    ksort($form['engine']['preview']['field']['#options']);

    $field = key($form['engine']['preview']['field']['#options']);
    if (isset($form_state['values']) && isset($form_state['values']['preview']['field'])) {
      $field = $form_state['values']['preview']['field'];
    }

    if (in_array($field, array_keys($ds_fields[$entity_type]))) {
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', $entity_type)
        ->entityCondition('bundle', $bundle)
        ->addTag('random')
        ->range(0, 50);
      $result = $query->execute();
      if (!empty($result)) {
        $entities = entity_load($entity_type, array_keys($result[$entity_type]));
        foreach ($entities as $key => $entity) {
          $form['engine']['preview']['entity']['#options'][$key] = entity_label($entity_type, $entity) . " [eid:{$key}]";
        }
      }
      $form['engine']['preview']['entity']['#disabled'] = FALSE;
      $form['engine']['preview']['button']['#disabled'] = FALSE;
    }
  }
}

/**
 * Implements hook_custom_formatters_preview_elements_alter() on behalf of
 * ds.module.
 *
 * @param $elements
 * @param $values
 */
function ds_custom_formatters_preview_elements_alter(&$elements, $values) {
  $ds_fields = ds_get_fields($elements['obj_type']);
  if (in_array($values['preview']['field'], array_keys($ds_fields))) {
    $elements['field']                = $ds_fields[$values['preview']['field']];
    $elements['field']['field_name']  = $values['preview']['field'];
    $elements['field']['entity']      = $elements['object'];
    $elements['field']['entity_type'] = $elements['obj_type'];
    $elements['field']['bundle']      = $values['preview']['bundle'];
    $elements['field']['view_mode']   = 'full';
    $elements['field']['build']       = array();

    $elements['instance'] = array();
    $elements['langcode'] = language_default('language');

    foreach (array_keys($elements['field']['properties']['formatters']) as $formatter) {
      if (strpos($formatter, 'custom_formatters_') !== 0) {
        $temp_field                    = $elements['field'];
        $temp_field['formatter']       = $formatter;
        $elements['items'][$formatter] = $elements['field']['#original_field']['function']($temp_field);
      }
    }

    $elements['display'] = array();
  }
}
