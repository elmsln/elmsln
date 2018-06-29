<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


/**
 * Replicates module_list() with its static cache variables.
 */
class ModuleList {

  /**
   * @var DrupalGetFilename
   */
  private $drupalGetFilename;

  /**
   * @var SystemList
   */
  private $systemList;

  /**
   * @var array
   */
  private $list = array();

  /**
   * @var string[]
   */
  private $moduleListSorted;

  /**
   * @var DrupalStatic
   */
  private $drupalStatic;

  /**
   * @param DrupalGetFilename $drupalGetFilename
   * @param SystemList $systemList
   * @param DrupalStatic $drupalStatic
   */
  function __construct(DrupalGetFilename $drupalGetFilename, SystemList $systemList, DrupalStatic $drupalStatic) {
    $this->drupalGetFilename = $drupalGetFilename;
    $this->systemList = $systemList;
    $this->drupalStatic = $drupalStatic;
  }

  /**
   * Replicates module_list(FALSE, FALSE, $sort, $fixed_list)
   *
   * @param array $fixed_list
   * @param bool $sort
   *
   * @return string[]
   */
  function setModuleList($fixed_list, $sort = FALSE) {

    foreach ($fixed_list as $name => $module) {
      $this->drupalGetFilename->drupalSetFilename('module', $name, $module['filename']);
      $this->list[$name] = $name;
    }

    if ($sort) {
      return $this->moduleListSorted();
    }

    return $this->list;
  }

  /**
   * Replicates module_list($refresh, $bootstrap_refresh, $sort, NULL)
   *
   * @see module_list()
   *
   * @param bool $refresh
   * @param bool $bootstrap_refresh
   * @param bool $sort
   *
   * @return string[]
   */
  function moduleList($refresh = FALSE, $bootstrap_refresh = FALSE, $sort = FALSE) {

    if (empty($this->list) || $refresh) {
      $this->list = array();
      $sorted_list = NULL;
      if ($refresh) {
        // For the $refresh case, make sure that system_list() returns fresh
        // data.
        $this->drupalStatic->resetKey('system_list');
      }
      if ($bootstrap_refresh) {
        $this->list = $this->systemList->systemListBootstrap();
      }
      else {
        // Not using drupal_map_assoc() here as that requires common.inc.
        $this->list = array_keys($this->systemList->systemListModuleEnabled());
        $this->list = !empty($this->list)
          ? array_combine($this->list, $this->list)
          : array();
      }
    }

    if ($sort) {
      return $this->moduleListSorted();
    }

    if (count($this->list)) {
      # HackyLog::log($this->list);
    }

    return $this->list;
  }

  /**
   * @return string[]
   */
  private function moduleListSorted() {
    if (!isset($this->moduleListSorted)) {
      $this->moduleListSorted = $this->list;
      ksort($this->moduleListSorted);
    }
    return $this->moduleListSorted;
  }
} 
