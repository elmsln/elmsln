<?php
$view = new view;
$view->name = 'questions_by_quiz';
$view->description = 'View of all the questions associated with a quiz';
$view->tag = 'quiz';
$view->view_php = '';
$view->base_table = 'quiz_node_properties';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'parent_vid' => array(
    'label' => 'node',
    'required' => 1,
    'id' => 'parent_vid',
    'table' => 'quiz_node_relationship',
    'field' => 'parent_vid',
    'relationship' => 'none',
  ),
  'child_vid' => array(
    'label' => 'question node revision',
    'required' => 0,
    'id' => 'child_vid',
    'table' => 'quiz_node_relationship',
    'field' => 'child_vid',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'child_nid' => array(
    'label' => 'Question Node ID',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'set_precision' => FALSE,
    'precision' => 0,
    'decimal' => '.',
    'separator' => '',
    'prefix' => '',
    'suffix' => '',
    'exclude' => 1,
    'id' => 'child_nid',
    'table' => 'quiz_node_relationship',
    'field' => 'child_nid',
    'relationship' => 'none',
  ),
  'title' => array(
    'label' => 'Question Title',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 1,
      'path' => 'node/[child_nid]',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node_revision',
    'field' => 'title',
    'relationship' => 'child_vid',
  ),
  'type' => array(
    'label' => 'Question Type',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'link_to_node' => 0,
    'exclude' => 0,
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'child_vid',
  ),
  'question_status' => array(
    'label' => 'Question Status',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
    ),
    'type' => 'yes-no',
    'not' => 0,
    'exclude' => 0,
    'id' => 'question_status',
    'table' => 'quiz_node_relationship',
    'field' => 'question_status',
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'nid' => array(
    'default_action' => 'not found',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => 'Questions',
    'breadcrumb' => '',
    'default_argument_type' => 'fixed',
    'default_argument' => '',
    'validate_type' => 'node',
    'validate_fail' => 'not found',
    'break_phrase' => 0,
    'not' => 0,
    'which_vid' => 'latest',
    'id' => 'nid',
    'table' => 'quiz_node_properties',
    'field' => 'nid',
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(
      '2' => 0,
      '3' => 0,
    ),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '',
    'validate_argument_node_type' => array(
      'quiz' => 'quiz',
      'certificate' => 0,
      'long_answer' => 0,
      'matching' => 0,
      'multichoice' => 0,
      'quiz_directions' => 0,
      'scale' => 0,
      'short_answer' => 0,
      'truefalse' => 0,
      'page' => 0,
      'story' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(),
    'validate_argument_type' => 'tid',
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
    'validate_argument_php' => '',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('use_ajax', TRUE);
$handler->override_option('use_pager', 'mini');
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => 'parent_vid',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'timestamp' => 'parent_nid',
    'title' => 'title',
    'type' => 'type',
    'child_nid' => 'child_nid',
    'child_vid' => 'child_vid',
    'question_status' => 'question_status',
    'parent_nid' => 'timestamp',
    'parent_vid' => 'parent_vid',
  ),
  'info' => array(
    'timestamp' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'title' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'type' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'child_nid' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'child_vid' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'question_status' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'parent_nid' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'parent_vid' => array(
      'sortable' => 0,
      'separator' => '',
    ),
  ),
  'default' => 'title',
));
$handler = $view->new_display('page', 'Questions by Specific Quiz', 'page_1');
$handler->override_option('path', 'admin/quiz/questions_by_quiz/%');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => 'Questions by Quiz',
  'description' => '',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
));
$handler = $view->new_display('page', 'Page', 'page_2');
$handler->override_option('path', 'admin/quiz/%/questions');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
));
