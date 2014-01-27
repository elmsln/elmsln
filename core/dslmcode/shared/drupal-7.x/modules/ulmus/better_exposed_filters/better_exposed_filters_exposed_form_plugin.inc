<?php
/**
 * @file
 * Provides an Better Exposed Filters exposed form plugin for View 3.x.
 */
class better_exposed_filters_exposed_form_plugin extends views_plugin_exposed_form_basic {

  function summary_title() {
    return t('BEF Settings');
  }

  function option_definition() {
    $options = parent::option_definition();

    // Add Better Exposed Filters options to those saved by Views
    $options['bef'] = array('default' => array());

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $bef_options = array();

    // Get current settings and default values for new filters
    $existing = $this->_bef_get_settings();

    /*
     * Add general options for exposed form items
     */
    $bef_options['general']['allow_secondary'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable secondary exposed form options'),
      '#default_value' => $existing['general']['allow_secondary'],
      '#description' => t('Allows you to specify some exposed form elements as being secondary options and places those elements in a collapsible fieldset. Use this option to place some exposed filters in an "Advanced Search" area of the form, for example.'),
    );
    $bef_options['general']['secondary_label'] = array(
      '#type' => 'textfield',
      '#default_value' => $existing['general']['secondary_label'],
      '#title' => t('Secondary options label'),
      '#description' => t(
        'The name of the fieldset to hold secondary options. This cannot be left blank or there will be no way to show/hide these options.'
      ),
      '#states' => array(
        'required' => array(
          ':input[name="allow_secondary"]' => array('checked' => TRUE),
        ),
      ),
      // Use CTool's #dependency as it adds some margin-left which looks nice.
      // Also, you can't change the required state via #dependency...
      '#dependency' => array('edit-exposed-form-options-bef-general-allow-secondary' => array(1)),
    );

    /*
     * Add options for exposed sorts
     */
    $exposed = FALSE;
    foreach ($this->display->handler->get_handlers('sort') as $label => $sort) {
      if ($sort->options['exposed']) {
        $exposed = TRUE;
        break;
      }
    }
    if ($exposed) {
      $bef_options['sort']['bef_format'] = array(
        '#type' => 'select',
        '#title' => t('Display exposed sort options as'),
        '#default_value' => $existing['sort']['bef_format'],
        '#options' => array(
          'default' => t('Default select list'),
          'bef' => t('Radio Buttons'),
          'bef_links' => t('Links'),
        ),
        '#description' => t('Select a format for the exposed sort options.'),
      );
      $bef_options['sort']['advanced'] = array(
        '#type' => 'fieldset',
        '#title' => t('Advanced sort options'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $bef_options['sort']['advanced']['collapsible'] = array(
        '#type' => 'checkbox',
        '#title' => t('Make sort options collapsible'),
        '#default_value' => $existing['sort']['advanced']['collapsible'],
        '#description' => t(
          'Puts the sort options in a collapsible fieldset'
        ),
      );
      $bef_options['sort']['advanced']['collapsible_label'] = array(
        '#type' => 'textfield',
        '#title' => t('Collapsible fieldset title'),
        '#default_value' => empty($existing['sort']['advanced']['collapsible_label'])
          ? t('Sort options') : $existing['sort']['advanced']['collapsible_label'],
        '#description' => t(
          'This cannot be left blank or there will be no way to show/hide sort options.'
        ),
        '#dependency' => array('edit-exposed-form-options-bef-sort-advanced-collapsible' => array(1)),
      );
      $bef_options['sort']['advanced']['combine'] = array(
        '#type' => 'checkbox',
        '#title' => t('Combine sort order with sort by'),
        '#default_value' => $existing['sort']['advanced']['combine'],
        '#description' => t(
          'Combines the sort by options and order (ascending or decending) into a single list.  Use this to
          display "Option1 (ascending)", "Option1 (descending)", "Option2 (ascending)", "Option2 (descending)"
          in a single form element.'
        ),
      );
      $bef_options['sort']['advanced']['combine_rewrite'] = array(
        '#type' => 'textarea',
        '#title' => t('Rewrite the text displayed'),
        '#default_value' => $existing['sort']['advanced']['combine_rewrite'],
        '#description' => t('
          Use this field to rewrite the text displayed for combined sort options and sort order.
          Use the format of current_value|replacement_value, one replacement per line.
          For example: <pre>
Post date Asc|Oldest first
Post date Desc|Newest first
Title Asc|A -> Z
Title Desc|Z -> A</pre> Leave the replacement value blank to remove an option altogether.
        '),
        '#dependency' => array('edit-exposed-form-options-bef-sort-advanced-combine' => array(1)),
      );
      $bef_options['sort']['advanced']['reset'] = array(
        '#type' => 'checkbox',
        '#title' => t('Include a "Reset sort" option'),
        '#default_value' => $existing['sort']['advanced']['reset'],
        '#description' => t('Adds a "Reset sort" link; Views will use the default sort order.'),
      );
      $bef_options['sort']['advanced']['reset_label'] = array(
        '#type' => 'textfield',
        '#title' => t('"Reset sort" label'),
        '#default_value' => $existing['sort']['advanced']['reset_label'],
        '#description' => t('This cannot be left blank if the above option is checked'),
        '#dependency' => array('edit-exposed-form-options-bef-sort-advanced-reset' => array(1)),
      );
      $bef_options['sort']['advanced']['is_secondary'] = array(
        '#type' => 'checkbox',
        '#title' => t('This is a secondary option'),
        '#default_value' => $existing['sort']['advanced']['is_secondary'],
        '#states' => array(
          'visible' => array(
            ':input[name="allow_secondary"]' => array('checked' => TRUE),
          ),
        ),
        '#description' => t('Places this element in the secondary options portion of the exposed form.'),
      );
    }

    /*
     * Add options for exposed pager
     */
    if (isset($this->display->display_options['pager']) && $this->display->display_options['pager']['options']['expose']['items_per_page']) {
      $bef_options['pager']['bef_format'] = array(
        '#type' => 'select',
        '#title' => t('Display exposed pager options as'),
        '#default_value' => $existing['pager']['bef_format'],
        '#options' => array(
          'default' => t('Default select list'),
          'bef' => t('Radio Buttons'),
          'bef_links' => t('Links'),
        ),
        '#description' => t('Select a format for the exposed pager options.'),
      );
      $bef_options['pager']['is_secondary'] = array(
        '#type' => 'checkbox',
        '#title' => t('This is a secondary option'),
        '#default_value' => $existing['pager']['is_secondary'],
        '#states' => array(
          'visible' => array(
            ':input[name="allow_secondary"]' => array('checked' => TRUE),
          ),
        ),
        '#description' => t('Places this element in the secondary options portion of the exposed form.'),
      );
    }

    // Only add the description text once -- it was getting a little long to be added to
    // each filter
    $bef_filter_intro = FALSE;

    // Go through each filter and add BEF options
    foreach ($this->display->handler->get_handlers('filter') as $label => $filter) {
      if (!$filter->options['exposed']) {
        continue;
      }

      // If we're adding BEF filter options, add an intro to explain what's going on
      if (!$bef_filter_intro) {
        $link = l('BEF settings documentation', 'http://drupal.org/node/1701012');
        $bef_options['bef_intro'] = array(
          '#markup' => '<h3>' . t('Exposed Filter Settings') . '</h3><p>'
            . t('This section lets you select additional options for exposed
                filters. Some options are only available in certain situations.
                If you do not see the options you expect, please see the !link
                page for more details.', array('!link' => $link))
            . '</p>',
        );
        $bef_filter_intro = TRUE;
      }

      // Is this a type of field we can tweak? If so, we'll display additional options.
      $valid = array('in', 'or', 'and');
      $bef_specific = FALSE;

      // We can work with any of these operators
      if (in_array($filter->operator, $valid)) {
        $bef_specific = TRUE;
      }
      // ... or any of these specific filters
      else if (isset($filter->value['type']) && 'date' == $filter->value['type']) {
        // Offer a datepicker option for date fields
        $bef_options[$label]['bef_format'] = array(
          '#type' => 'select',
          '#title' => t('Display "@identifier" exposed filter as', array('@identifier' => $filter->options['expose']['identifier'])),
          '#default_value' => $existing[$label]['bef_format'],
          '#options' => array(
            'default' => t('Default text field'),
            'bef_datepicker' => t('jQuery UI Datepicker'),
          ),
        );
      }
      else if ('yes-no' == $filter->definition['type']) {
        // others?
        $bef_specific = TRUE;
      }
      else {
        // dsm($filter->definition['type']);
      }

      // Main BEF option: default/checkboxes/hidden/etc.
      if ($bef_specific) {
        // Main BEF option: default or radios/checkboxes
        $display_options = array(
          'default' => t('Default select list'),
          'bef' => t('Checkboxes/Radio Buttons'),
        );

        // Taxonomy filters get the "nested" option
        if ($filter instanceof views_handler_filter_term_node_tid) {
          $display_options['bef_ul'] = t('Nested Checkboxes/Radio Buttons');
        }

        // Check for other display options based on the filter
        if ($filter instanceof views_handler_filter_boolean_operator && !$filter->options['expose']['multiple']) {
          $display_options['bef_single'] = t('Single on/off checkbox');
        }

        // Less used options, so put them last.
        $display_options['bef_links'] = t('Links');
        $display_options['bef_hidden'] = t('Hidden');

        $bef_options[$label]['bef_format'] = array(
          '#type' => 'select',
          '#title' => t('Display "@identifier" exposed filter as', array('@identifier' => $filter->options['expose']['identifier'])),
          '#default_value' => $existing[$label]['bef_format'],
          '#options' => $display_options,
        );
      }

      // Fieldset to keep the UI from getting out of hand
      $bef_options[$label]['more_options'] = array(
        '#type' => 'fieldset',
        '#title' => t('More options for "@identifier"', array('@identifier' => $filter->options['expose']['identifier'])),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      // Select all checkbox
      if ($bef_specific) {
        $bef_options[$label]['more_options']['bef_select_all_none'] = array(
          '#type' => 'checkbox',
          '#title' => t('Add select all/none links'),
          '#default_value' => $existing[$label]['more_options']['bef_select_all_none'],
          '#disabled' => !$filter->options['expose']['multiple'],
          '#description' => t(
            'Add a "Select All/None" link when rendering the exposed filter using
              checkboxes. If this option is disabled, edit the filter and check the
              "Allow multiple selections".'
          ),
        );

        // Put filter in collapsible fieldset option
        // TODO: expand to all exposed filters
        $bef_options[$label]['more_options']['bef_collapsible'] = array(
          '#type' => 'checkbox',
          '#title' => t('Make this filter collapsible'),
          '#default_value' => $existing[$label]['more_options']['bef_collapsible'],
          '#description' => t(
            'Puts this filter in a collapsible fieldset'
          ),
        );
      }

      // Allow any filter to be moved into the secondary options fieldset
      $bef_options[$label]['more_options']['is_secondary'] = array(
        '#type' => 'checkbox',
        '#title' => t('This is a secondary option'),
        '#default_value' => $existing[$label]['more_options']['is_secondary'],
        '#states' => array(
          'visible' => array(
            ':input[name="allow_secondary"]' => array('checked' => TRUE),
          ),
        ),
        '#description' => t('Places this element in the secondary options portion of the exposed form.'),
      );

      // Build a description option form element -- available to all exposed filters
      $bef_options[$label]['more_options']['bef_filter_description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => $existing[$label]['more_options']['bef_filter_description'],
        '#description' => t('Adds descriptive text to the exposed filter.  This is usually
                              rendered in smaller print under the label or the options.'),
      );

      // Add token support to the description field
      $bef_options[$label]['more_options']['tokens'] = array(
        '#title' => t('Replacement patterns'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      // Collect a list of token types that make sense for this filter
      $available = array('global_types');
      if (!empty($filter->options['vid'])) {
        $available[] = 'vocabulary';
      }
      // Other token types?

      $bef_options[$label]['more_options']['tokens']['list'] = array(
        '#theme' => 'token_tree',
        '#token_types' => $available,
      );
      $bef_options[$label]['more_options']['tokens']['available'] = array(
        '#type' => 'value',       // Save us from parsing available tokens again
        '#value' => $available,
      );

    } // foreach ($filters as $filter) {

    // Add BEF form elements to the exposed form options form
    $form['bef'] = $bef_options;
  }

  /*
   * Tweak the exposed filter form to show Better Exposed Filter options.
   */
  function exposed_form_alter(&$form, &$form_state) {
    parent::exposed_form_alter($form, $form_state);

    // If we have no visible elements, we don't show the Apply button.
    $show_apply = FALSE;

    // We only want to add the datepicker code once.
    // TODO: Does this need to be moved to a behavior.attach()?
    $add_datepicker = FALSE;
    $datepicker_format = '';

    // Grab BEF settings
    $settings = $this->_bef_get_settings();

    // Some elements may be placed in a secondary fieldset (eg: "Advanced
    // search options"). Place this after the exposed filters and before the
    // rest of the items in the exposed form.
    if ($allow_secondary = $settings['general']['allow_secondary']) {
      $secondary = array(
        '#type' => 'fieldset',
        '#title' => $settings['general']['secondary_label'],
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#theme' => 'secondary_exposed_elements',
      );
    }

    /*
     * Handle exposed sort elements
     */
    if (isset($settings['sort']) && !empty($form['sort_by']) && !empty($form['sort_order'])) {
      $show_apply = TRUE;

      // If selected, collect all sort-related form elements and put them
      // in a collapsible fieldset
      $collapse = $settings['sort']['advanced']['collapsible']
        && !empty($settings['sort']['advanced']['collapsible_label']);
      $sort_elems = array();

      // Check for combined sort_by and sort_order
      if ($settings['sort']['advanced']['combine']) {
        // Combine sort_by and sort_order into a single element
        $form['sort_bef_combine'] = array(
          '#type' => 'radios',
          '#title' => $form['sort_by']['#title'],   // Already sanitized by Views
        );
        $options = array();

        // Add reset sort option at the top of the list
        if ($settings['sort']['advanced']['reset']) {
          $options[' '] = t($settings['sort']['advanced']['reset_label']);
        }
        else {
          $form['sort_bef_combine']['#default_value'] = '';
        }

        $selected = '';
        foreach ($form['sort_by']['#options'] as $by_key => $by_val) {
          foreach ($form['sort_order']['#options'] as $order_key => $order_val) {
            // Use a space to separate the two keys, we'll unpack them in our submit handler
            $options["$by_key $order_key"] = "$by_val $order_val";

            if ($form['sort_order']['#default_value'] == $order_key && empty($selected)) {
              // Respect default sort order set in Views. The default sort field
              // will be the first one if there are multiple sort criteria.
              $selected = "$by_key $order_key";
            }
          }
        }

        // Rewrite the option values if any were specified
        if (!empty($settings['sort']['advanced']['combine_rewrite'])) {
          $lines = explode("\n", $settings['sort']['advanced']['combine_rewrite']);
          $rewrite = array();
          foreach ($lines as $line) {
            list($search, $replace) = explode('|', $line);
            $rewrite[$search] = $replace;
          }
          foreach ($options as $index => $option) {
            if (isset($rewrite[$option])) {
              if ('' == $rewrite[$option]) {
                unset($options[$index]);
              }
              else {
                $options[$index] = $rewrite[$option];
              }
            }
          }
        }

        $form['sort_bef_combine'] = array(
          '#type' => 'radios',
          '#options' => $options,
          '#default_value' => $selected,
          '#title' => $form['sort_by']['#title'],   // Already sanitized by Views
        );

        // Handle display-specific details
        switch ($settings['sort']['bef_format']) {
          case 'bef':
            $form['sort_bef_combine']['#prefix'] = '<div class="bef-sort-combined bef-select-as-radios">';
            $form['sort_bef_combine']['#suffix'] = '</div>';
            break;

          case 'bef_links':
            $form['sort_bef_combine']['#theme'] = 'select_as_links';
            break;

          case 'default':
            $form['sort_bef_combine']['#type'] = 'select';
            break;
        }

        // Add our submit routine to process
        $form['#submit'][] = 'bef_sort_combine_submit';

        // Remove the existing sort_by and sort_order elements
        unset($form['sort_by']);
        unset($form['sort_order']);

        if ($collapse) {
          $sort_elems[] = 'sort_bef_combine';
        }

      } // if ($settings['sort']['advanced']['combine']) {
      else {
        // Leave sort_by and sort_order as separate elements
        if ('bef' == $settings['sort']['bef_format']) {
          $form['sort_by']['#type'] = 'radios';
          if (empty($form['sort_by']['#process'])) {
            $form['sort_by']['#process'] = array();
          }
          array_unshift($form['sort_by']['#process'], 'form_process_radios');
          $form['sort_by']['#prefix'] = '<div class="bef-sortby bef-select-as-radios">';
          $form['sort_by']['#suffix'] = '</div>';

          $form['sort_order']['#type'] = 'radios';
          if (empty($form['sort_order']['#process'])) {
            $form['sort_order']['#process'] = array();
          }
          array_unshift($form['sort_order']['#process'], 'form_process_radios');
          $form['sort_order']['#prefix'] = '<div class="bef-sortorder bef-select-as-radios">';
          $form['sort_order']['#suffix'] = '</div>';
        }
        elseif ('bef_links' == $settings['sort']['bef_format']) {
          $form['sort_by']['#theme'] = 'select_as_links';
          $form['sort_order']['#theme'] = 'select_as_links';
        }

        if ($collapse) {
          $sort_elems[] = 'sort_by';
          $sort_elems[] = 'sort_order';
        }

        // Add reset sort option if selected
        if ($settings['sort']['advanced']['reset']) {
          array_unshift($form['sort_by']['#options'], $settings['sort']['advanced']['reset_label']);
        }
      } // if ($settings['sort']['advanced']['combine']) { ... } else {

      if ($collapse) {
        $form['bef_sort_options'] = array(
          '#type' => 'fieldset',
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#title' => $settings['sort']['advanced']['collapsible_label'],
        );
        foreach ($sort_elems as $elem) {
          $form['bef_sort_options'][$elem] = $form[$elem];
          unset($form[$elem]);
        }
      }

      // Check if this is a secondary form element
      if ($allow_secondary && $settings['sort']['advanced']['is_secondary']) {
        foreach (array('sort_bef_combine', 'sort_by', 'sort_order') as $elem) {
          if (!empty($form[$elem])) {
            $secondary[$elem] = $form[$elem];
            unset($form[$elem]);
          }
        }
      }
    }   // if (isset($settings['sort'])) {

    /*
     * Handle exposed pager elements
     */
    if (isset($settings['pager'])) {
      $show_apply = TRUE;

      switch ($settings['pager']['bef_format']) {
        case 'bef':
          $form['items_per_page']['#type'] = 'radios';
          if (empty($form['items_per_page']['#process'])) {
            $form['items_per_page']['#process'] = array();
          }
          array_unshift($form['items_per_page']['#process'], 'form_process_radios');
          $form['items_per_page']['#prefix'] = '<div class="bef-sortby bef-select-as-radios">';
          $form['items_per_page']['#suffix'] = '</div>';
          break;

        case 'bef_links':
          if (count($form['items_per_page']['#options']) > 1) {
            $form['items_per_page']['#theme'] = 'select_as_links';
            $form['items_per_page']['#items_per_page'] = max($form['items_per_page']['#default_value'], key($form['items_per_page']['#options']));
          }
          break;
      }

      // Check if this is a secondary form element
      if ($allow_secondary && $settings['pager']['is_secondary']) {
        foreach (array('items_per_page', 'offset') as $elem) {
          if (!empty($form[$elem])) {
            $secondary[$elem] = $form[$elem];
            unset($form[$elem]);
          }
        }
      }
    }

    // Shorthand for all filters in this view
    $filters = $form_state['view']->display_handler->handlers['filter'];

    // Go through each saved option looking for Better Exposed Filter settings
    foreach ($settings as $label => $options) {

      // Sanity check: Ensure this filter is an exposed filter
      if (empty($filters[$label]) || !$filters[$label]->options['exposed']) {
        continue;
      }

      // Form element is designated by the element ID which is user-configurable
      $field_id = $form['#info']["filter-$label"]['value'];

      // Token replacement on BEF Description fields
      if (!empty($options['more_options']['bef_filter_description'])) {
        // Collect replacement data
        $data = array();
        $available = $options['more_options']['tokens']['available'];
        if (in_array('vocabulary', $available)) {
          $vocabs = taxonomy_get_vocabularies();
          $data['vocabulary'] = $vocabs[$filters[$label]->options['vid']];
        }
        // Others?

        // Replace tokens
        $options['more_options']['bef_filter_description'] = token_replace(
          $options['more_options']['bef_filter_description'], $data
        );
        $form[$field_id]['#bef_description'] = $options['more_options']['bef_filter_description'];
      }

      if (!isset($options['bef_format'])) {
        $options['bef_format'] = '';
      }
      switch ($options['bef_format']) {
        case 'bef_datepicker':
          $show_apply = TRUE;
          $add_datepicker = TRUE;

          if ((
            // Single Date API-based input element
            isset($form[$field_id]['value']['#type'])
              && 'date_text' == $form[$field_id]['value']['#type']
          )
          || (    // Or ...
            // Double Date API-based input elements such as "in-between"
            isset($form[$field_id]['min']) && isset($form[$field_id]['max'])
            && 'date_text' == $form[$field_id]['min']['#type']
            && 'date_text' == $form[$field_id]['max']['#type']
          )) {
            // Date module date field

            /*
             * Convert Date API formatting to jQuery formatDate formatting.
             *
             * @TODO: To be honest, I'm not sure this is needed.  Can you
             * set a Date API field to accept anything other than Y-m-d?
             * Well, better safe than sorry...
             *
             * @see
             *  http://us3.php.net/manual/en/function.date.php
             * and
             *  http://docs.jquery.com/UI/Datepicker/formatDate
             *
             * Array format: PHP date format => jQuery formatDate format
             * (comments are for the PHP format, lines that are commented out
             * do not have a jQuery formatDate equivalent, but maybe someday
             * they will...)
             */
            $convert = array(
              // Day
              'd' => 'dd',    // Day of the month, 2 digits with leading zeros 01 to 31
              'D' => 'D',     // A textual representation of a day, three letters  Mon through Sun
              'j' => 'd',     // Day of the month without leading zeros  1 to 31
              'l' => 'DD',    // (lowercase 'L') A full textual representation of the day of the week  Sunday through Saturday
              // 'N' => ' ',     // ISO-8601 numeric representation of the day of the week (added in PHP 5.1.0) 1 (for Monday) through 7 (for Sunday)
              // 'S' => ' ',     // English ordinal suffix for the day of the month, 2 characters st, nd, rd or th. Works well with j
              // 'w' => ' ',     // Numeric representation of the day of the week 0 (for Sunday) through 6 (for Saturday)
              'z' => 'o',     // The day of the year (starting from 0) 0 through 365

              // Week
              // 'W' => ' ',     // ISO-8601 week number of year, weeks starting on Monday (added in PHP 4.1.0) Example: 42 (the 42nd week in the year)

              // Month
              'F' => 'MM',    // A full textual representation of a month, such as January or March  January through December
              'm' => 'mm',    // Numeric representation of a month, with leading zeros 01 through 12
              'M' => 'M',     // A short textual representation of a month, three letters  Jan through Dec
              'n' => 'm',     // Numeric representation of a month, without leading zeros  1 through 12
              // 't' => ' ',     // Number of days in the given month 28 through 31

              // Year
              // 'L' => ' ',     // Whether it's a leap year  1 if it is a leap year, 0 otherwise.
              // 'o' => ' ',     // ISO-8601 year number. This has the same value as Y, except that if the ISO week number (W) belongs to the previous or next year, that year is used instead. (added in PHP 5.1.0)  Examples: 1999 or 2003
              'Y' => 'yy',    // A full numeric representation of a year, 4 digits Examples: 1999 or 2003
              'y' => 'y',     // A two digit representation of a year  Examples: 99 or 03

              // Time
              // 'a' => ' ',     // Lowercase Ante meridiem and Post meridiem am or pm
              // 'A' => ' ',     // Uppercase Ante meridiem and Post meridiem AM or PM
              // 'B' => ' ',     // Swatch Internet time  000 through 999
              // 'g' => ' ',     // 12-hour format of an hour without leading zeros 1 through 12
              // 'G' => ' ',     // 24-hour format of an hour without leading zeros 0 through 23
              // 'h' => ' ',     // 12-hour format of an hour with leading zeros  01 through 12
              // 'H' => ' ',     // 24-hour format of an hour with leading zeros  00 through 23
              // 'i' => ' ',     // Minutes with leading zeros  00 to 59
              // 's' => ' ',     // Seconds, with leading zeros 00 through 59
              // 'u' => ' ',     // Microseconds (added in PHP 5.2.2) Example: 654321
            );

            $format = '';
            if (isset($form[$field_id]['value'])) {
              $format = $form[$field_id]['value']['#date_format'];
              $form[$field_id]['value']['#attributes']['class'][] = 'bef-datepicker';
            }
            else {
              // Both min and max share the same format
              $format = $form[$field_id]['min']['#date_format'];
              $form[$field_id]['min']['#attributes']['class'][] = 'bef-datepicker';
              $form[$field_id]['max']['#attributes']['class'][] = 'bef-datepicker';
            }
            $datepicker_format = str_replace(array_keys($convert), array_values($convert), $format);
          }
          else {
            /*
             * Standard Drupal date field.  Depending on the settings, the field
             * can be at $form[$field_id] (single field) or $form[$field_id][subfield]
             * for two-value date fields or filters with exposed operators.
             */
            $fields = array('min', 'max', 'value');
            if (count(array_intersect($fields, array_keys($form[$field_id])))) {
              foreach ($fields as $field) {
                if (isset($form[$field_id][$field])) {
                  $form[$field_id][$field]['#attributes']['class'][] = 'bef-datepicker';
                }
              }
            }
            else {
              $form[$field_id]['#attributes']['class'][] = 'bef-datepicker';
            }
          }
          break;

        case 'bef_links':
          $show_apply = TRUE;

          $form[$field_id]['#theme'] = 'select_as_links';
          break;

        case 'bef_single':
          $show_apply = TRUE;

          // Use filter label as checkbox label
          $form[$field_id]['#title'] = $filters[$label]->options['expose']['label'];
          $form[$field_id]['#description'] = $options['more_options']['bef_filter_description'];
          $form[$field_id]['#return_value'] = 1;
          $form[$field_id]['#type'] = 'checkbox';

          // Handoff to the theme layer
          $form[$field_id]['#theme'] = 'checkbox';
          break;

       case 'bef_ul':
          $show_apply = TRUE;

          $form[$field_id]['#bef_nested'] = TRUE;
          // Intentionally falling through to case 'bef':

        case 'bef':
          $show_apply = TRUE;

          if (empty($form[$field_id]['#multiple'])) {
            // Single-select -- display as radio buttons
            $form[$field_id]['#type'] = 'radios';
            if (empty($form[$field_id]['#process'])) {
              $form[$field_id]['#process'] = array();
            }
            array_unshift($form[$field_id]['#process'], 'form_process_radios');

            // Clean up objects from the options array (happens for taxonomy-based filters)
            $opts = $form[$field_id]['#options'];
            $form[$field_id]['#options'] = array();
            foreach ($opts as $index => $opt) {
              if (is_object($opt)) {
                list($key, $val) = each($opt->option);
                $form[$field_id]['#options'][$key] = $val;
              }
              else {
                $form[$field_id]['#options'][$index] = $opt;
              }
            }

            if (isset($form[$field_id]['#options']['All'])) {
              // @TODO: The terms 'All' and 'Any' are customizable in Views
              if ($filters[$label]->options['expose']['multiple']) {
                // Some third-party filter handlers still add the "Any" option even if this is not
                // an optional filter.  Zap it here if they do.
                unset($form[$field_id]['#options']['All']);
              }
              else {
                // Otherwise, make sure the "Any" text is clean
                $form[$field_id]['#options']['All'] = check_plain($form[$field_id]['#options']['All']);
              }
            }

            // Render as radio buttons or radio buttons in a collapsible fieldset
            if (!empty($options['more_options']['bef_collapsible'])) {
              // Pass the description and title along in a way such that it doesn't get rendered
              // as part of the exposed form widget.  We'll render them as part of the fieldset.
              if (isset($form['#info']["filter-$label"]['label'])) {
                $form[$field_id]['#bef_title'] = $form['#info']["filter-$label"]['label'];
                unset($form['#info']["filter-$label"]['label']);
              }
              if (!empty($options['more_options']['bef_filter_description'])) {
                $form[$field_id]['#bef_description'] = $options['more_options']['bef_filter_description'];
                if (isset($form[$field_id]['#description'])) {
                  unset($form[$field_id]['#description']);
                }
              }

              // If the operator is exposed as well, put it inside the fieldset
              if ($filters[$label]->options['expose']['use_operator']) {
                $operator_id = $filters[$label]->options['expose']['operator_id'];
                $form[$field_id]['#bef_operator'] = $form[$operator_id];
                unset ($form[$operator_id]);
              }

              // Add collapse/expand Javascript and BEF CSS to prevent collapsed
              // fieldset from disappearing.
              if (empty($form[$field_id]['#attached']['js'])) {
                $form[$field_id]['#attached']['js'] = array();
              }
              $form[$field_id]['#attached']['js'][] = 'misc/form.js';
              $form[$field_id]['#attached']['js'][] = 'misc/collapse.js';

              if (empty($form[$field_id]['#attached']['css'])) {
                $form[$field_id]['#attached']['css'] = array();
              }
              $form[$field_id]['#attached']['css'][] = drupal_get_path('module', 'better_exposed_filters') . '/better_exposed_filters.css';

              // Take care of adding the fieldset in the theme layer
              $form[$field_id]['#theme'] = 'select_as_radios_fieldset';
            } // if (!empty($options['more_options']['bef_collapsible'])) {
            else {
              // Render select element as radio buttons
              $form[$field_id]['#attributes']['class'][] = 'bef-select-as-radios';
              $form[$field_id]['#theme'] = 'select_as_radios';
            }
          } // if (empty($form[$field_id]['#multiple'])) {
          else {
            // Render as checkboxes or checkboxes enclosed in a collapsible fieldset
            if (!empty($options['more_options']['bef_collapsible'])) {
              // Pass the description and title along in a way such that it doesn't get rendered
              // as part of the exposed form widget.  We'll render them as part of the fieldset.
              if (isset($form['#info']["filter-$label"]['label'])) {
                $form[$field_id]['#bef_title'] = $form['#info']["filter-$label"]['label'];
                unset($form['#info']["filter-$label"]['label']);
              }
              if (!empty($options['more_options']['bef_filter_description'])) {
                $form[$field_id]['#bef_description'] = $options['more_options']['bef_filter_description'];
                if (isset($form[$field_id]['#description'])) {
                  unset($form[$field_id]['#description']);
                }
              }

              // If the operator is exposed as well, put it inside the fieldset
              if ($filters[$label]->options['expose']['use_operator']) {
                $operator_id = $filters[$label]->options['expose']['operator_id'];
                $form[$field_id]['#bef_operator'] = $form[$operator_id];
                unset ($form[$operator_id]);
              }

              // Add collapse/expand Javascript and BEF CSS to prevent collapsed
              // fieldset from disappearing.
              if (empty($form[$field_id]['#attached']['js'])) {
                $form[$field_id]['#attached']['js'] = array();
              }
              $form[$field_id]['#attached']['js'][] = 'misc/form.js';
              $form[$field_id]['#attached']['js'][] = 'misc/collapse.js';

              if (empty($form[$field_id]['#attached']['css'])) {
                $form[$field_id]['#attached']['css'] = array();
              }
              $form[$field_id]['#attached']['css'][] = drupal_get_path('module', 'better_exposed_filters') . '/better_exposed_filters.css';

              // Take care of adding the fieldset in the theme layer
              $form[$field_id]['#theme'] = 'select_as_checkboxes_fieldset';
            }
            else {
              $form[$field_id]['#theme'] = 'select_as_checkboxes';
            }

            if ($options['more_options']['bef_select_all_none']) {
              // Add BEF's JavaScript to the mix to handle select all/none functionality
              // @TODO: move to #attached?
              drupal_add_js(drupal_get_path('module', 'better_exposed_filters') . '/better_exposed_filters.js');

              // Add select all/none functionality to this filter.
              if (!isset($form[$field_id]['#attributes']['class'])) {
                $form[$field_id]['#attributes']['class'] = array();
              }
              $form[$field_id]['#bef_select_all_none'] = TRUE;
            }
          } // if (empty($form[$field_id]['#multiple'])) { ... } else {
          break; // case 'bef':

        case 'bef_hidden':
          $form['#info']["filter-$label"]['label'] = ''; // Hide the label
          if (empty($form[$field_id]['#multiple'])) {
            $form[$field_id]['#type'] = 'hidden';
          }
          else {
            $form[$field_id]['#theme'] = 'select_as_hidden';
          }
          break;

        default:
          // Handle functionality for exposed filters that are not limited to BEF only filters
          $show_apply = TRUE;

          // Add a description to the exposed filter
          if (!empty($options['more_options']['bef_filter_description'])) {
            $form[$field_id]['#description'] = t($options['more_options']['bef_filter_description']);
          }
          break;

      } // switch ($options['bef_format'])

      // Check if this is a secondary form element
      if ($allow_secondary && $settings[$label]['more_options']['is_secondary']) {
        $identifier = $form['#info']["filter-$label"]['value'];
        if (!empty($form[$identifier])) {
          $secondary[$identifier] = $form[$identifier];
          unset($form[$identifier]);
          $secondary[$identifier]['#title'] = $form['#info']["filter-$label"]['label'];
          unset($form['#info']["filter-$label"]);
        }
      }

    } // foreach ($settings...)

    // If our form has no visible filters, hide the submit button.
    $form['submit']['#access'] = $show_apply;
    $form['reset']['#access'] = $show_apply;

    // Only add datepicker code once
    drupal_add_js(array('better_exposed_filters' => array('bef_datepicker' => FALSE)), 'setting');
    if ($add_datepicker) {
       // Add Datepicker JS and CSS
      drupal_add_library('system', 'ui.datepicker');
      drupal_add_js(drupal_get_path('module', 'better_exposed_filters') . '/better_exposed_filters.js');

      // Trigger datepicker in better_exposed_filters.js
      drupal_add_js(array('better_exposed_filters' => array(
        'bef_datepicker' => TRUE,
        'bef_dateformat' => $datepicker_format,
      )), 'setting');
    }

    // Check for secondary elements
    if ($allow_secondary && !empty($secondary)) {
      // Add secondary elements after regular exposed filter elements
      $remaining = array_splice($form, count($form['#info']) +1);
      $form['secondary'] = $secondary;
      $form = array_merge($form, $remaining);
      $form['#info']['filter-secondary']['value'] = 'secondary';
    }

  } // function exposed_form_alter(...)

  /**
   * Similar to array_merge_recursive, but later numeric keys overwrites earlier
   * values.  Use this to set defaults for missing values in a multi-dimensional
   * array.  Eg:
   *
   *  $existing = $this->_bef_set_defaults($defaults, $existing);
   *
   * @return the resulting array
   */
  function _bef_set_defaults() {
    $count = func_num_args();
    if (!$count) {
      return;
    }
    else if (1 == $count) {
      return (func_get_arg(0));
    }

    // First array is the default values
    $params = func_get_args();
    $return = array_shift($params);

    // Merge the rest of the arrays onto the default array
    foreach ($params as $array) {
      foreach ($array as $key => $value) {
        // Numeric keyed values are added (unless already there)
        if (is_numeric($key) && !in_array ($value, $return)) {
          if (is_array($value)) {
            $return [] = $this->_bef_set_defaults($return[$key], $value);
          } else {
            $return [] = $value;
          }

        // String keyed values are replaced
        } else {
          if (isset($return[$key]) && is_array($value) && is_array($return[$key])) {
            $return[$key] = $this->_bef_set_defaults($return[$key], $value);
          } else {
            $return[$key] = $value;
          }
        }
      }
    }
    return $return;
  }

  /**
   * Updates legacy settings to their current location
   */
  function _bef_update_legacy_settings($settings) {
    // There has got to be a better way... But for now, this works.
    if (isset($settings['sort']['collapsible'])) {
      $settings['sort']['advanced']['collapsible'] = $settings['sort']['collapsible'];
      unset($settings['sort']['collapsible']);
    }
    if (isset($settings['sort']['collapsible_label'])) {
      $settings['sort']['advanced']['collapsible_label'] = $settings['sort']['collapsible_label'];
      unset($settings['sort']['collapsible_label']);
    }
    if (isset($settings['sort']['combine'])) {
      $settings['sort']['advanced']['combine'] = $settings['sort']['combine'];
      unset($settings['sort']['combine']);
    }
    if (isset($settings['sort']['reset'])) {
      $settings['sort']['advanced']['reset'] = $settings['sort']['reset'];
      unset($settings['sort']['reset']);
    }
    if (isset($settings['sort']['reset_label'])) {
      $settings['sort']['advanced']['reset_label'] = $settings['sort']['reset_label'];
      unset($settings['sort']['reset_label']);
    }

    return $settings;
  }

  /**
   * Returns an array of default or current existing values for BEF settings.
   * This helps us as we add new options and prevents a lot of
   *    if (isset($settings['new_settings'])) { ... }
   *  as there will be a default value at all positions in the settings array.
   *  Also updates legacy settings to their new locations via
   *  _bef_update_legacy_settings().
   *
   * @return array - multi-dimensional settings array
   */
  function _bef_get_settings() {
    // General, sort, pagers, etc.
    $defaults = array(
      'general' => array(
        'allow_secondary' => FALSE,
        'secondary_label' => t('Advanced options'),
      ),
      'sort' => array(
        'bef_format' => 'default',
        'advanced' => array(
          'collapsible' => FALSE,
          'collapsible_label' => '',
          'combine' => FALSE,
          'combine_rewrite' => '',
          'reset' => FALSE,
          'reset_label' => '',
          'is_secondary' => FALSE,
          ),
      ),
      'pager' => array(
        'bef_format' => 'default',
        'is_secondary' => FALSE,
      ),
    );

    // Update legacy settings in the exposed form settings form. This
    // keep us from losing settings when an option is put into an
    // 'advanced options' fieldset.
    $current = $this->_bef_update_legacy_settings($this->options['bef']);

    // Collect existing values or use defaults.  Prevents a lot of
    // isset($this->options['foo'] ? $this->options['foo'] : ''
    $settings = $this->_bef_set_defaults($defaults, $current);

    // Filter default values
    $filter_defaults = array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => FALSE,
        'is_secondary' => FALSE,
        'bef_filter_description' => '',
      ),
    );

    // Go through each exposed filter and collect settings
    foreach ($this->display->handler->get_handlers('filter') as $label => $filter) {
      if (!$filter->options['exposed']) {
        continue;
      }

      // Get existing values or use defaults
      if (!isset($this->options['bef'][$label])) {
        // First time opening the settings form with a new filter
        $settings[$label] = $filter_defaults;
      }
      else {
        $settings[$label] = $this->_bef_set_defaults($filter_defaults, $this->options['bef'][$label]);
      }
    }
    return $settings;
  }
}
