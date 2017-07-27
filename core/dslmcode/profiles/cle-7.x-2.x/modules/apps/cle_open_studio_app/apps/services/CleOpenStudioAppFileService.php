<?php


class CleOpenStudioAppFileService {

  /**
   * Get a list of comments
   * This will take into concideration what section the user is in and what section
   * they have access to.
   *
   * @param string $type File type extention
   * @param string $name Name of the file to be saved as.
   * @param array $options
   *                - file_wrapper Default: public
   *                - name Optionaly give the file a new name. Defaults to tmp_name
   */
  public function create($type, $tmp_name, $options = array()) {
    // see if we had a file_wrapper defined, otherwise this is public
    if (isset($options['file_wrapper'])) {
      $file_wrapper = $options['file_wrapper'];
    }
    else {
      $file_wrapper = 'public';
    }
    // check for the uploaded file from our 1-page-uploader app
    // and ensure there are entity permissions to create a file of this type
    if (entity_access('create', 'file', $type)) {
      // check for a file upload
      if (is_uploaded_file($tmp_name)) {
        // get contents of the file if it was uploaded into a variable
        $data = file_get_contents($tmp_name);
        // see if Drupal can load from this data source
        $name = $tmp_name;
        if (isset($options['name'])) {
          $name = $options['name'];
        }
        if ($file = file_save_data($data, $file_wrapper . '://' . $name)) {
          file_save($file);
          $return = array('file' => $file);
        }
      }
    }
  // $status = 403;
  // // see if we had a file_wrapper defined, otherwise this is public
  // if (isset($params['file_wrapper'])) {
  //   $file_wrapper = $params['file_wrapper'];
  // }
  // else {
  //   $file_wrapper = 'public';
  // }
  // // check for the uploaded file from our 1-page-uploader app
  // // and ensure there are entity permissions to create a file of this type
  // if (isset($_FILES['file-upload']) && entity_access('create', 'file', $_FILES['file-upload']['type'])) {
  //   $upload = $_FILES['file-upload'];
  //   // check for a file upload
  //   if (isset($upload['tmp_name']) && is_uploaded_file($upload['tmp_name'])) {
  //     // get contents of the file if it was uploaded into a variable
  //     $data = file_get_contents($upload['tmp_name']);
  //     // see if Drupal can load from this data source
  //     ddl($file_wrapper);
  //     ddl($upload['name']);
  //     if ($file = file_save_data($data, $file_wrapper . '://' . $upload['name'])) {
  //       file_save($file);
  //       $return = array('file' => $file);
  //       $status = 200;
  //     }
  //   }
  // }
  }
}