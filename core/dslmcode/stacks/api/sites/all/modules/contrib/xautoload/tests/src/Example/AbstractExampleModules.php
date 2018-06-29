<?php


namespace Drupal\xautoload\Tests\Example;


use Drupal\xautoload\Tests\DrupalBootTest\AbstractDrupalBootTest;
use Drupal\xautoload\Tests\Filesystem\VirtualFilesystem;
use Drupal\xautoload\Tests\VirtualDrupal\ExampleModulesInterface;
use Drupal\xautoload\Tests\VirtualDrupal\PureFunctions;

abstract class AbstractExampleModules implements ExampleModulesInterface {

  /**
   * Replicates drupal_system_listing('/^' . DRUPAL_PHP_FUNCTION_PATTERN . '\.module$/', 'modules', 'name', 0)
   *
   * @see drupal_system_listing()
   *
   * @return object[]
   */
  public function drupalSystemListingModules() {
    $modules = array();
    foreach ($this->getAvailableExtensions() as $name => $type) {
      if ('module' !== $type) {
        continue;
      }
      $modules[$name] = (object)array(
        'uri' => $this->getExtensionFilename($type, $name),
        'filename' => $name . '.module',
        'name' => $name,
      );
    }
    return $modules;
  }

  /**
   * @return string[]
   *   Extension types by name.
   */
  abstract protected function getAvailableExtensions();

  /**
   * @return true[]
   */
  public function getBootstrapModules() {
    $bootstrap_modules = array();
    foreach ($this->discoverModuleFilenames('module') as $name => $filename) {
      $php = file_get_contents($filename);
      foreach (PureFunctions::bootstrapHooks() as $hook) {
        if (FALSE !== strpos($php, 'function ' . $name . '_' . $hook)) {
          $bootstrap_modules[$name] = TRUE;
          break;
        }
      }
    }
    return $bootstrap_modules;
  }

  /**
   * @param \Drupal\xautoload\Tests\DrupalBootTest\AbstractDrupalBootTest $testCase
   */
  public function assertLoadExampleClasses(AbstractDrupalBootTest $testCase) {
    foreach ($this->getExampleClasses() as $class) {
      $testCase->assertLoadClass($class);
    }
  }

  /**
   * @return array[]
   */
  abstract public function getExampleClasses();

  /**
   * @param string $type
   *   E.g. 'module'
   *
   * @return string[]
   */
  function discoverModuleFilenames($type) {
    $filenames = array();
    foreach ($this->getAvailableExtensions() as $name => $itemType) {
      if ($type !== $itemType) {
        continue;
      }
      $filenames[$name] = $this->getExtensionFilename($type, $name);
    }
    return $filenames;
  }

  /**
   * @param string $type
   * @param string $name
   *
   * @return string
   */
  public function getExtensionFilename($type, $name) {
    if ('xautoload' === $name) {
      return dirname(dirname(dirname(__DIR__))) . '/xautoload.module';
    }
    $file = dirname(dirname(__DIR__)) . '/fixtures/.modules/' . $name . '/' . $name . '.module';
    if (is_file($file)) {
      return $file;
    }
  }

} 
