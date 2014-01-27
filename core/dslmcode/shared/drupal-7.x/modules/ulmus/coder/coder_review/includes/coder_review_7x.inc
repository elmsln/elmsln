<?php
/**
 * @file
 * This include file implements coder functionality for 6.x -> 7.x upgrades.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_7x_reviews() {
  $argex = '(((&?\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'\'|"")';

  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_7x_comment_doxygen_file_callback',
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_7x_info_file_callback',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'php',
    '#value' => '[\s=\(]update_sql\s*\(',
    '#warning' => array(
      '#text' => '!update_sql() is now deprecated',
      '#args' => array(
        '!update_sql' => _drupalapi('update_sql', 6),
      ),
      '#link' => _drupalnode(224333, 'update_sql'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'php',
    '#value' => 'return\s+(array|\$ret)',
    '#warning' => array(
      '#text' => 'Update hooks now return translated strings or throw exceptions',
      '#link' => _drupalnode(224333, 'update_sql'),
    ),
    '#function' => '_update_[0-9]+$',
    '#filename' => array('install'),
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_7x_module_implements_callback',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '((require|include)(_once)?).+[\'"]\.\/',
    '#warning' => array(
      '#text' => 'Use absolute path, constructed from DRUPAL_ROOT, when including a file.',
      '#link' => _drupalnode(224333, 'absolute_includes'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]time\s*\([\w\d\'"]*\)',
    '#warning' => array(
      '#text' => 'For improved performance, it is highly recommended that !time() is replaced with REQUEST_TIME',
      '#args' => array(
        '!time' => _phpapi('time'),
      ),
      '#link' => _drupalnode(224333, 'time'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_rebuild_code_registry\s*\(',
    '#warning' => array(
      '#text' => '!drupal_rebuild_code_registry() function has been renamed to !registry_rebuild()',
      '#args' => array(
        '!drupal_rebuild_code_registry' => _drupalapi('drupal_rebuild_code_registry', 6),
        '!registry_rebuild' => _drupalapi('registry_rebuild', 7),
      ),
      '#link' => _drupalnode(224333, 'rebuild_functions'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_uninstall_module\s*\(',
    '#warning' => array(
      '#text' => '!drupal_uninstall_module() has been renamed to !drupal_uninstall_modules() and now takes an array of module names.',
      '#args' => array(
        '!drupal_uninstall_module' => _drupalapi('drupal_uninstall_module', 6),
        '!drupal_uninstall_modules' => _drupalapi('drupal_uninstall_modules', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_uninstall_modules'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_http_request\s*\(\s*(' . $argex . '\s*,\s*){2,}(' . $argex . ')\s*\)',
    '#warning' => array(
      '#text' => 'Parameters to !drupal_http_request() have changed.',
      '#args' => array(
        '!drupal_http_request' => _drupalapi('drupal_http_request', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_http_request_parameters'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => 'admin\/reports\/settings',
    '#warning' => array(
      '#text' => 'Statistics settings have moved to "admin/config/system/statistics" and there is a new "administer statistics" permission.',
      '#link' => _drupalnode(224333, 'moved_statistics_settings'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]module_rebuild_cache\s*\(',
    '#warning' => array(
      '#text' => '!module_rebuild_cache() has been renamed to !system_get_module_data().',
      '#args' => array(
        '!module_rebuild_cache' => _drupalapi('module_rebuild_cache', 6),
        '!system_get_module_data' => _drupalapi('system_get_module_data', 7),
      ),
      '#link' => _drupalnode(224333, 'system_get_module_data'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]system_theme_data\s*\(',
    '#warning' => array(
      '#text' => '!system_theme_data() has been renamed to !system_get_theme_data().',
      '#args' => array(
        '!system_theme_data' => _drupalapi('system_theme_data', 6),
        '!system_get_theme_data' => _drupalapi('system_get_theme_data', 7),
      ),
      '#link' => _drupalnode(224333, 'system_get_module_data'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_set_html_head\s*\(',
    '#warning' => array(
      '#text' => '!drupal_set_html_head() has been renamed to !drupal_add_html_head().',
      '#args' => array(
        '!drupal_set_html_head' => _drupalapi('drupal_set_html_head', 6),
        '!drupal_add_html_head' => _drupalapi('drupal_add_html_head', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_set_html_head'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_eval\s*\(',
    '#warning' => array(
      '#text' => "!drupal_eval() has been renamed to !php_eval() and should be wrapped in a module_exists('php') check.",
      '#args' => array(
        '!drupal_eval' => _drupalapi('drupal_eval', 6),
        '!php_eval' => _drupalapi('php_eval', 7),
      ),
      '#link' => _drupalnode(224333, 'php_eval'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_set_content\s*\(',
    '#warning' => array(
      '#text' => '!drupal_set_content() has been renamed to !drupal_add_region_content().',
      '#args' => array(
        '!drupal_set_content' => _drupalapi('drupal_set_content', 6),
        '!drupal_add_region_content' => _drupalapi('drupal_add_region_content', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_set_content'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_get_content\s*\(',
    '#warning' => array(
      '#text' => '!drupal_get_content() has been renamed to !drupal_get_region_content().',
      '#args' => array(
        '!drupal_get_content' => _drupalapi('drupal_get_content', 6),
        '!drupal_get_region_content' => _drupalapi('drupal_get_region_content', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_set_content'),
    ),
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_7x_cache_implementation_callback',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]set_time_limit\s*\(',
    '#function-not' => '^drupal_set_time_limit$',
    '#warning' => array(
      '#text' => 'Use !drupal_set_time_limit() instead of !set_time_limit().',
      '#args' => array(
        '!drupal_set_time_limit' => _drupalapi('drupal_set_time_limit', 7),
        '!set_time_limit' => _phpapi('set_time_limit'),
      ),
      '#link' => _drupalnode(224333, 'time_limit'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(](drupal_set_header|drupal_get_headers)\s*\(',
    '#warning' => array(
      '#text' => '!drupal_set_header() has been renamed to !drupal_add_http_header() and its parameters changed, and !drupal_get_headers() renamed to !drupal_get_http_header()',
      '#args' => array(
        '!drupal_set_header' => _drupalapi('drupal_set_header', 6),
        '!drupal_get_headers' => _drupalapi('drupal_get_headers', 6),
        '!drupal_add_http_header' => _drupalapi('drupal_add_http_header', 7),
        '!drupal_get_http_header' => _drupalapi('drupal_get_http_header', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_set_header_renamed'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(,]WATCHDOG_EMERG.*$',
    '#not' => 'WATCHDOG_EMERGENCY',
    '#warning' => array(
      '#text' => 'WATCHDOG_EMERG was renamed to WATCHDOG_EMERGENCY',
      '#link' => _drupalnode(224333, 'watchdog_emerg'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_urlencode\s*\(',
    '#warning' => array(
      '#text' => 'Use !drupal_encode_path() instead of !drupal_urlencode().',
      '#args' => array(
        '!drupal_encode_path' => _drupalapi('drupal_encode_path', 7),
        '!drupal_urlencode' => _drupalapi('drupal_urlencode', 6),
      ),
      '#link' => _drupalnode(224333, 'remove-drupal-urlencode'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_search\s*\(',
    '#warning' => array(
      '#text' => '!hook_search() has been separated out into several other hooks: !hook_search_info(), !hook_search_admin(), !hook_search_execute(), !hook_search_reset(), !hook_search_status()',
      '#args' => array(
        '!hook_search' => _drupalapi('hook_search', 6),
        '!hook_search_info' => _drupalapi('hook_search_info', 7),
        '!hook_search_admin' => _drupalapi('hook_search_admin', 7),
        '!hook_search_execute' => _drupalapi('hook_search_execute', 7),
        '!hook_search_reset' => _drupalapi('hook_search_reset', 7),
        '!hook_search_status' => _drupalapi('hook_search_status', 7),
      ),
      '#link' => _drupalnode(224333, 'search-api'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]do_search\s*\(',
    '#warning' => array(
      '#text' => '!do_search() has been deprecated and instead modules should perform the search query using the "SearchQuery" extension.',
      '#args' => array(
        '!do_search' => _drupalapi('do_search', 6),
      ),
      '#link' => _drupalnode(224333, 'search-api'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(perm)\s*\(',
    '#warning' => array(
      '#text' => '!hook_perm() has been renamed to !hook_permission().',
      '#args' => array(
        '!hook_perm' => _drupalapi('hook_perm', 6),
        '!hook_permission' => _drupalapi('hook_permission', 7),
      ),
      '#link' => _drupalnode(224333, 'hook_permission'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_permission$',
    '#value' => '\s+array\s*\(\s*([\'"][a-zA-Z\s]+[\'"]\s*[,\)]\s*){1,}\s*;',
    '#warning' => array(
      '#text' => 'Permissions are required to have titles and descriptions in !hook_permission().',
      '#args' => array(
        '!hook_permission' => _drupalapi('hook_permission', 7),
      ),
      '#link' => _drupalnode(224333, 'descriptions_permissions'),
    ),
  );
  // @todo: does this properly check for DBTNG?
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => '^(select\s+.*\s+from\s+{permission}|insert\s+into\s+{permission}|update\s+{permission}\s+set|delete\s+from\s+{permission})',
    '#warning' => array(
      '#text' => "The 'permission' table has been renamed to 'role_permission' and has a different structure.",
      '#link' => _drupalnode(224333, 'permission_tables'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => '^use PHP for block visibility$',
    '#warning' => array(
      '#text' => 'The "use PHP for block visibility" permission has been replaced by the more generic "use PHP for settings" permission.',
      '#link' => _drupalnode(224333, 'php_permissions'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(access)\s*\(',
    '#function-not' => '^[^_]\w+_(node|field)_access$',
    '#warning' => array(
      '#text' => '!hook_access() removed in favor of !hook_node_access().',
      '#args' => array(
        '!hook_access' => _drupalapi('hook_access', 6),
        '!hook_node_access' => _drupalapi('hook_node_access', 7),
      ),
      '#link' => _drupalnode(224333, 'hook_node_access'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_(schema|update_\d+)$',
    '#value' => '[\'"]description[\'"]\s*=>\s*(t|st)\(',
    '#warning' => array(
      '#text' => 'Schema descriptions are no longer translated in !hook_schema()',
      '#args' => array(
        '!hook_schema' => _drupalapi('hook_schema', 6),
      ),
      '#link' => _drupalnode(224333, 'schema_translation'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]db_rewrite_sql\s*\(',
    '#warning' => array(
      '#text' => '!db_rewrite_sql() replaced with !hook_query_alter()',
      '#args' => array(
        '!db_rewrite_sql' => _drupalapi('db_rewrite_sql', 6),
        '!hook_query_alter' => _drupalapi('hook_query_alter', 7),
      ),
      '#link' => _drupalnode(224333, 'db_rewrite_sql'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_(schema|update_\d+)$',
    '#value' => '[\'"]description[\'"]\s*=>\s*.*?&lt;.*?&gt;',
    '#warning' => array(
      '#text' => 'Schema descriptions are now plain text instead of HTML.',
      '#link' => _drupalnode(224333, 'schema_html'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => 'db_query\s*\(\s*[\'"]select\s+count\s*\(\s*\*\s*\)\s+from\s+',
    '#warning' => array(
      '#text' => 'You may not want to use SELECT COUNT(*), if all you want to do is check for the existence of any rows, rather than actually counting the number of rows.',
      '#link' => _drupalnode(224333, 'select_count'),
    ),
    '#severity' => 'minor'
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'php',
    '#value' => '[\s\(]drupal_(un)?install_schema\s*\(',
    '#warning' => array(
      '#text' => 'A module no longer should explicitly install or uninstall its database schema in !hook_install() or !hook_uninstall().',
      '#args' => array(
        '!hook_install' => _drupalapi('hook_install', 7),
        '!hook_uninstall' => _drupalapi('hook_uninstall', 7),
      ),
      '#link' => _drupalnode(224333, 'install-schema'),
    ),
    '#function' => '_(un)?install$',
    '#function-not' => '^system_install$',
    '#filename' => array('install'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(menu_link_alter)\s*\(\s*(' . $argex . '\s*,\s*){1,}(' . $argex . ')\s*\)',
    '#warning' => array(
      '#text' => 'The parameters to !hook_menu_link_alter() have changed.',
      '#args' => array(
        '!hook_menu_link_alter' => _drupalapi('hook_menu_link_alter', 7),
      ),
      '#link' => _drupalnode(224333, 'hook_menu_link_alter'),
    ),
  );
  // @todo: this should also be in another review that gets run regularly.
  $rules[] = array(
    '#type' => 'callback',
    '#source' => 'allphp',
    '#value' => '_coder_review_7x_optional_block_callback',
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(block)\s*\(\s*\$op',
    '#warning' => array(
      '#text' => '!hook_block() has been split into a number of smaller hooks.',
      '#args' => array(
        '!hook_block' => _drupalapi('hook_block', 6),
      ),
      '#link' => _drupalnode(224333, 'remove_op'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]_comment_load\s*\(',
    '#warning' => array(
      '#text' => '!_comment_load() has been renamed to !comment_load()',
      '#args' => array(
        '!_comment_load' => _drupalapi('_comment_load', 6),
        '!comment_load' => _drupalapi('comment_load', 7),
      ),
      '#link' => _drupalnode(224333, 'comment_load'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_(menu|menu_alter)$',
    '#value' => '%_comment',
    '#warning' => array(
      '#text' => '%_comment wildcard has been renamed to %comment',
      '#link' => _drupalnode(224333, 'comment_load'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => '\{comments\}\s+WHERE\s+.*?\s*status\s*(!=|=|<>|>|<)\s*(0|1)',
    '#warning' => array(
      '#text' => 'Comment status values in the database have flipped so they match node status. We recommend you use constants like COMMENT_NOT_PUBLISHED in the future.',
      '#link' => _drupalnode(224333, 'comment_status'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]comment_validate\s*\(',
    '#warning' => array(
      '#text' => '!comment_validate() has been removed and !comment_form_validate() should be used instead.',
      '#args' => array(
        '!comment_validate' => _drupalapi('comment_validate', 6),
        '!comment_form_validate' => _drupalapi('comment_form_validate', 7),
      ),
      '#link' => _drupalnode(224333, 'comment_validate_removed'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]comment_node_url\s*\(',
    '#warning' => array(
      '#text' => '!comment_node_url() has been removed. Use "node/" .  $comment->nid to build URLs instead.',
      '#args' => array(
        '!comment_node_url' => _drupalapi('comment_node_url', 6),
      ),
      '#link' => _drupalnode(224333, 'comment_node_url'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]check_markup\s*\(\s*(' . $argex . '\s*,\s*){2}(\$check|FALSE|TRUE)',
    '#warning' => array(
      '#text' => 'Parameters for !check_markup() have changed',
      '#args' => array(
        '!check_markup' => _drupalapi('check_markup', 7),
      ),
      '#link' => _drupalnode(224333, 'check_markup_params'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]drupal_set_title\s*\(\s*(check_plain\s*\(|t\s*\(\s*[\'"][^@%]*(@\w|\%\w))',
    '#never' => 'PASS_THROUGH',
    '#warning' => array(
      '#text' => '!drupal_set_title() now uses !check_plain() by default',
      '#args' => array(
        '!drupal_set_title' => _drupalapi('drupal_set_title', 7),
        '!check_plain' => _drupalapi('check_plain', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_set_title'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+\w+_(filter)\s*\(',
    '#warning' => array(
      '#text' => '!hook_filter() has been removed in favour of !hook_filter_info().',
      '#args' => array(
        '!hook_filter_info' => _drupalapi('hook_filter_info', 7),
        '!hook_filter' => _drupalapi('hook_filter', 6),
      ),
      '#link' => _drupalnode(224333, 'hook_filter_info'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+\w+_(filter_tips)\s*\(',
    '#warning' => array(
      '#text' => '!hook_filter_tips() has been removed in favour of !hook_filter_info().',
      '#args' => array(
        '!hook_filter_info' => _drupalapi('hook_filter_info', 7),
        '!hook_filter_tips' => _drupalapi('hook_filter_tips', 6),
      ),
      '#link' => _drupalnode(224333, 'hook_filter_info'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '\$form\[.+?=\s*filter_form\(',
    '#warning' => array(
      '#text' => 'New #text_format to assign text format selection to fields.',
      '#link' => _drupalnode(224333, 'text_format'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => 'admin\/settings\/filters(\/.*?)?',
    '#warning' => array(
      '#text' => 'Administrative URLs in the Filter module have been renamed from plural to singular.',
      '#link' => _drupalnode(224333, 'filter_urls'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'php',
    '#value' => '[\s\(]taxonomy_get_tree\s*\(\s*(' . $argex . '\s*,\s*){2}(\$depth|-1)\s*[,\)]',
    '#warning' => array(
      '#text' => '!taxonomy_get_tree()\'s $depth and $max_depth parameters have changed positions.',
      '#args' => array(
        '!taxonomy_get_tree' => _drupalapi('taxonomy_get_tree', 7),
      ),
      '#link' => _drupalnode(224333, 'taxonomy_get_tree'),
    ),
  );
  $taxonomy_tables = '\{(term_data|term_hierarchy|term_node|term_relation|term_synonym|vocabulary|vocabulary_node_types)\}';
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => '^(select\s+.*\s+from\s+' . $taxonomy_tables . '|insert\s+into\s+' . $taxonomy_tables . '|update\s+' . $taxonomy_tables . '\s+set|delete\s+from\s+' . $taxonomy_tables . ')',
    '#warning' => array(
      '#text' => "Taxonomy DB table names have changed to begin with 'taxonomy_'",
      '#link' => _drupalnode(224333, 'taxonomy_tables'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_get_term\s*\(',
    '#warning' => array(
      '#text' => '!taxonomy_get_term() function has been renamed to !taxonomy_term_load()',
      '#args' => array(
        '!taxonomy_get_term' => _drupalapi('taxonomy_get_term', 6),
        '!taxonomy_term_load' => _drupalapi('taxonomy_term_load', 7),
      ),
      '#link' => _drupalnode(224333, 'taxonomy_crud'),
    ),
  );
  $taxonomy_save_term_warning = array(
    '#text' => '!taxonomy_save_term() function has been renamed to !taxonomy_term_save() and takes a term object as a parameter instead of any array.',
    '#args' => array(
      '!taxonomy_save_term' => _drupalapi('taxonomy_save_term', 6),
      '!taxonomy_term_save' => _drupalapi('taxonomy_term_save', 7),
    ),
    '#link' => _drupalnode(224333, 'taxonomy_crud'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_save_term\s*\(',
    '#warning' => $taxonomy_save_term_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_term_save\s*\(\s*array\s*\(',
    '#warning' => $taxonomy_save_term_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_del_term\s*\(',
    '#warning' => '_coder_review_7x_taxonomy_del_term_warning',
    '#warning' => array(
      '#text' => '!taxonomy_del_term() function has been renamed to !taxonomy_term_delete()',
      '#args' => array(
        '!taxonomy_del_term' => _drupalapi('taxonomy_del_term', 6),
        '!taxonomy_term_delete' => _drupalapi('taxonomy_term_delete', 7),
      ),
      '#link' => _drupalnode(224333, 'taxonomy_crud'),
    ),
  );
  $taxonomy_save_vocabulary_warning = array(
    '#text' => '!taxonomy_save_vocabulary() function has been renamed to !taxonomy_vocabulary_save() and takes a vocabulary object as a parameter instead of any array.',
    '#args' => array(
      '!taxonomy_save_vocabulary' => _drupalapi('taxonomy_save_vocabulary', 6),
      '!taxonomy_vocabulary_save' => _drupalapi('taxonomy_vocabulary_save', 7),
    ),
    '#link' => _drupalnode(224333, 'taxonomy_crud'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_save_vocabulary\s*\(',
    '#warning' => $taxonomy_save_vocabulary_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_vocabulary_save\s*\(\s*array\s*\(',
    '#warning' => $taxonomy_save_vocabulary_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_del_vocabulary\s*\(',
    '#warning' => '_coder_review_7x_taxonomy_del_vocabulary_warning',
    '#warning' => array(
      '#text' => '!taxonomy_del_vocabulary() function has been renamed to !taxonomy_vocabulary_delete()',
      '#args' => array(
        '!taxonomy_del_vocabulary' => _drupalapi('taxonomy_del_vocabulary', 6),
        '!taxonomy_vocabulary_delete' => _drupalapi('taxonomy_vocabulary_delete', 7),
      ),
      '#link' => _drupalnode(224333, 'taxonomy_crud'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => 'taxonomy\/term\/\d+(\+\d+|\,\d+|\/\d+)',
    '#warning' => '_coder_review_7x_taxonomy_paths_warning',
    '#warning' => array(
      '#text' => 'Support for taxonomy term paths with multiple tids and depth specification has been removed.',
      '#link' => _drupalnode(224333, 'taxonomy_paths'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]taxonomy_get_related\s*\(',
    '#warning' => array(
      '#text' => 'The related terms functionality has been removed from the taxonomy module.',
      '#link' => _drupalnode(224333, 'related_terms'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'Drupal\.behaviors\..+?\s*=\s*function\s*\(',
    '#filename' => array('js'),
    '#warning' => _coder_review_7x_drupal_behaviors_warning(),
  );
  $rules[] = array(
    '#type' => 'callback',
    '#value' => '_coder_review_7x_drupal_behaviors_callback',
    '#filename' => array('js'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]drupal_add_js\s*\(\s*' . $argex . '\s*,\s*[\'"](module|theme|core)[\'"]\s*[,\)]',
    '#warning' => array(
      '#text' => "Replace 'core', 'module' and 'theme' with 'file' in !drupal_add_js()",
      '#args' => array(
        '!drupal_add_js' => _drupalapi('drupal_add_js', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_add_js_weight'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_add_js\s*\(\s*(' . $argex . '\s*,\s*){2,}(' . $argex . ')\s*\)',
    '#warning' => array(
      '#text' => 'Parameters to !drupal_add_js() have changed.',
      '#args' => array(
        '!drupal_add_js' => _drupalapi('drupal_add_js', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_add_js_options'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\'"]scripts[\'"]',
    '#function' => '_preprocess_page$',
    '#warning' => array(
      '#text' => 'There is a new !hook_js_alter() to alter JavaScript.',
      '#args' => array(
        '!hook_js_alter' => _drupalapi('hook_js_alter', 7),
      ),
      '#link' => _drupalnode(224333, 'hook_js_alter'),
    ),
  );
  $rules[] = array(
    '#type' => 'grep_invert',
    '#value' => '(function ($) {',
    '#filename' => array('js'),
    '#warning' => '_coder_review_7x_javascript_compatibility_warning',
    '#warning' => array(
      '#text' => 'JavaScript should be compatible with other libraries than jQuery.',
      '#link' => _drupalnode(224333, 'javascript_compatibility'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]drupal_add_html_head\s*\(\s*[\'"].*?<script\s.*?src\s*=\s*[\'"][a-zA-Z:\/\._\-0-9]+?\.js',
    '#warning' => '_coder_review_7x_drupal_add_js_external_warning',
    '#warning' => array(
      '#text' => 'External JavaScript can now be referenced through !drupal_add_js().',
      '#args' => array(
        '!drupal_add_js' => _drupalapi('drupal_add_js', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_add_js_external'),
    ),
  );
  $jquery_13_warning = array(
    '#text' => 'jQuery has been upgraded to version 1.3.',
    '#link' => _drupalnode(224333, 'jquery_13'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '\[.*?@[a-zA-Z]+\s*(\^=|=|!=|\$=|\*=)\s*.+?\]',
    '#filename' => array('js'),
    '#warning' => $jquery_13_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '(\$|jQuery)\.(boxModel|browser.version|browser)',
    '#filename' => array('js'),
    '#warning' => $jquery_13_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'Drupal.jsEnabled',
    '#filename' => array('js'),
    '#warning' => '_coder_review_7x_no_jsenabled_warning',
    '#warning' => array(
      '#text' => 'JavaScript variable Drupal.jsEnabled has been removed.',
      '#link' => _drupalnode(224333, 'no-jsenabled'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_add_css\s*\(\s*(' . $argex . '\s*,\s*){2,}(' . $argex . ')\s*\)',
    '#warning' => array(
      '#text' => 'Parameters to !drupal_add_css() have changed.',
      '#args' => array(
        '!drupal_add_css' => _drupalapi('drupal_add_css', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_add_js_options'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_rebuild_theme_registry\s*\(',
    '#warning' => array(
      '#text' => '!drupal_rebuild_theme_registry() function has been renamed to !drupal_theme_rebuild()',
      '#args' => array(
        '!drupal_rebuild_theme_registry' => _drupalapi('drupal_rebuild_theme_registry', 6),
        '!drupal_theme_rebuild' => _drupalapi('drupal_theme_rebuild', 7),
      ),
      '#link' => _drupalnode(224333, 'rebuild_functions'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]theme\s*\(\s*[\'"]page[\'"]',
    '#warning' => '_coder_review_7x_theme_page_warning',
    '#warning' => array(
      '#text' => 'Instead of "theme(\'page\')" use !drupal_set_page_content()',
      '#args' => array(
        '!drupal_set_page_content' => _drupalapi('drupal_set_page_content', 7),
      ),
      '#link' => _drupalnode(224333, 'theme_page'),
    ),
  );
  $hook_footer_warning = array(
    '#text' => '!hook_footer() and !theme_closure() were removed.',
    '#args' => array(
      '!hook_footer' => _drupalapi('hook_footer', 6),
      '!theme_closure' => _drupalapi('theme_closure', 6),
    ),
    '#link' => _drupalnode(224333, 'hook_footer'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]theme\s*\(\s*[\'"]closure[\'"]',
    '#warning' => $hook_footer_warning
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(closure|footer)\s*\(',
    '#warning' => $hook_footer_warning
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '\$closure[^a-zA-Z_]',
    '#filename' => array('tpl.php'),
    '#warning' => array(
      '#text' => '$closure has been changed to $page_bottom.',
      '#link' => _drupalnode(224333, 'hook_footer'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_elements$',
    '#value' => '[\'"]#type[\'"]',
    '#warning' => array(
      '#text' => '@todo: The warning hook for this was missing, what should this message say?',
      '#link' => _drupalnode(224333, 'element_theme_properties'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_form_alter$',
    '#source' => 'allphp',
    '#value' => '\$form\[[\'"]type[\'"]\]\[[\'"]\#value[\'"]\]\s*\.\s*[\'"]_node_form[\'"]',
    '#warning' => '_coder_review_7x_node_form_warning',
    '#warning' => array(
      '#text' => 'Easier check for node form during !hook_form_alter().',
      '#args' => array(
        '!hook_form_alter' => _drupalapi('hook_form_alter', 7),
      ),
      '#link' => _drupalnode(224333, 'node_form'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#function' => '_form_alter$',
    '#value' => 'function\s+[a-z0-9_]+_(form_alter)\s*\(\s*&\$form,\s*\$form_state,\s*\$form_id\s*\)',
    '#warning' => array(
      '#text' => 'Parameters to !hook_form_alter() have changed.',
      '#args' => array(
        '!hook_form_alter' => _drupalapi('hook_form_alter', 7),
      ),
      // @todo: is there a good link for this?
//    '#link' => _drupalnode(224333, 'node_form'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\'"]#process[\'"](\])?\s*=(>)?\s*[\'"](expand_password_confirm|expand_date|expand_radios|form_expand_ahah|expand_checkboxes|process_weight)[\'"]',
    '#warning' => array(
      '#text' => '!expand_password_confirm(), !expand_date(), !expand_radios(), !form_expand_ahah(), !expand_checkboxes(), !process_weight() have been renamed.',
      '#args' => array(
        '!expand_password_confirm' => _drupalapi('expand_password_confirm', 6),
        '!expand_date' => _drupalapi('expand_date', 6),
        '!expand_radios' => _drupalapi('expand_radios', 6),
        '!form_expand_ahah' => _drupalapi('form_expand_ahah', 6),
        '!expand_checkboxes' => _drupalapi('expand_checkboxes', 6),
        '!process_weight' => _drupalapi('process_weight', 6),
      ),
      '#link' => _drupalnode(224333, 'process_functions'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_execute\s*\(',
    '#warning' => '_coder_review_7x_drupal_execute_renamed_warning',
    '#warning' => array(
      '#text' => '!drupal_execute() has been renamed to !drupal_form_submit()',
      '#args' => array(
        '!drupal_execute' => _drupalapi('drupal_execute', 6),
        '!drupal_form_submit' => _drupalapi('drupal_form_submit', 7),
      ),
      '#link' => _drupalnode(224333, 'drupal_execute_drupal_form_submit'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\'"]#ahah[\'"]',
    '#warning' => array(
      '#text' => '#ahah has changed to #ajax and the call details have changed.',
      '#link' => _drupalnode(224333, 'ahah-now-ajax'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]file_scan_directory\s*\(\s*((' . $argex . '\s*,\s*){4,}(' . $argex . ')\s*\)|(' . $argex . '\s*,\s*){2,}\$nomask)',
    '#warning' => '_coder_review_7x_file_scan_directory_array_itize_warning',
    '#warning' => array(
      '#text' => 'Parameters to !file_scan_directory() have changed.',
      '#args' => array(
        '!file_scan_directory' => _drupalapi('file_scan_directory', 7),
      ),
      '#link' => _drupalnode(224333, 'file_scan_directory_array_itize'),
    ),
  );
  $file_scan_directory_nomask_warning = array(
    '#text' => '!file_scan_directory() now uses a preg regular expression for the nomask parameter.',
    '#args' => array(
      '!file_scan_directory' => _drupalapi('file_scan_directory', 7),
    ),
    '#link' => _drupalnode(224333, 'file_scan_directory_nomask'),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]file_scan_directory\s*\(\s*(\s*.*?,\s*){2,}array\(([\'"].*?[\'"](,)*){1,}\)\s*[,\)]',
    '#warning' => $file_scan_directory_nomask_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]file_scan_directory\s*\(\s*(\s*.*?,\s*){2,}array\(.+?[\'"]nomask[\'"]\s*=>\s*array\(([\'"].*?[\'"](,)*){1,}\)\s*[,\)]',
    '#warning' => $file_scan_directory_nomask_warning,
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]file_set_status\s*\(',
    '#warning' => '_coder_review_7x_file_set_status_warning',
    '#warning' => array(
      '#text' => '!file_set_status() has been removed and !file_save() should be used in its place.',
      '#args' => array(
        '!file_set_status' => _drupalapi('file_set_status', 6),
        '!file_save' => _drupalapi('file_save', 7),
      ),
      '#link' => _drupalnode(224333, 'file_set_status'),
    ),
  );
  $rules[] = array(
    '#type' => 'grep',
    '#value' => 'FILE_STATUS_TEMPORARY',
    '#case-sensitive' => TRUE,
    '#warning' => array(
      '#text' => 'Removed FILE_STATUS_TEMPORARY constant.',
      '#link' => _drupalnode(224333, 'remove_FILE_STATUS_TEMPORARY'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]file_scan_directory\s*\(\s*([^,]+?\s*,\s*){1}[\'"].*?[\'"]\s*[,\)]',
    '#never' => '[\s\(]file_scan_directory\s*\(\s*[^,]+?,\s*[\'"]\/.*?\/[\'"]\s*[,\)]',
    '#warning' => array(
      '#text' => '!file_scan_directory() now uses preg regular expressions.',
      '#args' => array(
        '!file_scan_directory' => _drupalapi('file_scan_directory', 7),
      ),
      '#link' => _drupalnode(224333, 'preg_match'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]drupal_system_listing\s*\(\s*[\'"][^\/].*?[^\/][\'"]\s*,',
    '#never' => '[\s\(]drupal_system_listing\s*\(\s*[\'"]\/.*?\/[\'"]\s*,',
    '#warning' => array(
      '#text' => '!drupal_system_listing() now uses preg regular expressions.',
      '#args' => array(
        '!drupal_system_listing' => _drupalapi('drupal_system_listing', 7),
      ),
      '#link' => _drupalnode(224333, 'preg_match'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]user_delete\s*\(',
    '#warning' => array(
      '#text' => '!user_delete() replaced by !user_cancel()',
      '#args' => array(
        '!user_delete' => _drupalapi('user_delete', 6),
        '!user_cancel' => _drupalapi('user_cancel', 7),
      ),
      '#link' => _drupalnode(224333, 'user_cancel'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(user)\s*\(\s*(\$op|.*,\s*&\$account)',
    '#warning' => array(
      '#text' => '!hook_user() has been removed in favour of hook_user_$op functions, for example !hook_user_presave().',
      '#args' => array(
        '!hook_user' => _drupalapi('hook_user', 6),
        '!hook_user_presave' => _drupalapi('hook_user_presave', 7),
      ),
      '#link' => _drupalnode(224333, 'remove_op'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\'"]logout[\'"]',
    '#warning' => array(
      '#text' => 'Log out path changed from \'logout\' to \'user/logout\'',
      '#link' => _drupalnode(224333, 'logout_path'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]user_load\s*\(\s*(array\s*\(|\(\s*array\s*\))',
    '#warning' => array(
      '#text' => '!user_load() now only takes a user ID as its argument.',
      '#args' => array(
        '!user_load' => _drupalapi('user_load', 7),
      ),
      '#link' => _drupalnode(224333, 'user_load_multiple'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]user_authenticate\s*\(\s*' . $argex . '\s*\)',
    '#warning' => array(
      '#text' => 'Parameters to !user_authenticate() have changed.',
      '#args' => array(
        '!user_authenticate' => _drupalapi('user_authenticate', 7),
      ),
      '#link' => _drupalnode(224333, 'user_authenticate'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+\w+_profile_alter\s*\(',
    '#warning' => array(
      '#text' => '!hook_profile_alter() has been removed in favour of !hook_user_view().',
      '#args' => array(
        '!hook_profile_alter' => _drupalapi('hook_profile_alter', 6),
        '!hook_user_view' => _drupalapi('hook_user_view', 7),
      ),
      '#link' => _drupalnode(224333, 'hook-user-changes'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'quote',
    '#value' => '^(select\s+.*\s+from\s+{node_revisions}|insert\s+into\s+{node_revisions}|update\s+{node_revisions}\s+set|delete\s+from\s+{node_revisions})',
    '#warning' => array(
      '#text' => "The 'node_revisions' table has been renamed to 'node_revision'.",
//    '#link' => _drupalnode(224333, 'taxonomy_tables'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => 'function\s+[a-z0-9_]+_(link)\s*\(\s*([\'"](node|taxonomy terms)[\'"]|' . $argex . '\s*,\s*\$node\s*,)',
    '#warning' => array(
      '#text' => 'Node and taxonomy links are no longer emitted by !hook_link() and !hook_link_alter().',
      '#args' => array(
        '!hook_link' => _drupalapi('hook_link', 7),
        '!hook_link_alter' => _drupalapi('hook_link_alter', 7),
      ),
      '#link' => _drupalnode(224333, 'node_links'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#value' => '[\s\(]node_load\s*\(\s*(\$param\s*[,\)]|array\s*\()',
    '#warning' => array(
      '#text' => '!node_load() now only takes nid and vid as parameters.',
      '#args' => array(
        '!node_load' => _drupalapi('node_load', 7),
      ),
      '#link' => _drupalnode(224333, 'node_load_multiple'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_node_info$',
    '#value' => '[\'"](module)[\'"]\s*=>\s*[\'"].*?[\'"]',
    '#warning' => array(
      '#text' => 'Change "module" to "base" in !hook_node_info()',
      '#args' => array(
        '!hook_node_info' => _drupalapi('hook_node_info', 7),
      ),
      '#link' => _drupalnode(224333, 'node_type_base'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_node_info$',
    '#value' => '[\'"](module|base)[\'"]\s*=>\s*[\'"]node[\'"]',
    '#warning' => array(
      '#text' => 'For content types managed by the node module, change "node" to "node_content" in !hook_node_info()',
      '#args' => array(
        '!hook_node_info' => _drupalapi('hook_node_info', 7),
      ),
      '#link' => _drupalnode(224333, 'node_type_base'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(nodeapi)\s*\(',
    '#warning' => array(
      '#text' => '!hook_nodeapi() has been split into a number of smaller hooks.',
      '#args' => array(
        '!hook_nodeapi' => _drupalapi('hook_nodeapi', 6),
      ),
      '#link' => _drupalnode(224333, 'remove_op'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(comment)\s*\(.*,\s*\$op\)',
    '#warning' => array(
      '#text' => '!hook_comment() has been split into a number of smaller hooks, for example !hook_comment_view().',
      '#args' => array(
        '!hook_comment' => _drupalapi('hook_comment', 6),
        '!hook_comment_view' => _drupalapi('hook_comment_view', 7),
      ),
      '#link' => _drupalnode(224333, 'remove_op'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_invoke_nodeapi\s*\(',
    '#warning' => array(
      '#text' => '!node_invoke_nodeapi() has been removed and !module_invoke_all(\'node_\' . $hook, $node); should be used instead.',
      '#args' => array(
        '!node_invoke_nodeapi' => _drupalapi('node_invoke_nodeapi', 6),
        '!module_invoke_all' => _drupalapi('module_invoke_all', 6),
      ),
      '#link' => _drupalnode(224333, 'node_invoke_nodeapi'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#source' => 'allphp',
    '#function' => '_nodeapi$',
    '#value' => '[\'"]rss item[\'"]',
    '#warning' => array(
      '#text' => 'Removed $op "rss item" from !hook_nodeapi() in favor of NODE_BUILD_RSS.',
      '#args' => array(
        '!hook_nodeapi' => _drupalapi('hook_nodeapi', 7),
      ),
      '#link' => _drupalnode(224333, 'node_build_rss'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]node_get_types\s*\(',
    '#warning' => array(
      '#text' => '!node_get_types() function has been replaced by node_type_get_$op() functions.',
      '#args' => array(
        '!node_get_types' => _drupalapi('node_get_types', 6),
      ),
      '#link' => _drupalnode(224333, 'node_type_get_functions'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]\$node->build_mode',
    '#warning' => array(
      '#text' => '$node->build_mode property removed.',
      '#link' => _drupalnode(224333, 'build_mode'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]NODE_BUILD_PREVIEW',
    '#warning' => array(
      '#text' => 'NODE_BUILD_PREVIEW has been replaced by the $node->in_preview boolean flag.',
      '#link' => _drupalnode(224333, 'build_mode'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => 'function\s+[a-z0-9_]+_(nodeapi)_[a-z]+\s*\(',
    '#warning' => array(
      '#text' => 'hook_nodeapi_xxx() has been renamed to hook_node_xxx().',
      '#link' => _drupalnode(224333, 'hook_node_xxx'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    // @todo: this has two warning definitions, which one is right?
    '#value' => '[\s\(]t\s*\(\s*(.*?\s*,\s*){2,}([\'"].*?[\'"])\s*\)',
    '#value' => '[\s\(]t\s*\(\s*(' . $argex . '\s*,\s*){2,}([\'"].*?[\'"])\s*\)',
    '#warning' => array(
      '#text' => 'Context has been added to !t() as the third parameter, locale has to be an element in the array. Example: array("context" => "frontpage", "locale" => "de").',
      '#args' => array(
        '!t' => _drupalapi('t', 7),
      ),
      '#link' => _drupalnode(224333, 'locale_context'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]format_plural\s*\(\s*(' . $argex . '\s*,\s*){4,}([\'"].*?[\'"])\s*\)',
    '#warning' => array(
      '#text' => 'Context has been added to !format_plural() as the fifth parameter, locale has to be an element in the array. Example: array("context" => "frontpage", "locale" => "de").',
      '#args' => array(
        '!format_plural' => _drupalapi('format_plural', 7),
      ),
      '#link' => _drupalnode(224333, 'locale_context'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]book_toc\s*\(\s*' . $argex . '\s*,\s*(array\s*\(|(\$?)[a-zA-Z_]+\s*,\s*\d+)',
    '#warning' => '_coder_review_7x_book_toc_warning',
    '#warning' => array(
      '#text' => '!book_toc()\'s $depth_limit and $exclude parameters have changed positions.',
      '#args' => array(
        '!book_toc' => _drupalapi('book_toc', 7),
      ),
      '#link' => _drupalnode(224333, 'book_toc_parameters'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]referer_uri\s*\(',
    '#warning' => '_coder_review_7x_referer_uri_warning',
    '#warning' => array(
      '#text' => '!referer_uri() has been removed and replaced with the PHP global $_SERVER[\'HTTP_REFERER\']',
      '#args' => array(
        '!referer_uri' => _drupalapi('referer_uri', 6),
      ),
      '#link' => _drupalnode(224333, 'referer_uri'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]drupal_clone\s*\(',
    '#warning' => '_coder_review_7x_drupal_clone_warning',
    '#warning' => array(
      '#text' => '!drupal_clone() has been removed and the PHP 5 !clone should be used instead.',
      '#args' => array(
        '!drupal_clone' => _drupalapi('drupal_clone', 6),
        '!clone' => _phpapi('clone'),
      ),
      '#link' => _drupalnode(224333, 'drupal_clone'),
    ),
  );
  $rules[] = array(
    '#type' => 'regex',
    '#value' => '[\s\(]actions_synchronize\s*\((\$actions|[^,]+,)',
    '#warning' => '_coder_review_7x_actions_synchronize_warning',
    '#warning' => array(
      '#text' => 'Parameters for !actions_synchronize() have changed',
      '#args' => array(
        '!actions_synchronize' => _drupalapi('actions_synchronize', 7),
      ),
      '#link' => _drupalnode(224333, 'actions_synchronize'),
    ),
  );

  $review = array(
    '#title' => 'Converting 6.x modules to 7.x',
    '#link' => _drupalnode(394070),
    '#rules' => $rules,
    '#severity' => 'critical',
    '#version' => 2,
    '#image' => 'images/7.png',
  );
  return array('upgrade7x' => $review);
}

/**
 * Define the rule callbacks for 7.x, see do_coder_callback().
 */
function _coder_review_7x_info_file_callback(&$coder_args, $review, $rule, $lines, &$results) {
  // Only perform this check for module's (not includes).
  $filename = $coder_args['#filename'];
  $pathinfo = pathinfo($filename);
  if ($pathinfo['extension'] == 'module') {
    // @NOTE: no simpletest for this.
    // Read the .info file.
    $files_line = FALSE;
    $core = FALSE;
    $filename = $pathinfo['dirname'] . '/' . $pathinfo['filename'] . '.info';
    if (file_exists($filename)) {
      $lines = file($filename);
      if ($lines) {
        foreach ($lines as $lineno => $line) {
          if (preg_match('/^files\s*\[\s*\]\s*=/', $line)) {
            $files_line = TRUE;
          }
          if (preg_match('/^core\s*=\s*7/', $line)) {
            $core = TRUE;
          }
        }
        if (empty($files_line)) {
          $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
          $tmprule = $rule;
          $tmprule['#warning'] = array(
            '#text' => 'Module .info files must now specify all loadable code files explicitly.',
            '#link' => _drupalnode(224333, 'registry'),
          );
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
        if (!$core) {
          $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
          $tmprule = $rule;
          $tmprule['#warning'] = 'Info file should specify core=7.x';
          _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
        }
      }
    }
  }
}

/**
 * Define the rule callbacks for 7.x, see do_coder_callback().
 */
function _coder_review_7x_module_implements_callback(&$coder_args, $review, $rule, $lines, &$results) {
  $depth = 0;
  foreach ($lines as $lineno => $line) {
    if ($depth == 0) {
      if (preg_match('/^\s+foreach\s*\(\s*module_list\s*\(\s*\)/', $line[0])) {
        $depth = 1;
      }
    }
    else {
      if (preg_match('/module_invoke\s*\(/', $line[0])) {
        $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
        $tmprule = $rule;
        $tmprule['#warning'] = array(
          '#text' => 'Use module_implements not module_list when calling hook implementations.',
          '#link' => _drupalnode(224333, 'module_implements_not_module_list'),
        );
        _coder_review_error($results, $tmprule, $severity_name, $lineno, $line[0], $coder_args['#ignores']);
      }
      if (strpos($line[0], '{') !== FALSE) {
        $depth --;
      }
      if (strpos($line[0], '}') !== FALSE) {
        $depth ++;
      }
    }
  }
}

/**
 * @todo: add a function header comment.
 */
function _coder_review_7x_cache_implementation_callback(&$coder_args, $review, $rule, $lines, &$results) {
  // @NOTE: no simpletest for this.
  $filename = $coder_args['#filename'];
  if ($filename == 'includes/cache-install.inc' || $filename == 'includes/cache.inc') {
    return;
  }
  if (file_exists($filename)) {
    // Only do it for PHP files.
    $pathinfo = pathinfo($filename);
    if (in_array($pathinfo['extension'], array('module', 'php', 'inc'))) {
      $lines = file($filename);
      if ($lines) {
        foreach ($lines as $lineno => $line) {
          if (preg_match('/function\s+(cache_set|cache_get|cache_clear_all)\s*\(/', $line)) {
            $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
            $tmprule = $rule;
            $tmprule['#warning'] = array(
              '#text' => 'Alternative cache implementations have changed.',
              '#link' => _drupalnode(224333, 'cache_implementation'),
            );
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
          }
        }
      }
    }
  }
}

/**
 * @todo: add a function header comment.
 */
function _coder_review_7x_drupal_behaviors_callback(&$coder_args, $review, $rule, $lines, &$results) {
  // @NOTE: no simpletest for this.
  $filename = $coder_args['#filename'];
  if (file_exists($filename)) {
    // Only do it for js files.
    $pathinfo = pathinfo($filename);
    if ($pathinfo['extension'] == 'js') {
      $lines = file($filename);
      if ($lines) {
        $detach = FALSE;
        foreach ($lines as $lineno => $line) {
          // New function, reset detach boolean.
          if (preg_match('/(^|[\s\(=])function\s*([a-zA-Z_]+?|\()/', $line)) {
            $detach = FALSE;
          }
          if (preg_match('/Drupal\.detachBehaviors\s*\(/', $line)) {
            $detach = TRUE;
          }
          if (!$detach && preg_match('/(jQuery\.|\$\.|\$\([a-zA-Z_#\'"\-]+?\)\.)(ajax|get|getJSON|post|load)/', $line)) {
            $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
            $tmprule = $rule;
            $tmprule['#warning'] = _coder_review_7x_drupal_behaviors_warning();
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
          }
        }
      }
    }
  }
}

/**
 * @todo: add a function header comment.
 */
function _coder_review_7x_comment_doxygen_file_callback(&$coder_args, $review, $rule, $lines, &$results) {
  // @NOTE: no simpletest for this.
  // Only perform this check on install files.
  $pathinfo = pathinfo($coder_args['#filename']);
  if ($pathinfo['extension'] == 'install') {
    $file_found = 0;
    $invalid_file_message = 0;
    foreach ($lines as $lineno => $line) {
      if (preg_match('/^ * @file/', $line[0])) {
        $file_found = 1;
      }
      // Immediately reset $file_found on the next line, and check if the
      // comment matches the required format.
      elseif ($file_found == 1) {
        if (!preg_match('/^ * Install, update and uninstall functions for the \w+ module./', $line[0])) {
          $invalid_file_message = 1;
        }
        $file_found = 0;
      }
    }
    if ($invalid_file_message) {
      $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
      $tmprule = $rule;
      $tmprule['#warning'] = array(
        '#text' => 'For .install files, the @file description should be of the format "Install, update and uninstall functions for the XXX module.".',
        '#link' => _drupalnode(224333, 'afile'),
      );
      _coder_review_error($results, $tmprule, $severity_name, $theme_lineno, $theme_line, $coder_args['#ignores']);
    }
  }
}

/**
 * Make sure user defined block module as a dependency if using block functions.
 *
 * @see http://drupal.org/node/224333#block_optional
 */
function _coder_review_7x_optional_block_callback(&$coder_args, $review, $rule, $lines, &$results) {
  $functions_to_check = array('block_list', 'block_custom_block_get', 'block_page_build');
  $filename = $coder_args['#filename'];

  // Skip for unit tests as there is no physical file.
  if ($filename == 'snippet.php') {
    return;
  }

  // Find out the info filename and load it.
  $path_info = pathinfo($filename);
  list($modulename) = explode('.', $path_info['basename'], 2);
  $path = realpath($path_info['dirname'] . '/' . $modulename . '.info');
  if (!$path || !is_file($path)) {
    return;
  }

  // Check if the dependency has been declared.
  if (function_exists('drupal_parse_info_file')) {
    $ini = drupal_parse_info_file($path);
    $dependency_declared = (isset($ini['dependencies']) && is_array($ini['dependencies'])) ? in_array('block', $ini['dependencies']) : FALSE;
  }

  if (file_exists($filename) && $modulename != 'block' && !$dependency_declared) {
    $lines = file($filename);
    if ($lines) {
      foreach ($lines as $lineno => $line) {
        foreach ($functions_to_check as $function) {
          if (preg_match("/[\s\(]$function\(/", $line)) {
            $severity_name = _coder_review_severity_name($coder_args, $review, $rule);
            $tmprule = $rule;
            $tmprule['#warning'] = array(
              '#text' => "Block module is now optional, make sure you declare it as a dependency in your module's .info file.",
              '#link' => _drupalnode(224333, 'block_optional'),
            );
            _coder_review_error($results, $tmprule, $severity_name, $lineno, $line, $coder_args['#ignores']);
          }
        }
      }
    }
  }
}

/**
 * Define the warning callbacks.
 */

/**
 * Return the warning text for http://drupal.org/node/224333#drupal_behaviors.
 *
 * This is in it's own function because the text is needed in both the rules definition,
 * and in a callback function, so rather than define the warning twice, just define it
 * once here.
 */
function _coder_review_7x_drupal_behaviors_warning() {
  return array(
    '#text' => 'Changed Drupal.behaviors to objects having the methods "attach" and "detach".',
    '#link' => _drupalnode(224333, 'drupal_behaviors'),
  );
}
