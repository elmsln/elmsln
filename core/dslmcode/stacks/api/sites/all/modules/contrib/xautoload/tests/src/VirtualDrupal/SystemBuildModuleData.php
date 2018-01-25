<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class SystemBuildModuleData {

  /**
   * @var ExampleModulesInterface
   */
  private $exampleModules;

  /**
   * @var HookSystem
   */
  private $hookSystem;

  /**
   * @param ExampleModulesInterface $exampleModules
   * @param HookSystem $hookSystem
   */
  function __construct(ExampleModulesInterface $exampleModules, HookSystem $hookSystem) {
    $this->exampleModules = $exampleModules;
    $this->hookSystem = $hookSystem;
  }

  /**
   * Scans and collects module .info data.
   *
   * @see _system_rebuild_module_data()
   *
   * @return object[]
   */
  public function systemBuildModuleData() {
    // Find modules
    $modules = $this->exampleModules->drupalSystemListingModules();

    if (FALSE) {
      // Include the installation profile in modules that are loaded.
      $profile = 'minimal';
      $modules[$profile] = new \stdClass();
      $modules[$profile]->name = $profile;
      $modules[$profile]->uri = 'profiles/' . $profile . '/' . $profile . '.profile';
      $modules[$profile]->filename = $profile . '.profile';

      // Installation profile hooks are always executed last.
      $modules[$profile]->weight = 1000;
    }
    else {
      $profile = 'NO_PROFILE';
    }

    // Set defaults for module info.
    $defaults = array(
      'dependencies' => array(),
      'description' => '',
      'package' => 'Other',
      'version' => NULL,
      # 'php' => DRUPAL_MINIMUM_PHP,
      'files' => array(),
      'bootstrap' => 0,
    );

    // Read info files for each module.
    foreach ($modules as $key => $module) {
      // The module system uses the key 'filename' instead of 'uri' so copy the
      // value so it will be used by the modules system.
      $modules[$key]->filename = $module->uri;

      // Look for the info file.
      $module->info = $this->exampleModules->drupalParseInfoFile($module->name);

      // Skip modules that don't provide info.
      if (empty($module->info)) {
        unset($modules[$key]);
        continue;
      }

      // Merge in defaults and save.
      $modules[$key]->info = $module->info + $defaults;

      // Installation profiles are hidden by default, unless explicitly specified
      // otherwise in the .info file.
      if ($key == $profile && !isset($modules[$key]->info['hidden'])) {
        $modules[$key]->info['hidden'] = TRUE;
      }

      // Invoke hook_system_info_alter() to give installed modules a chance to
      // modify the data in the .info files if necessary.
      $type = 'module';
      $this->hookSystem->drupalAlter('system_info', $modules[$key]->info, $modules[$key], $type);
    }

    if (isset($modules[$profile])) {
      // The installation profile is required, if it's a valid module.
      $modules[$profile]->info['required'] = TRUE;
      // Add a default distribution name if the profile did not provide one. This
      // matches the default value used in install_profile_info().
      if (!isset($modules[$profile]->info['distribution_name'])) {
        $modules[$profile]->info['distribution_name'] = 'Drupal';
      }
    }

    unset($modules['NO_PROFILE']);

    return $modules;
  }

} 
