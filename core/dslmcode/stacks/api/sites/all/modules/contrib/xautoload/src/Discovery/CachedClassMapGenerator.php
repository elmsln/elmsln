<?php


namespace Drupal\xautoload\Discovery;

class CachedClassMapGenerator implements ClassMapGeneratorInterface {

  /**
   * @var ClassMapGeneratorInterface
   */
  protected $decorated;

  /**
   * @var \Drupal\xautoload\DrupalSystem\DrupalSystemInterface
   */
  protected $system;

  /**
   * @param ClassMapGeneratorInterface $decorated
   * @param \Drupal\xautoload\DrupalSystem\DrupalSystemInterface $system
   */
  function __construct($decorated, $system) {
    $this->decorated = $decorated;
    $this->system = $system;
  }

  /**
   * @param string[] $paths
   *
   * @return string[]
   */
  function wildcardPathsToClassmap($paths) {
    // Attempt to load from cache.
    $cid = 'xautoload:wildcardPathsToClassmap:' . md5(serialize($paths));
    $cache = $this->system->cacheGet($cid);
    if ($cache && isset($cache->data)) {
      return $cache->data;
    }
    // Resolve cache miss and save.
    $map = $this->decorated->wildcardPathsToClassmap($paths);
    $this->system->cacheSet($cid, $map);

    return $map;
  }
}
