<?php
/**
 * @file
 * Plugin: jsDelivr.
 */

namespace Drupal\libraries_cdn\Plugin\LibrariesCDN;

use Drupal\Component\Plugin\PluginBase;
use Drupal\libraries_cdn\Component\Annotation\LibrariesCDNPlugin;
use Drupal\libraries_cdn\Type\CDNBase;
use Drupal\service_container\Legacy\Drupal7;

/**
 * Class JSDelivr.
 *
 * @LibrariesCDNPlugin(
 *  id = "jsdelivr",
 *  description = "jsDelivr Integration",
 *  arguments = {
 *    "@drupal7"
 *  }
 * )
 */
class JSDelivr extends CDNBase {
  /**
   * {@inheritdoc}
   */
  public function __construct(array $configuration, $plugin_id, array $plugin_definition, Drupal7 $drupal7) {
    if (empty($configuration['urls'])) {
      $configuration['urls'] = array();
    }
    $configuration['urls'] += array(
      'isAvailable' => 'http://api.jsdelivr.com/v1/jsdelivr/libraries/%s',
      'getInformation' => 'http://api.jsdelivr.com/v1/jsdelivr/libraries?name=%s&fields=name,mainfile,lastversion,description,homepage,github,author',
      'getVersions' => 'http://api.jsdelivr.com/v1/jsdelivr/libraries?name=%s&fields=versions',
      'getFiles' => 'http://api.jsdelivr.com/v1/jsdelivr/libraries?name=%s&fields=assets',
      'search' => 'http://api.jsdelivr.com/v1/jsdelivr/libraries?name=*%s*',
      'convertFiles' => '//cdn.jsdelivr.net/%s/%s/',
    );

    parent::__construct($configuration, $plugin_id, $plugin_definition, $drupal7);
  }

  /**
   * {@inheritdoc}
   */
  public function formatData($function, array $data = array()) {
    switch ($function) {
      case 'getVersions':
        return isset($data[0]) && isset($data[0]['versions']) ? $data[0]['versions'] : array();

      case 'getFiles':
        return isset($data[0]) && isset($data[0]['assets']) ? $data[0]['assets'] : array();

      case 'getLatestVersion':
        return isset($data['lastversion']) ? $data['lastversion'] : NULL;

      case 'getInformation':
        return isset($data[0]) ? $data[0] : array();

      default:
        return $data;
    }
  }

}
