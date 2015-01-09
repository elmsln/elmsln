<?php

/**
 * @file
 * Providing extra functionality for the Entityform UI via views.
 */


/**
 * Implements hook_views_data().
 */
function entityform_views_data_alter(&$data) {
  $info = entity_get_info('entityform');
  $label = $info['label'];
  $data['entityform']['link_entityform'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the %label.', array('%label' => $label)),
      'handler' => 'entityform_handler_link_field',
    ),
  );
  $data['entityform']['edit_entityform'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the %label.', array('%label' => $label)),
      'handler' => 'entityform_handler_edit_link_field',
    ),
  );
  $data['entityform']['delete_entityform'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the %label.', array('%label' => $label)),
      'handler' => 'entityform_handler_delete_link_field',
    ),
  );

  // This content of this field are decided based on the menu structure that
  // follows entityforms/entityform/%entityform_id/op
  $data['entityform']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this %label.', array('%label' => $label)),
      'handler' => 'entityform_handler_entityform_operations_field',
    ),
  );

  $data['entityform_type']['table']['join'] = array(
    'entityform' => array(
      'left_field' => 'type',
      'field' => 'type',
      //'type' => 'INNER', // all nodes have an author.
    ),
  );
  $data['entityform_type']['submit_entityform_type'] = array(
      'field' => array(
          'title' => t('Submit Link'),
          'help' => t('Provide a link to the submit form for the entityform type.'),
          'handler' => 'entityform_type_handler_submit_link_field',
      ),
  );
  // @todo This should be handled by entity api remove
  $data['entityform']['uid']['relationship'] = array(
    'base' => 'users',
    'field' => 'uid',
    'handler' => 'views_handler_relationship',
    'label' => t('User Submitting'),
  );
  $data['entityform']['table']['join']['user'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );
}
