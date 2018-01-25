<?php


namespace Drupal\xautoload\Tests\Example;


use Drupal\xautoload\Tests\DrupalBootTest\AbstractDrupalBootTest;
use Drupal\xautoload\Tests\Filesystem\VirtualFilesystem;

/**
 * @see DrupalBootHookTest
 */
class HookTestExampleModules extends AbstractExampleModules {

  /**
   * @return array[]
   */
  public function getAvailableExtensions() {
    return array_fill_keys(array(
        'system', 'xautoload', 'libraries',
        'testmod',
      ), 'module');
  }

  /**
   * @return string[]
   */
  public function getExampleClasses() {
    return array(
      'testmod' => array(
        'Drupal\\testmod\\Foo',
        'Acme\\TestLib\\Foo',
      ),
    );
  }

  /**
   * Replicates drupal_parse_info_file(dirname($module->uri) . '/' . $module->name . '.info')
   *
   * @see drupal_parse_info_file()
   *
   * @param string $name
   *
   * @return array
   *   Parsed info file contents.
   */
  public function drupalParseInfoFile($name) {
    $info = array('core' => '7.x');
    if ('testmod' === $name) {
      $info['dependencies'][] = 'xautoload';
      $info['dependencies'][] = 'libraries';
    }
    return $info;
  }

}
