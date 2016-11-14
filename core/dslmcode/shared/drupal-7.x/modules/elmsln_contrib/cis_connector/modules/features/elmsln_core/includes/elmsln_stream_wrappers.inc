<?php
/**
 * ELMSLNLocalStreamWrapper
 */
abstract class ELMSLNLocalStreamWrapper extends DrupalLocalStreamWrapper {
  /**
   * Get the path for the elmsln configuration file
   */
  public function getELMSLNConfigPath() {
    // load configuration file
    $cfg = _elmsln_core_get_cfg();
    return $cfg['configsdir'];
  }

  /**
   * Get the path for the elmsln configuration file
   */
  public function getELMSLNHost() {
    // load configuration file
    $cfg = _elmsln_core_get_cfg();
    return $cfg['host'];
  }

  /**
   * Get the path for the elmsln configuration file
   */
  public function getELMSLNDomain($tool) {
    $domain = '';
    // load configuration file
    if ($settings = _cis_connector_build_registry($tool)) {
      $adr = explode('.', $settings['address']);
      $domain = array_shift($adr);
    }
    return $domain;
  }
}

/**
 * ELMSLN Authority public (elmslnauthority://) stream wrapper class.
 *
 * Provides support for storing and retrieving files based on
 * the patterned file structure of elmsln.
 *
 * elmslnauthority://cpr/user/abc123.jpg => /var/www/elmsln/domains/people/sites/people/{part}/files/user/abc123.jpg
 */
class ELMSLNAuthorityStreamWrapper extends ELMSLNLocalStreamWrapper {
  /**
   * Implements abstract public function getDirectoryPath()
   */
  public function getDirectoryPath() {
    // convert target into array
    $fileparts =  explode('/', str_replace('\\', '/', $this->getTarget()));
    // shift front off into tool name
    $tool = array_shift($fileparts);
    // convert back to file you are looking for
    $filepath = implode('/', $fileparts);
    // build full path to return
    $path = self::getELMSLNConfigPath() . '/stacks/' . self::getELMSLNDomain($tool) . '/sites/' . self::getELMSLNDomain($tool) . '/' . self::getELMSLNHost() . '/files/' . $filepath;
    return $path;
  }

  /**
   * Overrides getExternalUrl().
   *
   * Return the HTML URI of a public file.
   */
  function getExternalUrl() {
    // convert target into array
    $fileparts =  explode('/', str_replace('\\', '/', $this->getTarget()));
    // shift front off into tool name
    $tool = array_shift($fileparts);
    // convert back to file you are looking for
    $filepath = implode('/', $fileparts);
    // load settings so we can build an appropriate address
    $settings = _cis_connector_build_registry($tool);
    // build address from registry
    $address = _cis_connector_format_address($settings, '', 'front');
    return $address . '/sites/' . self::getELMSLNDomain($tool) . '/' . self::getELMSLNHost() . '/files/' . drupal_encode_path($filepath);
  }
}

/**
 * ELMSLN Service public (elmslnservice://) stream wrapper class.
 *
 * Provides support for storing and retrieving files based on
 * the patterned file structure of elmsln.
 * This allos for things like:
 * elmslnservice://mooc/sing100/images/things.jpg => /var/www/elmsln/domains/courses/sites/courses/{part}/sing100/files/images/things.jpg
 */
class ELMSLNServiceStreamWrapper extends ELMSLNLocalStreamWrapper {
  /**
   * Implements abstract public function getDirectoryPath()
   */
  public function getDirectoryPath() {
    // convert target into array
    $fileparts =  explode('/', str_replace('\\', '/', $this->getTarget()));
    // shift front off into tool name
    $tool = array_shift($fileparts);
    // shift front off into tool name
    $course = array_shift($fileparts);
    // convert back to file you are looking for
    $filepath = implode('/', $fileparts);
    // build full path to return
    $path = self::getELMSLNConfigPath() . '/stacks/' . self::getELMSLNDomain($tool) . '/sites/' . self::getELMSLNDomain($tool) . '/' . self::getELMSLNHost() . '/' . $course . '/files/' . $filepath;
    return $path;
  }

  /**
   * Overrides getExternalUrl().
   *
   * Return the HTML URI of a public file.
   */
  function getExternalUrl() {
    // convert target into array
    $fileparts =  explode('/', str_replace('\\', '/', $this->getTarget()));
    // shift front off into tool name
    $tool = array_shift($fileparts);
    // shift front off into tool name
    $course = array_shift($fileparts);
    // convert back to file you are looking for
    $filepath = implode('/', $fileparts);
    // load settings so we can build an appropriate address
    $settings = _cis_connector_build_registry($tool);
    // build address from registry
    $address = _cis_connector_format_address($settings, '/' . $course, 'front');
    return $address . '/sites/' . self::getELMSLNDomain($tool) . '/' . self::getELMSLNHost() . '/' . $course . '/files/' . drupal_encode_path($filepath);
  }
}