<?php


namespace Drupal\xautoload\ClassFinder\InjectedApi;

/**
 * To help testability, we use an injected API instead of just a return value.
 * The injected API can be mocked to provide a mocked file_exists(), and to
 * monitor all suggested candidates, not just the correct return value.
 */
interface InjectedApiInterface {

  /**
   * This is done in the injected api object, so we can easily provide a mock
   * implementation.
   */
  function is_dir($dir);

  /**
   * Get the name of the class we are looking for.
   *
   * @return string
   *   The class we are looking for.
   */
  function getClass();

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
  function suggestFile($file);

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
  function suggestFile_skipFileExists($file);

  /**
   * Same as suggestFile(), but assume that file_exists() returns TRUE.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return bool
   *   TRUE, if the file was found - which is always.
   */
  function suggestFile_checkNothing($file);

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
  function suggestFile_checkIncludePath($file);

  /**
   * Suggest a file that MUST exists, and that MAY declare the class we are
   * looking for.
   *
   * This is useful if a plugin already did the is_file() check by itself.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return boolean|NULL
   *   TRUE, if we are not interested in further candidates.
   *   FALSE|NULL, if we are interested in further candidates.
   */
  function guessFile($file);

  /**
   * Suggest a file that MAY exist, and that MAY declare the class we are
   * looking for.
   *
   * This is useful if a plugin already did the is_file() check by itself.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return boolean|NULL
   *   TRUE, if we are not interested in further candidates.
   *   FALSE|NULL, if we are interested in further candidates.
   */
  function guessPath($file);

  /**
   * Suggest a file that MUST exist, and if so, MUST declare the class we are
   * looking for.
   *
   * This is useful if a plugin already did the is_file() check by itself.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return boolean|NULL
   *   TRUE, if we are not interested in further candidates.
   *   FALSE|NULL, if we are interested in further candidates.
   */
  function claimFile($file);

  /**
   * Suggest a file that MAY exist, and if so, MUST declare the class we are
   * looking for.
   *
   * This is useful if a plugin already did the is_file() check by itself.
   *
   * @param string $file
   *   The file that is supposed to declare the class.
   *
   * @return boolean|NULL
   *   TRUE, if we are not interested in further candidates.
   *   FALSE|NULL, if we are interested in further candidates.
   */
  function claimPath($file);

}
