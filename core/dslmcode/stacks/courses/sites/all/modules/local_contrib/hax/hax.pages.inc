<?php

/**
 * Edit mode callback.
 */

/**
 * Implementation of hook_form().
 */
function hax_page_edit_form($form, $form_state) {
  $node = menu_get_object();
  $form['hax_body'] = array(
    '#type' => 'textfield',
    '#title' => t('body'),
    '#value' => $node->body['und'][0]['value'],
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Submit'),
    '#value' => 'submit'
  );
  return $form;
}

/**
 * Implementation of hook_form_submit().
 */
function hax_page_edit_form_submit($form, $form_state) {
  $node = menu_get_object();
  $node->body['und'][0]['value'] = $form_state['input']['hax_body'];
  node_save($node);
  drupal_set_message(t('Page saved!'), 'status');
}

/**
 * Callback for node/%/authoring
 * @param  object $node drupal node based on id from URI
 * @return string
 */
function hax_page_edit($node) {
  drupal_add_js(drupal_get_path('module', 'hax') . '/js/hax-drag-drop.js');
  drupal_add_css(drupal_get_path('module', 'hax') . '/css/hax.css');
  drupal_add_css('http://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.css');
  // @todo make this more generic then simply the node body field
  $markup = check_markup($node->body['und'][0]['value'], $node->body['und'][0]['format']);
  // quick and dirty substitution, all p/img/iframe tags can be moved
  $markup = str_replace('<p', '<p data-draggable="item"', $markup);
  $markup = str_replace('<img', '<img data-draggable="item"', $markup);
  $markup = str_replace('<iframe', '<iframe data-draggable="item"', $markup);
  // quick and dirty substitution, all div tags are containers
  $markup = str_replace('<div', '<div data-draggable="target"', $markup);
  $output = '<div class="columns hax-accessible hax-body">' . $markup . '</div>';
  // apply the toolbar to the interface
  $output .= _hax_render_toolbar();

  return $output;
}
