<?php

/**
 * @file
 * Administrative page callbacks for the linkchecker module.
 */

/**
 * Implements hook_admin_settings_form().
 */
function linkchecker_admin_settings_form($form_state) {

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => FALSE,
  );
  // @todo node_type_get_names() can return an empty array!?
  $names = node_type_get_names();
  $form['settings']['linkchecker_scan_nodetypes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Scan content types for links'),
    '#default_value' => variable_get('linkchecker_scan_nodetypes', array()),
    '#options' => array_map('check_plain', $names),
    '#description' => t('Enable link checking for the selected content type(s).'),
  );

  $comment_dependencies = '<div class="admin-requirements">';
  $comment_dependencies .= t('Requires: !module-list', array('!module-list' => (module_exists('comment') ? t('@module (<span class="admin-enabled">enabled</span>)', array('@module' => 'Comment')) : t('@module (<span class="admin-disabled">disabled</span>)', array('@module' => 'Comment')))));
  $comment_dependencies .= '</div>';

  $form['settings']['linkchecker_scan_comments'] = array(
    '#default_value' => variable_get('linkchecker_scan_comments', 0),
    '#type' => 'checkbox',
    '#title' => t('Scan comments for links'),
    '#description' => t('Enable this checkbox if links in comments of the above selected content type(s) should be checked.') . $comment_dependencies,
    '#disabled' => module_exists('comment') ? FALSE : TRUE,
  );

  $block_custom_dependencies = '<div class="admin-requirements">';
  $block_custom_dependencies .= t('Requires: !module-list', array('!module-list' => (module_exists('block') ? t('@module (<span class="admin-enabled">enabled</span>)', array('@module' => 'Block')) : t('@module (<span class="admin-disabled">disabled</span>)', array('@module' => 'Block')))));
  $block_custom_dependencies .= '</div>';

  $form['settings']['linkchecker_scan_blocks'] = array(
    '#default_value' => variable_get('linkchecker_scan_blocks', 0),
    '#type' => 'checkbox',
    '#title' => t('Scan blocks for links'),
    '#description' => t('Enable this checkbox if links in blocks should be checked.') . $block_custom_dependencies,
    '#disabled' => module_exists('block') ? FALSE : TRUE,
  );
  $form['settings']['linkchecker_check_links_types'] = array(
    '#type' => 'select',
    '#title' => t('What type of links should be checked?'),
    '#description' => t('A full qualified link (http://example.com/foo/bar) to a page is considered external, whereas an absolute (/foo/bar) or relative link (node/123) without a domain is considered internal.'),
    '#default_value' => variable_get('linkchecker_check_links_types', 1),
    '#options' => array(
      '0' => t('Internal and external'),
      '1' => t('External only (http://example.com/foo/bar)'),
      '2' => t('Internal only (node/123)'),
    ),
  );

  $form['tag'] = array(
    '#type' => 'fieldset',
    '#title' => t('Link extraction'),
    '#collapsible' => FALSE,
  );
  $form['tag']['linkchecker_extract_from_a'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_a', 1),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;a&gt;</code> and <code>&lt;area&gt;</code> tags'),
    '#description' => t('Enable this checkbox if normal hyperlinks should be extracted. The anchor element defines a hyperlink, the named target destination for a hyperlink, or both. The area element defines a hot-spot region on an image, and associates it with a hypertext link.'),
  );
  $form['tag']['linkchecker_extract_from_audio'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_audio', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;audio&gt;</code> tags including their <code>&lt;source&gt;</code> and <code>&lt;track&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in audio tags should be extracted. The audio element is used to embed audio content.'),
  );
  $form['tag']['linkchecker_extract_from_embed'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_embed', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;embed&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in embed tags should be extracted. This is an obsolete and non-standard element that was used for embedding plugins in past and should no longer used in modern websites.'),
  );
  $form['tag']['linkchecker_extract_from_iframe'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_iframe', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;iframe&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in iframe tags should be extracted. The iframe element is used to embed another HTML page into a page.'),
  );
  $form['tag']['linkchecker_extract_from_img'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_img', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;img&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in image tags should be extracted. The img element is used to add images to the content.'),
  );
  $form['tag']['linkchecker_extract_from_object'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_object', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;object&gt;</code> and <code>&lt;param&gt;</code> tags'),
    '#description' => t('Enable this checkbox if multimedia and other links in object and their param tags should be extracted. The object tag is used for flash, java, quicktime and other applets.'),
  );
  $form['tag']['linkchecker_extract_from_video'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_video', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;video&gt;</code> tags including their <code>&lt;source&gt;</code> and <code>&lt;track&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in video tags should be extracted. The video element is used to embed video content.'),
  );

  // Get all filters available on the system.
  $filter_info = filter_get_filters();
  $filter_options = array();
  foreach ($filter_info as $name => $filter) {
    if (in_array($name, explode('|', LINKCHECKER_DEFAULT_FILTER_BLACKLIST))) {
      $filter_options[$name] = t('!title <span class="form-required">(Recommended)</span>', array('!title' => $filter['title']));
    }
    else {
      $filter_options[$name] = $filter['title'];
    }
  }
  $form['tag']['linkchecker_filter_blacklist'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Filters disabled for link extraction'),
    '#default_value' => variable_get('linkchecker_filter_blacklist', explode('|', LINKCHECKER_DEFAULT_FILTER_BLACKLIST)),
    '#options' => $filter_options,
    '#description' => t('If a filter has been enabled for an input format it runs first and afterwards the link extraction. This helps the link checker module to find all links normally created by custom filters (e.g. Markdown filter, Bbcode). All filters used as inline references (e.g. Weblink filter <code>[link: id]</code>) to other content and filters only wasting processing time (e.g. Line break converter) should be disabled. This setting does not have any effect on how content is shown on a page. This feature optimizes the internal link extraction process for link checker and prevents false alarms about broken links in content not having the real data of a link.'),
  );

  $count_lids_enabled = db_query("SELECT count(lid) FROM {linkchecker_link} WHERE status = :status", array(':status' => 1))->fetchField();
  $count_lids_disabled = db_query("SELECT count(lid) FROM {linkchecker_link} WHERE status = :status", array(':status' => 0))->fetchField();
  $form['check'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check settings'),
    '#description' => t('For simultaneous link checks it is recommended to install the <a href="@httprl">HTTP Parallel Request & Threading Library</a>. This may be <strong>necessary</strong> on larger sites with very many links (30.000+), but will also improve overall link check duration on smaller sites. Currently the site has @count links (@count_enabled enabled / @count_disabled disabled).', array('@httprl' => 'http://drupal.org/project/httprl', '@count' => $count_lids_enabled+$count_lids_disabled, '@count_enabled' => $count_lids_enabled, '@count_disabled' => $count_lids_disabled)),
    '#collapsible' => FALSE,
  );
  $form['check']['linkchecker_check_library'] = array(
    '#type' => 'select',
    '#title' => t('Check library'),
    '#description' => t('Defines the library that is used for checking links.'),
    '#default_value' => variable_get('linkchecker_check_library', 'core'),
    '#options' => array(
      'core' => t('Drupal core'),
      'httprl' => t('HTTP Parallel Request & Threading Library'),
    ),
  );
  $form['check']['linkchecker_check_connections_max'] = array(
    '#type' => 'select',
    '#title' => t('Number of simultaneous connections'),
    '#description' => t('Defines the maximum number of simultaneous connections that can be opened by the server. <em>HTTP Parallel Request & Threading Library</em> make sure that a single domain is not overloaded beyond RFC limits. For small hosting plans with very limited CPU and RAM it may be required to reduce the default limit.'),
    '#default_value' => variable_get('linkchecker_check_connections_max', 8),
    '#options' => drupal_map_assoc(array(2, 4, 8, 16, 24, 32, 48, 64, 96, 128)),
    '#states' => array(
      // Hide the setting when Drupal core check library is selected.
      'invisible' => array(
        ':input[name="linkchecker_check_library"]' => array('value' => 'core'),
      ),
    ),
  );
  $form['check']['linkchecker_check_useragent'] = array(
    '#type' => 'select',
    '#title' => t('User-Agent'),
    '#description' => t('Defines the user agent that will be used for checking links on remote sites. If someone blocks the standard Drupal user agent you can try with a more common browser.'),
    '#default_value' => variable_get('linkchecker_check_useragent', 'Drupal (+http://drupal.org/)'),
    '#options' => array(
      'Drupal (+http://drupal.org/)' => 'Drupal (+http://drupal.org/)',
      'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)' => 'Windows 7 (x64), Internet Explorer 9.0',
      'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:17.0) Gecko/20100101 Firefox/17.0' => 'Windows 7 (x64), Mozilla Firefox 17.0',
      'Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)' => 'Windows 8 (x64), Internet Explorer 10.0',
      'Mozilla/5.0 (Windows NT 6.2; WOW64; rv:17.0) Gecko/20100101 Firefox/17.0' => 'Windows 8 (x64), Mozilla Firefox 17.0',
    ),
  );
  $form['check']['linkchecker_check_links_interval'] = array(
    '#type' => 'select',
    '#title' => t('Check interval for links'),
    '#description' => t('This interval setting defines how often cron will re-check the status of links.'),
    '#default_value' => variable_get('linkchecker_check_links_interval', 2419200),
    '#options' => drupal_map_assoc(array(86400, 172800, 259200, 604800, 1209600, 2419200, 4838400), 'format_interval'),
  );
  $form['check']['linkchecker_disable_link_check_for_urls'] = array(
    '#default_value' => variable_get('linkchecker_disable_link_check_for_urls', LINKCHECKER_RESERVED_DOCUMENTATION_DOMAINS),
    '#type' => 'textarea',
    '#title' => t('Do not check the link status of links containing these URLs'),
    '#description' => t('By default this list contains the domain names reserved for use in documentation and not available for registration. See <a href="@rfc-2606">RFC 2606</a>, Section 3 for more information. URLs on this list are still extracted, but the link setting <em>Check link status</em> becomes automatically disabled to prevent false alarms. If you change this list you need to clear all link data and re-analyze your content. Otherwise this setting will only affect new links added after the configuration change.', array('@rfc-2606' => 'http://www.rfc-editor.org/rfc/rfc2606.txt')),
  );

  $form['error'] = array(
    '#type' => 'fieldset',
    '#title' => t('Error handling'),
    '#description' => t('Defines error handling and custom actions to be executed if specific HTTP requests are failing.'),
    '#collapsible' => FALSE,
  );
  $linkchecker_default_impersonate_user = user_load(1);
  $form['error']['linkchecker_impersonate_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Impersonate user account'),
    '#description' => t('If below error handling actions are executed they can be impersonated with a custom user account. By default this is user %name, but you are able to assign a custom user to allow easier identification of these automatic revision updates. Make sure you select a user with <em>full</em> permissions on your site or the user may not able to access and save all content.', array('%name' => $linkchecker_default_impersonate_user->name)),
    '#size' => 30,
    '#maxlength' => 60,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => variable_get('linkchecker_impersonate_user', ''),
  );
  $form['error']['linkchecker_action_status_code_301'] = array(
    '#title' => t('Update permanently moved links'),
    '#description' => t('If enabled, outdated links in content providing a status <em>Moved Permanently</em> (status code 301) are automatically updated to the most recent URL. If used, it is recommended to use a value of <em>three</em> to make sure this is not only a temporarily change. This feature trust sites to provide a valid permanent redirect. A new content revision is automatically created on link updates if <em>create new revision</em> is enabled in the <a href="@content_types">content types</a> publishing options. It is recommended to create new revisions for all link checker enabled content types. Link updates are nevertheless always logged in <a href="@dblog">recent log entries</a>.', array('@dblog' => url('admin/reports/dblog'), '@content_types' => url('admin/structure/types'))),
    '#type' => 'select',
    '#default_value' => variable_get('linkchecker_action_status_code_301', 0),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('After one failed check'),
      2 => t('After two failed checks'),
      3 => t('After three failed checks'),
      5 => t('After five failed checks'),
      10 => t('After ten failed checks'),
    ),
  );
  $form['error']['linkchecker_action_status_code_404'] = array(
    '#title' => t('Unpublish content on file not found error'),
    '#description' => t('If enabled, content with one or more broken links (status code 404) will be unpublished and moved to moderation queue for review after the number of specified checks failed. If used, it is recommended to use a value of <em>three</em> to make sure this is not only a temporarily error.'),
    '#type' => 'select',
    '#default_value' => variable_get('linkchecker_action_status_code_404', 0),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('After one file not found error'),
      2 => t('After two file not found errors'),
      3 => t('After three file not found errors'),
      5 => t('After five file not found errors'),
      10 => t('After ten file not found errors'),
    ),
  );
  $form['error']['linkchecker_ignore_response_codes'] = array(
    '#default_value' => variable_get('linkchecker_ignore_response_codes', "200\n206\n302\n304\n401\n403"),
    '#type' => 'textarea',
    '#title' => t("Don't treat these response codes as errors"),
    '#description' => t('One HTTP status code per line, e.g. 403.'),
  );

  // Buttons are only required for testing and debugging reasons.
  $description = '<p>' . t('These actions will either clear all link checker tables in the database and/or analyze all selected content types, blocks and fields (see settings above) for new/updated/removed links. Normally there is no need to press one of these buttons. Use this only for immediate cleanup tasks and to force a full re-build of the links to be checked in the linkchecker tables. Keep in mind that all custom link settings will be lost if you clear link data!') . '</p>';
  $description .= '<p>' . t('<strong>Note</strong>: These functions ONLY collect the links, they do not evaluate the HTTP response codes, this will be done during normal cron runs.') . '</p>';

  $form['clear'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maintenance'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['clear']['linkchecker_analyze'] = array(
    '#type' => 'submit',
    '#value' => t('Reanalyze content for links'),
    '#submit' => array('linkchecker_analyze_links_submit'),
  );
  $form['clear']['linkchecker_clear_analyze'] = array(
    '#type' => 'submit',
    '#value' => t('Clear link data and analyze content for links'),
    '#submit' => array('linkchecker_clear_analyze_links_submit'),
  );

  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults'));

  return $form;
}

/**
 * Implements hook_admin_settings_form_validate().
 */
function linkchecker_admin_settings_form_validate($form, &$form_state) {
  $form_state['values']['linkchecker_disable_link_check_for_urls'] = trim($form_state['values']['linkchecker_disable_link_check_for_urls']);
  $form_state['values']['linkchecker_ignore_response_codes'] = trim($form_state['values']['linkchecker_ignore_response_codes']);
  $ignore_response_codes = preg_split('/(\r\n?|\n)/', $form_state['values']['linkchecker_ignore_response_codes']);
  foreach ($ignore_response_codes as $ignore_response_code) {
    if (!_linkchecker_isvalid_response_code($ignore_response_code)) {
      form_set_error('linkchecker_ignore_response_codes', t('Invalid response code %code found.', array('%code' => $ignore_response_code)));
    }
  }

  // Prevent the removal of RFC documentation domains. This are the official and
  // reserved documentation domains and not "example" hostnames!
  $linkchecker_disable_link_check_for_urls = array_filter(preg_split('/(\r\n?|\n)/', $form_state['values']['linkchecker_disable_link_check_for_urls']));
  $form_state['values']['linkchecker_disable_link_check_for_urls'] = implode("\n", array_unique(array_merge(explode("\n", LINKCHECKER_RESERVED_DOCUMENTATION_DOMAINS), $linkchecker_disable_link_check_for_urls)));

  // Validate impersonation user name.
  $linkchecker_impersonate_user = user_load_by_name($form_state['values']['linkchecker_impersonate_user']);
  if (empty($linkchecker_impersonate_user->uid)) {
    form_set_error('linkchecker_impersonate_user', t('User account %name cannot found.', array('%name' => $form_state['values']['linkchecker_impersonate_user'])));
  }
}

/**
 * Implements hook_admin_settings_form_submit().
 */
function linkchecker_admin_settings_form_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  unset($form_state['values']['linkchecker_analyze'], $form_state['values']['linkchecker_clear_analyze']);

  // Save form settings.
  system_settings_form_submit($form, $form_state);

  // Re-scan items, if node types or comment or custom block selection has been
  // changed.
  $additional_nodetypes_selected = array_diff($form_state['values']['linkchecker_scan_nodetypes'], $form['settings']['linkchecker_scan_nodetypes']['#default_value']);
  if (!empty($additional_nodetypes_selected) || $form_state['values']['linkchecker_scan_comments'] > $form['settings']['linkchecker_scan_comments']['#default_value']) {
    $node_types = array_keys(array_filter($form_state['values']['linkchecker_scan_nodetypes']));

    // If one or more node types have been selected.
    if (!empty($node_types)) {
      module_load_include('inc', 'linkchecker', 'linkchecker.batch');
      batch_set(_linkchecker_batch_import_nodes($node_types));

      // If comment scanning of node types has been selected.
      if ($form_state['values']['linkchecker_scan_comments'] > $form['settings']['linkchecker_scan_comments']['#default_value']) {
        batch_set(_linkchecker_batch_import_comments($node_types));
      }
    }
  }

  // If block scanning has been selected.
  if ($form_state['values']['linkchecker_scan_blocks'] > $form['settings']['linkchecker_scan_blocks']['#default_value']) {
    module_load_include('inc', 'linkchecker', 'linkchecker.batch');
    batch_set(_linkchecker_batch_import_block_custom());
  }
}

/**
 * Submit callback.
 *
 * Analyze fields in all node types, comments, custom blocks.
 */
function linkchecker_analyze_links_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  unset($form_state['values']['linkchecker_analyze'], $form_state['values']['linkchecker_clear_analyze']);

  // Save form settings.
  system_settings_form_submit($form, $form_state);

  // Start batch and analyze all nodes.
  $node_types = array_keys(array_filter(variable_get('linkchecker_scan_nodetypes', array())));
  if (!empty($node_types)) {
    module_load_include('inc', 'linkchecker', 'linkchecker.batch');
    batch_set(_linkchecker_batch_import_nodes($node_types));
    if (variable_get('linkchecker_scan_comments', 0)) {
      batch_set(_linkchecker_batch_import_comments($node_types));
    }
  }

  if (variable_get('linkchecker_scan_blocks', 0)) {
    module_load_include('inc', 'linkchecker', 'linkchecker.batch');
    batch_set(_linkchecker_batch_import_block_custom());
  }
}

/**
 * Submit callback.
 *
 * Clear link data and analyze fields in all content types, comments, custom
 * blocks.
 */
function linkchecker_clear_analyze_links_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  unset($form_state['values']['linkchecker_analyze'], $form_state['values']['linkchecker_clear_analyze']);

  // Save form settings.
  system_settings_form_submit($form, $form_state);

  db_truncate('linkchecker_block_custom')->execute();
  db_truncate('linkchecker_comment')->execute();
  db_truncate('linkchecker_node')->execute();
  db_truncate('linkchecker_link')->execute();

  // Start batch and analyze all nodes.
  $node_types = array_keys(array_filter(variable_get('linkchecker_scan_nodetypes', array())));
  if (!empty($node_types)) {
    module_load_include('inc', 'linkchecker', 'linkchecker.batch');
    batch_set(_linkchecker_batch_import_nodes($node_types));
    if (variable_get('linkchecker_scan_comments', 0)) {
      batch_set(_linkchecker_batch_import_comments($node_types));
    }
  }

  if (variable_get('linkchecker_scan_blocks', 0)) {
    module_load_include('inc', 'linkchecker', 'linkchecker.batch');
    batch_set(_linkchecker_batch_import_block_custom());
  }
}
