<?php
/**
 * @file editableviews.views.inc
 * Contains Views hooks.
 */

/**
 * Implements hook_views_plugins().
 */
function editableviews_views_plugins() {
  $plugins = array();
  $plugins['style'] = array(
    'editableviews_table' => array(
      'title' => t('Editable table'),
      'help' => t('Displays a table whose fields can be edited.'),
      'handler' => 'editableviews_plugin_style_row_edit_table',
      'theme' => 'views_view_table',
      'theme path' => drupal_get_path('module', 'views') . '/theme',
      'uses row class' => TRUE,
      'uses fields' => TRUE,
      'uses options' => TRUE,
      'type' => 'normal',
      'help topic' => 'style-table',
    ),
  );

  return $plugins;
}

/**
 * Implements hook_views_data_alter().
 *
 *  - Add editable field handlers.
 *  - Set the direction on entityreference reverse relationships.
 */
function editableviews_views_data_alter(&$data) {
  // We're going to need this.
  $entity_info = entity_get_info();

  // Editable fields for FieldAPI fields.
  foreach (field_info_fields() as $field) {
    if ($field['storage']['type'] != 'field_sql_storage') {
      continue;
    }

    // Because we act in a way analogous to Views' default views_data helper,
    // field_views_field_default_views_data(), we should consider checking
    // that the field's module doesn't implement hook_field_views_data(),
    // because if it does, it possibly means our one-size-fits-all approach
    // here is unsuitable for the field. TODO!

    $table = _field_sql_storage_tablename($field);
    $column = $field['field_name'];
    $keys = array_keys($field['columns']);
    $real_field = reset($keys);

    // Some fields just aren't there, such as OG ones.
    if (!isset($data[$table][$column])) {
      continue;
    }

    // Copy the UI texts from the original field. We don't copy the whole
    // array because that will have other, unwanted, handler types on it.
    $new_field_name = $column . '_editable';
    $data[$table][$new_field_name] = array(
      'group'       => $data[$table][$column]['group'],
      'title'       => $data[$table][$column]['title'] . ' ' . t('(editable)'),
      'title short' => $data[$table][$column]['title short'],
      // TODO: add detail here.
      'help'        => $data[$table][$column]['help'],
    );

    $data[$table][$new_field_name]['field'] = $data[$table][$column]['field'];
    $data[$table][$new_field_name]['field']['handler'] = 'editableviews_handler_field_field_edit';
  } // foreach field_info_fields()

  // Editable field for entity metadata properties. Only properties with a
  // defined 'setter callback' may be used.
  // We define a single pseudofield, and set the particular property at the
  // handler options level, as depending on metadata properties here is quite
  // likely weirdly circular.
  foreach ($entity_info as $entity_type => $entity_type_info) {
    if (!empty($entity_type_info['base table']) && isset($data[$entity_type_info['base table']])) {
      $data[$entity_type_info['base table']]['metadata_property_editable'] = array(
        'title' => t("Entity metadata property (editable)"),
        'help' => t("Editable field for entity metadata properties that have setter callbacks defined."),
        'field' => array(
          'real field' => $entity_type_info['entity keys']['id'],
          'handler' => 'editableviews_handler_field_entity_metadata_property',
        ),
      );
    }
  }

  // Node title editable field.
  $data['node']['title_editable'] = array(
    'title' => $data['node']['title']['title'] . ' ' . t('(editable)'),
    'help'  => $data['node']['title']['help'],
  );
  $data['node']['title_editable']['field'] = $data['node']['title']['field'];
  $data['node']['title_editable']['field']['handler'] = 'editableviews_handler_field_node_title_edit';

  // Define the direction of entityreference reverse relationships.
  // This is set by entityreference module in the magic callback on the field,
  // hook_field_views_data_views_data_alter(). This is invoked by Field module's
  // hook_views_data_alter(). Unfortunately, unlike Field module's
  // hook_views_data() there is no drupal_alter() of the resulting data.
  // Therefore our only way to alter it is here. Extremely fortunately, it
  // appears to already be here in the data at this point and module weight
  // does not seem to be an issue!
  foreach (field_info_fields() as $field) {
    if ($field['type'] == 'entityreference') {
      // This repeats much of the code in
      // entityreference_field_views_data_views_data_alter().
      foreach ($field['bundles'] as $entity_type => $bundles) {
        $target_entity_type = $field['settings']['target_type'];
        if (isset($entity_info[$target_entity_type]['base table'])) {
          $target_entity_info = $entity_info[$target_entity_type];
          $pseudo_field_name = 'reverse_' . $field['field_name'] . '_' . $entity_type;
          $data[$target_entity_info['base table']][$pseudo_field_name]['relationship']['editableviews_direction'] = 'reverse';
        }
      }
    }
  }

  // Save button jump link field.
  $data['views']['editableviews_jump_link'] = array(
    'title' => t('Editable view save button jump link'),
    'help' => t('Ouputs a jump link to the save button at the bottom of the view.'),
    'field' => array(
      'handler' => 'editableviews_handler_field_save_button_jump_link',
    ),
  );
}

/**
 * Implement hook_field_views_data_alter.
 *
 * Define the direction of entityreference forward relationships.
 *
 * Watch carefully: this is called by Field module's hook_views_data() to alter
 * the Views data definition for a single field, either as given by the field
 * module itself with hook_field_views_data(), or by default values. In our
 * case, we're altering entityreference field data defined in
 * entityreference_field_views_data().
 */
function editableviews_field_views_data_alter(&$data, $field, $module) {
  // Bail for anything else.
  if ($module != 'entityreference') {
    return;
  }

  // There will be more than one table (node revisions). But we only care about
  // the real one.
  $table_name = _field_sql_storage_tablename($field);
  $field_name = $field['field_name'] . '_target_id';

  $data[$table_name][$field_name]['relationship']['editableviews_direction'] = 'forward';
  // This is mysteriously missing from Entityreference!
  $data[$table_name][$field_name]['relationship']['field_name'] = $field['field_name'];
}
