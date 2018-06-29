<?php


namespace Drupal\xautoload\Libraries;


use Drupal\xautoload\CacheMissObserver\CacheMissObserverInterface;
use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;

class LibraryCacheMissObserver implements CacheMissObserverInterface {

  /**
   * @var callable
   */
  private $callable;

  /**
   * @var string
   */
  private $path;

  /**
   * @param callable $callable
   * @param string $path
   */
  function __construct($callable, $path) {
    $this->callable = $callable;
    $this->path = $path;
  }

  /**
   * Executes the operation.
   *
   * This method will only be called if and when the "real" class finder is
   * initialized.
   *
   * @param ExtendedClassFinderInterface $finder
   *   The class finder.
   */
  function cacheMiss($finder) {
    $adapter = \xautoload_InjectedAPI_hookXautoload::create($finder, $this->path);
    call_user_func($this->callable, $adapter, $this->path);
  }

} 
