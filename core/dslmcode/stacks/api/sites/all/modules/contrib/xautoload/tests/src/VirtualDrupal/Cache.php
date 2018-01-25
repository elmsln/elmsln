<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class Cache {

  /**
   * @var array[]
   */
  private $cache = array();

  /**
   * Replicates cache_get().
   *
   * @param string $cid
   * @param string $bin
   *
   * @return object|false
   *
   * @see cache_get()
   */
  function cacheGet($cid, $bin = 'cache') {
    if (!isset($this->cache[$bin][$cid])) {
      return FALSE;
    }
    return $this->cache[$bin][$cid];
  }

  /**
   * @param string $cid
   * @param mixed $data
   * @param string $bin
   *
   * @see cache_set()
   */
  function cacheSet($cid, $data, $bin = 'cache') {
    $this->cache[$bin][$cid] = (object)array(
      'data' => $data,
    );
  }

  /**
   * @param null $cid
   * @param null $bin
   *
   * @return mixed
   *
   * @see cache_clear_all()
   */
  function cacheClearAll($cid = NULL, $bin = NULL) {
    if (!isset($cid) && !isset($bin)) {
      $this->cacheClearAll(NULL, 'cache_page');
      return NULL;
    }
    elseif (!isset($cid)) {
      unset($this->cache[$bin]);
    }
    elseif (!isset($bin)) {
      throw new \InvalidArgumentException("No cache \$bin argument given.");
    }
    else {
      unset($this->cache[$bin][$cid]);
    }
  }

}
