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

    // Add Better Exposed Filters options to those saved by Views.
    $options['bef'] = array('default' => array());

    // Options for the input required setting.
    $options['input_required'] = array('default' => FALSE);
    $options['text_input_required'] = array('default' => t('Select any filter and click on Apply to see results'), 'translatable' => TRUE);
    $options['text_input_required_format'] = array('default' => NULL);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $bef_options = array();

    // Get current settings and default values for new filters.
    $existing = $this->_bef_get_settings();

    /*
     * Add general options for exposed form items.
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
     * Add options for exposed sorts.
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
          'bef_toggle_links' => t('Toggle Links'),
        ),
        '#description' => t('Select a format for the exposed sort options. Note: the "toggle links" option will only work correctly if "Combine sort order with sort by" is checked in the "Advanced Sort Options" section.'),
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
        '#default_value' => empty($existing['sort']['advanced']['collapsible_label']) ? t('Sort options') : $existing['sort']['advanced']['collapsible_label'],
        '#description' => t('This cannot be left blank or there will be no way to show/hide sort options.'),
        '#dependency' => array('edit-exposed-form-options-bef-sort-advanced-collapsible' => array(1)),
      );
      $bef_options['sort']['advanced']['combine'] = array(
        '#type' => 'checkbox',
        '#title' => t('Combine sort order with sort by'),
        '#default_value' => $existing['sort']['advanced']['combine'],
        '#description' => t('Combines the sort by options and order (ascending or decending) into a single list.  Use this to display "Option1 Desc", "Option1 Asc", "Option2 Desc", "Option2 Asc" in a single form element.'),
      );
      $bef_options['sort']['advanced']['combine_rewrite'] = array(
        '#type' => 'textarea',
        '#title' => t('Rewrite the text displayed'),
        '#default_value' => $existing['sort']['advanced']['combine_rewrite'],
        '#description' => t('Use this field to rewrite the text displayed for combined sort options and sort order. Use the format of current_value|replacement_value, one replacement per line. For example: <pre>
Post date Asc|Oldest first
Post date Desc|Newest first
Title Asc|A -> Z
Title Desc|Z -> A</pre> Leave the replacement value blank to remove an option altogether.'),
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
     * Add options for exposed pager.
     */
    if (isset($this->display->display_options['pager']) && !empty($this->display->display_options['pager']['options']['expose']['items_per_page'])) {
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

    // Only add the description text once -- it was getting a little long to be
    // added to each filter.
    $bef_filter_intro = FALSE;

    $form['input_required'] = array(
      '#type' => 'checkbox',
      '#default_value' => $existing['general']['input_required'],
      '#title' => t('Require input before results are shown'),
      '#description' => t("Emulates the built in <em>Input Required</em> exposed filter handler")
    );

    $form['text_input_required'] = array(
      '#type' => 'container',
      '#tree' => FALSE,
      '#states' => array(
        // Hide this field when the input_required checkbox is disabled.
        'invisible' => array(
         ':input[name="exposed_form_options[input_required]"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['text_input_required']['text_input_required'] = array(
      '#type' => 'text_format',
      '#title' => t('Text on demand'),
      '#description' => t('Text to display instead of results until the user selects and applies an exposed filter.'),
      '#default_value' => $this->options['text_input_required'],
      '#format' => isset($this->options['text_input_required_format']) ? $this->options['text_input_required_format'] : filter_default_format(),
      '#wysiwyg' => FALSE,
    );

    // Go through each filter and add BEF options.
    foreach ($this->display->handler->get_handlers('filter') as $label => $filter) {
      if (!$filter->options['exposed']) {
        continue;
      }

      // If we're adding BEF filter options, add an intro to explain what's
      // going on.
      if (!$bef_filter_intro) {
        $link = l(t('BEF settings documentation'), 'http://drupal.org/node/1701012');
        $bef_options['bef_intro'] = array(
          '#markup' => '<h3>'
          . t('Exposed Filter Settings')
          . '</h3><p>'
          . t('This section lets you select additional options for exposed filters. Some options are only available in certain situations. If you do not see the options you expect, please see the !link page for more details.',
              array('!link' => $link))
          . '</p>',
        );
        $bef_filter_intro = TRUE;
      }

      // These filter operators get our standard options: select, radio or
      // checkboxes, links, etc.
      $bef_standard = FALSE;

      // These filters get a single on/off checkbox option for boolean
      // operators.
      $bef_single = FALSE;

      // Used for taxonomy filters with heirarchy.
      $bef_nested = FALSE;

      // Used for date-based filters.
      $bef_datepicker = FALSE;

      // Used for numeric, non-date filters.
      $bef_slider = FALSE;

      // Check various filter types and determine what options are available.
      if ($filter instanceof views_handler_filter_string || $filter instanceof views_handler_filter_in_operator) {
        if (in_array($filter->operator, array('in', 'or', 'and'))) {
          $bef_standard = TRUE;
        }
        if (in_array($filter->operator, array('empty', 'not empty'))) {
          $bef_standard = TRUE;
          if (!$filter->options['expose']['multiple']) {
            $bef_single = TRUE;
          }
        }
      }

      if ($filter instanceof views_handler_filter_boolean_operator) {
        $bef_standard = TRUE;
        if (!$filter->options['expose']['multiple']) {
          $bef_single = TRUE;
        }
      }

      if ($filter instanceof views_handler_filter_term_node_tid) {
        // Autocomplete and dropdown taxonomy filter are both instances of
        // view_handler_filter_term_node_tid, but we can't show BEF options for
        // the autocomplete widget.
        if ('textfield' == $filter->options['type']) {
          $bef_standard = FALSE;
        }
        elseif (!empty($filter->options['hierarchy'])) {
          $bef_nested = TRUE;
        }
      }

      if ($filter instanceof views_handler_filter_date || !empty($filter->date_handler)) {
        $bef_datepicker = TRUE;
      }

      // The date filter handler extends the numeric filter handler so we have
      // to exclude it specifically.
      if ($filter instanceof views_handler_filter_numeric && !($filter instanceof views_handler_filter_date)) {
        $bef_slider = TRUE;
      }

      // Search API extends the more general views_handler_filter rather than
      // operator-specific classes such as views_handler_filter_in_operator.
      // Handle those options here.
      if ($filter instanceof SearchApiViewsHandlerFilterOptions) {
        $bef_standard = TRUE;
      }
      elseif ($filter instanceof SearchApiViewsHandlerFilterDate) {
        $bef_datepicker = TRUE;
        if ($filter->options['is_grouped']) {
          $bef_standard = TRUE;
        }
      }
      elseif ($filter instanceof SearchApiViewsHandlerFilterBoolean) {
        $bef_single = TRUE;
      }

      // All filters can use the default filter exposed by Views.
      $display_options = array('default' => t('Default select list'));

      if ($bef_standard) {
        // Main BEF option: radios/checkboxes.
        $display_options['bef'] = t('Checkboxes/Radio Buttons');
      }

      if ($bef_nested) {
        $display_options['bef_ul'] = t('Nested Checkboxes/Radio Buttons');
      }

      if ($bef_single) {
        $display_options['bef_single'] = t('Single on/off checkbox');
      }

      if ($bef_datepicker) {
        $display_options['bef_datepicker'] = t('jQuery UI Datepicker');
      }

      if ($bef_slider) {
        $display_options['bef_slider'] = t('jQuery UI slider');
      }

      if ($bef_standard) {
        // Less used BEF options, so put them last.
        $display_options['bef_links'] = t('Links');
        $display_options['bef_hidden'] = t('Hidden');
      }

      $identifier = '"' . $filter->options['expose']['identifier'] . '"';
      if (!empty($filter->options['expose']['label'])) {
        $identifier .= t(' (Filter label: "@fl")', array('@fl' => $filter->options['expose']['label']));
      }
      $bef_options[$label]['bef_format'] = array(
        '#type' => 'select',
        '#title' => t('Display @identifier exposed filter as', array('@identifier' => $identifier)),
        '#default_value' => $existing[$label]['bef_format'],
        '#options' => $display_options,
      );

      if ($bef_slider) {
        // Fieldset for jQuery slider options.
        $bef_options[$label]['slider_options'] = array(
          '#type' => 'fieldset',
          '#title' => t('Slider options for @identifier', array('@identifier' => $identifier)),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
          '#states' => array(
            'visible' => array(
              ':input[name="exposed_form_options[bef][' . $label . '][bef_format]"]' => array('value' => 'bef_slider'),
            ),
          ),
        );

        $bef_options[$label]['slider_options']['bef_slider_min'] = array(
          '#type' => 'textfield',
          '#title' => t('Range minimum'),
          '#default_value' => $existing[$label]['slider_options']['bef_slider_min'],
          '#bef_filter_id' => $label,
          '#states' => array(
            'required' => array(
              ':input[name="exposed_form_options[bef][' . $label . '][bef_format]"]' => array('value' => 'bef_slider'),
            ),
          ),
          '#description' => t('The minimum allowed value for the jQuery range slider. It can be positive, negative, or zero and have up to 11 decimal places.'),
          '#element_validate' => array('element_validate_number', 'better_exposed_filters_element_validate_slider_required', 'better_exposed_filters_element_validate_slider_min_max'),
        );
        $bef_options[$label]['slider_options']['bef_slider_max'] = array(
          '#type' => 'textfield',
          '#title' => t('Range maximum'),
          '#default_value' => $existing[$label]['slider_options']['bef_slider_max'],
          '#bef_filter_id' => $label,
          '#states' => array(
            'required' => array(
              ':input[name="exposed_form_options[bef][' . $label . '][bef_format]"]' => array('value' => 'bef_slider'),
            ),
          ),
          '#description' => t('The maximum allowed value for the jQuery range slider. It can be positive, negative, or zero and have up to 11 decimal places.'),
          '#element_validate' => array('element_validate_number', 'better_exposed_filters_element_validate_slider_required', 'better_exposed_filters_element_validate_slider_min_max'),
        );
        $bef_options[$label]['slider_options']['bef_slider_step'] = array(
          '#type' => 'textfield',
          '#title' => t('Step'),
          '#default_value' => empty($existing[$label]['slider_options']['bef_slider_step']) ? 1 : $existing[$label]['slider_options']['bef_slider_step'],
          '#bef_filter_id' => $label,
          '#states' => array(
            'required' => array(
              ':input[name="exposed_form_options[bef][' . $label . '][bef_format]"]' => array('value' => 'bef_slider'),
            ),
          ),
          '#description' => t('Determines the size or amount of each interval or step the slider takes between the min and max.') . '<br />' .
                            t('The full specified value range of the slider (Range maximum - Range minimum) must be evenly divisible by the step.') . '<br />' .
                            t('The step must be a positive number of up to 5 decimal places.'),
          '#element_validate' => array('element_validate_number', 'better_exposed_filters_element_validate_slider_required', 'better_exposed_filters_element_validate_slider_step'),
        );
        $bef_options[$label]['slider_options']['bef_slider_animate'] = array(
          '#type' => 'textfield',
          '#title' => t('Animate'),
          '#default_value' => $existing[$label]['slider_options']['bef_slider_animate'],
          '#bef_filter_id' => $label,
          '#description' => t('Whether to slide handle smoothly when user click outside handle on the bar. Allowed values are "slow", "normal", "fast" or the number of milliseconds to run the animation (e.g. 1000). If left blank, there will be no animation, the slider will just jump to the new value instantly.'),
          '#element_validate' => array('better_exposed_filters_element_validate_slider_animate'),
        );
        $bef_options[$label]['slider_options']['bef_slider_orientation'] = array(
          '#type' => 'select',
          '#title' => t('Orientation'),
          '#options' => array(
            'horizontal' => t('Horizontal'),
            'vertical' => t('Vertical'),
          ),
          '#default_value' => $existing[$label]['slider_options']['bef_slider_orientation'],
          '#bef_filter_id' => $label,
          '#states' => array(
            'required' => array(
              ':input[name="exposed_form_options[bef][' . $label . '][bef_format]"]' => array('value' => 'bef_slider'),
            ),
          ),
          '#description' => t('The orientation of the jQuery range slider.'),
        );
      }

      // Fieldset to keep the UI from getting out of hand.
      $bef_options[$label]['more_options'] = array(
        '#type' => 'fieldset',
        '#title' => t('More options for @identifier', array('@identifier' => $identifier)),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      // Select all checkbox.
      if ($bef_standard) {
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

        if ($bef_nested) {
          $bef_options[$label]['more_options']['bef_select_all_none_nested'] = array(
            '#type' => 'checkbox',
            '#title' => t('Add nested all/none selection'),
            '#default_value' => $existing[$label]['more_options']['bef_select_all_none_nested'],
            '#disabled' => !$filter->options['expose']['multiple'] || !$filter->options['hierarchy'],
            '#description' => t(
              'When a parent checkbox is checked, check all its children. If this option
                is disabled, edit the filter and check "Allow multiple selections" and
                edit the filter settings and check "Show hierarchy in dropdown".'
            ),
          );
        }

        // Put filter in collapsible fieldset option.
        // TODO: expand to all exposed filters.
        $bef_options[$label]['more_options']['bef_collapsible'] = array(
          '#type' => 'checkbox',
          '#title' => t('Make this filter collapsible'),
          '#default_value' => $existing[$label]['more_options']['bef_collapsible'],
          '#description' => t(
            'Puts this filter in a collapsible fieldset'
          ),
        );
      }

      // Allow any filter to be moved into the secondary options fieldset.
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

      // Allow "Any" label to be overridden.
      $bef_options[$label]['more_options']['any_label'] = array(
        '#type' => 'textfield',
        '#title' => t('Override "Any" option label'),
        '#default_value' => $existing[$label]['more_options']['any_label'],
        '#description' => t('Leave blank to use views default value. <em>Note: overriding this label will break translations and localizations. Leave this field blank if preserving internationalization is important to your site.</em>'),
      );

      // Build a description option form element -- available to all exposed
      // filters.
      $bef_options[$label]['more_options']['bef_filter_description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => $existing[$label]['more_options']['bef_filter_description'],
        '#description' => t('Adds descriptive text to the exposed filter.  This is usually rendered in smaller print under the label or the options.'),
      );

      // Add token support to the description field.
      $bef_options[$label]['more_options']['tokens'] = array(
        '#title' => t('Replacement patterns'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      if (!module_exists('token')) {
        $bef_options[$label]['more_options']['tokens']['no_tokens'] = array(
          '#markup' => '<p>'
          . t('Enable the !token module to use replacement values.', array('!token' => l(t('Token'), 'http://drupal.org/project/token')))
          . '</p>',
        );
      }

      // Collect a list of token types that make sense for this filter.
      $available = array('global_types');
      if (!empty($filter->options['vid'])) {
        $available[] = 'vocabulary';
      }
      /* @TODO: Other token types? */

      $bef_options[$label]['more_options']['tokens']['list'] = array(
        '#theme' => 'token_tree',
        '#token_types' => $available,
      );
      $bef_options[$label]['more_options']['tokens']['available'] = array(
        // Save us from parsing available tokens again.
        '#type' => 'value',
        '#value' => $available,
      );

      // Allow rewriting of filter options for any filter.
      $bef_options[$label]['more_options']['rewrite'] = array(
        '#title' => t('Rewrite filter options'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $bef_options[$label]['more_options']['rewrite']['filter_rewrite_values'] = array(
        '#type' => 'textarea',
        '#title' => t('Rewrite the text displayed'),
        '#default_value' => $existing[$label]['more_options']['rewrite']['filter_rewrite_values'],
        '#description' => t('
          Use this field to rewrite the filter options displayed. Use the format
          of current_value|replacement_value, one replacement per line. For
          example: <pre>
0|Zero
1|One
2|Two
</pre> Leave the replacement value blank to remove an option altogether. If using hierarchical taxonomy filters, do not including leading hyphens in the current value.
        '),
      );
    }
    /* Ends: foreach ($filters as $filter) { */

    // Add BEF form elements to the exposed form options form.
    $form['bef'] = $bef_options;
  }

  /**
   * Tweak the exposed filter form to show Better Exposed Filter options.
   *
   * @param array $form
   *   Exposed form array
   * @param array $form_state
   *   Current state of form variables
   */
  function exposed_form_alter(&$form, &$form_state) {
    parent::exposed_form_alter($form, $form_state);
    global $language;

    // If we have no visible elements, we don't show the Apply button.
    $show_apply = FALSE;

    // Collect BEF's Javascript settings, add to Drupal.settings at the end.
    // Historical note: We used to only add BEF's Javascript when absolutely
    // needed. Eventually, much of that functionality worked its way into the
    // normal usage of BEF so that we now turn those Jvaascript behaviors on
    // by default. (See https://drupal.org/node/1807114).
    $bef_add_js = TRUE;
    $bef_js = array(
      'datepicker' => FALSE,
      'slider' => FALSE,
      'settings' => array(),
    );

    // Some widgets will require additional CSS.
    $bef_add_css = FALSE;

    // Grab BEF settings.
    $settings = $this->_bef_get_settings();

    // Some elements may be placed in a secondary fieldset (eg: "Advanced
    // search options"). Place this after the exposed filters and before the
    // rest of the items in the exposed form.
    if ($allow_secondary = $settings['general']['allow_secondary']) {
      // If one of the secondary widgets has exposed input, do not collapse
      // the secondary fieldset.
      $secondary_collapse = TRUE;
      foreach ($this->view->get_exposed_input() as $key => $value) {
        if (!empty($value) && isset($settings[$key]['more_options']['is_secondary'])) {
          $secondary_collapse = FALSE;
          break;
        }
      }
      $secondary = array(
        '#type' => 'fieldset',
        '#title' => $settings['general']['secondary_label'],
        '#collapsible' => TRUE,
        '#collapsed' => $secondary_collapse,
        '#theme' => 'secondary_exposed_elements',
      );
    }

    /*
     * Handle exposed sort elements.
     */
    if (isset($settings['sort']) && !empty($form['sort_by']) && !empty($form['sort_order'])) {
      $show_apply = TRUE;

      // If selected, collect all sort-related form elements and put them
      // in a collapsible fieldset.
      $collapse = $settings['sort']['advanced']['collapsible']
        && !empty($settings['sort']['advanced']['collapsible_label']);
      $sort_elems = array();

      // Check for combined sort_by and sort_order.
      if ($settings['sort']['advanced']['combine']) {
        // Combine sort_by and sort_order into a single element.
        $form['sort_bef_combine'] = array(
          '#type' => 'radios',
          // Already sanitized by Views.
          '#title' => $form['sort_by']['#title'],
        );
        $options = array();
        // If using the bef_toggle_links format, determine which links should
        // not be shown.
        $hidden_options = array();

        // Add reset sort option at the top of the list.
        if ($settings['sort']['advanced']['reset']) {
          $options[' '] = t($settings['sort']['advanced']['reset_label']);
        }
        else {
          $form['sort_bef_combine']['#default_value'] = '';
        }

        $selected = '';
        $used_sort_keys = array();
        foreach ($form['sort_by']['#options'] as $by_key => $by_val) {
          foreach ($form['sort_order']['#options'] as $order_key => $order_val) {
            // Use a space to separate the two keys, we'll unpack them in our
            // submit handler.
            $options["$by_key $order_key"] = "$by_val $order_val";

            if ($form['sort_order']['#default_value'] == $order_key && empty($selected)) {
              // Respect default sort order set in Views. The default sort field
              // will be the first one if there are multiple sort criteria.
              $selected = "$by_key $order_key";
            }
           if ($settings['sort']['bef_format'] == 'bef_toggle_links') {
             if (isset($used_sort_keys[$by_key])
               || (!empty($form_state['input']['sort_bef_combine']) && $form_state['input']['sort_bef_combine'] == "$by_key $order_key")
               || (empty($form_state['input']['sort_bef_combine']) && $selected == "$by_key $order_key")
             ) {
                $hidden_options["$by_key $order_key"] = "$by_val $order_val";
             }
             else {
                $used_sort_keys[$by_key] = $order_key;
             }
            }
          }
        }

        $view = $form_state['view'];

        // Rewrite the option values if any were specified.
        if (!empty($settings['sort']['advanced']['combine_rewrite'])) {
          $combine_rewrite = trim($settings['sort']['advanced']['combine_rewrite']);
          $textgroup = implode(':', array(
            'better_exposed_filters',
            'combine_rewrite',
            $view->name,
            $view->current_display,
          ));
          $combine_rewrite = better_exposed_filters_translate($textgroup, $combine_rewrite);
          $lines = explode("\n", $combine_rewrite);
          $rewrite = array();
          foreach ($lines as $line) {
            list($search, $replace) = explode('|', $line);
            if (!empty($search)) {
              $rewrite[$search] = $replace;
            }
          }
          foreach ($options as $index => $option) {
            if (isset($rewrite[$option])) {
              if ('' == $rewrite[$option]) {
                unset($options[$index]);
                if ($selected == $index) {
                  // Avoid "Illegal choice" errors.
                  $selected = NULL;
                }
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
          '#hidden_options' => $hidden_options,
          '#settings' => array(
            'toggle_links' => ($settings['sort']['bef_format'] == 'bef_toggle_links'),
           ),
          '#default_value' => $selected,
          // Already sanitized by Views.
          '#title' => $form['sort_by']['#title'],
        );

        // Handle display-specific details.
        switch ($settings['sort']['bef_format']) {
          case 'bef':
            $form['sort_bef_combine']['#prefix'] = '<div class="bef-sort-combined bef-select-as-radios">';
            $form['sort_bef_combine']['#suffix'] = '</div>';
            break;

          case 'bef_links':
          case 'bef_toggle_links':
            $form['sort_bef_combine']['#theme'] = 'select_as_links';

            // Exposed form displayed as blocks can appear on pages other than
            // the view results appear on. This can cause problems with
            // select_as_links options as they will use the wrong path. We
            // provide a hint for theme functions to correct this.
            if (!empty($this->display->display_options['exposed_block'])) {
              $form['sort_bef_combine']['#bef_path'] = $this->display->display_options['path'];
            }
            break;

          case 'default':
            $form['sort_bef_combine']['#type'] = 'select';
            break;
        }

        // Add our submit routine to process.
        $form['#submit'][] = 'bef_sort_combine_submit';

        // Pretend we're another exposed form widget.
        $form['#info']['sort-sort_bef_combine'] = array(
          'value' => 'sort_bef_combine',
        );

        // Remove the existing sort_by and sort_order elements.
        unset($form['sort_by']);
        unset($form['sort_order']);

        if ($collapse) {
          $sort_elems[] = 'sort_bef_combine';
        }
      }
      /* if ($settings['sort']['advanced']['combine']) { } */
      else {
        // Leave sort_by and sort_order as separate elements.
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

          // Exposed form displayed as blocks can appear on pages other than the
          // view results appear on. This can cause problems with
          // select_as_links options as they will use the wrong path. We provide
          // a hint for theme functions to correct this.
          if (!empty($this->display->display_options['exposed_block'])) {
            $form['sort_by']['#bef_path'] = $this->display->display_options['path'];
            $form['sort_order']['#bef_path'] = $this->display->display_options['path'];
          }
        }

        if ($collapse) {
          $sort_elems[] = 'sort_by';
          $sort_elems[] = 'sort_order';
        }

        // Add reset sort option if selected.
        if ($settings['sort']['advanced']['reset']) {
          array_unshift($form['sort_by']['#options'], $settings['sort']['advanced']['reset_label']);
        }
      }
      /* Ends: if ($settings['sort']['advanced']['combine']) { ... } else { */

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

      // Check if this is a secondary form element.
      if ($allow_secondary && $settings['sort']['advanced']['is_secondary']) {
        foreach (array('sort_bef_combine', 'sort_by', 'sort_order') as $elem) {
          if (!empty($form[$elem])) {
            $secondary[$elem] = $form[$elem];
            unset($form[$elem]);
          }
        }
      }
    }
    /* Ends: if (isset($settings['sort'])) { */

    /*
     * Handle exposed pager elements.
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

            // Exposed form displayed as blocks can appear on pages other than
            // the view results appear on. This can cause problems with
            // select_as_links options as they will use the wrong path. We
            // provide a hint for theme functions to correct this.
            if (!empty($this->display->display_options['exposed_block'])) {
              $form['items_per_page']['#bef_path'] = $this->display->display_options['path'];
            }
          }
          break;
      }

      // Check if this is a secondary form element.
      if ($allow_secondary && $settings['pager']['is_secondary']) {
        foreach (array('items_per_page', 'offset') as $elem) {
          if (!empty($form[$elem])) {
            $secondary[$elem] = $form[$elem];
            unset($form[$elem]);
          }
        }
      }
    }

    // Shorthand for all filters in this view.
    $filters = $form_state['view']->display_handler->handlers['filter'];

    // Go through each saved option looking for Better Exposed Filter settings.
    foreach ($settings as $label => $options) {

      // Sanity check: Ensure this filter is an exposed filter.
      if (empty($filters[$label]) || !$filters[$label]->options['exposed']) {
        continue;
      }

      // Form element is designated by the element ID which is user-
      // configurable.
      $field_id = $form['#info']["filter-$label"]['value'];

      // Token replacement on BEF Description fields.
      if (!empty($options['more_options']['bef_filter_description'])) {
        // Collect replacement data.
        $data = array();
        $available = $options['more_options']['tokens']['available'];
        if (in_array('vocabulary', $available)) {
          $vocabs = taxonomy_get_vocabularies();
          $data['vocabulary'] = $vocabs[$filters[$label]->options['vid']];
        }
        /* Others? */

        // Replace tokens.
        $options['more_options']['bef_filter_description'] = token_replace(
          $options['more_options']['bef_filter_description'], $data
        );
        $form[$field_id]['#bef_description'] = $options['more_options']['bef_filter_description'];
      }

      // Handle filter value rewrites.
      if (!empty($options['more_options']['rewrite']['filter_rewrite_values'])) {
        $lines = explode("\n", trim($options['more_options']['rewrite']['filter_rewrite_values']));
        $rewrite = array();
        foreach ($lines as $line) {
          list($search, $replace) = explode('|', $line);
          if (!empty($search)) {
            $rewrite[$search] = $replace;
          }
        }

        foreach ($form[$field_id]['#options'] as $index => $option) {
          $is_object = FALSE;
          if (is_object($option)) {
            // Taxonomy filters use objects instead of text.
            $is_object = TRUE;
            $option = reset($option->option);

            // Hierarchical filters prepend hyphens to indicate depth. We need
            // to remove them for comparison, but keep them after replacement to
            // ensure nested options display correctly.
            $option = ltrim($option, '-');
          }

          if (isset($rewrite[$option])) {
            if ('' == $rewrite[$option]) {
              unset($form[$field_id]['#options'][$index]);
            }
            else {
              if ($is_object) {
                // dsm($form[$field_id]['#options'][$index]->option, "$field_id at $index");
                // Taxonomy term filters are stored as objects. Use str_replace
                // to ensure that keep hyphens for hierarchical filters.
                list($tid, $original) = each($form[$field_id]['#options'][$index]->option);
                $form[$field_id]['#options'][$index]->option[$tid] = str_replace($option, $rewrite[$option], $original);
              }
              else {
                $form[$field_id]['#options'][$index] = $rewrite[$option];
              }
            }
          }
        }
      }

      // @TODO: Is this conditional needed anymore after the existing settings
      // array default values were added?
      if (!isset($options['bef_format'])) {
        $options['bef_format'] = '';
      }

      // These BEF options require a set of given options to work (namely,
      // $form[$field_id]['#options'] needs to set). But it is possilbe to
      // adjust settings elsewhere in the view that removes these options from
      // the form (eg: changing a taxonomy term filter from dropdown to
      // autocomplete). Check for that here and revert to Views' default filter
      // in those cases.
      $requires_options = array('bef', 'bef_ul', 'bef_links', 'bef_hidden');
      if (in_array($options['bef_format'], $requires_options) && !array_key_exists('#options', $form[$field_id])) {
        $options['bef_format'] = 'default';
      }

      switch ($options['bef_format']) {
        case 'bef_datepicker':
          $show_apply = TRUE;
          $bef_add_js = TRUE;
          $bef_js['datepicker'] = TRUE;
          $bef_js['datepicker_options'] = array();

          if ((
            // Single Date API-based input element.
            isset($form[$field_id]['value']['#type'])
              && 'date_text' == $form[$field_id]['value']['#type']
          )
          // Double Date-API-based input elements such as "in-between".
          || (isset($form[$field_id]['min']) && isset($form[$field_id]['max'])
            && 'date_text' == $form[$field_id]['min']['#type']
            && 'date_text' == $form[$field_id]['max']['#type']
          )) {
            /*
             * Convert Date API formatting to jQuery formatDate formatting.
             *
             * @TODO: To be honest, I'm not sure this is needed.  Can you set a
             * Date API field to accept anything other than Y-m-d? Well, better
             * safe than sorry...
             *
             * @see http://us3.php.net/manual/en/function.date.php
             * @see http://docs.jquery.com/UI/Datepicker/formatDate
             *
             * Array format: PHP date format => jQuery formatDate format
             * (comments are for the PHP format, lines that are commented out do
             * not have a jQuery formatDate equivalent, but maybe someday they
             * will...)
             */
            $convert = array(
              /* Day */

              // Day of the month, 2 digits with leading zeros 01 to 31.
              'd' => 'dd',
              // A textual representation of a day, three letters  Mon through
              // Sun.
              'D' => 'D',
              // Day of the month without leading zeros  1 to 31.
              'j' => 'd',
              // (lowercase 'L') A full textual representation of the day of the
              // week Sunday through Saturday.
              'l' => 'DD',
              // ISO-8601 numeric representation of the day of the week (added
              // in PHP 5.1.0) 1 (for Monday) through 7 (for Sunday).
              // 'N' => ' ',
              // English ordinal suffix for the day of the month, 2 characters
              // st, nd, rd or th. Works well with j.
              // 'S' => ' ',
              // Numeric representation of the day of the week 0 (for Sunday)
              // through 6 (for Saturday).
              // 'w' => ' ',
              // The day of the year (starting from 0) 0 through 365.
              'z' => 'o',

              /* Week */
              // ISO-8601 week number of year, weeks starting on Monday (added
              // in PHP 4.1.0) Example: 42 (the 42nd week in the year).
              // 'W' => ' ',
              //
              /* Month */
              // A full textual representation of a month, such as January or
              // March  January through December.
              'F' => 'MM',
              // Numeric representation of a month, with leading zeros 01
              // through 12.
              'm' => 'mm',
              // A short textual representation of a month, three letters  Jan
              // through Dec.
              'M' => 'M',
              // Numeric representation of a month, without leading zeros  1
              // through 12.
              'n' => 'm',
              // Number of days in the given month 28 through 31.
              // 't' => ' ',
              //
              /* Year */
              // Whether it's a leap year  1 if it is a leap year, 0 otherwise.
              // 'L' => ' ',
              // ISO-8601 year number. This has the same value as Y, except that
              // if the ISO week number (W) belongs to the previous or next
              // year, that year is used instead. (added in PHP 5.1.0).
              // Examples: 1999 or 2003.
              // 'o' => ' ',
              // A full numeric representation of a year, 4 digits Examples:
              // 1999 or 2003.
              'Y' => 'yy',
              // A two digit representation of a year  Examples: 99 or 03.
              'y' => 'y',

              /* Time */
              // Lowercase Ante meridiem and Post meridiem am or pm.
              // 'a' => ' ',
              // Uppercase Ante meridiem and Post meridiem AM or PM.
              // 'A' => ' ',
              // Swatch Internet time  000 through 999.
              // 'B' => ' ',
              // 12-hour format of an hour without leading zeros 1 through 12.
              // 'g' => ' ',
              // 24-hour format of an hour without leading zeros 0 through 23.
              // 'G' => ' ',
              // 12-hour format of an hour with leading zeros  01 through 12.
              // 'h' => ' ',
              // 24-hour format of an hour with leading zeros  00 through 23.
              // 'H' => ' ',
              // Minutes with leading zeros  00 to 59.
              // 'i' => ' ',
              // Seconds, with leading zeros 00 through 59.
              // 's' => ' ',
              // Microseconds (added in PHP 5.2.2) Example: 654321.
              // 'u' => ' ',
            );

            $format = '';
            if (isset($form[$field_id]['value'])) {
              $format = $form[$field_id]['value']['#date_format'];
              $form[$field_id]['value']['#attributes']['class'][] = 'bef-datepicker';
            }
            else {
              // Both min and max share the same format.
              $format = $form[$field_id]['min']['#date_format'];
              $form[$field_id]['min']['#attributes']['class'][] = 'bef-datepicker';
              $form[$field_id]['max']['#attributes']['class'][] = 'bef-datepicker';
            }
            $bef_js['datepicker_options']['dateformat'] = str_replace(array_keys($convert), array_values($convert), $format);
          }
          else {
            $bef_js['datepicker_options']['dateformat'] = '';
            /*
             * Standard Drupal date field.  Depending on the settings, the field
             * can be at $form[$field_id] (single field) or
             * $form[$field_id][subfield] for two-value date fields or filters
             * with exposed operators.
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

        case 'bef_slider':
          $show_apply = TRUE;
          $bef_add_js = TRUE;
          $bef_add_css = TRUE;
          $bef_js['slider'] = TRUE;

          // Add js options for the slider for this filter.
          $bef_js['slider_options'][$field_id] = array(
            'min' => $options['slider_options']['bef_slider_min'],
            'max' => $options['slider_options']['bef_slider_max'],
            'step' => $options['slider_options']['bef_slider_step'],
            'animate' => $options['slider_options']['bef_slider_animate'],
            'orientation' => $options['slider_options']['bef_slider_orientation'],
            'id' => drupal_html_id($field_id),
            'viewId' => $form['#id'],
          );
          break;

        case 'bef_links':
          $show_apply = TRUE;
          $form[$field_id]['#theme'] = 'select_as_links';

          // Exposed form displayed as blocks can appear on pages other than
          // the view results appear on. This can cause problems with
          // select_as_links options as they will use the wrong path. We provide
          // a hint for theme functions to correct this.
          if (!empty($this->display->display_options['exposed_block'])) {
            $form[$field_id]['#bef_path'] = $this->display->display_options['path'];
          }
          break;

        case 'bef_single':
          $show_apply = TRUE;

          // Use filter label as checkbox label.
          $form[$field_id]['#title'] = $filters[$label]->options['expose']['label'];
          $form[$field_id]['#description'] = $options['more_options']['bef_filter_description'];
          $form[$field_id]['#return_value'] = 1;
          $form[$field_id]['#type'] = 'checkbox';

          // Handoff to the theme layer.
          $form[$field_id]['#theme'] = 'checkbox';
          break;

        case 'bef_ul':
          $show_apply = TRUE;

          $form[$field_id]['#bef_nested'] = TRUE;
          /* Intentionally falling through to case 'bef'. */

        case 'bef':
          $show_apply = TRUE;

          if (empty($form[$field_id]['#multiple'])) {
            // Single-select -- display as radio buttons.
            $form[$field_id]['#type'] = 'radios';
            if (empty($form[$field_id]['#process'])) {
              $form[$field_id]['#process'] = array();
            }
            array_unshift($form[$field_id]['#process'], 'form_process_radios');

            // Add description
            if (!empty($form[$field_id]['#bef_description'])) {
              $form[$field_id]['#description'] = $form[$field_id]['#bef_description'];
            }

            // Clean up objects from the options array (happens for taxonomy-
            // based filters).
            $opts = $form[$field_id]['#options'];
            $form[$field_id]['#options'] = array();
            foreach ($opts as $index => $opt) {
              if (is_object($opt)) {
                reset($opt->option);
                list($key, $val) = each($opt->option);
                $form[$field_id]['#options'][$key] = $val;
              }
              else {
                $form[$field_id]['#options'][$index] = $opt;
              }
            }

            if (isset($form[$field_id]['#options']['All'])) {
              // @TODO: The terms 'All' and 'Any' are customizable in Views.
              if ($filters[$label]->options['expose']['multiple']) {
                // Some third-party filter handlers still add the "Any" option
                // even if this is not an optional filter.  Zap it here if they
                // do.
                unset($form[$field_id]['#options']['All']);
              }
              else {
                // Otherwise, make sure the "Any" text is clean.
                $form[$field_id]['#options']['All'] = check_plain($form[$field_id]['#options']['All']);
              }
            }

            // Render as radio buttons or radio buttons in a collapsible
            // fieldset.
            if (!empty($options['more_options']['bef_collapsible'])) {
              // Pass the description and title along in a way such that it
              // doesn't get rendered as part of the exposed form widget.  We'll
              // render them as part of the fieldset.
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

              // If the operator is exposed as well, put it inside the fieldset.
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

              // Take care of adding the fieldset in the theme layer.
              $form[$field_id]['#theme'] = 'select_as_radios_fieldset';
            }
            /* if (!empty($options['more_options']['bef_collapsible'])) { */
            else {
              // Render select element as radio buttons.
              $form[$field_id]['#attributes']['class'][] = 'bef-select-as-radios';
              $form[$field_id]['#theme'] = 'select_as_radios';
            }
          }
          /* if (empty($form[$field_id]['#multiple'])) { */
          else {
            // Render as checkboxes or checkboxes enclosed in a collapsible
            // fieldset.
            if (!empty($options['more_options']['bef_collapsible'])) {
              // Pass the description and title along in a way such that it
              // doesn't get rendered as part of the exposed form widget.  We'll
              // render them as part of the fieldset.
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

              // If the operator is exposed as well, put it inside the fieldset.
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

              // Take care of adding the fieldset in the theme layer.
              $form[$field_id]['#theme'] = 'select_as_checkboxes_fieldset';
            }
            else {
              $form[$field_id]['#theme'] = 'select_as_checkboxes';
            }

            if ($options['more_options']['bef_select_all_none'] || $options['more_options']['bef_select_all_none_nested']) {
              $bef_add_js = TRUE;

              if ($options['more_options']['bef_select_all_none']) {
                $form[$field_id]['#bef_select_all_none'] = TRUE;
              }
              if ($options['more_options']['bef_select_all_none_nested']) {
                $form[$field_id]['#bef_select_all_none_nested'] = TRUE;
              }
            }

          }
          /* Ends: if (empty($form[$field_id]['#multiple'])) { ... } else { */
          break;

        case 'bef_hidden':
          // Hide the label.
          $form['#info']["filter-$label"]['label'] = '';
          if (empty($form[$field_id]['#multiple'])) {
            $form[$field_id]['#type'] = 'hidden';
          }
          else {
            $form[$field_id]['#theme'] = 'select_as_hidden';
          }
          break;

        default:
          // Handle functionality for exposed filters that are not limited to
          // BEF only filters.
          $show_apply = TRUE;

          // Add a description to the exposed filter.
          if (!empty($options['more_options']['bef_filter_description'])) {
            $form[$field_id]['#description'] = t($options['more_options']['bef_filter_description']);
          }
          break;
      }
      /* Ends switch ($options['bef_format']) */

      // Check if this is a secondary form element.
      if ($allow_secondary && $settings[$label]['more_options']['is_secondary']) {
        $identifier = $form['#info']["filter-$label"]['value'];
        if (!empty($form[$identifier])) {
          // Move exposed operators with exposed filters
          if (!empty($filters[$label]->options['expose']['use_operator'])) {
            $op_id = $filters[$label]->options['expose']['operator_id'];
            $secondary[$op_id] = $form[$op_id];
            unset($form[$op_id]);
          }
          $secondary[$identifier] = $form[$identifier];
          unset($form[$identifier]);
          $secondary[$identifier]['#title'] = $form['#info']["filter-$label"]['label'];
          unset($form['#info']["filter-$label"]);
        }
      }
    }

    // Override "Any" label, if applicable.
    if (!empty($options['more_options']['any_label']) && !empty($form[$field_id]['#options']['All'])) {
      $form[$field_id]['#options']['All'] = $options['more_options']['any_label'];
    }

    // If our form has no visible filters, hide the submit button.
    $form['submit']['#access'] = $show_apply;
    $form['reset']['#access'] = $show_apply;

    // Add Javascript as needed.
    if ($bef_add_js) {
      // Add jQuery UI library code as needed.
      if ($bef_js['datepicker']) {
        drupal_add_library('system', 'ui.datepicker');
      }
      if ($bef_js['slider']) {
        drupal_add_library('system', 'ui.slider');
      }

      drupal_add_js(array('better_exposed_filters' => $bef_js), 'setting');
      drupal_add_js(drupal_get_path('module', 'better_exposed_filters') . '/better_exposed_filters.js');
    }
    if ($bef_add_css) {
      drupal_add_css(drupal_get_path('module', 'better_exposed_filters') . '/better_exposed_filters.css');
    }

    // Check for secondary elements.
    if ($allow_secondary && !empty($secondary)) {
      // Add secondary elements after regular exposed filter elements.
      $remaining = array_splice($form, count($form['#info']) + 1);
      $form['secondary'] = $secondary;
      $form = array_merge($form, $remaining);
      $form['#info']['filter-secondary']['value'] = 'secondary';
    }
  }

  /**
   * Fills in missing settings with default values.
   *
   * Similar to array_merge_recursive, but later numeric keys overwrites earlier
   * values.  Use this to set defaults for missing values in a multi-dimensional
   * array.  Eg:
   *
   *  $existing = $this->_bef_set_defaults($defaults, $existing);
   *
   * @return array
   *   The resulting settings array
   */
  function _bef_set_defaults() {
    $count = func_num_args();
    if (!$count) {
      return;
    }
    elseif (1 == $count) {
      return (func_get_arg(0));
    }

    // First array is the default values.
    $params = func_get_args();
    $return = array_shift($params);

    // Merge the rest of the arrays onto the default array.
    foreach ($params as $array) {
      foreach ($array as $key => $value) {
        // Numeric keyed values are added (unless already there).
        if (is_numeric($key) && !in_array($value, $return)) {
          if (is_array($value)) {
            $return[] = $this->_bef_set_defaults($return[$key], $value);
          }
          else {
            $return[] = $value;
          }
        }
        // String keyed values are replaced.
        else {
          if (isset($return[$key]) && is_array($value) && is_array($return[$key])) {
            $return[$key] = $this->_bef_set_defaults($return[$key], $value);
          }
          else {
            $return[$key] = $value;
          }
        }
      }
    }
    return $return;
  }

  /**
   * Updates legacy settings to their current location.
   *
   * @param array $settings
   *   Array of BEF settings.
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
   *
   * This helps us as we add new options and prevents a lot of
   * @code
   *    if (isset($settings['new_settings'])) { ... }
   * @endcode
   * as there will be a default value at all positions in the settings array.
   * Also updates legacy settings to their new locations via
   * _bef_update_legacy_settings().
   *
   * @return array
   *   Multi-dimensional settings array.
   */
  function _bef_get_settings() {
    // General, sort, pagers, etc.
    $defaults = array(
      'general' => array(
        'input_required' => FALSE,
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

    // Collect existing values or use defaults.
    $settings = $this->_bef_set_defaults($defaults, $current);

    // Filter default values.
    $filter_defaults = array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_select_all_none_nested' => FALSE,
        'bef_collapsible' => FALSE,
        'is_secondary' => FALSE,
        'bef_filter_description' => '',
        'any_label' => '',
        'tokens' => array(
          'list' => array(),
          'available' => array(),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
      'slider_options' => array(
        'bef_slider_min' => 0,
        'bef_slider_max' => 99999,
        'bef_slider_step' => 1,
        'bef_slider_animate' => '',
        'bef_slider_orientation' => 'horizontal',
      ),
    );

    // Go through each exposed filter and collect settings.
    foreach ($this->display->handler->get_handlers('filter') as $label => $filter) {
      if (!$filter->options['exposed']) {
        continue;
      }

      // Get existing values or use defaults.
      if (!isset($this->options['bef'][$label])) {
        // First time opening the settings form with a new filter.
        $settings[$label] = $filter_defaults;
      }
      else {
        $settings[$label] = $this->_bef_set_defaults($filter_defaults, $this->options['bef'][$label]);
      }
    }
    return $settings;
  }

  /**
   * Util function to determine if any filters have been applied.
   * Borrowed from views_plugin_exposed_form_input_required
   */
  function exposed_filter_applied() {
    static $cache = NULL;
    if (!isset($cache)) {
      $view = $this->view;
      if (is_array($view->filter) && count($view->filter)) {
        foreach ($view->filter as $filter_id => $filter) {
          if ($filter->is_exposed()) {
            $identifier = $filter->options['expose']['identifier'];
            if (isset($view->exposed_input[$identifier])) {
              if (!empty($view->exposed_input[$identifier])) {
                $cache = TRUE;
                return $cache;
              }
            }
          }
        }
      }
      $cache = FALSE;
    }

    return $cache;
  }

  /**
   * Pre render callback to append the 'no values found' text if input required
   * options is enabled.
   */
  function pre_render($values) {
    if (!$this->exposed_filter_applied() && !empty($this->options['input_required'])) {
      $options = array(
        'id' => 'area',
        'table' => 'views',
        'field' => 'area',
        'label' => '',
        'relationship' => 'none',
        'group_type' => 'group',
        'content' => $this->options['text_input_required'],
        'format' => $this->options['text_input_required_format'],
        'empty' => TRUE,
      );
      $handler = views_get_handler('views', 'area', 'area');
      $handler->init($this->view, $options);
      $this->display->handler->handlers['empty'] = array(
        'area' => $handler,
      );
      $this->display->handler->set_option('empty', array('text' => $options));
    }
  }

  /**
   * Query callback, intervenes if no filters are applied and input is required.
   */
  function query() {
    if (!$this->exposed_filter_applied() && !empty($this->options['input_required'])) {
      // We return with no query; this will force the empty text.
      $this->view->built = TRUE;
      $this->view->executed = TRUE;
      $this->view->result = array();
    }
    else {
      parent::query();
    }
  }

  /**
   * Submit handler for the options to unpack the format/text from the
   * text_format field.
   */
  function options_submit(&$form, &$form_state) {
    $view = $form_state['view'];
    $values = &$form_state['values'];
    $values['exposed_form_options']['text_input_required_format'] = $values['text_input_required']['format'];
    $values['exposed_form_options']['text_input_required'] = $values['text_input_required']['value'];
    if (function_exists('i18n_string_update')) {
      $combine_rewrite = $values['exposed_form_options']['bef']['sort']['advanced']['combine_rewrite'];
      $textgroup = implode(':', array(
        'better_exposed_filters',
        'combine_rewrite',
        $view->name,
        $view->current_display,
      ));
      i18n_string_update($textgroup, $combine_rewrite, array(
        'format' => FALSE,
      ));
    }
    parent::options_submit($form, $form_state);
  }
}
