<?php
// a site object
class HAXCMSSite {
  public $name;
  public $manifest;
  public $directory;
  public $pages;
  /**
   * Load a site based on directory and name
   */
  public function load($directory, $name) {
    $this->directory = $directory;
    $this->name = $name;
    $this->manifest = json_decode(file_get_contents($this->directory . '/' . $name . '/site.json'));
    // @todo look for pages on the file system and read them in
    $this->pages = array();
  }
  /**
   * Initialize a site
   */
  public function newSite($directory, $name) {
    // attempt to shift it on the file system
    $this->recurseCopy(HAXCMS_ROOT . '/system/boilerplate/site', $directory . '/' . $name);
    // load what we just created
    $this->load($directory, $name);
    return $this;
  }
  /**
   * Add a page to the site
   */
  public function addPage() {
    // attempt to shift it on the file system
    $this->recurseCopy(HAXCMS_ROOT . '/system/boilerplate/page', $this->directory . '/' . $this->name . '/' . count($this->pages));
    $page = new stdClass();
    try {
      $page->manifest = json_decode(file_get_contents($this->directory . '/' . $this->name . '/' . count($this->pages) . '/page.json'));
      array_unshift($this->pages, $page);
      return $page;
    }
    catch (Exception $e) {
    }
  }
  /**
   * Change the directory this site is located in
   */
  public function changeName($new) {
    // attempt to shift it on the file system
    if ($new != $this->name) {
      return rename($this->name, $new);
    }
  }
  /**
   * Recursive copy to rename high level but copy all files
   */
  private function recurseCopy($src, $dst) {
    $dir = opendir($src);
    // see if we can make the directory to start off
    if (!is_dir($dst) && @mkdir($dst)) {
      while (FALSE !== ( $file = readdir($dir)) ) {
        if (($file != '.') && ($file != '..')) {
          if (is_dir($src . '/' . $file)) {
            $this->recurseCopy($src . '/' . $file,$dst . '/' . $file);
          }
          else {
            copy($src . '/' . $file, $dst . '/' . $file);
          }
        }
      }
    }
    else {
      return FALSE;
    }
    closedir($dir);
  }
}