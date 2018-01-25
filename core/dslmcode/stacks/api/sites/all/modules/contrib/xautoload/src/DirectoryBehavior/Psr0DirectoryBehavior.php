<?php


namespace Drupal\xautoload\DirectoryBehavior;

/**
 * Directory behavior for PSR-0.
 *
 * This class is a marker only, to be checked with instanceof.
 * @see \Drupal\xautoload\ClassFinder\GenericPrefixMap::loadClass()
 */
final class Psr0DirectoryBehavior implements DirectoryBehaviorInterface {
}
