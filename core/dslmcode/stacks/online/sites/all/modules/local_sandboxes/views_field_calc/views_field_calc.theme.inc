<?php

/**
 * @file
 * An array of preprocessors to fill variables for templates and helper
 * functions to make theming easier.
 */
/**
 * Theme the form for the table style plugin
 */
function theme_views_field_calc_ui_table($variables) {
  $form = $variables['form'];
  $output = drupal_render($form['description_markup']);

  $header = array(
    t('Field'),
    t('Column calculations'),
    t('Column'),
    t('Align'),
    t('Separator'),
    t('Sortable'),
    t('Default Order'),
    t('Default sort'),
  );
  $rows = array();
  foreach (element_children($form['columns']) as $id) {
    $row = array();
    $row[] = drupal_render($form['info'][$id]['name']);
    $row[] = drupal_render($form['info'][$id]['has_calc']) . drupal_render($form['info'][$id]['calc']);
    $row[] = drupal_render($form['columns'][$id]);
    $row[] = drupal_render($form['info'][$id]['align']);
    $row[] = drupal_render($form['info'][$id]['separator']);
    $row[] = drupal_render($form['info'][$id]['sortable']);
    $row[] = drupal_render($form['info'][$id]['default_sort_order']);
    $row[] = drupal_render($form['default'][$id]);
    // Remove the option to hide empty columns.
    // This may create problems since we need to know what
    // the columns are for the summary queries.
    unset($form['info'][$id]['empty_column']);
    $rows[] = $row;
  }

  // Add the special 'None' row.
  $rows[] = array(t('None'), '', '', '', '', '', '', array(
      'align' => 'center',
      'data' => drupal_render($form['default'][-1]),
    ));

  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);
  return $output;
}


/**
 * Display a view as a table style.
 */
function template_preprocess_views_field_calc_table(&$vars) {
  $view     = $vars['view'];

  // We need the raw data for this grouping, which is passed in as $vars['rows'].
  // However, the template also needs to use for the rendered fields.  We
  // therefore swap the raw data out to a new variable and reset $vars['rows']
  // so that it can get rebuilt.
  // Store rows so that they may be used by further preprocess functions.
  $result   = $vars['result'] = $vars['rows'];
  $vars['rows'] = array();
  $vars['field_classes'] = array();

  $options  = $view->style_plugin->options;
  $handler  = $view->style_plugin;

  $fields   = &$view->field;
  $columns  = $handler->sanitize_columns($options['columns'], $fields);

  $active   = !empty($handler->active) ? $handler->active : '';
  $order    = !empty($handler->order) ? $handler->order : 'asc';

  $query    = tablesort_get_query_parameters();

  if (isset($view->exposed_raw_input)) {
    $query += $view->exposed_raw_input;
  }

  $info = $view->style_plugin->options['info'];

  $header = array();

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
          'html' => true,
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
      $class = $fields[$field]->element_label_classes();
      if ($class) {
        if ($vars['header_classes'][$field]) {
          $vars['header_classes'][$field] .= ' ';
        }
        $vars['header_classes'][$field] .= $class;
      }

      // Add a header label wrapper if one was selected.
      if ($vars['header'][$field]) {
        $element_label_type = $fields[$field]->element_label_type(TRUE, TRUE);
        if ($element_label_type) {
          $vars['header'][$field] = '<' . $element_label_type . '>' . $vars['header'][$field] . '</' . $element_label_type . '>';
        }
      }

    }

    // Add a CSS align class to each field if one was set
    if (!empty($options['info'][$field]['align'])) {
      $vars['fields'][$field] .= ' ' . views_css_safe($options['info'][$field]['align']);
    }

    // Render each field into its appropriate column.
    foreach ($result as $num => $row) {
      // Add field classes
      $vars['field_classes'][$field][$num] = '';
      if ($fields[$field]->options['element_default_classes']) {
        $vars['field_classes'][$field][$num] = "views-field views-field-" . $vars['fields'][$field];
      }
      if ($classes = $fields[$field]->element_classes()) {
        if ($vars['field_classes'][$field][$num]) {
          $vars['field_classes'][$field][$num] .= ' ';
        }

        $vars['field_classes'][$field][$num] .= $classes;
      }
      if (!empty($fields[$field]) && empty($fields[$field]->options['exclude'])) {

        $field_output = $renders[$num][$field];
        $element_type = $fields[$field]->element_type(TRUE, TRUE);

        // Get data for each row.
        if ($info[$field]['has_calc']) {
          $types = _views_field_calc_calc_options();
          foreach ($info[$field]['calc'] as $item) {
            if (in_array($item, array_keys($types))) {
              $type = $item;
              $exp = $types[$item];
              break;
            }
          }
          // Add totals.
          $vars['result'][$field][] = $field_output;
          // Save type for this field.
          $vars['calc'][$field] = $type;
        }
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
  }

  // Calculate totals.
  foreach ($columns as $field => $column) {
    if (!empty($fields[$field]) && !$fields[$field]->options['exclude']) {
      if (isset($vars['calc'][$field]) && $calc = $vars['calc'][$field]) {
        $results = $vars['result'][$field];
        $vars['total'][$field] = views_field_calc_total($calc, $results);
      }
      else {
        $vars['total'][$field] = '';
      }
    }
  }

  $count = 0;
  foreach ($vars['rows'] as $num => $row) {
    $vars['row_classes'][$num][] = ($count++ % 2 == 0) ? 'odd' : 'even';
    if ($row_class = $handler->get_row_class($num)) {
      $vars['row_classes'][$num][] = $row_class;
    }
  }

  $vars['row_classes'][0][] = 'views-row-first';
  $vars['row_classes'][count($vars['row_classes']) - 1][] = 'views-row-last';

  $vars['class'] = 'views-table';
  if (!empty($options['sticky'])) {
    drupal_add_js('misc/tableheader.js');
    $vars['class'] .= " sticky-enabled";
  }
  $vars['class'] .= ' cols-' . count($vars['header']);

  $vars['attributes'] = '';
  if (!empty($handler->options['summary'])) {
    $vars['attributes'] = drupal_attributes(array('summary' => $handler->options['summary']));
  }
}
