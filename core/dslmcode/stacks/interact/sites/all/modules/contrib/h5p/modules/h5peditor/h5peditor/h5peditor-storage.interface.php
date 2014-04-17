<?php 

interface H5peditorStorage {
  /**
   * TODO
   */  
  public function getLanguage($machineName, $majorVersion, $minorVersion);

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
}
