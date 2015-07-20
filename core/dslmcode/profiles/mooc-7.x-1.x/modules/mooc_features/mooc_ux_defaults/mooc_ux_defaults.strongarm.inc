<?php
/**
 * @file
 * mooc_ux_defaults.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mooc_ux_defaults_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'book_allowed_types';
  $strongarm->value = array(
    0 => 'page',
  );
  $export['book_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'book_child_type';
  $strongarm->value = 'page';
  $export['book_child_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_page';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_page';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_page';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_page';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_page';
  $strongarm->value = '1';
  $export['node_preview_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_page';
  $strongarm->value = 0;
  $export['node_submitted_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'outline_designer_context_menu_exclusion_matrix';
  $strongarm->value = array(
    2 => array(
      'nid' => array(
        'unchecked' => TRUE,
      ),
      'add_content' => array(
        'unchecked' => TRUE,
      ),
      'rename' => array(
        'unchecked' => TRUE,
      ),
      'edit' => array(
        'unchecked' => TRUE,
      ),
      'view' => array(
        'unchecked' => TRUE,
      ),
      'delete' => array(
        'unchecked' => TRUE,
      ),
      'change_type' => array(
        'unchecked' => TRUE,
      ),
      'hidden_nodes' => array(
        'unchecked' => TRUE,
      ),
      'book_title_override' => array(
        'unchecked' => TRUE,
      ),
      'book_copy' => array(
        'unchecked' => TRUE,
      ),
    ),
    5 => array(
      'nid' => array(
        'unchecked' => TRUE,
      ),
      'add_content' => array(
        'unchecked' => TRUE,
      ),
      'rename' => array(
        'unchecked' => TRUE,
      ),
      'edit' => array(
        'unchecked' => TRUE,
      ),
      'view' => array(
        'unchecked' => TRUE,
      ),
      'delete' => array(
        'unchecked' => TRUE,
      ),
      'change_type' => array(
        'unchecked' => TRUE,
      ),
      'hidden_nodes' => array(
        'unchecked' => TRUE,
      ),
      'book_title_override' => array(
        'unchecked' => TRUE,
      ),
      'book_copy' => array(
        'unchecked' => TRUE,
      ),
    ),
    3 => array(
      'nid' => array(
        'unchecked' => TRUE,
      ),
      'add_content' => array(
        'unchecked' => TRUE,
      ),
      'rename' => array(
        'unchecked' => TRUE,
      ),
      'edit' => array(
        'unchecked' => TRUE,
      ),
      'view' => array(
        'unchecked' => TRUE,
      ),
      'delete' => array(
        'unchecked' => TRUE,
      ),
      'change_type' => array(
        'unchecked' => TRUE,
      ),
      'hidden_nodes' => array(
        'unchecked' => TRUE,
      ),
      'book_title_override' => array(
        'unchecked' => TRUE,
      ),
      'book_copy' => array(
        'unchecked' => TRUE,
      ),
    ),
    7 => array(
      'nid' => array(
        'unchecked' => TRUE,
      ),
      'add_content' => array(
        'unchecked' => TRUE,
      ),
      'rename' => array(
        'unchecked' => TRUE,
      ),
      'edit' => array(
        'unchecked' => TRUE,
      ),
      'view' => array(
        'unchecked' => TRUE,
      ),
      'delete' => array(
        'unchecked' => TRUE,
      ),
      'change_type' => array(
        'unchecked' => TRUE,
      ),
      'hidden_nodes' => array(
        'unchecked' => TRUE,
      ),
      'book_title_override' => array(
        'unchecked' => TRUE,
      ),
      'book_copy' => array(
        'unchecked' => TRUE,
      ),
    ),
    8 => array(
      'nid' => array(
        'unchecked' => TRUE,
      ),
      'add_content' => array(
        'unchecked' => TRUE,
      ),
      'rename' => array(
        'unchecked' => TRUE,
      ),
      'edit' => array(
        'unchecked' => TRUE,
      ),
      'view' => array(
        'unchecked' => TRUE,
      ),
      'delete' => array(
        'unchecked' => TRUE,
      ),
      'change_type' => array(
        'unchecked' => TRUE,
      ),
      'hidden_nodes' => array(
        'unchecked' => TRUE,
      ),
      'book_title_override' => array(
        'unchecked' => TRUE,
      ),
      'book_copy' => array(
        'unchecked' => TRUE,
      ),
    ),
    10 => array(
      'nid' => array(
        'unchecked' => TRUE,
      ),
      'add_content' => array(
        'unchecked' => TRUE,
      ),
      'rename' => array(
        'unchecked' => TRUE,
      ),
      'edit' => array(
        'unchecked' => TRUE,
      ),
      'view' => array(
        'unchecked' => TRUE,
      ),
      'delete' => array(
        'unchecked' => TRUE,
      ),
      'change_type' => array(
        'unchecked' => TRUE,
      ),
      'hidden_nodes' => array(
        'unchecked' => TRUE,
      ),
      'book_title_override' => array(
        'unchecked' => TRUE,
      ),
      'book_copy' => array(
        'unchecked' => TRUE,
      ),
    ),
    4 => array(
      'delete' => array(
        'unchecked' => TRUE,
      ),
      'change_type' => array(
        'unchecked' => TRUE,
      ),
      'hidden_nodes' => array(
        'unchecked' => TRUE,
      ),
      'book_title_override' => array(
        'unchecked' => TRUE,
      ),
      'book_copy' => array(
        'unchecked' => TRUE,
      ),
    ),
  );
  $export['outline_designer_context_menu_exclusion_matrix'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tipsy';
  $strongarm->value = array(
    'drupal_forms' => array(
      'forms' => 0,
      'options' => array(
        'fade' => 1,
        'gravity' => 'autoWE',
        'delayIn' => '0',
        'delayOut' => '0',
        'trigger' => 'focus',
        'opacity' => '0.8',
        'offset' => '0',
      ),
    ),
    'custom_selectors' => array(
      0 => array(
        'selector' => '.tipsy',
        'options' => array(
          'fade' => 1,
          'gravity' => 'w',
          'trigger' => 'hover',
          'delayIn' => '0',
          'delayOut' => '0',
          'opacity' => '0.8',
          'offset' => '0',
          'html' => 0,
          'tooltip_content' => array(
            'source' => 'attribute',
            'selector' => 'title',
          ),
        ),
      ),
      1 => array(
        'selector' => '.book-sibling-nav-link',
        'options' => array(
          'fade' => 1,
          'gravity' => 's',
          'trigger' => 'hover',
          'delayIn' => '0',
          'delayOut' => '0',
          'opacity' => '0.8',
          'offset' => '0',
          'html' => 0,
          'tooltip_content' => array(
            'source' => 'attribute',
            'selector' => 'title',
          ),
        ),
      ),
    ),
  );
  $export['tipsy'] = $strongarm;

  return $export;
}
