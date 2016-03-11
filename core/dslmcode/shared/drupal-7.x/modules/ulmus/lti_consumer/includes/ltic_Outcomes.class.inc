<?php

class Outcomes {

  /**
   * @var string 
   */
  protected $command;

  /**
   * @var int
   */
  protected $resource_id;

  /**
   * @var EntityFieldQuery 
   */
  protected $entityQuery;

  public function __construct() {
    $this->command = $this->getStream();
    $this->parseCommand();
  }

  /**
   * @return SimpleXMLElement
   */
  protected function getStream() {
    $stream = fopen('drupal://input', 'r');
    if ($stream) {
      return simplexml_load_string(stream_get_contents($stream));
    }
  }

  protected function parseCommand() {
    $request = key($this->command->imsx_POXBody);
    switch ($request) {
      case 'readResultRequest':
        $this->request();
        break;
      case 'replaceResultRequest':
        $this->replace();
        break;
      case 'deleteResultRequest':
        $this->delete();
        break;

      default:
        $this->other($request);
        break;
    }
  }

  protected function request() {
    if ($id = $this->command->imsx_POXBody->readResultRequest->resultRecord->sourcedGUID->sourcedId) {
      if ($success = ltic_result_load($id)) {
        $result = $success->ltic_result;
        $response = new OutcomesResponse(isset($success) ? 'success' : 'failure', 'Result read', $id, 'readResultResponse');
        $responsexml = $response->getResponse();
        $node = $responsexml->imsx_POXBody->readResultResponse;
        $node = $node->addChild('result')->addChild('resultScore');
        $node->addChild('language', 'en');
        $node->addChild('textString', isset($result) ? $result : '');
      }
      else {
        $response = new OutcomesResponse('failure', 'Result read', uniqid(), 'readResultResponse');
        $responsexml = $response->getResponse();
      }
      echo $responsexml->asXML();
    }
  }

  protected function delete() {
    $sucess = FALSE;
    if ($id = $this->command->imsx_POXBody->deleteResultRequest->resultRecord->sourcedGUID->sourcedId) {
      if ($record = ltic_result_load($id)) {
        if (isset($record->ltic_result)) {
          $record->ltic_result = NULL;
          ltic_result_save($record);
          $sucess = TRUE;
        }
        $response = new OutcomesResponse($sucess ? 'success' : 'failure', 'Grade delete request', $id, 'deleteResultResponse');
      }
      else {
        $response = new OutcomesResponse('failure', 'Grade delete request', uniqid(), 'deleteResultResponse');
      }
      $responsexml = $response->getResponse();
      echo $responsexml->asXML();
    }
  }

  protected function checkScore($score) {
    $score = (string) $score;
    if (!is_numeric($score)) {
      throw new Exception('Score must be numeric');
    }
    $score = floatval($score);
    if ($score < 0.0 || $score > 1.0) {
      throw new Exception('Score not between 0.0 and 1.0');
    }
    return $score;
  }

  protected function replace() {
    if ($id = $this->command->imsx_POXBody->replaceResultRequest->resultRecord->sourcedGUID->sourcedId) {
      if ($record = ltic_result_load($id)) {
        $value = $this->command->imsx_POXBody->replaceResultRequest->resultRecord->result->resultScore->textString;
        try {
          $value = $this->checkScore($value);
          $record->ltic_result = $value;
          $result = ltic_result_save($record);
          $message = 'Grade replace response';
        }
        catch (Exception $ex) {
          $result = NULL;
          $message = $ex->getMessage();
          $id = uniqid();
        }
        $response = new OutcomesResponse(isset($result) ? 'success' : 'failure', $message, $id, 'replaceResultResponse');
      }
      else {
        $response = new OutcomesResponse('failure', 'Grade replace response', uniqid(), 'replaceResultResponse');
      }
      $responsexml = $response->getResponse();
      echo $responsexml->asXML();
    }
  }

  /**
   * @param string $message_type
   */
  protected function other($message_type) {
    $handled = FALSE;
    /**
     * Add a hook to allow other modules to hook into outcomes api call
     * All it needs to do is set the flag for handled to TRUE and implement the
     * response in standard format, can use passed object 
     */
    drupal_alter('ltic_outcomes_request', $handled, $message_type, $this);
    if (!$handled) {
      $response = new OutcomesResponse('unsupported', 'unsupported', uniqid(), $message_type);
      $responsexml = $response->getResponse();
      echo $responsexml->asXML();
    }
  }

  protected function setFieldQuery() {
    $this->entityQuery = new EntityFieldQuery();
  }

}
