<?php

/**
 * @file
 * Define callbacks for hook_menu admin/config/user-interface/cis-lmsless-nav
 */

function cis_lmsless_nav_parent_form($form_state) {
  // Identify that the elements in 'links' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['links']['#tree'] = TRUE;

  // fetch the current links from the variable
  $result = variable_get('cis_lmsless_nav_links', array());
  $icon_libs = _elmsln_core_icon_libraries();
  // for each link in the array create form elements
  if (!empty($result)) {
    foreach ($result as $item_key => $item) {
      // Create a form entry for this item.
      // Each entry will be an array using the the unique id for that item as
      // the array key, and an array of table row data as the value.
      $form['links'][$item_key] = array(
        'title' => array(
          '#markup' => $item['title'],
        ),
        'path' => array(
          '#markup' => $item['path'],
        ),
        'group' => array(
          '#markup' => $item['group'],
        ),
        'machine_name' => array(
          '#markup' => $item['machine_name'],
        ),
        'icon_library' => array(
          '#markup' => $icon_libs[$item['icon_library']]['title'],
        ),
        'edit' => array(
          '#markup' => l('edit', 'admin/config/user-interface/cis-lmsless-nav/edit-link/' . $item_key),
        ),
        'delete' => array(
          '#markup' => l('delete', 'admin/config/user-interface/cis-lmsless-nav/delete-link/' . $item_key),
        ),
        'id' => array(
          '#type' => 'hidden',
          '#default_value' => $item_key,
        ),
        // The 'weight' field will be manipulated as we move the items around in
        // the table using the tabledrag activity.  We use the 'weight' element
        // defined in Drupal's Form API.
        'weight' => array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#default_value' => $item_key,
          '#delta' => 10,
          '#title_display' => 'invisible',
        ),
        // We'll use a hidden form element to pass the current 'depth' of each
        // item within our parent/child tree structure to the theme function.
        // This will be used to calculate the initial amount of indentation to
        // add before displaying any child item rows.
        'depth' => array(
          '#type' => 'hidden',
          '#value' => 0,
        ),
      );
    }

    // Now we add our submit button, for submitting the form results.
    //
    // The 'actions' wrapper used here isn't strictly necessary for tabledrag,
    // but is included as a Form API recommended practice.
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));

    return $form;
  }
  else {
    return $form;
  }
}

/**
 * Style the LMSless icon table form.
 */
function theme_cis_lmsless_nav_parent_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = array();

  // Iterate over each element in our $form['links'] array.
  foreach (element_children($form['links']) as $id) {
    // add specific class to the weight field for table draggable
    $form['links'][$id]['weight']['#attributes']['class'] = array('cis_lmsless_weight');
    $class = array('draggable');

    // If this is a child element, we need to add some indentation to the row,
    // so that it appears nested under its parent.  Our $depth parameter was
    // calculated while building the tree in tabledrag_example_parent_get_data
    $indent = theme('indentation', array('size' => $form['links'][$id]['depth']['#value']));
    unset($form['links'][$id]['depth']);

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = array(
      'data' => array(
        // Add our 'name' column, being sure to include our indentation.
        $indent . drupal_render($form['links'][$id]['title']),
        // Add our 'description' column.
        drupal_render($form['links'][$id]['path']),
        // Add our 'weight' column.
        drupal_render($form['links'][$id]['group']),
        // Add our hidden 'id' column.
        drupal_render($form['links'][$id]['machine_name']),
        // Add our hidden 'parent id' column.
        drupal_render($form['links'][$id]['icon_library']),
        drupal_render($form['links'][$id]['edit']),
        drupal_render($form['links'][$id]['delete']),
        drupal_render($form['links'][$id]['weight']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      'class' => $class,
    );
  }

  $header = array(t('title'), t('path'), t('group'), t('machine_name'), t('icon_library'), t('edit'), t('delete'), t('weight'));
  $table_id = 'example-items-table';
  // add link to add new links
  $output = l('Add new link', 'admin/config/user-interface/cis-lmsless-nav/add-link');
  // We can render our tabledrag table for output.
  $output .= theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // And then render any remaining form elements (such as our submit button).
  $output .= drupal_render_children($form);
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'cis_lmsless_weight', NULL, NULL, FALSE);

  return $output;
}

/**
 * [cis_lmsless_nav_parent_form_submit description]
 * @param  [type] $form        [description]
 * @param  [type] &$form_state [description]
 * @return [type]              [description]
 */
function cis_lmsless_nav_parent_form_submit($form, &$form_state) {
  $origin_links = variable_get('cis_lmsless_nav_links', array());
  $sort_array = array_keys($form_state['input']['links']);
  $new_array = array();

  foreach ($sort_array as $id) {
    if (isset($origin_links[$id])) {
      $new_array[] = $origin_links[$id];
    }
  }
  // save this locally and network wide
  _cis_lmsless_set_nav($new_array);
}