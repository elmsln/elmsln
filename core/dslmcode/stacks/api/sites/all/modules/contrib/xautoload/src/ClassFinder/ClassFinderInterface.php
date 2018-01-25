<?php


namespace Drupal\xautoload\ClassFinder;

use Drupal\xautoload\ClassLoader\ClassLoaderInterface;

interface ClassFinderInterface extends ClassLoaderInterface {

  /**
   * Finds the path to the file where the class is defined.
   *
   * @param \Drupal\xautoload\ClassFinder\InjectedApi\InjectedApiInterface $api
   *   API object with a suggestFile() method.
   *   We are supposed to call $api->suggestFile($file) with all suggestions we
   *   can find, until it returns TRUE. Once suggestFile() returns TRUE, we stop
   *   and return TRUE as well. The $file will be in the $api object, so we
   *   don't need to return it.
   * @param string $class
   *   The name of the class, with all namespaces prepended.
   *   E.g. Some\Namespace\Some\Class
   *
   * @return TRUE|NULL
   *   TRUE, if we found the file for the class.
   *   That is, if the $api->suggestFile($file) method returned TRUE one time.
   *   NULL, if we have no more suggestions.
   */
  function apiFindFile($api, $class);

}
