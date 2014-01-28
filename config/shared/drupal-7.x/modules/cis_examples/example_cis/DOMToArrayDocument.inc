<?php
// class extending DOMDocument object to allow for simple array function
// see documentation at http://php.net/manual/en/class.domdocument.php
class DOMToArrayDocument extends DOMDocument
{
  public function toArray(DOMNode $oDomNode = null)
  {
    // return empty array if dom is blank
    if (is_null($oDomNode) && !$this->hasChildNodes()) {
        return array();
    }
    $oDomNode = (is_null($oDomNode)) ? $this->documentElement : $oDomNode;
    if (!$oDomNode->hasChildNodes()) {
      $mResult = $oDomNode->nodeValue;
    }
    else {
      $mResult = array();
      foreach ($oDomNode->childNodes as $oChildNode) {
        // how many of these child nodes do we have?
        $oChildNodeList = $oDomNode->getElementsByTagName($oChildNode->nodeName);  
        $iChildCount = 0;
        // however, we are only interested in the # of siblings with the same tag name
        foreach ($oChildNodeList as $oNode) {
          if ($oNode->parentNode->isSameNode($oChildNode->parentNode)) {
            $iChildCount++;
          }
        }
        $mValue = $this->toArray($oChildNode);
        $sKey = ($oChildNode->nodeName{0} == '#') ? 0 : $oChildNode->nodeName;
        $mValue = is_array($mValue) ? $mValue[$oChildNode->nodeName] : $mValue;
        // how many of thse child nodes do we have?
        if ($iChildCount > 1) {  // more than 1 child - make numeric array
          $mResult[$sKey][] = $mValue;
        }
        else {
          $mResult[$sKey] = $mValue;
        }
      }
      // if the child is <foo>bar</foo>, the result will be array(bar)
      // make the result just 'bar'
      if (count($mResult) == 1 && isset($mResult[0]) && !is_array($mResult[0])) {
        $mResult = $mResult[0];
      }
    }
    // get our attributes if we have any
    $arAttributes = array();
    if ($oDomNode->hasAttributes()) {
      foreach ($oDomNode->attributes as $sAttrName=>$oAttrNode) {
        // retain namespace prefixes
        $arAttributes["@{$oAttrNode->nodeName}"] = $oAttrNode->nodeValue;
      }
    }
    // check for namespace attribute
    if ($oDomNode instanceof DOMElement && $oDomNode->getAttribute('xmlns')) {
      $arAttributes["@xmlns"] = $oDomNode->getAttribute('xmlns');
    }
    if (count($arAttributes)) {
      if (!is_array($mResult)) {
        $mResult = (trim($mResult)) ? array($mResult) : array();
      }
      $mResult = array_merge($mResult, $arAttributes);
    }
    $arResult = array($oDomNode->nodeName=>$mResult);
    return $arResult;
  }
}