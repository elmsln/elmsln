<?php

namespace Drupal\xautoload;

/**
 * A number of static methods that don't interact with any global state.
 */
class Util {

  /**
   * Generate a random string made of uppercase and lowercase characters and numbers.
   *
   * @param int $length
   *   Length of the random string to generate
   * @param string $chars
   *   Allowed characters
   * @param string $chars_first
   *   Allowed characters for the first character.
   *
   * @return string
   *   Random string of the specified length
   */
  static function randomString($length = 30, $chars = NULL, $chars_first = NULL) {

    if (!isset($chars)) {
      $chars = 'abcdefghijklmnopqrstuvwxyz' .
        'ABCDEFGHIJKLMNOPQRSTUVWXYZ' .
        '1234567890';
    }

    if (!isset($chars_first)) {
      $chars_first = $chars;
    }

    // Initialize the randomizer.
    srand((double) microtime() * 1000000);

    $str = substr($chars_first, rand() % strlen($chars_first), 1);
    for ($i = 0; $i < $length; ++$i) {
      $str .= substr($chars, rand() % strlen($chars), 1);
    }

    return $str;
  }

  /**
   * Generate a random string that is a valid PHP identifier.
   *
   * @param int $length
   *   Length of the random string to generate
   *
   * @return string
   *   Random string of the specified length
   */
  static function randomIdentifier($length = 40) {

    // Since PHP is case insensitive, we only user lowercase characters.
    $chars_first = 'abcdefghijklmnopqrstuvwxyz_';
    $chars = 'abcdefghijklmnopqrstuvwxyz_1234567890';

    return self::randomString($length, $chars, $chars_first);
  }

  /**
   * Generate a random string that is a stream wrapper protocol.
   *
   * @param int $length
   *   Length of the random string to generate
   *
   * @return string
   *   Random string of the specified length
   */
  static function randomProtocol($length = 40) {

    // Since PHP is case insensitive, we only user lowercase characters.
    $chars_first = 'abcdefghijklmnopqrstuvwxyz_';
    $chars = 'abcdefghijklmnopqrstuvwxyz_1234567890';

    return self::randomString($length, $chars, $chars_first);
  }

  /**
   * Get a string representation of a callback for debug purposes.
   *
   * @param callback $callback
   *   A PHP callback, which could be an array or a string.
   *
   * @return string
   *   A string representation to be displayed to a user, e.g.
   *   "Foo::staticMethod()", or "Foo->bar()"
   */
  static function callbackToString($callback) {
    if (is_array($callback)) {
      list($obj, $method) = $callback;
      if (is_object($obj)) {
        $str = get_class($obj) . '->' . $method . '()';
      }
      else {
        $str = $obj . '::';
        $str .= $method . '()';
      }
    }
    else {
      $str = $callback;
    }

    return $str;
  }

  /**
   * Convert the underscores of a prefix into directory separators.
   *
   * @param string $prefix
   *   Prefix, without trailing underscore.
   *
   * @return string
   *   Path fragment representing the prefix, with trailing '/'.
   */
  static function prefixLogicalPath($prefix) {
    if (!strlen($prefix)) {
      return '';
    }
    $pear_logical_path = str_replace('_', '/', rtrim($prefix, '_') . '_');
    // Clean up surplus '/' resulting from duplicate underscores, or an
    // underscore at the beginning of the class.
    while (FALSE !== $pos = strrpos('/' . $pear_logical_path, '//')) {
      $pear_logical_path{$pos} = '_';
    }

    return $pear_logical_path;
  }

  /**
   * Replace the namespace separator with directory separator.
   *
   * @param string $namespace
   *   Namespace without trailing namespace separator.
   *
   * @return string
   *   Path fragment representing the namespace, with trailing '/'.
   */
  static function namespaceLogicalPath($namespace) {
    return
      strlen($namespace)
        ? str_replace('\\', '/', rtrim($namespace, '\\') . '\\')
        : '';
  }

  /**
   * Check if a file exists, considering the full include path.
   * Return the resolved path to that file.
   *
   * @param string $file
   *   The filepath
   * @return boolean|string
   *   The resolved file path, if the file exists in the include path.
   *   FALSE, otherwise.
   */
  static function findFileInIncludePath($file) {
    if (function_exists('stream_resolve_include_path')) {
      // Use the PHP 5.3.1+ way of doing this.
      return stream_resolve_include_path($file);
    }
    elseif ($file{0} === '/') {
      // That's an absolute path already.
      return file_exists($file)
        ? $file
        : FALSE;
    }
    else {
      // Manually loop all candidate paths.
      foreach (explode(PATH_SEPARATOR, get_include_path()) as $base_dir) {
        if (file_exists($base_dir . '/' . $file)) {
          return $base_dir . '/' . $file;
        }
      }

      return FALSE;
    }
  }

  /**
   * Checks whether an identifier is defined as either a class, interface or
   * trait. Does not trigger autoloading.
   *
   * @param string $class
   * @return bool
   */
  static function classIsDefined($class) {
    return class_exists($class, FALSE)
    || interface_exists($class, FALSE)
    || (PHP_VERSION_ID >= 50400 && trait_exists($class, FALSE));
  }

  /**
   * Dummy method to force autoloading this class (or an ancestor).
   */
  static function forceAutoload() {
    // Do nothing.
  }
}

