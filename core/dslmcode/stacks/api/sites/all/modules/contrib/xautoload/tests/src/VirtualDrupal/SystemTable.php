<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;



/**
 * Virtual Drupal database / persistence layer.
 *
 * This is not really a simulated database, but one abstraction level higher.
 */
class SystemTable {

  /**
   * Simulated system table.
   *
   * @var array[]
   */
  private $systemTableData = array();

  /**
   * @param string $module
   * @param string $filename
   *
   * @throws \Exception
   */
  function addModuleWithFilename($module, $filename) {
    $this->addModule($module, array('filename' => $filename));
  }

  /**
   * @param string $module
   * @param mixed[] $data
   *
   * @throws \Exception
   */
  function addModule($module, $data) {
    if (!isset($data['filename'])) {
      throw new \Exception("Missing filename in module data.");
    }
    if ($data['filename'] !== dirname($data['filename']) . '/' . $module . '.module') {
      throw new \Exception("Unexpected filename for module.");
    }
    $this->systemTableData[$module] = $data + array(
      'status' => 0,
      'bootstrap' => 0,
      'schema_version' => -1,
      'weight' => 0,
      'info' => NULL,
      'type' => 'module',
      'name' => $module,
    );
  }

  /**
   * @param string $module
   * @param string $dir
   *
   * @throws \Exception
   */
  function moduleSetDir($module, $dir) {
    if (!isset($this->systemTableData[$module])) {
      throw new \Exception("Unknown module '$module'.");
    }
    $filename = $dir . '/' . $module . '.module';
    $this->systemTableData[$module]['filename'] = $filename;
  }

  /**
   * @param string $module
   * @param string $filename
   *
   * @throws \Exception
   */
  function moduleSetFilename($module, $filename) {
    if (!isset($this->systemTableData[$module])) {
      throw new \Exception("Unknown module '$module'.");
    }
    $this->systemTableData[$module]['filename'] = $filename;
  }

  /**
   * @param string $module
   *
   * @throws \Exception
   */
  function moduleSetEnabled($module) {
    if (!isset($this->systemTableData[$module])) {
      throw new \Exception("Unknown module '$module'.");
    }
    $this->systemTableData[$module]['status'] = 1;
  }

  /**
   * @param string $module
   * @param int $version
   *
   * @throws \Exception
   */
  public function moduleSetSchemaVersion($module, $version) {
    if (!isset($this->systemTableData[$module])) {
      throw new \Exception("Unknown module '$module'.");
    }
    $this->systemTableData[$module]['schema_version'] = $version;
  }

  /**
   * @return string[]
   *   Extension type by extension name.
   */
  function getActiveExtensions() {
    $activeExtensions = array();
    foreach ($this->systemTableData as $module => $data) {
      if (1 === $data['status']) {
        $activeExtensions[$module] = $data['type'];
      }
    }
    return $activeExtensions;
  }

  /**
   * Load module data/status from the system table.
   *
   * @param $module
   *
   * @return array|null
   */
  function moduleGetData($module) {
    if (!isset($this->systemTableData[$module])) {
      return NULL;
    }
    return $this->systemTableData[$module];
  }

  /**
   * @param string $module
   *
   * @return string|null
   */
  function moduleGetFilename($module) {
    if (!isset($this->systemTableData[$module])) {
      return NULL;
    }
    return $this->systemTableData[$module]['filename'];
  }

  /**
   * @param string $module
   *
   * @return int
   * @throws \Exception
   */
  function moduleGetStatus($module) {
    if (!isset($this->systemTableData[$module])) {
      throw new \Exception("Unknown module '$module'.");
    }
    return $this->systemTableData[$module]['status'];
  }

  /**
   * @param string $module
   *
   * @return int
   * @throws \Exception
   */
  function moduleGetSchemaVersion($module) {
    if (!isset($this->systemTableData[$module])) {
      throw new \Exception("Unknown module '$module'.");
    }
    return $this->systemTableData[$module]['schema_version'];
  }

  /**
   * @param string[]|null $fields
   * @param string|null $type
   *
   * @return array
   */
  public function systemTableObjects(array $fields = NULL, $type = NULL) {
    $objects = array();
    foreach ($this->systemTableData as $name => $record) {
      if (NULL !== $type && $type !== $record['type']) {
        continue;
      }
      $objects[$name] = $this->makeObject($record, $fields);
    }
    return $objects;
  }

  /**
   * @param string[] $fields
   * @param string|null $type
   *
   * @return object[]
   */
  public function systemTableSortedObjects(array $fields = NULL, $type = NULL) {
    $byWeight = array();
    foreach ($this->systemTableData as $name => $record) {
      if (NULL !== $type && $type !== $record['type']) {
        continue;
      }
      $byWeight[$record['weight']][$name] = $this->makeObject($record, $fields);
    }
    ksort($byWeight);
    $sorted = array();
    foreach ($byWeight as $records) {
      ksort($records);
      $sorted += $records;
    }
    return $sorted;
  }

  /**
   * @param $array
   * @param array $fields
   *
   * @return \stdClass
   */
  private function makeObject($array, array $fields = NULL) {
    if (!isset($fields)) {
      return (object)$array;
    }
    $object = new \stdClass;
    foreach ($fields as $field) {
      $object->$field = $array[$field];
    }
    return $object;
  }

  /**
   * Retrieves the current status of an array of files in the system table.
   *
   * @see system_get_files_database()
   *
   * @param object[] $files
   * @param string $type
   *   E.g. 'module'
   */
  public function systemGetFilesDatabase($files, $type) {
    $fields = array('filename', 'name', 'type', 'status', 'schema_version', 'weight');
    foreach ($this->systemTableObjects($fields) as $file) {
      if ($type !== $file->type) {
        continue;
      }
      if (!isset($files[$file->name]) || !is_object($files[$file->name])) {
        continue;
      }
      $file->uri = $file->filename;
      foreach ($file as $key => $value) {
        if (!isset($files[$file->name]->$key)) {
          $files[$file->name]->$key = $value;
        }
      }
    }
  }

  /**
   * @see system_update_files_database()
   *
   * @param object[] $files
   * @param string $type
   */
  public function systemUpdateFilesDatabase(&$files, $type) {

    // Add all files that need to be deleted to a DatabaseCondition.
    foreach ($this->systemTableObjects(NULL, $type) as $record) {
      if (isset($files[$record->name]) && is_object($files[$record->name])) {
        $file = $files[$record->name];
        // Scan remaining fields to find only the updated values.
        foreach ($record as $key => $oldvalue) {
          if (isset($file->$key)) {
            $this->systemTableData[$record->name][$key] = $file->$key;
          }
        }
        // Indicate that the file exists already.
        $file->exists = TRUE;
      }
      else {
        // File is not found in file system, so delete record from the system table.
        unset($this->systemTableData[$record->name]);
      }
    }

    // All remaining files are not in the system table, so we need to add them.
    foreach ($files as $name => $file) {
      if (isset($file->exists)) {
        unset($file->exists);
      }
      else {
        $this->systemTableData[$name] = array(
          'filename' => $file->uri,
          'name' => $file->name,
          'type' => $type,
          'owner' => isset($file->owner) ? $file->owner : '',
          'info' => $file->info,
          'status' => 0,
          'bootstrap' => 0,
          'schema_version' => -1,
          'weight' => 0,
        );
        $file->type = $type;
        $file->status = 0;
        $file->schema_version = -1;
      }
    }
  }

  /**
   * @param true[] $bootstrap_modules
   */
  public function setBootstrapModules($bootstrap_modules) {
    foreach ($this->systemTableData as $name => $record) {
      $record['bootstrap'] = empty($bootstrap_modules[$name]) ? 0 : 1;
    }
  }

  /**
   * @param string $name
   * @param int $weight
   *
   * @throws \Exception
   */
  public function moduleSetWeight($name, $weight) {
    if (!isset($this->systemTableData[$name])) {
      throw new \Exception("Unknown module '$name'.");
    }
    $this->systemTableData[$name]['weight'] = $weight;
  }
} 
