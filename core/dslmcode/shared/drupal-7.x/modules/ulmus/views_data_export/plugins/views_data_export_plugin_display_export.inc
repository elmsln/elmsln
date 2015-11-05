<?php

/**
 * @file
 * Contains the bulk export display plugin.
 *
 * This allows views to be rendered in parts by batch API.
 */

/**
 * The plugin that batches its rendering.
 *
 * We are based on a feed display for compatibility.
 *
 * @ingroup views_display_plugins
 */
class views_data_export_plugin_display_export extends views_plugin_display_feed {

  /**
   * The batched execution state of the view.
   */
  public $batched_execution_state;

  /**
   * The alias of the weight field in the index table.
   */
  var $weight_field_alias = '';

  /**
   * A map of the index column names to the expected views aliases.
   */
  var $field_aliases = array();

  /**
   * Private variable that stores the filename to save the results to.
   */
  var $_output_file = '';

  var $views_data_export_cached_view_loaded;

  var $errors = array();

  /**
   * Return the type of styles we require.
   */
  function get_style_type() { return 'data_export'; }

  /**
   * Return the sections that can be defaultable.
   */
  function defaultable_sections($section = NULL) {
    if (in_array($section, array('items_per_page', 'offset', 'use_pager', 'pager_element',))) {
      return FALSE;
    }

    return parent::defaultable_sections($section);
  }

  /**
   * Define the option for this view.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['use_batch'] = array('default' => 'no_batch');
    $options['items_per_page'] = array('default' => '0');
    $options['return_path'] = array('default' => '');
    $options['style_plugin']['default'] = 'views_data_export_csv';

    // This is the default size of a segment when doing a batched export.
    $options['segment_size']['default'] = 100;

    if (isset($options['defaults']['default']['items_per_page'])) {
      $options['defaults']['default']['items_per_page'] = FALSE;
    }

    return $options;
  }

  /**
   * Provide the summary for page options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);

    $categories['page']['title'] = t('Data export settings');

    $options['use_batch'] = array(
      'category' => 'page',
      'title' => t('Batched export'),
      'value' => ($this->get_option('use_batch') == 'batch' ? t('Yes') : t('No')),
    );

    if (!$this->is_compatible() && $this->get_option('use_batch')) {
      $options['use_batch']['value'] .= ' <strong>' . t('(Warning: incompatible)') . '</strong>';
    }
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'use_batch':
        $form['#title'] .= t('Batched export');
        $form['use_batch'] = array(
          '#type' => 'radios',
          '#description' => t(''),
          '#default_value' => $this->get_option('use_batch'),
          '#options' => array(
            'no_batch' => t('Export data all in one segment. Possible time and memory limit issues.'),
            'batch' => t('Export data in small segments to build a complete export. Recommended for large exports sets (1000+ rows)'),
          ),
        );
        // Allow the administrator to configure the number of items exported per batch.
        $form['segment_size'] = array(
          '#type' => 'select',
          '#title' => t('Segment size'),
          '#description' => t('If each row of your export consumes a lot of memory to render, then reduce this value. Higher values will generally mean that the export completes in less time but will have a higher peak memory usage.'),
          '#options' => drupal_map_assoc(range(1, 500)),
          '#default_value' => $this->get_option('segment_size'),
          '#process' => array('ctools_dependent_process'),
          '#dependency' => array(
            'radio:use_batch' => array('batch')
          ),
        );
        $form['return_path'] = array(
          '#title' => t('Return path'),
          '#type' => 'textfield',
          '#description' => t('Return path after the batched operation, leave empty for default. This path will only be used if the export URL is visited directly, and not by following a link when attached to another view display.'),
          '#default_value' => $this->get_option('return_path'),
          '#dependency' => array(
            'radio:use_batch' => array('batch')
          ),
        );
        if (!$this->is_compatible()) {
          $form['use_batch']['#disabled'] = TRUE;
          $form['use_batch']['#default_value'] = 'no_batch';
          $form['use_batch']['message'] = array (
            '#type' => 'markup',
            '#markup' => theme('views_data_export_message', array('message' => t('The underlying database (!db_driver) is incompatible with the batched export option and it has been disabled.', array('!db_driver' => $this->_get_database_driver())), 'type' => 'warning')),
            '#weight' => -10,
          );
        }
        break;

      case 'cache':
        // We're basically going to disable using cache plugins, by disabling
        // the UI.
        if (isset($form['cache']['type']['#options'])) {
          foreach ($form['cache']['type']['#options'] as $id => $v) {
            if ($id != 'none') {
              unset($form['cache']['type']['#options'][$id]);
            }
            $form['cache']['type']['#description'] = t("Views data export isn't currently compatible with caching plugins.");
          }
        }
        break;

    }
  }

  function get_option($option) {
    // Force people to never use caching with Views data export. Sorry folks,
    // but it causes too many issues for our workflow. If you really want to add
    // caching back, then you can subclass this display handler and override
    // this method to add it back.
    if ($option == 'cache') {
      return array('type' => 'none');
    }

    return parent::get_option($option);
  }

  /**
   * Save the options from the options form.
   */
  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);
    switch ($form_state['section']) {
      case 'use_batch':
        $this->set_option('use_batch', $form_state['values']['use_batch']);
        $this->set_option('segment_size', $form_state['values']['segment_size']);
        $this->set_option('return_path', $form_state['values']['return_path']);
        break;
    }
  }

  /**
   * Determine if this view should run as a batch or not.
   */
  function is_batched() {
    // The source of this option may change in the future.
    return ($this->get_option('use_batch') == 'batch') && empty($this->view->live_preview);
  }

  /**
   * Add HTTP headers for the file export.
   */
  function add_http_headers() {
    // Ask the style plugin to add any HTTP headers if it wants.
    if (method_exists($this->view->style_plugin, 'add_http_headers')) {
      $this->view->style_plugin->add_http_headers();
    }
  }

  /**
   * Execute this display handler.
   *
   * This is the main entry point for this display. We do different things based
   * on the stage in the rendering process.
   *
   * If we are being called for the very first time, the user has usually just
   * followed a link to our view. For this phase we:
   * - Register a new batched export with our parent module.
   * - Build and execute the view, redirecting the output into a temporary table.
   * - Set up the batch.
   *
   * If we are being called during batch processing we:
   * - Set up our variables from the context into the display.
   * - Call the rendering layer.
   * - Return with the appropriate progress value for the batch.
   *
   * If we are being called after the batch has completed we:
   * - Remove the index table.
   * - Show the complete page with a download link.
   * - Transfer the file if the download link was clicked.
   */
  function execute() {
    if (!$this->is_batched()) {
      return parent::execute();
    }

    // Try and get a batch context if possible.
    $eid = !empty($_GET['eid']) ? $_GET['eid'] :
            (!empty($this->batched_execution_state->eid) ? $this->batched_execution_state->eid : FALSE);
    if ($eid) {
      $this->batched_execution_state = views_data_export_get($eid);
    }

    // First time through
    if (empty($this->batched_execution_state)) {
      $output = $this->execute_initial();
    }

    // Call me on the cached version of this view please
    // This allows this view to be programatically executed with nothing
    // more than the eid in $_GET in order for it to execute the next chunk
    // TODO: What is going on here?
    /*
     Jamsilver tells me this might be useful one day.
    if (!$this->views_data_export_cached_view_loaded) {
      $view = views_data_export_view_retrieve($this->batched_execution_state->eid);
      $view->set_display($this->view->current_display);
      $view->display_handler->batched_execution_state->eid = $this->batched_execution_state->eid;
      $view->display_handler->views_data_export_cached_view_loaded = TRUE;
      $ret =  $view->execute_display($this->view->current_display);
      $this->batched_execution_state = &$view->display_handler->batched_execution_state;
      return $ret;
    }*/

    // Last time through
    if ($this->batched_execution_state->batch_state == VIEWS_DATA_EXPORT_FINISHED) {
      $output = $this->execute_final();
    }
    // In the middle of processing
    else {
      $output = $this->execute_normal();
    }

    //Ensure any changes we made to the database sandbox are saved
    views_data_export_update($this->batched_execution_state);

    return $output;
  }


  /**
   * Initializes the whole export process and starts off the batch process.
   *
   * Page execution will be ended at the end of this function.
   */
  function execute_initial() {

    // Register this export with our central table - get a unique eid
    // Also store our view in a cache to be retrieved with each batch call
    $this->batched_execution_state = views_data_export_new($this->view->name, $this->view->current_display, $this->outputfile_create());
    views_data_export_view_store($this->batched_execution_state->eid, $this->view);

    // We need to build the index right now, before we lose $_GET etc.
    $this->initialize_index();
    //$this->batched_execution_state->fid = $this->outputfile_create();

    // Initialize the progress counter
    $this->batched_execution_state->sandbox['max'] = db_query('SELECT COUNT(*) FROM {' . $this->index_tablename() . '}')->fetchField();
    // Record the time we started.
    list($usec, $sec) = explode(' ', microtime());
    $this->batched_execution_state->sandbox['started'] = (float) $usec + (float) $sec;

    // Build up our querystring for the final page callback.
    $querystring = array(
      'eid' => $this->batched_execution_state->eid,
      'return-url' => NULL,
    );

    // If we have a configured return path, use that.
    if ($this->get_option('return_path')) {
      $querystring['return-url'] = $this->get_option('return_path');
    }
    // Else if we were attached to another view, grab that for the final URL.
    else if (!empty($_GET['attach']) && isset($this->view->display[$_GET['attach']])) {
      // Get the path of the attached display:
      $querystring['return-url'] = $this->view->get_url(NULL, $this->view->display[$_GET['attach']]->handler->get_path());
    }

    //Set the batch off
    $batch = array(
      'operations' => array (
        array('_views_data_export_batch_process', array($this->batched_execution_state->eid, $this->view->current_display,  $this->view->get_exposed_input())),
      ),
      'title' => t('Building export'),
      'init_message' => t('Export is starting up.'),
      'progress_message' => t('Exporting @percentage% complete,'),
      'error_message' => t('Export has encountered an error.'),
    );

    // We do not return, so update database sandbox now
    views_data_export_update($this->batched_execution_state);

    $final_destination = $this->view->get_url();

    // Provide a way in for others at this point
    // e.g. Drush to grab this batch and yet execute it in
    // it's own special way
    $batch['view_name'] = $this->view->name;
    $batch['exposed_filters'] = $this->view->get_exposed_input();
    $batch['display_id'] = $this->view->current_display;
    $batch['eid'] = $this->batched_execution_state->eid;
    $batch_redirect = array($final_destination, array('query' => $querystring));
    drupal_alter('views_data_export_batch', $batch, $batch_redirect);

    // Modules may have cleared out $batch, indicating that we shouldn't process further.
    if (!empty($batch)) {
      batch_set($batch);
      // batch_process exits
      batch_process($batch_redirect);
    }
  }


  /**
   * Compiles the next chunk of the output file
   */
  function execute_normal() {

    // Pass through to our render method,
    $output = $this->view->render();

    // Append what was rendered to the output file.
    $this->outputfile_write($output);

    // Store for convenience.
    $state = &$this->batched_execution_state;
    $sandbox = &$state->sandbox;

    // Update progress measurements & move our state forward
    switch ($state->batch_state) {

      case VIEWS_DATA_EXPORT_BODY:
        // Remove rendered results from our index
        if (count($this->view->result) && ($sandbox['weight_field_alias'])) {
          $last = end($this->view->result);
          db_delete($this->index_tablename())
            ->condition($sandbox['weight_field_alias'], $last->{$sandbox['weight_field_alias']}, '<=')
            ->execute();

          // Update progress.
          $progress = db_query('SELECT COUNT(*) FROM {' . $this->index_tablename() . '}')->fetchField();
          // TODO: These next few lines are messy, clean them up.
          $progress = 0.99 - ($progress / $sandbox['max'] * 0.99);
          $progress = ((int)floor($progress * 100000));
          $progress = $progress / 100000;
          $sandbox['finished'] = $progress;
        }
        else {
          // No more results.
          $progress = 0.99;
          $state->batch_state = VIEWS_DATA_EXPORT_FOOTER;
        }
        break;

      case VIEWS_DATA_EXPORT_HEADER:
        $sandbox['finished'] = 0;
        $state->batch_state = VIEWS_DATA_EXPORT_BODY;
        break;

      case VIEWS_DATA_EXPORT_FOOTER:
        $sandbox['finished'] = 1;
        $state->batch_state = VIEWS_DATA_EXPORT_FINISHED;
        break;
    }

    // Create a more helpful exporting message.
    $sandbox['message'] = $this->compute_time_remaining($sandbox['started'], $sandbox['finished']);
  }


  /**
   * Renders the final page
   *  We should be free of the batch at this point
   */
  function execute_final() {
    // Should we download the file.
    if (!empty($_GET['download'])) {
      // This next method will exit.
      $this->transfer_file();
    }
    else {
      // Remove the index table.
      $this->remove_index();
      return $this->render_complete();
    }
  }


  /**
   * Render the display.
   *
   * We basically just work out if we should be rendering the header, body or
   * footer and call the appropriate functions on the style plugins.
   */
  function render() {

    if (!$this->is_batched()) {
      $result = parent::render();
      if (empty($this->view->live_preview)) {
        $this->add_http_headers();
      }
      return $result;
    }

    $this->view->build();

    switch ($this->batched_execution_state->batch_state) {
      case VIEWS_DATA_EXPORT_BODY:
        $output = $this->view->style_plugin->render_body();
        break;
      case VIEWS_DATA_EXPORT_HEADER:
        $output = $this->view->style_plugin->render_header();
        break;
      case VIEWS_DATA_EXPORT_FOOTER:
        $output = $this->view->style_plugin->render_footer();
        break;
    }

    return $output;
  }



  /**
   * Trick views into thinking that we have executed the query and got results.
   *
   * We are called in the build phase of the view, but short circuit straight to
   * getting the results and making the view think it has already executed the
   * query.
   */
  function query() {

    if (!$this->is_batched()) {
      return parent::query();
    }

    // Make the query distinct if the option was set.
    if ($this->get_option('distinct')) {
      $this->view->query->set_distinct();
    }

    if (!empty($this->batched_execution_state->batch_state) && !empty($this->batched_execution_state->sandbox['weight_field_alias'])) {

      switch ($this->batched_execution_state->batch_state) {
        case VIEWS_DATA_EXPORT_BODY:
        case VIEWS_DATA_EXPORT_HEADER:
        case VIEWS_DATA_EXPORT_FOOTER:
          // Tell views its been executed.
          $this->view->executed = TRUE;

          // Grab our results from the index, and push them into the view result.
          // TODO: Handle external databases.
          $result = db_query_range('SELECT * FROM {' . $this->index_tablename() . '} ORDER BY ' . $this->batched_execution_state->sandbox['weight_field_alias'] . ' ASC', 0, $this->get_option('segment_size'));
          $this->view->result = array();
          foreach ($result as $item_hashed) {
            $item = new stdClass();
            // We had to shorten some of the column names in the index, restore
            // those now.
            foreach ($item_hashed as $hash => $value) {
              if (isset($this->batched_execution_state->sandbox['field_aliases'][$hash])) {
                $item->{$this->batched_execution_state->sandbox['field_aliases'][$hash]} = $value;
              }
              else {
                $item->{$hash} = $value;
              }
            }
            // Push the restored $item in the views result array.
            $this->view->result[] = $item;
          }
          $this->view->_post_execute();
          break;
      }
    }
  }


  /**
   * Render the 'Export Finished' page with the link to the file on it.
   */
  function render_complete() {
    $return_path = empty($_GET['return-url']) ? '' : $_GET['return-url'];

    $query = array(
      'download' => 1,
      'eid' => $this->batched_execution_state->eid,
    );

    return theme('views_data_export_complete_page', array(
      'file' => url($this->view->get_url(), array('query' => $query)),
      'errors' => $this->errors,
      'return_url' => $return_path));
  }

  /**
   * TBD - What does 'preview' mean for bulk exports?
   * According to doc:
   * "Fully render the display for the purposes of a live preview or
   * some other AJAXy reason. [views_plugin_display.inc:1877]"
   *
   * Not sure it makes sense for Bulk exports to be previewed in this manner?
   * We need the user's full attention to run the batch. Suggestions:
   * 1) Provide a link to execute the view?
   * 2) Provide a link to the last file we generated??
   * 3) Show a table of the first 20 results?
   */
  function preview() {
    if (!$this->is_batched()) {
      // Can replace with return parent::preview() when views 2.12 lands.
      if (!empty($this->view->live_preview)) {
        // Change the items per page.
        $this->view->set_items_per_page(20);
        // Force a pager to be used.
        $this->set_option('pager', array('type' => 'some', 'options' => array()));
        return '<p>' . t('A maximum of 20 items will be shown here, all results will be shown on export.') . '</p><pre>' . check_plain($this->view->render()) . '</pre>';
      }
      return $this->view->render();
    }
    return '';
  }

  /**
   * Transfer the output file to the client.
   */
  function transfer_file() {
    // Build the view so we can set the headers.
    $this->view->build();
    // Arguments can cause the style to not get built.
    if (!$this->view->init_style()) {
      $this->view->build_info['fail'] = TRUE;
    }
    // Set the headers.
    $this->add_http_headers();
    file_transfer($this->outputfile_path(), array());
  }

  /**
   * Called on export initialization.
   *
   * Modifies the view query to insert the results into a table, which we call
   * the 'index', this means we essentially have a snapshot of the results,
   * which we can then take time over rendering.
   *
   * This method is essentially all the best bits of the view::execute() method.
   */
  protected function initialize_index() {
    $view = &$this->view;
    // Get views to build the query.
    $view->build();

    // Change the query object to use our custom one.
    switch ($this->_get_database_driver()) {
      case 'pgsql':
        $query_class = 'views_data_export_plugin_query_pgsql_batched';
        break;

      default:
        $query_class = 'views_data_export_plugin_query_default_batched';
        break;
    }
    $query = new $query_class();
    // Copy the query over:
    foreach ($view->query as $property => $value) {
      $query->$property = $value;
    }
    // Replace the query object.
    $view->query = $query;

    $view->execute();
  }

  /**
   * Given a view, construct an map of hashed aliases to aliases.
   *
   * The keys of the returned array will have a maximum length of 33 characters.
   */
  function field_aliases_create(&$view) {
    $all_aliases = array();
    foreach ($view->query->fields as $field) {
      if (strlen($field['alias']) > 32) {
        $all_aliases['a' . md5($field['alias'])] = $field['alias'];
      }
      else {
        $all_aliases[$field['alias']] = $field['alias'];
      }
    }
    return $all_aliases;
  }

  /**
   * Create an alias for the weight field in the index.
   *
   * This method ensures that it isn't the same as any other alias in the
   * supplied view's fields.
   */
  function _weight_alias_create(&$view) {
    $alias = 'vde_weight';
    $all_aliases = array();
    foreach ($view->query->fields as $field) {
      $all_aliases[] = $field['alias'];
    }
    // Keep appending '_' until we are unique.
    while (in_array($alias, $all_aliases)) {
      $alias .= '_';
    }
    return $alias;
  }

  /**
   * Remove the index.
   */
  function remove_index() {
    $ret = array();
    if (db_table_exists($this->index_tablename())) {
      db_drop_table($this->index_tablename());
    }
  }

  /**
   * Return the name of the unique table to store the index in.
   */
  function index_tablename() {
    return VIEWS_DATA_EXPORT_INDEX_TABLE_PREFIX . $this->batched_execution_state->eid;
  }

  /**
   * Get the output file path.
   */
  function outputfile_path() {
    if (empty($this->_output_file)) {
      if (!empty($this->batched_execution_state->fid)) {
        // Return the filename associated with this file.
        $this->_output_file = $this->file_load($this->batched_execution_state->fid);
      }
      else {
        return NULL;
      }
    }
    return $this->_output_file->uri;
  }

  /**
   * Called on export initialization
   * Creates the output file, registers it as a temporary file with Drupal
   * and returns the fid
   */
  protected function outputfile_create() {

    $dir = variable_get('views_data_export_directory', 'temporary://views_plugin_display');

    // Make sure the directory exists first.
    if (!file_prepare_directory($dir, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      $this->abort_export(t('Could not create temporary directory for result export (@dir). Check permissions.', array ('@dir' => $dir)));
    }

    $path = drupal_tempnam($dir, 'views_data_export');

    // Save the file into the DB.
    $file = $this->file_save_file($path);

    return $file->fid;
  }

  /**
   * Write to the output file.
   */
  protected function outputfile_write($string) {
    $output_file = $this->outputfile_path();
    if (file_put_contents($output_file, $string, FILE_APPEND) === FALSE) {
      $this->abort_export(t('Could not write to temporary output file for result export (@file). Check permissions.', array ('@file' => $output_file)));
    }
  }

  function abort_export($errors) {
    // Just cause the next batch to do the clean-up
    if (!is_array($errors)) {
      $errors = array($errors);
    }
    foreach ($errors as $error) {
      drupal_set_message($error . ' ['. t('Export Aborted') . ']', 'error');
    }
    $this->batched_execution_state->batch_state = VIEWS_DATA_EXPORT_FINISHED;
  }

  /**
    * Load a file from the database.
    *
    * @param $fid
    *   A numeric file id or string containing the file path.
    * @return
    *   A file object.
    */
  function file_load($fid) {
    return file_load($fid);
  }

  /**
  * Save a file into a file node after running all the associated validators.
  *
  * This function is usually used to move a file from the temporary file
  * directory to a permanent location. It may be used by import scripts or other
  * modules that want to save an existing file into the database.
  *
  * @param $filepath
  *   The local file path of the file to be saved.
  * @return
  *   An array containing the file information, or 0 in the event of an error.
  */
  function file_save_file($filepath) {
    return file_save_data('', $filepath, FILE_EXISTS_REPLACE);
  }

  /**
   * Helper function that computes the time remaining
   */
  function compute_time_remaining($started, $finished) {
    list($usec, $sec) = explode(' ', microtime());
    $now = (float) $usec + (float) $sec;
    $diff = round(($now - $started), 0);
    // So we've taken $diff seconds to get this far.
    if ($finished > 0) {
      $estimate_total = $diff / $finished;
      $stamp = max(1, $estimate_total - $diff);
      // Round up to nearest 30 seconds.
      $stamp = ceil($stamp / 30) * 30;
      // Set the message in the batch context.
      return t('Time remaining: about @interval.', array('@interval' => format_interval($stamp)));
    }
  }

  /**
   * Checks the driver of the database underlying
   * this query and returns FALSE if it is imcompatible
   * with the approach taken in this display.
   * Basically mysql & mysqli will be fine, pg will not
   */
  function is_compatible() {
    $incompatible_drivers = array (
      //'pgsql',
    );
    $db_driver = $this->_get_database_driver();
    return !in_array($db_driver, $incompatible_drivers);
  }

  function  _get_database_driver() {
    $name = !empty($this->view->base_database) ? $this->view->base_database : 'default';
    $conn_info = Database::getConnectionInfo($name);
    return $conn_info['default']['driver'];
  }
}

class views_data_export_plugin_query_default_batched extends views_plugin_query_default {


  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->current_page.
   */
  function execute(&$view) {
    $display_handler = &$view->display_handler;
    $external = FALSE; // Whether this query will run against an external database.
    $query = $view->build_info['query'];
    $count_query = $view->build_info['count_query'];

    $query->addMetaData('view', $view);
    $count_query->addMetaData('view', $view);

    if (empty($this->options['disable_sql_rewrite'])) {
      $base_table_data = views_fetch_data($this->base_table);
      if (isset($base_table_data['table']['base']['access query tag'])) {
        $access_tag = $base_table_data['table']['base']['access query tag'];
        $query->addTag($access_tag);
        $count_query->addTag($access_tag);
      }
    }

    $items = array();
    if ($query) {
      $additional_arguments = module_invoke_all('views_query_substitutions', $view);

      // Count queries must be run through the preExecute() method.
      // If not, then hook_query_node_access_alter() may munge the count by
      // adding a distinct against an empty query string
      // (e.g. COUNT DISTINCT(1) ...) and no pager will return.
      // See pager.inc > PagerDefault::execute()
      // http://api.drupal.org/api/drupal/includes--pager.inc/function/PagerDefault::execute/7
      // See http://drupal.org/node/1046170.
      $count_query->preExecute();

      // Build the count query.
      $count_query = $count_query->countQuery();

      // Add additional arguments as a fake condition.
      // XXX: this doesn't work... because PDO mandates that all bound arguments
      // are used on the query. TODO: Find a better way to do this.
      if (!empty($additional_arguments)) {
        // $query->where('1 = 1', $additional_arguments);
        // $count_query->where('1 = 1', $additional_arguments);
      }

      $start = microtime(TRUE);

      if ($this->pager->use_count_query() || !empty($view->get_total_rows)) {
        $this->pager->execute_count_query($count_query);
      }

      // Let the pager modify the query to add limits.
      $this->pager->pre_execute($query);

      if (!empty($this->limit) || !empty($this->offset)) {
        // We can't have an offset without a limit, so provide a very large limit instead.
        $limit  = intval(!empty($this->limit) ? $this->limit : 999999);
        $offset = intval(!empty($this->offset) ? $this->offset : 0);
        $query->range($offset, $limit);
      }

      try {
        // The $query is final and ready to go, we are going to redirect it to
        // become an insert into our table, sneaky!
        // Our query will look like:
        // CREATE TABLE {idx} SELECT @row := @row + 1 AS weight_alias, cl.* FROM
        // (-query-) AS cl, (SELECT @row := 0) AS r
        // We do some magic to get the row count.

        $display_handler->batched_execution_state->sandbox['weight_field_alias'] = $display_handler->_weight_alias_create($view);

        $display_handler->batched_execution_state->sandbox['field_aliases'] = $display_handler->field_aliases_create($view);
        $select_aliases = array();
        foreach ($display_handler->batched_execution_state->sandbox['field_aliases'] as $hash => $alias) {
          $select_aliases[] = "cl.$alias AS $hash";
        }

        // TODO: this could probably be replaced with a query extender and new query type.
        $query->preExecute();
        $args = $query->getArguments();
        $insert_query = 'CREATE TABLE {' . $display_handler->index_tablename() . '} SELECT @row := @row + 1 AS ' . $display_handler->batched_execution_state->sandbox['weight_field_alias'] . ', ' . implode(', ', $select_aliases) . ' FROM (' . (string)$query . ') AS cl, (SELECT @row := 0) AS r';
        db_query($insert_query, $args);


        $view->result = array();

        $this->pager->post_execute($view->result);

        if ($this->pager->use_pager()) {
          $view->total_rows = $this->pager->get_total_items();
        }

        // Now create an index for the weight field, otherwise the queries on the
        // index will take a long time to execute.
        db_add_unique_key($display_handler->index_tablename(), $display_handler->batched_execution_state->sandbox['weight_field_alias'], array($display_handler->batched_execution_state->sandbox['weight_field_alias']));
      }
      catch (Exception $e) {
        $view->result = array();
        debug('Exception: ' . $e->getMessage());
      }

    }
    $view->execute_time = microtime(TRUE) - $start;
  }
}

class views_data_export_plugin_query_pgsql_batched extends views_data_export_plugin_query_default_batched {


  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->current_page.
   */
  function execute(&$view) {
    $display_handler = &$view->display_handler;
    $external = FALSE; // Whether this query will run against an external database.
    $query = $view->build_info['query'];
    $count_query = $view->build_info['count_query'];

    $query->addMetaData('view', $view);
    $count_query->addMetaData('view', $view);

    if (empty($this->options['disable_sql_rewrite'])) {
      $base_table_data = views_fetch_data($this->base_table);
      if (isset($base_table_data['table']['base']['access query tag'])) {
        $access_tag = $base_table_data['table']['base']['access query tag'];
        $query->addTag($access_tag);
        $count_query->addTag($access_tag);
      }
    }

    $items = array();
    if ($query) {
      $additional_arguments = module_invoke_all('views_query_substitutions', $view);

      // Count queries must be run through the preExecute() method.
      // If not, then hook_query_node_access_alter() may munge the count by
      // adding a distinct against an empty query string
      // (e.g. COUNT DISTINCT(1) ...) and no pager will return.
      // See pager.inc > PagerDefault::execute()
      // http://api.drupal.org/api/drupal/includes--pager.inc/function/PagerDefault::execute/7
      // See http://drupal.org/node/1046170.
      $count_query->preExecute();

      // Build the count query.
      $count_query = $count_query->countQuery();

      // Add additional arguments as a fake condition.
      // XXX: this doesn't work... because PDO mandates that all bound arguments
      // are used on the query. TODO: Find a better way to do this.
      if (!empty($additional_arguments)) {
        // $query->where('1 = 1', $additional_arguments);
        // $count_query->where('1 = 1', $additional_arguments);
      }

      $start = microtime(TRUE);

      if ($this->pager->use_count_query() || !empty($view->get_total_rows)) {
        $this->pager->execute_count_query($count_query);
      }

      // Let the pager modify the query to add limits.
      $this->pager->pre_execute($query);

      if (!empty($this->limit) || !empty($this->offset)) {
        // We can't have an offset without a limit, so provide a very large limit instead.
        $limit  = intval(!empty($this->limit) ? $this->limit : 999999);
        $offset = intval(!empty($this->offset) ? $this->offset : 0);
        $query->range($offset, $limit);
      }

      try {
        // The $query is final and ready to go, we are going to redirect it to
        // become an insert into our table, sneaky!
        // Our query will look like:
        // CREATE TABLE {idx} SELECT @row := @row + 1 AS weight_alias, cl.* FROM
        // (-query-) AS cl, (SELECT @row := 0) AS r
        // We do some magic to get the row count.

        $display_handler->batched_execution_state->sandbox['weight_field_alias'] = $display_handler->_weight_alias_create($view);

        $display_handler->batched_execution_state->sandbox['field_aliases'] = $display_handler->field_aliases_create($view);
        $select_aliases = array();
        foreach ($display_handler->batched_execution_state->sandbox['field_aliases'] as $hash => $alias) {
          $select_aliases[] = "cl.$alias AS $hash";
        }

        // TODO: this could probably be replaced with a query extender and new query type.
        $query->preExecute();
        $args = $query->getArguments();
        // Create temporary sequence
        $seq_name = $display_handler->index_tablename() . '_seq';
        db_query('CREATE TEMP sequence ' . $seq_name);
        // Query uses sequence to create row number
        $insert_query = 'CREATE TABLE {' . $display_handler->index_tablename() . "} AS SELECT nextval('". $seq_name . "') AS " . $display_handler->batched_execution_state->sandbox['weight_field_alias'] . ', ' . implode(', ', $select_aliases) . ' FROM (' . (string)$query . ') AS cl';
        db_query($insert_query, $args);


        $view->result = array();

        $this->pager->post_execute($view->result);

        if ($this->pager->use_pager()) {
          $view->total_rows = $this->pager->get_total_items();
        }

        // Now create an index for the weight field, otherwise the queries on the
        // index will take a long time to execute.
        db_add_unique_key($display_handler->index_tablename(), $display_handler->batched_execution_state->sandbox['weight_field_alias'], array($display_handler->batched_execution_state->sandbox['weight_field_alias']));
      }
      catch (Exception $e) {
        $view->result = array();
        debug('Exception: ' . $e->getMessage());
      }

    }
    $view->execute_time = microtime(TRUE) - $start;
  }
}
