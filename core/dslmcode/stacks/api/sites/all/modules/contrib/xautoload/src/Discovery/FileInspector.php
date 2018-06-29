<?php

namespace Drupal\xautoload\Discovery;

use RuntimeException;

class FileInspector {

  /**
   * @param string $path
   * @return string[]
   * @throws RuntimeException
   */
  static function inspectPhpFile($path) {
    try {
      $contents = php_strip_whitespace($path);
    } catch (\Exception $e) {
      throw new \RuntimeException(
        'Could not scan for classes inside ' . $path . ": \n" . $e->getMessage(),
        // The Exception code. Defaults to 0.
        0,
        // The previous exception used for exception chaining.
        $e);
    }

    return self::inspectFileContents($contents);
  }

  /**
   * @param string $contents
   *   The PHP file contents obtained with php_strip_whitespace($path).
   *
   * @return string[]
   *   Classes discovered in the file.
   */
  protected static function inspectFileContents($contents) {
    $traits = version_compare(PHP_VERSION, '5.4', '<')
      ? ''
      : '|trait';

    // return early if there is no chance of matching anything in this file
    if (!preg_match('{\b(?:class|interface' . $traits . ')\s}i', $contents)) {
      return array();
    }

    // strip heredocs/nowdocs
    $contents = preg_replace(
      '{<<<\'?(\w+)\'?(?:\r\n|\n|\r)(?:.*?)(?:\r\n|\n|\r)\\1(?=\r\n|\n|\r|;)}s',
      'null',
      $contents);

    // strip strings
    $contents = preg_replace(
      '{"[^"\\\\]*(\\\\.[^"\\\\]*)*"|\'[^\'\\\\]*(\\\\.[^\'\\\\]*)*\'}s',
      'null',
      $contents);

    // strip leading non-php code if needed
    if (substr($contents, 0, 2) !== '<?') {
      $contents = preg_replace('{^.+?<\?}s', '<?', $contents);
    }

    // strip non-php blocks in the file
    $contents = preg_replace('{\?>.+<\?}s', '?><?', $contents);

    // strip trailing non-php code if needed
    $pos = strrpos($contents, '?>');
    if (FALSE !== $pos && FALSE === strpos(substr($contents, $pos), '<?')) {
      $contents = substr($contents, 0, $pos);
    }

    preg_match_all(
      '{
                  (?:
                       \b(?<![\$:>])(?P<type>class|interface' . $traits . ') \s+ (?P<name>[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*)
               | \b(?<![\$:>])(?P<ns>namespace) (?P<nsname>\s+[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*(?:\s*\\\\\s*[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*)*)? \s*[\{;]
            )
        }ix',
      $contents,
      $matches
    );

    $classes = array();
    $namespace = '';

    for ($i = 0, $len = count($matches['type']); $i < $len; $i++) {
      if (!empty($matches['ns'][$i])) {
        $namespace = str_replace(array(' ', "\t", "\r", "\n"), '', $matches['nsname'][$i])
          . '\\';
      }
      else {
        $classes[] = ltrim($namespace . $matches['name'][$i], '\\');
      }
    }

    return $classes;
  }
} 
