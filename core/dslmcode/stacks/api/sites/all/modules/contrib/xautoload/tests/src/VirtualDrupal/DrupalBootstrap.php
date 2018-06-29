<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;



class DrupalBootstrap {

  /**
   * @var HookSystem
   */
  private $hookSystem;

  /**
   * @var ModuleList
   */
  private $moduleList;

  /**
   * @var DrupalLoad
   */
  private $drupalLoad;

  /**
   * Replicates the static $has_run in module_load_all()
   *
   * @var bool
   */
  private $moduleLoadAllHasRun = FALSE;

  /**
   * @param DrupalLoad $drupalLoad
   * @param HookSystem $hookSystem
   * @param ModuleList $moduleList
   */
  function __construct(DrupalLoad $drupalLoad, HookSystem $hookSystem, ModuleList $moduleList) {
    $this->drupalLoad = $drupalLoad;
    $this->hookSystem = $hookSystem;
    $this->moduleList = $moduleList;
  }

  /**
   * @see drupal_bootstrap()
   */
  function boot() {
    $this->drupalBootstrapVariables();
    $this->drupalBootstrapPageHeader();
    $this->drupalBootstrapFull();
  }

  /**
   * @see _drupal_bootstrap_variables()
   */
  private function drupalBootstrapVariables() {
    $this->moduleLoadAll(TRUE);
  }

  /**
   * @see _drupal_bootstrap_page_header()
   */
  private function drupalBootstrapPageHeader() {
    $this->bootstrapInvokeAll('boot');
  }

  /**
   * @see _drupal_bootstrap_full()
   */
  private function drupalBootstrapFull() {
    $this->moduleLoadAll();
    $this->menuSetCustomTheme();
    $this->hookSystem->moduleInvokeAll('init');
  }

  /**
   * @see menu_set_custom_theme()
   */
  private function menuSetCustomTheme() {
    $this->hookSystem->moduleInvokeAll('custom_theme');
  }

  /**
   * Replicates module_load_all()
   *
   * @see module_load_all()
   *
   * @param bool|null $bootstrap
   *
   * @return bool
   */
  private function moduleLoadAll($bootstrap = FALSE) {
    if (isset($bootstrap)) {
      foreach ($this->moduleList->moduleList(TRUE, $bootstrap) as $module) {
        $this->drupalLoad->drupalLoad('module', $module);
      }
      // $has_run will be TRUE if $bootstrap is FALSE.
      $this->moduleLoadAllHasRun = !$bootstrap;
    }
    return $this->moduleLoadAllHasRun;
  }

  /**
   * @see bootstrap_invoke_all()
   *
   * @param string $hook
   */
  private function bootstrapInvokeAll($hook) {
    // Bootstrap modules should have been loaded when this function is called, so
    // we don't need to tell module_list() to reset its internal list (and we
    // therefore leave the first parameter at its default value of FALSE). We
    // still pass in TRUE for the second parameter, though; in case this is the
    // first time during the bootstrap that module_list() is called, we want to
    // make sure that its internal cache is primed with the bootstrap modules
    // only.
    foreach ($this->moduleList->moduleList(FALSE, TRUE) as $module) {
      $this->drupalLoad->drupalLoad('module', $module);
      PureFunctions::moduleInvoke($module, $hook);
    }
  }
} 
