<?php

/**
 * @file
 * This file contains the functions required for views integration
 */

/**
 * Implementation of hook_views_data().
 *
 */
function sco_node_views_data() {

  // tables
  $data['sco_node']['table']['group'] = t('SCO Node');
  
  $data['sco_node']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('SCO Node'),
    'help' => t('SCO nodes containing SCORM content.'),
    'access query tag' => 'node_access',
  );

  // joins  
  $data['sco_node']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );
  
  // fields
  $data['sco_node']['nid'] = array(
    'title' => t('SCO Node'),
    'help' => t('SCO Node.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('SCO Node'),
    ),
  );
  
  $data['sco_node']['status'] = array(
    'title' => t('Status'),
    'help' => t('SCO Status for current user.'),
    'real field' => 'nid',
    'field' => array(
      'handler' => 'sco_node_status_views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'sco_node_status_views_handler_filter_equality',
      'label' => t('Status'),
      'use equal' => TRUE,
    ),
  );
  
  $data['sco_node']['completed'] = array(
    'title' => t('Completed'),
    'help' => t('SCO completion date for current user.'),
    'real field' => 'nid',
    'field' => array(
      'handler' => 'sco_node_completed_views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array( 
      'handler' => 'views_handler_sort_date', 
    ), 
    'filter' => array( 
      'handler' => 'views_handler_filter_date', 
    ),
  );
  
  // sco_node_attempt table
  $data['sco_node_attempt']['table']['group'] = t('SCO Node Attempt');
  
  $data['sco_node_attempt']['table']['base'] = array(
    'field' => 'id',
    'title' => t('SCO Node Attempt'),
    'help' => t('SCO node attempt.'),
  );

  // joins  
  $data['sco_node_attempt']['table']['join']['sco_node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );
  $data['sco_node_attempt']['table']['join']['node'] = array(
    'left_table' => 'sco_node',
    'left_field' => 'nid',
    'field' => 'nid',
  );
  $data['sco_node_attempt']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );
  
  // fields
  $data['sco_node_attempt']['id'] = array(
    'title' => t('Attempt ID'),
    'help' => t('Attempt Id.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );  
  
  $data['sco_node_attempt']['nid'] = array(
    'title' => t('SCO Node'),
    'help' => t('SCO Node.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('SCO Node'),
    ),
    'field' => array( 
      'handler' => 'views_handler_field_node', 
      'click sortable' => TRUE, 
    ),
    'argument' => array( 
      'handler' => 'views_handler_argument_node_nid', 
      'name field' => 'title', 
      'numeric' => TRUE, 
      'validate type' => 'nid', 
    ),      
  );
  
  $data['sco_node_attempt']['uid'] = array(
    'title' => t('User'),
    'help' => t('User.'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('SCO Attempt User'),
    ),
  );
  
  $data['sco_node_attempt']['started'] = array(
    'title' => t('Started'),
    'help' => t('Timestamp of attempt start.'),
    'field' => array(
      'handler' => 'sco_node_attempt_datetime_views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  
  $data['sco_node_attempt']['completed'] = array(
    'title' => t('Completed'),
    'help' => t('Timestamp of attempt completion.'),
    'field' => array(
      'handler' => 'sco_node_attempt_datetime_views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  
  $data['sco_node_attempt']['status'] = array(
    'title' => t('Status'),
    'help' => t('Attempt Status.'),
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
  
  $data['sco_node_attempt']['outcome'] = array(
    'title' => t('Outcome'),
    'help' => t('Attempt Outcome.'),
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
  
  $data['sco_node_attempt']['score'] = array(
    'title' => t('Score'),
    'help' => t('Attempt Score.'),
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
  
  $data['sco_node_attempt']['total_time'] = array(
    'title' => t('Total Time'),
    'help' => t('Total Time to complete the attempt.'),
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
  
  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function sco_node_views_data_alter(&$data) {

  $data['node']['table']['join']['sco_node'] = array(
    'field' => 'nid',
    'left_field' => 'nid',
  );
  
  $data['node']['table']['join']['sco_node_attempt'] = array(
    'field' => 'nid',
    'left_field' => 'nid',
  );
  
  $data['users']['table']['join']['sco_node_attempt'] = array(
    'field' => 'uid',
    'left_field' => 'uid',
  );

  // SCO attempt count (node).
  $data['node']['sco_node_attempt_count_node'] = array(
    'group' => t('SCO Node'),
    'field' => array(
      'title' => t('SCO Node attempt count'),
      'help' => t('The number of SCO attempts for this node.'),
      'handler' => 'sco_node_attempt_count_views_handler_field',
      'count_type' => 'node',
    ),
  );
  
  // SCO user attempted count (node).
  $data['node']['sco_node_user_attempted_count_node'] = array(
    'group' => t('SCO Node'),
    'field' => array(
      'title' => t('SCO Node attempted user count'),
      'help' => t('The number of users that attempted the SCO.'),
      'handler' => 'sco_node_attempt_count_views_handler_field',
      'count_type' => 'user_attempted',
    ),
  );
  
  // SCO user completed count (node).
  $data['node']['sco_node_user_completed_count_node'] = array(
    'group' => t('SCO Node'),
    'field' => array(
      'title' => t('SCO Node completed user count'),
      'help' => t('The number of users that completed the SCO.'),
      'handler' => 'sco_node_attempt_count_views_handler_field',
      'count_type' => 'user_completed',
    ),
  );
  
  // SCO attempt count (user).
  $data['users']['sco_node_attempt_count_user'] = array(
    'field' => array(
      'title' => t('SCO Node attempt count'),
      'help' => t('The number of SCO attempts for this user.'),
      'handler' => 'sco_node_attempt_count_views_handler_field',
      'count_type' => 'user',
    ),
  );
}

class sco_node_status_views_handler_filter_equality extends views_handler_filter_equality {

  function value_form(&$form, &$form_state) { 
  
    parent::value_form($form, $form_state);   
  
    $form['value'] = array( 
      '#type' => 'select', 
      '#title' => t('Status'), 
      '#options' => array( 
        'complete' => t('Complete'), 
        'incomplete' => t('Incomplete'), 
      ), 
      '#default_value' => $this->value, '
      #required' => FALSE, 
    ); 
  }
}

class sco_node_status_views_handler_field extends views_handler_field {

  function get_value($values, $field = NULL) {
  
    return sco_node_get_user_status($values->nid);
  }
}

class sco_node_completed_views_handler_field extends views_handler_field_date {

  function get_value($values, $field = NULL) {
  
    return strtotime(sco_node_get_user_completed($values->nid));
  }
}

class sco_node_attempt_count_views_handler_field extends views_handler_field {

  function construct() {
    parent::construct();
    $this->count_type = $this->definition['count_type'];

    if ($this->count_type == 'node' || $this->count_type == 'user_completed' || $this->count_type == 'user_attempted') {
      $this->additional_fields['nid'] = 'nid';
    }
    elseif ($this->count_type == 'user') {
      $this->additional_fields['uid'] = 'uid';
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    if ($this->definition['count_type'] == 'node' || $this->definition['count_type'] == 'user') {
      $options['label'] = array('default' => '# of Attempts', 'translatable' => TRUE);
    }
    elseif ($this->definition['count_type'] == 'user_attempted') {
      $options['label'] = array('default' => '# of Users Attempted', 'translatable' => TRUE);
    }
    elseif ($this->definition['count_type'] == 'user_completed') {
      $options['label'] = array('default' => '# of Users Completed', 'translatable' => TRUE);
    }
    return $options;
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
  
    $output = NULL;
    if ($this->count_type == 'node') {
      $output = sco_node_get_attempt_count_node($values->{$this->aliases['nid']});
    }
    elseif ($this->count_type == 'user') {
      $output = sco_node_get_attempt_count_user($values->{$this->aliases['nid']}, $values->{$this->aliases['uid']});
    }
    elseif ($this->count_type == 'user_attempted') {
      $output = sco_node_get_attempted_user_count_node($values->{$this->aliases['nid']});
    }
    elseif ($this->count_type == 'user_completed') {
      $output = sco_node_get_completed_user_count_node($values->{$this->aliases['nid']});
    }

    return $output;
  }
}

class sco_node_attempt_datetime_views_handler_field extends views_handler_field_date {

  function get_value($values, $field = NULL) {
    $value = parent::get_value($values, $field);
    if (!empty($value)) {
      // Convert database datetime value to timestamp, so that the date handler
      // understands it.
      $datetime = new DateTime($value);
      $value = $datetime->getTimestamp();
    }
    return $value;
  }
}

