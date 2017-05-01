<?php

/**
 * @file
 * Definition of MediaInternetBaseHandler.
 */

/**
 * A base class for managing the addition of Internet media.
 *
 * Classes extending this class manage the addition of Internet media. To
 * achieve this, the class should parse user-submitted embed code, claim it
 * when appropriate and save it as a managed file.
 */
abstract class MediaInternetBaseHandler {

  /**
   * The constructor for the MediaInternetBaseHandler class. This method is also called
   * from the classes that extend this class and override this method.
   */
  public function __construct($embedCode) {
    $this->embedCode = $embedCode;
  }

  /**
   * Determines if this handler should claim the item.
   *
   * @param string $embed_code
   *   A string of user-submitted embed code.
   *
   * @return boolean
   *   Pass TRUE to claim the item.
   */
  abstract public function claim($embed_code);

  /**
   * Returns a file object which can be used for validation.
   *
   * @return StdClass
   */
  abstract public function getFileObject();

  /**
   * If required, implementors can validate the embedCode.
   */
  public function validate() {
  }

  /**
   * Before the file has been saved, implementors may do additional operations.
   *
   * @param object $file_obj
   */
  public function preSave(&$file_obj) {
  }

  /**
   * Saves a file to the file_managed table (with file_save).
   *
   * @return StdClass
   */
  public function save() {
    $file_obj = $this->getFileObject();
    $this->preSave($file_obj);
    file_save($file_obj);
    $this->postSave($file_obj);
    return $file_obj;
  }

  /**
   * After the file has been saved, implementors may do additional operations.
   *
   * @param object $file_obj
   */
  public function postSave(&$file_obj) {
  }
}
