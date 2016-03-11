<?php

/**
 * This will put togather the details to launch a lti
 *
 * @author Darren Whittington
 */
class AuthDetails {

  /**
   * @var array 
   */
  protected $launchData;

  /**
   * @var string
   */
  protected $lurl;

  /**
   * @var DateTime 
   */
  protected $now;

  /**
   * @var string
   */
  protected $key;

  /**
   * @var string
   */
  protected $secret;

  /**
   * @var array
   */
  protected $resource;

  /**
   * @var array 
   */
  protected $context;

  /**
   * @var stdClass
   */
  protected $user;

  /**
   * @var string
   */
  protected $signature;

  /**
   * @var array 
   */
  protected $custom;

  //This will get details from user or database
  /**
   * Receives Context and resource id
   * 'context','resource'
   * @param array $ids
   */
  public function __construct(array $ids) {
    $this->setVars();
    $this->setResource($ids['resource']);
    $this->setContext($ids['context']);
    $this->setUser();
    $this->setExtraParams();
    $this->swapoutVars();
    $this->buildLaunchData();
    $this->setNow();
    $this->setLtiDetails();
    $this->setOAuth();
  }

  public function build() {
    $this->sort();
    $this->setSignature();
  }

  /**
   * @param int $id
   */
  protected function setResource($id) {
    $res = new BuildResource(array($id));
    $this->resource = $res->getDetails()[$id];
  }

  /**
   * @param int $id
   */
  protected function setContext($id) {
    $con = new BuildContext($id);
    $this->context = $con->getDetails();
  }

  protected function setUser() {
    $user_inst = new BuildUser();
    $this->user = $user_inst->getDetails();
  }

  protected function buildLaunchData() {
    $this->launchData = array_merge($this->context, $this->resource, $this->user, $this->custom);
  }

  protected function setLtiDetails() {
    $this->launchData["lti_version"] = variable_get('ltic_ltiversion', "LTI-1p0");
    $this->launchData["lti_message_type"] = "basic-lti-launch-request";
    $this->launchData["tool_consumer_info_product_family_code"] = variable_get('ltic_tool_consumer_info_product_family_code', 'ltic_drupal7');
    $this->launchData["tool_consumer_info_version"] = variable_get('ltic_tool_consumer_info_version', "0.1");
    $this->launchData["launch_presentation_locale"] = variable_get('ltic_tool_locale', 'en-UK');
    $this->launchData["tool_consumer_instance_name"] = variable_get('ltic_tool_consumer_instance_name', 'LTI Module Drupal 7');
    $this->launchData["tool_consumer_instance_description"] = variable_get('ltic_tool_consumer_instance_description', 'A generic LTI Module Drupal 7');
    $this->launchData["tool_consumer_instance_guid"] = variable_get('ltic_tool_consumer_instance_guid', 'drupal.lti.module');
    $this->launchData["tool_consumer_instance_contact_email"] = variable_get('site_mail', '');
  }

  public function setParameter($key, $value) {
    $this->launchData[$key] = $value;
  }

  protected function setVars() {
    $this->lurl = variable_get('ltic_tool_launch_url', '');
    $this->key = variable_get('ltic_tool_consumer_key', '');
    $this->secret = variable_get('ltic_tool_consumer_secret', '');
  }

  protected function setNow() {
    $this->now = new DateTime();
  }

  protected function setExtraParams() {
    $string = variable_get('ltic_tool_custom_param', '');
    if (isset($string)) {
      foreach (preg_split("/((\r?\n)|(\r\n?))/", $string) as $line) {
        $params = explode('=', $line);
        $customed = 'custom_' . $params[0];
        $changed = strtolower(preg_replace('/[^a-zA-Z0-9+]/', '_', $customed));
        if (strcmp($changed, $customed !== 0)) {
          $this->custom[$changed] = $params[1];
        }
        $this->custom[$customed] = $params[1];
      }
    }
  }

  /**
   * This method calls a new class that looks for custom varables
   * in the extra parameters, if matches are found it adds in the system 
   * value
   */
  protected function swapoutVars() {
    $pv = new ParseVars($this->custom);
    $this->custom = $pv->parseParams();
  }

  /**
   * Basic LTI uses OAuth to sign requests
   * OAuth Core 1.0 spec: http://oauth.net/core/1.0/
   */
  protected function setOAuth() {
    $this->launchData["oauth_callback"] = "about:blank";
    $this->launchData["oauth_consumer_key"] = $this->key;
    $this->launchData["oauth_version"] = "1.0";
    $this->launchData["oauth_nonce"] = uniqid('', true);
    $this->launchData["oauth_timestamp"] = $this->now->getTimestamp();
    $this->launchData["oauth_signature_method"] = "HMAC-SHA1";
  }

  protected function sort() {
    ksort($this->launchData);
  }

  private function setSignature() {
    $this->signature_method = new OAuthSignatureMethod_HMAC_SHA1();
    $this->signature = $this->signature_method->build_signature(
        new OAuthRequest('POST', $this->lurl, $this->launchData), new OAuthConsumer($this->key, $this->secret), NULL
    );
  }

  /**
   * Getters and setters
   */

  /**
   * @return DateTime
   */
  public function getNow() {
    return $this->now();
  }

  /**
   * @return array
   */
  public function getLD() {
    return $this->launchData;
  }

  /**
   * @return string
   */
  public function getLaunchUrl() {
    return $this->lurl;
  }

  /**
   * @return string
   */
  public function getSignature() {
    return $this->signature;
  }

  /**
   * @return string
   */
  public function getSecret() {
    return $this->secret;
  }

  /**
   * @return string
   */
  public function getKey() {
    return $this->key;
  }

}
