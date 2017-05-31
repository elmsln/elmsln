<?php
/**
 * @file
 * Upload callback
 */

/**
 * Callback for apps/lrnapp-media-upload/data.
 */
function _webcomponent_app_lrnapp_media_upload($machine_name, $app_route) {
  $status = 403;
  $file_wrapper = 'public';
  // check for the uploaded file from our 1-page-uploader app
  if (isset($_FILES['file-upload'])) {
    $upload = $_FILES['file-upload'];
    // check for a file upload
    if (isset($upload['tmp_name']) && is_uploaded_file($upload['tmp_name'])) {
      // get contents of the file if it was uploaded into a variable
      $data = file_get_contents($upload['tmp_name']);
      // see if Drupal can load from this data source
      if ($file = file_save_data($data, $file_wrapper . '://' . $upload['name'])) {
        // save the file entity
        file_save($file);
        $return = $file;
        $status = 200;
      }
    }
  }
  return array(
    'status' => $status,
    'data' => $return
  );
}