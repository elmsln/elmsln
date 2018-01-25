<?php

namespace Drupal\xautoload\ClassFinder\InjectedApi;

use Drupal\xautoload\Util;

/**
 * To help testability, we use an injected API instead of just a return value.
 * The injected API can be mocked to provide a mocked file_exists(), and to
 * monitor all suggested candidates, not just the correct return value.
 */
class FindFileInjectedApi extends AbstractInjectedApi {

  /**
   * @var string
   *   The file that was found.
   */
  protected $file;

  /**
   * When the process has finished, use this to return the result.
   *
   * @return string
   *   The file that is supposed to declare the class.
   */
  function getFile() {
    return $this->file;
  }

  /**
   * Suggest a file that, if the file exists,
   * has to declare the class we are looking for.
   * Only keep the class on success.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return bool
   *   TRUE, if the file exists.
   *   FALSE, otherwise.
   */
  function suggestFile($file) {
    if (file_exists($file)) {
      $this->file = $file;
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Same as suggestFile(), but skip the file_exists(),
   * assuming that we already know the file exists.
   *
   * This could make sense if a plugin already did the file_exists() check.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return bool
   *   TRUE, if the file was found - which is always.
   */
  function suggestFile_skipFileExists($file) {
    $this->file = $file;
    return TRUE;
  }

  /**
   * Same as suggestFile(), but assume that file_exists() returns TRUE.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return bool
   *   TRUE, if the file was found - which is always.
   */
  function suggestFile_checkNothing($file) {
    $this->file = $file;
    return TRUE;
  }

  /**
   * Same as suggestFile(), but check the full PHP include path.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return bool
   *   TRUE, if the file exists.
   *   FALSE, otherwise.
   */
  function suggestFile_checkIncludePath($file) {
    if (FALSE !== $file = Util::findFileInIncludePath($file)) {
      $this->file = $file;
      return TRUE;
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  function guessFile($file) {
    // The file must be included, or else we can't know if it defines the class.
    require_once $file;
    if (Util::classIsDefined($this->className)) {
      $this->file = $file;
      return TRUE;
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  function guessPath($file) {
    if (file_exists($file)) {
      // The file must be included, or else we can't know if it defines the class.
      require_once $file;
      if (Util::classIsDefined($this->className)) {
        $this->file = $file;
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  function claimFile($file) {
    $this->file = $file;
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  function claimPath($file) {
    if (file_exists($file)) {
      $this->file = $file;
      return TRUE;
    }
    return FALSE;
  }
}
