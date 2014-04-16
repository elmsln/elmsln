<?php

/**
 * @file
 * Hooks provided by the File Entity module.
 */

/**
 * Declare that your module provides default file types.
 *
 * Your module may already implement this hook for other CTools plugin types.
 * If so, copy the body of this function into the existing hook.
 */
function hook_ctools_plugin_api($owner, $api) {
  if ($owner == 'file_entity' && $api == 'file_type') {
    return array('version' => 1);
  }
}

/**
 * Define default file types.
 *
 * File types are implemented as CTools exportables, so modules can alter the
 * defaults via hook_file_default_types_alter(), and the administrator can
 * save overridden and custom types to the {file_type} database table.
 *
 * @return array
 *   An array whose keys are file type names and whose values are objects
 *   representing the file type, with the following key/value pairs:
 *   - api_version: The version of this data.
 *   - type: The file type name.
 *   - label: The human-readable name of the file type.
 *   - description: The description of this file type.
 *   - mimetypes: An array of mimetypes that this file type will map to.
 */
function hook_file_default_types() {
  return array(
    'image' => (object) array(
      'api_version' => 1,
      'type' => 'image',
      'label' => t('Image'),
      'description' => t("An <em>Image</em> is a two-dimensional picture that has a similar appearance to some subject, usually a physical object or a person."),
      'mimetypes' => array(
        'image/*',
      ),
    ),
  );
}

/**
 * Alter default file types.
 *
 * @see hook_file_default_types()
 */
function hook_file_default_types_alter(&$types) {
  $types['image']->mimetypes[] = 'image/svg+xml';
}

/**
 * Define file formatters.
 *
 * @return array
 *   An array whose keys are file formatter names and whose values are arrays
 *   describing the formatter.
 *
 * @todo Document key/value pairs that comprise a formatter.
 *
 * @see hook_file_formatter_info_alter()
 */
function hook_file_formatter_info() {
  // @todo Add example.
}

/**
 * Perform alterations on file formatters.
 *
 * @param array $info
 *   Array of information on file formatters exposed by
 *   hook_file_formatter_info() implementations.
 */
function hook_file_formatter_info_alter(&$info) {
  // @todo Add example.
}

/**
 * @todo Add documentation.
 *
 * Note: This is not really a hook. The function name is manually specified via
 * 'view callback' in hook_file_formatter_info(), with this recommended callback
 * name pattern.
 */
function hook_file_formatter_FORMATTER_view($file, $display, $langcode) {
}

/**
 * @todo Add documentation.
 *
 * Note: This is not really a hook. The function name is manually specified via
 * 'settings callback' in hook_file_formatter_info(), with this recommended
 * callback name pattern.
 */
function hook_file_formatter_FORMATTER_settings($form, &$form_state, $settings) {
}

/**
 * @todo Add documentation.
 */
function hook_file_displays_alter($displays, $file, $view_mode) {
}

/**
 * @todo Add documentation.
 */
function hook_file_view($file, $view_mode, $langcode) {
}

/**
 * @todo Add documentation.
 */
function hook_file_view_alter($build, $type) {
}

/**
 * Add mass file operations.
 *
 * This hook enables modules to inject custom operations into the mass
 * operations dropdown found at admin/content/file, by associating a callback
 * function with the operation, which is called when the form is submitted. The
 * callback function receives one initial argument, which is an array of the
 * checked files.
 *
 * @return array
 *   An array of operations. Each operation is an associative array that may
 *   contain the following key-value pairs:
 *   - 'label': Required. The label for the operation, displayed in the dropdown
 *     menu.
 *   - 'callback': Required. The function to call for the operation.
 *   - 'callback arguments': Optional. An array of additional arguments to pass
 *     to the callback function.
 */
function hook_file_operations() {
  $operations = array(
    'delete' => array(
      'label' => t('Delete selected files'),
      'callback' => NULL,
    ),
  );
  return $operations;
}

/**
 * Control access to a file.
 *
 * Modules may implement this hook if they want to have a say in whether or not
 * a given user has access to perform a given operation on a file.
 *
 * The administrative account (user ID #1) always passes any access check,
 * so this hook is not called in that case. Users with the "bypass file access"
 * permission may always view and edit files through the administrative
 * interface.
 *
 * Note that not all modules will want to influence access on all
 * file types. If your module does not want to actively grant or
 * block access, return FILE_ENTITY_ACCESS_IGNORE or simply return nothing.
 * Blindly returning FALSE will break other file access modules.
 *
 * @param string $op
 *   The operation to be performed. Possible values:
 *   - "create"
 *   - "delete"
 *   - "update"
 *   - "view"
 *   - "download"
 * @param object $file
 *   The file on which the operation is to be performed, or, if it does
 *   not yet exist, the type of file to be created.
 * @param object $account
 *   A user object representing the user for whom the operation is to be
 *   performed.
 *
 * @return string|NULL
 *   FILE_ENTITY_ACCESS_ALLOW if the operation is to be allowed;
 *   FILE_ENTITY_ACCESS_DENY if the operation is to be denied;
 *   FILE_ENTITY_ACCESS_IGNORE to not affect this operation at all.
 *
 * @ingroup file_entity_access
 */
function hook_file_entity_access($op, $file, $account) {
  $type = is_string($file) ? $file : $file->type;

  if ($op !== 'create' && (REQUEST_TIME - $file->timestamp) < 3600) {
    // If the file was uploaded in the last hour, deny access to it.
    return FILE_ENTITY_ACCESS_DENY;
  }

  // Returning nothing from this function would have the same effect.
  return FILE_ENTITY_ACCESS_IGNORE;
}

/**
 * Control access to listings of files.
 *
 * @param object $query
 *   A query object describing the composite parts of a SQL query related to
 *   listing files.
 *
 * @see hook_query_TAG_alter()
 * @ingroup file_entity_access
 */
function hook_query_file_entity_access_alter(QueryAlterableInterface $query) {
  // Only show files that have been uploaded more than an hour ago.
  $query->condition('timestamp', REQUEST_TIME - 3600, '<=');
}

/**
 * Act on a file being displayed as a search result.
 *
 * This hook is invoked from file_entity_search_execute(), after file_load()
 * and file_view() have been called.
 *
 * @param object $file
 *   The file being displayed in a search result.
 *
 * @return array
 *   Extra information to be displayed with search result. This information
 *   should be presented as an associative array. It will be concatenated
 *   with the file information (filename) in the default search result theming.
 *
 * @see template_preprocess_search_result()
 * @see search-result.tpl.php
 *
 * @ingroup file_entity_api_hooks
 */
function hook_file_entity_search_result($file) {
  $file_usage_count = db_query('SELECT count FROM {file_usage} WHERE fid = :fid', array('fid' => $file->fid))->fetchField();
  return array(
    'file_usage_count' => format_plural($file_usage_count, '1 use', '@count uses'),
  );
}

/**
 * Act on a file being indexed for searching.
 *
 * This hook is invoked during search indexing, after file_load(), and after
 * the result of file_view() is added as $file->rendered to the file object.
 *
 * @param object $file
 *   The file being indexed.
 *
 * @return string
 *   Additional file information to be indexed.
 *
 * @ingroup file_entity_api_hooks
 */
function hook_file_update_index($file) {
  $text = '';
  $uses = db_query('SELECT module, count FROM {file_usage} WHERE fid = :fid', array(':fid' => $file->fid));
  foreach ($uses as $use) {
    $text .= '<h2>' . check_plain($use->module) . '</h2>' . check_plain($use->count);
  }
  return $text;
}

/**
 * Provide additional methods of scoring for core search results for files.
 *
 * A file's search score is used to rank it among other files matched by the
 * search, with the highest-ranked files appearing first in the search listing.
 *
 * For example, a module allowing users to vote on files could expose an
 * option to allow search results' rankings to be influenced by the average
 * voting score of a file.
 *
 * All scoring mechanisms are provided as options to site administrators, and
 * may be tweaked based on individual sites or disabled altogether if they do
 * not make sense. Individual scoring mechanisms, if enabled, are assigned a
 * weight from 1 to 10. The weight represents the factor of magnification of
 * the ranking mechanism, with higher-weighted ranking mechanisms having more
 * influence. In order for the weight system to work, each scoring mechanism
 * must return a value between 0 and 1 for every file. That value is then
 * multiplied by the administrator-assigned weight for the ranking mechanism,
 * and then the weighted scores from all ranking mechanisms are added, which
 * brings about the same result as a weighted average.
 *
 * @return array
 *   An associative array of ranking data. The keys should be strings,
 *   corresponding to the internal name of the ranking mechanism, such as
 *   'recent', or 'usage'. The values should be arrays themselves, with the
 *   following keys available:
 *   - "title": the human readable name of the ranking mechanism. Required.
 *   - "join": part of a query string to join to any additional necessary
 *     table. This is not necessary if the table required is already joined to
 *     by the base query, such as for the {file_managed} table. Other tables
 *     should use the full table name as an alias to avoid naming collisions.
 *     Optional.
 *   - "score": part of a query string to calculate the score for the ranking
 *     mechanism based on values in the database. This does not need to be
 *     wrapped in parentheses, as it will be done automatically; it also does
 *     not need to take the weighted system into account, as it will be done
 *     automatically. It does, however, need to calculate a decimal between
 *     0 and 1; be careful not to cast the entire score to an integer by
 *     inadvertently introducing a variable argument. Required.
 *   - "arguments": if any arguments are required for the score, they can be
 *     specified in an array here.
 *
 * @ingroup file_entity_api_hooks
 */
function hook_file_ranking() {
  // If voting is disabled, we can avoid returning the array, no hard feelings.
  if (variable_get('vote_file_enabled', TRUE)) {
    return array(
      'vote_average' => array(
        'title' => t('Average vote'),
        // Note that we use i.sid, the search index's search item id, rather
        // than fm.fid.
        'join' => 'LEFT JOIN {vote_file_data} vote_file_data ON vote_file_data.fid = i.sid',
        // The highest possible score should be 1,
        // and the lowest possible score, always 0, should be 0.
        'score' => 'vote_file_data.average / CAST(%f AS DECIMAL)',
        // Pass in the highest possible voting score as a decimal argument.
        'arguments' => array(variable_get('vote_score_max', 5)),
      ),
    );
  }
}

/**
 * Alter file download headers.
 *
 * @param array $headers
 *   Array of download headers.
 * @param object $file
 *   File object.
 */
function hook_file_download_headers_alter(array &$headers, $file) {
  // Instead of being powered by PHP, tell the world this resource was powered
  // by your custom module!
  $headers['X-Powered-By'] = 'My Module';
}

/**
 * React to a file being downloaded.
 */
function hook_file_transfer($uri, array $headers) {
  // Redirect a download for an S3 file to the actual location.
  if (file_uri_scheme($uri) == 's3') {
    $url = file_create_url($uri);
    drupal_goto($url);
  }
}

/**
 * Decides which file type (bundle) should be assigned to a file entity.
 *
 * @param object $file
 *   File object.
 *
 * @return array
 *   Array of file type machine names that can be assigned to a given file type.
 *   If there are more proposed file types the one, that was returned the first,
 *   wil be chosen. This can be, however, changed in alter hook.
 *
 * @see hook_file_type_alter()
 */
function hook_file_type($file) {
  // Assign all files uploaded by anonymous users to a special file type.
  if (user_is_anonymous()) {
    return array('untrusted_files');
  }
}

/**
 * Alters list of file types that can be assigned to a file.
 *
 * @param array $types
 *   List of proposed types.
 * @param object $file
 *   File object.
 */
function hook_file_type_alter(&$types, $file) {
  // Choose a specific, non-first, file type.
  $types = array($types[4]);
}

/**
 * Provides metadata information.
 *
 * @todo Add documentation.
 *
 * @return array
 *   An array of metadata information.
 */
function hook_file_metadata_info() {

}

/**
 * Alters metadata information.
 *
 * @todo Add documentation.
 *
 * @return array
 *   an array of metadata information.
 */
function hook_file_metadata_info_alter() {

}
