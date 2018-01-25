<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


interface ExampleModulesInterface {

  /**
   * @param string $type
   *   E.g. 'module'
   *
   * @return string[]
   *   *.module paths by module name.
   */
  public function discoverModuleFilenames($type);

  /**
   * Replicates drupal_system_listing('/^' . DRUPAL_PHP_FUNCTION_PATTERN . '\.module$/', 'modules', 'name', 0)
   *
   * @see drupal_system_listing()
   *
   * @return object[]
   *   E.g. array('devel' => (object)array(
   *     'uri' => 'sites/all/modules/contrib/devel/devel.module',
   *     'filename' => 'devel.module',
   *     'name' => 'devel',
   *   ));
   */
  public function drupalSystemListingModules();

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
  public function drupalParseInfoFile($name);

  /**
   * @return true[]
   */
  public function getBootstrapModules();
}
