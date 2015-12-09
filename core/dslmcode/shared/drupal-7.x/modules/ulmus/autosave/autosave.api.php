<?php
/**
 * @file
 * API documentation for Autosave module.
 */

/**
 * Implements hook_autosave_prevent_alter().
 *
 * @param $prevent_autosave
 *   Set this to TRUE to prevent autosaving.
 *
 *   More useful parameters are in $_POST.
 */
function hook_autosave_prevent_alter(&$prevent_autosave) {
  $path = $_POST['autosave_form_path'];
  $path_args = explode("/", $path);
  // check if node has just been saved - if it has then it's because AS ajax fired off as user was submitting
  // if it had just been submitted - no need to AS now
  //    - easy to figure out if we are submitting an edit to existing node
  //    - little harder if we have just added a node
  if ($path_args[0] == 'node') {
    // update case
    if (is_numeric($path_args[1])) {
      $submitted = node_load($path_args[1]);
    }
    else {
      // add case
      $submitted = db_query_range("SELECT created AS changed FROM {node} WHERE uid = :uid and type = :type ORDER BY created DESC", 0, 1, array(
        ':uid' => $user->uid,
        ':type' => str_replace("-", "_", $path_args[2])))->fetchObject();
    }
    $prevent_autosave = ($submitted && (REQUEST_TIME - $submitted->changed < variable_get('autosave_period', 10))) ? TRUE : $prevent_autosave;
  }
}
