<?php

namespace Drupal\xautoload\Libraries;


class LibrariesPreLoadCallback {

  /**
   * @var callable
   *   A callable that is serializable, so not a closure.
   *   Can be a SerializableClosureWrapper.
   */
  private $callable;

  /**
   * @param callable $callable
   */
  function __construct($callable) {
    $this->callable = $callable;
  }

  /**
   * Callback that is applied directly before the library is loaded. At this
   * point the library contains variant-specific information, if specified. Note
   * that in this group the 'variants' property is no longer available.
   *
   * @param array $library
   *   An array of library information belonging to the top-level library, a
   *   specific version, a specific variant or a specific variant of a specific
   *   version. Because library information such as the 'files' property (see
   *   above) can be declared in all these different locations of the library
   *   array, but a callback may have to act on all these different parts of the
   *   library, it is called recursively for each library with a certain part of
   *   the libraries array passed as $library each time.
   * @param string|null $version
   *   If the $library array belongs to a certain version (see above), a string
   *   containing the version. This argument may be empty, so NULL should be
   *   specified as the default value.
   * @param string|null $variant
   *   If the $library array belongs to a certain variant (see above), a string
   *   containing the variant name. This argument may be empty, so NULL should
   *   be specified as the default value.
   */
  function __invoke($library, $version, $variant) {
    if (!empty($library['installed'])) {
      xautoload()->proxyFinder->observeFirstCacheMiss(
        new LibraryCacheMissObserver($this->callable, $library['library path']));
    }
  }

}
