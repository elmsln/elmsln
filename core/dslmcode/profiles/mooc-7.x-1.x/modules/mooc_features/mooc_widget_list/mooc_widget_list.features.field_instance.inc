<?php
/**
 * @file
 * mooc_widget_list.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mooc_widget_list_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'field_collection_item-field_mooc_tab_collection-field_mooc_tab_content'
  $field_instances['field_collection_item-field_mooc_tab_collection-field_mooc_tab_content'] = array(
    'bundle' => 'field_mooc_tab_collection',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_mooc_tab_content',
    'label' => 'Content',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_mooc_tab_collection-field_mooc_tab_title'
  $field_instances['field_collection_item-field_mooc_tab_collection-field_mooc_tab_title'] = array(
    'bundle' => 'field_mooc_tab_collection',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_mooc_tab_title',
    'label' => 'Title',
    'required' => 1,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 50,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'node-mooc_list_widget-field_mooc_tab_collection'
  $field_instances['node-mooc_list_widget-field_mooc_tab_collection'] = array(
    'bundle' => 'mooc_list_widget',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 0,
      ),
      'mooc_fieldset' => array(
        'label' => 'hidden',
        'module' => 'field_collection_fieldset',
        'settings' => array(
          'add' => 'Add',
          'collapsed' => 1,
          'collapsible' => 1,
          'delete' => 'Delete',
          'description' => 0,
          'edit' => 'Edit',
          'legend' => 'field_mooc_tab_title',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_fieldset_view',
        'weight' => 0,
      ),
      'mooc_tabs' => array(
        'label' => 'hidden',
        'module' => 'field_collection_tabs',
        'settings' => array(
          'title_field' => 'field_mooc_tab_title',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_tabs',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_mooc_tab_collection',
    'label' => 'Tabs',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_collection_fieldset',
      'settings' => array(
        'collapsed' => 1,
        'last_item_collapsed' => 1,
      ),
      'type' => 'field_collection_fieldset',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Tabs');
  t('Title');

  return $field_instances;
}
