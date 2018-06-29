<?php


namespace Drupal\xautoload\Tests\DrupalBootTest;

use Drupal\xautoload\Tests\VirtualDrupal\DrupalEnvironment;
use Drupal\xautoload\Tests\Example\ExampleModules;
use Drupal\xautoload\Tests\Filesystem\StreamWrapper;
use Drupal\xautoload\Tests\Util\CallLog;
use Drupal\xautoload\Tests\Util\StaticCallLog;

// Due to problems with @runTestsInSeparateProcesses and @preserveGlobalState,
// this file needs to be included manually.
require_once dirname(dirname(__DIR__)) . '/bootstrap.php';

/**
 * @runTestsInSeparateProcesses
 * @preserveGlobalState disabled
 */
class DrupalBootTest extends AbstractDrupalBootTest {

  /**
   * @param bool $install
   *
   * @return array[]
   *   Variations of modules being either
   *   - enabled (TRUE),
   *   - installed but disabled (FALSE), or
   *   - not installed (NULL).
   *   Structure: array(..., array(
   *     'system' => TRUE,
   *     'xautoload' => FALSE,
   *     'libraries' => NULL), ...)
   */
  private function initialModulesVariations($install) {
    $variations = array();
    $state = $install ? NULL : FALSE;
    $variation = array('system' => TRUE);
    $variation += array_fill_keys(array_keys($this->exampleModules->getExampleClasses()), $state);
    $variations[] = $variation;
    foreach (array('xautoload') as $module) {
      $variations = $this->providerArrayKeyVariations($variations, $module, array(TRUE, FALSE, NULL));
    }
    return $variations;
  }

  /**
   * @return array[]
   */
  public function providerModuleEnable() {
    $this->initOnce();
    $variations = array();
    foreach (array(TRUE, FALSE) as $install) {
      $expectedCalls = array();
      $enabledModulesSoFar = array();
      foreach ($this->exampleModules->getExampleClasses() as $module => $classes) {
        $enabledModulesSoFar[] = $module;
        if ($install) {
          $expectedCalls[] = array(
            'function' => $module . '_schema',
            'args' => array(),
          );
          $expectedCalls[] = array(
            'function' => $module . '_install',
            'args' => array(),
          );
          foreach ($enabledModulesSoFar as $module) {
            $expectedCalls[] = array(
              'function' => $module . '_watchdog',
              'args' => array(),
            );
          }
        }
        $expectedCalls[] = array(
          'function' => $module . '_enable',
          'args' => array(),
        );
        foreach ($enabledModulesSoFar as $module) {
          $expectedCalls[] = array(
            'function' => $module . '_watchdog',
            'args' => array(),
          );
        }
      }
      foreach ($this->initialModulesVariations($install) as $moduleStates) {
        /*
        $enabledModules = array();
        foreach ($moduleStates as $module => $state) {
          if (TRUE !== $state) {
            $enabledModules[$module] = TRUE;
          }
        }
        foreach ($enabledModulesSoFar as $module) {
          if (isset($enabledModules[$module])) {
            unset($enabledModules[$module]);
            $enabledModules[$module] = TRUE;
          }
        }
        $enabledModules = array_keys($enabledModules);
        */
        $variationExpectedCalls = $expectedCalls;
        foreach (array_keys($this->exampleModules->getExampleClasses()) as $module) {
          $variationExpectedCalls[] = array(
            'function' => $module . '_modules_enabled',
            'args' => array('(array)'),
          );
        }
        $variations[] = array($moduleStates, $variationExpectedCalls);
      }
    }

    return $variations;
  }

  function initOnce() {
    if (isset($this->exampleDrupal)) {
      return;
    }
    $this->exampleModules = new ExampleModules();
    $this->exampleDrupal = new DrupalEnvironment($this->exampleModules);
    $this->exampleDrupal->setStaticInstance();
  }

  /**
   * setUp() does not help us because of the process sharing problem.
   * So we use this instead.
   *
   * @throws \Exception
   */
  protected function prepare() {
    $this->initOnce();
    $filesystem = StreamWrapper::register('test');
    foreach ($this->exampleModules->discoverModuleFilenames('module') as $name => $filename) {
      $this->exampleDrupal->getSystemTable()->addModuleWithFilename($name, $filename);
    }
    $this->exampleDrupal->getSystemTable()->moduleSetEnabled('system');
    $this->exampleDrupal->initBootstrapStatus();
    # $this->exampleDrupal->getCache()->cacheSet('module_implements', $data, 'cache_bootstrap');
    xautoload()->getServiceContainer()->set('system', $this->exampleDrupal->getMockDrupalSystem());
    $this->callLog = new CallLog();
    StaticCallLog::setCallLog($this->callLog);
  }

  /**
   * @return array[]
   */
  protected function getExpectedCallsForNormalRequest() {
    $expectedCalls = array();
    foreach ($this->exampleModules->getExampleClasses() as $module => $classes) {
      $expectedCalls[] = array(
        'function' => $module . '_init',
        'args' => array(),
      );
    }
    return $expectedCalls;
  }
}
