<?php

/**
 * @file
 * Main help definition.
 */

function _security_review_help() {
  drupal_add_js(drupal_get_path('module', 'security_review') . '/security_review.js');
  $output = '';
  $output .= '<p>';
  $output .= t('You should take the security of your site very seriously.
    Fortunately, Drupal is fairly secure by default.
    The Security Review module automates many of the easy-to-make mistakes that render your site insecure, however it does not automatically make your site impenetrable.
    You should give care to what modules you install and how you configure your site and server.
    Be mindful of who visits your site and what features you expose for their use.');
  $output .= '</p>';
  $output .= '<p>';
  $output .= t('You can read more about securing your site in the <a href="!do">drupal.org handbooks</a> and on <a href="!cd">CrackingDrupal.com</a>.
    There are also additional modules you can install to secure or protect your site. Be aware though that the more modules you have running on your site the greater (usually) attack area you expose.',
    array('!do' => 'http://drupal.org/security/secure-configuration', '!cd' => 'http://crackingdrupal.com'));
  $output .= '</p>';
  $output .= '<p>' . l(t('Drupal.org Handbook: Introduction to security-related contrib modules'), 'http://drupal.org/node/382752') . '</p>';
  /*$output .= '<h3>' . t('Contrib modules for additional security and strength') . '</h3>';
   $output .= '<p>' . t('There are a wealth of modules on drupal.org.') . '</p>';
   $items[] = _security_review_help_ssl();
   $items[] = _security_review_help_spam();
   $output .= theme('item_list', $items);*/
  return $output;
}

function _security_review_help_ssl() {
  $description = t('The transfer of data between the visitor on your site and you Drupal installation can be secured through encryption.');
  $element = array(
    'problem' => t("Secure and private communication"),
    'type' => 'ssl',
    'description' => $description,
    'options' => array(
      array(
        'name' => 'Secure Pages',
        'href' => 'http://drupal.org/project/securepages',
      ),
    ),
  );
  return theme('security_review_help_options', array('element' => $element));
}

function _security_review_help_spam() {
  $element = array(
    'problem' => t("Spammers and spam content"),
    'type' => 'spam',
    'description' => t('Spammers use automated tools and systems to bombarge your site with unsollicited content. You can use modules to prevent the submission of such content.'),
    'options' => array(
      array(
        'name' => 'CAPTCHA',
        'href' => 'http://drupal.org/project/captcha',
      ),
    ),
  );
  return theme('security_review_help_options', array('element' => $element));
}

function theme_security_review_help_options($element) {
  $output .= '<div class="sec-rev-help-option">';
  $output .= l($element['problem'], 'admin/reports/security-review/help', array('fragment' => $element['type'], 'attributes' => array('class' => 'sec-rev-help-dyn')));
  $output .= '<div class="sec-rev-help-content">';
  $output .= '<p>' . $element['description'] . '</p>';
  foreach ($element['options'] as $option) {
    $items[] = l($option['name'], $option['href']);
  }
  $output .= theme('item_list', array('items' => $items));
  $output .= '</div>';
  $output .= '</div>';
  return $output;
}

function security_review_check_file_perms_help($check = NULL, $skipped_message = NULL) {
  $element['title'] =  t("Web server file system permissions");
  $element['descriptions'][] = t("It is dangerous to allow the web server to write to files inside the document root of your server. Doing so could allow Drupal to write files that could then be executed. An attacker might use such a vulnerability to take control of your site. An exception is the Drupal files, private files, and temporary directories which Drupal needs permission to write to in order to provide features like file attachments.");
  $element['descriptions'][] = t("In addition to inspecting existing directories, this test attempts to create and write to your file system. Look in your security_review module directory on the server for files named file_write_test.YYYYMMDDHHMMSS and for a file called IGNOREME.txt which gets a timestamp appended to it if it is writeable.</p>");
  $element['descriptions'][] = t("<a href='!link'>Read more about file system permissions in the handbooks.</a>", array('!link' => url('http://drupal.org/node/244924')));

  if ($skipped_message) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('The following files and directories appear to be writeable by your web server. In most cases you can fix this by simply altering the file permissions or ownership. If you have command-line access to your host try running "chmod 644 [file path]" where [file path] is one of the following paths (relative to your webroot). For more information consult the <a href="!link">Drupal.org handbooks on file permissions</a>.', array('!link' => url('http://drupal.org/node/244924')));
    foreach ($check['value'] as $file) {
      $element['findings']['items'][] = array(
        'safe' => check_plain($file),
        'raw' => $file,
      );
    }
  }
  return $element;
}

function security_review_check_input_formats_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Allowed HTML tags in text formats');
  $element['descriptions'][] = t("Certain HTML tags can allow an attacker to take control of your site. Drupal's input format system makes use of a set filters to run on incoming text. The 'HTML Filter' strips out harmful tags and Javascript events and should be used on all formats accessible by untrusted users.");
  $element['descriptions'][] = t("<a href='!link'>Read more about Drupal's input formats in the handbooks.</a>", array('!link' => url('http://drupal.org/node/224921')));

  if ($skipped_message) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    if (!empty($check['value']['tags'])) {
      $element['findings']['descriptions'][] = t('<a href="!link">Review your text formats.</a>', array('!link' => url('admin/config/content/formats')));
      $element['findings']['descriptions'][] = t('It is recommended you remove the following tags from roles accessible by untrusted users.');
      foreach ($check['value']['tags'] as $tag) {
        $element['findings']['items'][] = array(
          'safe' => $tag, // Tag doesn't need filtering cause it's not user-defined.
          'raw' => $tag,
        );
      }
    }
    elseif (!empty($check['value']['formats'])) {
      $element['findings']['descriptions'][] = t('The following formats are usable by untrusted roles and do not filter or escape allowed HTML tags.');
      foreach ($check['value']['formats'] as $id => $format) {
        $element['findings']['items'][] = array(
          'html' => l($format->name, 'admin/config/content/formats/' . $format->format),
          'safe' => check_plain($format->name),
          'raw' => $format->name,
        );
      }
    }
  }
  return $element;
}

function security_review_check_php_filter_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('PHP Input Format');
  $element['descriptions'][] = t("Drupal's PHP Text Format allows for the interpretation and execution of PHP code via user-supplied input. Because this input runs in the context of Drupal itself it has access to everything Drupal does.");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    if (!empty($check['value']['formats'])) {
      $element['findings']['descriptions'][] = t('The following formats are usable by untrusted roles and allow use of the PHP evaluator. You should edit the format to remove PHP use.');
      foreach ($check['value']['formats'] as $id => $format) {
        $element['findings']['items'][] = array(
          'html' => l($format->name, 'admin/config/content/formats/' . $format->format),
          'safe' => check_plain($format->name),
          'raw' => $format->name,
        );
      }
    }
  }
  return $element;
}

function security_review_check_error_reporting_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Error reporting');
  $element['descriptions'][] = t('As a form of hardening your site you should avoid information disclosure. Drupal by default prints errors to the screen and writes them to the log. Error messages disclose the full path to the file where the error occured.');

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('You have error reporting set to both the screen and the log.');
    $element['findings']['descriptions'][] = t('<a href="!link">Alter error reporting settings.</a>', array('!link' => url('admin/config/development/logging')));
  }
  return $element;
}

function security_review_check_private_files_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Private files');
  $element['descriptions'][] = t("If you have Drupal's private files feature enabled you should move the files directory outside of the web server's document root. Drupal will secure access to files that it renders the link to, but if a user knows the actual system path they can circumvent Drupal's private files feature. You can protect against this by specifying a files directory outside of the webserver root.");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('Your files directory is not outside of the server root.');
    $element['findings']['descriptions'][] = t('<a href="!link">Edit the files directory path.</a>', array('!link' => url('admin/config/media/file-system')));
    $element['findings']['items'][] = array(
      'safe' => t('Private files directory: @value', array('@value' => $check['value'])),
      'raw' => 'Directory: ' . $check['value'],
    );
  }
  return $element;
}

function security_review_check_query_errors_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Abundant query errors from the same IP');
  $element['descriptions'][] = t("Database errors triggered from the same IP may be an artifact of a malicious user attempting to probe the system for weaknesses like SQL injection or information disclosure.");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('The following IPs were observed with an abundance of query errors.');
    foreach ($check['value'] as $ip) {
      $element['findings']['items'][] = array(
        'safe' => check_plain($ip),
        'raw' => $ip,
      );
    }
  }
  return $element;
}

function security_review_check_failed_logins_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Abundant failed logins from the same IP');
  $element['descriptions'][] = t("Failed login attempts from the same IP may be an artifact of a malicous user attempting to brute-force their way onto your site as an authenticated user to carry out nefarious deeds. ");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('The following IPs were observed with an abundanced of failed login attempts.');
    foreach ($check['value'] as $ip) {
      $element['findings']['items'][] = array(
        'safe' => check_plain($ip),
        'raw' => $ip,
      );
    }
  }
  return $element;
}

function security_review_check_admin_permissions_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Admin and trusted Drupal permissions');
  $element['descriptions'][] = t("Drupal's permission system is extensive and allows for varying degrees of control. Certain permissions would allow a user total control, or the ability to escalate their control, over your site and should only be granted to trusted users.");
  $element['descriptions'][] = t('<a href="!link">Read more about trusted vs. untrusted roles and permissions on DrupalScout.com.</a>', array('!link' => url('http://drupalscout.com/knowledge-base/importance-user-roles-and-permissions-site-security')));

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $roles = user_roles();
    $element['findings']['descriptions'][] = t('You have granted untrusted roles the following permissions that you should revoke.');
    foreach ($check['value'] as $rid => $permissions) {
      $permissions = implode(', ', $permissions);
      $html = t('<a href="!link">@name</a> has %permissions', array('!link' => url('admin/people/permissions/' . $rid), '@name' => $roles[$rid], '%permissions' => $permissions));
      $safe = t('@name has %permissions', array('@name' => $roles[$rid], $permissions));
      $element['findings']['items'][] = array(
        'html' => $html,
        'safe' => $safe,
        'raw' => $roles[$rid] . ':' . $permissions,
      );
    }
  }
  return $element;
}

function security_review_check_field_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Dangerous tags in content');
  $element['descriptions'][] = t('Script and PHP code in content does not align with Drupal best practices and may be a vulnerability if an untrusted user is allowed to edit such content. It is recommended you remove such contents.');

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('The following items potentially have dangerous tags.  ');
    foreach ($check['value'] as $entity_type => $value) {
      $ids = array_keys($value);
      $entity_info = entity_get_info($entity_type);
      $id = $entity_info['entity keys']['id'];
      $label = isset($entity_info['entity keys']['label']) ? $entity_info['entity keys']['label'] : $id;
      $uri_callback = FALSE;
      if (isset($entity_info['uri callback'])) {
        $uri_callback = $entity_info['uri callback'];
      }
      // There is no access checking. We state that the use of this module should be granted to trusted users only.
      $entities = entity_load($entity_type, $ids);
      foreach ($entities as $entity) {
        $uri = '#';
        if ($uri_callback && function_exists($uri_callback)) {
          $uri = $uri_callback($entity);
          $uri = url($uri['path'] . '/edit'); // @todo can this assumption be made?
        }
        $html = t('@description found in @field field of <a href="!link">@title</a>', array('@field' => $value[$entity->{$id}]['field'], '@description' => $value[$entity->{$id}]['type'], '!link' => $uri, '@title' => $entity->{$label}));
        $element['findings']['items'][] = array(
          'html' => $html,
          'safe' => t('@description in @field field of !url', array('@field' => $value[$entity->{$id}]['field'], '@description' => $value[$entity->{$id}], '!url' => $uri)),
          'raw' => $value[$entity->{$id}] . ':' . $uri,
        );
      }
    }
    //$element['findings']['pager'] = theme('pager', array('tags' => NULL));
  }

  return $element;
}

function security_review_check_upload_extensions_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Allowed upload extensions');
  $element['descriptions'][] = t('File and image fields allow for uploaded files. Some extensions are considered dangerous because the files can be evaluated and then executued in the browser. A malicious user could use this opening to gain control of your site. Review <a href="@fields_report">all fields on your site</a>.', array('@fields_report' => url('admin/reports/fields')));

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('The following extensions are considered unsafe and should be removed or limited from use. Or, be sure you are not granting untrusted users the ability to upload files.');
    foreach ($check['value'] as $field_name => $extensions) {
      foreach ($extensions as $bundle => $extension) {
        $element['findings']['items'][] = array(
          'raw' => $extension,
          'safe' => check_plain($extension),
          'html' => l(t('Review @type in @name field on @bundle', array('@type' => $extension, '@name' => $field_name, '@bundle' => $bundle)), 'admin/structure/types/manage/' . $bundle . '/fields/' . $field_name),
        );
      }
    }
  }
  return $element;
}

function security_review_check_views_access_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Views access');
  $element['descriptions'][] = t("Views can check if the user is allowed access to the content. It is recommended that all Views implement some amount of access control, at a minimum checking for the permission 'access content'.");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('The following View displays do not check access.');
    foreach ($check['value'] as $view => $displays) {
      $url = 'admin/structure/views/view/' . $view . '/edit/';
      foreach ($displays as $display) {
        $item = $view . ': ' . $display;
        $element['findings']['items'][] = array(
          'html' => l($item, $url . $display),
          'safe' => $item, // View names are safe.
          'raw' => $item,
        );
      }
    }
  }

  return $element;
}

function security_review_check_name_passwords_help($check = NULL, $skipped_message = NULL) {
  $element['title'] = t('Username as password');
  $element['descriptions'][] = t("Users with elevated access on the site (trusted users) who have a their account password the same as their username. It is recommended you enforce a password strength policy to avoid an attacker easily gaining access to your site.");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('The following users have extremely weak passwords. The links go to the edit page.');
    foreach ($check['value'] as $uid => $name) {
      $element['findings']['items'][] = array(
        'html' => l($name, 'user/' . $uid . '/edit'),
        'safe' => check_plain($name),
        'raw' => $name,
      );
    }
    $element['findings']['pager'] = theme('pager', NULL, 20);
  }

  return $element;
}

function security_review_check_executable_php_help($check = NULL, $skipped_message = NULL) {
  $element = array();
  $element['title'] = t('Executable PHP in files directory');
  $element['descriptions'][] = t("The Drupal files directory is for user-uploaded files and by default provides some protection against a malicious user executing arbitrary PHP code against your site.");
  $element['descriptions'][] = t('Read more about the <a href="!link">risk of PHP code execution on Drupal.org</a>.', array('!link' => 'https://drupal.org/node/615888'));

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  if (!empty($check['value'])) {
    foreach ($check['value'] as $label) {
      switch ($label) {
        case 'executable_php':
          $element['findings']['descriptions'][] = t('Security Review was able to execute a PHP file written to your files directory.');
          break;
        case 'missing_htaccess':
          $directory = variable_get('file_public_path', 'sites/default/files');
          $element['findings']['descriptions'][] = t("The .htaccess file is missing from the files directory at !path", array('!path' => $directory));
          $element['findings']['descriptions'][] = t("Note, if you are using a webserver other than Apache you should consult your server's documentation on how to limit the execution of PHP scripts in this directory.");
          break;
        case 'incorrect_htaccess':
            $element['findings']['descriptions'][] = t("The .htaccess file exists but does not contain the correct content. It is possible it's been maliciously altered.");
            break;
        case 'outdated_core':
            $element['findings']['descriptions'][] = t("You are running a out-of-date Drupal installation that is vulnerable to arbitrary code execution via weak htaccess protection. Upgrade to the latest version of Drupal. See <a href='https://drupal.org/SA-CORE-2013-003'>SA-CORE-2013-003 - Drupal core - Multiple vulnerabilities</a> for the full report.");
            break;
        case 'writable_htaccess':
          $element['findings']['descriptions'][] = t("The .htaccess file is writeable which poses a risk should a malious user find a way to execute PHP code they could alter the htaccess file to allow further PHP code execution.");
          break;
      }
    }
  }

  return $element;
}

function security_review_check_base_url_help($check = NULL, $skipped_message = NULL) {
  global $base_url;
  $element = array();
  $element['title'] = t('Drupal base URL');
  $element['descriptions'][] = t("Setting Drupal's \$base_url in settings.php can help protect against attackers manipulating links to your site. For example, an attacker could exploit a missing \$base_url setting to carry out a phishing attack that may lead to the theft of your site's private user data.");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t('Your site is available at the following URL: !url.', array('!url' => $base_url));
    $element['findings']['descriptions'][] = t("If your site should only be available at that URL it is recommended that you set it as the \$base_url variable in the settings.php file at !file", array('!file' => DRUPAL_ROOT . '/' . conf_path() . '/settings.php'));
    $element['findings']['descriptions'][] = t("Or, if you are using Drupal's multi-site functionality then you should set the \$base_url variable for the appropriate settings.php for your site.");
  }

  return $element;
}

function security_review_check_temporary_files_help($check = NULL, $skipped_message = NULL) {
  $element = array();
  $element['title'] = t('Sensitive temporary files');
  $element['descriptions'][] = t("Some file editors create temporary copies of a file that can be left on the file system. A copy of a sensitive file like Drupal's settings.php may be readable by a malicious user who could use that information to further attack a site.");

  if (!empty($skipped_message)) {
    $element['findings']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $element['findings']['descriptions'][] = t("The following are extraneous files in your Drupal installation that can probably be removed. You should confirm you have saved any of your work in the original files prior to removing these.");
    foreach ($check['value'] as $path) {
      $element['findings']['items'][] = array(
        'safe' => check_plain($path),
        'raw' => $path,
      );
    }
  }

  return $element;
}
