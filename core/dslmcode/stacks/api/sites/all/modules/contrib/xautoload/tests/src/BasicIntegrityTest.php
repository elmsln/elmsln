<?php


namespace Drupal\xautoload\Tests;

/**
 * A test class to verify that all class files work well across PHP versions.
 */
class BasicIntegrityTest extends \PHPUnit_Framework_TestCase {

  /**
   * Tests that all classes in the lib/ folder can be included without conflict.
   */
  public function testIncludeAll() {
    $lib = dirname(dirname(__DIR__)) . '/lib';
    $skip = array($lib . '/Drupal');
    $this->includeAllRecursivePsr4($lib, 'Drupal\xautoload', $skip);
  }

  /**
   * @param string $dir
   * @param string $namespace
   * @param array $skip
   *
   * @throws \Exception
   */
  private function includeAllRecursivePsr4($dir, $namespace, array $skip) {
    foreach (scandir($dir) as $candidate) {
      if ('.' === $candidate || '..' === $candidate) {
        continue;
      }
      $path = $dir . '/' . $candidate;
      if (in_array($path, $skip)) {
        continue;
      }
      if (is_dir($path)) {
        $this->includeAllRecursivePsr4($dir . '/' . $candidate, $namespace . '\\' . $candidate, $skip);
      }
      elseif (is_file($path)) {
        if ('.php' === substr($candidate, -4)) {
          $class = $namespace . '\\' . substr($candidate, 0, -4);
          if (class_exists($class)) {
            continue;
          }
          if (interface_exists($class)) {
            continue;
          }
          if (function_exists('trait_exists') && trait_exists($class)) {
            continue;
          }
          throw new \Exception("Non-existing class, trait or interface '$class'.");
        }
      }
    }
  }
} 
