<?php
// a site object
class HAXCMSFIle {
  /**
   * Save file into this site, optionally updating reference inside the page
   */
  public function save($upload, $site, $page = NULL) {
    global $HAXCMS;
    // check for a file upload
    if (isset($upload['tmp_name']) && is_uploaded_file($upload['tmp_name'])) {
      // get contents of the file if it was uploaded into a variable
      $filedata = file_get_contents($upload['tmp_name']);
      // attempt to save the file
      $fullpath = HAXCMS_ROOT . '/' . $HAXCMS->sitesDirectory . '/' . $site->name . '/files/' . $upload['name'];
      if ($size = file_put_contents($fullpath, $filedata)) {
        // @todo fake the file object creation stuff from CMS land
        $return = array(
          'file' => array(
            'path' => $fullpath,
            'fullUrl' => $HAXCMS->basePath . $HAXCMS->sitesDirectory . '/' . $site->name . '/files/' . $upload['name'],
            'url' => 'files/' . $upload['name'],
            'type' => mime_content_type($fullpath),
            'name' => $upload['name'],
            'size' => $size,
          )
        );
        if ($page != NULL) {
          // now update the page's metadata to suggest it uses this file. FTW!
          if (!isset($page->metadata->files)) {
            $page->metadata->files = array();
          }
          $page->metadata->files[] = $return['file'];
          $site->updatePage($page);
        }
        $status = 200;
      }
    }
    if ($size === FALSE) {
      $status = 500;
      $return = 'failed to write';
    }
    return json_encode(array(
      'status' => $status,
      'data' => $return,
    ));
  }
}