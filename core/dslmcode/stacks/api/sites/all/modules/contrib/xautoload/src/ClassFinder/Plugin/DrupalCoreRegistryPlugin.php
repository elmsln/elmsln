<?php

namespace Drupal\xautoload\ClassFinder\Plugin;

use Drupal\xautoload\ClassFinder\InjectedApi\InjectedApiInterface;

/**
 * @see _registry_check_code()
 */
class DrupalCoreRegistryPlugin implements FinderPluginInterface {

  /**
   * @var string
   */
  private $baseDir;

  /**
   * @param string $baseDir
   */
  function __construct($baseDir) {
    $this->baseDir = $baseDir;
  }

  /**
   * Find the file for a class that in PSR-0 or PEAR would be in
   * $psr_0_root . '/' . $path_fragment . $path_suffix
   *
   * E.g.:
   *   - The class we look for is Some\Namespace\Some\Class
   *   - The file is actually in "exotic/location.php". This is not following
   *     PSR-0 or PEAR standard, so we need a plugin.
   *   -> The class finder will transform the class name to
   *     "Some/Namespace/Some/Class.php"
   *   - The plugin was registered for the namespace "Some\Namespace". This is
   *     because all those exotic classes all begin with Some\Namespace\
   *   -> The arguments will be:
   *     ($api = the API object, see below)
   *     $logical_base_path = "Some/Namespace/"
   *     $relative_path = "Some/Class.php"
   *     $api->getClass() gives the original class name, if we still need it.
   *   -> We are supposed to:
   *     if ($api->suggestFile('exotic/location.php')) {
   *       return TRUE;
   *     }
   *
   * @param InjectedApiInterface $api
   *   An object with a suggestFile() method.
   *   We are supposed to suggest files until suggestFile() returns TRUE, or we
   *   have no more suggestions.
   * @param string $logical_base_path_empty
   *   The key that this plugin was registered with.
   *   With trailing '/'.
   * @param string $relative_path_irrelevant
   *   Second part of the canonical path, ending with '.php'.
   *
   * @return bool|null
   *   TRUE, if the file was found.
   *   FALSE or NULL, otherwise.
   */
  function findFile($api, $logical_base_path_empty, $relative_path_irrelevant) {
    $q = db_select('registry');
    // Use LIKE here to make the query case-insensitive.
    $q->condition('name', db_like($api->getClass()), 'LIKE');
    $q->addField('registry', 'filename');
    $stmt = $q->execute();
    while ($relative_path = $stmt->fetchField()) {
      $file = $this->baseDir . $relative_path;
      // Attention: The db_select() above can trigger the class loader for
      // classes and interfaces of the database layer. This can cause some files
      // to be included twice, if the file defines more than one class.
      // So we need to use require_once here, instead of require. That is, use
      // guessFile() instead of claimFile().
      if ($api->guessFile($file)) {
        return TRUE;
      }
    }
    return FALSE;
  }
}
