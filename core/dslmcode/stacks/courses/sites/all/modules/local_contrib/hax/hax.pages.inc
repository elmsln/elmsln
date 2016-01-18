<?php

/**
 * Edit mode callback.
 */

/**
 * Implementation of hook_form().
 */
function hax_page_edit_form($form, $form_state) {
  $node = menu_get_object();
  // allow projects to jump in and implement a wysiwyg for hax to use
  module_invoke_all('hax_inline_editor');
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
  $body = $form_state['input']['hax_body'];
  $search = array('data-draggable="item"','data-draggable="target"','data-hax-processed="true"', 'draggable="true"', 'aria-grabbed="false"', 'tabindex="0"');
  $body = str_replace($search, array(''), $body);
  $node->body['und'][0]['value'] = $body;
  node_save($node);
  drupal_set_message(t('Page saved!'), 'status');
  drupal_goto('node/' . $node->nid);
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

/**
 * Implements hook_form().
 */
function hax_settings_form($form, $form_state) {
  $filters = filter_formats();
  $list = array();
  foreach ($filters as $name => $filter) {
    $list[$name] = $filter->name;
  }
  $form['hax_inline_editor'] = array(
    '#type' => 'select',
    '#title' => t('Inline WYSIWYG'),
    '#description' => t('What editor format do you want to use for HAX inline edit mode?'),
    '#options' => $list,
    '#default_value' => variable_get('hax_inline_editor','filtered_html'),
  );
  return system_settings_form($form);
}
