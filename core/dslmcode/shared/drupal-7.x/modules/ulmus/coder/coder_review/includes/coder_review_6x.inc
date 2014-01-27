<?php
/**
 * @file
 * This include file implements coder functionality for 5.x -> 6.x upgrades.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_6x_reviews() {
  $argex = '(((\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'\'|"")';

  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_menu$',
    '#value' => '\$items\[\]\s*=|if\s*\(\$may_cache\)',
    '#warning' => array(
      '#text' => 'The menu system has been completely over-hauled in 6.x.',
      '#link' => _drupalnode(103114),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_menu$',
    '#value' => '(for|foreach|while)\s*\(',
    '#warning' => array(
      '#text' => 'The menu system has been completely over-hauled in 6.x, and if you are looping, you are probably doing something wrong.',
      '#link' => _drupalnode(103114),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_form_alter\s*\(\$',
    '#warning' => array(
      '#text' => '!hook_form_alter() parameters have changed',
      '#args' => array(
        '!hook_form_alter' => _drupalapi('hook_form_alter', 6),
      ),
      '#link' => _drupalnode(144132, 'form-alter'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_link_alter\s*\(\$',
    '#warning' => array(
      '#text' => '!hook_link_alter() parameters have changed',
      '#args' => array(
        '!hook_link_alter' => _drupalapi('hook_link_alter', 6),
      ),
      '#link' => _drupalnode(114774, 'link-alter'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_profile_alter\s*\(\$',
    '#warning' => array(
      '#text' => '!hook_profile_alter() parameters have changed',
      '#args' => array(
        '!hook_profile_alter' => _drupalapi('hook_profile_alter', 6),
      ),
      '#link' => _drupalnode(114774, 'profile-alter'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_mail_alter\s*\([^,]+,',
    '#warning' => array(
      '#text' => '!hook_mail_alter() parameters have changed',
      '#args' => array(
        '!hook_mail_alter' => _drupalapi('hook_mail_alter', 6),
      ),
      '#link' => _drupalnode(114774, 'mail-alter'),
    ),
  );
  $url_l_warning =  array(
    '#text' => '!url() and !l() arguments changed, if you have a lot of these use <a href="@script">this conversion script</a>',
    '#args' => array(
      '!url' => _drupalapi('url', 6),
      '!l' => _drupalapi('l', 6),
      '@script' => 'http://drupal.org/files/issues/replace.php_.txt',
    ),
    '#link' => _drupalnode(114774, 'url'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]l\s*\((' . $argex . '\s*,\s*){3,}(' . $argex . ')\s*\)',
    '#warning' => $url_l_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]url\s*\((' . $argex . '\s*,\s*){2,}(' . $argex . ')\s*\)',
    '#warning' => $url_l_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'global \$locale',
    '#warning' => '$locale became $language',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '(taxonomy_node_get_terms|taxonomy_node_get_terms_by_vocabulary|taxonomy_node_save|taxonomy_node_delete)\s*\(\s*(\d+|\$(nid|node->nid))',
    '#warning' => array(
      '#text' => '!taxonomy_node_get_terms(), !taxonomy_node_get_terms_by_vocabulary(), !taxonomy_node_save and !taxonomy_node_delete() now take a full $node object, not just a nid (node id).',
      '#args' => array(
        '!taxonomy_node_get_terms' => _drupalapi('taxonomy_node_get_terms', 6),
        '!taxonomy_node_get_terms_by_vocabulary' => _drupalapi('taxonomy_node_get_terms_by_vocabulary', 6),
        '!taxonomy_node_save' => _drupalapi('taxonomy_node_save', 6),
        '!taxonomy_node_delete' => _drupalapi('taxonomy_node_delete', 6),
      ),
      '#link' => _drupalnode(114774, 'taxonomy-revisions'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]strtr\s*\(\s*format_plural\s*\(',
    '#warning' => array(
      '#text' => '!format_plural() accepts replacements, you no longer need to use !strtr()',
      '#args' => array(
        '!format_plural' => _drupalapi('format_plural', 6),
        '!strtr' => _phpapi('strtr'),
      ),
      '#link' => _drupalnode(114774, 'format-plural'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'watchdog\s*\(\s*\'\',\s*t\(\'',
    '#warning' => array(
      '#text' => 'Parameters of !watchdog() changed, you <em>must</em> remove calls to !t()',
      '#args' => array(
        '!watchdog' => _drupalapi('watchdog', 6),
        '!t' => _drupalapi('t', 6),
      ),
      '#link' => _drupalnode(114774, 'watchdog_parameters'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]cache_set\s*\(\s*[^,]+,\s*([\'"]|\$table)',
    '#warning' => array(
      '#text' => 'Changes to !cache_set() parameter order',
      '#args' => array(
        '!cache_set' => _drupalapi('cache_set', 6),
      ),
      '#link' => _drupalnode(114774, 'cache-set-parameter-order'),
    ),
  );
  $cache_serialize_warning = array(
    '#text' => '!cache_set() and !cache_get() automatically (un)serialize complex data types',
    '#args' =>  array(
      '!cache_set' => _drupalapi('cache_set', 6),
      '!cache_get' => _drupalapi('cache_get', 6),
    ),
    '#link' => _drupalnode(114774, 'cache-data-parameter'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]cache_set\s*\(\s*[^\)]+,\s*serialize\s*\(\s*',
    '#warning' => $cache_serialize_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]unserialize\s*\(\s*cache_get\s*\(',
    '#warning' => $cache_serialize_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '\$_SERVER\s*\[\s*[\'"]REMOTE_ADDR[\'"]\s*\]',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => 'Use new !ip_address() function instead of $_SERVER[\'REMOTE_ADDR\']',
      '#args' => array(
        '!ip_address' => _drupalapi('ip_address', 6),
      ),
      '#link' => _drupalnode(114774, 'ip-address'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]file_check_upload\s*\(',
    '#warning' => array(
      '#text' => '!file_check_upload() merged into !file_save_upload()',
      '#args' => array(
        '!file_check_upload' => _drupalapi('file_check_upload', 5),
        '!file_save_upload' => _drupalapi('file_save_upload', 6),
      ),
      '#link' => _drupalnode(114774, 'file-check-upload'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]file_save_upload\s*\([^,]+\s*,\s*(\$dest|\$destination|\'\'|"")\s*',
    '#never' => 'function\s+file_save_upload',
    '#warning' => array(
      '#text' => 'Parameters for !file_save_upload() have changed',
      '#args' => array(
        '!file_save_upload' => _drupalapi('file_save_upload', 6),
      ),
      '#link' => _drupalnode(114774, 'file-check-upload'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '\{file_revisions\}',
    '#warning' => 'The {' . 'file_revisions} table is now {upload}',
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_6x_callback',
  );

  /*
   * @{
   * FAPI rules.
   */

  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '(\$form\s*\[\s*[\'"]#base[\'"]|[\'"]#base[\'"]\s*=>)',
    '#warning' => 'FormAPI\'s #base property is gone, manually populate the $form[\'#submit\'], $form[\'#validate\'], and $form[\'#theme\'] elements with the proper function names',
  );
  $formapi_element_validate_warning = array(
    '#text' => 'Validation for specific form elements now uses the #element_validate property',
    '#link' => _drupalnode(144132, 'element-validate'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '\$form\s*\[\s*[\'"]#validate[\'"]\]\[[\'"]',
    '#warning' => $formapi_element_validate_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_elements$',
    '#value' => '\s*[\'"]#validate[\'"]\s*=>\s*',
    '#warning' => $formapi_element_validate_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '(\$form\s*\[\s*[\'"]#multistep[\'"]|[\'"]#multistep[\'"]\s*=>)',
    '#warning' => '#multistep is gone, use $form_state instead',
  );
  $form_validate_and_submit_warning = array(
    '#text' => 'The parameters for form validation and submission functions have changed to $form, &$form_state.',
    '#link' => _drupalnode(144132, 'process-params'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_(validate|submit)\s*\(\s*\$form_id',
    '#warning' => $form_validate_and_submit_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_(validate|submit)\s*\(\s*\$form\s*,\s*\$form_state\s*\)[^;]',
    '#warning' => $form_validate_and_submit_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_(prerender)\s*\(\s*\$form_id',
    '#warning' => array(
      '#text' => 'The parameters for form prerender functions have changed to $form.',
      '#link' => _drupalnode(144132, 'pre-render'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '\$form\[[\'"]#submit[\'"]\]\[[\'"]',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => '$form[\'#submit\'] and $form[\'#validate\'] no longer support custom parameters',
      '#link' => _drupalnode(144132, 'custom-params'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]form_set_value\s*\([^,]+(,\s*[^,\)]+){0,1}\)',
    '#warning' => array(
      '#text' => '!form_set_value() parameters have changed',
      '#args' => array(
        '!form_set_value' => _drupalapi('form_set_value', 6),
      ),
      '#link' => _drupalnode(144132, 'set-value'),
    ),
    '#not' => 'array\s*\(',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]custom_url_rewrite\s*\(',
    '#warning' => array(
      '#text' => 'In place of !custom_url_rewrite(), use !custom_url_rewrite_inbound() or !custom_url_rewrite_outbound()',
      '#args' => array(
        '!custom_url_rewrite' => _drupalapi('custom_url_rewrite', 5),
        '!custom_url_rewrite_inbound' => _drupalapi('custom_url_rewrite_inbound', 6),
        '!custom_url_rewrite_outbound' => _drupalapi('custom_url_rewrite_outbound', 6),
      ),
      '#link' => _drupalnode(114774, 'custom-url-rewrite'),
    ),
  );
  $hook_info_auth_warning  = array(
    '#text' => 'hook no longer exists, use !hook_form_alter() to swap your own validation handler',
    '#args' => array(
      '!hook_form_alter' => _drupalapi('hook_form_alter', 6),
    ),
    '#link' => _drupalnode(114774, 'dist-auth'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_(info)\s*\(\s*\$field',
    '#warning' => $hook_info_auth_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '_(auth)\s*\(\s*\$user',
    '#warning' => $hook_info_auth_warning,
  );

  /*
   * @} End of FAPI rules.
   */

  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(help)\s*\(\s*[^,]+\)',
    '#not' => '_drush_help\(',
    '#warning' => array(
      '#text' => 'The arguments to !hook_help() have changed',
      '#args' => array(
        '!hook_help' => _drupalapi('hook_help', 6),
      ),
      '#link' => _drupalnode(114774, 'hook-help'),
      '#description' => 'Change the first two lines to <code>function yourmodule_help($path, $arg) {' . "\n" . ' switch ($path) { ...</code>.',
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '\$form(_values)?\s*\[\s*[\'"]?op[\'"]?\s*\]',
    '#warning' => 'replace $form[\'op\'] with $form_state[\'values\'][\'op\']',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_(un)?install$|_update_[0-9]+$',
    '#value' => '\$GLOBALS\[[\'"]?db_type[\'"]?\]',
    '#warning' => array(
      '#text' => 'A new schema API has been added in 6.x',
      '#link' => _drupalnode(146843),
      '#description' => 'This patch caused changes to the format of hook_install(), hook_uninstall(), and hook_update_N(). No longer are switch statements done on $GLOBALS[\'db_type\']; instead, use the variety of schema API functions to perform table manipulation.',
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_submit$|_validate$',
    '#value' => '\$form(_values)?\[[\'"][A-Za-z]',
    '#never' => '[\s\(]form_error\(',
    '#warning' => 'use $form_state[\'values\'] instead, which is where the values are stored after a submit',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]theme_get_function\s*\(',
    '#warning' => array(
      '#text' => '!theme_get_function() has been deprecated because of template theming; see !theme_get_registry()',
      '#args' => array(
        '!theme_get_function' => _drupalapi('theme_get_function', 5),
        '!theme_get_registry' => _drupalapi('theme_get_registry', 6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]db_num_rows\s*\(',
    '#warning' => array(
      '#text' => '!db_num_rows() has been deprecated',
      '#args' => array(
        '!db_num_rows' => _drupalapi('db_num_rows', 5),
      ),
      '#link' => _drupalnode(114774, 'db-num-rows'),
      '#description' => 'The db_num_rows() method was removed from the database abstraction layer in 6.x core, as it was a database dependent method.  Use SELECT COUNT(*) or some other appropriate solutions',
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_retrieve_form\s*\(' . $argex . '\s*\)',
    '#warning' => array(
      '#text' => 'Parameters for !drupal_retrieve_form() have changed, add $form_state as a second argument',
      '#args' => array(
        '!drupal_retrieve_form' => _drupalapi('drupal_retrieve_form', 6),
      ),
      '#link' => _drupalnode(144132, 'retrieve-form'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_menu$',
    '#value' => 'node\/add\/',
    '#source' => 'all',
    '#warning' => array(
      '#text' => 'The node/add/$type menu items are now auto-generated by the menu system in 6.x. You should not declare them in your menu hook.',
      '#link' => _drupalnode(114774, 'node_add_summary'),
    ),
  );
  $comment_form_location_warning = array(
    '#text' => 'Comment settings are now per node type.',
    '#link' => _drupalnode(114774, 'comment_settings_per_node_type'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'variable_(get|set|del)\(\s*[\'"]comment_form_location[\'"]\s*(,|\))',
    '#source' => 'allphp',
    '#warning' => $comment_form_location_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '=\s*[\'"]comment_form_location[\'"]\s*;',
    '#source' => 'allphp',
    '#warning' => $comment_form_location_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'admin\/content\/comment\/settings',
    '#source' => 'quote',
    '#warning' => $comment_form_location_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_access_rebuild\s*\(',
    '#function' => '_disable$|_enable$',
    '#warning' => array(
      '#text' => '!node_access_rebuild() should not be called from !hook_enable() or !hook_disable() functions any more.',
      '#args' => array(
        '!node_access_rebuild' => _drupalapi('node_access_rebuild', 6),
        '!hook_enable' => _drupalapi('hook_enable', 6),
        '!hook_disable' => _drupalapi('hook_disable', 6),
      ),
      '#link' => _drupalnode(114774, 'node_access_rebuild_batch'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'admin\/logs',
    '#source' => 'all',
    '#warning' => array(
      '#text' => 'admin' . '/logs has been renamed to admin/reports, including all subpages.',
      '#link' => _drupalnode(114774, 'locale'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'user_access\s*\(\s*\'\s*administer\s+access\s+control\s*\'\s*\)|admin\/user\/access',
    '#source' => 'all',
    '#warning' => array(
      '#text' => 'The "administer access control" permission has been renamed to "administer permissions", and the path \'admin/' . 'user/access\' to \'admin/user/permissions\'.',
      '#link' => _drupalnode(114774, 'permissions'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '(\$form\s*\[\s*[\'"]#DANGEROUS_SKIP_CHECK[\'"]|[\'"]#DANGEROUS_SKIP_CHECK[\'"]\s*=>)',
    '#warning' => array(
      '#text' => 'Support for form property #DANGEROUS_SKIP_CHECK has been removed.',
      '#link' => _drupalnode(114774, 'choice_check'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]locale_refresh_cache\s*\(',
    '#warning' => array(
      '#text' => '!locale_refresh_cache() is deprecated.  Use !cache_clear_all() instead.',
      '#args' => array(
        '!locale_refresh_cache' => _drupalapi('locale_refresh_cache', 5),
        '!cache_clear_all' => _drupalapi('cache_clear_all', 6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]db_next_id\s*\(',
    '#warning' => array(
      '#text' => '!db_next_id() is deprecated.  Use !db_last_insert_id() instead.',
      '#args' => array(
        '!db_next_id' => _drupalapi('db_next_id', 5),
        '!db_last_insert_id' => _drupalapi('db_last_insert_id', 6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]menu_set_location\s*\(',
    '#warning' => array(
      '#text' => '!menu_set_location() is deprecated.  Use !drupal_set_breadcrumb() to set a custom breadcrumb or !menu_set_item() to set the current location in the menu tree.',
      '#args' => array(
        '!menu_set_location' => _drupalapi('menu_set_location', 5),
        '!drupal_set_breadcrumb' => _drupalapi('drupal_set_breadcrumb', 6),
        '!menu_set_item' => _drupalapi('menu_set_item', 6),
      ),
      '#link' => _drupalnode(114774, 'menu_set_location'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_get_vocabulary\s*\(',
    '#warning' => array(
      '#text' => '!taxonomy_get_vocabulary() is deprecated.  Use !taxonomy_vocabulary_load() instead.',
      '#args' => array(
        '!taxonomy_get_vocabulary' => _drupalapi('taxonomy_get_vocabulary', 5),
        '!taxonomy_vocabulary_load' => _drupalapi('taxonomy_vocabulary_load', 6),
      ),
      '#link' => _drupalnode(114774, 'taxonomy-load'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]db_result\s*\((' . $argex . ')\s*,\s*' . $argex . '\);$',
    '#warning' => array(
      '#text' => 'Remove $row argument from !db_result() method',
      '#args' => array(
        '!db_result' => _drupalapi('db_result', 6),
      ),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'watchdog\s*\(\s*[\'"]debug[\'"]\s*,\s*',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => 'Parameters of !watchdog() changed, you use $severity WATCHDOG_DEBUG instead of $type \'debug\'',
      '#args' => array(
        '!watchdog' => _drupalapi('watchdog', 6),
      ),
      '#link' => _drupalnode(114774, 'watchdog_logging'),
    ),
  );

  /*
   * @{
   * Book module rules.
   */

  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_admin_orphan\s*\(',
    '#warning' => array(
      '#text' => '!book_admin_orphan() is deprecated',
      '#args' => array(
        '!book_admin_orphan' => _drupalapi('book_admin_orphan', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_content\s*\(',
    '#warning' => array(
      '#text' => '!book_content() is deprecated',
      '#args' => array(
        '!book_content' => _drupalapi('book_content', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_form\s*\(',
    '#warning' => array(
      '#text' => '!book_form() is deprecated',
      '#args' => array(
        '!book_form' => _drupalapi('book_form', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_insert\s*\(',
    '#warning' => array(
      '#text' => '!book_insert() is deprecated',
      '#args' => array(
        '!book_insert' => _drupalapi('book_insert', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_location\s*\(',
    '#warning' => array(
      '#text' => '!book_location() is deprecated',
      '#args' => array(
        '!book_location' => _drupalapi('book_location', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_location_down\s*\(',
    '#warning' => array(
      '#text' => '!book_location_down() is deprecated',
      '#args' => array(
        '!book_location_down' => _drupalapi('book_location_down', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_node_visitor_html_post\s*\(',
    '#warning' => array(
      '#text' => '!book_node_visitor_html_post() is deprecated',
      '#args' => array(
        '!book_node_visitor_html_post' => _drupalapi('book_node_visitor_html_post', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_node_visitor_html_pre\s*\(',
    '#warning' => array(
      '#text' => '!book_node_visitor_html_pre() is deprecated',
      '#args' => array(
        '!book_node_visitor_html_pre' => _drupalapi('book_node_visitor_html_pre', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_recurse\s*\(',
    '#warning' => array(
      '#text' => '!book_recurse() is deprecated',
      '#args' => array(
        '!book_recurse' => _drupalapi('book_recurse', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_toc_recurse\s*\(',
    '#warning' => array(
      '#text' => '!book_toc_recurse() is deprecated',
      '#args' => array(
        '!book_toc_recurse' => _drupalapi('book_toc_recurse', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_tree\s*\(',
    '#warning' => array(
      '#text' => '!book_tree() is deprecated',
      '#args' => array(
        '!book_tree' => _drupalapi('book_tree', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_tree_recurse\s*\(',
    '#warning' => array(
      '#text' => '!book_tree_recurse() is deprecated',
      '#args' => array(
        '!book_tree_recurse' => _drupalapi('book_tree_recurse', 5),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_admin_edit\s*\((' . $argex . '\s*)\)',
    '#warning' => array(
      '#text' => 'Parameters to !book_admin_edit() have changed',
      '#args' => array(
        '!book_admin_edit' => _drupalapi('book_admin_edit', 6),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](book_toc\s*\((' . $argex . '\s*)\)|book_toc\s*\(\s*\))',
    '#warning' => array(
      '#text' => 'Parameters to !book_toc() have changed',
      '#args' => array(
        '!book_toc' => _drupalapi('book_toc', 6),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_export_html\s*\((' . $argex . '\s*,\s*)',
    '#warning' => array(
      '#text' => 'Parameters to !book_export_html() have changed',
      '#args' => array(
        '!book_export_html' => _drupalapi('book_export_html', 6),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](book_export\s*\((' . $argex . '\s*)\)|book_export\s*\(\s*\))',
    '#warning' => array(
      '#text' => 'Parameters to !book_export() have changed',
      '#args' => array(
        '!book_export' => _drupalapi('book_export', 6),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_outline\s*\(\$(nid|node->nid)',
    '#warning' => array(
      '#text' => 'Parameters to !book_outline() have changed',
      '#args' => array(
        '!book_outline' => _drupalapi('book_outline', 6),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_prev\s*\(\$node',
    '#warning' => array(
      '#text' => 'Parameters to !book_prev() have changed',
      '#args' => array(
        '!book_prev' => _drupalapi('book_prev', 6),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_next\s*\(\$node',
    '#warning' => array(
      '#text' => 'Parameters to !book_next() have changed',
      '#args' => array(
        '!book_next' => _drupalapi('book_next', 6),
      ),
      '#link' => _drupalnode(114774, 'book_module'),
    ),
  );

  /*
   * @} End of Book module rules.
   */

  $rules[] = array(
    '#type' => 'regex',
    '#value' => '\s*[\'"]#value[\'"]\s*=>\s*t\s*\(\s*[\'"]Submit[\'"]\s*\)',
    '#source' => 'allphp',
    '#warning' => 'When labelling buttons, make it clear what the button does, "Submit" is too generic.',
    '#severity' => 'minor',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_nodeapi$',
    '#source' => 'allphp',
    '#value' => '(case\s+[\'"]submit[\'"]\s*:)|(==\s*[\'"]submit[\'"])',
    '#warning' => array(
      '#text' => '!hook_nodeapi(\'submit\') has been replaced by op=\'presave\'',
      '#args' => array(
        '!hook_nodeapi' => _drupalapi('hook_nodeapi', 6),
      ),
      '#link' => _drupalnode(114774, 'nodeapi_presave'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]drupal_mail\s*\(\s*[^,]+,\s*(\$to|\$recipient|\$[a-zA-Z_]+?\->mail|(\'|").+@.+(\'|"))',
    '#warning' => array(
      '#text' => 'Parameters to !drupal_mail() have changed',
      '#args' => array(
        '!drupal_mail' => _drupalapi('drupal_mail', 6),
      ),
      '#link' => _drupalnode(189367),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '^(create\s+table\s+|alter\s+table\s+|drop\s+table\s+)',
    '#source' => 'quote',
    '#warning' => array(
      '#text' => 'Use the new Schema API to create, alter and drop tables rather than db_query()',
      '#link' => _drupalnode(146862),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]user_authenticate\s*\((' . $argex . '\s*,\s*)(' . $argex . ')\s*\)',
    '#warning' => array(
      '#text' => 'Parameters to !user_authenticate have changed',
      '#args' => array(
        '!user_authenticate' => _drupalapi('user_authenticate', 6),
      ),
      '#link' => _drupalnode(114774, 'user_authenticate'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(access)\s*\((' . $argex . '\s*,\s*)(' . $argex . ')\s*\)',
    '#warning' => array(
      '#text' => 'Parameters to !hook_access() have changed',
      '#args' => array(
        '!hook_access' => _drupalapi('hook_access', 6),
      ),
      '#link' => _drupalnode(114774, 'hook_access'),
    ),
    '#function-not' => '^[^_]\w+_(node|field)_access$',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '(node|user|menu|menu_link|taxonomy_vocabulary|contact|filter_format|forum_term|aggregator_feed|aggregator_category)_load\(arg\([0-9]\)\)',
    '#warning' => array(
      '#text' => 'Use !menu_get_object() to get an object based on your path',
      '#args' => array(
        '!menu_get_object' => _drupalapi('menu_get_object', 6),
      ),
      '#link' => _drupalnode(114774, 'menu_get_object'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_submit$',
    '#value' => '\s+return\s+(' . $argex . ');',
    '#warning' => array(
      '#text' => 'Submit handlers use $form_state[\'redirect\'] rather than returning urls',
      '#link' => _drupalnode(144132, 'redirect'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_menu$',
    '#source' => 'allphp',
    '#value' => '\'title\'\s*=>\s*t\(|\'description\'\s*=>\s*t\(',
    '#warning' => array(
      '#text' => 'Menu item titles and descriptions should now no longer be wrapped in t() calls.',
      '#link' => _drupalnode(140311),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(forms)\s*\(\s*[^,]+\)',
    '#warning' => array(
      '#text' => 'The arguments to !hook_forms() have changed',
      '#args' => array(
        '!hook_forms' => _drupalapi('hook_forms', 6),
      ),
      '#link' => _drupalnode(144132, 'hook-forms'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '\$form\s*\[\s*[\'"]#pre_render[\'"]\s*\]\[\s*[\'"].*[\'"]\s*\]\s*=',
    '#warning' => array(
      '#text' => 'The form API for the #pre_render property has changed structure.',
      '#link' => _drupalnode(144132, 'pre-render'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_menu$',
    '#value' => '[\'"]access callback.*=.*\(',
    '#source' => 'allphp',
    '#warning' => array(
      '#text' => "The value for the 'access callback' must always be a string which is the the name of the function - never a function call. It may also be assigned the value TRUE or FALSE if the callback is always (or never) accessible.",
      '#link' => _drupalnode(109157),
    ),
  );

  $review = array(
    '#title' => 'Converting 5.x modules to 6.x',
    '#link' => _drupalnode(114774),
    '#rules' => $rules,
    '#severity' => 'critical',
    '#version' => 2,
    '#image' => 'images/6.png',
  );
  return array('upgrade6x' => $review);
}

/**
 * Define the rule callbacks for 6.x, see do_coder_review_callback().
 */
function _coder_review_6x_callback(&$coder_args, $review, $rule, $lines, &$results) {
  // Only perform this check on module's (not includes).
  $filename = $coder_args['#filename'];
  if (_substr($filename, -7) == '.module') {
    // If there are any theme functions, make sure that a hook_theme exists.
    $theme = $hook_theme = FALSE;
    foreach ($lines as $lineno => $line) {
      if (preg_match('/function theme_/', $line[0])) {
        if (!$theme) {
          $theme = TRUE;
          $theme_line = $line[0];
          $theme_lineno = $lineno;
        }
      }
      if (preg_match('/function \w+_theme\(/', $line[0])) {
        $hook_theme = TRUE;
      }
    }
    if ($theme && !$hook_theme) {
      $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
      $tmprule = $rule;
      $tmprule['#warning'] = array(
        '#text' => 'new !hook_theme() function is required to register theme_ functions',
        '#args' => array(
          '!hook_theme' => _drupalapi('hook_theme', 6),
        ),
        '#link' => _drupalnode(114774, 'theme_registry'),
      );
      _coder_review_error($results, $tmprule, $severity_name, $theme_lineno, $theme_line, $coder_args['#ignores']);
    }

    // Read the .info file.
    $filename = _substr(realpath($filename), 0, -7) . '.info';
    if (file_exists($filename)) {
      $lines = file($filename);
      if ($lines) {
        $core = FALSE;
        foreach ($lines as $lineno => $line) {
          if (preg_match('/^dependencies\s*=/', $line)) {
            $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
            $tmprule = $rule;
            $tmprule['#warning'] = array(
              '#warning' => 'New syntax for .info files, use dependencies[]',
              '#link' => _drupalnode(114774, 'info'),
            );
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
          }
          if (preg_match('/^core\s*=/', $line)) {
            $core = TRUE;
          }
        }
        if (!$core) {
          $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
          $tmprule = $rule;
          $tmprule['#warning'] = array(
            '#text' => 'New syntax for .info files files requires core=6.x',
            '#link' => _drupalnode(114774, 'info'),
          );
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }

    // Check that there is a translations directory and not a po directory.
    $dir = dirname($filename);
    if (file_exists($dir . '/po') && !file_exists($dir . '/translations')) {
      $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
      $tmprule = $rule;
      $tmprule['#warning'] = array(
        '#text' => 'Translations moved from ./po to ./translations',
        '#link' => _drupalnode(114774, 'translations_directory'),
      );
      _coder_review_error($results, $tmprule, $severity_name, -1, $dir);
    }
  }
}
