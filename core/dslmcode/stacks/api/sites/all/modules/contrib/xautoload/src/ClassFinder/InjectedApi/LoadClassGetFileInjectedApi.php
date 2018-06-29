<?php

namespace Drupal\xautoload\ClassFinder\InjectedApi;

use Drupal\xautoload\Util;

/**
 * To help testability, we use an injected API instead of just a return value.
 * The injected API can be mocked to provide a mocked file_exists(), and to
 * monitor all suggested candidates, not just the correct return value.
 */
class LoadClassGetFileInjectedApi extends FindFileInjectedApi {

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
      require $file;
      return TRUE;
    }
    else {
      return FALSE;
    }
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
    require $file;
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
    require $file;
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
      require $file;
      return TRUE;
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  function guessFile($file) {
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
    require $file;
    $this->file = $file;
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  function claimPath($file) {
    if (file_exists($file)) {
      require $file;
      $this->file = $file;
      return TRUE;
    }
    return FALSE;
  }
}
