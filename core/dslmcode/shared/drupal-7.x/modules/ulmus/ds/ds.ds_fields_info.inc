<?php

/**
 * @file
 * Display Suite fields.
 */

/**
 * Implements hook_ds_fields_info().
 */
function ds_ds_fields_info($entity_type) {

  /* --------------------------------------------------------------
     Custom fields.
    -------------------------------------------------------------- */

  ctools_include('export');
  $custom_fields = ctools_export_crud_load_all('ds_fields');
  foreach ($custom_fields as $key => $field) {
    if (isset($field->entities[$entity_type])) {
      $fields[$entity_type][$key] = array(
        'title' => $field->label,
        'field_type' => $field->field_type,
        'properties' => $field->properties,
      );
      if (!empty($field->ui_limit)) {
        $lines = explode("\n", $field->ui_limit);
        $fields[$entity_type][$key]['ui_limit'] = $lines;
      }
    }
  }

  /* --------------------------------------------------------------
     General node fields.
    -------------------------------------------------------------- */

  // Node title.
  $fields['node']['title'] = array(
    'title' => t('Title'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'ds_render_field',
    'properties' => array(
      'entity_render_key' => 'title',
      'settings' => array(
        'link' => array('type' => 'select', 'options' => array('no', 'yes')),
        'wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')),
        'class' => array('type' => 'textfield', 'description' => t('Put a class on the wrapper. Eg: block-title')),
      ),
      'default' => array('wrapper' => 'h2', 'link' => 0, 'class' => ''),
    )
  );

  // Links.
  $fields['node']['links'] = array(
    'title' => t('Links'),
    'field_type' => DS_FIELD_TYPE_IGNORE,
  );

  // Comments.
  if (module_exists('comment')) {
    $fields['node']['comments'] = array(
      'title' => t('Comments'),
      'field_type' => DS_FIELD_TYPE_IGNORE,
      'ui_limit' => array(
        '*|full', '*|default',
      ),
    );
  }

  // Node link.
  $fields['node']['node_link'] = array(
    'title' => t('Read more'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'ds_render_field',
    'properties' => array(
      'settings' => array(
        'link text' => array('type' => 'textfield'),
        'link class' => array('type' => 'textfield', 'description' => t('Put a class on the link. Eg: btn btn-default')),
        'wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')),
        'class' => array('type' => 'textfield', 'description' => t('Put a class on the wrapper. Eg: block-title')),
      ),
      'default' => array('link text' => 'Read more', 'link class' => '', 'wrapper' => '', 'class' => '', 'link' => 1),
    )
  );

  // Author.
  $fields['node']['author'] = array(
    'title' => t('Author'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'ds_render_author_field',
    'properties' => array(
      'formatters' => array(
        'author' => t('Author'),
        'author_linked' => t('Author linked to profile')
      ),
    ),
  );

  // Created time.
  $format_types = system_get_date_types();
  $date_formatters = array();
  foreach ($format_types as $formatter) {
    $date_formatters['ds_post_date_' . $formatter['type']] = t($formatter['title']);
  }
  $fields['node']['post_date'] = array(
    'title' => t('Post date'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'ds_render_date_field',
    'properties' => array(
      'formatters' => $date_formatters,
      'entity_render_key' => 'created',
    ),
  );

  // Updated time.
  $fields['node']['changed_date'] = array(
    'title' => t('Last modified'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'ds_render_date_field',
    'properties' => array(
      'formatters' => $date_formatters,
      'entity_render_key' => 'changed',
    ),
  );

  // "Submitted by"-line. Skip this if the "Submitted By" module is used.
  if (!module_exists('submitted_by')) {
    $date_formatters = array('ds_time_ago' => t('Time ago')) + $date_formatters;
    $fields['node']['submitted_by'] = array(
      'title' => t('Submitted by'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'ds_render_submitted_by',
      'properties' => array(
        'formatters' => $date_formatters,
      ),
    );
  }

  // User picture
  if (variable_get('user_pictures', 0)) {
    $key = 'user_picture';
    $type = DS_FIELD_TYPE_IGNORE;
    $picture_formatters = array();
    if (module_exists('image')) {
      $key = 'ds_user_picture';
      $type = DS_FIELD_TYPE_FUNCTION;
      $styles = image_styles();
      foreach ($styles as $formatter) {
        $picture_formatters['ds_picture_' . $formatter['name']] = drupal_ucfirst(str_replace('_', ' ', $formatter['name']));
      }
    }
    else {
      $picture_formatters['default'] = t('Default');
    }
    $fields['node'][$key] = array(
      'title' => t('User picture'),
      'field_type' => $type,
      'properties' => array(
        'formatters' => $picture_formatters,
      ),
    );
    if ($type == DS_FIELD_TYPE_FUNCTION) {
      $fields['node'][$key]['function'] = 'ds_render_user_picture';
    }
  }

  /* --------------------------------------------------------------
     Book support.
    -------------------------------------------------------------- */

  if (module_exists('book')) {

    $ui_limit = array();
    $types = variable_get('book_allowed_types', array('book'));
    foreach ($types as $type) {
      $ui_limit[] = $type . '|full';
    }

    if (!empty($ui_limit)) {
      $fields['node']['book_navigation'] = array(
        'title' => t('Book navigation'),
        'field_type' => DS_FIELD_TYPE_IGNORE,
        'ui_limit' => $ui_limit,
      );
    }
  }

  /* --------------------------------------------------------------
     Comment support.
    -------------------------------------------------------------- */

  if (module_exists('comment')) {

    // Comment Links.
    $fields['comment']['links'] = array(
      'title' => t('Links'),
      'field_type' => DS_FIELD_TYPE_IGNORE,
    );

    // Created time.
    $format_types = system_get_date_types();
    $date_formatters = array();
    foreach ($format_types as $formatter) {
      $date_formatters['ds_post_date_' . $formatter['type']] = t($formatter['title']);
    }
    $fields['comment']['post_date'] = array(
      'title' => t('Post date'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'ds_render_date_field',
      'properties' => array(
        'formatters' => $date_formatters,
        'entity_render_key' => 'created',
      ),
    );

    // Permalink.
    $fields['comment']['permalink'] = array(
      'title' => t('Permalink'),
      'field_type' => DS_FIELD_TYPE_PREPROCESS,
    );

    // Submitted.
    $fields['comment']['submitted'] = array(
      'title' => t('Submitted'),
      'field_type' => DS_FIELD_TYPE_PREPROCESS,
    );

    // Title.
    $fields['comment']['title'] = array(
      'title' => t('Title'),
      'field_type' => DS_FIELD_TYPE_PREPROCESS,
    );

    // Author.
    $fields['comment']['author'] = array(
      'title' => t('Author'),
      'field_type' => DS_FIELD_TYPE_PREPROCESS,
    );

    // User signature.
    if (variable_get('user_signatures', 0)) {
      $fields['comment']['signature'] = array(
        'title' => t('User signature'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      );
    }

    // User picture
    if (variable_get('user_pictures', 0)) {
      $key = 'picture';
      $type = DS_FIELD_TYPE_PREPROCESS;
      $picture_formatters = array();
      if (module_exists('image')) {
        $key = 'ds_user_picture';
        $type = DS_FIELD_TYPE_FUNCTION;
        $styles = image_styles();
        foreach ($styles as $formatter) {
          $picture_formatters['ds_picture_' . $formatter['name']] = drupal_ucfirst(str_replace('_', ' ', $formatter['name']));
        }
      }
      else {
        $picture_formatters['default'] = t('Default');
      }
      $fields['comment'][$key] = array(
        'title' => t('User picture'),
        'field_type' => $type,
        'properties' => array(
          'formatters' => $picture_formatters,
        ),
      );
      if ($type == DS_FIELD_TYPE_FUNCTION) {
        $fields['comment'][$key]['function'] = 'ds_render_user_picture';
      }
    }
  }

  /* --------------------------------------------------------------
     User support.
    -------------------------------------------------------------- */

  // Username
  $fields['user']['name'] = array(
    'title' => t('Username'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'ds_render_field',
    'properties' => array(
      'entity_render_key' => 'name',
      'settings' => array(
        'link' => array('type' => 'select', 'options' => array('no', 'yes')),
        'wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')),
        'class' => array('type' => 'textfield', 'description' => t('Put a class on the wrapper. Eg: block-title')),
      ),
      'default' => array('wrapper' => 'h2', 'link' => 0, 'class' => ''),
    )
  );

  // User signature
  if (variable_get('user_signatures', 0)) {
    $fields['user']['user_signature'] = array(
      'title' => t('User signature'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'ds_render_markup',
      'properties' => array(
        'key' => 'signature',
        'format' => 'signature_format',
      ),
    );
  }

  // User picture
  if (variable_get('user_pictures', 0)) {
    $key = 'user_picture';
    $type = DS_FIELD_TYPE_IGNORE;
    $picture_formatters = array();
    if (module_exists('image')) {
      $key = 'ds_user_picture';
      $type = DS_FIELD_TYPE_FUNCTION;
      $styles = image_styles();
      foreach ($styles as $formatter) {
        $picture_formatters['ds_picture_' . $formatter['name']] = drupal_ucfirst(str_replace('_', ' ', $formatter['name']));
      }
    }
    else {
      $picture_formatters['default'] = t('Default');
    }
    $fields['user'][$key] = array(
      'title' => t('User picture'),
      'field_type' => $type,
      'properties' => array(
        'formatters' => $picture_formatters,
      ),
    );
    if ($type == DS_FIELD_TYPE_FUNCTION) {
      $fields['user'][$key]['function'] = 'ds_render_user_picture';
    }
  }

  /* --------------------------------------------------------------
     Taxonomy support.
    -------------------------------------------------------------- */

  if (module_exists('taxonomy')) {
    // Taxonomy term title.
    $fields['taxonomy_term']['title'] = array(
      'title' => t('Title'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'ds_render_field',
      'properties' => array(
        'entity_render_key' => 'name',
        'settings' => array(
          'link' => array('type' => 'select', 'options' => array('no', 'yes')),
          'wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')),
          'class' => array('type' => 'textfield', 'description' => t('Put a class on the wrapper. Eg: block-title')),
        ),
        'default' => array('wrapper' => 'h2', 'link' => 0, 'class' => ''),
      )
    );

    // Taxonomy term link.
    $fields['taxonomy_term']['more_link'] = array(
      'title' => t('Read more'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'ds_render_field',
      'properties' => array(
        'settings' => array(
          'link text' => array('type' => 'textfield'),
          'wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')),
          'class' => array('type' => 'textfield', 'description' => t('Put a class on the wrapper. Eg: block-title')),
        ),
        'default' => array('link text' => 'Read more', 'wrapper' => '', 'class' => '', 'link' => 1),
      )
    );
  }

  // Support for ECK Entity title
  if (module_exists('eck')) {
    $entity_info = entity_get_info($entity_type);
    if (isset($entity_info['module']) && $entity_info['module'] == 'eck') {
      $fields[$entity_type]['title'] = array(
        'title' => t('Title'),
        'field_type' => DS_FIELD_TYPE_FUNCTION,
        'function' => 'ds_render_field',
        'properties' => array(
          'entity_render_key' => 'title',
          'settings' => array(
            'link' => array('type' => 'select', 'options' => array('no', 'yes')),
            'wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')),
            'class' => array('type' => 'textfield', 'description' => t('Put a class on the wrapper. Eg: block-title')),
          ),
          'default' => array('wrapper' => 'h2', 'link' => 0, 'class' => ''),
        )
      );
    }
  }

  // Support for fieldable panels panes.
  if (module_exists('fieldable_panels_panes')) {
    $fields['fieldable_panels_pane']['title_ds'] = array(
      'title' => t('Display Suite Title'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'ds_render_field',
      'properties' => array(
        'entity_render_key' => 'title',
        'settings' => array(
          'link' => array('type' => 'select', 'options' => array('no', 'yes')),
          'wrapper' => array('type' => 'textfield', 'description' => t('Eg: h1, h2, p')),
          'class' => array('type' => 'textfield', 'description' => t('Put a class on the wrapper. Eg: block-title')),
        ),
        'default' => array('wrapper' => 'h2', 'link' => 0, 'class' => ''),
      )
    );
  }

  if (isset($fields[$entity_type])) {
    return array($entity_type => $fields[$entity_type]);
  }
  return;
}
