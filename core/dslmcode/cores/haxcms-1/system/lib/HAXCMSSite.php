<?php
// a site object
class HAXCMSSite {
  public $name;
  public $manifest;
  public $directory;
  public $basePath = '/';
  /**
   * Load a site based on directory and name
   */
  public function load($directory, $name) {
    $this->name = $name;
    $this->directory = $directory;
    $this->manifest = new JSONOutlineSchema();
    $this->manifest->load($this->directory . '/' . $this->name . '/site.json');
  }
  /**
   * Initialize a new site with a single page to start the outline
   * @var $directory string file system path
   * @var $siteBasePath string web based url / base_path
   * @var $name string name of the site
   * @var $theme string theme to load / copy as the method of display the JSON
   * 
   * @return HAXCMSSite object 
   */
  public function newSite($directory, $siteBasePath, $name, $theme = 'default') {
    // newSite calls must set basePath internally to avoid page association issues
    $this->basePath = $siteBasePath;
    $this->directory = $directory;
    $tmpname = strtolower($name);
    $this->name = $name;
    // attempt to shift it on the file system
    $this->recurseCopy(HAXCMS_ROOT . '/system/boilerplate/sites/' . $theme, $directory . '/' . $tmpname);
    // load what we just created
    $this->manifest = new JSONOutlineSchema();
    // where to save it to
    $this->manifest->file = $directory . '/' . $tmpname . '/site.json';
    // start updating the schema to match this new item we got
    $this->manifest->title = $name;
    $this->manifest->location = $this->basePath . $tmpname . '/index.html';
    $this->manifest->metadata->siteName = $tmpname;
    // create an initial page to make sense of what's there
    // this will double as saving our location and other updated data
    $this->addPage();
    return $this;
  }
  /**
   * Add a page to the site's file system and reflect it in the outine schema.
   *
   * @var $parent JSONOutlineSchemaItem representing a parent to add this page under
   *
   * @return $page repesented as JSONOutlineSchemaItem
   */
  public function addPage($parent = NULL) {
    $location = $this->directory . '/' . $this->name . '/' . count($this->manifest->items);
    // copy the boilerplate page we use for simplicity (or later complexity if we want)
    $this->recurseCopy(HAXCMS_ROOT . '/system/boilerplate/page', $location);
    // draft an outline schema item
    $page = new JSONOutlineSchemaItem();
    // set a crappy default title
    $page->title = 'New page';
    if ($parent == NULL) {
      $page->parent = NULL;
      $page->indent = 0;
    }
    else {
      // set to the parent id
      $page->parent = $parent->id;
      // move it one indentation below the parent; this can be changed later if desired
      $page->indent = $parent->indent+1;
    }
    // set order to the page's count for default add to end ordering
    $page->order = count($this->manifest->items);
    // location is the html file we just copied and renamed
    $page->location = $this->basePath . $this->name . '/' . count($this->manifest->items) . '/index.html';
    $this->manifest->addItem($page);
    $this->manifest->save();
    return $page;
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
            $this->recurseCopy($src . '/' . $file, $dst . '/' . $file);
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