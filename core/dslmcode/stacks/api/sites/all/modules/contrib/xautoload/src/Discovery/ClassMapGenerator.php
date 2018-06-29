<?php


namespace Drupal\xautoload\Discovery;

class ClassMapGenerator implements ClassMapGeneratorInterface {

  /**
   * @param string[] $paths
   *
   * @return string[]
   */
  function wildcardPathsToClassmap($paths) {
    $files = $this->wildcardPathsToFiles($paths);

    return $this->filesToClassmap($files);
  }

  /**
   * @param string[] $files
   *
   * @return string[]
   */
  protected function filesToClassmap($files) {
    $map = array();
    foreach ($files as $file) {
      $classes = FileInspector::inspectPhpFile($file);
      foreach ($classes as $class) {
        $map[$class] = $file;
      }
    }

    return $map;
  }

  /**
   * @param string[] $paths
   *
   * @return string[]
   */
  protected function wildcardPathsToFiles($paths) {
    $wildcardFinder = new WildcardFileFinder();
    $wildcardFinder->addPaths($paths);

    return $wildcardFinder->getFiles();
  }
} 