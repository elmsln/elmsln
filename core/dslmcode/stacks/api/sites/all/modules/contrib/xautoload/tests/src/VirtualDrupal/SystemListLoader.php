<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class SystemListLoader {

  /**
   * @var SystemTable
   */
  private $systemTable;

  /**
   * @param SystemTable $systemTable
   */
  function __construct(SystemTable $systemTable) {
    $this->systemTable = $systemTable;
  }

  /**
   * @return object[]
   */
  public function fetchBootstrapSystemList() {
    $bootstrapList = array();
    foreach ($this->systemTable->systemTableSortedObjects(NULL, 'module') as $name => $record) {
      if (1 == $record->status && 1 == $record->bootstrap) {
        $bootstrapList[$name] = (object)array(
          'name' => $record->name,
          'filename' => $record->filename,
        );
      }
    }
    return $bootstrapList;
  }

  /**
   * @see system_list()
   *
   * @return array[]
   */
  public function loadSystemLists() {

    $lists = array(
      'module_enabled' => array(),
      'theme' => array(),
      'filepaths' => array(),
    );

    // The module name (rather than the filename) is used as the fallback
    // weighting in order to guarantee consistent behavior across different
    // Drupal installations, which might have modules installed in different
    // locations in the file system. The ordering here must also be
    // consistent with the one used in module_implements().
    foreach ($this->systemTable->systemTableSortedObjects() as $record) {
      // Build a list of all enabled modules.
      if ($record->type == 'module') {
        if (1 != $record->status) {
          continue;
        }
        $lists['module_enabled'][$record->name] = $record;
      }
      // Build a list of themes.
      elseif ($record->type == 'theme') {
        $lists['theme'][$record->name] = $record;
      }
      else {
        continue;
      }
      // Build a list of filenames so drupal_get_filename can use it.
      if ($record->status) {
        $lists['filepaths'][] = array(
          'type' => $record->type,
          'name' => $record->name,
          'filepath' => $record->filename
        );
      }
    }

    $this->themesAddHierarchy($lists['theme']);

    return $lists;
  }

  /**
   * @param array $themes
   */
  private function themesAddHierarchy(array $themes) {
    foreach ($themes as $key => $theme) {
      if (!empty($theme->info['base theme'])) {
        // Make a list of the theme's base themes.
        $theme->base_themes = $this->drupalFindBaseThemes($themes, $key);
        // Don't proceed if there was a problem with the root base theme.
        if (!current($theme->base_themes)) {
          continue;
        }
        // Determine the root base theme.
        $base_key = key($theme->base_themes);
        // Add to the list of sub-themes for each of the theme's base themes.
        foreach (array_keys($theme->base_themes) as $base_theme) {
          $themes[$base_theme]->sub_themes[$key] = $theme->info['name'];
        }
        // Add the base theme's theme engine info.
        $theme->info['engine'] = isset($themes[$base_key]->info['engine'])
          ? $themes[$base_key]->info['engine']
          : 'theme';
      }
      else {
        // A plain theme is its own engine.
        $base_key = $key;
        if (!isset($theme->info['engine'])) {
          $theme->info['engine'] = 'theme';
        }
      }
      // Set the theme engine prefix.
      $theme->prefix = ($theme->info['engine'] == 'theme')
        ? $base_key
        : $theme->info['engine'];
    }
  }

  /**
   * Replicates drupal_find_base_themes()
   *
   * @param $themes
   * @param $key
   * @param array $used_keys
   *
   * @return array
   */
  private function drupalFindBaseThemes($themes, $key, $used_keys = array()) {
    $base_key = $themes[$key]->info['base theme'];
    // Does the base theme exist?
    if (!isset($themes[$base_key])) {
      return array($base_key => NULL);
    }

    $current_base_theme = array($base_key => $themes[$base_key]->info['name']);

    // Is the base theme itself a child of another theme?
    if (isset($themes[$base_key]->info['base theme'])) {
      // Do we already know the base themes of this theme?
      if (isset($themes[$base_key]->base_themes)) {
        return $themes[$base_key]->base_themes + $current_base_theme;
      }
      // Prevent loops.
      if (!empty($used_keys[$base_key])) {
        return array($base_key => NULL);
      }
      $used_keys[$base_key] = TRUE;
      return $this->drupalFindBaseThemes($themes, $base_key, $used_keys) + $current_base_theme;
    }
    // If we get here, then this is our parent theme.
    return $current_base_theme;
  }
} 
