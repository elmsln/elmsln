<?php
/**
 * Upload a file and convert it into a node and return it.
 */
function elmsmedia_helper_elmsln_api_callback_elmsmedia_upload() {
  global $_elmsln;
  $params = $_elmsln['args'];
  // see if we had a file_wrapper defined, otherwise this is public
  if (isset($params['file_wrapper'])) {
    $file_wrapper = $params['file_wrapper'];
  }
  else {
    $file_wrapper = 'public';
  }
  // check for the uploaded file from our 1-page-uploader app
  // and ensure there are entity permissions to create a file of this type
  if (isset($params['upload']) && entity_access('create', 'file', $params['upload']['type'][0])) {
    $upload = $params['upload'];
    // load the user account so we can associate it to the post coming in
    $account = user_load_by_name($params['user']);
    // special handling of video and audio since these files are bigger
    if ($upload['type'][0] == 'video' || $upload['type'][0] == 'audio') {
      $file = new stdClass();
      $file->filename = $upload['name'];
      $file->uri = $params['file_data'];
      $file->status = FILE_STATUS_PERMANENT;
      $file->filemime = file_get_mimetype($params['file_data']);
      $file->uid = $account->uid;
      // move from tempory location to real directory
      $file = file_copy($file, $file_wrapper . '://' . $upload['name']);
      $file->url = file_create_url($file->uri);
    }
    else {
      // get contents of the file if it was uploaded into a variable
      $data = base64_decode($params['file_data']);
      $file = file_save_data($data, $file_wrapper . '://' . $upload['name']);
      $file->uid = $account->uid;
      file_save($file);
      $file->url = file_create_url($file->uri);
    }
    // see if Drupal can load from this data source
    if ($file) {
      // now we need to make a node to match
      $node = new stdClass();
      switch ($upload['type'][0]) {
        case 'image':
          $node->type = 'elmsmedia_image';
          $node->field_image[LANGUAGE_NONE][0]['fid'] = $file->fid;
        break;
        case 'audio':
          $node->type = 'audio';
          $node->field_audio[LANGUAGE_NONE][0]['fid'] = $file->fid;
          $node->field_audio[LANGUAGE_NONE][0]['display'] = 1;
        break;
        case 'video':
          $node->type = 'video';
          $node->field_video[LANGUAGE_NONE][0]['fid'] = $file->fid;
          $node->field_video[LANGUAGE_NONE][0]['display'] = 1;
        break;
        default:
          $node->type = 'document';
          $node->field_document_file[LANGUAGE_NONE][0]['fid'] = $file->fid;
          $node->field_document_file[LANGUAGE_NONE][0]['display'] = 1;
        break;
      }
      node_object_prepare($node);
      $node->language = LANGUAGE_NONE;
      $node->status = 1;
      $node->promote = 0;
      $node->revision = 1;
      // default title to the name of the file uploaded
      $node->title = $upload['name'];
      $node->uid = $account->uid;
      // convert machine name of course to node id
      $node->field_cis_course_ref[LANGUAGE_NONE][0]['target_id'] = $course_nid = _cis_connector_get_course_by_machine_name($params['__course_context']);
      // build out via submit then save
      if ($node = node_submit($node)) {
        node_save($node);
      }
    }
  }
  return array(
    'elmsmedia_upload' => TRUE,
    'file' => $file,
    'node' => $node,
    'message' => "Upload successful",
  );
}
