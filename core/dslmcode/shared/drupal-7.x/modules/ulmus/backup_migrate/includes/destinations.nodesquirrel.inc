<?php

/**
 * @file
 * Functions to handle the NodeSquirrel backup destination.
 */

define('NODESQUIRREL_SECRET_KEY_PATTERN', '/^[0-9a-f]{32}\:?[0-9a-f]{32}$/');

/**
 * The NodeSquirrel settings form page.
 */
function nodesquirrel_settings_page() {
  return drupal_get_form('nodesquirrel_settings');
}

/**
 * Check that a nodesquirel key is valid.
 */
function nodesquirrel_check_secret_key($secret_key) {
  if ($destination = nodesquirrel_get_destination($secret_key)) {
    if ($destination->confirm_destination()) {
      return $destination;
    }
  }
  return FALSE;
}

/**
 * Get the NS destination for the given key.
 */
function nodesquirrel_get_destination($secret_key) {
  if ($secret_key) {
    backup_migrate_include('destinations');
    $destination = backup_migrate_create_destination('nodesquirrel', array('destination_id' => 'nodesquirrel'));
    $destination->settings['secret_key'] = $secret_key;
    return $destination;
  }
  return NULL;
}

/**
 * Get a helper link to activate a site and create a tree.
 */
function nodesquirrel_get_activate_help_text() {
  $activate_link = nodesquirrel_get_activate_link();
  return array(
    '#type' => 'item',
    '#title' => t('Need a Secret Key?'),
    '#markup' => t('Visit !nodesquirrel.', array('!nodesquirrel' => $activate_link)),
    '#description' => t('Don\'t worry if you don\'t have an account yet. You can create one when you get there.'),
  );
}

/**
 * Get a helper link to activate a site and create a tree.
 */
function nodesquirrel_get_activate_link() {
  $activate_link = l('nodesquirrel.com/activate', variable_get('nodesquirrel_activate_url', 'http://manage.nodesquirrel.com/activate'), array('query' => array('url' => url('', array('absolute' => TRUE)), 'email' => variable_get('site_mail', ''), 'configure' => url($_GET['q'], array('absolute' => TRUE)))));
  return $activate_link;
}

/**
 * Get a helper link to activate a site and create a tree.
 */
function nodesquirrel_get_manage_link($destination) {
  $url = variable_get('nodesquirrel_manage_url', 'http://manage.nodesquirrel.com') . '/backups/' . $destination->_get_destination();
  return l($url, $url);
}

/**
 * NodeSquirrel settings form.
 */
function nodesquirrel_settings($form_state) {
  _backup_migrate_message_callback('_backup_migrate_message_browser');

  $form = array();

  $key = variable_get('nodesquirrel_secret_key', '');
  $destination = nodesquirrel_check_secret_key($key);

  $form['intro'] = array(
    '#type' => 'markup',
    '#markup' => t('<p>For better protection, back your site up regularly to a location not on your web server. !nodesquirrel is the cloud backup service built by the maintainers of Backup and Migrate. Find out more at <a href="http://nodesquirrel.com">nodesquirrel.com</a></p><p>You can also !add such as FTP or Amazon S3. Additional 3rd party options are available and many are listed on the !bam.', array('!nodesquirrel' => l(t('NodeSquirrel'), 'http://nodesquirrel.com'), '!add' => l(t('add other offsite destinations'), BACKUP_MIGRATE_MENU_PATH . '/destination/list/add'), '!bam' => l(t('Backup and Migrate project page'), 'http://drupal.org/project/backup_migrate'))),
    );

  $form['nodesquirrel_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('NodeSquirrel Status'),
  );
  $form['nodesquirrel_status']['status'] = array(
    '#type' => 'item',
    '#title' => t('NodeSquirrel Status'),
    '#markup' => t('Not Configured'),
  );

  // Warn the user if the key they entered is invalid.
  if ($key && empty($destination)) {
    $form['nodesquirrel_status']['status']['#markup'] = t('Your secret key does not seem to be valid. Please check that you entered it correctly or visit !ns to generate a new key.', array('!ns' => nodesquirrel_get_activate_link()));
  }
  else if (!empty($destination)) {
    $form['nodesquirrel_status']['manage'] = array(
      '#type' => 'item',
      '#title' => t('Management Console'),
      '#markup' => nodesquirrel_get_manage_link($destination),
      '#description' => t('You can use the NodeSquirrel management console to add and edit your sites, reset your secret key, download and delete backups, and modify your NodeSquirrel account.'),
    );
    $form['nodesquirrel_status']['status']['#markup'] = t('Ready to Backup');
    if (user_access('perform backup')) {
      $form['nodesquirrel_status']['status']['#markup'] .= ' ' . l('(' . t('backup now') . ')', BACKUP_MIGRATE_MENU_PATH, array('query' => array('destination_id' => 'nodesquirrel')));
    }
  }

  $form['nodesquirrel_credentials'] = array(
    '#type' => 'fieldset',
    '#title' => t('NodeSquirrel Credentials'),
  );
  $form['nodesquirrel_credentials']['nodesquirrel_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret Key'),
    '#size' => 80,
    '#default_value' => variable_get('nodesquirrel_secret_key', ''),
  );
  if (empty($destination)) {
    $form['nodesquirrel_credentials']['secret_key_help'] = nodesquirrel_get_activate_help_text();
  }

  $form['nodesquirrel_schedule'] = array(
    '#type' => 'fieldset',
    '#title' => t('Backup Schedule'),
  );


  $schedule = variable_get('nodesquirrel_schedule', 60*60*24);
  $form['nodesquirrel_schedule']['nodesquirrel_schedule'] = array(
    '#type' => 'select',
    '#title' => t('Backup to NodeSquirrel'),
    '#options' => array(
      ''            => t('- None - '),
      (60*60)       => t('Hourly'),
      (60*60*24)    => t('Daily'),
      (60*60*24*7)  => t('Weekly'),
    ),
    '#default_value' => variable_get('nodesquirrel_schedule', 60*60*24),
    '#description' => t('Set up a schedule to back up your database to NodeSquirrel. You can customize this schedule in the !schedule. Not seeing your automatic backups? Make sure !cron is set to run at the same frequency or higher.', array('!schedule' => l(t('Schedules tab'), BACKUP_MIGRATE_MENU_PATH . '/schedule'), '!cron' => l(t('cron'), 'http://drupal.org/cron'))),
  );

  // If the schedule has been overriden it must be edited in the schedule tab.
  backup_migrate_include('crud');
  $item = backup_migrate_crud_get_item('schedule', 'nodesquirrel');
  if ($item && $item->storage == BACKUP_MIGRATE_STORAGE_OVERRIDEN) {
    $form['nodesquirrel_schedule']['nodesquirrel_schedule']['#options'] = array('' => $item->get_frequency_description());
    $form['nodesquirrel_schedule']['nodesquirrel_schedule']['#disabled'] = TRUE;
    $form['nodesquirrel_schedule']['nodesquirrel_schedule']['#description'] = t('Your NodeSquirrel schedule has been overriden and must be edited in the !schedule.', array('!schedule' => l(t('Schedules tab'), BACKUP_MIGRATE_MENU_PATH . '/schedule/list/edit/nodesquirrel')));
  }

  return system_settings_form($form);
}

/**
 * A destination for sending database backups to the NodeSquirel backup service.
 *
 * @ingroup backup_migrate_destinations
 */
class backup_migrate_destination_nodesquirrel extends backup_migrate_destination {
  var $supported_ops = array('scheduled backup', 'manual backup', 'restore', 'list files', 'configure', 'delete');
  var $cache_files = TRUE;
  // Don't generate a metadata file as NodeSquirrel can save metadata natively.
  var $save_metadata = FALSE;

  /**
   * Get the destination name. Provide a default.
   */
  function get_name() {
    if (empty($this->name)) {
      return t('NodeSquirrel');
    }
    return $this->name;
  }

  /**
   * Save to the NodeSquirrel destination.
   */
  function save_file($file, $settings) {
    if ($destination = $this->_get_destination()) {
      srand((double)microtime()*1000000);

      $filename = $file->filename();
      $filesize = filesize($file->filepath());
      $ticket = $this->_xmlrpc('backups.getUploadTicket', array($destination, $filename, $filesize, $file->file_info));

      if ($ticket) {
  
        $url = $ticket['url'];
  
        // If the ticket requires authentication add our username/password to the url.
        if (!empty($ticket['auth']) && $ticket['auth'] = 'basic') {
          $parts = parse_url($ticket['url']);
          list($parts['user'], $parts['pass']) = $this->get_user_pass();
          $url = $this->glue_url($parts, FALSE);
        }

        $out = $this->_post_file($url, 'POST', $ticket['params'], $file);

        if ($out->code == 200) {
          // Confirm the upload.
          $confirm = $this->_xmlrpc('backups.confirmUpload', array($destination, $filename, $filesize));

          if ($confirm['success']) {
            // Set a message with a link to the manage console.
            $url = variable_get('nodesquirrel_manage_url', 'http://manage.nodesquirrel.com') . '/backups/' . $this->_get_destination();
            _backup_migrate_message('Your backup has been saved to your NodeSquirrel account. View it at !account', array('!account' => l($url, $url)));

            return $file;
          }
          else {
            _backup_migrate_message('The backup file never made it to the NodeSquirrel backup server. There may have been a network problem. Please try again later');
          }
        }
        else {
          $error = !empty($out->headers['x-bams-error']) ? $out->headers['x-bams-error'] : $out->error;
          _backup_migrate_message('The NodeSquirrel server returned the following error: %err', array('%err' => $error), 'error');
        }
      }
      else if ($err = xmlrpc_error()) {
        // XMLRPC errors are already handled by the server function below.
      }
      else {
        _backup_migrate_message('The NodeSquirrel server refused the backup but did not specify why. Maybe the server is down.');
      }
    }
    return NULL;
  }

  /**
   * Load from the NodeSquirrel destination.
   */
  function load_file($file_id) {
    if ($destination = $this->_get_destination()) {
      backup_migrate_include('files');
      $file = new backup_file(array('filename' => $file_id));

      $ticket = $this->_xmlrpc('backups.getDownloadTicket', array($destination, $file_id));

      if ($ticket && $url = $ticket['url']) {
        // If the ticket requires authentication add our username/password to the url.
        if (!empty($ticket['auth']) && $ticket['auth'] = 'basic') {
          $parts = parse_url($ticket['url']);
          $parts['user'] = @$this->dest_url['user'];
          $parts['pass'] = @$this->dest_url['pass'];
          $url = $this->glue_url($parts, FALSE);
        }
  
        $out = drupal_http_request($url);

        if ($out->code == 200) {
          file_put_contents($file->filepath(), $out->data);
          return $file;
        }
        else {
          $error = !empty($out->headers['x-bams-error']) ? $out->headers['x-bams-error'] : $out->error;
          _backup_migrate_message('The server returned the following error: %err', array('%err' => $error), 'error');
        }
      }
    }
    return NULL;
  }

  /**
   * Delete from the NodeSquirrel destination.
   */
  function delete_file($file_id) {
    if ($destination = $this->_get_destination()) {
      $result = $this->_xmlrpc('backups.deleteFile', array($destination, $file_id));
    }
  }

  /**
   * List the files in the remote destination.
   */
  function _list_files() {
    $files = array();
    backup_migrate_include('files');

    if ($destination = $this->_get_destination()) {
      $file_list = $this->_xmlrpc('backups.listFiles', array($destination));
      foreach ((array)$file_list as $file) {
        $files[$file['filename']] = new backup_file($file);
      }
    }

    return $files;
  }

  /**
   * List the files in the remote destination.
   */
  function check_limits() {
    if (empty($this->limits)) {
      $this->limits = $this->_xmlrpc('backups.getLimits', array($this->_get_destination()));
    }
    return $this->limits;
  }

  /**
   * Check that a destination is valid.
   */
  function confirm_destination() {
    return $this->check_limits();
  }

  /**
   * Get the form for the settings for this destination.
   */
  function edit_form() {
    $form = parent::edit_form();

    $form['settings'] = array('#tree' => TRUE);
    $activate_link = l('nodesquirrel.com/activate', variable_get('nodesquirrel_activate_url', 'http://manage.nodesquirrel.com/activate'), array('query' => array('url' => url('', array('absolute' => TRUE)), 'email' => variable_get('site_mail', ''), 'configure' => url($_GET['q'], array('absolute' => TRUE)))));

    // Retrieve the key from the settings or get it from the get string if this is an auto-config action.
    $key = $this->settings('secret_key');
    if (!empty($_GET['key']) && preg_match(NODESQUIRREL_SECRET_KEY_PATTERN, $_GET['key'])) {
      $key = $_GET['key'];
    }

    $form['settings']['secret_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Secret Key'),
      '#default_value' => $key,
    );
    $form['settings']['location'] = array('#type' => 'value', '#value' => '');

    $form['settings']['secret_key_help'] = array(
      '#type' => 'item',
      '#title' => t('Need a Secret Key?'),
      '#markup' => t('Visit !nodesquirrel.', array('!nodesquirrel' => $activate_link)),
    );

    return $form;
  }



  /**
   * Submit the configuration form. Glue the url together and add the old password back if a new one was not specified.
   */
  function edit_form_validate($form, &$form_state) {
    $key = trim($form_state['values']['settings']['secret_key']);
    if ($key) {
      if (!preg_match(NODESQUIRREL_SECRET_KEY_PATTERN, $key)) {
        form_set_error('secret_key', 'The secret key you entered is not the right format. Please make sure you copy it exactly.');
        return;
      }
      $this->settings['secret_key'] = check_plain($key);

      $limits = $this->check_limits();

      if (!$limits) {
        $err = xmlrpc_error();
        if (!empty($err->code) && $err->code == '401') {
          form_set_error('user', 'Could not login to server. Please check that your secret key is correct.');
        }
        else {
          form_set_error('', 'There was an error retrieving the specified site. Please check that your secret key is correct.');
        }
      }
    }
  }

  /**
   * Submit the configuration form. Glue the url together and add the old password back if a new one was not specified.
   */
  function edit_form_submit($form, &$form_state) {
    $form_state['values']['secret_key'] = check_plain($form_state['values']['settings']['secret_key']);
    parent::edit_form_submit($form, $form_state);
  }

  /**
   * Get the destination id or warn the user that it has not been set.
   */
  function _get_destination($warn = TRUE) {
    list($id, $key) = $this->get_user_pass();
    return $id;
  }

  /**
   * Get the destination id or warn the user that it has not been set.
   */
  function _get_private_key($warn = TRUE) {
    list($id, $key) = $this->get_user_pass();
    return $key;
  }

  /**
   * Break the secret key into the public/private key (user/pass).
   */
  function get_user_pass() {
    $key = $this->settings('secret_key');
    // The username is the first 32 chars.
    $user = substr($key, 0, 32);
    // The pass is the last 32 chars. There may be a separating character.
    $pass = substr($key, strlen($key) - 32);
    return array($user, $pass);
  }

  function get_display_location() {
    return t('NodeSquirrel.com');
  }

  function add_scheme($url) {
    return 'http://' . $url;
  }

  /**
   * Get the form for the settings for this destination.
   */
  function _xmlrpc($method, $args = array()) {
    // Retrieve the severs or read them from a stored variable.
    $servers = $this->_get_endpoints();

    // Do the actual call.
    return $this->__xmlrpc($method, $args, $servers);
  }

  /**
   * Get the form for the settings for this destination.
   */
  function __xmlrpc($method, $args, $servers, $retry = 3) {
    if ($servers && --$retry > 0) {
      // Add the key authentication arguments if we can.
      if ($this->_sign_request($args)) {  
        $url = reset($servers);
        // Try each available server in order.
        while ($url) {
  
          $url = $this->add_scheme($url);

          $out = xmlrpc($url, array($method => $args));
  
          // Check for errors.
          $err = xmlrpc_error();
          if ($err && $err->is_error) {
            switch ($err->code) {
              case '500':
              case '503':
              case '404':
                // Some sort of server error. Try the next one.
                $url = next($servers);

                // If we're at the end of the line then try refetching the urls
                if (!$url) {
                  $servers = $this->_get_endpoints(TRUE, $retry);
                  return $this->__xmlrpc($method, $args, $servers, $retry);
                }
              break;
              case '300':
                // 'Multiple Choices' means that the existing server list needs to be refreshed.
                $servers = $this->_get_endpoints(TRUE, $retry);
                return $this->__xmlrpc($method, $args, $servers, $retry);
              break;
              case '401':
              case '403':
                // Authentication failed.
                _backup_migrate_message('Couldn\'t log in to NodeSquirrel. The server error was: %err', array('%err' => $err->message), 'error');
                return FALSE;
              break;
              default:
                // Some sort of client error. Don't try the next server because it'll probably say the same thing.
                _backup_migrate_message('The NodeSquirrel server returned the following error: %err', array('%err' => $err->message), 'error');
                return FALSE;
              break;
            }
          }
          // No error, return the result.
          else {
            return $out;
          }
        }
      }
    }
  }

  /** 
   * Genrate a hash with a given secret key, timestamp and random value.
   */
  function _get_hash($time, $nonce) {
    if ($private_key = $this->_get_private_key()) {
      $message = $time . ':' . $nonce . ':' . $private_key;
      // Use HMAC-SHA1 to authenticate the call.
      $hash = base64_encode(
        pack('H*', sha1((str_pad($private_key, 64, chr(0x00)) ^ (str_repeat(chr(0x5c), 64))) .
        pack('H*', sha1((str_pad($private_key, 64, chr(0x00)) ^ (str_repeat(chr(0x36), 64))) .
        $message))))
      );
      return $hash;
    }
    _backup_migrate_message('You must enter a valid private key to use NodeSquirrel.', array(), 'error');
    return FALSE;
  }

  /** 
   * Genrate a hash with a given secret key, timestamp and random value.
   */
  function _sign_request(&$args) {
    $nonce  = md5(mt_rand());
    $time   = time();
    $hash   = $this->_get_hash($time, $nonce); 
    if ($hash) {
      array_unshift($args, $nonce);
      array_unshift($args, $time);
      array_unshift($args, $hash);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Retrieve the list of servers.
   */
  function _get_endpoints($refresh = FALSE, $retry = 3) {
    $servers = (array)variable_get('nodesquirrel_endpoint_urls', array());

    // No servers saved or a force refreshr required.
    if ($refresh || empty($servers)) {
      $servers = array_unique(array_merge($servers, variable_get('nodesquirrel_default_endpoint_urls', array('api.nodesquirrel.com/services/xmlrpc'))));
      // Call the get endpoints method but use the default or previous servers to avoid infinite loops.
      $new_servers = $this->__xmlrpc('backups.getEndpoints', array($this->_get_destination(), 'xmlrpc'), $servers, $retry);
      if ($new_servers) {
        variable_set('nodesquirrel_endpoint_urls', $new_servers);
        $servers = $new_servers;
      }
    }
    return $servers;
  }

  /**
   * Post a file via http.
   *
   * This looks a lot like a clone of drupal_http_request but it can post a large 
   * file without reading the whole file into memory.
   */
  function _post_file($url, $method = 'GET', $params = array(), $file = NULL, $retry = 3) {
    global $db_prefix;
  
    $result = new stdClass();
  
    // Parse the URL and make sure we can handle the schema.
    $uri = parse_url($url);
  
    if ($uri == FALSE) {
      $result->error = 'unable to parse URL';
      $result->code = -1001;
      return $result;
    }
  
    if (!isset($uri['scheme'])) {
      $result->error = 'missing schema';
      $result->code = -1002;
      return $result;
    }
  
    switch ($uri['scheme']) {
      case 'http':
      case 'feed':
        $port = isset($uri['port']) ? $uri['port'] : 80;
        $host = $uri['host'] . ($port != 80 ? ':'. $port : '');
        $fp = @fsockopen($uri['host'], $port, $errno, $errstr, 15);
        break;
      case 'https':
        // Note: Only works for PHP 4.3 compiled with OpenSSL.
        $port = isset($uri['port']) ? $uri['port'] : 443;
        $host = $uri['host'] . ($port != 443 ? ':'. $port : '');
        $fp = @fsockopen('ssl://'. $uri['host'], $port, $errno, $errstr, 20);
        break;
      default:
        $result->error = 'invalid schema '. $uri['scheme'];
        $result->code = -1003;
        return $result;
    }
  
    // Make sure the socket opened properly.
    if (!$fp) {
      // When a network error occurs, we use a negative number so it does not
      // clash with the HTTP status codes.
      $result->code = -$errno;
      $result->error = trim($errstr);
  
      // Mark that this request failed. This will trigger a check of the web
      // server's ability to make outgoing HTTP requests the next time that
      // requirements checking is performed.
      // @see system_requirements()
      variable_set('drupal_http_request_fails', TRUE);
  
      return $result;
    }
  
    // Construct the path to act on.
    $path = isset($uri['path']) ? $uri['path'] : '/';
    if (isset($uri['query'])) {
      $path .= '?'. $uri['query'];
    }

    // Prepare the data payload.
    $boundary = '---------------------------'. substr(md5(rand(0,32000)),0,10);
    $data_footer = "\r\n--$boundary--\r\n";

    $data_header = '';
    foreach ($params as $key => $value) {
      $data_header .="--$boundary\r\n";
      $data_header .= "Content-Disposition: form-data; name=\"".$key."\"\r\n";
      $data_header .= "\r\n".$value."\r\n";
      $data_header .="--$boundary\r\n";
    }
  
    // Add the file header to the post payload.
    $data_header .="--$boundary\r\n";
    $data_header .= "Content-Disposition: form-data; name=\"file\"; filename=\"". $file->filename() ."\"\r\n";
    $data_header .= "Content-Type: application/octet-stream;\r\n";
    $data_header .= "\r\n";

    // Calculate the content length.
    $content_length = strlen($data_header . $data_footer) + filesize($file->filepath());

    //file_get_contents($file->filepath()));
    
    // Create HTTP request.
    $defaults = array(
      // RFC 2616: "non-standard ports MUST, default ports MAY be included".
      // We don't add the port to prevent from breaking rewrite rules checking the
      // host that do not take into account the port number.
      'Host' => "Host: $host",
      'Content-type' => "Content-type: multipart/form-data, boundary=$boundary",
      'User-Agent' => 'User-Agent: NodeSquirrel Client/1.x (+http://www.nodesquirrel.com) (Drupal '. VERSION .'; Backup and Migrate 2.x)',
      'Content-Length' => 'Content-Length: '. $content_length
    );

    // If the server url has a user then attempt to use basic authentication
    if (isset($uri['user'])) {
      $defaults['Authorization'] = 'Authorization: Basic '. base64_encode($uri['user'] . (!empty($uri['pass']) ? ":". $uri['pass'] : ''));
    }

    $request = $method .' '. $path ." HTTP/1.0\r\n";
    $request .= implode("\r\n", $defaults);
    $request .= "\r\n\r\n";  
    $result->request = $request;

    // Write the headers and start of the headers
    fwrite($fp, $request);
    fwrite($fp, $data_header);

    // Copy the file 512k at a time to prevent memory issues.
    if ($fp_in = fopen($file->filepath(), 'rb')) {
      while (!feof($fp_in)) {
        fwrite($fp, fread($fp_in, 1024 * 512));
      }
      $success = TRUE;
    }
    @fclose($fp_in);

    // Finish the write.
    fwrite($fp, $data_footer);

    // Fetch response.
    $response = '';
    while (!feof($fp) && $chunk = fread($fp, 1024)) {
      $response .= $chunk;
    }
    fclose($fp);
  
    // Parse response.
    list($split, $result->data) = explode("\r\n\r\n", $response, 2);
    $split = preg_split("/\r\n|\n|\r/", $split);
  
    list($protocol, $code, $status_message) = explode(' ', trim(array_shift($split)), 3);
    $result->protocol = $protocol;
    $result->status_message = $status_message;
  
    $result->headers = array();
  
    // Parse headers.
    while ($line = trim(array_shift($split))) {
      list($header, $value) = explode(':', $line, 2);
      if (isset($result->headers[$header]) && $header == 'Set-Cookie') {
        // RFC 2109: the Set-Cookie response header comprises the token Set-
        // Cookie:, followed by a comma-separated list of one or more cookies.
        $result->headers[$header] .= ','. trim($value);
      }
      else {
        $result->headers[$header] = trim($value);
      }
    }
  
    $responses = array(
      100 => 'Continue', 101 => 'Switching Protocols',
      200 => 'OK', 201 => 'Created', 202 => 'Accepted', 203 => 'Non-Authoritative Information', 204 => 'No Content', 205 => 'Reset Content', 206 => 'Partial Content',
      300 => 'Multiple Choices', 301 => 'Moved Permanently', 302 => 'Found', 303 => 'See Other', 304 => 'Not Modified', 305 => 'Use Proxy', 307 => 'Temporary Redirect',
      400 => 'Bad Request', 401 => 'Unauthorized', 402 => 'Payment Required', 403 => 'Forbidden', 404 => 'Not Found', 405 => 'Method Not Allowed', 406 => 'Not Acceptable', 407 => 'Proxy Authentication Required', 408 => 'Request Time-out', 409 => 'Conflict', 410 => 'Gone', 411 => 'Length Required', 412 => 'Precondition Failed', 413 => 'Request Entity Too Large', 414 => 'Request-URI Too Large', 415 => 'Unsupported Media Type', 416 => 'Requested range not satisfiable', 417 => 'Expectation Failed',
      500 => 'Internal Server Error', 501 => 'Not Implemented', 502 => 'Bad Gateway', 503 => 'Service Unavailable', 504 => 'Gateway Time-out', 505 => 'HTTP Version not supported'
    );
    // RFC 2616 states that all unknown HTTP codes must be treated the same as the
    // base code in their class.
    if (!isset($responses[$code])) {
      $code = floor($code / 100) * 100;
    }
  
    switch ($code) {
      case 200: // OK
      case 304: // Not modified
        break;
      case 301: // Moved permanently
      case 302: // Moved temporarily
      case 307: // Moved temporarily
        $location = $result->headers['Location'];
  
        if ($retry) {
          $result = drupal_http_request($result->headers['Location'], $headers, $method, $data, --$retry);
          $result->redirect_code = $result->code;
        }
        $result->redirect_url = $location;
  
        break;
      default:
        $result->error = $status_message;
    }
  
    $result->code = $code;
    return $result;
  }
}

