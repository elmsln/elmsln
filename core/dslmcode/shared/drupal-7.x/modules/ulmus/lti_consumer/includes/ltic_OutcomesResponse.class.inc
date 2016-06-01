<?php

class OutcomesResponse {

  /**
   * @var SimpleXMLElement
   */
  protected $response;

  /**
   * @var string 
   */
  protected $codeMajor;

  /**
   * @var string 
   */
  protected $description;

  /**
   * @var string
   */
  protected $messageRef;

  /**
   * @var string
   */
  protected $messageType;

  /**
   * @param string $codemajor
   * @param string $description
   * @param string $messageref
   * @param string $messagetype
   */
  public function __construct($codemajor, $description, $messageref, $messagetype) {
    $this->codeMajor = $codemajor;
    $this->description = $description;
    $this->messageRef = $messageref;
    $this->messageType = $messagetype;
    $this->response = new SimpleXMLElement('<?xml version="1.0" encoding="UTF-8"?><imsx_POXEnvelopeResponse />');
    $this->buildbasic();
    $this->setStatusInfo();
    $this->setBody();
  }

  protected function buildbasic() {
    $this->response->addAttribute('xmlns', 'http://www.imsglobal.org/services/ltiv1p1/xsd/imsoms_v1p0');
  }

  /**
   * 
   * @return SimpleXMLElement
   */
  protected function getHeaderInfo() {
    $header_info = $this->response->addChild('imsx_POXHeader')->addChild('imsx_POXResponseHeaderInfo');
    $header_info->addChild('imsx_version', 'V1.0');
    $header_info->addChild('imsx_messageIdentifier', (string) mt_rand());
    return $header_info;
  }

  protected function setStatusInfo() {
    $header = $this->getHeaderInfo();
    $status_info = $header->addChild('imsx_statusInfo');
    $status_info->addchild('imsx_codeMajor', $this->codeMajor);
    $status_info->addChild('imsx_severity', 'status');
    $status_info->addChild('imsx_description', $this->description);
    $status_info->addChild('imsx_messageRefIdentifier', $this->messageRef);
  }

  protected function setBody() {
    $this->response->addChild('imsx_POXBody')
        ->addChild($this->messageType);
  }

  /**
   * @return SimpleXMLElement
   */
  public function getResponse() {
    return $this->response;
  }

}
