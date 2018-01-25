<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class SystemUpdateBootstrapStatus {

  /**
   * @var SystemTable
   */
  private $systemTable;

  /**
   * @var HookSystem
   */
  private $hookSystem;

  /**
   * @var SystemListReset
   */
  private $systemListReset;

  /**
   * @param HookSystem $hookSystem
   * @param SystemTable $systemTable
   * @param SystemListReset $systemListReset
   */
  function __construct(HookSystem $hookSystem, SystemTable $systemTable, SystemListReset $systemListReset) {
    $this->hookSystem = $hookSystem;
    $this->systemTable = $systemTable;
    $this->systemListReset = $systemListReset;
  }

  /**
   * @see _system_update_bootstrap_status()
   */
  function systemUpdateBootstrapStatus() {
    $bootstrap_modules = array();
    foreach (PureFunctions::bootstrapHooks() as $hook) {
      foreach ($this->hookSystem->moduleImplements($hook) as $module) {
        $bootstrap_modules[$module] = TRUE;
      }
    }
    $this->systemTable->setBootstrapModules($bootstrap_modules);
    // Reset the cached list of bootstrap modules.
    $this->systemListReset->systemListReset();
  }
} 
