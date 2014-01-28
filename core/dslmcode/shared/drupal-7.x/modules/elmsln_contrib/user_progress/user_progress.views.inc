<?php
/**
 * @file
 * Provide views integration with the three user progress tables
 */
/**
 * Describe table structure to Views.
 *
 * This hook should be placed in MODULENAME.views.inc and it will
 * be auto-loaded. This must either be in the same directory as the
 * .module file or in a subdirectory named 'includes'.
 *
 * The full documentation for this hook is in the advanced help.
 * @link http://views-help.doc.logrus.com/help/views/api-tables @endlink
 */
function user_progress_views_data() {
  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['user_progress_types']['table']['group'] = t('User progress types');

  // Define this as a base table. In reality this is not very useful for
  // this table, as it isn't really a distinct object of its own, but
  // it makes a good example.
  $data['user_progress_types']['table']['base'] = array(
    'field' => 'upt_name',
    'title' => t('User progress types'),
    'help' => t("Listing of all types in the system"),
    'weight' => -10,
  );

  // This table references the {node} table.
  // This creates an 'implicit' relationship to the node table, so that when 'Node'
  // is the base table, the fields are automatically available.
  $data['user_progress_types']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'user_progress_registry' => array(
      'left_field' => 'upt_name',
      'field' => 'upt_name',
    ),
  );

  // Next, describe each of the individual fields in this table to Views. For
  // each field, you may define what field, sort, argument, and/or filter
  // handlers it supports. This will determine where in the Views interface you
  // may use the field.
  // Example plain text field.
  $data['user_progress_types']['upt_name'] = array(
    'title' => t('Machine type name'),
    'help' => t('Machine name for registry type'),
    // Because this is a foreign key to the {node} table. This allows us to
    // have, when the view is configured with this relationship, all the fields
    // for the related node available.
    'relationship' => array(
      'base' => 'user_progress_registry',
      'field' => 'upt_name',
      'handler' => 'views_handler_relationship',
      'label' => t('User progress activity registry'),
    ),
  );
  // Example plain text field.
  $data['user_progress_types']['name'] = array(
    'title' => t('Name'),
    'help' => t('Name of this type'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['user_progress_registry']['table']['group'] = t('User progress registry');

  // Define this as a base table. In reality this is not very useful for
  // this table, as it isn't really a distinct object of its own, but
  // it makes a good example.
  $data['user_progress_registry']['table']['base'] = array(
    'field' => 'upregid',
    'title' => t('User progress registry'),
    'help' => t("Listing of all up registry in scope of this system"),
    'weight' => -10,
  );

  // This table references the {node} table.
  // This creates an 'implicit' relationship to the node table, so that when 'Node'
  // is the base table, the fields are automatically available.
  $data['user_progress_registry']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'user_progress_types' => array(
      'left_field' => 'upt_name',
      'field' => 'upt_name',
    ),
  );

  // Next, describe each of the individual fields in this table to Views. For
  // each field, you may define what field, sort, argument, and/or filter
  // handlers it supports. This will determine where in the Views interface you
  // may use the field.

  // Node ID field.
  $data['user_progress_registry']['nid'] = array(
    'title' => t('User progress registry'),
    'help' => t('Relate a User progress registry'),
    // Because this is a foreign key to the {node} table. This allows us to
    // have, when the view is configured with this relationship, all the fields
    // for the related node available.
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('User progress record'),
    ),
  );

  // Example plain text field.
  $data['user_progress_registry']['title'] = array(
    'title' => t('Title'),
    'help' => t('Title of this activity type'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Example plain text field.
  $data['user_progress_registry']['upt_name'] = array(
    'title' => t('Machine type name'),
    'help' => t('Machine name for registry type'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Example numeric text field.
  $data['user_progress_registry']['upregid'] = array(
    'title' => t('registry id'),
    'help' => t('Unique id of this registry record'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Make user progress records table visible to views

  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['user_progress_records']['table']['group'] = t('User Progress record');

  // Define this as a base table. In reality this is not very useful for
  // this table, as it isn't really a distinct object of its own, but
  // it makes a good example.
  $data['user_progress_records']['table']['base'] = array(
    'field' => 'uprid',
    'title' => t('User progress records'),
    'help' => t("Listing of all recorded up records"),
    'weight' => -10,
  );

  // This table references the {node} table.
  // This creates an 'implicit' relationship to the node table, so that when 'Node'
  // is the base table, the fields are automatically available.
  $data['user_progress_records']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'user_progress_registry' => array(
      'left_field' => 'upregid',
      'field' => 'upregid',
    ),
  );

  // Next, describe each of the individual fields in this table to Views. For
  // each field, you may define what field, sort, argument, and/or filter
  // handlers it supports. This will determine where in the Views interface you
  // may use the field.

  // Example numeric text field.
  $data['user_progress_records']['uprid'] = array(
    'title' => t('User progress id'),
    'help' => t('Unique id of this up record'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // registry id
  $data['user_progress_records']['upregid'] = array(
    'title' => t('registry id'),
    'help' => t('Related User progress registry'),
    'relationship' => array(
      'base' => 'user_progress_registry',
      'field' => 'upregid',
      'handler' => 'views_handler_relationship',
      'label' => t('Activity type in registry'),
    ),
  );

  // User ID field.
  $data['user_progress_records']['uid'] = array(
    'title' => t('User progress record'),
    'help' => t('Relate a User progress record'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User that recorded progress'),
    ),
  );

  // User ID field.
  $data['user_progress_records']['nid'] = array(
    'title' => t('Node of record'),
    'help' => t('Node id that was involved with this record'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Node progress happened on'),
    ),
  );

  // Example plain text field.
  for ($i=1; $i<USER_PROGRESS_MAX_DATA_POINTS+1; $i++) {
    $data['user_progress_records']['data' . $i] = array(
      'title' => t('Data point @i', array('@i' => $i)),
      'help' => t('Data is subject to schema definition'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    );
  }

  // Example timestamp field.
  $data['user_progress_records']['created'] = array(
    'title' => t('Timestamp'),
    'help' => t('Record timestamp'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}
