<?php

namespace Drupal\xautoload\ClassFinder\InjectedApi;

/**
 * To help testability, we use an injected API instead of just a return value.
 * The injected API can be mocked to provide a mocked file_exists(), and to
 * monitor all suggested candidates, not just the correct return value.
 */
class CollectFilesInjectedApi extends AbstractInjectedApi {

  /**
   * @var string
   *   The method that, if called with $this->file, will return TRUE.
   */
  protected $methodName;

  /**
   * @var string
   *   The file where $this->$method($this->file) will return TRUE.
   */
  protected $file;

  /**
   * @var array[]
   *   All files that were suggested.
   */
  protected $suggestions;

  /**
   * @param string $class_name
   * @var string $method
   *   The method that, if called with $this->file, will return TRUE.
   * @param string $file
   *   The file where $this->$method($this->file) will return TRUE.
   */
  function __construct($class_name, $method_name, $file) {
    $this->methodName = $method_name;
    $this->file = $file;
    parent::__construct($class_name);
  }

  /**
   * When the process has finished, use this to return the result.
   *
   * @return string
   *   The file that is supposed to declare the class.
   */
  function getSuggestions() {
    return $this->suggestions;
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
    $this->suggestions[] = array(__FUNCTION__, $file);
    return __FUNCTION__ === $this->methodName && $file === $this->file;
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
    $this->suggestions[] = array(__FUNCTION__, $file);
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
    $this->suggestions[] = array(__FUNCTION__, $file);
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
    $this->suggestions[] = array(__FUNCTION__, $file);
    return __FUNCTION__ == $this->methodName && $file === $this->file;
  }

  /**
   * {@inheritdoc}
   */
  function guessFile($file) {
    $this->suggestions[] = array(__FUNCTION__, $file);
    return __FUNCTION__ == $this->methodName && $file === $this->file;
  }

  /**
   * {@inheritdoc}
   */
  function guessPath($file) {
    $this->suggestions[] = array(__FUNCTION__, $file);
    return __FUNCTION__ == $this->methodName && $file === $this->file;
  }

  /**
   * {@inheritdoc}
   */
  function claimFile($file) {
    $this->suggestions[] = array(__FUNCTION__, $file);
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  function claimPath($file) {
    $this->suggestions[] = array(__FUNCTION__, $file);
    return __FUNCTION__ == $this->methodName && $file === $this->file;
  }
}
