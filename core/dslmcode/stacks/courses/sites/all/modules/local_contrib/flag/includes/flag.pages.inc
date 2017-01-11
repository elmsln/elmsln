<?php

/**
 * @file
 * Menu callbacks for the Flag module.
 */

/**
 * Menu callback for (un)flagging a node.
 *
 * Used both for the regular callback as well as the JS version.
 *
 * @param $action
 *   The action about to be performed. One of 'flag' or 'unflag'.
 * @param $flag
 *   The flag object.
 * @param $entity_id
 *   The ID of the entity to be acted upon. The type is implicit in the flag.
 */
function flag_page($action, $flag, $entity_id) {
  global $user;

  // Shorten up the variables that affect the behavior of this page.
  $js = isset($_REQUEST['js']);
  $token = $_REQUEST['token'];

  // Specifically $_GET to avoid getting the $_COOKIE variable by the same key.
  $has_js = isset($_GET['has_js']);

  // Check the flag token, and then javascript status.
  if (!flag_check_token($token, $entity_id)) {
    $flag->errors['token'] = t('Bad token. You seem to have followed an invalid link.');
  }
  elseif ($user->uid == 0 && !$has_js) {
    $flag->errors['javascript'] = t('You must have JavaScript and cookies enabled in your browser to flag content.');
  }

  // If no errors have been detected thus far, perform the flagging.
  // Further errors may still be detected during validation and prevent
  // the operation from succeeding.
  if (!$flag->errors) {
    $flag->flag($action, $entity_id);
  }

  // If successful, return data according to the request type.
  if ($js) {
    drupal_add_http_header('Content-Type', 'text/javascript; charset=utf-8');
    $flag->link_type = 'toggle';
    // Any errors that have been set will be output below
    // the flag link with javascript.
    print drupal_json_encode(flag_build_javascript_info($flag, $entity_id));
    drupal_exit();
  }
  else {
    $errors = $flag->get_errors();
    if ($errors) {
      // If an error was received, set a message and exit.
      foreach ($errors as $error) {
        drupal_set_message($error, 'error');
      }
      if (isset($errors['access-denied'])) {
        return MENU_ACCESS_DENIED;
      }
      else {
        drupal_goto();
      }
    }
    else {
      drupal_set_message($flag->get_label($action . '_message', $entity_id));
      drupal_goto();
    }
  }
}

/**
 * Form for confirming the (un)flagging of an entity.
 *
 * @param string $action
 *   Either 'flag' or 'unflag'.
 * @param flag_flag $flag
 *   A loaded flag object.
 * @param int $entity_id
 *   The id of the entity to operate on. The type is implicit in the flag.
 *
 * @see flag_confirm_submit()
 */
function flag_confirm($form, &$form_state, $action, $flag, $entity_id) {
  $form['#flag'] = $flag;
  $form['action'] = array(
    '#type' => 'value',
    '#value' => $action,
  );
  $form['entity_id'] = array(
    '#type' => 'value',
    '#value' => $entity_id,
  );

  $question = $flag->get_label($action . '_confirmation', $entity_id);
  $path = isset($_GET['destination']) ? $_GET['destination'] : '<front>';
  $yes = strip_tags($flag->get_label($action . '_short', $entity_id));

  if ($action == 'flag') {
    // If the action 'flag', we're potentially about to create a new
    // flagging entity. We need an empty new entity to pass to FieldAPI.
    $flagging = $flag->new_flagging($entity_id);
    field_attach_form('flagging', $flagging, $form, $form_state);
    $form['#flagging'] = $flagging;

    // Take the same approach as Core entity forms: shove all the entity
    // properties into the form as values so that entity_form_field_validate()
    // can build a pseudoentity from $form_values in the validate handler.
    foreach (array(
      'flag_name',
      'entity_type',
      'entity_id',
      'uid',
    ) as $key) {
      $form[$key] = array(
        '#type' => 'value',
        '#value' => isset($flagging->$key) ? $flagging->$key : NULL,
      );
    }
  }

  return confirm_form($form, $question, $path, '', $yes);
}

/**
 * Validate handler for the flag confirm form.
 *
 * Validate any Field API fields on the Flagging.
 *
 * @see flag_confirm()
 */
function flag_confirm_validate($form, &$form_state) {
  // Only validate the entity fields when we're saving an entity.
  $action = $form_state['values']['action'];
  if ($action == 'flag') {
    entity_form_field_validate('flagging', $form, $form_state);
  }
}

/**
 * Submit handler for the flag confirm form.
 *
 * Note that validating whether the user may perform the action is done here,
 * rather than in a form validation handler.
 *
 * @see flag_confirm()
 */
function flag_confirm_submit(&$form, &$form_state) {
  $flag = $form['#flag'];
  $action = $form_state['values']['action'];
  $entity_id = $form_state['values']['entity_id'];

  if ($action == 'flag') {
    // If the action 'flag', further build up the new entity from form values.
    $flagging = $form['#flagging'];
    entity_form_submit_build_entity('flagging', $flagging, $form, $form_state);

    $result = $flag->flag($action, $entity_id, NULL, FALSE, $flagging);
  }
  else {
    $result = $flag->flag($action, $entity_id, NULL, FALSE);
  }

  if (!$result) {
    if ($errors = $flag->get_errors()) {
      foreach ($errors as $error) {
        drupal_set_message($error, 'error');
      }
    }
  }
  else {
    drupal_set_message($flag->get_label($action . '_message', $entity_id));
  }
}

/**
 * Builds the JavaScript structure describing the flagging operation.
 */
function flag_build_javascript_info($flag, $entity_id) {
  $errors = $flag->get_errors();
  $info = array(
    'status' => TRUE,
    'newLink' => $flag->theme($flag->is_flagged($entity_id) ? 'unflag' : 'flag', $entity_id, array(
      'after_flagging' => TRUE,
      'errors' => $errors,
    )),
    // Further information for the benefit of custom JavaScript event handlers:
    'flagSuccess' => !$errors,
    'contentId' => $entity_id,
    'entityType' => $flag->entity_type,
    'flagName' => $flag->name,
    'flagStatus' => $flag->is_flagged($entity_id) ? 'flagged' : 'unflagged',
  );
  drupal_alter('flag_javascript_info', $info, $flag);
  return $info;
}
