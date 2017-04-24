<?php

/**
 * @file
 * Extends the MediaInternetBaseHandler class to handle videos from an imaginary example.com.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetTestHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    // http://example.com/video/*
    $patterns = array(
      '@example\.com/video/(\d+)@i',
    );

    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[1])) {
        return file_stream_wrapper_uri_normalize('mediainternettest://video/' . $matches[1]);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    // Override the default filename for testing purposes.
    if (empty($file->fid)) {
      $file->filename = 'Drupal';
    }

    return $file;
  }
}
