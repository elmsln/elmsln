<?php


namespace Drupal\xautoload\Tests\DrupalBootTest;


use Drupal\xautoload\Tests\Example\HookTestExampleModules;
use Drupal\xautoload\Tests\VirtualDrupal\DrupalEnvironment;
use Drupal\xautoload\Tests\Filesystem\StreamWrapper;
use Drupal\xautoload\Tests\Util\CallLog;
use Drupal\xautoload\Tests\Util\StaticCallLog;

// Due to problems with @runTestsInSeparateProcesses and @preserveGlobalState,
// this file needs to be included manually.
require_once dirname(dirname(__DIR__)) . '/bootstrap.php';

/**
 * Tests modules that use hook_xautoload() and hook_libraries_info()
 *
 * @runTestsInSeparateProcesses
 * @preserveGlobalState disabled
 *
 * @see HookTestExampleModules
 */
class DrupalBootHookTest extends AbstractDrupalBootTest {

  /**
   * @return array[]
   */
  public function providerModuleEnable() {
    $hookXautoloadEarly = FALSE;
    $hookXautoloadLate = TRUE;
    $initialModuleVariations = array(array('system' => TRUE));
    foreach (array(
      'xautoload' => array(FALSE, TRUE),
      'libraries' => array(FALSE, TRUE),
      'testmod' => array(FALSE, NULL),
    ) as $module => $states) {
      $initialModuleVariations = $this->providerArrayKeyVariations($initialModuleVariations, $module, $states);
    }
    $variations = array();
    foreach ($initialModuleVariations as $initialModuleVariation) {
      $expectedCalls = array();

      if ($hookXautoloadEarly) {
        $expectedCalls[] = array(
          'function' => 'testmod_xautoload',
          'args' => array(
            '(xautoload_InjectedAPI_hookXautoload)',
            dirname(dirname(__DIR__)) . '/fixtures/.modules/testmod',
          ),
        );
      }

      if (NULL === $initialModuleVariation['testmod']) {
        $expectedCalls[] = array(
          'function' => 'testmod_schema',
          'args' => array(),
        );
        $expectedCalls[] = array(
          'function' => 'testmod_install',
          'args' => array(),
        );
        $expectedCalls[] = array(
          'function' => 'testmod_watchdog',
          'args' => array(),
        );
      }

      $expectedCalls[] = array(
        'function' => 'testmod_enable',
        'args' => array(),
      );
      $expectedCalls[] = array(
        'function' => 'testmod_watchdog',
        'args' => array(),
      );

      if ($hookXautoloadLate) {
        $expectedCalls[] = array(
          'function' => 'testmod_xautoload',
          'args' => array(
            '(xautoload_InjectedAPI_hookXautoload)',
            dirname(dirname(__DIR__)) . '/fixtures/.modules/testmod',
          ),
        );
      }
      $expectedCalls[] = array(
        'function' => 'testmod_modules_enabled',
        'args' => array(
          '(array)'
        ),
      );
      $expectedCalls[] = array(
        'function' => 'testmod_libraries_info',
        'args' => array(),
      );
      $expectedCalls[] = array(
        'function' => '_testmod_libraries_testlib_xautoload',
        'args' => array(
          '(xautoload_InjectedAPI_hookXautoload)',
          dirname(dirname(__DIR__)) . '/fixtures/.libraries/testlib',
        ),
      );

      $variations[] = array($initialModuleVariation, $expectedCalls);
    }
    return $variations;
  }

  function initOnce() {
    if (isset($this->exampleDrupal)) {
      return;
    }
    $this->exampleModules = new HookTestExampleModules();
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
    $expectedCalls = array(
      array(
        'function' => 'testmod_xautoload',
        'args' => array(
          '(xautoload_InjectedAPI_hookXautoload)',
          dirname(dirname(__DIR__)) . '/fixtures/.modules/testmod',
          # 'test://modules/testmod',
        ),
      ),
      array(
        'function' => 'testmod_init',
        'args' => array(),
      ),
      array(
        'function' => 'testmod_libraries_info',
        'args' => array(),
      ),
      array(
        'function' => '_testmod_libraries_testlib_xautoload',
        'args' => array(
          '(xautoload_InjectedAPI_hookXautoload)',
          dirname(dirname(__DIR__)) . '/fixtures/.libraries/testlib',
          # 'test://libraries/testlib',
        ),
      ),
    );
    return $expectedCalls;
  }
} 
