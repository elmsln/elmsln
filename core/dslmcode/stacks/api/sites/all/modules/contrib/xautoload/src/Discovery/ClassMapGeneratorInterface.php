<?php


namespace Drupal\xautoload\Discovery;

interface ClassMapGeneratorInterface {

  /**
   * @param string[] $paths
   *
   * @return string[]
   */
  function wildcardPathsToClassmap($paths);
} 