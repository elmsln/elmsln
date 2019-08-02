<?php

/**
 * The Canvas class is the base class used for making all Canvas API calls.
 *
 * Depending on the requested API, we need to make calls using the following
 * methods: GET (default), PUT, POST, and DELETE. Child classes can set the
 * method and parameters for the call.
 */
class Canvas {

  public $params;
  public $path;
  protected $base;
  protected $headers;
  protected $method;

  function __construct(){
    $this->_setHeaders();
    $this->_setUrl();

  }

  private function _setHeaders(){
    $token = variable_get('canvas_api_token');
    $this->headers = array(
      'Authorization' => 'Bearer ' . $token,
      'Cache-Control' => 'no-cache',
      'cache-control' => 'no-cache',
      'Content-Type' => 'application/x-www-form-urlencoded',
    );
  }

  private function _setURL(){
    $institution = variable_get('canvas_api_institution', '');
    $environment = variable_get('canvas_api_environment', 'test');
    $url = "https://$institution";
    if($environment != 'production'){
      $url .= '.' . $environment;
    }
    $url .= '.instructure.com/';
    $this->url = $url;
  }

  /**
   * Execute the API request and return the response.
   *
   * @param $method
   * GET (default), PUT, POST, and DELETE
   *
   * @return array
   * JSON-decoded response from Canvas
   */
  protected function _getResponse($method){

    $path = 'api/v1/' . $this->path;

    $query = $this->_buildQuery($this->params);

    $url = $this->url . $path;

    $options = array(
      'headers' => $this->headers,
      'method' => $method,
      'data' => $query,
    );
    $response = $this->_makeRequest($url, $options);
    // Canvas limits the number of responses returned in a GET request. If we pass
    // per_page=100, we can get up to 100, but that's all; if there are more,
    // we need to get the "next" page, which is passed in the Link: attribute
    // in the response header.
    if ($method == 'get') {
      $data = json_decode($response->data, TRUE);
      list($next, $max) = $this->_getNextURL($response);
      // We use a counter as a failsafe to this becoming an infinite loop.
      $i = 0;
      // ensure we have something to walk and we don't go above max results
      while ($next && ($i < $max)) {
        $response = $this->_makeRequest($next, $options);
        $data = array_merge($data, json_decode($response->data, TRUE));
        list($next, $tmp) = $this->_getNextURL($response);
        $i++;
        if ($i>30) {
          // THIS IS JUST A FAILSAFE FOR HUGE RESULTSETS;
          die('Over 30 iterations');
        }
      }
      return $data;
    }

    return json_decode($response->data, TRUE);
  }

  public function put(){
    return $this->_getResponse('put');
  }

  public function _makeRequest($url, $options){
    // support developers overloading the request method, specifically curl
    // as some systems can have issues with SSL configuration and socket connections
    if (variable_get('canvas_api_request_method', 'drupal_http_request') == 'curl' && function_exists('curl_init')) {
      $headers = array();
      foreach ($options['headers'] as $property => $value) {
        $headers[] = $property . ': ' . $value;
      }
      $curl = curl_init();
      curl_setopt_array($curl, array(
        CURLOPT_URL => $url . '?' . $options['data'],
        CURLOPT_RETURNTRANSFER => TRUE,
        CURLOPT_HEADER => TRUE,
        CURLOPT_VERBOSE => TRUE,
        CURLOPT_ENCODING => "",
        CURLOPT_MAXREDIRS => 10,
        CURLOPT_TIMEOUT => 30,
        CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
        CURLOPT_CUSTOMREQUEST => strtoupper($options['method']),
        CURLOPT_HTTPHEADER => $headers,
        CURLOPT_POSTFIELDS => "",
      ));
      $return = curl_exec($curl);
      $header_size = curl_getinfo($curl, CURLINFO_HEADER_SIZE);
      $header = substr($return, 0, $header_size);
      $rawheader = explode("\n", $header);
      $body = substr($return, $header_size);
      curl_close($curl);
      $response = new stdClass();
      $response->data = $body;
      foreach ($rawheader as $header) {
        if (strpos($header, 'Link: ') === 0) {
          $response->headers['link'] = str_replace('Link: ', '', $header);
        }
      }
    }
    // support for httprl which is faster then core and does same thing
    elseif (module_exists('httprl')) {
      httprl_request($url, $options);
      // send the request off
      $tmp = httprl_send_request();
      $response = array_pop($tmp);
    }
    else {
      // original fallback
      $response = drupal_http_request($url, $options);
    }
    return $response;
  }

  public function post(){
    return $this->_getResponse('post');
  }

  public function get(){
    $this->params['per_page'] = 100;
    return $this->_getResponse('get');
  }

  public function delete(){
    return $this->_getResponse('delete');
  }

  /**
   * Extracts the "next" url from the response header.
   *
   * @param object $response
   * Http response
   *
   * @return string
   * Link to next URL if found, FALSE if not
   */
  private function _getNextURL($response){
    if(isset($response->headers['link'])){
      $next = FALSE;
      $last = FALSE;
      $linkHeader = $response->headers['link'];
      // simplify preg later
      $links = explode(',', $response->headers['link']);
      $link = $linkHeader;
      if (is_array($linkHeader)) {
        $link = reset($linkHeader);
      }
      $matches = array();
      $pattern = '/,<(.+)>; rel="next"/';
      preg_match($pattern, $link, $matches);
      // discover next element to request
      if(isset($matches[1])){
        $next = $matches[1];
      }
      $matches = array();
      $pattern = '/<(.+)>; rel="last"/';
      preg_match($pattern, $links[3], $matches);
      if(isset($matches[1])){
        $last = $matches[1];
      }
      if ($last) {
        $tmp = explode('page=', $last);
        $tmp = explode('&', $tmp[1]);
        if (is_numeric($tmp[0])) {
          $last = $tmp[0];
        }
      }
      return array($next, $last);
    }
    return array(FALSE, FALSE);
  }

  /**
   * Helper function to build the query.
   *
   * Array values passed to Canvas must be in the form foo[]=bar&foo[]=baz, but
   * http_build_query (used by the Guzzle Client) will encode this as
   * foo[0]=bar&foo[1]=baz, which will fail. This helper function will also
   * allow us to pass in parameters as arrays, i.e.:
   *    $canvas_api->params = array(
   *      'course' => array(
   *         'account_id' => 1,
   *         'name' => 'Course Name',
   *         'term_id' => 6,
   *      ),
   *    );
   *
   * See @link https://canvas.instructure.com/doc/api/courses.html#method.courses.update @endlink
   *
   * @param array $params
   * @return string
   */
  private function _buildQuery($params = array()){

    $query = [];
    foreach($params as $key=>$param){
      if(is_array($param)) {
        foreach ($param as $key2=>$value) {
          $index = is_int($key2) ? '' : $key2;
          $query[] = $key . '[' . $index . ']=' . $value;
        }
      } else {
        $query[] = $key . '=' . $param;
      }
    }
    return implode('&', $query);
  }
}
