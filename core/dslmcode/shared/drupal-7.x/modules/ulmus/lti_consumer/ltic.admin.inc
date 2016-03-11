<?php

/**
 * @return array
 */
function ltic_resource_info_page() {
  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('A resource type'),
  );
  if (user_access('administer entity_example_basic entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.', array('!link' => l(t('here'), 'admin/structure/entity_example_basic/manage'))
    );
  }
  $content['table'] = ltic_resource_list_entities();

  return $content;
}

/**
 * Callback to list ltic_resource entities. 
 * @return array
 */
function ltic_resource_list_entities() {
  $content = [];
  // Load all of our entities.
  $entities = ltic_resource_load_multiple();
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      // Create tabular rows for our entities.
      $rows[] = [
        'data' => [
          'id' => $entity->ltic_resource_id,
          'item_description' => l($entity->ltic_resource_link_description, 'ltic/ltic_resource/basic/' . $entity->ltic_resource_id),
        //'bundle' => $entity->bundle_type,
        ],
      ];
    }
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = [
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => [t('ID'), t('Resource Description')],
    ];
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No entity_example_basic entities currently exist.'),
    );
  }
  return $content;
}

/**
 * @return array
 */
function ltic_context_info_page() {
  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('A context entity'),
  );
  if (user_access('administer entity_example_basic entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.', array('!link' => l(t('here'), 'admin/structure/entity_example_basic/manage'))
    );
  }
  $content['table'] = ltic_context_list_entities();

  return $content;
}

/**
 * Callback to list ltic_context entities.
 * @return array
 */
function ltic_context_list_entities() {
  $content = array();
  // Load all of our entities.
  $entities = ltic_context_load_multiple();
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      // Create tabular rows for our entities.
      $rows[] = array(
        'data' => array(
          'id' => $entity->ltic_context_id,
          'item_description' => l($entity->ltic_context_title, 'ltic/ltic_context/basic/' . $entity->ltic_context_id),
        //'bundle' => $entity->bundle_type,
        ),
      );
    }
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('ID'), t('Context Title')),
    );
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No entity_example_basic entities currently exist.'),
    );
  }
  return $content;
}

/**
 * Menu callback to display an entity.
 *
 * As we load the entity for display, we're responsible for invoking a number
 * of hooks in their proper order.
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 * @see hook_entity_view_alter()
 */
function ltic_context_view($entity, $view_mode = 'tweaky') {
  // Our entity type, for convenience.
  $entity_type = 'ltic_context';
  // Start setting up the content.
  $entity->content = array(
    '#view_mode' => $view_mode,
  );
  // Build fields content - this is where the Field API really comes in to play.
  // The task has very little code here because it all gets taken care of by
  // field module.
  // field_attach_prepare_view() lets the fields load any data they need
  // before viewing.
  field_attach_prepare_view($entity_type, array($entity->ltic_context_id => $entity), $view_mode);
  // We call entity_prepare_view() so it can invoke hook_entity_prepare_view()
  // for us.
  entity_prepare_view($entity_type, array($entity->ltic_context_id => $entity));
  // Now field_attach_view() generates the content for the fields.
  $entity->content += field_attach_view($entity_type, $entity, $view_mode);

  // OK, Field API done, now we can set up some of our own data.
  $entity->content['created'] = array(
    '#type' => 'item',
    '#title' => t('Created date'),
    '#markup' => format_date($entity->created),
  );
  $entity->content['ltic_context_title'] = array(
    '#type' => 'item',
    '#title' => t('Context Title'),
    '#markup' => $entity->ltic_context_title,
  );

  // Now to invoke some hooks. We need the language code for
  // hook_entity_view(), so let's get that.
  global $language;
  $langcode = $language->language;
  // And now invoke hook_entity_view().
  module_invoke_all('entity_view', $entity, $entity_type, $view_mode, $langcode);
  // Now invoke hook_entity_view_alter().
  drupal_alter(array('ltic_context_view', 'entity_view'), $entity->content, $entity_type);
  // And finally return the content.
  return $entity->content;
}

/**

 * @param stdClass $entity
 * @return strings
 */
function ltic_context_basic_title($entity) {
  return t('@item_description', array('@item_description' => $entity->ltic_context_title));
}

/**
 * Provides a wrapper on the edit form to add a new entity.
 */
function ltic_context_basic_add() {
  // Create a basic entity structure to be used and passed to the validation
  // and submission functions.
  $entity = entity_get_controller('ltic_context')->create();
  return drupal_get_form('ltic_context_basic_form', $entity);
}

/**
 * Menu callback to display an entity.
 *
 * As we load the entity for display, we're responsible for invoking a number
 * of hooks in their proper order.
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 * @see hook_entity_view_alter()
 */
function ltic_resource_view($entity, $view_mode = 'tweaky') {
//  echo '<pre>';
//  var_dump($entity);
//  echo '</pre>';
  // Our entity type, for convenience.
  $entity_type = 'ltic_resource';
  // Start setting up the content.
  $entity->content = array(
    '#view_mode' => $view_mode,
  );
  // Build fields content - this is where the Field API really comes in to play.
  // The task has very little code here because it all gets taken care of by
  // field module.
  // field_attach_prepare_view() lets the fields load any data they need
  // before viewing.
  field_attach_prepare_view($entity_type, array($entity->ltic_resource_id => $entity), $view_mode);
  // We call entity_prepare_view() so it can invoke hook_entity_prepare_view()
  // for us.
  entity_prepare_view($entity_type, array($entity->ltic_resource_id => $entity));
  // Now field_attach_view() generates the content for the fields.
  $entity->content += field_attach_view($entity_type, $entity, $view_mode);

  // OK, Field API done, now we can set up some of our own data.
  $entity->content['created'] = array(
    '#type' => 'item',
    '#title' => t('Created date'),
    '#markup' => format_date($entity->created),
  );
  $entity->content['ltic_resource_link_description'] = array(
    '#type' => 'item',
    '#title' => t('Resource description'),
    '#markup' => $entity->ltic_resource_link_description,
  );

  // Now to invoke some hooks. We need the language code for
  // hook_entity_view(), so let's get that.
  global $language;
  $langcode = $language->language;
  // And now invoke hook_entity_view().
  module_invoke_all('entity_view', $entity, $entity_type, $view_mode, $langcode);
  // Now invoke hook_entity_view_alter().
  drupal_alter(array('ltic_resource_view', 'entity_view'), $entity->content, $entity_type);

  // And finally return the content.
  return $entity->content;
}

function ltic_resource_basic_title($entity) {
  return t('@item_description', array('@item_description' => $entity->ltic_resource_link_title));
}

/**
 * Provides a wrapper on the edit form to add a new entity.
 */
function ltic_resource_basic_add() {
  // Create a basic entity structure to be used and passed to the validation
  // and submission functions.
  $entity = entity_get_controller('ltic_resource')->create();
  return drupal_get_form('ltic_resource_basic_form', $entity);
}

/**
 * Form function to create an ltic_context entity.
 */
function ltic_context_basic_form($form, &$form_state, $entity) {

  $form['ltic_context_id_ref'] = array(
    '#type' => 'textfield',
    '#title' => t('Context ID'),
    '#required' => TRUE,
    '#default_value' => $entity->ltic_context_id_ref,
  );
  $form['ltic_context_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Context title'),
    '#required' => TRUE,
    '#default_value' => $entity->ltic_context_title,
  );
  $form['ltic_context_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Context label'),
    '#required' => TRUE,
    '#default_value' => $entity->ltic_context_label,
  );
  $form['ltic_lis_course_section_sourcedid'] = array(
    '#type' => 'textfield',
    '#title' => t('Course Section ID'),
    '#default_value' => $entity->ltic_lis_course_section_sourcedid,
  );

  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );

  field_attach_form('ltic_context', $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );

  //if its new dont show delete
  if ($entity->ltic_context_id != 0) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ltic_context_basic_edit_delete'),
      '#attributes' => [
        'onclick' => 'return confirm("Are you sure you want to delete this context?")',
      ],
      '#weight' => 200,
    );
  }

  return $form;
}

/**
 * Validation handler for ltic_context_basic_form form.
 */
function ltic_context_basic_form_validate($form, &$form_state) {
  field_attach_form_validate('ltic_context', $form_state['values']['basic_entity'], $form, $form_state);
}

/**
 * Form submit handler: Submits basic_add_form information.
 */
function ltic_context_basic_form_submit($form, &$form_state) {
  $entity = $form_state['values']['basic_entity'];
  $entity->ltic_context_id_ref = $form_state['values']['ltic_context_id_ref'];
  $entity->ltic_context_title = $form_state['values']['ltic_context_title'];
  $entity->ltic_context_label = $form_state['values']['ltic_context_label'];
  $entity->ltic_lis_course_section_sourcedid = $form_state['values']['ltic_lis_course_section_sourcedid'];
  field_attach_submit('ltic_context', $entity, $form, $form_state);
  $entity = ltic_context_save($entity);
  $form_state['redirect'] = 'ltic/ltic_context/basic/' . $entity->ltic_context_id;
}

function ltic_context_basic_edit_delete($form, &$form_state) {
  $entity = $form_state['values']['basic_entity'];
  ltic_context_delete($entity);
  drupal_set_message(t('The entity %item_description (ID %id) has been deleted', array('%item_description' => $entity->ltic_context_title, '%id' => $entity->ltic_context_id))
  );
  $form_state['redirect'] = 'admin/structure/ltic_context/manage';
}

function ltic_context_delete($entity) {
  entity_get_controller('ltic_context')->delete($entity);
}

/**
 * Form function to create an ltic_context_basic entity.
 */
function ltic_resource_basic_form($form, &$form_state, $entity) {
  $form['ltic_resource_link_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Resource link title'),
    '#required' => TRUE,
    '#default_value' => $entity->ltic_resource_link_title,
  );
  $form['ltic_resource_link_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Resource Description'),
    '#required' => TRUE,
    '#default_value' => $entity->ltic_resource_link_description,
  );

  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );

  field_attach_form('ltic_resource', $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  //if its new dont show delete
  if ($entity->ltic_resource_id != 0) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ltic_resource_basic_edit_delete'),
      '#attributes' => [
        'onclick' => 'return confirm("Are you sure you want to delete this resource?")',
      ],
      '#weight' => 200,
    );
  }

  return $form;
}

/**
 * Validation handler for ltic_resource_basic_form form.
 */
function ltic_resource_basic_form_validate($form, &$form_state) {
  field_attach_form_validate('ltic_resource', $form_state['values']['basic_entity'], $form, $form_state);
}

/**
 * Form submit handler: Submits ltic_resource_basic_form information.
 */
function ltic_resource_basic_form_submit($form, &$form_state) {
  $entity = $form_state['values']['basic_entity'];
  $entity->ltic_resource_link_title = $form_state['values']['ltic_resource_link_title'];
  $entity->ltic_resource_link_description = $form_state['values']['ltic_resource_link_description'];
//Think this needs removing
  field_attach_submit('entity_example_basic', $entity, $form, $form_state);
  $entity = ltic_resource_save($entity);
  $form_state['redirect'] = 'ltic/ltic_resource/basic/' . $entity->ltic_resource_id;
}

function ltic_resource_basic_edit_delete($form, &$form_state) {
  $entity = $form_state['values']['basic_entity'];
  ltic_resource_delete($entity);
  drupal_set_message(t('The entity %item_description (ID %id) has been deleted', array('%item_description' => $entity->ltic_resource_link_title, '%id' => $entity->ltic_resource_id))
  );
  $form_state['redirect'] = 'admin/structure/ltic_resource/manage';
}

function ltic_resource_delete($entity) {
  entity_get_controller('ltic_resource')->delete($entity);
}
