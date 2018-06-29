<?php

namespace Drupal\xautoload\ClassLoader;

use Drupal\xautoload\ClassFinder\ClassFinderInterface;

/**
 * Behaves mostly like the Symfony ClassLoader classes.
 */
abstract class AbstractClassLoaderDecorator extends AbstractClassLoader {

  /**
   * @var ClassFinderInterface
   */
  protected $finder;

  /**
   * @param ClassFinderInterface $finder
   *   The object that does the actual class finding.
   */
  protected function __construct($finder) {
    $this->finder = $finder;
  }

  /**
   * Replace the finder with another one.
   *
   * @param ClassFinderInterface $finder
   *   The object that does the actual class finding.
   */
  function setFinder($finder) {
    $this->finder = $finder;
  }

  /**
   * {@inheritdoc}
   */
  function loadClass($class) {
    $this->finder->loadClass($class);
  }
}
