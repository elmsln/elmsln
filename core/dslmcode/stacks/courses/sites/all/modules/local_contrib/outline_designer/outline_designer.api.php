<?php

// PHP EXAMPLE HOOKS
// examples taken from hidden_nodes implementation
// for adding pure API calls to the operations list (like drag and drop)
// set the title to <<OUTLINE_DESIGNER_API_ONLY>>

/**
 * Implementation of hook_outline_designer_operations().
 */
function hook_outline_designer_operations($type) {
  switch ($type) {
    case 'book': // the type of operation group, outline_designer_book handles book
      $ops = array(
        'hidden_nodes' => array( // the key of this operation
          'title' => t('Hide node'), // title for display in menus
          'icon' => drupal_get_path('module', 'hidden_nodes') .'/images/hidden_node.png', // the icon location for menus
          'callback' => 'hidden_nodes_outline_designer_hide_node', // optional callback to handle the ajax request this button most likely has
        ),
      );
    break;
    default: // default case of a blank array for when other things provide od types
      $ops = array();
    break;
  }
  return $ops;
}

/**
 * Implementation of hook_outline_designer_ops_js().
 */
function hook_outline_designer_ops_js($ajax_path) {
// ajax_path is provided by any sub module implementation of outline designer
// you can include any javascript or css you'd like to be included for this request
// this has a special function to ensure js is loaded in the right order
  drupal_add_js(drupal_get_path('module', 'hidden_nodes') .'/js/hidden_nodes_ops.js', 'footer');
  return 1;
}

/**
 * Implementation of hook_outline_designer_form_overlay().
 */
function hook_outline_designer_form_overlay() {
// an example output of elements for use in the overlay
// try and wrap things in a div at the end like this function does
// class name helps with theming, id helps with targetting to render
  // delete form
  $form['od_hidden_nodes_multiple'] = array(
   '#title' => t('Propagate hidden status'),
   '#id' => 'od_hidden_nodes_multiple',
   '#type' => 'checkbox',
   '#description' => t('Should this status be applied to all child content?'),
   '#weight' => 0,
   '#default_value' => TRUE,
  );
  // hidden status
  $form['od_hidden_nodes_status'] = array(
   '#title' => t('Hide content'),
   '#id' => 'od_hidden_nodes_status',
   '#type' => 'checkbox',
   '#description' => t('Hide this content'),
   '#weight' => 0,
   '#default_value' => FALSE,
  );
  $output = '<div id="od_hidden_nodes" class="od_uiscreen">'. drupal_render($form) .'</div>';
  return $output;
}
/**
 * Helper function to process the ajax callback for hiding a node
 */
function hidden_nodes_outline_designer_hide_node($nid, $multiple, $status) {
// return 0 to trigger a permission error message in the growl system
  return 'whatever info you want to return as the message after processing';
}

// JS - the key name is critical in the outline_designer_ops data object
// there are 3 key'ed function names you need, all are listed below
// {key}, {key}_submit, and {key}_reset
// this steps through rendering the overlay form, submiting it, and clean up
/*
(function ($) {
  // define function for hidden_nodes operation
  Drupal.outline_designer_ops.hidden_nodes = function() {
    $(".od_submit_button").val('Submit');
    // set default state based on whats loaded
    if ($("#node-" + Drupal.settings.outline_designer.activeNid +"-icon").parent().parent().hasClass('node_is_hidden')) {
      $('#od_hidden_nodes_status').attr('checked','checked')
    }
    else {
      $('#od_hidden_nodes_status').removeAttr('checked')
    }
    // function call
    Drupal.outline_designer.render_popup(true);
  };
  // submit handler
  Drupal.outline_designer_ops.hidden_nodes_submit = function() {
    var multiple = $('#od_hidden_nodes_multiple:checked').length;
    var hide_status = $('#od_hidden_nodes_status:checked').length;
    // update database
    Drupal.outline_designer.ajax_call('book', 'hidden_nodes', Drupal.settings.outline_designer.activeNid, multiple, hide_status, null);
  };
  // reset handler
  Drupal.outline_designer_ops.hidden_nodes_reset = function() {
    $("#od_hidden_nodes_multiple").attr("checked", true);
  };
})(jQuery);
*/
