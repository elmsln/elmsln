<?php

function tabledrag_example_parent_form($form_state) {
  // Identify that the elements in 'example_items' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['example_items']['#tree'] = TRUE;

  // Fetch the example data from the database, ordered by parent/child/weight.
  $result = tabledrag_example_parent_get_data();

  // Iterate through each database result.
  foreach ($result as $item) {

    // Create a form entry for this item.
    //
    // Each entry will be an array using the the unique id for that item as
    // the array key, and an array of table row data as the value.
    $form['example_items'][$item->id] = array(

      // We'll use a form element of type '#markup' to display the item name.
      'name' => array(
        '#markup' => $item->name,
      ),

      // We'll use a form element of type '#textfield' to display the item
      // description, to demonstrate that form elements can be included in the
      // table. We limit the input to 255 characters, which is the limit we
      // set on the database field.
      'description' => array(
        '#type' => 'textfield',
        '#default_value' => $item->description,
        '#size' => 20,
        '#maxlength' => 255,
      ),

      // For parent/child relationships, we also need to add form items to
      // store the current item's unique id and parent item's unique id.
      //
      // We would normally use a hidden element for this, but for this example
      // we'll use a disabled textfield element called 'id' so that we can
      // display the current item's id in the table.
      //
      // Because tabledrag modifies the #value of this element, we use
      // '#default_value' instead of '#value' when defining a hidden element.
      // Also, because tabledrag modifies '#value', we cannot use a markup
      // element, which does not support the '#value' property. (Markup
      // elements use the '#markup' property instead.)
      'id' => array(
        // '#type' => 'hidden',
        // '#default_value' => $item->id,
        '#type' => 'textfield',
        '#size' => 3,
        '#default_value' => $item->id,
        '#disabled' => TRUE,
      ),

      // The same information holds true for the parent id field as for the
      // item id field, described above.
      'pid' => array(
        // '#type' => 'hidden',
        // '#default_value' => $item->pid,
        '#type' => 'textfield',
        '#size' => 3,
        '#default_value' => $item->pid,
      ),

      // The 'weight' field will be manipulated as we move the items around in
      // the table using the tabledrag activity.  We use the 'weight' element
      // defined in Drupal's Form API.
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => $item->weight,
        '#delta' => 10,
        '#title_display' => 'invisible',
      ),

      // We'll use a hidden form element to pass the current 'depth' of each
      // item within our parent/child tree structure to the theme function.
      // This will be used to calculate the initial amount of indentation to
      // add before displaying any child item rows.
      'depth' => array(
        '#type' => 'hidden',
        '#value' => $item->depth,
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