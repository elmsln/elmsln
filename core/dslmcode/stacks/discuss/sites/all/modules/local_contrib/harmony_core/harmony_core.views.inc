<?php

/**
 * @file
 * Provide additional Views fields for entity content.
 */

/**
 * Implements hook_views_data_alter().
 *
 * We need to use this hook instead of hook_views_data() as
 * entity API already provides data for our custom entity type.
 */
function harmony_core_views_data_alter(&$data) {
  // General fields & things.
  $data['views']['harmony_listing_header'] = array(
    'title' => t('Harmony listing header'),
    'help' => t('Listing header which provides a link to add a new thread.'),
    'area' => array(
      'handler' => 'harmony_core_views_handler_area_add_thread',
    ),
  );

  $data['views']['reverse_counter'] = array(
    'title' => t('View result reverse counter'),
    'group' => t('Harmony'),
    'help' => t('Displays the actual position of the view result, reversed.'),
    'field' => array(
      'handler' => 'harmony_core_views_handler_field_reverse_counter',
    ),
  );

  // Extra Threads fields.
  $data['harmony_thread']['thread_id'] = array(
    'title' => t('Thread ID'),
    'help' => t('The internal ID of the thread.'),
    'relationship' => array(
      'title' => t('Thread ID'),
      'base' => 'harmony_thread',
      'field' => 'thread_id',
      'label' => t('thread'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['harmony_thread']['view_link'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the thread.'),
      'handler' => 'harmony_core_views_handler_thread_field_link',
    ),
  );
  $data['harmony_thread']['edit_link'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the thread.'),
      'handler' => 'harmony_core_views_handler_thread_field_link_edit',
    ),
  );
  $data['harmony_thread']['delete_link'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a simple link to delete the thread.'),
      'handler' => 'harmony_core_views_handler_thread_field_link_delete',
    ),
  );
  $data['harmony_thread']['reply_link'] = array(
    'field' => array(
      'title' => t('Reply to thread link'),
      'help' => t('Provide a link to the reply form for the thread.'),
      'handler' => 'harmony_core_views_handler_thread_field_reply_link',
    ),
  );
  // Provide taxonomy with representative thread.
  /*$data['taxonomy_term_data']['tid_representative_thread'] = array(
    'relationship' => array(
      'title' => t('Representative thread'),
      'label'  => t('Representative thread'),
      'help' => t('Obtains a single representative thread for each term, according to a chosen sort criterion.'),
      'handler' => 'views_handler_relationship_groupwise_max',
      'relationship field' => 'tid',
      'outer field' => 'taxonomy_term_data.tid',
      'argument table' => 'taxonomy_term_data',
      'argument field' =>  'tid',
      'base'   => 'harmony_thread',
      'field'  => 'thread_id',
    ),
  );
  // Provide user with representative thread.
  $data['users']['uid_representative_thread'] = array(
    'relationship' => array(
      'title' => t('Representative thread'),
      'label'  => t('Representative thread'),
      'help' => t('Obtains a single representative thread for each user, according to a chosen sort criterion.'),
      'handler' => 'views_handler_relationship_groupwise_max',
      'relationship field' => 'uid',
      'outer field' => 'users.uid',
      'argument table' => 'users',
      'argument field' =>  'uid',
      'base'   => 'harmony_thread',
      'field'  => 'thread_id',
    ),
  );*/

  // Override the title field slightly to use our custom views field handler
  // which has the "link to thread" functionality.
  $data['harmony_thread']['title']['field']['handler'] = 'harmony_core_views_handler_thread_field';

  $data['harmony_thread']['last_post_uri'] = array(
    'field' => array(
      'title' => t('Last post URI'),
      'help' => t('Provides a path to the last post within the thread (can be used in rewriting with replacements).'),
      'handler' => 'harmony_core_views_handler_thread_field_last_post_uri',
    ),
  );

  $data['harmony_thread']['term_thread_tid_depth'] = array(
    'help' => t('Display thread if it has the selected taxonomy terms, or children of the selected terms. Due to additional complexity, this has fewer options than the versions without depth.'),
    'real field' => 'thread_id',
    'argument' => array(
      'title' => t('Category (with depth)'),
      'handler' => 'harmony_core_views_handler_argument_default_taxonomy_tid_depth',
      'accept depth modifier' => TRUE,
    ),
  );

  // Provide a field which shows number of replies to a thread which is post
  // count - 1.
  $data['field_data_field_harmony_post_count']['harmony_thread_replies'] = array(
    'group' => t('Thread'),
    'title' => t('Number of replies to Thread'),
    'help' => t('The number of replies to a thread, which will be thread post count -1, with supporting text. E.g. "1 reply".'),
    'field' => $data['field_data_field_harmony_post_count']['field_harmony_post_count']['field'],
  );
  $data['field_data_field_harmony_post_count']['harmony_thread_replies']['field']['handler'] = 'harmony_core_views_handler_thread_field_replies';

  // ----------------------------------------------------------------------
  // History table

  // We're actually defining a specific instance of the table, so let's
  // alias it so that we can later add the real table for other purposes if we
  // need it.
  $data['harmony_thread_read_history_user']['moved to'] = 'harmony_thread_read_history';
  $data['harmony_thread_read_history']['table']['group']  = t('Thread');

  // Explain how this table joins to others.
  $data['harmony_thread_read_history']['table']['join'] = array(
     // Directly links to node table.
    'harmony_thread' => array(
      'table' => 'harmony_thread_read_history',
      'left_field' => 'thread_id',
      'field' => 'thread_id',
      'extra' => array(
        array('field' => 'uid', 'value' => '***CURRENT_USER***', 'numeric' => TRUE),
      ),
    ),
  );

  $data['harmony_thread_read_history']['timestamp'] = array(
    'title' => t('Thread new/updated'),
    'field' => array(
      'help' => t('Show a marker if the content is new or updated.'),
      'handler' => 'harmony_core_views_handler_field_thread_read_history_timestamp',
    ),
    'filter' => array(
      'help' => t('Show only content that is new or updated.'),
      'handler' => 'harmony_core_views_handler_filter_thread_read_history_timestamp',
    ),
  );

  // Post ID.
  $data['harmony_post']['post_id'] = array(
    'title' => t('Post ID'),
    'help' => t('The internal ID of the post revision.'),
    'relationship' => array(
      'title' => t('Post ID'),
      'base' => 'harmony_post',
      'field' => 'post_id',
      'label' => t('post'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Add in post vid.
  $data['harmony_post']['vid'] = array(
    'title' => t('Current revision ID'),
    'help' => t('The internal ID of the post.'),
    'relationship' => array(
      'title' => t('Current revision'),
      'base' => 'harmony_post_revision',
      'field' => 'vid',
      'label' => t('revision'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Extra Post entity fields.
  $data['harmony_post']['view_link'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the post.'),
      'handler' => 'harmony_core_views_handler_post_field_link',
    ),
  );
  $data['harmony_post']['edit_link'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the post.'),
      'handler' => 'harmony_core_views_handler_post_field_link_edit',
    ),
  );
  $data['harmony_post']['delete_link'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a simple link to delete the post.'),
      'handler' => 'harmony_core_views_handler_post_field_link_delete',
    ),
  );
  // Quick view post content link.
  $data['harmony_post']['post_view_text'] = array(
    'field' => array(
      'title' => t('Link to view or AJAX load the posts text'),
      'help' => t('Provide a link to view the content of the post in a modal window if JavaScript is enabled.'),
      'handler' => 'harmony_core_views_handler_post_field_view_text',
    ),
  );

  // Override the title field slightly to use our custom views field handler
  // which has the "link to post" functionality.
  $data['harmony_post']['title']['field']['handler'] = 'harmony_core_views_handler_post_field';

  // Custom field handler to provide a posts position within a thread, we need
  // the thread id so we copy that handler for the most part to grab that data.
  $data['harmony_post']['position'] = array(
    'field' => array(
      'title' => t('Position in thread'),
      'help' => t('The position of the post within the thread it belongs to. Not recommended for listings which show posts from multiple threads or long lists of posts.'),
      'handler' => 'harmony_core_views_handler_post_field_position',
    ),
  );

  // Define the post revision table, relationship and fields.
  $data['harmony_post_revision'] = array(
    'table' => array(
      'base' => array(
        'field' => 'vid',
        'title' => t('Post entity revisions'),
        'help' => t('Revisions for post entities.'),
      ),
      'group' => t('Post (historical data)'),
      'entity type' => 'harmony_post',
    ),
    'post_id' => array(
      'title' => t('Post ID'),
      'help' => t('The post entity this is a revision for.'),
      'relationship' => array(
        'title' => t('Post entity'),
        'base' => 'harmony_post',
        'field' => 'post_id',
        'label' => t('post'),
      ),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'vid' => array(
      'title' => t('Revision ID'),
      'help' => t('The internal ID of the revision.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'title' => array(
      'title' => t('Title'),
      'help' => t('The content title of the this revision of the entity.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'timestamp' => array(
      'title' => t('Created date'),
      'help' => t('The date the entity was created.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
    'log' => array(
      'title' => t('Log message'),
      'help' => t('The message provided for the revision.'),
      'field' => array(
        'handler' => 'views_handler_field_xss',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'hostname' => array(
      'title' => t('Hostname'),
      'help' => t('The hostname or IP address from where the revision was created.'),
      'field' => array(
        'handler' => 'views_handler_field_xss',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'uid' => array(
      'title' => t('Author UID'),
      'help' => t('The user authoring the revision. If you need more fields from the author, add the Author relationship.'),
      'relationship' => array(
        'title' => t('Author'),
        'help' => t('Relate the revision to the user who created it.'),
        'handler' => 'views_handler_relationship',
        'base' => 'users',
        'field' => 'uid',
        'label' => t('author'),
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_name',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'field' => array(
        'handler' => 'views_handler_field_user',
      ),
    ),
    'view_revision' => array(
      'field' => array(
        'title' => t('Administrative link'),
        'help' => t('Provide a simple link for administrators to view the content.'),
        'handler' => 'harmony_core_views_handler_post_field_view_revision',
      ),
    ),
    'delete_revision' => array(
      'field' => array(
        'title' => t('Administrative delete link'),
        'help' => t('Provide a simple link for administrators to delete the content.'),
        'handler' => 'harmony_core_views_handler_post_field_delete_revision',
      ),
    ),
    'is_current' => array(
      'field' => array(
        'title' => t('Is current'),
        'help' => t('Determine if this is the current revision for the entity.'),
        'handler' => 'harmony_core_views_handler_post_field_is_current',
      ),
    ),
    'make_current' => array(
      'field' => array(
        'title' => t('Administrative set current revision link'),
        'help' => t('Provide a simple link for administrators to delete the content.'),
        'handler' => 'harmony_core_views_handler_post_field_make_current',
      ),
    ),
    'view_diff' => array(
      'field' => array(
        'title' => t('Link to view or AJAX load the post differences'),
        'help' => t('Provide a link for users who have permission, to view a diff of a revision.'),
        'handler' => 'harmony_core_views_handler_post_field_view_diff',
      ),
    ),
  );
}

/**
 * Implements hook_views_plugins().
 */
function harmony_core_views_plugins() {
  $module_dir = drupal_get_path('module', 'harmony_core');

  return array(
    'module' => 'harmony_core',
    'row' => array(
      'harmony_post' => array(
        'title' => t('Harmony'),
        'help' => t('Display the content with standard post view.'),
        'handler' => 'harmony_core_views_plugin_row_harmony_post_view',
        'base' => array('harmony_post'),
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'argument default' => array(
      'harmony_thread_id' => array(
        'title' => t('Thread ID from URL'),
        'handler' => 'harmony_core_views_plugin_argument_default_thread'
      ),
      'harmony_post_id' => array(
        'title' => t('Post ID from URL'),
        'handler' => 'harmony_core_views_plugin_argument_default_post'
      ),
      'harmony_thread_taxonomy_tid' => array(
        'title' => t('Taxonomy term ID from thread page'),
        'handler' => 'harmony_core_views_plugin_argument_default_taxonomy_tid',
        'parent' => 'fixed',
      ),
    ),
    'style' => array(
      'harmony_table' => array(
        'title' => t('Harmony Responsive Table'),
        'help' => t('Displays rows in a responsive table.'),
        'handler' => 'harmony_core_views_plugin_style_harmony_table',
        'theme' => 'views_view_harmony_table',
        'path' => $module_dir . '/theme',
        'theme path' => $module_dir . '/theme',
        'theme file' => 'theme.inc',
        'uses row plugin' => FALSE,
        'uses row class' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
