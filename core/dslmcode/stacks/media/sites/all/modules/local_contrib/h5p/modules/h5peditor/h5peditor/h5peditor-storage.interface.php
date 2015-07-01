<?php

interface H5peditorStorage {
  /**
   * TODO
   */
  public function getLanguage($machineName, $majorVersion, $minorVersion, $language);

  /**
   * TODO
   */
  public function addTmpFile($file);

  /**
   * TODO
   */
  public function keepFile($oldPath, $newPath);

  /**
   * TODO
   */
  public function removeFile($path);

  /**
   * TODO
   */
  public function getLibraries($libraries = NULL);
  
  /**
   * Alter styles and scripts
   * 
   * @param array $files
   *  List of files as objects with path and version as properties
   * @param array $libraries
   *  List of libraries indexed by machineName with objects as values. The objects
   *  have majorVersion and minorVersion as properties.
   */
  public function alterLibraryFiles(&$files, $libraries);
}
