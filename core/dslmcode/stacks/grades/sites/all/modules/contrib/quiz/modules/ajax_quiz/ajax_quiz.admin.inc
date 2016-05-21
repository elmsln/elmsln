<?php


/* @file
 * ajax quiz admin page
 */

/*
 * @function
 * callback for ajax quiz menu
 * @return
 * HTML quiz description
 */
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function ajax_quiz_instruction($node) {
  // If this is an AJAX request, return the AJAX result.
  if (isset($_REQUEST['ajax_load_example']) && $_REQUEST['ajax_load_example']) {
    _ajax_quiz_get_questions($node);
  }
  else {
    drupal_add_js(drupal_get_path('module', 'ajax_quiz') . '/ajax_quiz.js');
    $output = '<div class="ajax-quiz-wrapper">';
    $output .= '<div class="ajax-quiz-description">' . $node->body . '</div>';
    $output .= '<div class="ajax-quiz-start">' . l(t('Start'), $_GET['q'], array('attributes' => array('class' => 'ajax-load-example'))) . '</div>';
    $output .= '</div>';
    return $output;
  }
}

function _ajax_quiz_get_questions($node) {
  $output = '';
  foreach (drupal_get_messages() as $type) {
    foreach ($type as $message) {
      $output .= '<script type="text/javascript"> alert("' . "$type : $message" . '"); </script>';
    }
  }
  $output .= node_view($node, FALSE, TRUE);
  $result = array(
    'content' => $output,
    // Put the Javascript callback you will use here.
    // You can if you wish leave out this line and instead
    // call your callback directly in your Javascript. See
    // comments in ajax_load_example.js.
    '__callbacks' => array('Drupal.AjaxLoadExample.formCallback'),
  );
  // Call drupal_alter('ajax_data', ...). This is what allows ajax_load to
  // add its data and register its Javascript callback.
  // The second argument is the data to be altered.
  // The third argument is a unique identifier for this AJAX data operation.
  // The fourth and optional argument is the original data that was the subject
  // of the ajax operation--in this case, a form ID.
  drupal_alter('ajax_data', $result, 'ajax_load_example', 'node_view');
  drupal_json_output($result);
}

