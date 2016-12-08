<?php

/**
 * @file
 * CAS module settings UI.
 */

/**
 * Provides settings pages.
 */
function cas_admin_settings() {

  $form['library'] = array(
    '#type' => 'fieldset',
    '#title' => t('Library (phpCAS)'),
    '#collapsible' => TRUE,
  );
  if (module_exists('libraries')) {
    // If Libraries API is enabled, print an information item.
    $form['library']['cas_library_dir'] = array(
      '#type' => 'item',
      '#title' => t('Library directory'),
      '#value' => t('Using <a href="@url">Libraries API</a>.', array('@url' => 'http://drupal.org/project/libraries')),
      '#description' => t('Please ensure phpCAS is installed in a location compatible with Libraries API. For example, install phpCAS so that <em>sites/all/libraries/CAS/CAS.php</em> exists. See README.txt for more information.'),
      '#after_build' => array('cas_library_version_check'),
    );
  }
  else {
    // If Libraries API is not installed, display path settings.
    $form['library']['cas_library_dir'] = array(
      '#type' => 'textfield',
      '#title' => t('Library directory'),
      '#default_value' => variable_get('cas_library_dir', 'CAS'),
      '#description' => t('Specify the path to the directory the CAS.php file resides in. Leave blank to load cas from your phpinclude path.'),
      '#after_build' => array('cas_library_version_check'),
    );
  }


  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('CAS Server'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['server']['cas_version'] = array(
    '#type' => 'radios',
    '#title' => t('Version'),
    '#default_value' => variable_get('cas_version', '3.0'),
    '#options' => array(
      '1.0' => '1.0',
      '2.0' => t('2.0'),
      '3.0' => t('3.0 or higher (requires phpCAS >= 1.3.3)'),
      'S1' => t('SAML Version 1.1'),
    ),
  );

  $form['server']['cas_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Hostname'),
    '#default_value' => variable_get('cas_server', ''),
    '#size' => 30,
    // Hostnames can be 255 characters long.
    '#maxlength' => 255,
    '#description' => t('Hostname or IP Address of the CAS server.'),
  );

  $form['server']['cas_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Port'),
    '#default_value' => variable_get('cas_port', '443'),
    '#size' => 5,
    // The maximum port number is 65536, 5 digits.
    '#maxlength' => 5,
    '#description' => t('443 is the standard SSL port. 8443 is the standard non-root port for Tomcat.'),
  );

  $form['server']['cas_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('URI'),
    '#default_value' => variable_get('cas_uri', ''),
    '#size' => 30,
    '#description' => t('If CAS is not at the root of the host, include a URI (e.g., /cas).'),
  );

  $form['server']['cas_cert'] = array(
    '#type' => 'textfield',
    '#title' => t('Certificate Authority PEM Certificate'),
    '#default_value' => variable_get('cas_cert', ''),
    '#maxlength' => 255,
    '#description' => t('The PEM certificate of the Certificate Authority that issued the certificate of the CAS server. If omitted, the certificate authority will not be verified.'),
  );

  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login form'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['login']['cas_login_form'] = array(
    '#type' => 'radios',
    '#title' => t('Add CAS link to login forms'),
    '#default_value' => variable_get('cas_login_form', CAS_NO_LINK),
    '#options' => array(
      CAS_NO_LINK => t('Do not add link to login forms'),
      CAS_ADD_LINK => t('Add link to login forms'),
      CAS_MAKE_DEFAULT => t('Make CAS login default on login forms'),
      CAS_REDIRECT => t('Redirect the login form to CAS'),
    ),
  );

  $form['login']['cas_login_invite'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS Login invitation'),
    '#default_value' => variable_get('cas_login_invite', CAS_LOGIN_INVITE_DEFAULT),
    '#description' => t('Message users will see to invite them to log in with CAS credentials.'),
  );

  $form['login']['cas_login_drupal_invite'] = array(
    '#type' => 'textfield',
    '#title' => t('Drupal login invitation'),
    '#default_value' => variable_get('cas_login_drupal_invite', CAS_LOGIN_DRUPAL_INVITE_DEFAULT),
    '#description' => t('Message users will see to invite them to log in with Drupal credentials.'),
  );

  $form['login']['cas_login_redir_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirection notification message'),
    '#default_value' => variable_get('cas_login_redir_message', CAS_LOGIN_REDIR_MESSAGE),
    '#description' => t('Message users see at the top of the CAS login form to warn them that they are being redirected to the CAS server.'),
  );

  // Setting for message displayed to user upon successful login
  $form['login']['cas_login_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Successful login message'),
    '#default_value' => variable_get('cas_login_message', 'Logged in via CAS as %cas_username.'),
    '#description' => t('Message displayed when a user logs in successfully. <em>%cas_username</em> will be replaced with the user\'s name.'),
  );


  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('User accounts'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['account']['cas_user_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create Drupal accounts'),
    '#default_value' => variable_get('cas_user_register', 1),
    '#description' => t('Whether a Drupal account is automatically created the first time a CAS user logs into the site. If disabled, you will need to pre-register Drupal accounts for authorized users.'),
  );

  $form['account']['cas_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#field_prefix' => t('username@'),
    '#default_value' => variable_get('cas_domain', ''),
    '#size' => 30,
    // Hostnames can be 255 characters long.
    '#maxlength' => 255,
    '#description' => t("If provided, automatically generate each new user's e-mail address. If omitted, the e-mail field will not be populated. Other modules may be used to populate the e-mail field from CAS attributes or LDAP servers."),
  );

  // Taken from Drupal's User module.
  $roles = array_map('check_plain', user_roles(TRUE));
  $checkbox_authenticated = array(
    '#type' => 'checkbox',
    '#title' => $roles[DRUPAL_AUTHENTICATED_RID],
    '#default_value' => TRUE,
    '#disabled' => TRUE,
  );
  unset($roles[DRUPAL_AUTHENTICATED_RID]);
  $form['account']['cas_auto_assigned_role'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#description' => t('The selected roles will be automatically assigned to each CAS user on login. Use this to automatically give CAS users additional privileges or to identify CAS users to other modules.'),
    '#default_value' => variable_get('cas_auto_assigned_role', array()),
    '#options' => $roles,
    '#access' => user_access('administer permissions'),
    DRUPAL_AUTHENTICATED_RID => $checkbox_authenticated,
  );

  $form['account']['cas_hide_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change email address'),
    '#default_value' => variable_get('cas_hide_email', 0),
    '#description' => t('Hide email address field on the edit user form.'),
  );

  $form['account']['cas_hide_password'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change password'),
    '#default_value' => variable_get('cas_hide_password', 0),
    '#description' => t('Hide password field on the edit user form. This also removes the requirement to enter your current password before changing your e-mail address.'),
  );

  if (module_exists('persistent_login')) {
    $form['account']['cas_allow_rememberme'] = array(
      '#type' => 'checkbox',
      '#title' => t('Users can stay logged in between sessions'),
      '#default_value' => variable_get('cas_allow_rememberme', 0),
      '#description' => t('If Persistent Login is enabled, users can choose to stay logged in between browser sessions'),
      );
  }

  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirection'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['pages']['cas_check_frequency'] = array(
    '#type' => 'radios',
    '#title' => t('Check with the CAS server to see if the user is already logged in?'),
    '#default_value' => variable_get('cas_check_frequency', CAS_CHECK_NEVER),
    '#options' => array(
      CAS_CHECK_NEVER => 'Never',
      CAS_CHECK_ONCE => 'Once per browser session',
      CAS_CHECK_ALWAYS => 'Always (every page load)',
    ),
    '#description' => t('This implements the') . ' <a href="https://wiki.jasig.org/display/CAS/gateway">Gateway feature</a> ' . t('of the CAS Protocol.') . ' <strong>WARNING:</strong> ' . t('Enabling it at all will') . ' <em>' . t('completely disable page caching') . '</em>' . t(', and will prevent users from logging out locally unless also logged out of CAS. Setting it to "Always" will perform redirects on EVERY page load unless the user is already logged in, and is not recommended in most circumstances.'),
  );

  $form['pages']['cas_access'] = array(
    '#type' => 'radios',
    '#title' => t('Require CAS login for'),
    '#default_value' => variable_get('cas_access', 0),
    '#options' => array(t('specific pages'), t('all pages except specific pages')),
  );

  $form['pages']['cas_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Specific pages'),
    '#default_value' => variable_get('cas_pages', ''),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );

  $form['pages']['cas_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded Pages'),
    '#default_value' => variable_get('cas_exclude', CAS_EXCLUDE),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Indicates which pages will be ignored (no login checks). Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );


  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login/Logout Destinations'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Settings for redirection upon first login
  $form['misc']['cas_first_login_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial login destination'),
    '#default_value' => variable_get('cas_first_login_destination', ''),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Drupal path or URL. Enter a destination if you want the user to be redirected to this page on their first CAS login. An example path is <em>blog</em> for the blog page, <em>&lt;front&gt;</em> for the front page, or <em>user</em> for the user's page."),
  );

  // Setting for page to return to after a CAS logout
  $form['misc']['cas_logout_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout destination'),
    '#default_value' => variable_get('cas_logout_destination', ''),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Drupal path or URL. Enter a destination if you want a user to be directed to this page after logging out of CAS, or leave blank to direct users back to the previous page. An example path is <em>blog</em> for the blog page or <em>&lt;front&gt;</em> for the front page."),
  );

  $form['misc']['cas_changePasswordURL'] = array(
    '#type' => 'textfield',
    '#title' => t('Change password URL'),
    '#default_value' => variable_get('cas_changePasswordURL', ''),
    '#maxlength' => 255,
    '#description' => t('The URL users should use for changing their password.  Leave blank to use the standard Drupal page.'),
  );

  $form['misc']['cas_registerURL'] = array(
    '#type' => 'textfield',
    '#title' => t('Registration URL'),
    '#default_value' => variable_get('cas_registerURL', ''),
    '#maxlength' => 255,
    '#description' => t('The URL users should use for changing registering.  Leave blank to use the standard Drupal page.'),
  );


  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Miscellaneous & Experimental Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['cas_proxy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Initialize CAS as proxy'),
    '#default_value' => variable_get('cas_proxy', 0),
    '#description' => t('Initialize phpCAS as a proxy rather than a client. The proxy ticket returned by the CAS server allows access to external services as the CAS user.')
  );

  $form['advanced']['cas_proxy_settings'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
        'input[name="cas_proxy"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['advanced']['cas_proxy_settings']['cas_pgtformat'] = array(
    '#type' => 'radios',
    '#title' => t('CAS PGT storage file format'),
    '#default_value' => variable_get('cas_pgtformat', 'plain'),
    '#options' => array('plain' => t('Plain Text'), 'xml' => t('XML')),
    '#after_build' => array('cas_pgtformat_version_check'),
  );

  $form['advanced']['cas_proxy_settings']['cas_pgtpath'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS PGT storage path'),
    '#default_value' => variable_get('cas_pgtpath', ''),
    '#maxlength' => 255,
    '#description' => t("Only needed if 'Use CAS proxy initializer' is configured. Leave empty for default."),
  );

  $form['advanced']['cas_proxy_list'] = array(
    '#type' => 'textarea',
    '#title' => t('CAS proxy list'),
    '#description' => t("If CAS client could be proxied, indicate each proxy server absolute url per line. If not provided, phpCAS will exclude by default all tickets provided by proxy. Each proxy server url could be a plain url or a regular expression. IMPORTANT : regular expression delimiter must be a slash. For example : https://proxy.example.com/ AND/OR regular expression : /^https:\/\/app[0-9]\.example\.com\/rest\//."),
    '#default_value' => variable_get('cas_proxy_list', ''),
    '#after_build' => array('cas_proxy_list_version_check'),
  );

  $form['advanced']['cas_debugfile'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS debugging output file'),
    '#default_value' => variable_get('cas_debugfile', ''),
    '#maxlength' => 255,
    '#description' => "<p>" . t("A file system path and filename where the CAS debug log will be written. May be either a full path or a path relative to the Drupal installation root. The directory and file must be writable by Drupal.") . "</p> <p>" . t("Leave blank to disable logging.") . "</p> <p><strong>" . t("Debugging should not be enabled on production systems.") . "</strong></p>",
  );

  return system_settings_form($form);
}

/**
 * Checks that the library is installed in the location specified by loading the
 * class and extracting the version.
 *
 * @param $element
 *   The form element containing the "library" fieldset.
 * @param $form_state
 *   An array containing the form's state information.
 *
 * @return
 *   The modified form element containing the "library" fieldset.
 */
function cas_library_version_check($element, &$form_state) {
  $path = module_exists('libraries') ? NULL : $element['#value'];
  // Suppress errors if phpCAS cannot be loaded.
  if ($version = @cas_phpcas_load($path)) {
    $element['#suffix'] = '<div class="ok messages">' . t('phpCAS version %version successfully loaded.', array('%version' => $version)) . '</div>';
  }
  else {
    $element['#suffix'] = '<div class="error messages">' . t('The phpCAS library was not found or could not be loaded.') . '</div>';
  }
  return $element;
}

/**
 * Proxy chain object only exists with phpCAS version >= 1.3. As phpCAS CAS.php
 * is include only after building element 'cas_library_dir', we must check it after it.
 */
function cas_proxy_list_version_check($element, &$form_state) {
  if (!defined('PHPCAS_VERSION') || version_compare(PHPCAS_VERSION, '1.3', '<')) {
    $element['#access'] = FALSE;
  }
  return $element;
}

/**
 * Since 1.3, pgt format isn't supported and default to plain.
 */
function cas_pgtformat_version_check($element, &$form_state) {
  if (!defined('PHPCAS_VERSION') || version_compare(PHPCAS_VERSION, '1.3', '>')) {
    $element['#access'] = FALSE;
  }
  return $element;
}
