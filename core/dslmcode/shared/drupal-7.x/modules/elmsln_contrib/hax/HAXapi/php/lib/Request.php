<?php
// valid operations to execute
include_once 'Operations.php';
/**
 * Request object thats in charge of validating and brokering requests
 */
class Request {
    private $status;
    private $contentType;
    public $validateJWT;
    public function __construct() {
        // status is dead, something has to escalate it
        $this->status = 500;
        $this->contentType = "application/json";
        // default to validation of both though not everything needs it
        $this->validateJWT = true;
    }
    /**
     * Validate the current request
     */
    private function valid() {
      if ($this->validateJWT) {
        if (!$GLOBALS['HAXCMS']->validateJWT()) {
          return FALSE;
        }
      }
      return TRUE;
    }
    /**
     * Return encoded data, optional flag for data without headers
     */
    private function encodeData($response, $dataOnly = FALSE, $encode = TRUE) {
      if (!$dataOnly) {
        http_response_code($this->status);
        header('Content-Type: ' . $this->contentType);
      }
      if ($encode) {
        print json_encode($response);
      }
      else {
        print $response;
      }
      if (!$dataOnly) {
        exit();
      }
    }
    /**
     * Execute the callback ensuring its ones we support
     * @todo need to support custom / modular callbacks
     */
    public function execute($op, $params = array(), $rawParams = array()) {
      // we only skip JWT validation on edge cases
      // @todo add support for supplying these pass throughs via object if we find we need a lot
      if (in_array($op, array(
        'generateAppStore',
        'connectionSettings',
        'listSites',
        'login',
        'logout',
        'api',
        'options',
        'openapi',
        'refreshAccessToken'))) {
        $this->validateJWT = FALSE;
      }
      if ($this->valid()) {
        // validated so lets mark it so in headers
        $this->status = 200;
        $operations = new Operations();
        // if this method exists, it's been validated so execute it
        // and return response data
        if (method_exists($operations, $op)) {
          $operations->params = $params;
          $operations->rawParams = $rawParams;
          // support some commands that have to set via the camelCase
          // this only happens in rare situations like file upload
          // because of front end requirements to ship via GET vars
          // normalize these edge cases here, CLI needs this as well
          // siteName and nodeId should be the only two
          if (isset($operations->rawParams['siteName'])) {
            if (!isset($operations->params['site'])) {
              $operations->params['site'] = array();
            }
            $operations->params['site']['name'] = $operations->rawParams['siteName'];
            if (!isset($operations->rawParams['site'])) {
              $operations->rawParams['site'] = array();
            }
            $operations->rawParams['site']['name'] = $operations->rawParams['siteName'];
          }
          // nodeId is the same way
          if (isset($operations->rawParams['nodeId'])) {
            if (!isset($operations->params['node'])) {
              $operations->params['node'] = array();
            }
            $operations->params['node']['id'] = $operations->rawParams['nodeId'];
            if (!isset($operations->rawParams['node'])) {
              $operations->rawParams['node'] = array();
            }
            $operations->rawParams['node']['id'] = $operations->rawParams['nodeId'];
          }
          $response = $operations->{$op}();
          if (is_array($response) && isset($response['__failed'])) {
            $this->status = $response['__failed']['status'];
            $this->encodeData($response['__failed']['message']);
          }
          else if (is_array($response) && isset($response['__noencode'])) {
            $this->contentType = $response['__noencode']['contentType'];
            $this->status = $response['__noencode']['status'];
            $this->encodeData($response['__noencode']['message'], FALSE, FALSE);
          }
          else {
            $this->encodeData($response);
          }
        }
        else {
          $this->status = 500;
          $this->encodeData("$op is not a valid callback");
        }
      }
    }
}