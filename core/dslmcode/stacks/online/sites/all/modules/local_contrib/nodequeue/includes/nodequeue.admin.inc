<?php

/**
 * @file
 * Admin page callbacks for the nodequeue module.
 */

/**
 * Form builder for the nodequeue settings tab.
 */
function nodequeue_admin_settings($form, &$form_state) {
  $form = array();
  $form['nodequeue_use_tab'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create a menu tab for each node that could belong to any queues'),
    '#default_value' => variable_get('nodequeue_use_tab', 1),
  );
  $form['nodequeue_tab_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Nodequeue tab label'),
    '#default_value' => variable_get('nodequeue_tab_name', t('Nodequeue')),
    '#description' => t('If nodes will have a menu tab for manipulating related nodequeues, what should that tab be called?'),
  );
  $form['nodequeue_autocomplete_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Nodequeue autocomplete limit'),
    '#size'=> 2,
    '#default_value' => variable_get('nodequeue_autocomplete_limit', 10),
    '#description' => t('Number of node titles to show in the autocomplete search results.'),
  );
  $form['nodequeue_view_per_queue'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create one view per queue'),
    '#description' => t("Nodequeue can create a view for each queue. \n
      If you wish to have fewer views, you can disable this option and use a single view with an argument for the qid."),
    '#default_value' => variable_get('nodequeue_view_per_queue', 1),
  );
  return system_settings_form($form);
}

/**
 * Page callback to add a node to a queue.
 */
function nodequeue_admin_add_node($queue, $subqueue, $node) {
  if (!nodequeue_check_token($node->nid)) {
    return drupal_goto();
  }
  $id = nodequeue_get_content_id($queue, $node);
  nodequeue_subqueue_add($queue, $subqueue, $id);

  // Provide a response if this is javascript.
  if (!empty($_POST['js'])) {
    if (isset($_GET['tab'])) {
      nodequeue_js_output(t('Remove from queue'),
        url("nodequeue/$queue->qid/remove-node/$subqueue->sqid/$node->nid", array('query' => nodequeue_get_query_string($node->nid, TRUE, array('tab' => '1')))),
        nodequeue_subqueue_size_text($queue->size, $queue->size ? min($subqueue->count, $queue->size) : $subqueue->count, FALSE),
        $subqueue->sqid);
    }
    else {
      nodequeue_js_output(nodequeue_title_substitute($queue->link_remove, $queue, $subqueue),
        url("nodequeue/$queue->qid/remove-node/$subqueue->sqid/$node->nid", array('query' => nodequeue_get_query_string($node->nid, TRUE))));
    }
  }

  // There should always be a destination set for this, so just goto wherever.
  drupal_goto();
}

/**
 * Page callback to remove a node from a queue.
 */
function nodequeue_admin_remove_node($queue, $subqueue, $node) {
  if (!nodequeue_check_token($node->nid)) {
    return drupal_goto();
  }
  $id = nodequeue_get_content_id($queue, $node);
  nodequeue_subqueue_remove_node($subqueue->sqid, $id);

  // Provide a response if this is javascript.
  if (!empty($_POST['js'])) {
    if (isset($_GET['tab'])) {
      nodequeue_js_output(t('Add to queue'),
        url("nodequeue/$queue->qid/add-node/$subqueue->sqid/$node->nid", array('query' => nodequeue_get_query_string($node->nid, TRUE, array('tab' => '1')))),
        nodequeue_subqueue_size_text($queue->size, $subqueue->count - 1, FALSE),
        $subqueue->sqid);
    }
    else {
      nodequeue_js_output(nodequeue_title_substitute($queue->link, $queue, $subqueue),
        url("nodequeue/$queue->qid/add-node/$subqueue->sqid/$node->nid", array('query' => nodequeue_get_query_string($node->nid, TRUE))));
    }
  }

  // There should always be a destination set for this, so just goto wherever.
  drupal_goto();
}

/**
 * Display the queue controls for a node.
 *
 * @param $node
 *   The loaded $node; will be loaded by the hook_menu.
 */
function nodequeue_node_tab($node) {
  $output = '';

  // moved from hook_menu due to architecture change.  This function seems to only be called from menu anyway...
  $queues = nodequeue_load_queues_by_type($node->type, 'tab');
  if (!$queues) {
    return FALSE;
  }
  $header = array();
  $header[] = array('data' => t('Title'), 'field' => 'title', 'sort' => 'asc', 'class' => array('nodequeue-title'));
  $header[] = array('data' => t('Max nodes'), 'field' => 'size', 'class' => array('nodequeue-max-nodes'));
  $header[] = array('data' => t('In queue'), 'field' => 'count', 'class' => array('nodequeue-in-queue'));
  $header[] = array('data' => t('Operation'), 'class' => array('nodequeue-operation'));
  $table_sort = tablesort_init($header);

  $subqueues = nodequeue_get_subqueues_by_node($queues, $node);

  nodequeue_set_subqueue_positions($subqueues, $node->nid);

  $sort_primary = array();
  $sort_secondary = array();
  $sort_direction_regular = array('asc' => SORT_ASC, 'desc' => SORT_DESC);
  $sort_direction_reverse = array('asc' => SORT_DESC, 'desc' => SORT_ASC);
  foreach ($subqueues as $subqueue) {
    $queue = $queues[$subqueue->qid];
    $sort_secondary[] = $queue->title;
    switch ($table_sort['sql']) {
      case 'title':
      default:
        $sort_primary[] = $queue->title;
        $sort_direction = $sort_direction_regular;
        break;
      case 'size':
        $sort_primary[] = $queue->size;
        $sort_direction = $sort_direction_reverse;
        break;
      case 'count':
        $sort_primary[] = $subqueue->count;
        $sort_direction = $sort_direction_reverse;
        break;
    }
  }

  if (!empty($table_sort)) {
    if (strtolower($table_sort['sort']) == 'desc') {
      array_multisort($sort_primary, $sort_direction['desc'], $sort_secondary, $subqueues); // Re-indexes array keys; key no longer equals qid.
    }
    else {
      array_multisort($sort_primary, $sort_direction['asc'], $sort_secondary, $subqueues); // Re-indexes array keys; key no longer equals qid.
    }
  }

  $rows = array();
  foreach ($subqueues as $subqueue) {
    $queue = $queues[$subqueue->qid];
    $id = nodequeue_get_content_id($queue, $node);
    if (module_exists('translation')) {
      $subqueue = array($subqueue->sqid => $subqueue);
      nodequeue_set_subqueue_positions($subqueue, $id);
      $subqueue = array_shift($subqueue);
    }
    if (empty($subqueue->position)) {
      $op = l(
        t('Add to queue'),
        "nodequeue/$queue->qid/add-node/$subqueue->sqid/$id",
        array('attributes' => array('class' => array('nodequeue-ajax-toggle')),
          'query' => nodequeue_get_query_string($id, TRUE, array('tab' => '1')),
          'purl' => array('disabled' => TRUE))
      );
    }
    else {
      $op = l(
        t('Remove from queue'),
        "nodequeue/$queue->qid/remove-node/$subqueue->sqid/$id",
        array('attributes' => array('class' => array('nodequeue-ajax-toggle')),
          'query' => nodequeue_get_query_string($id, TRUE, array('tab' => '1')),
          'purl' => array('disabled' => TRUE))
      );
    }
    $row = array();
    $row[] = array(
      'class' => array('nodequeue-title'),
      'data' => l(nodequeue_title_substitute($queue->subqueue_title, $queue, $subqueue), "admin/structure/nodequeue/$queue->qid/view/$subqueue->sqid"),
    );
    $row[] = array(
      'class' => array('nodequeue-max-nodes'),
      'data' => $queue->size ? $queue->size : t('Infinite')
    );
    $row[] = array(
      'id' => 'nodequeue-count-' . $subqueue->sqid,
      'class' => array('nodequeue-in-queue'),
      'data' => nodequeue_subqueue_size_text($queue->size, $subqueue->count, FALSE)
    );
    $row[] = array('class' => array('nodequeue-operation'), 'data' => $op);
    $rows[] = $row;
  }

  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('nodequeue-table'))));
  drupal_add_js(drupal_get_path('module', 'nodequeue') . '/nodequeue.js');
  drupal_add_css(drupal_get_path('module', 'nodequeue') . '/nodequeue.css');
  return $output;
}

/**
 * Display a list of queues and their status for the administrator.
 */
function nodequeue_view_queues() {
  $output = '';

  if (module_exists('advanced_help')) {
    $output .= theme('advanced_help_topic', array(
      'module' => 'nodequeue',
      'topic' => 'about',
    ));
    $output .= '&nbsp;' . theme('advanced_help_topic', array(
      'module' => 'nodequeue',
      'topic' => 'about',
      'type' => t('Click here for information about this module'),
    ));
    $output = '<p>' . $output . '</p>';
  }

  // Fetch all of the queues.
  $queues = nodequeue_load_queues(nodequeue_get_all_qids(25));

  foreach ($queues as $queue) {
    if (!nodequeue_queue_access($queue)) {
      unset($queues[$queue->qid]);
    }
  }

  if (empty($queues)) {
    return $output . t('No nodequeues exist.');
  }

  $header = array(
    array('data' => t('Title'), 'field' => 'title', 'sort' => 'asc'),
    array('data' => t('Max nodes'), 'field' => 'size'),
    array('data' => t('Subqueues'), 'field' => 'subqueues'),
    array('data' => t('Operation')),
  );
  $table_sort = tablesort_init($header);

  $qids = array();
  $sort_primary = array();
  $sort_secondary = array();
  $sort_direction_regular = array('asc' => SORT_ASC, 'desc' => SORT_DESC);
  $sort_direction_reverse = array('asc' => SORT_DESC, 'desc' => SORT_ASC);
  foreach ($queues as $queue) {
    // If a queue has only one subqueue, store the qid so we can display
    // the number of nodes in the subqueue.
    if ($queue->subqueues == 1) {
      $qids[] = $queue->qid;
    }
    $sort_secondary[] = drupal_strtolower($queue->title);
    switch ($table_sort['sql']) {
      case 'title':
      default:
        $sort_primary[] = drupal_strtolower($queue->title);
        $sort_direction = $sort_direction_regular;
        break;
      case 'size':
        $sort_primary[] = $queue->size;
        $sort_direction = $sort_direction_reverse;
        break;
      case 'subqueues':
        $sort_primary[] = $queue->subqueues;
        $sort_direction = $sort_direction_regular;
        break;
    }
  }

  $subqueues = nodequeue_load_subqueues_by_queue($qids);
  // Relate all the subqueues we loaded back to our queues.
  foreach ($subqueues as $subqueue) {
    if (nodequeue_api_subqueue_access($subqueue, NULL, $queues[$subqueue->qid])) {
      $queues[$subqueue->qid]->subqueue = $subqueue;
    }
  }

  if (!empty($table_sort)) {
    if (strtolower($table_sort['sort']) == 'desc') {
      array_multisort($sort_primary, $sort_direction['desc'], $sort_secondary, $queues); // Re-indexes array keys; key no longer equals qid.
    }
    else {
      array_multisort($sort_primary, $sort_direction['asc'], $sort_secondary, $queues); // Re-indexes array keys; key no longer equals qid.
    }
  }

  $rows = array();
  foreach ($queues as $queue) {
    $operations = array();
    $sub_text = $queue->subqueues;

    // If this queue has only one subqueue.
    if ($sub_text == 1) {
      $sub_text .= " (" . nodequeue_subqueue_size_text($queue->size, $queue->subqueue->count) . ")";
      $operations[] = l(t('View'), "admin/structure/nodequeue/$queue->qid/view/" . $queue->subqueue->sqid);
    }
    else {
      $operations[] = l(t('View'), "admin/structure/nodequeue/$queue->qid/view");
    }

    if (user_access('administer nodequeue')) {
      $operations[] = l(t('Edit'), "admin/structure/nodequeue/$queue->qid/edit");
      $operations[] = l(t('Delete'), "admin/structure/nodequeue/$queue->qid/delete");
    }

    $rows[] = array(
      array('class' => array('nodequeue-title'), 'data' => check_plain($queue->title)),
      array('class' => array('nodequeue-max-nodes'), 'data' => $queue->size == 0 ? t('Infinite') : $queue->size),
      array('class' => array('nodequeue-subqueues'), 'data' => $sub_text),
      array('class' => array('nodequeue-operation'), 'data' => implode(' | ', $operations)),
    );
  }

  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= theme('pager', array('tags' => NULL));

  return $output;
}

/**
 * Display a list of subqueues for a queue and their sizes
 */
function nodequeue_view_subqueues($queue) {
  // Fetch all of the subqueues.
  $subqueues = nodequeue_load_subqueues_by_queue($queue->qid);

  $header = array(t('Title'), t('In queue'), t('Operation'));

  $rows = array();
  foreach ($subqueues as $subqueue) {
    if (nodequeue_api_subqueue_access($subqueue, NULL, $queue)) {
      $sub_text = nodequeue_subqueue_size_text($queue->size, $subqueue->count, FALSE);
      $rows[] = array(
        array('class' => array('nodequeue-title'), 'data' => check_plain($subqueue->title)),
        array('class' => array('nodequeue-subqueues'), 'data' => $sub_text),
        array('class' => array('nodequeue-operation'), 'data' => l(t('View'), "admin/structure/nodequeue/$queue->qid/view/$subqueue->sqid"))
      );
    }
  }

  $output = '<p>' . t('Max nodes in queue: @size', array('@size' => $queue->size ? $queue->size : t("Infinite"))) . '</p>';
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= theme('pager', array('tags' => NULL));

  return $output;
}

/**
 * Add or edit a queue.
 */
function nodequeue_edit_queue_form($form, &$form_state, $queue) {
  $info = nodequeue_api_info();

  // For adding queues.
  if (is_string($queue)) {
    // If the $queue is a string - name of a queue type, basically - then we test that it's a valid queue type.
    $queue = strtolower($queue);
    if (!isset($info[$queue])) {
      return FALSE;
    }
    drupal_set_title(t('Add @type', array('@type' => $info[$queue]['title'])), PASS_THROUGH);
    $queue = new nodequeue_queue($queue);
  }
  else {
    drupal_set_title(t("Nodequeue '@title'", array('@title' => $queue->title)), PASS_THROUGH);
  }

  $form['description'] = array(
    '#type' => 'fieldset',
    '#title' => filter_xss($info[$queue->owner]['title']),
    '#description' => filter_xss($info[$queue->owner]['description']),
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $queue->title,
    '#size' => 50,
    '#required' => TRUE,
    '#maxlength' => 64,
    '#description' => t('Enter the name of the queue'),
  );

  $form['name'] = array(
    '#type' => 'machine_name',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'nodequeue_machine_name_exists',
      'source' => array('title'),
    ),
    '#description' => t('A unique machine-readable name for this queue. It must only contain lowercase letters, numbers, and underscores.'),
  );

  if (!empty($queue->name)) {
    $form['name']['#default_value'] = $queue->name;
    $form['name']['#disabled'] = TRUE;
    $form['name']['#value'] = $queue->name;
  }

  // This is a value; as the default nodequeue implementation has just one
  // queue per nodequeue, this field is totally redundant. Plugins can
  // override this.
  $form['subqueue_title'] = array(
    '#type' => 'value',
    '#value' => $queue->subqueue_title,
  );
  // The placeholder is put here so that modifiers have an easy way to put
  // additional form widgets in a prominent spot but not before the title of
  // the queue.
  $form['placeholder'] = array();

  $form['size'] = array(
    '#type' => 'textfield',
    '#title' => t('Queue size'),
    '#default_value' => $queue->size,
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('The maximum number of nodes will appear in the queue. Enter 0 for no limit'),
  );

  $form['reverse'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reverse in admin view'),
    '#default_value' => $queue->reverse,
    '#description' => t('Ordinarily queues are arranged with the front of the queue (where items will be removed) on top and the back (where items will be added) on the bottom. If checked, this will display the queue such that items will be added to the top and removed from the bottom.'),
  );

  $form['link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link "add to queue" text'),
    '#default_value' => $queue->link,
    '#size' => 40,
    '#maxlength' => 40,
    '#description' => t('If you want a link to add a node to a queue in the "links" section (next to "add new comment"), enter the text here. If left blank no link will be given; note that enabling this feature for any queue will cause an extra query to be run every time a node is loaded. "%subqueue" will be replaced with the subqueue title, if applicable.'),
  );

  $form['link_remove'] = array(
    '#type' => 'textfield',
    '#title' => t('Link "remove from queue" text'),
    '#default_value' => $queue->link_remove,
    '#size' => 40,
    '#maxlength' => 40,
    '#description' => t('Enter the text for the corresponding link to remove a node from a queue. This may be blank (in which case no link will appear) but a remove link will only appear if link, above, is set.'),
  );

  $manipulate_all_queues = user_roles(FALSE, 'manipulate all queues');
  $manipulate_queues = user_roles(FALSE, 'manipulate queues');
  $roles = $manipulate_all_queues + $manipulate_queues;

  if (!empty($roles)) {
    $form['roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Roles'),
      '#default_value' => is_array($queue->roles) ? $queue->roles : array(),
      '#options' => $roles,
      '#description' => t('Check each role that can add nodes to the queue. Be sure that roles you want to appear here have "manipulate queues" access in the main access control panel.'),
    );

    foreach ($roles as $rid => $role) {
      $form['roles'][$rid] = array(
        '#type' => 'checkbox',
        '#title' => $role,
        '#default_value' => (isset($manipulate_all_queues[$rid]) || in_array($rid, $queue->roles)) ? TRUE : FALSE,
        '#disabled' => (isset($manipulate_all_queues[$rid])) ? TRUE : FALSE,
      );
    }
  }
  else {
    $form['roles'] = array(
      '#type' => 'value',
      '#value' => array(),
    );

    $form['roles_markup'] = array(
      '#type' => 'item',
      '#title' => t('Roles'),
      '#description' => '<strong>' . t('No roles have the "manipulate queues" permission, so only the administrator account will be able to add or remove items from this queue.') . '</strong>',
    );
  }

  $nodes = node_type_get_names();

  $form['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Types'),
    '#default_value' => $queue->types,
    '#options' => $nodes,
    '#description' => t('Check each node type that can be added to this queue.'),
  );

  $form['i18n'] = array(
    '#type' => 'radios',
    '#title' => t('Internationalization'),
    '#options' => array(
      '1' => t('Treat translation nodes as a single node'),
      '0' => t('Manually manage translated nodes'),
    ),
    '#default_value' => empty($queue->qid) && module_exists('translation') ? 0 : $queue->i18n,
    '#description' => t('Treating translations as a single node allows users to add, remove and manipulate a node
      in the queue regardless of which translation is acted upon; nodequeue will only act on the original node.
      When manually managing translation nodes, Nodequeue will ignore the relationship between node translations;
      each translation node must be added to the queue separately and will occupy a separate spot in the queue.
      Changing this setting will <strong>not</strong> update content that is already in the queue.'),
    '#access' => module_exists('translation'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  $form['owner'] = array(
    '#type' => 'value',
    '#value' => $queue->owner,
  );

  $form['show_in_links'] = array(
    '#type' => 'value',
    '#value' => $queue->show_in_links,
  );

  $form['show_in_tab'] = array(
    '#type' => 'value',
    '#value' => $queue->show_in_tab,
  );

  $form['show_in_ui'] = array(
    '#type' => 'value',
    '#value' => $queue->show_in_ui,
  );

  $form['reference'] = array(
    '#type' => 'value',
    '#value' => $queue->reference,
  );

  $form['subqueues'] = array(
    '#type' => 'value',
    '#value' => $queue->subqueues,
  );

  if (isset($queue->qid)) {
    $form[] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#validate' => array('nodequeue_edit_queue_form_delete_validate'),
      '#submit' => array('nodequeue_edit_queue_form_delete_submit'),
    );
    $form['qid'] = array(
      '#type' => 'value',
      '#value' => $queue->qid,
    );
    $form['count'] = array(
      '#type' => 'value',
      '#value' => $queue->count,
    );
  }

  nodequeue_api_queue_form($queue, $form);

  return $form;
}

/**
 * Validate function for the nodequeue_queue form.
 */
function nodequeue_edit_queue_form_validate($form, &$form_state) {
  if (empty($form_state['values']['title'])) {
    form_set_error('title', t('Please enter a title for this queue.'));
  }
  $queue = (object) $form_state['values'];
  // Fix checkboxes.
  $queue->roles = array_keys(array_filter($queue->roles));
  $queue->types = array_keys(array_filter($queue->types));

  if (!isset($queue->qid)) {
    $queue->new = TRUE;
  }

  nodequeue_api_queue_form_validate($queue, $form_state, $form);
}

/**
 * Submit function for the nodequeue_queue form.
 */
function nodequeue_edit_queue_form_submit($formid, &$form_state) {
  $queue = (object) $form_state['values'];
  // Fix checkboxes.
  $queue->roles = array_keys(array_filter($queue->roles));
  $queue->types = array_keys(array_filter($queue->types));

  // Remove roles that have the 'manipulate all queues' permission.
  $manipulate_all_queues = array_keys(user_roles(FALSE, 'manipulate all queues'));
  $queue->roles = array_diff($queue->roles, $manipulate_all_queues);

  if (!isset($queue->qid)) {
    $queue->new = TRUE;
  }

  // Modify show_in_links based on whether or not links are available.
  $queue->show_in_links = !empty($queue->link) || !empty($queue->link_remove);

  nodequeue_api_queue_form_submit($queue, $form_state);

  $qid = nodequeue_save($queue); // sets $queue->qid if needed.

  nodequeue_api_queue_form_submit_finish($queue, $form_state);

  nodequeue_check_subqueue_sizes($queue);

  if (!empty($queue->new)) {
    $form_state['values']['qid'] = $qid;
    drupal_set_message(t('The queue has been created.'));
  }
  else {
    drupal_set_message(t('The queue has been updated.'));
  }
  $form_state['redirect'] = 'admin/structure/nodequeue';
}

/**
 * Delete-validate function for the nodequeue_queue form.
 */
function nodequeue_edit_queue_form_delete_validate($form, &$form_state) {
  // No validation for delete step!  But we need to have this so the default validation isn't called.
}

/**
 * Delete-submit function for the nodequeue_queue form.
 */
function nodequeue_edit_queue_form_delete_submit($formid, &$form_state) {
  $form_state['redirect'] = "admin/structure/nodequeue/" . $form_state['values']['qid'] . "/delete";
}

/**
 * Confirm form to delete a queue
 */
function nodequeue_admin_delete($form, &$form_state, $queue) {
  $form['qid'] = array('#type'  => 'value', '#value' => $queue->qid);
  return confirm_form($form,
    t('Are you sure you want to delete "%title"?', array('%title' => $queue->title)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/structure/nodequeue',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

/**
 * Submit function for nodequeue delete
 */
function nodequeue_admin_delete_submit($formid, &$form_state) {
  if ($form_state['values']['confirm']) {
    nodequeue_delete($form_state['values']['qid']);
    drupal_set_message(t('The queue has been deleted.'));
  }
  $form_state['redirect'] = 'admin/structure/nodequeue';
}

/**
 * Page callback to view a queue.
 */
function nodequeue_admin_view($queue, $subqueue = array()) {
  drupal_set_title(t("Nodequeue '@title'", array('@title' => $queue->title)), PASS_THROUGH);
  $qid = $queue->qid;

  // If the queue has just one subqueue, it gets special treatment.
  if (empty($subqueue->sqid)) {
    if ($queue->subqueues == 1) {
      $subqueues = nodequeue_load_subqueues_by_queue($queue->qid);
      $subqueue = array_shift($subqueues);
    }
    else {
      // display subqueue list page.
      return nodequeue_view_subqueues($queue);
    }
  }
  elseif ($subqueue->sqid) {
    if (!nodequeue_api_subqueue_access($subqueue, NULL, $queue)) {
      return drupal_not_found();
    }
    // Adjust properties of the page so our subqueue is in the right
    // visual place.
    drupal_set_title(t("Subqueue '@title'",
      array('@title' => nodequeue_title_substitute($queue->subqueue_title, $queue, $subqueue))), PASS_THROUGH);
    $breadcrumb = drupal_get_breadcrumb();
    $breadcrumb[] = l($queue->title, "admin/structure/nodequeue/$queue->qid");
    drupal_set_breadcrumb($breadcrumb);
  }
  return nodequeue_arrange_subqueue($queue, $subqueue);
}

/**
 * View the contents of a subqueue, with links to re-order the queue.
 */
function nodequeue_arrange_subqueue($queue, $subqueue = NULL) {
  // set title and load subqueue if it's not provided
  drupal_set_title(t("Nodequeue '@title'", array('@title' => $queue->title)), PASS_THROUGH);
  if (!$subqueue->sqid) {
    if ($queue->subqueues == 1) {
      $subqueues = nodequeue_load_subqueues_by_queue($queue->qid);
      $subqueue = array_shift($subqueues);
    }
    else {
      return drupal_not_found();
    }
  }
  elseif ($subqueue->sqid) {
    if (!nodequeue_api_subqueue_access($subqueue, NULL, $queue)) {
      return drupal_not_found();
    }
    drupal_set_title(t("Subqueue '@title'", array('@title' => nodequeue_title_substitute($queue->subqueue_title, $queue, $subqueue))), PASS_THROUGH);
  }

  // get nodes from the queue
  $nodes = _nodequeue_dragdrop_get_nodes($queue, $subqueue);

  return drupal_get_form('nodequeue_arrange_subqueue_form_' . $subqueue->sqid, $queue, $nodes, $subqueue);
}

/**
 * Return a list of nodes in a specific subqueue.
 */
function _nodequeue_dragdrop_get_nodes($queue, $subqueue) {
  $order = $queue->reverse ? 'DESC' : 'ASC';

  $visible = nodequeue_nids_visible($subqueue->sqid);

  // Get a list of all nodes in the subqueue, regardless of access restrictions.
  $query = db_select('node', 'n')
    ->distinct();

  $query->leftJoin('nodequeue_nodes', 'nq', 'nq.nid = n.nid');
  $query->fields('n', array('nid'))
    ->fields('nq', array('position'))
    ->condition('nq.sqid', $subqueue->sqid)
    ->orderBy('nq.position', $order);
  $result = $query->execute();

  $nids = array();
  $sq_nodes = array();
  foreach ($result as $sq_node) {
    $nids[] = $sq_node->nid;
    // Save node position in a separate array so we can reference it later.
    $sq_nodes[$sq_node->nid]['position'] = $sq_node->position;
  }
  $nodes = node_load_multiple($nids);

  foreach ($nodes as $node) {
    $node->visible = isset($visible[$node->nid]) ? TRUE : FALSE;
    $node->position = $sq_nodes[$node->nid]['position'];
  }

  return $nodes;
}

/**
 * Form definition for nodequeue drag'n'drop form.
 */
function nodequeue_arrange_subqueue_form($form, $form_state, $queue, $nodes, $subqueue) {
  $form = array('#tree' => TRUE);

  // Prepare the main part of the form which will be themed as a table.
  $count = count($nodes);
  $form['nodes'] = array();
  $form['nodes']['#theme'] = 'nodequeue_arrange_subqueue_form_table';

  // Theme function needs these.
  $form['nodes']['#queue']    = (array) $queue;
  $form['nodes']['#subqueue'] = (array) $subqueue;

  foreach ($nodes as $node) {
    $form['nodes'][$node->nid]['#node'] = (array) $node;
    if ($node->visible) {
      $form['nodes'][$node->nid]['#node'] = (array) $node;
      $form['nodes'][$node->nid]['title'] = array('#markup' => l($node->title, 'node/' . $node->nid));
      $form['nodes'][$node->nid]['author'] = array('#markup' => theme('username', array('account' => $node)));
      $form['nodes'][$node->nid]['date'] = array('#markup' => format_date($node->created, 'short'));
    }
    else {
      $form['nodes'][$node->nid]['title'] = array('#value' => t('Restricted node, NID: @nid', array('@nid' => $node->nid)));
      $form['nodes'][$node->nid]['author'] = array('#value' => '');
      $form['nodes'][$node->nid]['date'] = array('#value' => '');
    }

    if (node_access('update', $node)) {
      $form['nodes'][$node->nid]['edit'] = array('#markup' => l(t('edit'), 'node/' . $node->nid . '/edit', array('attributes' => array('title' => t('Edit this node')))));
    }
    $form['nodes'][$node->nid]['position'] = array(
      '#type' => 'position',
      '#delta' => $count,
      '#default_value' => $node->position,
      '#attributes' => array(
        'class' => array('node-position'),
      ),
    );

    $attr = array(
      '#attributes' => array(
        'title' => t('Remove from queue'),
        'style' => 'display: none;',
        'class' => array('nodequeue-remove'),
        'id' => 'nodequeue-remove-' . $node->nid,
      ),
      'query' => nodequeue_get_query_string($node->nid, TRUE),
    );
    $form['nodes'][$node->nid]['remove'] = array('#markup' => l(t('remove'), 'nodequeue/' . $queue->qid . '/remove-node/' . $subqueue->sqid . '/' . $node->nid, $attr));
  }

  // Textfield for adding nodes to the queue.
  $form['add'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['add']['nid'] = array(
    '#type' => 'textfield',
    '#autocomplete_path' => 'nodequeue/autocomplete/' . $subqueue->sqid,
    '#maxlength' => 1024,
    '#default_value' => t('Enter the title of a node to add it to the queue'),
    '#attributes' => array('class' => array('subqueue-add-nid')),
  );
  $form['add']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add content'),
    '#submit' => array('nodequeue_arrange_subqueue_form_add_submit'),
  );

  // Submit, reverse, shuffle, and clear actions.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('nodequeue_arrange_subqueue_form_submit'),
  );
  $form['actions']['reverse'] = array(
    '#type' => 'submit',
    '#value' => t('Reverse'),
    '#submit' => array('nodequeue_arrange_subqueue_form_reverse_submit'),
  );
  $form['actions']['shuffle'] = array(
    '#type' => 'submit',
    '#value' => t('Shuffle'),
    '#submit' => array('nodequeue_arrange_subqueue_form_shuffle_submit'),
  );
  $form['actions']['clear'] = array(
    '#type' => 'submit',
    '#value' => t('Clear'),
    '#submit' => array('nodequeue_arrange_subqueue_form_clear_submit'),
  );

  // Disable all buttons if the queue is empty.
  if ($count == 0) {
    $form['actions']['submit']['#disabled']  = TRUE;
    $form['actions']['reverse']['#disabled'] = TRUE;
    $form['actions']['shuffle']['#disabled'] = TRUE;
    $form['actions']['clear']['#disabled']   = TRUE;
  }

  return $form;
}

/**
 * Validate handler for nodequeue_arrange_subqueue_form.
 */
function nodequeue_arrange_subqueue_form_validate($form, &$form_state) {
  $positions = array();
  foreach ($form_state['values'] as $nid => $element) {
    if (is_numeric($nid) && is_numeric($element['position'])) {
      $positions[$nid] = $element['position'];
    }
  }
  if (count(array_unique($positions)) < count($positions)) {
    $seen = array();
    foreach ($positions as $nid => $position) {
      if (isset($seen[$position])) {
        form_set_error($nid . '][position', t('Duplicate position value.'));
      }
      $seen[$position] = TRUE;
    }
  }
}

/**
 * Submit function for nodequeue_arrange_subqueue_form on 'Reverse' button.
 *
 * Yeah, this just calls the below function with a different parameter, but in D6 we're not supposed to use the $form['ops'].
 */
function nodequeue_arrange_subqueue_form_reverse_submit($form, &$form_state) {
  nodequeue_arrange_subqueue_form_submit($form, $form_state, TRUE, FALSE);
}

function nodequeue_arrange_subqueue_form_shuffle_submit($form, &$form_state) {
  nodequeue_arrange_subqueue_form_submit($form, $form_state, FALSE, TRUE);
}

/**
 * Submit handler for nodequeue drag'n'drop form. Updates node positions in {nodequeue_nodes}.
 */
function nodequeue_arrange_subqueue_form_submit($form, &$form_state, $reverse = FALSE, $shuffle = FALSE) {
  $nodes = array();
  foreach ($form_state['values']['nodes'] as $nid => $element) {
    if (is_numeric($nid)) {
      $nodes[$form_state['values']['nodes'][$nid]['position']] = array(
        'nid' => $nid,
        'data' => $form_state['values']['nodes'][$nid]
      );
    }
  }

  $message = 'The queue has been updated.';

  if ($reverse || $shuffle) {
    $keys = array_keys($nodes);
    $values = array_values($nodes);

    // reverse the list if the reverse button was pressed
    if ($reverse) {
      $values = array_reverse($values);
      $message = 'The queue has been reversed.';
    }

    // shuffle the list if the shuffle button was pressed.
    if ($shuffle) {
      shuffle($values);
      $message = 'The queue has been shuffled.';
    }

    $nodes = array_combine($keys, $values);
  }

  $qid  = $form['nodes']['#queue']['qid'];
  $sqid = $form['nodes']['#subqueue']['sqid'];
  nodequeue_save_subqueue_order($nodes, $qid, $sqid);

  drupal_set_message(t('@message', array('@message' => $message)));
}

/**
 * Validates new subqueue order information and if it passes validation,
 * deletes the old subqueue data from the database and saves the new data.
 *
 * @param $nodes:
 *   an array of nodes, keyed on the subqueue position.
 * @param $qid
 *   the queue id
 * @param unknown_type $sqid
 *   the subqueue id
 * @return An array where the first element is a numeric status code
 *   (0 means successfully saved) and the second element is a status message.
 */
function nodequeue_save_subqueue_order($nodes, $qid, $sqid) {
  $positions = array();
  $now = REQUEST_TIME;

  $queue = nodequeue_load($qid);
  $subqueue = nodequeue_load_subqueue($sqid);

  // cleanup the node array
  $clean = array();
  $count = 1;
  ksort($nodes);
  drupal_alter('nodequeue_sort', $nodes, $sqid);
  foreach ($nodes as $pos => $node) {
    if (!is_numeric($node['nid']) || $node['nid'] < 1) {
      return array(NODEQUEUE_INVALID_NID, 'Invalid nid value. New subqueue order not saved.');
    }
    if (is_numeric($pos)) {
      $clean[$count] = $node;
      $count++;
    }
    elseif ($pos == 'r') {
      // Remove the node from this subqueue.
      nodequeue_subqueue_remove_node($sqid, $node['nid']);
    }
    else {
      return array(NODEQUEUE_INVALID_POSITION, 'Invalid position value. New subqueue order not saved.');
    }
  }
  $nodes = $clean;

  array_walk($clean, create_function('&$node', '$node = serialize($node);'));

  if (count(array_unique($clean)) < count($nodes)) {
    return array(NODEQUEUE_DUPLICATE_POSITION, 'Duplicate position values are not allowed. New subqueue order not saved.');
  }
  // Allow other modules to alter the order of nodes.
  foreach (module_implements('nodequeue_save_subqueue_order_alter') as $module) {
    $function = $module . '_nodequeue_save_subqueue_order_alter';
    $function($sqid, $nodes);
  }

  // clear the queue and save the new positions
  db_delete('nodequeue_nodes')
    ->condition('sqid', $sqid)
    ->execute();
  foreach ($nodes as $pos => $node) {
    $args = array();
    if ($pos != 'r') {
      $query = db_insert('nodequeue_nodes')
        ->fields(array(
          'sqid' => $sqid,
          'qid' => $qid,
          'nid' => $node['nid'],
          'position' => $pos,
          'timestamp' => $now,
        ))
        ->execute();
    }
  }

  if ($queue->size) {
    // only necessary if the subqueue is of finite length
    nodequeue_check_subqueue_size($queue, $subqueue);
  }

  return array(NODEQUEUE_OK, 'The queue has been updated.');
}

function nodequeue_arrange_subqueue_form_clear_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/nodequeue/' . $form['nodes']['#queue']['qid'] . '/clear/' . $form['#subqueue']['sqid'];
}

function nodequeue_arrange_subqueue_form_add_submit($form, &$form_state) {
  $queue = nodequeue_load($form['nodes']['#queue']['qid']);
  $subqueue = nodequeue_load_subqueue($form['nodes']['#subqueue']['sqid']);

  if (!empty($form_state['values']['add']['nid'])) {
    preg_match('/\[nid: (\d+)\]$/', $form_state['values']['add']['nid'], $matches);
    $nid = $matches[1];
    if (empty($nid)) {
      form_set_error('', t('Please enter a valid node title.'));
    }
  }

  nodequeue_subqueue_add($queue, $subqueue, $nid);
}

/**
 * Page callback to remove an item from a queue. This will be used only
 * if javascript is disabled in the client, and is a fallback technique.
 * This differs from nodequeue_admin_remove_node in that it removes a
 * specific position, which is necessary in case a node is in a queue
 * multiple times.
 */
function nodequeue_admin_remove($queue, $subqueue, $pos) {
  if (!is_numeric($pos) || !is_object($subqueue) || !nodequeue_check_token($pos)) {
    return drupal_goto();
  }

  nodequeue_subqueue_remove($subqueue, $pos);

  drupal_goto();
}

/**
 * Confirm form to clear a queue.
 */
function nodequeue_clear_confirm($form, &$form_state, $queue, $subqueue) {
  if (empty($subqueue)) {
    return;
  }

  drupal_set_title(t("Nodequeue '@title'", array('@title' => $queue->title)), PASS_THROUGH);

  $form['qid']  = array('#type' => 'value', '#value' => $queue->qid);
  $form['sqid'] = array('#type' => 'value', '#value' => $subqueue->sqid);

  return confirm_form($form,
    t('Are you sure you want to clear the nodequeue %queue?', array('%queue' => nodequeue_title_substitute($queue->subqueue_title, $queue, $subqueue))),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/structure/nodequeue/' . $queue->qid . '/view/' . $subqueue->sqid,
    t('This action will remove all nodes from the queue and cannot be undone.'),
    t('Clear'), t('Cancel')
  );
}

/**
 * Submit function for nodequeue clear confirm
 */
function nodequeue_clear_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    nodequeue_queue_clear($form_state['values']['sqid']);
    drupal_set_message(t('The queue has been cleared.'));
    $form_state['redirect'] = 'admin/structure/nodequeue/' . $form_state['values']['qid'] . '/view/' . $form_state['values']['sqid'];
  }
}

/**
 * Page callback for autocomplete.
 */
function nodequeue_autocomplete() {
  $args = func_get_args();
  $sqid = array_shift($args);
  $string = implode('/', $args);
  $matches = _nodequeue_autocomplete($sqid, $string);
  drupal_json_output(drupal_map_assoc($matches));
}

function _nodequeue_autocomplete($sqid, $string) {
  $output = array();

  if (!is_numeric($sqid) || !$string) {
    return $output;
  }

  $subqueue = nodequeue_load_subqueue($sqid);
  if (!$subqueue) {
    return $output;
  }

  $queue = nodequeue_load($subqueue->qid);
  if (!$queue) {
    return $output;
  }

  $nodes = nodequeue_api_autocomplete($queue, $subqueue, $string);
  return $nodes;
}
