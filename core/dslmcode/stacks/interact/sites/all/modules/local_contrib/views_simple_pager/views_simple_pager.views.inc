<?php

/**
 * @file
 * 
 * Views plugin implementations for Views Simple Pager.
 */

/**
 * Implements hook_views_plugins
 */
function views_simple_pager_views_plugins() {
  return array(
    'pager' => array(
      'views_simple_pager' => array(
        'title' => t('Paged output using Views Simple Pager'),
        'short title' => t('Views Simple Pager'),
        'help' => t('Use the Views Simple Pager output.'),
        'handler' => 'views_simple_pager',
        'uses options' => TRUE,
        'parent' => 'full',
      ),
    ),
  );
}

/**
 * The plugin to provide the Views Simple Pager.
 *
 * @ingroup views_pager_plugins
 */
class views_simple_pager extends views_plugin_pager {
  /**
   * Return a string to display as the clickable title for the
   * pager plugin.
   */
  function summary_title() {
    $name = t('Simple pager');
    if (!empty($this->options['offset'])) {
      return format_plural($this->options['items_per_page'], '@name, @count item, skip @skip', '@name, @count items, skip @skip', array('@name' => $name, '@count' => $this->options['items_per_page'], '@skip' => $this->options['offset']));
    }
    return format_plural($this->options['items_per_page'], '@name, @count item', 'Simple pager, @count items', array('@name' => $name, '@count' => $this->options['items_per_page']));
  }

  /**
   * Information about options for all kinds of purposes will be held here.
   * @code
   * 'option_name' => array(
   *  - 'default' => default value,
   *  - 'translatable' => TRUE/FALSE (wrap in t() on export if true),
   *  - 'contains' => array of items this contains, with its own defaults, etc.
   *      If contains is set, the default will be ignored and assumed to
   *      be array()
   *
   *  ),
   *  @endcode
   * Each option may have any of the following functions:
   *  - export_option_OPTIONNAME -- Special export handling if necessary.
   *  - translate_option_OPTIONNAME -- Special handling for translating data
   *    within the option, if necessary.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['items_per_page'] = array('default' => 10);
    $options['offset'] = array('default' => 0);
    $options['id'] = array('default' => 0);
    $options['total_pages'] = array('default' => '');
    $options['prev_label'] = array('default' => 'previous', 'translatable' => TRUE);
    $options['next_label'] = array('default' => 'next', 'translatable' => TRUE);
    $options['reverse_links'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $pager_text = $this->display->handler->get_pager_text();
    $form['items_per_page'] = array(
      '#title' => $pager_text['items per page title'],
      '#type' => 'textfield',
      '#description' => $pager_text['items per page description'],
      '#default_value' => $this->options['items_per_page'],
    );

    $form['offset'] = array(
      '#type' => 'textfield',
      '#title' => t('Offset'),
      '#description' => t('The number of items to skip. For example, if this field is 3, the first 3 items will be skipped and not displayed.'),
      '#default_value' => $this->options['offset'],
    );

    $form['id'] = array(
      '#type' => 'textfield',
      '#title' => t('Pager ID'),
      '#description' => t("Unless you're experiencing problems with pagers related to this view, you should leave this at 0. If using multiple pagers on one page you may need to set this number to a higher value so as not to conflict within the ?page= array. Large values will add a lot of commas to your URLs, so avoid if possible."),
      '#default_value' => $this->options['id'],
    );

    $form['total_pages'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of pages'),
      '#description' => t('The total number of pages. Leave empty to show all pages.'),
      '#default_value' => $this->options['total_pages'],
    );

    $form['prev_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label for "previous" pager link'),
      '#description' => t('The label to use for the traditional "previous" link that traverses towards the top of the list.'),
      '#default_value' => $this->options['prev_label'],
    );

    $form['next_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label for "next" pager link'),
      '#description' => t('The label to use for the traditional "next" link that traverses towards the bottom of the list.'),
      '#default_value' => $this->options['next_label'],
    );

    $form['reverse_links'] = array(
      '#type' => 'checkbox',
      '#title' => t('Reverse placement of "previous" and "next" links'),
      '#description' => t('If checked, this option will reverse the "traditional" link layout (i.e. "next" will come first, then "previous")'),
      '#default_value' => $this->options['reverse_links'],
    );
      }

  /**
   * Provide the default callback for validating options
   */
  function options_validate(&$form, &$form_state) {
    // Make sure our numeric values are excatly that - numeric
    $err_elems = array();
    if (!is_numeric($form_state['values']['pager_options']['items_per_page'])) {
      $err_elems[] = 'pager_options][items_per_page';
    }
    if (!empty($form_state['values']['pager_options']['offset']) && !is_numeric($form_state['values']['pager_options']['offset'])) {
      $err_elems[] = 'pager_options][offset';
    }
    if (!empty($form_state['values']['pager_options']['total_pages']) && !is_numeric($form_state['values']['pager_options']['total_pages'])) {
      $err_elems[] = 'pager_options][total_pages';
    }
    foreach ($err_elems as $el) {
      form_set_error($el, t('Please insert a non-negative integer value'));
    }

    // Make sure our labels are not empty
    // #1941876: Note we are no longer calling filter_xss as check_plain gets called under the hood by the pager link theme functions we leverage elsewhere
    if (empty($form_state['values']['pager_options']['prev_label'])) {
      form_set_error('pager_options][prev_label', t('Previous pager item label cannot be blank'));
    }
    if (empty($form_state['values']['pager_options']['next_label'])) {
      form_set_error('pager_options][next_label', t('Next pager item label cannot be blank'));
    }
  }

  /**
   * Modify the query for paging
   *
   * This is called during the build phase and can directly modify the query.
   */
  function query() {
    $limit = $this->options['items_per_page'];
    $offset = $this->current_page * $this->options['items_per_page'] + $this->options['offset'];
    if (!empty($this->options['total_pages'])) {
      if ($this->current_page >= $this->options['total_pages']) {
        $limit = $this->options['items_per_page'];
        $offset = $this->options['total_pages'] * $this->options['items_per_page'];
      }
    }

    $this->view->query->set_limit($limit);
    $this->view->query->set_offset($offset);
  }

  /**
   * Render the pager.
   *
   * Called during the view render process, this will render the
   * pager.
   *
   * @param $input
   *   Any extra GET parameters that should be retained, such as exposed
   *   input.
   */
  function render($input) {
    $pager_theme = views_theme_functions('views_simple_pager', $this->view, $this->display);
    return theme($pager_theme, array(
      'parameters' => $input, 
      'element' => $this->options['id'],
      'options' => $this->options,
    ));
  }

  /**
   * Set the current page.
   *
   * @param $number
   *   If provided, the page number will be set to this. If NOT provided,
   *   the page number will be set from the global page array.
   */
  function set_current_page($number = NULL) {
    if (isset($number)) {
      $this->current_page = $number;
      return;
    }

    // If the current page number was not specified, extract it from the global
    // page array.
    global $pager_page_array;

    if (empty($pager_page_array)) {
      $pager_page_array = array();
    }

    // Fill in missing values in the global page array, in case the global page
    // array hasn't been initialized before.
    $page = isset($_GET['page']) ? explode(',', $_GET['page']) : array();

    for ($i = 0; $i <= $this->options['id'] || $i < count($pager_page_array); $i++) {
      $pager_page_array[$i] = empty($page[$i]) ? 0 : $page[$i];
    }

    $this->current_page = intval($pager_page_array[$this->options['id']]);

    if ($this->current_page < 0) {
      $this->current_page = 0;
    }
  }

  function get_pager_total() {
    if ($items_per_page = intval($this->get_items_per_page())) {
      return ceil($this->total_items / $items_per_page);
    }
    else {
      return 1;
    }
  }

  /**
   * Update global paging info.
   *
   * This is called after the count query has been run to set the total
   * items available and to update the current page if the requested
   * page is out of range.
   */
  function update_page_info() {
    if (!empty($this->options['total_pages'])) {
      if (($this->options['total_pages'] * $this->options['items_per_page']) < $this->total_items) {
        $this->total_items = $this->options['total_pages'] * $this->options['items_per_page'];
      }
    }

    // Don't set pager settings for items per page = 0.
    $items_per_page = $this->get_items_per_page();
    if (!empty($items_per_page)) {
      // Dump information about what we already know into the globals.
      global $pager_page_array, $pager_total, $pager_total_items, $pager_limits;
      // Set the limit.
      $pager_limits[$this->options['id']] = $this->options['items_per_page'];
      // Set the item count for the pager.
      $pager_total_items[$this->options['id']] = $this->total_items;
      // Calculate and set the count of available pages.
      $pager_total[$this->options['id']] = $this->get_pager_total();

      // See if the requested page was within range:
      if ($this->current_page < 0) {
        $this->current_page = 0;
      }
      elseif ($this->current_page >= $pager_total[$this->options['id']]) {
        // Pages are numbered from 0 so if there are 10 pages, the last page is 9.
        $this->current_page = $pager_total[$this->options['id']] - 1;
      }

      // Put this number in to guarantee that we do not generate notices when the pager
      // goes to look for it later.
      $pager_page_array[$this->options['id']] = $this->current_page;
    }
  }
}
