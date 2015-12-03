<?php

/**
 * @file
 * Youtube uploader Zend Gdata implementation
 */

class YoutubeUploaderYtapi {

  protected $yt;
  protected $client;

  /**
   * Set library path.
   */
  public function __construct() {
    $this->includeGoogleLib();
  }

  /**
   * Test if Google API library is available.
   */
  public function mtestGoogleLib() {
    if (!$this->includeGoogleLib()) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Set Google API library path.
   */
  protected function includeGoogleLib() {

    if (file_exists(DRUPAL_ROOT . "/sites/all/libraries/google-api-php-client/src/Google/autoload.php")) {
      $path = DRUPAL_ROOT . "/sites/all/libraries";
    }
    elseif (file_exists(DRUPAL_ROOT . "/sites/" . $_SERVER['SERVER_NAME'] . "/libraries/google-api-php-client/src/Google/autoload.php")) {
      $path = DRUPAL_ROOT . "/sites/" . $_SERVER['SERVER_NAME'] . "/libraries";
    }
    elseif (file_exists('profiles/' . drupal_get_profile() . '/libraries/google-api-php-client/src/Google/autoload.php')) {
      $path = 'profiles/' . drupal_get_profile() . '/libraries';
    }
    else {
      return FALSE;
    }

    set_include_path(get_include_path() . PATH_SEPARATOR . $path);

    require_once $path . '/google-api-php-client/src/Google/autoload.php';

    return TRUE;
  }

  /**
   * Get a authentication url.
   */
  public function getAuthUrl($credentials = array()) {
    $this->authenticate();
    $state = mt_rand();
    $this->client->setState($state);
    $auth_url = $this->client->createAuthUrl();
    return $auth_url;
  }

  /**
   * Get a token based on returned code.
   */
  public function getTokenFromCode($code) {
    try {
      $this->authenticate();
      $this->client->authenticate($code);
      variable_set('youtube_uploader_token', drupal_json_decode($this->client->getAccessToken()));
    }
    catch (Google_ServiceException $e) {
      drupal_set_message(t('A service error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage()))), 'error');
    }
    catch (Google_Exception $e) {
      drupal_set_message(t('A client error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage()))), 'error');
    }
  }

  /**
   * Authenticate to google with account settings.
   */
  public function authenticate($credentials = array()) {

    $error = '';
    try {
      if (!isset($this->client)) {
        $app_name = !empty($credentials['app_name']) ? $credentials['app_name'] : variable_get('youtube_uploader_app_name', '');
        $client_secret = !empty($credentials['client_secret']) ? $credentials['client_secret'] : variable_get('youtube_uploader_client_secret', '');
        $client_id = !empty($credentials['client_id']) ? $credentials['client_id'] : variable_get('youtube_uploader_client_id', '');

        // Authenticate to Google API.
        $client = new Google_Client();
        $client->setClientId($client_id);
        $client->setClientSecret($client_secret);
        $client->setScopes('https://www.googleapis.com/auth/youtube');
        $client->setRedirectUri($GLOBALS['base_url'] . '/youtube_uploader/oauth2callback');
        $client->setApplicationName($app_name);
        $client->setAccessType('offline');
        $client->setApprovalPrompt('force');

        $this->yt = new Google_Service_YouTube($client);
        $this->client = $client;
      }
    }
    catch (Google_ServiceException $e) {
      $error = t('A service error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage())));
    }
    catch (Google_Exception $e) {
      $error = t('A client error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage())));
    }
    return array('error' => $error);
  }

  /**
   * Get a fresh, valid token.
   */
  public function getFreshToken() {

    $token = variable_get('youtube_uploader_token', array());

    if (empty($token['refresh_token'])) {
      return array('error' => t('no refresh token'));
    }

    $error = '';
    try {
      $this->authenticate();
      $this->client->setAccessToken(drupal_json_encode($token));

      // Check to see if our access token has expired.
      // If so, get a new one and save it to file for future use.
      if ($this->client->isAccessTokenExpired()) {
        $new_token = json_decode($this->client->getAccessToken());
        $this->client->refreshToken($new_token->refresh_token);
        $token = drupal_json_decode($this->client->getAccessToken());
        variable_set('youtube_uploader_token', $token);
      }
    }
    catch (Google_ServiceException $e) {
      $error = t('A service error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage())));
    }
    catch (Google_Exception $e) {
      $error = t('A client error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage())));
    }
    return array('token' => $token['access_token'], 'error' => $error);
  }

  /**
   * Get default thumb and actual title for a video.
   */
  public function getTitleThumbs($video_id) {

    $this->getFreshToken();
    $list_response = $this->yt->videos->listVideos("snippet",
      array('id' => $video_id));

    if (empty($list_response)) {
      return array('error' => t('Video %vid not found', array('%vid' => $video_id)));
    }
    $video = $list_response[0]['snippet'];
    return array('title' => $video['title'], 'default_thumb' => $video['thumbnails']['high']['url']);
  }

  /**
   * Get categories.
   */
  public function getCategories() {

    $cat = array();
    $this->getFreshToken();
    if (!empty($this->yt)) {
      $region = _youtube_uploader_get_country();
      $list_response = $this->yt->videoCategories->listVideoCategories('snippet', array('regionCode' => $region));
      foreach ($list_response as $resp) {
        $cat[$resp['id']] = $resp['snippet']['title'];
      }
    }
    return $cat;
  }


  /**
   * Delete a video from YouTube.
   */
  public function deleteVideo($video_id) {
    $this->getFreshToken();
    $error = '';
    try {
      $result = $this->yt->videos->delete($video_id);
    }
    catch (Google_ServiceException $e) {
      drupal_set_message(t('A service error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage()))), 'error');
    }
    catch (Google_Exception $e) {
      drupal_set_message(t('A client error occurred: <code>@error</code></p>', array('@error' => htmlspecialchars($e->getMessage()))), 'error');
    }
  }
}
