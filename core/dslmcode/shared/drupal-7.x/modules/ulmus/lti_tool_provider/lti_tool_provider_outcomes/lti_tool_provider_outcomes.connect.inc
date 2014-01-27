<?php

/**
 * @file
 * Functions for http xml requests to LTI Consumer services.
 */

/**
 * Send single grade via http post.
 *
 * @param string $params
 *   An array containing the POST data, eg, lti_message_type etc.
 * @param string $key
 *   The consumer key.
 * @param string $url
 *   URL of the LTI service.
 *
 * @return string
 *   HTTP response.
 */
function lti_tool_provider_outcomes_lti_service_post($params, $key, $url) {
  $ext_response = NULL;
  if (!empty($url)) {
    // Check for query parameters which need to be included in the signature.
    $query_params = array();
    $query_string = parse_url($url, PHP_URL_QUERY);
    if (!is_null($query_string)) {
      $query_items = explode('&', $query_string);
      foreach ($query_items as $item) {
        if (strpos($item, '=') !== FALSE) {
          list($name, $value) = explode('=', $item);
          $query_params[$name] = $value;
        }
        else {
          $query_params[$name] = '';
        }
      }
    }
    $params = $params + $query_params;
    // Add standard parameters.
    $params['oauth_consumer_key'] = $key;
    $params['lti_version'] = 'LTI-1p0';
    $oauth_consumer_key = $key;
    $store = new LTIToolProviderOAuthDataStore();
    $consumer = $store->lookup_consumer($oauth_consumer_key);
    $token = '';
    $hmac_method = new OAuthSignatureMethod_HMAC_SHA1();
    $request = OAuthRequest::from_consumer_and_token($consumer, $token, 'POST', $url, $params);
    $request->sign_request($hmac_method, $consumer, $token);
    $params = $request->get_parameters();

    // Remove parameters being passed on the query string.
    foreach (array_keys($query_params) as $name) {
      unset($params[$name]);
    }
    // Connect to tool consumer.
    // http_build_query($params).
    $options = array(
      'data' => http_build_query($params),
      'method' => 'POST',
      'max_redirects' => 5,
      'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
    );
    $ext_response = drupal_http_request($url, $options);
  }
  return $ext_response;
}

/**
 * Constructs an array of parameters(READ) for the http post.
 *
 * @param string $sourcedid
 *   Sourece did of the incoming request.
 *
 * @return array
 *   Array of parameters.
 */
function lti_tool_provider_outcomes_construct_params_array_read($sourcedid) {
  $params = array();
  $params['lti_message_type'] = 'basic-lis-readresult';
  $params['sourcedid'] = $sourcedid;
  return $params;
}

/**
 * Constructs an array of parameters(UPDATE) for the http post.
 *
 * @param string $source_did
 *   Result Source DID.
 * @param string $grade
 *   Grade of the outcome record.
 * @param string $datatype
 *   Datatype of the resource.
 *
 * @return array
 *   Array of parameters.
 */
function lti_tool_provider_outcomes_construct_params_array_update($source_did, $grade, $base_no, $datatype) {
  $params = array();
  $params['lti_message_type'] = 'basic-lis-updateresult';
  $params['sourcedid'] = $source_did;
  // $params['result_resultscore_textstring'] =
  // lti_tool_provider_outcomes_format_raw_score($grade, $base_no, $datatype);
  $params['result_resultscore_textstring'] = $grade;
  $params['result_resultvaluesourcedid'] = 'decimal';
  return $params;
}

/**
 * Constructs an array of parameters(DELETE) for the http post.
 *
 * @param string $sourcedid
 *   Result Source DID.
 *
 * @return array
 *   Array of parameters.
 */
function lti_tool_provider_outcomes_construct_params_array_delete($sourcedid) {
  $params = array();
  $params['lti_message_type'] = 'basic-lis-deleteresult';
  $params['sourcedid'] = $sourcedid;
  return $params;
}

/**
 * Implements lti_tool_provider_outcomes_lti_service_xml().
 *
 * @param string $consumer
 *   Consumer entity.
 * @param string $url
 *   Endpoint URL.
 * @param string $message_type
 *   1 : UPDATE / replaceRESULT
 *   2 : READ / readRESULT
 *   3 : DELETE / deleteRESULT.
 * @param string $source_did
 *   lis_result_sourcedid.
 * @param string $grade
 *   OPTIONAL. Grade value to be updated.
 *
 * @return string
 *   HTTP response.
 */
function lti_tool_provider_outcomes_lti_service_xml($consumer, $url, $message_type, $source_did, $grade = NULL) {
  switch ($message_type) {
    // Create grades UPDATE xml service body.
    case 1: {
      $body = lti_tool_provider_outcomes_create_grades_update_service_body($source_did, $grade);
      break;
    };
    // Create grades READ xml service body.
    case 2: {
      $body = lti_tool_provider_outcomes_create_grades_read_service_body($source_did);
      break;
    };
    // Create grades DELETE xml service body.
    case 3: {
      $body = lti_tool_provider_outcomes_create_grades_delete_service_body($source_did);
      break;
    };
  }
  $response = lti_tool_provider_outcomes_send_oauth_xml_body_post('POST', $url, $consumer->lti_tool_provider_consumer_key, $consumer->lti_tool_provider_consumer_secret, 'application/xml', $body);
  return $response;
}

/**
 * Create a IMS POX body request for sync grades.
 *
 * @param string $source
 *   Source did required for the request.
 * @param float $grade
 *   User grade.
 *
 * @return string
 *   XML body.
 */
function lti_tool_provider_outcomes_create_grades_update_service_body($source, $grade) {
  return '<?xml version = "1.0" encoding = "UTF-8"?>
    <imsx_POXEnvelopeRequest xmlns = "http://www.imsglobal.org/lis/oms1p0/pox">
    <imsx_POXHeader>
    <imsx_POXRequestHeaderInfo>
    <imsx_version>V1.0</imsx_version>
    <imsx_messageIdentifier>' . REQUEST_TIME . '</imsx_messageIdentifier>
      </imsx_POXRequestHeaderInfo>
      </imsx_POXHeader>
      <imsx_POXBody>
      <replaceResultRequest>
      <resultRecord>
      <sourcedGUID>
      <sourcedId>' . $source . '</sourcedId>
        </sourcedGUID>
        <result>
        <resultScore>
        <language>en-us</language>
        <textString>' . $grade . '</textString>
          </resultScore>
          </result>
          </resultRecord>
          </replaceResultRequest>
          </imsx_POXBody>
          </imsx_POXEnvelopeRequest>';
}

/**
 * Create a IMS POX body request for reading grades.
 *
 * @param string $source
 *   Sourceid required for the request.
 *
 * @return string
 *   XML body.
 */
function lti_tool_provider_outcomes_create_grades_read_service_body($source) {
  return '<?xml version = "1.0" encoding = "UTF-8"?>
    <imsx_POXEnvelopeRequest xmlns = "http://www.imsglobal.org/services/ltiv1p1/xsd/imsoms_v1p0">
    <imsx_POXHeader>
    <imsx_POXRequestHeaderInfo>
    <imsx_version>V1.0</imsx_version>
    <imsx_messageIdentifier>' . REQUEST_TIME . '</imsx_messageIdentifier>
      </imsx_POXRequestHeaderInfo>
      </imsx_POXHeader>
      <imsx_POXBody>
      <readResultRequest>
      <resultRecord>
      <sourcedGUID>
      <sourcedId>' . $source . '</sourcedId>
        </sourcedGUID>
        </resultRecord>
        </readResultRequest>
        </imsx_POXBody>
        </imsx_POXEnvelopeRequest>';
}

/**
 * Create a IMS POX body request for deleting grades.
 *
 * @param string $source
 *   Source did required for the request.
 *
 * @return string
 *   XML body.
 */
function lti_tool_provider_outcomes_create_grades_delete_service_body($source) {
  return '<?xml version = "1.0" encoding = "UTF-8"?>
    <imsx_POXEnvelopeRequest xmlns = "http://www.imsglobal.org/services/ltiv1p1/xsd/imsoms_v1p0">
    <imsx_POXHeader>
    <imsx_POXRequestHeaderInfo>
    <imsx_version>V1.0</imsx_version>
    <imsx_messageIdentifier>' . REQUEST_TIME . '</imsx_messageIdentifier>
      </imsx_POXRequestHeaderInfo>
      </imsx_POXHeader>
      <imsx_POXBody>
      <deleteResultRequest>
      <resultRecord>
      <sourcedGUID>
      <sourcedId>' . $source . '</sourcedId>
        </sourcedGUID>
        </resultRecord>
        </deleteResultRequest>
        </imsx_POXBody>
        </imsx_POXEnvelopeRequest>';
}

/**
 * Use Oauth to sign the XML body.
 *
 * @param string $method
 *   HTTP method.
 * @param string $endpoint
 *   Endpoint Service URL.
 * @param string $oauth_consumer_key
 *   Consumer Key.
 * @param string $content_type
 *   HTTP request content type.
 * @param string $body
 *   XML body.
 *
 * @return string
 *   HTTP Response.
 */
function lti_tool_provider_outcomes_send_oauth_xml_body_post($method, $endpoint, $oauth_consumer_key, $oauth_consumer_secret, $content_type, $body) {
  $hash = base64_encode(sha1($body, TRUE));
  $parms = array('oauth_body_hash' => $hash);
  $test_token = '';
  $hmac_method = new OAuthSignatureMethod_HMAC_SHA1();
  $test_consumer = new OAuthConsumer($oauth_consumer_key, $oauth_consumer_secret, NULL);
  $acc_req = OAuthRequest::from_consumer_and_token($test_consumer, $test_token, $method, $endpoint, $parms);
  $acc_req->sign_request($hmac_method, $test_consumer, $test_token);
  $header = $acc_req->to_header();
  $header = $header . "\r\nContent-type: " . $content_type . "\r\n";
  $params = array(
    'http' => array(
      'method' => 'POST',
      'content' => $body,
      'header' => $header,
    ),
  );
  $ctx = stream_context_create($params);
  $fp = @fopen($endpoint, 'rb', FALSE, $ctx);
  $response = @stream_get_contents($fp);
  return $response;
}

/**
 * Decode XML for extension services.
 *
 * @param string $data
 *   HTTP Response.
 *
 * @return boolean
 *   TRUE if success / FALSE if not successful.
 */
function lti_tool_provider_outcomes_decode_ext_xml_reply($data) {
  if ($data->code != 200) {
    drupal_set_message(t('Request failed with code @code.', array('@code' => $data->code)), 'info');
    return FALSE;
  }
  if ($data->status_message != 'OK') {
    drupal_set_message(t('Request failed with status @message.', array('@message' => $data->status_message)), 'info');
    return FALSE;
  }
  $reader = new XMLReader();
  $reader->XML($data->data);
  $result = array();
  // Default XML elements.
  $codemajor = 'codemajor';
  $severity = 'severity';
  $codeminor = 'codeminor';
  while ($reader->read()) {
    // Codemajor    Success / Failure / Unsupported.
    // Severity     Status / Warning / Error.
    // Codeminor    fullsuccess / reason for failure.
    // Value        Value of the setting.
    if ($reader->nodeType == XMLReader::ELEMENT && ($reader->name == $codemajor || $reader->name == $severity || $reader->name == $codeminor)) {
      $str = $reader->readInnerXml();
      $codemajor_check = strcasecmp($str, 'success');
      $severity_check = strcasecmp($str, 'status');
      $codeminor_check = strcasecmp($str, 'fullsuccess');
      if ($codemajor_check == 0|| $severity_check == 0 || $codeminor_check == 0) {
        $result[] = $str;
      };
    }
  }
  $reader->close();
  if (count($result) == 3) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Decode xml reply from lis outcome service.
 *
 * @param string $data
 *   HTTP Response.
 *
 * @return boolean
 *   TRUE if success / FALSE if not successful.
 */
function lti_tool_provider_outcomes_decode_xml_reply($data) {
  if ($data->code != 200) {
    drupal_set_message(t('Request failed with code @code.', array('@code' => $data->code)), 'info');
    return FALSE;
  }
  if ($data->status_message != 'OK') {
    drupal_set_message(t('Request failed with status @message.', array('@message' => $data->status_message)), 'info');
    return FALSE;
  }
  $reader = new XMLReader();
  $reader->XML($data);
  $result = array();
  // Default XML elements.
  $imsx_codemajor = 'imsx_codeMajor';
  $imsx_severity = 'imsx_severity';
  $imsx_description = 'imsx_description';
  while ($reader->read()) {
    // Codemajor    Success / Failure / Unsupported.
    // Severity     Status / Warning / Error.
    // Codeminor    fullsuccess / reason for failure.
    // Value        Value of the setting.
    if ($reader->nodeType == XMLReader::ELEMENT && ($reader->name == $imsx_codemajor || $reader->name == $imsx_severity)) {
      $str = $reader->readInnerXml();
      $codemajor_check = strcasecmp($str, 'success');
      $severity_check = strcasecmp($str, 'status');
      if ($codemajor_check == 0 || $severity_check == 0) {
        $result[] = $str;
      };
    }
  }
  $reader->close();
  if (count($result) == 2) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Extract score from extension service.
 *
 * @param string $data
 *   HTTP Response,
 *
 * @return boolean
 *   TRUE if success / FALSE if not successful
 */
function lti_tool_provider_outcomes_extract_ext_xml_score_reply($data) {
  if (isset($data)) {
    $reader = new XMLReader();
    $reader->XML($data->data);
    $result = array();
    // Default XML elements.
    $codemajor = 'codemajor';
    $severity = 'severity';
    $codeminor = 'codeminor';
    while ($reader->read()) {
      // Codemajor    Success / Failure / Unsupported.
      // Severity     Status / Warning / Error.
      // Codeminor    fullsuccess / reason for failure.
      // Value        Value of the setting.
      if ($reader->nodeType == XMLReader::ELEMENT && ($reader->name == $codemajor || $reader->name == $severity || $reader->name == $codeminor)) {
        $str = $reader->readInnerXml();
        $codemajor_check = strcasecmp($str, 'success');
        $severity_check = strcasecmp($str, 'status');
        $codeminor_check = strcasecmp($str, 'fullsuccess');
        if ($codemajor_check == 0|| $severity_check == 0 || $codeminor_check == 0) {
          $result[] = $str;
        };
      }
      if (count($result) == 3) {
        if ($reader->nodeType == XMLReader::ELEMENT && $reader->name == 'textstring') {
          $score = $reader->readInnerXml();
          break;
        }

      }
    }
    $reader->close();
    if (isset($score)) {
      return $score;
    }
  }
}

/**
 * Extract score from lis outcome services.
 *
 * @param string $data
 *   HTTP Response.
 *
 * @return boolean
 *   TRUE if success / FALSE if not successful.
 */
function lti_tool_provider_outcomes_extract_xml_score_reply($data) {
  if (isset($data)) {
    $reader = new XMLReader();
    $reader->XML($data);
    $result = array();
    // Default XML elements.
    $imsx_codemajor = 'imsx_codeMajor';
    $imsx_severity = 'imsx_severity';
    $imsx_description = 'imsx_description';
    while ($reader->read()) {
      // Codemajor    Success / Failure / Unsupported.
      // Severity     Status / Warning / Error.
      // Codeminor    fullsuccess / reason for failure.
      // Value        Value of the setting.
      if ($reader->nodeType == XMLReader::ELEMENT && ($reader->name == $imsx_codemajor || $reader->name == $imsx_severity)) {
        $str = $reader->readInnerXml();
        $codemajor_check = strcasecmp($str, 'success');
        $severity_check = strcasecmp($str, 'status');
        if ($codemajor_check == 0 || $severity_check == 0) {
          $result[] = $str;
        };
      }
      if (count($result) == 2) {
        if ($reader->nodeType == XMLReader::ELEMENT && $reader->name == 'textString') {
          $score = $reader->readInnerXml();
          break;
        }
      }
    }
    $reader->close();
    if (isset($score)) {
      return $score;
    }
  }
}
