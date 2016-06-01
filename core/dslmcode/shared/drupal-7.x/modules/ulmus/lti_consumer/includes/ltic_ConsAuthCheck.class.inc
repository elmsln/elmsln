<?php

class ConsAuthCheck {

  /**
   * @var string
   */
  protected $consumerKey;

  public function __construct() {
    $this->getConsumerKey();
  }

  /**
   * @return string
   */
  function getBody() {
    $stream = fopen('drupal://input', 'r');
    return stream_get_contents($stream);
  }

  /**
   * @throws Exception
   */
  function getConsumerKey() {
    foreach (OAuthUtil::get_headers() as $name => $value) {
      if ($name === 'Authorization') {
        // TODO: Switch to core oauthlib once implemented - MDL-30149
        $oauthparams = OAuthUtil::split_header($value);

        $this->consumerKey = $oauthparams['oauth_consumer_key'];
        break;
      }
    }
    if (empty($this->consumerKey)) {
      throw new Exception('Consumer key is missing.');
    }
  }

  /**
   * @return boolean
   */
  public function verifyMessage() {
    //This took key,secret,body,headers
    $signaturefailed = false;
    try {
      $this->handleOAuthBodyPOST();
    }
    catch (Exception $e) {
      $signaturefailed = true;
    }
    if (!$signaturefailed) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * @global text $base_url
   * @return text
   * @throws Exception
   */
  function handleOAuthBodyPOST() {
    $request_headers = OAuthUtil::get_headers();
    if (@substr($request_headers['Authorization'], 0, 6) == "OAuth ") {
      $header_parameters = OAuthUtil::split_header($request_headers['Authorization']);
      $oauth_body_hash = $header_parameters['oauth_body_hash'];
    }

    if (!isset($oauth_body_hash)) {
      throw new Exception("OAuth request body signing requires oauth_body_hash body");
    }

    // Verify the message signature
    $store = new LTICOAuthDataStore();
    $store->add_consumer($this->consumerKey, variable_get('ltic_tool_consumer_secret', ''));
    $server = new OAuthServer($store);
    $method = new OAuthSignatureMethod_HMAC_SHA1();
    $server->add_signature_method($method);
    global $base_url;
    $request = new OAuthRequest('POST', $base_url . '/' . variable_get('ltic_outcomes_launch_path', ''), $header_parameters);


    try {
      $server->verify_request($request);
    }
    catch (Exception $e) {
      $message = $e->getMessage();
      throw new Exception("OAuth signature failed: " . $message);
    }

    $postdata = $this->getBody();
    $hash = base64_encode(sha1($postdata, TRUE));
    if ($hash != $oauth_body_hash) {
      throw new Exception("OAuth oauth_body_hash mismatch");
    }
    return $postdata;
  }

}
