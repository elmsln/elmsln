<?php

/**
 * @file
 * Provides the Display Suite views entity style plugin.
 */

/**
 * Plugin which defines the view mode on the resulting entity object.
 */
class views_plugin_ds_entity_view extends views_plugin_row {

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->base_table = $view->base_table;
    // Special case for apachesolr_views.
    if ($this->base_table == 'apachesolr') {
      $this->base_table = 'node';
    }
    $this->base_field = $this->ds_views_3_support();
  }

  // Return base_field based on base_table. It might not be
  // the cleanest solution, it's the fastest though.
  function ds_views_3_support() {
    if (strpos($this->base_table, 'eck_') === 0) {
      // Base tables of entities created by entity construction kit (eck)
      // are prefixed with 'eck_' and the base field is always 'id'.
      $this->entity_type = str_replace('eck_', '', $this->base_table);
      return 'id';
    }

    $base_table_fields = array(
      'node' => array('field' => 'nid', 'entity_type' => 'node'),
      'comment' => array('field' => 'cid', 'entity_type' => 'comment'),
      'users' => array('field' => 'uid', 'entity_type' => 'user'),
      'apachesolr' => array('field' => 'nid', 'entity_type' => 'node'),
      'taxonomy_term_data' => array('field' => 'tid', 'entity_type' => 'taxonomy_term'),
      'file_managed' => array('field' => 'fid', 'entity_type' => 'file'),
      'micro' => array('field' => 'mid', 'entity_type' => 'micro'),
    );
    $this->entity_type = isset($base_table_fields[$this->base_table]) ? $base_table_fields[$this->base_table]['entity_type'] : 'node';
    return isset($base_table_fields[$this->base_table]) ? $base_table_fields[$this->base_table]['field'] : 'nid';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['view_mode'] = array('default' => 'teaser');
    $options['load_comments'] = array('default' => FALSE);
    $options['alternating'] = array('default' => FALSE);
    $options['changing'] = array('default' => FALSE);
    $options['grouping'] = array('default' => FALSE);
    $options['advanced'] = array('default' => FALSE);
    $options['delta_fieldset'] = array(
      'contains' => array(
        'delta_fields' => array('default' => FALSE),
      ),
    );
    $options['grouping_fieldset'] = array(
      'contains' => array(
        'grouping' => array('default' => FALSE, 'bool' => TRUE),
        'group_field' => array('default' => ''),
        'group_field_function' => array('default' => ''),
      ),
    );
    $options['default_fieldset'] = array(
      'contains' => array(
        'view_mode' => array('default' => ''),
      ),
    );
    $options['switch_fieldset'] = array(
      'contains' => array(
        'switch' => array('default' => FALSE, 'bool' => TRUE),
      ),
    );
    $options['alternating_fieldset'] = array(
      'contains' => array(
        'alternating' => array('default' => FALSE, 'bool' => TRUE),
        'allpages' => array('default' => FALSE, 'bool' => TRUE),
        'item' => array(
          'default' => array(),
          'export' => 'ds_item_export_option',
        ),
      ),
    );
    $options['advanced_fieldset'] = array(
      'contains' => array(
        'advanced' => array('default' => FALSE, 'bool' => TRUE),
      ),
    );
    return $options;
  }

  /**
   * Custom export function for alternating_fieldset items.
   */
  function ds_item_export_option($indent, $prefix, $storage, $option, $definition, $parents) {
    $output = '';
    $definition = array('default' => 'teaser');
    foreach ($storage as $key => $value) {
      if (strstr($key, 'item_') !== FALSE) {
        $output .= parent::export_option($indent, $prefix, $storage, $key, $definition, $parents);
      }
    }
    return $output;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $view_mode_options = array();
    $entity_type = $this->view->base_table;
    // In case we're working with users or managed files, change the entity type variable.
    if ($entity_type == 'users') $entity_type = 'user';
    if ($entity_type == 'file_managed') $entity_type = 'file';
    $entity_view_modes = ds_entity_view_modes($entity_type);
    foreach ($entity_view_modes as $key => $view_mode) {
      $view_mode_options[$key] = $view_mode['label'];
    }

    // Default view mode & load comments.
    $form['default_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Default view mode'),
      '#collapsible' => TRUE,
      '#collapsed' => ($this->options['advanced']),
    );
    $form['default_fieldset']['view_mode'] = array(
      '#type' => 'select',
      '#default_value' => $this->options['view_mode'],
      '#options' => $view_mode_options,
      '#description' => t('Select the default view mode for this view.')
    );
    if ($entity_type == 'node') {
      $form['default_fieldset']['load_comments'] = array(
        '#title' => t('Comments'),
        '#type' => 'checkbox',
        '#description' => t('Load comments for every node to display.'),
        '#default_value' => isset($this->options['load_comments']) ? $this->options['load_comments'] : FALSE,
        '#access' => module_exists('comment'),
      );
    }

    // Use view mode of display settings.
    if ($entity_type == 'node' && variable_get('ds_extras_switch_view_mode', FALSE)) {
      $form['switch_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Use view mode of display settings'),
        '#collapsible' => TRUE,
        '#collapsed' => !$this->options['switch_fieldset']['switch'],
      );
      $form['switch_fieldset']['switch'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use view mode of display settings'),
        '#default_value' => $this->options['switch_fieldset']['switch'],
        '#description' => t('Use the alternative view mode selected in the display settings tab.')
      );
    }

    // Changing view modes.
    $form['alternating_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Alternating view mode'),
      '#collapsible' => TRUE,
      '#collapsed' => !$this->options['alternating'],
    );
    $form['alternating_fieldset']['alternating'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use the changing view mode selector'),
      '#default_value' => $this->options['alternating'],
    );
    $form['alternating_fieldset']['allpages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use this configuration on every page. Otherwhise the default view mode is used as soon you browse away from the first page of this view.'),
      '#default_value' => (isset($this->options['alternating_fieldset']['allpages'])) ? $this->options['alternating_fieldset']['allpages'] : FALSE,
    );

    $limit = $this->view->display_handler->get_option('items_per_page');
    $pager = $this->view->display_handler->get_plugin('pager');
    $limit = (isset($pager->options['items_per_page'])) ? $pager->options['items_per_page'] : 0;
    if ($limit == 0 || $limit > 20) {
      $form['alternating_fieldset']['disabled'] = array(
        '#markup' => t('This option is disabled because you have unlimited items or listing more than 20 items.'),
      );
      $form['alternating_fieldset']['alternating']['#disabled'] = TRUE;
      $form['alternating_fieldset']['allpages']['#disabled'] = TRUE;
    }
    else {
      $i = 1;
      $a = 0;
      while ($limit != 0) {
        $form['alternating_fieldset']['item_' . $a] = array(
          '#title' => t('Item @nr', array('@nr' => $i)),
          '#type' => 'select',
          '#default_value' => (isset($this->options['alternating_fieldset']['item_' . $a])) ? $this->options['alternating_fieldset']['item_' . $a] : 'teaser',
          '#options' => $view_mode_options,
        );
        $limit--;
        $a++;
        $i++;
      }
    }

    // Grouping rows.
    $sorts = $this->view->display_handler->get_option('sorts');
    $groupable = !empty($sorts) && $this->options['grouping'];
    $form['grouping_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group data'),
      '#collapsible' => TRUE,
      '#collapsed' => !$groupable,
    );
    $form['grouping_fieldset']['grouping'] = array(
      '#type' => 'checkbox',
      '#title' => t('Group data on a field. The value of this field will be displayed too.'),
      '#default_value' => $groupable,
    );

    if (!empty($sorts)) {
      $sort_options = array();
      foreach ($sorts as $key => $sort) {
        $sort_name = drupal_ucfirst($sort['field']);
        $sort_options[$sort['table'] . '|' . $sort['field']] = $sort_name;
      }

      $form['grouping_fieldset']['group_field'] = array(
        '#type' => 'select',
        '#options' => $sort_options,
        '#default_value' => isset($this->options['grouping_fieldset']['group_field']) ? $this->options['grouping_fieldset']['group_field'] : '',
      );

      $form['grouping_fieldset']['group_field_function'] = array(
        '#type' => 'textfield',
        '#title' => 'Heading function',
        '#description' => check_plain(t('The value of the field can be in a very raw format (eg, date created). Enter a custom function which you can use to format that value. The value and the object will be passed into that function eg. custom_function($raw_value, $object);')),
        '#default_value' => isset($this->options['grouping_fieldset']['group_field_function']) ? $this->options['grouping_fieldset']['group_field_function'] : '',
      );
    }
    else {
      $form['grouping_fieldset']['grouping']['#disabled'] = TRUE;
      $form['grouping_fieldset']['grouping']['#description'] = t('Grouping is disabled because you do not have any sort fields.');
    }

    // Advanced function.
    $delta_fields = array();
    $field_api_fields = field_info_instances($this->entity_type);
    foreach ($field_api_fields as $bundle => $fields) {
      foreach ($fields as $field_name => $instance_info) {
        $field_info = field_info_field($field_name);
        if ($field_info['cardinality'] != 1) {
          $delta_fields[$field_name] = $field_name;
        }
      }
    }
    $form['delta_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Delta fields'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($this->options['delta_fields']),
    );
    $form['delta_fieldset']['delta_fields'] = array(
      '#type' => 'select',
      '#title' => t('Select fields'),
      '#description' => t('Select fields which "delta" value should be added to the result row. On the manage display of an entity you can decide to look for this delta value to only print that row.'),
      '#options' => $delta_fields,
      '#multiple' => TRUE,
      '#default_value' => !empty($this->options['delta_fields']) ? $this->options['delta_fields'] : '',
    );

    // Advanced function.
    $form['advanced_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced view mode'),
      '#collapsible' => TRUE,
      '#collapsed' => !$this->options['advanced'],
    );
    $form['advanced_fieldset']['advanced'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use the advanced view mode selector'),
      '#description' => t('This gives you the opportunity to have full control of a list for really advanced features.<br /> There is no UI for this, you need to create a function named like this: ds_views_row_adv_@VIEWSNAME($entity, $view_mode, $load_comments).<br />See <a href="http://drupal.org/node/697320#ds_views_row_adv_VIEWSNAME">http://drupal.org/node/697320#ds_views_row_adv_VIEWSNAME</a> for an example.', array('@VIEWSNAME' => $this->view->name)),
      '#default_value' => $this->options['advanced'],
    );
  }

  /**
   * Validate view mode type selector.
   */
  function options_validate(&$form, &$form_state) {
    if (($form_state['values']['row_options']['alternating_fieldset']['alternating'] || $form_state['values']['row_options']['grouping_fieldset']['grouping']) && $form_state['values']['row_options']['advanced_fieldset']['advanced']) {
      form_set_error('advanced', t('You can not have changing/grouping and advanced enabled at the same time'));
    }
  }

  /**
   * Reset all fieldsets except for changing.
   */
  function options_submit(&$form, &$form_state) {
    $form_state['values']['row_options']['load_comments'] = $form_state['values']['row_options']['default_fieldset']['load_comments'];
    $form_state['values']['row_options']['view_mode'] = $form_state['values']['row_options']['default_fieldset']['view_mode'];
    $form_state['values']['row_options']['switch'] = isset($form_state['values']['row_options']['switch_fieldset']) ? $form_state['values']['row_options']['switch_fieldset']['switch'] : FALSE;
    $form_state['values']['row_options']['alternating'] = $form_state['values']['row_options']['alternating_fieldset']['alternating'];
    $form_state['values']['row_options']['grouping'] = $form_state['values']['row_options']['grouping_fieldset']['grouping'];
    $form_state['values']['row_options']['advanced'] = $form_state['values']['row_options']['advanced_fieldset']['advanced'];
    $form_state['values']['row_options']['delta_fields'] = $form_state['values']['row_options']['delta_fieldset']['delta_fields'];
  }

  /**
   * Query method.
   */
  function query() {
    parent::query();
    $this->delta_fields = array();
    $delta_fields = $this->options['delta_fieldset']['delta_fields'];
    if (!empty($delta_fields)) {
      foreach ($delta_fields as $field) {
        $field_name = 'field_data_' . $field;
        $field_name_delta = $field_name . '_delta';
        $this->view->query->add_field($field_name, 'delta');
        $this->delta_fields[$field] = $field_name_delta;
      }
    }
  }

  /**
   * Preload all entities.
   */
  function pre_render($values) {
    $ids = array();
    foreach ($values as $row) {
      $ids[] = $row->{$this->field_alias};
    }

    switch ($this->base_table) {
      case 'node':
        $this->entities = node_load_multiple($ids);
        break;
      case 'comment':
        $this->entities = comment_load_multiple($ids);
        break;
      case 'users':
        $this->entities = user_load_multiple($ids);
        break;
      case 'taxonomy_term_data':
        $this->entities = taxonomy_term_load_multiple($ids);
        if (function_exists('i18n_taxonomy_localize_terms')) {
          global $language;
          foreach($this->entities as $index => &$entity) {
            $entity = i18n_taxonomy_localize_terms($entity, $language->language);
          }
        }
        break;
      case 'file_managed':
        $this->entities = file_load_multiple($ids);
        break;
      case 'micro':
        $this->entities = entity_load($this->base_table, $ids);
        break;
    }
  }

  /**
   * Render each $row.
   */
  function render($row) {

    // Set a variable to indicate if comments need to be loaded or not.
    $load_comments = isset($this->options['load_comments']) ? $this->options['load_comments'] : FALSE;

    // The advanced selector searches for a function called
    // ds_views_row_adv_VIEWSNAME. Return the row immediately.
    if ($this->options['advanced']) {
      $row_function = 'ds_views_row_adv_' . $this->view->name;
      if (function_exists($row_function)) {
        return $row_function($this->entities[$row->{$this->field_alias}], $this->options['view_mode'], $load_comments);
      }
    }

    // Keep a static group array.
    static $grouping = array();
    $view_name = $this->view->name . '_' . $this->view->current_display;
    $group_value_content = '';

    // Default view mode.
    $view_mode = $this->options['view_mode'];

    // Display settings view mode.
    if ($this->options['switch_fieldset']['switch']) {
      if (!empty($this->entities[$row->{$this->field_alias}]->ds_switch)) {
        $view_mode = $this->entities[$row->{$this->field_alias}]->ds_switch;
      }
    }

    // Change the view mode per row.
    if ($this->options['alternating']) {
      // Check for paging to determine the view mode.
      if (isset($_GET['page']) && isset($this->options['alternating_fieldset']['allpages']) && !$this->options['alternating_fieldset']['allpages']) {
        $view_mode = $this->options['view_mode'];
      }
      else {
        $view_mode = isset($this->options['alternating_fieldset']['item_' . $this->view->row_index]) ? $this->options['alternating_fieldset']['item_' . $this->view->row_index] : $this->options['view_mode'];
      }
    }

    // Give modules a chance to alter the $view_mode. Use $view_mode by ref.
    $context = array(
      'entity' => $this->entities[$row->{$this->field_alias}],
      'view_name' => $this->view->name,
      'display' => $this->view->current_display
    );
    drupal_alter('ds_views_view_mode', $view_mode, $context);
    // Call the row render function.
    $content = $this->ds_views_row_render_entity($view_mode, $row, $load_comments);

    // Keep a static grouping for this view.
    if ($this->options['grouping']) {

      $group_field = $this->options['grouping_fieldset']['group_field'];

      // New way of creating the alias.
      if (strpos($group_field, '|') !== FALSE) {
        list($ftable, $ffield) = explode('|', $group_field);
        $group_field = $this->view->sort[$ffield]->table_alias . '_' . $this->view->sort[$ffield]->real_field;
      }

      // Note, the keys in the $row object are cut of at 60 chars.
      // see views_plugin_query_default.inc.
      if (drupal_strlen($group_field) > 60) {
        $group_field = drupal_substr($group_field, 0, 60);
      }

      $raw_group_value = isset($row->{$group_field}) ? $row->{$group_field} : '';
      $group_value = $raw_group_value;
      // Special function to format the heading value.
      if (!empty($this->options['grouping_fieldset']['group_field_function'])) {
        $function = $this->options['grouping_fieldset']['group_field_function'];
        if (function_exists($function)) {
          $group_value = $function($raw_group_value, $this->entities[$row->{$this->field_alias}]);
        }
      }
      if (!isset($grouping[$view_name][$group_value])) {
        $group_value_content = '<h2 class="grouping-title">' . $group_value . '</h2>';
        $grouping[$view_name][$group_value] = $group_value;
      }
    }

    // Grouping.
    if (!empty($grouping[$view_name])) {
      if (!empty($group_value_content)) {
        $content = $group_value_content . $content;
      }
      $content = '<div class="grouping-content">' . $content . '</div>';
    }

    // Return the content.
    return $content;
  }

  /**
   * Render a discrete entity based with the selected view mode.
   *
   * @param $view_mode
   *   The view mode which is set in the Views' options.
   * @param $row
   *   The current active row object being rendered.
   *
   * @return $content
   *   An entity view rendered as HTML
   */
  function ds_views_row_render_entity($view_mode, $row, $load_comments) {

    // Add delta fields if necessary.
    if (!empty($this->delta_fields)) {
      $ds_delta = array();
      foreach ($this->delta_fields as $field_name => $delta_field) {
        $ds_delta[$field_name] = $row->{$delta_field};
      }
      $this->entities[$row->{$this->field_alias}]->ds_delta = $ds_delta;
    }

    $row_function = 'ds_views_row_render_' . $this->base_table;
    $content = $row_function($this->entities[$row->{$this->field_alias}], $view_mode, $load_comments);
    // Allow other modules to modify the entity render array in context.
    $context = array(
      'row' => $row,
      'view' => &$this->view,
      'view_mode' => $view_mode,
      'load_comments' => $load_comments,
    );
    drupal_alter('ds_views_row_render_entity', $content, $context);
    return drupal_render($content);
  }
}

/**
 * Render the node through the entity plugin.
 */
function ds_views_row_render_node($entity, $view_mode, $load_comments) {
  $node_display = node_view($entity, $view_mode);
  if ($load_comments && module_exists('comment')) {
    $node_display['comments'] = comment_node_page_additions($entity);
  }
  return $node_display;
}

/**
 * Render the comment through the entity plugin.
 */
function ds_views_row_render_comment($entity, $view_mode, $load_comments) {
  $node = node_load($entity->nid);
  $element = comment_view($entity, $node, $view_mode);
  return $element;
}

/**
 * Render the user through the entity plugin.
 */
function ds_views_row_render_users($entity, $view_mode, $load_comments) {
  $element = user_view($entity, $view_mode);
  return $element;
}

/**
 * Render the taxonomy term through the entity plugin.
 */
function ds_views_row_render_taxonomy_term_data($entity, $view_mode, $load_comments) {
  $element = taxonomy_term_view($entity, $view_mode);
  return $element;
}

/**
 * Render the file through the entity plugin.
 */
function ds_views_row_render_file_managed($entity, $view_mode, $load_comments) {
  $element = file_view($entity, $view_mode);
  return $element;
}

/**
 * Render the micro through the entity plugin.
 */
function ds_views_row_render_micro($entity, $view_mode, $load_comments) {
  $element = micro_view($entity, $view_mode);
  return $element;
}
