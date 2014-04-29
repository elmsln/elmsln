<?php

/**
 * Implements hook_field_info()
 */
function radioactivity_field_info() {
  return array(
    RADIOACTIVITY_FIELD_TYPE => array(
      'label' => t('Radioactivity'),
      'description' => t('This field stores radioactivity in the database.'),
      'settings' => array(
      ),
      'instance_settings' => array(
        'profile' => 'default',
        'history' => 0,
        'history_limit' => 8,
      ),
      'default_widget' => RADIOACTIVITY_BASIC_WIDGET,
      'default_formatter' => RADIOACTIVITY_COMBO_FORMATTER,
      'property_type' => 'decimal',
      'microdata' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_instance_settings_form()
 */
function radioactivity_field_instance_settings_form($field, $instance) {
  $settings = $instance['settings'];

  $form = array();

  if ($field['type'] == RADIOACTIVITY_FIELD_TYPE) {

    $profiles = radioactivity_get_decay_profile_options_list();

    $form['profile'] = array(
      '#type' => 'select',
      '#title' => t('Decay profile'),
      '#default_value' => $settings['profile'],
      '#required' => TRUE,
      '#description' => t('Select the decay profile for this instance. You can create and edit decay profiles !here.', array(
          "!here" => l("here", "admin/structure/radioactivity/profiles"),
        )
      ),
      '#options' => $profiles,
    );

    $form['history'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable history'),
      '#default_value' => isset($settings['history']) ? $settings['history'] : 0,
      '#description' => t('Enable history tracking for this field instance. You can view the history on the edit page or by changing the fields display type.'),
    );

    $form['history_limit'] = array(
      '#type' => 'textfield',
      '#title' => t('History limit'),
      '#default_value' => isset($settings['history_limit']) ? $settings['history_limit'] : 8,
      '#description' => t('For how many hours do you want to store the data for?'),
    );

    if (isset($profiles['none'])) {
      $form['profile']['#disabled'] = TRUE;
      $form['profile']['#description'] = t(
        'It seems that you have not created any profiles yet. You can create and edit decay profiles !here.',
        array(
          "!here" => l("here", "admin/structure/radioactivity/profiles"),
        )
      );
    }
  }

  return $form;
}

/**
 * Implements hook_field_widget_info().
 */
function radioactivity_field_widget_info() {
  return array(
    RADIOACTIVITY_BASIC_WIDGET => array(
      'label' => t('Default text field'),
      'field types' => array(RADIOACTIVITY_FIELD_TYPE),
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function radioactivity_field_formatter_info() {
  return array(
    RADIOACTIVITY_COMBO_FORMATTER => array(
      'label' => t('Radioactivity combo emitter + display'),
      'field types' => array(RADIOACTIVITY_FIELD_TYPE),
      'settings' => array(
        'energy' => 10,
        'type' => 'none',
        'accuracy' => '100',
      ),
    ),
  );
}

function _radioactivity_register_emitter($storage = NULL, $entity_type = NULL, $bundle = NULL, $field_name = NULL, $language = NULL, $entity_id = NULL, $settings = NULL) {
  static $cache = array();
  if ($storage == NULL) {
    return $cache;
  } else if ($storage == 'RESET') {
    $cache = array();
    return;
  }

  $incident = $settings + array(
    'storage'     => $storage,
    'entity_type' => $entity_type,
    'bundle'      => $bundle,
    'field_name'  => $field_name,
    'language'    => $language,
    'entity_id'   => $entity_id,
  );
  @$cache['emitDefault'][] = _radioactivity_prepare_incident($incident);
}

/**
 * Implements hook_field_formatter_view()
 */
function radioactivity_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {

  $element = array();

  switch ($display['type']) {
    case RADIOACTIVITY_COMBO_FORMATTER:

      $entity_id = 0;

      $info = entity_get_info($entity_type);

      $id = $info['entity keys']['id'];

      $entity_id = $entity->{$id};

      $language = LANGUAGE_NONE;
      if ($field['translatable']) {
        $language = field_language($entity_type, $entity, $field['field_name']);
      }

      if ($entity_id > 0) {
        $settings = $display['settings'];
        if ($settings['energy'] != 0) {

          $profile = radioactivity_get_field_profile($entity_type, $instance['bundle'], $field['field_name']);
          if ($profile && $profile->storageObject) {
            _radioactivity_register_emitter($profile->storage, $entity_type, $instance['bundle'], $field['field_name'], $language, $entity_id, $settings);
          }
          else {
            watchdog(
              "radioactivity",
              "Storage for field @field not found for @bundle. Please change it in the field configuration.",
              array("@field" => $field['field_name'], "@bundle" => $instance['bundle']),
              WATCHDOG_ERROR
            );
          }
        }
      }

      drupal_add_css(drupal_get_path('module', 'radioactivity') . '/css/radioactivity.css');

      if (isset($settings['type'])) {
        switch ($settings['type']) {

          case 'none':
            break;

          case 'energy':
            foreach ($items as $delta => $item) {
              $element[$delta] = array(
                '#markup' => $item[RADIOACTIVITY_FIELD_ENERGY],
              );
            }
            break;

          case 'popularity':
            $maximum = ceil(_radioactivity_get_field_maximum($field['id'], $entity_type));
            $maximum = $maximum == 0 ? 1 : $maximum;
            foreach ($items as $delta => $item) {
              $energy          = $item[RADIOACTIVITY_FIELD_ENERGY];
              $element[$delta] = array(
                '#markup' => round(($energy / $maximum) * 100),
              );
            }
            break;

          case 'gauge':
            $maximum = ceil(_radioactivity_get_field_maximum($field['id'], $entity_type));
            $maximum = $maximum == 0 ? 1 : $maximum;
            foreach ($items as $delta => $item) {
              $energy          = $item[RADIOACTIVITY_FIELD_ENERGY];
              $element[$delta] = array(
                '#theme' => 'radioactivity_gauge',
                '#maximum' => $maximum,
                '#energy' => $energy,
              );
            }
            break;

          case 'history':
            $data = _radioactivity_get_history_for_field_and_entity($instance['id'], $entity_id);
            foreach ($items as $delta => $item) {
              $energy          = $item[RADIOACTIVITY_FIELD_ENERGY];
              $element[$delta] = array(
                '#theme' => 'radioactivity_history',
                '#dataset' => $data,
              );
            }
            break;
        }
      }
    break; // case RADIOACTIVITY_COMBO_FORMATTER:
  }

  return $element;
}

/**
 * Implements hook_field_instance_settings_form().
 */
function radioactivity_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {

  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $form = array();

  if ($field['type'] == RADIOACTIVITY_FIELD_TYPE) {

    switch ($display['type']) {
      case RADIOACTIVITY_COMBO_FORMATTER:

        $form['energy'] = array(
          '#type' => 'textfield',
          '#title' => t('View incident energy'),
          '#default_value' => $settings['energy'],
          '#required' => TRUE,
          '#description' => t('Defines the energy emitted by viewing this field. Set to 0 to disable emit.'),
          '#element_validate' => array('_element_validate_number'),
        );

        $form['type'] = array(
          '#type' => 'select',
          '#title' => t('Type'),
          '#default_value' => $settings['type'],
          '#options' => radioactivity_combo_field_types(),
          '#required' => TRUE,
        );

        $form['accuracy'] = array(
          '#type' => 'textfield',
          '#title' => t('Accuracy'),
          '#default_value' => $settings['accuracy'],
          '#required' => TRUE,
          '#element_validate' => array('_element_validate_number'),
          '#description' => t('Value from 1 to 100 describing the statistic accuracy of this emitter. If value of 80 is given then 80% of field views trigger an emit. Actual energy of this emitter is then corrected by shifting the amount of energy emitted e.g. if incident energy is 10 and accuracy 80, the actual amount of energy emitted per view is 10 / 80 * 100.'),
        );

        break;
    }
  }

  return $form;
}

/**
 * Get radioactivity widget formatter types
 */
function radioactivity_combo_field_types() {
  return array(
    'none' => t('Do not display energy'),
    'energy' => t('Raw numeric value'),
    'popularity' => t('Percentage'),
    'gauge' => t('Hotness gauge'),
    'history' => t('History'),
  );
}

/**
 * Implementation of hook_form_alter().
 */
function radioactivity_form_field_ui_field_edit_form_alter(&$form, &$form_state, $form_id) {
  if ($form['#field']['type'] == 'radioactivity') {
    // Hide the 'required' and 'multi value' field settings
    $form['field']['#access'] = FALSE;
    $form['instance']['required']['#access'] = FALSE;
  }
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function radioactivity_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $types = radioactivity_combo_field_types();

  if ($settings['type'] != 'none') {
    $summary = t('Energy display: @type.', array("@type" => $types[$settings['type']]));
  }
  else {
    $summary = t('Energy display is disabled.');
  }

  if ($settings['energy'] != 0) {
    $summary .= ' '  . t('Emit @energy when visible.', array(
        '@energy' => $settings['energy'],
      ));
  }
  else {
    $summary .= ' '  . t('Emitter is disabled');
  }

  $summary .= ' ' .t('Accuracy is @accu.', array('@accu' => $settings['accuracy']));

  return $summary;
}

/**
 * Implements hook_page_alter()
 */
function radioactivity_page_alter($page) {
  radioactivity_update_emitters();
}

/**
 * Update emitters on page
 */
function radioactivity_update_emitters() {

  // foreach emitters emitter->emit();
  $register = _radioactivity_register_emitter();
  module_load_include("inc", "radioactivity", "radioactivity-bootstrap");
  $path = base_path() . drupal_get_path('module', 'radioactivity') . '/emit.php';

  $config = array(
    'emitPath' => $path,
    'fpEnabled' => variable_get('radioactivity_flood_protection', FALSE),
    'fpTimeout' => variable_get('radioactivity_flood_timeout', 15),
  );

  if (count($register) > 0) {
    drupal_add_library('system', 'jquery.cookie');
    drupal_add_js(drupal_get_path('module', 'radioactivity') . '/js/radioactivity.js');
    drupal_add_js(array('radioactivity' => array('emitters' => $register)), 'setting');
    drupal_add_js(array('radioactivity' => array('config' => $config)), 'setting');
  }
  _radioactivity_register_emitter('RESET');
}

/**
 * Implement hook_field_validate().
 */
function radioactivity_field_validate($obj_type, $object, $field, $instance, $langcode, &$items, &$errors) {
  foreach ($items as $delta => $item) {
    if (isset($item[RADIOACTIVITY_FIELD_ENERGY]) < 0) {
      $errors[$field['field_name']][$langcode][$delta][] = array(
        'error' => 'radioactivity_invalid',
        'message' => t('Value must be greater than 0'),
      );
    }
  }
}

/**
 * Implement hoo_field_is_empty().
 */
function radioactivity_field_is_empty($item, $field) {
  return strlen($item[RADIOACTIVITY_FIELD_ENERGY]) == 0;
}

function radioactivity_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  if ($field['type'] == RADIOACTIVITY_FIELD_TYPE) {

    foreach ($items as $delta => $item) {

      // ensure values
      $items[$delta][RADIOACTIVITY_FIELD_TIMESTAMP] = time();
    }
  }
}

/**
 * Implement hook_field_insert().
 */
function radioactivity_field_insert($entity_type, $entity, $field, $instance, $langcode, &$items) {
  if ($field['type'] == RADIOACTIVITY_FIELD_TYPE) {
    foreach ($items as $delta => $item) {
      // ensure values
      $items[$delta][RADIOACTIVITY_FIELD_TIMESTAMP] = time();
    }
  }
}

/**
 * Implement hook_field_widget().
 *
 * This widget displayed three text fields\, one each for red, green,
 * and blue. However, the field type defines a single text column,
 * rgb, which needs an HTML color spec. Define an element validate
 * handler that converts our r, g, and b fields into a simulaed single
 * 'rgb' form element.
 */
function radioactivity_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta = 0, $element) {

  if (!user_access("edit radioactivity")) {
    return $element;
  }

  if (isset($items[$delta][RADIOACTIVITY_FIELD_TIMESTAMP]) && $items[$delta][RADIOACTIVITY_FIELD_TIMESTAMP] > 0) {
    $seconds = time() - $items[$delta][RADIOACTIVITY_FIELD_TIMESTAMP];
    $minutes = floor($seconds / 60);
    $hours   = floor($minutes / 60);
    $seconds = $seconds - ($minutes * 60);
    $minutes = $minutes - ($hours * 60);

    $time_ago = t(
      "Radioactivity energy. Last emission @hour hours @min minutes and @sec seconds ago",
      array(
        "@hour" => $hours,
        "@min" => $minutes,
        "@sec" => $seconds,
      )
    );
  }
  else {
    $time_ago = t("Radioactivity energy.");
  }

  $title     = $instance['label'];
  $energy    = isset($items[$delta][RADIOACTIVITY_FIELD_ENERGY]) ? $items[$delta][RADIOACTIVITY_FIELD_ENERGY] : 0;
  $timestamp = isset($items[$delta][RADIOACTIVITY_FIELD_TIMESTAMP]) ? $items[$delta][RADIOACTIVITY_FIELD_TIMESTAMP] : time();
  $element += array(
    '#type' => 'fieldset',
    '#group' => 'Radioactivity',
    '#title' => $title,
    RADIOACTIVITY_FIELD_ENERGY => array(
      '#type' => 'textfield',
      '#title' => t("Energy"),
      '#default_value' => $energy,
      '#description' => $time_ago,
    ),
    RADIOACTIVITY_FIELD_TIMESTAMP => array(
      '#type' => 'hidden',
      '#title' => t("Last emission"),
      '#default_value' => $timestamp,
    ),
  );

  if ($instance['settings']['history']) {

    drupal_add_js(drupal_get_path('module', 'radioactivity') . '/js/radioactivity-history.js');

    $entity = &$form['#entity'];
    $info = entity_get_info($instance['entity_type']);
    $id = $info['entity keys']['id'];

    if (isset($entity->{$id})) {
      $entity_id = $entity->{$id};
      $data = _radioactivity_get_history_for_field_and_entity($instance['id'], $entity_id);

      $element += array(
        RADIOACTIVITY_HISTORY_GRAPH => array(
          '#theme' => 'radioactivity_history',
          '#dataset' => $data,
        ),
      );
    }
  }

  return $element;
}
