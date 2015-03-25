<?php

/**
 * @file
 * Administration pages for the WYSIWYG Filter module.
 */

/**
 * Implements hook_filter_FILTER_settings
 *
 * @ingroup forms
 * TODO:
 * * remove defaults from info hook
 * * set defaults in helper func
 * * save settings for other formats in hidden form items
 * * remove format suffix, will be first array index
 * * care for pre- and post-processing, or remove it like parsed-elements
 * * rewrite validate to get correct values like $form['filters']['settings'][$name] / $form_state['values']['filters'][$name]['settings']
 * 
 */
function wysiwyg_filter_filter_wysiwyg_settings(&$form, &$form_state, $filter, $format, $defaults, $filters) {
  global $base_url;
  drupal_add_css(drupal_get_path('module', 'wysiwyg_filter') . '/wysiwyg_filter.admin.css', array('preprocess' => FALSE));
  // Load common functions.
  module_load_include('inc', 'wysiwyg_filter');

  $settings = $filter->settings;
  $settings += $defaults;
  
  // carry over settings for other formats
  $filterform = array();
  
  // *** valid elements ***
  $valid_elements = $settings['valid_elements'];
  $valid_elements_rows = min(20, max(5, substr_count($valid_elements, "\n") + 2));
  // show blacklisted elements in description
  $elements_blacklist = wysiwyg_filter_get_elements_blacklist();
  foreach ($elements_blacklist as $i => $element) {
    $elements_blacklist[$i] = '<' . $element . '>';
  }
  $filterform['valid_elements'] = array(
    '#type' => 'textarea',
    '#title' => t('HTML elements and attributes'),
    '#default_value' => $valid_elements,
    '#cols' => 60,
    '#rows' => $valid_elements_rows,
    '#description' => t('<p>
This option allows you to specify which HTML elements and attributes are allowed in <a href="@valid-elements">TinyMCE valid_elements format</a>.
</p>
<strong>Syntax tips:</strong><ul>
  <li>Use a comma separated list to allow several HTML elements. Example: &quot;em,strong,br,p,ul,ol,li&quot;. Note that you can split your definitions using any number of lines.</li>
  <li>Use square brackets &quot;[]&quot; to specify the attributes that are allowed for each HTML element. Attributes should be whitelisted explicitly, otherwise element attributes will be ignored. Example: &quot;a&quot; will NOT allow users to post links, you should use &quot;a[href]&quot; instead!</li>
  <li>Use the vertical bar character &quot;|&quot; to separate several attribute definitions for a single HTML element. Example: &quot;a[href|target]&quot; means users may optionally specify the &quot;href&quot; and &quot;target&quot; attributes for &quot;a&quot; elements, any other attribute will be ignored.</li>
  <li>Use the exclamation mark &quot;!&quot; to set one attribute as being required for a particular HTML element. Example: &quot;a[!href|target]&quot; means users must specify the &quot;href&quot; attribute, otherwise the whole &quot;a&quot; element will be ignored. Users may optionally specify the &quot;target&quot; attribute as well. However, any other attribute will be ignored.</li>
  <li>Use the asterisk symbol &quot;*&quot; to whitelist all possible attributes for a particular HTML element. Example: &quot;a[*]&quot; means users will be allowed to use any attribute for the &quot;a&quot; element.</li>
  <li>Use the at sign character &quot;@&quot; to whitelist a common set of attributes for all allowed HTML elements. Example: &quot;@[class|style]&quot; means users will be allowed to use the &quot;class&quot; and &quot;style&quot; attributes for any whitelisted HTML element.</li>
  <li>For further information and examples, please consult documentation of the <a href="@valid-elements">valid_elements</a> option in the TinyMCE Wiki site.</li>
</ul>
<strong>Additional notes:</strong><ul>
  <li>The following elements cannot be whitelisted due to security reasons, to prevent users from breaking site layout and/or to avoid posting invalid HTML. Forbidden elements: %elements-blacklist.</li>
  <li>JavaScript event attributes such as onclick, onmouseover, etc. are always ignored. Should you need them, please consider using the &quot;Full HTML&quot; input format instead.</li>
  <li>If you allow usage of the attributes &quot;id&quot;, &quot;class&quot; and/or &quot;style&quot;, then you should also select which style properties are allowed and/or specify explicit matching rules for them using the &quot;Advanced rules&quot; section below.</li>
</ul>', array(
      '@valid-elements' => 'http://wiki.moxiecode.com/index.php/TinyMCE:Configuration/valid_elements',
      '%elements-blacklist' => implode(' ', $elements_blacklist),
    )),
  );

  // *** allow comments ***
  $filterform['allow_comments'] = array(
    '#type' => 'radios',
    '#title' => t('HTML comments'),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('Enabled'),
    ),
    '#default_value' => $settings['allow_comments'],
    '#description' => t('Use this option to allow HTML comments.'),
  );

  // *** Style properties ***
  $filterform['styles'] = array(
    '#title' => t('Style properties'),
    '#description' => '<p>' . t('This section allows you to select which style properties can be used for HTML elements where the &quot;style&quot; attribute has been allowed. The <em>WYSIWYG Filter</em> will strip out style properties (and their values) not explicitly enabled here. On the other hand, for allowed style properties the <em>WYSIWYG Filter</em> will check their values for strict CSS syntax and strip out those that do not match.') . '</p>' .
      '<p>' . t('Additional matching rules should be specified from the &quot;Advanced rules&quot; section below for a few of these properties that may contain URLs in their values (&quot;background&quot;, &quot;background-image&quot;, &quot;list-style&quot; and &quot;list-style-image&quot;). Otherwise, these style properties will be ignored from user input.') . '</p>',
  );
  $style_property_groups = wysiwyg_filter_get_style_property_groups();
  $enabled_style_properties = array();
  $i = 0;
  foreach ($style_property_groups as $group => $group_info) {
    $style_properties = $settings["style_$group"];
    $enabled_style_properties += array_filter($style_properties);
    $filterform["style_$group"] = array(
      '#type' => 'checkboxes',
      '#title' => $group_info['title'],
      '#default_value' => $style_properties,
      '#options' => drupal_map_assoc(array_keys($group_info['properties'])),
      '#checkall' => TRUE,
      '#prefix' => '<div class="wysiwyg-filter-style-properties-group">',
      '#suffix' => '</div>'. (($i % 3) == 2?'<br style="clear:both"/>':''),
    );
    $i++;
  }

  // *** Advanced rules ***
  $filterform['rules'] = array(
    '#title' => t('Advanced rules'),
    '#prefix' => '<br style="clear:both"/>',
    '#description' => '<p>' . t('Use the following options to configure additional rules for certain HTML element attributes. As a safety measure, these rules should be defined explicitly. Otherwise, the corresponding HTML element attributes will be ignored from user input.') . '</p>',
  );
  $valid_elements_parsed = wysiwyg_filter_parse_valid_elements($settings['valid_elements']);
  foreach (wysiwyg_filter_get_advanced_rules() as $rule_key => $rule_info) {
    $field_name = "rule_$rule_key";
    $default_value = wysiwyg_filter_array2csv($settings[$field_name]);
    $filterform[$field_name] = array(
      '#type' => 'textarea',
      '#title' => $rule_info['title'],
      '#default_value' => $default_value,
      '#cols' => 60,
      '#rows' => min(10, max(2, substr_count($default_value, "\n") + 2)),
      '#description' => $rule_info['description'],
    );

    // Display warning if the field is empty but the rule definition is not
    // complete.
    if (empty($default_value) && !_wysiwyg_filter_is_rule_definition_complete($rule_info, $valid_elements_parsed, $enabled_style_properties)) {
      drupal_set_message($rule_info['required_by_message'], 'warning');
    }
  }

  // *** Nofollow properties ***
  $filterform['nofollow'] = array(
    '#title' => t('Spam link deterrent settings'),
    '#description' => t('As a measure to reduce the effectiveness of spam links, it is often recommended to add rel=&quot;nofollow&quot; to posted links leading to external sites. The WYSIWYG Filter can easily do this for you while HTML is being processed with almost no additional performance impact.'),
  );
  $filterform['nofollow_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Policy'),
    '#options' => array(
      'disabled' => t('Disabled - Do not add rel=&quot;nofollow&quot; to any link.'),
      'whitelist' => t('Whitelist - Add rel=&quot;nofollow&quot; to all links except those leading to domain names specified in the list below.'),
      'blacklist' => t('Blacklist - Add rel=&quot;nofollow&quot; to all links leading to domain names specified in the list below.'),
    ),
    '#default_value' => $settings['nofollow_policy'],
    '#description' => t('If you choose the whitelist option, be sure to add your own domain names to the list!'),
  );
  $parts = parse_url($base_url);
  // Note that domains list is stored by our submit handler in array form where
  // dots have been escaped, so we need here to revert the process to get a clean
  // string for user input where dots are unescaped.
  $nofollow_domains = wysiwyg_filter_array2csv($settings['nofollow_domains']);
  $filterform['nofollow_domains'] = array(
    '#type' => 'textarea',
    '#title' => t('Domains list'),
    '#default_value' => $nofollow_domains,
    '#cols' => 60,
    '#rows' => min(10, max(5, substr_count($nofollow_domains, "\n") + 2)),
    '#description' => t('Enter a comma separated list of top level domain names. Note that all subdomains will also be included. Example: example.com will match example.com, www.example.com, etc.'),
  );

  return $filterform;
}

/*
 * Implements hook_form_FORM_ID_alter
 * 
 * add validate and submit handlers
 */
function wysiwyg_filter_form_filter_admin_format_form_alter(&$form, &$form_state, $form_id) {
  $form['#validate'][] = 'wysiwyg_filter_filter_wysiwyg_settings_validate';
  // Add the submit callback to the beginning of the array because we need
  // to prepare data for system_settings_form_submit().
  array_unshift($form['#submit'], 'wysiwyg_filter_filter_wysiwyg_settings_submit');
}

/**
 * Validate if the given rule definition is complete.
 *
 * @param $rule_info
 *   An array of information about the rule we are about to check.
 * @param $elements
 *   The array of all valid elements enabled for the current filter.
 * @param $style_properties
 *   The array of all style properties enabled for the current filter.
 * @return
 *   TRUE if the rule definiton is complete, FALSE otherwise.
 *
 * @see wysiwyg_filter_parse_valid_elements()
 * @see wysiwyg_filter_get_advanced_rules()
 */
function _wysiwyg_filter_is_rule_definition_complete($rule_info, $elements, $style_properties) {
  foreach ($elements as $tag => $attributes) {
    if (isset($attributes[$rule_info['required_by']])) {
      // If this rule is not dependent on style properties, then we found it,
      // while we should not, so the rule is not complete.
      if (empty($rule_info['required_by_styles'])) {
        return FALSE;
      }
      // If this rule is dependent on style properties, then we need to check
      // if the related style properties exist.
      foreach ($rule_info['required_by_styles'] as $style_property) {
        if (isset($style_properties[$style_property])) {
          return FALSE;
        }
      }
    }
  }
  return TRUE;
}

/**
 * Clear any warning message we might have set previously.
 */
function _wysiwyg_filter_clear_messages() {
  $messages = drupal_get_messages('warning');
  if (!empty($messages)) {
    foreach (wysiwyg_filter_get_advanced_rules() as $rule_info) {
      $my_messages[] = $rule_info['required_by_message'];
    }
    foreach ($messages['warning'] as $warning) {
      if (!in_array($warning, $my_messages)) {
        drupal_set_message($warning, 'warning');
      }
    }
  }
}

/**
 * Validate filter settings form.
 *
 * @ingroup forms
 */
function wysiwyg_filter_filter_wysiwyg_settings_validate($form, &$form_state) {
  $values =& $form_state['values']['filters']['wysiwyg']['settings'];

  // *** validate valid_elements ***
  // Check elements against hardcoded backlist.
  $elements_blacklist = wysiwyg_filter_get_elements_blacklist();
  $valid_elements = trim($values['valid_elements']);
  $valid_elements = wysiwyg_filter_parse_valid_elements($valid_elements);
  $forbidden_elements = array();
  foreach (array_keys($valid_elements) as $element) {
    if (in_array($element, $elements_blacklist)) {
      $forbidden_elements[] = $element;
    }
  }
  if (!empty($forbidden_elements)) {
    form_set_error('valid_elements', t('The following elements cannot be allowed: %elements.', array('%elements' => implode(', ', $forbidden_elements))));
  }

  // *** validate nofollow_domains ***
  foreach (wysiwyg_filter_get_advanced_rules() as $rule_key => $rule_info) {
    $field_name = "rule_$rule_key";
    $expressions = array_filter(explode(',', preg_replace('#\s+#', ',', trim($values[$field_name])))); // form2db
    $errors = array();
    foreach ($expressions as $expression) {
      if (preg_match('`[*?]\*|\*\?`', $expression)) {
        $errors[] = t('Invalid expression %expression. Please, do not use more than one consecutive asterisk (**) or one that is next to a question mark wildcard (?* or *?).', array('%expression' => $expression));
      }
      if (!preg_match($rule_info['validate_regexp'], $expression)) {
        $errors[] = t('Invalid expression %expression. Please, check the syntax of the %field field.', array('%expression' => $expression, '%field' => $rule_info['title']));
      }
    }
    if (!empty($errors)) {
      form_set_error($field_name, implode('<br />', $errors));
    }
  }

  // *** validate nofollow_domains ***
  $nofollow_domains = array_filter(explode(',', preg_replace('#\s+#', ',', $values['nofollow_domains']))); // form2db
  foreach ($nofollow_domains as $nofollow_domain) {
    if (!preg_match('#^([a-z0-9]([-a-z0-9]*)?\.)+([a-z]+)$#i', $nofollow_domain)) {
      form_set_error('nofollow_domains', t('Invalid domain %domain. Please, enter a comma separated list of valid domain names.', array('%domain' => $nofollow_domain)));
    }
  }
}

/**
 * Submit processing for the filter settings form.
 *
 * Parse filter options to help us save resources that would otherwiese
 * require time and precious cpu cycles at filter processing time.
 *
 * @ingroup forms
 */
function wysiwyg_filter_filter_wysiwyg_settings_submit($form, &$form_state) {
  $values =& $form_state['values']['filters']['wysiwyg']['settings'];
    
  // *** prepare valid_elements - just trim ***
  $values['valid_elements'] = trim($values['valid_elements']);
  
  // *** prepare rules - csv2array ***
  foreach (array_keys(wysiwyg_filter_get_advanced_rules()) as $rule_key) {
    $field_name = "rule_$rule_key";
    $values[$field_name] = wysiwyg_filter_csv2array($values[$field_name]);
  }

  // *** prepare nofollow_domains - csv2array ***
  $values['nofollow_domains'] = wysiwyg_filter_csv2array($values['nofollow_domains']);
}

/*
 * CSV to Array
 * 
 * @param atring $v
 * @param bool $space2comma - shall we convet whitespace to commas before processing?
 * @return array
 */
function wysiwyg_filter_csv2array($v, $space2comma = TRUE) {
  IF($space2comma) $v = preg_replace('#\s+#', ',', $v);
  return array_filter(explode(',', $v));
}
/*
 * Array to CSV
 * 
 * @param array $v
 * @return string
 */
function wysiwyg_filter_array2csv($v, $separator = ",\n") {
  return implode($separator, $v);
}
