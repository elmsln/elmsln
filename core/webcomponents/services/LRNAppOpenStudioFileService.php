<?php


class LRNAppOpenStudioFileService {

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
        $file_uri = $file_wrapper . '://' . $name;
        if ($file = file_save_data($data, $file_uri)) {
          $ext = explode('.', $name);
          $extention = array_pop($ext);
          // generate derivatives if we know this is an image we support
          if (module_exists('imageinfo_cache') && in_array($extention, array('png', 'gif', 'jpeg', 'jpg'))) {
            $styles = image_styles();
            // only process our core elmsln ones we care about
            foreach ($styles as $style => $style_settings) {
              // only pull in our elmsln core styles that are derivatives
              // otherwise everything downstream will fail
              if (!in_array($style, array('elmsln_gray', 'elmsln_normalize', 'elmsln_small'))) {
                unset($styles[$style]);
              }
            }
            // generate background callback to build the image styles
            $return = _elmsln_api_create_image_styles_call(array($file_uri, image_style_path('elmsln_normalize', $file_uri)), $styles);
          }
          $encoded_file = _elmsln_api_v1_file_output($file);
          $encoded_file['originalurl'] = $encoded_file['url'];
          $encoded_file['thumbnail'] = $encoded_file['url'];
          // fix things that aren't gif since it might be animated
          if ($encoded_file['filemime'] != 'image/gif') {
            $encoded_file['url'] = $encoded_file['image_styles']['elmsln_normalize'];
            $encoded_file['thumbnail'] = $encoded_file['image_styles']['elmsln_small'] . '&reload=' . time();
          }
          return $encoded_file;
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