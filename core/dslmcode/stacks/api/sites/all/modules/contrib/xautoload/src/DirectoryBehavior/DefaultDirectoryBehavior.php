<?php


namespace Drupal\xautoload\DirectoryBehavior;

/**
 * Directory behavior for PSR-4 and PEAR.
 *
 * This class is a marker only, to be checked with instanceof.
 * @see \Drupal\xautoload\ClassFinder\GenericPrefixMap::loadClass()
 */
final class DefaultDirectoryBehavior implements DirectoryBehaviorInterface {
}
