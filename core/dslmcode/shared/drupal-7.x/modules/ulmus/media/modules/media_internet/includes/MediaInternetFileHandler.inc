<?php

/**
 * @file
 * Definition of MediaInternetFileHandler.
 */

/**
 * A class for managing the addition of Internet files.
 */
class MediaInternetFileHandler extends MediaInternetBaseHandler {

  public $fileObject;

  public function preSave(&$file_obj) {
    // Coppies the remote file locally.
    $remote_uri = $file_obj->uri;
    //@TODO: we should follow redirection here an save the final filename, not just the basename.
    $local_filename = basename($remote_uri);
    $local_filename = file_munge_filename($local_filename, variable_get('file_entity_default_allowed_extensions', 'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm'), FALSE);
    $local_uri = file_stream_wrapper_uri_normalize('temporary://' . $local_filename);
    if (!@copy($remote_uri, $local_uri)) {
      throw new Exception('Unable to add file ' . $remote_uri);
      return;
    }
    // Make the current fileObject point to the local_uri, not the remote one.
    $file_obj = file_uri_to_object($local_uri);
  }

  public function postSave(&$file_obj) {
    $scheme = variable_get('file_default_scheme', 'public') . '://';
    module_load_include('inc', 'file_entity', 'file_entity.pages');
    $destination_uri = file_entity_upload_destination_uri(array());
    $uri = file_stream_wrapper_uri_normalize($destination_uri . '/' . $file_obj->filename);
    // Now to its new home.
    $file_obj = file_move($file_obj, $uri, FILE_EXISTS_RENAME);
  }

  public function getFileObject() {
    if (!$this->fileObject) {
      $this->fileObject = file_uri_to_object($this->embedCode);
    }
    return $this->fileObject;
  }

  public function claim($embedCode) {
    // Claim only valid URLs using a supported scheme.
    if (!valid_url($embedCode, TRUE) || !in_array(file_uri_scheme($embedCode), variable_get('media_fromurl_supported_schemes', array('http', 'https', 'ftp', 'smb', 'ftps')))) {
      return FALSE;
    }

    // This handler is intended for regular files, so don't claim URLs
    // containing query strings or fragments.
    if (preg_match('/[\?\#]/', $embedCode)) {
      return FALSE;
    }

    // Since this handler copies the remote file to the local web server, do not
    // claim a URL with an extension disallowed for media uploads.
    $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote(variable_get('file_entity_default_allowed_extensions', 'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm'))) . ')$/i';
    if (!preg_match($regex, basename($embedCode))) {
      return FALSE;
    }

    return TRUE;
  }
}
