<?php

/**
 *  @file
 *  Extends the MediaReadOnlyStreamWrapper class to handle videos from an imaginary example.com.
 */

/**
 *  Create an instance like this:
 *  $media_internet_test = new MediaInternetTestStreamWrapper('mediainternettest://video/[video-code]');
 */
class MediaInternetTestStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://example.com';

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/mediainternettest';
  }

  function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '/' . $parameters['video'];
    }
  }
}
