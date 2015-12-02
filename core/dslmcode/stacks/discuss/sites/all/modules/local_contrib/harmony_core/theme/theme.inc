<?php

/**
 * @file
 * theme.inc
 * Base theme functions for Harmony.
 */

/**
 * Display inline diff metadata.
 */
function theme_harmony_post_diff_inline_metadata($variables) {
  $post = $variables['post'];

  $output = '<div class="diff-inline-metadata clear-block">';
  $log = theme('harmony_post_revision_display_log', $variables);
  if ($log) {
    $output .= '<div class="diff-edit-reason diff-inline-legend">' . $log . '</div>';
  }
  $output .= '<div class="diff-inline-legend clear-block">';
  $output .= '<label>' . t('Legend') . '</label>';
  $output .= theme('diff_inline_chunk', array('text' => t('Added'), 'type' => 'add'));
  $output .= theme('diff_inline_chunk', array('text' => t('Changed'), 'type' => 'change'));
  $output .= theme('diff_inline_chunk', array('text' => t('Deleted'), 'type' => 'delete'));
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}

/**
 * Field extra field callback which provides the revision log message
 * if it's filled in and set to display to the user.
 */
function theme_harmony_post_revision_display_log($variables) {
  extract($variables);
  $output = NULL;

  if (trim($post->log) != '' && $post->log_show) {
    $user = user_load($post->revision_uid);
    $text = t('Edited on @date by !editor, @reason', array(
      '@date' => format_date($post->updated, variable_get('harmony_core_date_type', 'medium'), variable_get('harmony_core_date_format', '')),
      '!editor' => theme('username', array('account' => $user)),
      '@reason' => $post->log,
    ));
    $output = '<div class="post-revision-log text-small">' . $text . '</div>';
  }

  return $output;
}

/**
 * Field extra field callback which provides the revision log message
 * if it's filled in and set to display to the user.
 */
function theme_harmony_core_post_display_hostname($variables) {
  $text = t('<strong>Posted from:</strong> !hostname', array(
    '!hostname' => $variables['post']->hostname,
  ));

  return '<div class="post-ip-address text-small">' . $text . '</div>';
}

/**
 * Processes variables for harmony-thread.tpl.php
 */
function template_preprocess_harmony_thread(&$variables) {
  $variables['view_mode'] = $variables['elements']['#view_mode'];
  $variables['thread'] = $variables['elements']['#thread'];
  $thread = $variables['thread'];

  // Flatten the thread object's member fields.
  $variables = array_merge((array) $thread, $variables);

  // Helpful $content variable for templates.
  $variables += array('content' => array());
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }
}

/**
 * Processes variables for harmony-post.tpl.php
 *
 * The $variables array contains the following arguments:
 * - $post
 * - $view_mode
 * - $page
 *
 * @see harmony-post.tpl.php
 */
function template_preprocess_harmony_post(&$variables) {
  $variables['view_mode'] = $variables['elements']['#view_mode'];
  $variables['post'] = $variables['elements']['#post'];
  $post = $variables['post'];
  $lang = !empty($post->language) ? $post->language : LANGUAGE_NONE;

  // Thread data.
  $wrapper = entity_metadata_wrapper('harmony_post', $post);
  $thread_id = $wrapper->field_harmony_thread->value() ? $wrapper->field_harmony_thread->thread_id->value() : NULL;
  if (!$thread_id && !empty($post->field_harmony_thread[$lang][0]['target_id'])) {
    $thread_id = $post->field_harmony_thread[$lang][0]['target_id'];
  }
  $thread_type = $wrapper->field_harmony_thread->value() ? $wrapper->field_harmony_thread->type->value() : NULL;

  // Add in some useful variables.
  $variables['title'] = check_plain($post->title);
  $variables['belongs_to_thread'] = FALSE;
  if ($thread_id) {
    $variables['thread_url'] = url("thread/$thread_id");
    $variables['thread_post_url'] = harmony_core_post_thread_url($thread_id, $post->post_id);
    $variables['belongs_to_thread'] = TRUE;
  }
  $variables['url'] = url("post/$post->post_id");
  $variables['permalink_url'] = $variables['url'];
  $variables['link_created'] = $variables['thread_post_url'] && $post->status == HARMONY_PUBLISHED && $post->hidden != HARMONY_HIDDEN;
  $variables['created'] = format_date($post->created, variable_get('harmony_core_date_type', 'medium'), variable_get('harmony_core_date_format', ''));
  $variables['updated'] = format_date($post->updated, variable_get('harmony_core_date_type', 'medium'), variable_get('harmony_core_date_format', ''));
  $variables['is_page'] = arg(0) === 'post';

  // Flatten the post object's member fields.
  $variables = array_merge((array) $post, $variables);

  // Helpful $content variable for templates.
  $variables += array('content' => array());
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }

  // Add in the user profile, this is controlled via field ui
  // so you can easily add/remove things. Display suite is
  // recommended for as much control as possible.
  if ($post->author) {
    $account = $post->author;
    $user_view = user_view($account, 'harmony_user_post_profile');
    $variables['user_profile'] = drupal_render($user_view);
  }
  else {
    $variables['user_profile'] = theme('harmony_anonymous_user_post_profile');
  }

  // Add the "Direct reply" link.
  $variables['direct_reply'] = NULL;
  if ($wrapper->field_harmony_post_is_reply_to->value()) {
    $replying_to_post_id = $wrapper->field_harmony_post_is_reply_to->post_id->value();
    $user_is_obj = is_object($wrapper->field_harmony_post_is_reply_to->uid->value());
    $replying_to_name = $user_is_obj ? $wrapper->field_harmony_post_is_reply_to->uid->name->value() : variable_get('anonymous', t('Anonymous'));
    $replying_to_post_url = harmony_core_post_thread_url($thread_id, $replying_to_post_id);

    $variables['direct_reply'] = '<a href="' . $replying_to_post_url . '">' . t('In reply to @name', array('@name' => $replying_to_name)) . '</a>';
  }

  // Generate the revisions link if the user has access and there's more
  // than one.
  $variables['revisions'] = NULL;
  if (harmony_core_post_revision_access_callback('view', $post)) {
    $revision_count = db_query('SELECT COUNT(vid) FROM {harmony_post_revision} WHERE post_id = :post_id', array(':post_id' => $post->post_id))->fetchField();
    if ($revision_count > 1) {
      // Reduce the count by one as we don't count the original revision.
      $variables['revisions'] = l(format_plural($revision_count - 1, '1 edit', '@count edits'), "post/$post->post_id/revisions");
    }
  }

  // Make the field variables available with the appropriate language.
  field_attach_preprocess('harmony_post', $post, $variables['content'], $variables);

  // Add in the post classes.
  $variables['classes_array'][] = 'post';
  $variables['classes_array'][] = 'post-' . drupal_html_class($variables['view_mode']);
  if (!$variables['status']) {
    $variables['classes_array'][] = 'post-unpublished';
  }
  if ($variables['locked']) {
    $variables['classes_array'][] = 'post-locked';
  }
  if ($variables['first_post']) {
    $variables['classes_array'][] = 'post-first-in-thread';
  }
  if ($variables['last_post']) {
    $variables['classes_array'][] = 'post-last-in-thread';
  }
  if (!empty($post->field_harmony_post_is_reply_to)) {
    $variables['classes_array'][] = 'post-is-direct-reply';
  }
  if ($variables['is_page']) {
    $variables['classes_array'][] = 'post-page';
  }

  // Suggest some templates, including default? What's going wrong here?
  $variables['theme_hook_suggestions'][] = 'harmony_post';
  $variables['theme_hook_suggestions'][] = 'harmony_post__' . $variables['view_mode'];
  if ($thread_type) {
    $variables['theme_hook_suggestions'][] = "harmony_post__{$thread_type}";
  }
  $variables['theme_hook_suggestions'][] = "harmony_post__{$post->post_id}";

  // Suggest templates for other things like, only post, first post and last
  // post.
  if ($variables['first_post'] && $variables['last_post']) {
    $variables['theme_hook_suggestions'][] = 'harmony_post__only';
  }
  elseif ($variables['first_post']) {
    $variables['theme_hook_suggestions'][] = 'harmony_post__first';
  }
  elseif ($variables['last_post']) {
    $variables['theme_hook_suggestions'][] = 'harmony_post__last';
  }
}

/**
 * Theme the form for the table style plugin
 */
function theme_harmony_core_views_style_plugin_harmony_table_ui($variables) {
  $form = $variables['form'];
  $output = drupal_render($form['description_markup']);

  $header = array(
    t('Field'),
    t('Column'),
    t('Align'),
    t('Separator'),
    array(
      'data' => t('Sortable'),
      'align' => 'center',
    ),
    array(
      'data' => t('Default order'),
      'align' => 'center',
    ),
    array(
      'data' => t('Default sort'),
      'align' => 'center',
    ),
    array(
      'data' => t('Hide empty column'),
      'align' => 'center',
    ),
    array(
      'data' => t('Cell class'),
      'align' => 'center',
    ),
    array(
      'data' => t('Is a Meta field'),
      'align' => 'center',
    ),
  );
  $rows = array();
  foreach (element_children($form['columns']) as $id) {
    $row = array();
    $row[] = check_plain(drupal_render($form['info'][$id]['name']));
    $row[] = drupal_render($form['columns'][$id]);
    $row[] = drupal_render($form['info'][$id]['align']);
    $row[] = drupal_render($form['info'][$id]['separator']);
    if (!empty($form['info'][$id]['sortable'])) {
      $row[] = array(
        'data' => drupal_render($form['info'][$id]['sortable']),
        'align' => 'center',
      );
      $row[] = array(
        'data' => drupal_render($form['info'][$id]['default_sort_order']),
        'align' => 'center',
      );
      $row[] = array(
        'data' => drupal_render($form['default'][$id]),
        'align' => 'center',
      );
    }
    else {
      $row[] = '';
      $row[] = '';
      $row[] = '';
    }
    $row[] = array(
      'data' => drupal_render($form['info'][$id]['empty_column']),
      'align' => 'center',
    );
    $row[] = drupal_render($form['info'][$id]['cell_class']);
    $row[] = array(
      'data' => drupal_render($form['info'][$id]['meta_field']),
      'align' => 'center',
    );
    $rows[] = $row;
  }

  // Add the special 'None' row.
  $rows[] = array(t('None'), '', '', '', '', '', array('align' => 'center', 'data' => drupal_render($form['default'][-1])), '', '', '');

  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Display a view as in the harmony responsive table style.
 */
function template_preprocess_views_view_harmony_table(&$vars) {
  $view = $vars['view'];

  // Add CSS.
  drupal_add_css(drupal_get_path('module', 'harmony_core') . '/css/harmony-core.css');

  // We need the raw data for this grouping, which is passed in as $vars['rows'].
  // However, the template also needs to use for the rendered fields.  We
  // therefore swap the raw data out to a new variable and reset $vars['rows']
  // so that it can get rebuilt.
  // Store rows so that they may be used by further preprocess functions.
  $result = $vars['result'] = $vars['rows'];
  $vars['rows'] = array();
  $vars['field_classes'] = array();
  $vars['header'] = array();

  $options  = $view->style_plugin->options;
  $handler  = $view->style_plugin;

  $default_row_class = isset($options['default_row_class']) ? $options['default_row_class'] : TRUE;
  $row_class_special = isset($options['row_class_special']) ? $options['row_class_special'] : TRUE;

  $fields   = &$view->field;
  $columns  = $handler->sanitize_columns($options['columns'], $fields);

  $active   = !empty($handler->active) ? $handler->active : '';
  $order    = !empty($handler->order) ? $handler->order : 'asc';

  $query    = tablesort_get_query_parameters();
  if (isset($view->exposed_raw_input)) {
    $query += $view->exposed_raw_input;
  }

  // Fields must be rendered in order as of Views 2.3, so we will pre-render
  // everything.
  $renders = $handler->render_fields($result);

  foreach ($columns as $field => $column) {
    // Create a second variable so we can easily find what fields we have and what the
    // CSS classes should be.
    $vars['fields'][$field] = drupal_clean_css_identifier($field);
    if ($active == $field) {
      $vars['fields'][$field] .= ' active';
    }

    // render the header labels
    if ($field == $column && empty($fields[$field]->options['exclude'])) {
      $label = check_plain(!empty($fields[$field]) ? $fields[$field]->label() : '');
      if (empty($options['info'][$field]['sortable']) || !$fields[$field]->click_sortable()) {
        $vars['header'][$field] = $label;
      }
      else {
        $initial = !empty($options['info'][$field]['default_sort_order']) ? $options['info'][$field]['default_sort_order'] : 'asc';

        if ($active == $field) {
          $initial = ($order == 'asc') ? 'desc' : 'asc';
        }

        $title = t('sort by @s', array('@s' => $label));
        if ($active == $field) {
          $label .= theme('tablesort_indicator', array('style' => $initial));
        }

        $query['order'] = $field;
        $query['sort'] = $initial;
        $link_options = array(
          'html' => TRUE,
          'attributes' => array('title' => $title),
          'query' => $query,
        );
        $vars['header'][$field] = l($label, $_GET['q'], $link_options);
      }

      $vars['header_classes'][$field] = '';
      // Set up the header label class.
      if ($fields[$field]->options['element_default_classes']) {
        $vars['header_classes'][$field] .= "views-field views-field-" . $vars['fields'][$field];
      }
      $class = $fields[$field]->element_label_classes(0);
      if ($class) {
        if ($vars['header_classes'][$field]) {
          $vars['header_classes'][$field] .= ' ';
        }
        $vars['header_classes'][$field] .= $class;
      }
      // Add a CSS align class to each field if one was set
      if (!empty($options['info'][$field]['align'])) {
        $vars['header_classes'][$field] .= ' ' . drupal_clean_css_identifier($options['info'][$field]['align']);
      }
      // Add a CSS align cell class to each field if one was set.
      if (!empty($options['info'][$field]['cell_class'])) {
        $vars['header_classes'][$field] .= ' ' . drupal_clean_css_identifier($options['info'][$field]['cell_class']);
      }
      // Add a header label wrapper if one was selected.
      if ($vars['header'][$field]) {
        $element_label_type = $fields[$field]->element_label_type(TRUE, TRUE);
        if ($element_label_type) {
          $vars['header'][$field] = '<' . $element_label_type . '>' . $vars['header'][$field] . '</' . $element_label_type . '>';
        }
      }

    }

    // Render each field into its appropriate column.
    foreach ($result as $num => $row) {
      // Add field classes
      $vars['field_classes'][$field][$num] = 'tl-cell';
      if (!empty($options['info'][$column]['meta_field']) && $options['info'][$column]['meta_field'] === 1) {
        $vars['field_classes'][$field][$num] .= ' tl-meta';
      }
      // Add a CSS align class to each field if one was set.
      if (!empty($options['info'][$field]['align'])) {
        $vars['field_classes'][$field][$num] .= ' ' . drupal_clean_css_identifier($options['info'][$field]['align']);
      }
      // Add a CSS align cell class to each field if one was set.
      if (!empty($options['info'][$field]['cell_class'])) {
        $vars['field_classes'][$field][$num] .= ' ' . drupal_clean_css_identifier($options['info'][$field]['cell_class']);
      }
      if (!empty($fields[$field]->options['element_default_classes'])) {
        $vars['field_classes'][$field][$num] .= ' views-field views-field-' . $vars['fields'][$field];
      }
      if ($classes = $fields[$field]->element_classes($num)) {
        if ($vars['field_classes'][$field][$num]) {
          $vars['field_classes'][$field][$num] .= ' ';
        }

        $vars['field_classes'][$field][$num] .= $classes;
      }
      $vars['field_attributes'][$field][$num] = array();

      if (!empty($fields[$field]) && empty($fields[$field]->options['exclude'])) {
        $field_output = $renders[$num][$field];
        $element_type = $fields[$field]->element_type(TRUE, TRUE);
        if ($element_type) {
          $field_output = '<' . $element_type . '>' . $field_output . '</' . $element_type . '>';
        }

        // Don't bother with separators and stuff if the field does not show up.
        if (empty($field_output) && !empty($vars['rows'][$num][$column])) {
          continue;
        }

        // Place the field into the column, along with an optional separator.
        if (!empty($vars['rows'][$num][$column])) {
          if (!empty($options['info'][$column]['separator'])) {
            $vars['rows'][$num][$column] .= filter_xss_admin($options['info'][$column]['separator']);
          }
        }
        else {
          $vars['rows'][$num][$column] = '';
        }

        $vars['rows'][$num][$column] .= $field_output;
      }
    }

    // Remove columns if the option is hide empty column is checked and the field is not empty.
    if (!empty($options['info'][$field]['empty_column'])) {
      $empty = TRUE;
      foreach ($vars['rows'] as $num => $columns) {
        $empty &= empty($columns[$column]);
      }
      if ($empty) {
        foreach ($vars['rows'] as $num => &$column_items) {
          unset($column_items[$column]);
          unset($vars['header'][$column]);
        }
      }
    }
  }

  // Hide table header if all labels are empty.
  if (!array_filter($vars['header'])) {
    $vars['header'] = array();
  }

  $count = 0;
  foreach ($vars['rows'] as $num => $row) {
    $vars['row_classes'][$num] = array();
    if ($row_class_special) {
      $vars['row_classes'][$num][] = ($count++ % 2 == 0) ? 'odd' : 'even';
    }
    if ($row_class = $handler->get_row_class($num)) {
      $vars['row_classes'][$num][] = $row_class;
    }
  }

  if ($row_class_special) {
    $vars['row_classes'][0][] = 'views-row-first';
    $vars['row_classes'][count($vars['row_classes']) - 1][] = 'views-row-last';
  }

  $vars['classes_array'] = array(
    'table-list',
    'views-table',
  );
  if (empty($vars['rows']) && !empty($options['empty_table'])) {
    $vars['rows'][0][0] = $view->display_handler->render_area('empty');
    // Calculate the amounts of rows with output.
    $vars['field_attributes'][0][0]['colspan'] = count($vars['header']);
    $vars['field_classes'][0][0] = 'views-empty';
  }


  if (!empty($options['sticky'])) {
    drupal_add_js('misc/tableheader.js');
    $vars['classes_array'][] = "sticky-enabled";
  }
  $vars['classes_array'][] = 'cols-' . count($vars['header']);

  // Add the summary to the list if set.
  if (!empty($handler->options['summary'])) {
    $vars['attributes_array'] = array('summary' => filter_xss_admin($handler->options['summary']));
  }

  // Add the caption to the list if set.
  if (!empty($handler->options['caption'])) {
    $vars['caption'] = filter_xss_admin($handler->options['caption']);
  }
  else {
    $vars['caption'] = '';
  }
}

/**
 * Views listing header.
 */
function theme_harmony_listing_header($variables) {
  $text = $variables['link_text'];
  $attrs = !empty($variables['link_attrs']) && is_array($variables['link_attrs']) ? $variables['link_attrs'] : array();

  return '<div class="harmony-listing-header clearfix">' . l($text, 'thread/add', $attrs) . '</div>';
}

/**
 * Build up the title meta things for a thread.
 */
function theme_harmony_core_thread_meta_wrapper($variables) {
  extract($variables);
  $classes = array('harmony-meta');

  if (isset($in_title) && $in_title) {
    $classes[] = 'harmony-title-meta';
  }

  // Pass along which properties to output.
  $properties_default = array(
    'locked',
    'pinned',
  );
  $properties = variable_get('harmony_core_thread_meta_properties', $properties_default);

  $output = array();
  foreach ($properties as $property) {
    $meta_item = theme('harmony_core_thread_meta_item', array('thread_properties' => $thread_properties, 'property' => $property));

    if ($meta_item) {
      $output[] = $meta_item;
    }
  }

  return !empty($output) ? '<span class="' . implode(' ', $classes) . '">' . implode(' ', $output) . '</span>' : NULL;
}

/**
 * Theme function for an individual property.
 */
function theme_harmony_core_thread_meta_item($variables) {
  $thread_properties = $variables['thread_properties'];
  $property = $variables['property'];
  $output = NULL;
  $classes = array(
    'harmony-meta-item',
    'harmony-thread-' . drupal_html_class($variables['property']),
  );

  if (!empty($thread_properties[$property]) && $thread_properties[$property]) {
    $property_text = harmony_core_meta_get_property('harmony_thread', $property);
    $output = '<span class="' . implode(' ', $classes) . '" title="' . $property_text['help'] . '">' . $property_text['title'] . '</span>';
  }

  return $output;
}

/**
 * Return some markup for a deleted user for use in the post profile area.
 */
function theme_harmony_anonymous_user_post_profile() {
  return '<span class="grey">' . t('Deleted user') . '</span>';
}
