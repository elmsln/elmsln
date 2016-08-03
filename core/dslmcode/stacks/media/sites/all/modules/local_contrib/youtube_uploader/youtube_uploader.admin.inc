<?php
/**
 * @file
 * Administrative page callbacks for the youtube_upload module.
 */

/**
 * General configuration form for youtube (account info + youtube settings).
 */
function youtube_uploader_account_settings_form($form, $form_state) {
  include_once DRUPAL_ROOT . '/includes/locale.inc';

  // Test if we get the google API Library client.
  $ytapi = new youtubeUploaderYtapi();
  if (!$ytapi->mtestGoogleLib()) {
    $form['lib_error']['#markup'] = t('Google Libraries not found.<br />Use drush to download them <em>drush ytu-libraries</em>
        <br /> then go to the library folder google-api-php-client and run <em>composer install</em> 
        <br />so the path <em>libraries/google-api-php-client/vendor/autoload.php</em> is available
        <br /> or check the !status for the manual procedure, section Google API and Google CORS.', array(
          '!status' => l(t('Status report'), 'admin/reports/status'),
      ));
    return $form;
  }

  $token = variable_get('youtube_uploader_token', array());

  // Display the authorization link.
  if (empty($token['refresh_token']) && variable_get('youtube_uploader_app_name', '') != '') {
    // Test the connection to google.
    $ytapi = new youtubeUploaderYtapi();
    $res = $ytapi->getAuthUrl();
    drupal_set_message(t('You need to allow your application by following !link_auth', array('!link_auth' => l(t('this link'), $res))), 'warning', FALSE);
  }
  elseif (!empty($token['refresh_token'])) {
    drupal_set_message('Token acquired from Google', 'status', FALSE);
  }

  $form['google_app'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Google Application'),
  );
  $form['google_app']['youtube_uploader_app_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Application name'),
    '#default_value' => variable_get('youtube_uploader_app_name', ''),
    '#required' => TRUE,
  );
  $form['google_app']['youtube_uploader_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => variable_get('youtube_uploader_client_id', ''),
    '#required' => TRUE,
    '#description' => '<em>xxx..apps.googleusercontent.com</em><br />'
  );
  $protocol = (isset($_SERVER['HTTPS'])) ? 'https' : 'http';
  $form['google_app']['youtube_uploader_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#description' => t('Get credentials keys on !here <br />Next in "APIs & auth" -> "Credentials" -> "OAuth". Click "Create new Client ID" and then under "Application Type" select "Web Application".<br />For the redirect uri use !protocol :// !server_name /youtube_uploader/oauth2callback',
      array(
        '!here' => l(t('https://console.developers.google.com'), 'https://console.developers.google.com/project'),
        '!protocol' => $protocol,
        '!server_name' => $_SERVER['SERVER_NAME'])),
    '#default_value' => variable_get('youtube_uploader_client_secret', ''),
    '#required' => TRUE,
  );
  $country = _youtube_uploader_get_country();
  $countries = country_get_list();
  $form['google_app']['youtube_uploader_app_country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#description' => t('The country is required to get video category list. If you change this setting, make sure the default category is still available after save (in "Youtube Settings" section here below)'),
    '#options' => $countries,
    '#default_value' => $country,
    '#required' => TRUE,
  );
  
  $form['youtube_uploader_autotitle'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use node title as video title'),
      '#description' => t('Synchronize the title from the node'),
      '#default_value' => variable_get('youtube_uploader_autotitle', FALSE),
  );

  $form['youtube_settings'] = youtube_uploader_get_settings_form();

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save configuration'),
  );

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function youtube_uploader_account_settings_form_submit($form, &$form_state) {

  $vals = $form_state['values'];

  // If account has changed, the autorisation should be done again.
  if (variable_get('youtube_uploader_app_name', '') != $vals['youtube_uploader_app_name'] ||
      variable_get('youtube_uploader_client_secret', '') != $vals['youtube_uploader_client_secret'] ||
      variable_get('youtube_uploader_client_id', '') != $vals['youtube_uploader_client_id']
      ) {
    variable_del('youtube_uploader_token');
  }
  
  form_state_values_clean($form_state);

  // Populate variables.
  foreach ($form_state['values'] as $key => $val) {
    // Convert settings to variables.
    variable_set($key, $val);
  }

}
