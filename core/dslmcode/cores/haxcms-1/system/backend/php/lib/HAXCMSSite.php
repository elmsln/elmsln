<?php
// working with RSS
include_once 'RSS.php';
use \Gumlet\ImageResize;
// a site object
class HAXCMSSite
{
    public $name;
    public $manifest;
    public $directory;
    public $basePath = '/';
    public $language = 'en-us';
    /**
     * Load a site based on directory and name
     */
    public function load($directory, $siteBasePath, $name)
    {
        $this->name = $name;
        $tmpname = urldecode($name);
        $tmpname = $GLOBALS['HAXCMS']->cleanTitle($tmpname, false);
        $this->basePath = $siteBasePath;
        $this->directory = $directory;
        $this->manifest = new JSONOutlineSchema();
        $this->manifest->load($this->directory . '/' . $tmpname . '/site.json');
    }
    /**
     * Initialize a new site with a single page to start the outline
     * @var $directory string file system path
     * @var $siteBasePath string web based url / base_path
     * @var $name string name of the site
     * @var $gitDetails git details
     * @var $domain domain information
     *
     * @return HAXCMSSite object
     */
    public function newSite(
        $directory,
        $siteBasePath,
        $name,
        $gitDetails,
        $domain = null
    ) {
        // calls must set basePath internally to avoid page association issues
        $this->basePath = $siteBasePath;
        $this->directory = $directory;
        $this->name = $name;
        // clean up name so it can be in a URL / published
        $tmpname = urldecode($name);
        $tmpname = $GLOBALS['HAXCMS']->cleanTitle($tmpname, false);
        $loop = 0;
        $newName = $tmpname;
        while (file_exists($directory . '/' . $newName)) {
            $loop++;
            $newName = $tmpname . '-' . $loop;
        }
        $tmpname = $newName;
        // attempt to shift it on the file system
        $this->recurseCopy(
            HAXCMS_ROOT . '/system/boilerplate/site',
            $directory . '/' . $tmpname
        );
        // create symlink to make it easier to resolve things to single built asset buckets
        @symlink('../../build', $directory . '/' . $tmpname . '/build');
        // symlink to do local development if needed
        @symlink('../../dist', $directory . '/' . $tmpname . '/dist');
        // symlink to do project development if needed
        if (is_link(HAXCMS_ROOT . '/node_modules') || is_dir(HAXCMS_ROOT . '/node_modules')) {
            @symlink(
            '../../node_modules',
            $directory . '/' . $tmpname . '/node_modules'
            );
        }
        // links babel files so that unification is easier
        @symlink(
            '../../../babel/babel-top.js',
            $directory . '/' . $tmpname . '/assets/babel-top.js'
        );
        @symlink(
            '../../../babel/babel-bottom.js',
            $directory . '/' . $tmpname . '/assets/babel-bottom.js'
        );
        // default support is for gh-pages
        if (is_null($domain) && isset($gitDetails->user)) {
            $domain = 'https://' . $gitDetails->user . '.github.io/' . $tmpname;
        } else {
            // put domain into CNAME not the github.io address if that exists
            @file_put_contents($directory . '/' . $tmpname . '/CNAME', $domain);
        }
        // load what we just created
        $this->manifest = new JSONOutlineSchema();
        // where to save it to
        $this->manifest->file = $directory . '/' . $tmpname . '/site.json';
        // start updating the schema to match this new item we got
        $this->manifest->title = $name;
        $this->manifest->location = $this->basePath . $tmpname . '/index.html';
        $this->manifest->metadata = new stdClass();
        $this->manifest->metadata->author = new stdClass();
        $this->manifest->metadata->site = new stdClass();
        $this->manifest->metadata->site->name = $tmpname;
        $this->manifest->metadata->site->domain = $domain;
        $this->manifest->metadata->site->created = time();
        $this->manifest->metadata->site->updated = time();
        $this->manifest->metadata->theme = new stdClass();
        $this->manifest->metadata->theme->variables = new stdClass();
        $this->manifest->metadata->node = new stdClass();
        $this->manifest->metadata->node->fields = new stdClass();
        $this->manifest->metadata->node->dynamicElementLoader = new stdClass();
        // create an initial page to make sense of what's there
        // this will double as saving our location and other updated data
        $this->addPage(null, 'Welcome to a new HAXcms site!', 'init');
        // put this in version control :) :) :)
        $git = new Git();
        $repo = $git->create($directory . '/' . $tmpname);
        if (
            !isset($this->manifest->metadata->site->git->url) &&
            isset($gitDetails->url)
        ) {
            $this->gitSetRemote($gitDetails);
        }
        // write the managed files to ensure we get happy copies
        $this->rebuildManagedFiles();
        $this->gitCommit('Managed files updated');
        return $this;
    }
    /**
     * Return the forceUpgrade status which is whether to force end users to upgrade their browser
     * @return string status of forced upgrade, string as boolean since it'll get written into a JS file
     */
    public function getForceUpgrade() {
        if (isset($this->manifest->metadata->site->settings->forceUpgrade) && $this->manifest->metadata->site->settings->forceUpgrade) {
            return "true";
        }
        return "false";
    }
    /**
     * Return the sw status
     * @return string status of forced upgrade, string as boolean since it'll get written into a JS file
     */
    public function getServiceWorkerStatus() {
        if (isset($this->manifest->metadata->site->settings->sw) && $this->manifest->metadata->site->settings->sw) {
            return TRUE;
        }
        return FALSE;
    }
    /**
     * Return an array of files we care about rebuilding on managed file operations
     * @return array keyed array of files we wish to pull from the boilerplate and keep in sync
     */
    public function getManagedTemplateFiles() {
        return array(
            'htaccess' => '.htaccess', // not templated (yet) but ensures self refreshing if we tweak it
            '404' => '404.html',
            'msbc' => 'browserconfig.xml',
            'dat' => 'dat.json',
            'build' => 'build.js',
            'buildhaxcms' => 'build-haxcms.js',
            'index' => 'index.html',
            'manifest' => 'manifest.json',
            'package' => 'package.json',
            'polymer' => 'polymer.json',
            'push' => 'push-manifest.json',
            'robots' => 'robots.txt',
            'sw' => 'service-worker.js',
            'outdated' => 'assets/upgrade-browser.html',
        );
    }
    /**
     * Reprocess the files that twig helps set in their static
     * form that the user is not in control of.
     */
    public function rebuildManagedFiles() {
      $templates = $this->getManagedTemplateFiles();
      // this can't be there by default since it's a dynamic file and we only
      // want to update this when we are refreshing the managed files directly
      $templates['indexphp'] = 'index.php';
      $siteDirectoryPath = $this->directory . '/' . $this->manifest->metadata->site->name;
      $boilerPath = HAXCMS_ROOT . '/system/boilerplate/site/';
      foreach ($templates as $file) {
        copy($boilerPath . $file, $siteDirectoryPath . '/' . $file);
      }
      $licenseData = $this->getLicenseData('all');
      $licenseLink = '';
      $licenseName = '';
      if (isset($this->manifest->license) && isset($licenseData[$this->manifest->license])) {
        $licenseLink = $licenseData[$this->manifest->license]['link'];
        $licenseName = 'License: ' . $licenseData[$this->manifest->license]['name'];
      }
      
      $templateVars = array(
          'hexCode' => HAXCMS_FALLBACK_HEX,
          'version' => $GLOBALS['HAXCMS']->getHAXCMSVersion(),
          'basePath' =>
              $this->basePath . $this->manifest->metadata->site->name . '/',
          'title' => $this->manifest->title,
          'short' => $this->manifest->metadata->site->name,
          'description' => $this->manifest->description,
          'forceUpgrade' => $this->getForceUpgrade(),
          'swhash' => array(),
          'ghPagesURLParamCount' => 0,
          'licenseLink' => $licenseLink,
          'licenseName' => $licenseName,
          'serviceWorkerScript' => $this->getServiceWorkerScript($this->basePath . $this->manifest->metadata->site->name . '/'),
          'bodyAttrs' => $this->getSitePageAttributes(),
          'metadata' => $this->getSiteMetadata(),
          'logo512x512' => $this->getLogoSize('512','512'),
          'logo310x310' => $this->getLogoSize('310','310'),
          'logo192x192' => $this->getLogoSize('192','192'),
          'logo150x150' => $this->getLogoSize('150','150'),
          'logo144x144' => $this->getLogoSize('144','144'),
          'logo96x96' => $this->getLogoSize('96','96'),
          'logo72x72' => $this->getLogoSize('72','72'),
          'logo70x70' => $this->getLogoSize('70','70'),
          'logo48x48' => $this->getLogoSize('48','48'),
          'logo36x36' => $this->getLogoSize('36','36'),
          'favicon' => $this->getLogoSize('16','16'),
      );
      $swItems = $this->manifest->items;
      // the core files you need in every SW manifest
      $coreFiles = array(
          'index.html',
          $this->getLogoSize('512','512'),
          $this->getLogoSize('310','310'),
          $this->getLogoSize('192','192'),
          $this->getLogoSize('150','150'),
          $this->getLogoSize('144','144'),
          $this->getLogoSize('96','96'),
          $this->getLogoSize('72','72'),
          $this->getLogoSize('70','70'),
          $this->getLogoSize('48','48'),
          $this->getLogoSize('36','36'),
          $this->getLogoSize('16','16'),
          'manifest.json',
          'site.json',
          '404.html',
      );
      // loop through files directory so we can cache those things too
      if ($handle = opendir($siteDirectoryPath . '/files')) {
          while (false !== ($file = readdir($handle))) {
              if (
                  $file != "." &&
                  $file != ".." &&
                  $file != '.gitkeep' &&
                  $file != '.DS_Store'
              ) {
                  // ensure this is a file
                  if (
                      is_file($siteDirectoryPath . '/files/' . $file)
                  ) {
                      $coreFiles[] = 'files/' . $file;
                  } else {
                      // @todo maybe step into directories?
                  }
              }
          }
          closedir($handle);
      }
      foreach ($coreFiles as $itemLocation) {
          $coreItem = new stdClass();
          $coreItem->location = $itemLocation;
          $swItems[] = $coreItem;
      }
      // generate a legit hash value that's the same for each file name + file size
      foreach ($swItems as $item) {
          if (
              $item->location === '' ||
              $item->location === $templateVars['basePath']
          ) {
              $filesize = filesize(
                  $siteDirectoryPath . '/index.html'
              );
          } elseif (
              file_exists($siteDirectoryPath . '/' . $item->location)
          ) {
              $filesize = filesize(
                  $siteDirectoryPath . '/' . $item->location
              );
          } else {
              // ?? file referenced but doesn't exist
              $filesize = 0;
          }
          if ($filesize !== 0) {
              $templateVars['swhash'][] = array(
                  $item->location,
                  strtr(
                      base64_encode(
                          hash_hmac(
                              'md5',
                              (string) $item->location . $filesize,
                              (string) 'haxcmsswhash',
                              true
                          )
                      ),
                      array(
                          '+' => '',
                          '/' => '',
                          '=' => '',
                          '-' => ''
                      )
                  )
              );
          }
      }
      if (isset($this->manifest->metadata->theme->variables->hexCode)) {
          $templateVars['hexCode'] =
              $this->manifest->metadata->theme->variables->hexCode;
      }
      // put the twig written output into the file
      $loader = new \Twig\Loader\FilesystemLoader($siteDirectoryPath);
      $twig = new \Twig\Environment($loader);
      foreach ($templates as $location) {
          if (file_exists($siteDirectoryPath . '/' . $location)) {
            @file_put_contents(
                $siteDirectoryPath . '/' . $location,
                $twig->render($location, $templateVars)
            );
          }
      }
    }
    /**
     * Rename a page from one location to another
     * This ensures that folders are moved but not the final index.html involved
     * It also helps secure the sites by ensuring movement is only within
     * their folder tree
     */
    public function renamePageLocation($old, $new)
    {
        $siteDirectory =
            $this->directory . '/' . $this->manifest->metadata->site->name;
        $old = str_replace('./', '', str_replace('../', '', $old));
        $new = str_replace('./', '', str_replace('../', '', $new));
        global $fileSystem;
        // ensure the path to the new folder is valid
        if (file_exists($siteDirectory . '/' . $old)) {
            $fileSystem->mirror(
                str_replace('/index.html', '', $siteDirectory . '/' . $old),
                str_replace('/index.html', '', $siteDirectory . '/' . $new)
            );
            $fileSystem->remove($siteDirectory . '/' . $old);
        }
    }
    /**
     * Basic wrapper to commit current changes to version control of the site
     */
    public function gitCommit($msg = 'Committed changes')
    {
        $git = new Git();
        // commit, true flag will attempt to make this a git repo if it currently isn't
        $repo = $git->open(
            $this->directory . '/' . $this->manifest->metadata->site->name, true
        );
        $repo->add('.');
        $repo->commit($msg);
        // commit should execute the automatic push flag if it's on
        if (isset($this->manifest->metadata->site->git->autoPush) && $this->manifest->metadata->site->git->autoPush && isset($this->manifest->metadata->site->git->branch)) {
            $repo->push('origin', $this->manifest->metadata->site->git->branch);
        }
        return true;
    }
    /**
     * Basic wrapper to revert top commit of the site
     */
    public function gitRevert($count = 1)
    {
        $git = new Git();
        $repo = $git->open(
            $this->directory . '/' . $this->manifest->metadata->site->name, true
        );
        $repo->revert($count);
        return true;
    }
    /**
     * Basic wrapper to commit current changes to version control of the site
     */
    public function gitPush()
    {
        $git = new Git();
        $repo = $git->open(
            $this->directory . '/' . $this->manifest->metadata->site->name, true
        );
        $repo->add('.');
        $repo->commit($msg);
        return true;
    }

    /**
     * Basic wrapper to commit current changes to version control of the site
     *
     * @var $git a stdClass containing repo details
     */
    public function gitSetRemote($gitDetails)
    {
        $git = new Git();
        $repo = $git->open(
            $this->directory . '/' . $this->manifest->metadata->site->name, true
        );
        $repo->set_remote("origin", $gitDetails->url);
        return true;
    }
    /**
     * Add a page to the site's file system and reflect it in the outine schema.
     *
     * @var $parent JSONOutlineSchemaItem representing a parent to add this page under
     * @var $title title of the new page to create
     * @var $template string which boilerplate page template / directory to load
     *
     * @return $page repesented as JSONOutlineSchemaItem
     */
    public function addPage($parent = null, $title = 'New page', $template = "default")
    {
        // draft an outline schema item
        $page = new JSONOutlineSchemaItem();
        // set a crappy default title
        $page->title = $title;
        if ($parent == null) {
            $page->parent = null;
            $page->indent = 0;
        } else {
            // set to the parent id
            $page->parent = $parent->id;
            // move it one indentation below the parent; this can be changed later if desired
            $page->indent = $parent->indent + 1;
        }
        // set order to the page's count for default add to end ordering
        $page->order = count($this->manifest->items);
        // location is the html file we just copied and renamed
        $page->location = 'pages/welcome/index.html';
        $page->metadata->created = time();
        $page->metadata->updated = time();
        $location =
            $this->directory .
            '/' .
            $this->manifest->metadata->site->name .
            '/pages/welcome';
        // copy the page we use for simplicity (or later complexity if we want)
        switch ($template) {
            case 'init':
                $this->recurseCopy(HAXCMS_ROOT . '/system/boilerplate/page/init', $location);
            break;
            default:
                $this->recurseCopy(HAXCMS_ROOT . '/system/boilerplate/page/default', $location);
            break;
        }
        $this->manifest->addItem($page);
        $this->manifest->save();
        $this->updateAlternateFormats();
        return $page;
    }
    /**
     * Save the site, though this basically is just a mapping to the manifest site.json saving
     */
    public function save() {
      $this->manifest->save();
    }
    /**
     * Update RSS, Atom feeds, site map, legacy outline, search index
     * which are physical files and need rebuilt on chnages to data structure
     */
    public function updateAlternateFormats($format = NULL)
    {
        $siteDirectory = $this->directory . '/' . $this->manifest->metadata->site->name . '/';
        if (is_null($format) || $format == 'rss') {
            // rip changes to feed urls
            $rss = new FeedMe();
            $siteDirectory =
                $this->directory . '/' . $this->manifest->metadata->site->name . '/';
            @file_put_contents($siteDirectory . 'rss.xml', $rss->getRSSFeed($this));
            @file_put_contents(
                $siteDirectory . 'atom.xml',
                $rss->getAtomFeed($this)
            );
        }
        // build a sitemap if we have a domain, kinda required...
        if (is_null($format) || $format == 'sitemap') {
            if (isset($this->manifest->metadata->site->domain)) {
                $domain = $this->manifest->metadata->site->domain;
                $generator = new \Icamys\SitemapGenerator\SitemapGenerator(
                    $domain,
                    $siteDirectory
                );
                // will create also compressed (gzipped) sitemap
                $generator->createGZipFile = true;
                // determine how many urls should be put into one file
                // according to standard protocol 50000 is maximum value (see http://www.sitemaps.org/protocol.html)
                $generator->maxURLsPerSitemap = 50000;
                // sitemap file name
                $generator->sitemapFileName = "sitemap.xml";
                // sitemap index file name
                $generator->sitemapIndexFileName = "sitemap-index.xml";
                // adding url `loc`, `lastmodified`, `changefreq`, `priority`
                foreach ($this->manifest->items as $key => $item) {
                    if ($item->parent == null) {
                        $priority = '1.0';
                    } elseif ($item->indent == 2) {
                        $priority = '0.7';
                    } else {
                        $priority = '0.5';
                    }
                    $updatedTime = new DateTime();
                    $updatedTime->setTimestamp($item->metadata->updated);
                    $updatedTime->format(DateTime::ATOM);
                    $generator->addUrl(
                        $domain .
                            '/' .
                            str_replace(
                                'pages/',
                                '',
                                str_replace('/index.html', '', $item->location)
                            ),
                        $updatedTime,
                        'daily',
                        $priority
                    );
                }
                // generating internally a sitemap
                $generator->createSitemap();
                // writing early generated sitemap to file
                $generator->writeSitemap();
            }
        }
        if (is_null($format) || $format == 'legacy') {
            // now generate a static list of links. This is so we can have legacy fail-back iframe mode in tact
            @file_put_contents(
                $siteDirectory . 'legacy-outline.html',
                '<!DOCTYPE html>
                <html lang="en">
                    <head>
                        <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
                        <meta content="utf-8" http-equiv="encoding">
                    </head>
                    <body>' .
                    $this->treeToNodes($this->manifest->items) .
                    '</body>
                </html>'
            );
        }
        if (is_null($format) || $format == 'search') {
            // now generate the search index
            @file_put_contents(
                $siteDirectory . 'lunrSearchIndex.json',
                    json_encode($this->lunrSearchIndex($this->manifest->items))
            );
        }
    }
    /**
     * Create Lunr.js style search index
     */
    private function lunrSearchIndex($items) {
      $data = array();
      foreach ($items as $item) {
        $created = time();
        if (isset($item->metadata) && isset($item->metadata->created)) {
          $created = $item->metadata->created;
        }
        // may seem silly but IDs in lunr have a size limit for some reason in our context..
        $data[] = array(
          "id" => substr(str_replace('-', '', str_replace('item-', '', $item->id)), 0, 29),
          "title" => $item->title,
          "created" => $created,
          "location" => str_replace('pages/', '', str_replace('/index.html', '', $item->location)),
          "description" => $item->description,
          "text" => $this->cleanSearchData(@file_get_contents($this->directory . '/' . $this->manifest->metadata->site->name . '/' . $item->location)),
        );
      }
      return $data;
    }
    /**
     * Clean up data from a file and make it easy for us to index on the front end
     */
    private function cleanSearchData($text) {
      // clean up initial, small, trim, replace end lines, utf8 no tags
      $text = trim(strtolower(str_replace("\n", ' ', utf8_encode(strip_tags($text)))));
      // all weird chars
      $text = preg_replace('/[^a-z0-9\']/', ' ', $text);
      $text = str_replace("'", '', $text);
      // all words 1 to 4 letters long
      $text = preg_replace('~\b[a-z]{1,4}\b\s*~', '', $text);
      // all excess white space
      $text = preg_replace('/\s+/', ' ', $text);
      // crush string to array and back to make an unique index
      $text = implode(' ', array_unique(explode(' ', $text)));
      return $text;
    }
    private function compareItemKeys($a, $b) {
      $key = $this->__compareItemKey;
      $dir = $this->__compareItemDir;
      if (isset($a->metadata->{$key})) {
        if ($dir == 'DESC') {
          return $a->metadata->{$key} > $b->metadata->{$key};
        }
        else {
          return $a->metadata->{$key} < $b->metadata->{$key};
        }
      }
    }
    /**
     * Sort items by a certain key value. Must be in the included list for safety of the sort
     * @var string $key - the key name to sort on, only some supported
     * @var string $dir - direction to sort, ASC default or DESC to reverse
     * @return array $items - sorted items based on the key used
     */
    public function sortItems($key, $dir = 'ASC') {
        $items = $this->manifest->items;
        switch ($key) {
            case 'created':
            case 'updated':
            case 'readtime':
              $this->__compareItemKey = $key;
              $this->__compareItemDir = $dir;
              usort($items, array($this,'compareItemKeys'));
            break;
            case 'id':
            case 'title':
            case 'indent':
            case 'location':
            case 'order':
            case 'parent':
            case 'description':
                usort($items, function ($a, $b) {
                  if ($dir == 'ASC') {
                    return $a->{$key} > $b->{$key};
                  }
                  else {
                    return $a->{$key} < $b->{$key};
                  }
                });
            break;
        }
        return $items;
    }
    /**
     * Build a JOS into a tree of links recursively
     */
    private function treeToNodes($current, &$rendered = array(), $html = '')
    {
        $loc = '';
        foreach ($current as $item) {
            if (!array_search($item->id, $rendered)) {
                $loc .=
                    '<li><a href="' .
                    $item->location .
                    '" target="content">' .
                    $item->title .
                    '</a>';
                array_push($rendered, $item->id);
                $children = array();
                foreach ($this->manifest->items as $child) {
                    if ($child->parent == $item->id) {
                        array_push($children, $child);
                    }
                }
                // sort the kids
                usort($children, function ($a, $b) {
                    return $a->order > $b->order;
                });
                // only walk deeper if there were children for this page
                if (count($children) > 0) {
                    $loc .= $this->treeToNodes($children, $rendered);
                }
                $loc .= '</li>';
            }
        }
        // make sure we aren't empty here before wrapping
        if ($loc != '') {
            $loc = '<ul>' . $loc . '</ul>';
        }
        return $html . $loc;
    }
    /**
     * Load node by unique id
     */
    public function loadNode($uuid)
    {
        foreach ($this->manifest->items as $item) {
            if ($item->id == $uuid) {
                return $item;
            }
        }
        return false;
    }
    /**
     * Get a social sharing image based on context of page or site having media
     * @var string $page page to mine the image from or attempt to
     * @return string full URL to an image
     */
    public function getSocialShareImage($page = null) {
      // resolve a JOS Item vs null
      if ($page != null) {
        $id = $page->id;
      }
      else {
        $id = null;
      }
      $fileName = &$GLOBALS['HAXCMS']->staticCache(__FUNCTION__ . $id);
      
      if (!isset($fileName)) {
        if (is_null($page)) {
          $page = $this->loadNodeByLocation();
        }
        if (isset($page->metadata->files)) {
          foreach ($page->metadata->files as $file) {
            if ($file->type == 'image/jpeg') {
              $fileName = $file->fullUrl;
            }
          }
        }
        // look for the theme banner
        if (isset($this->manifest->metadata->theme->variables->image)) {
          $fileName = $this->manifest->metadata->theme->variables->image;
        }
      }
      return $fileName;
    }
    /**
     * Return attributes for the site
     * @todo make this mirror the drupal get attributes method
     * @return string eventually, array of data keyed by type of information
     */
    public function getSitePageAttributes() {
      return 'vocab="http://schema.org/" prefix="oer:http://oerschema.org cc:http://creativecommons.org/ns dc:http://purl.org/dc/terms/"';
    }
    /**
     * Return the base tag accurately which helps with the PWA / SW side of things
     * @return string HTML blob for hte <base> tag
     */
    public function getBaseTag() {
      return '<base href="' . $this->basePath . $this->name . '/" />';
    }
    /**
     * Return a standard service worker that takes into account
     * the context of the page it's been placed on.
     * @todo this will need additional vetting based on the context applied
     * @return string <script> tag that will be a rather standard service worker
     */
    public function getServiceWorkerScript($basePath = null, $ignoreDevMode = FALSE, $addSW = TRUE) {
      // because this can screw with caching, let's make sure we
      // can throttle it locally for developers as needed
      if (!$addSW || ($GLOBALS["HAXCMS"]->developerMode && !$ignoreDevMode)) {
        return "\n  <!-- Service worker disabled via settings -->\n";
      }
      // support dynamic calculation
      if (is_null($basePath)) {
        $basePath = $this->basePath . $this->name . '/';
      }
      return "
  <script>
    if ('serviceWorker' in navigator) {
      var sitePath = '" . $basePath . "';
      // discover this path downstream of the root of the domain
      var swScope = window.location.pathname.substring(0, window.location.pathname.indexOf(sitePath)) + sitePath;
      if (swScope != document.head.getElementsByTagName('base')[0].href) {
        document.head.getElementsByTagName('base')[0].href = swScope;
      }
      window.addEventListener('load', function () {
        navigator.serviceWorker.register('service-worker.js', {
          scope: swScope
        }).then(function (registration) {
          registration.onupdatefound = function () {
            // The updatefound event implies that registration.installing is set; see
            // https://slightlyoff.github.io/ServiceWorker/spec/service_worker/index.html#service-worker-container-updatefound-event
            var installingWorker = registration.installing;
            installingWorker.onstatechange = function () {
              switch (installingWorker.state) {
                case 'installed':
                  if (!navigator.serviceWorker.controller) {
                    window.dispatchEvent(new CustomEvent('simple-toast-show', {
                      bubbles: true,
                      cancelable: false,
                      detail: {
                        text: 'Pages you view are cached for offline use.',
                        duration: 8000
                      }
                    }));
                  }
                break;
                case 'redundant':
                  throw Error('The installing service worker became redundant.');
                break;
              }
            };
          };
        }).catch(function (e) {
          console.warn('Service worker registration failed:', e);
        });
        // Check to see if the service worker controlling the page at initial load
        // has become redundant, since this implies there's a new service worker with fresh content.
        if (navigator.serviceWorker.controller) {
          navigator.serviceWorker.controller.onstatechange = function(event) {
            if (event.target.state === 'redundant') {
              var b = document.createElement('paper-button');
              b.appendChild(document.createTextNode('Reload'));
              b.raised = true;
              b.addEventListener('click', function(e){ window.location.reload(true); });
              window.dispatchEvent(new CustomEvent('simple-toast-show', {
                bubbles: true,
                cancelable: false,
                detail: {
                  text: 'A site update is available. Reload for latest content.',
                  duration: 12000,
                  slot: b,
                  clone: false
                }
              }));
            }
          };
        }
      });
    }
  </script>";
    }
    /**
     * Load content of this page
     * @var JSONOutlineSchemaItem $page - a loaded page object
     * @return string HTML / contents of the page object
     */
    public function getPageContent($page) {
      if (isset($page->location) && $page->location != '') {
        return filter_var(file_get_contents(HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $this->name . '/' . $page->location));
      }
    }
    /**
     * Return accurate, rendered site metadata
     * @var JSONOutlineSchemaItem $page - a loaded page object, most likely whats active
     * @return string an html chunk of tags for the head section
     * @todo move this to a render function / section / engine
     */
    public function getSiteMetadata($page = NULL, $domain = NULL, $cdn = '') {
      if (is_null($page)) {
        $page = new JSONOutlineSchemaItem();
      }
      // domain's need to inject their own full path for OG metadata (which is edge case)
      // most of the time this is the actual usecase so use the active path
      if (is_null($domain)) {
        $domain = $GLOBALS['HAXCMS']->getURI();
      }
      // support preconnecting CDNs, sets us up for dynamic CDN switching too
      $preconnect = '';
      $base = './';
      if ($cdn == '' && $GLOBALS['HAXCMS']->cdn != './') {
        $preconnect = '<link rel="preconnect" crossorigin href="' . $GLOBALS['HAXCMS']->cdn . '">';
        $cdn = $GLOBALS['HAXCMS']->cdn;
      }
      if ($cdn != '') {
        // preconnect for faster DNS lookup
        $preconnect = '<link rel="preconnect" crossorigin href="' . $cdn . '">';
        // preload rewrite correctly
        $base = $cdn . '/';
      }
      $title = $page->title;
      $siteTitle = $this->manifest->title . ' | ' . $page->title;
      $description = $page->description;
      $hexCode = HAXCMS_FALLBACK_HEX;
      if ($description == '') {
        $description = $this->manifest->description;
      }
      if ($title == '' || $title == 'New item') {
        $title = $this->manifest->title;
        $siteTitle = $this->manifest->title;
      }
      if (isset($this->manifest->metadata->theme->variables->hexCode)) {
          $hexCode = $this->manifest->metadata->theme->variables->hexCode;
      }
      $metadata = '<meta charset="utf-8">
  ' . $preconnect . '
  <link rel="preconnect" crossorigin href="https://fonts.googleapis.com">
  <link rel="preconnect" crossorigin href="https://cdnjs.cloudflare.com">
  <link rel="preconnect" crossorigin href="https://i.creativecommons.org">
  <link rel="preconnect" crossorigin href="https://licensebuttons.net">
  <link rel="preload" href="' . $base . 'build/es6/node_modules/mobx/lib/mobx.module.js" as="script" crossorigin="anonymous" />
  <link rel="preload" href="' . $base . 'build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/core/haxcms-site-builder.js" as="script" crossorigin="anonymous" />
  <link rel="preload" href="' . $base . 'build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/core/haxcms-site-store.js" as="script" crossorigin="anonymous" />
  <link rel="preload" href="' . $base . 'build/es6/dist/my-custom-elements.js" as="script" crossorigin="anonymous" />
  <link rel="preload" href="' . $base . 'build/es6/node_modules/@lrnwebcomponents/haxcms-elements/lib/base.css" as="style" />
  <link rel="preload" href="./custom/build/custom.es6.js" as="script" crossorigin="anonymous" />
  <link rel="preload" href="./theme/theme.css" as="style" />  
  <meta name="generator" content="HAXcms">
  <link rel="manifest" href="manifest.json">
  <meta name="viewport" content="width=device-width, minimum-scale=1, initial-scale=1, user-scalable=yes">
  <title>' . $siteTitle . '</title>
  <link rel="icon" href="' . $this->getLogoSize('16', '16') . '">
  <meta name="theme-color" content="' . $hexCode . '">
  <meta name="robots" content="index, follow">
  <meta name="mobile-web-app-capable" content="yes">
  <meta name="application-name" content="' . $title . '">

  <meta name="apple-mobile-web-app-capable" content="yes">
  <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
  <meta name="apple-mobile-web-app-title" content="' . $title . '">

  <link rel="apple-touch-icon" sizes="48x48" href="' . $this->getLogoSize('48', '48') . '">
  <link rel="apple-touch-icon" sizes="72x72" href="' . $this->getLogoSize('72', '72') . '">
  <link rel="apple-touch-icon" sizes="96x96" href="' . $this->getLogoSize('96', '96') . '">
  <link rel="apple-touch-icon" sizes="144x144" href="' . $this->getLogoSize('144', '144') . '">
  <link rel="apple-touch-icon" sizes="192x192" href="' . $this->getLogoSize('192', '192') . '">

  <meta name="msapplication-TileImage" content="' . $this->getLogoSize('144', '144') . '">
  <meta name="msapplication-TileColor" content="' . $hexCode . '">
  <meta name="msapplication-tap-highlight" content="no">
        
  <meta name="description" content="' . $description . '" />
  <meta name="og:sitename" property="og:sitename" content="' . $this->manifest->title . '" />
  <meta name="og:title" property="og:title" content="' . $title . '" />
  <meta name="og:type" property="og:type" content="article" />
  <meta name="og:url" property="og:url" content="' . $domain . '" />
  <meta name="og:description" property="og:description" content="' . $description . '" />
  <meta name="og:image" property="og:image" content="' . $this->getSocialShareImage($page) . '" />
  <meta name="twitter:card" property="twitter:card" content="summary_large_image" />
  <meta name="twitter:site" property="twitter:site" content="' . $domain . '" />
  <meta name="twitter:title" property="twitter:title" content="' . $title . '" />
  <meta name="twitter:description" property="twitter:description" content="' . $description . '" />
  <meta name="twitter:image" property="twitter:image" content="' . $this->getSocialShareImage($page) . '" />';  
      // mix in license metadata if we have it
      $licenseData = $this->getLicenseData('all');
      if (isset($this->manifest->license) && isset($licenseData[$this->manifest->license])) {
          $metadata .= "\n" . '  <meta rel="cc:license" href="' . $licenseData[$this->manifest->license]['link'] . '" content="License: ' . $licenseData[$this->manifest->license]['name'] . '"/>' . "\n";
      }
      // add in twitter link if they provided one
      if (isset($this->manifest->metadata->author->socialLink) && strpos($this->manifest->metadata->author->socialLink, 'https://twitter.com/') === 0) {
          $metadata .= "\n" . '  <meta name="twitter:creator" content="' . str_replace('https://twitter.com/', '@', $this->manifest->metadata->author->socialLink) . '" />';
      }
      $GLOBALS['HAXCMS']->dispatchEvent('haxcms-site-metadata', $metadata);
      return $metadata;
    }
    /**
     * Load a node based on a path
     * @var $path the path to try loading based on or search for the active from address
     * @return new JSONOutlineSchemaItem() a blank JOS item
     */
    public function loadNodeByLocation($path = NULL) {
        // load from the active address if we have one
        if (is_null($path) && isset($_SERVER['SCRIPT_URL'])) {
          $path = str_replace('/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $this->name . '/', '', $_SERVER['SCRIPT_URL']);
        }
        $path .= "/index.html";
        // failsafe in case someone had closing /
        $path = 'pages/' . str_replace('//', '/', $path);
        foreach ($this->manifest->items as $item) {
            if ($item->location == $path) {
                return $item;
            }
        }
       return new JSONOutlineSchemaItem();
    }
    /**
     * Generate or load the path to variations on the logo
     * @var string $height height of the icon as a string
     * @var string $width width of the icon as a string
     * @return string path to the image (web visible) that was created or pulled together
     */
    public function getLogoSize($height, $width) {
      $fileName = &$GLOBALS['HAXCMS']->staticCache(__FUNCTION__ . $height . $width);
      if (!isset($fileName)) {
        // if no logo, just bail with an easy standard one
        if (!isset($this->manifest->metadata->site->logo) || (isset($this->manifest->metadata->site) && ($this->manifest->metadata->site->logo == '' || $this->manifest->metadata->site->logo == null || $this->manifest->metadata->site->logo == "null"))) {
            $fileName = 'assets/icon-' . $height . 'x' . $width . '.png';
        }
        else {
          // ensure this path exists otherwise let's create it on the fly
          $path = HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $this->name . '/';
          $fileName = str_replace('files/', 'files/haxcms-managed/' . $height . 'x' . $width . '-', $this->manifest->metadata->site->logo);
          if (file_exists($path . $this->manifest->metadata->site->logo) && !file_exists($path . $fileName)) {
              global $fileSystem;
              $fileSystem->mkdir($path . 'files/haxcms-managed');
              $image = new ImageResize($path . $this->manifest->metadata->site->logo);
              $image->crop($height, $width)
              ->save($path . $fileName);
          }
        }
      }
      return $fileName;
    }
    /**
     * Load field schema for a page
     * Field cascade always follows Core -> Deploy -> Theme -> Site
     * Anything downstream can always override upstream but no one can remove fields
     */
    public function loadNodeFieldSchema($page)
    {
        $fields = array(
            'configure' => array(),
            'advanced' => array()
        );
        // load core fields
        // it may seem silly but we seek to not brick any usecase so if this file is gone.. don't die
        if (file_exists($GLOBALS['HAXCMS']->coreConfigPath . 'nodeFields.json')) {
            $coreFields = json_decode(
                file_get_contents(
                    $GLOBALS['HAXCMS']->coreConfigPath . 'nodeFields.json'
                )
            );
            $themes = array();
            foreach ($GLOBALS['HAXCMS']->getThemes() as $key => $item) {
                $themes[$key] = $item->name;
                $themes['key'] = $key;
            }
            // this needs to be set dynamically
            foreach ($coreFields->advanced as $key => $item) {
                if ($item->property === 'theme') {
                    $coreFields->advanced[$key]->options = $themes;
                }
            }
            // CORE fields
            if (isset($coreFields->configure)) {
                foreach ($coreFields->configure as $item) {
                    // edge case for pathauto
                    if ($item->property == 'location' && isset($this->manifest->metadata->site->settings->pathauto) && $this->manifest->metadata->site->settings->pathauto) {
                        // skip this core field if we have pathauto on
                        $item->required = false;
                        $item->disabled = true;
                    }
                    $fields['configure'][] = $item;
                }
            }
            if (isset($coreFields->advanced)) {
                foreach ($coreFields->advanced as $item) {
                    $fields['advanced'][] = $item;
                }
            }
        }
        // fields can live globally in config
        if (isset($GLOBALS['HAXCMS']->config->node->fields)) {
            if (isset($GLOBALS['HAXCMS']->config->node->fields->configure)) {
                foreach (
                    $GLOBALS['HAXCMS']->config->node->fields->configure
                    as $item
                ) {
                    $fields['configure'][] = $item;
                }
            }
            if (isset($GLOBALS['HAXCMS']->config->node->fields->advanced)) {
                foreach (
                    $GLOBALS['HAXCMS']->config->node->fields->advanced
                    as $item
                ) {
                    $fields['advanced'][] = $item;
                }
            }
        }
        // fields can live in the theme
        if (
            isset($this->manifest->metadata->theme->fields) &&
            file_exists(
                HAXCMS_ROOT .
                    '/build/es6/node_modules/' .
                    $this->manifest->metadata->theme->fields
            )
        ) {
            // @todo think of how to make this less brittle
            // not a fan of pegging loading this definition to our file system's publishing structure
            $themeFields = json_decode(
                file_get_contents(
                    HAXCMS_ROOT .
                        '/build/es6/node_modules/' .
                        $this->manifest->metadata->theme->fields
                )
            );
            if (isset($themeFields->configure)) {
                foreach ($themeFields->configure as $item) {
                    $fields['configure'][] = $item;
                }
            }
            if (isset($themeFields->advanced)) {
                foreach ($themeFields->advanced as $item) {
                    $fields['advanced'][] = $item;
                }
            }
        }
        // fields can live in the site itself
        if (isset($this->manifest->metadata->node->fields)) {
            if (isset($this->manifest->metadata->node->fields->configure)) {
                foreach (
                    $this->manifest->metadata->node->fields->configure
                    as $item
                ) {
                    $fields['configure'][] = $item;
                }
            }
            if (isset($this->manifest->metadata->node->fields->advanced)) {
                foreach ($this->manifest->metadata->node->fields->advanced as $item) {
                    $fields['advanced'][] = $item;
                }
            }
        }
        // core values that live outside of the fields area
        $values = array(
            'title' => $page->title,
            'location' => str_replace(
                'pages/',
                '',
                str_replace('/index.html', '', $page->location)
            ),
            'description' => $page->description,
            'created' => (isset($page->metadata->created) ? $page->metadata->created : 54),
            'published' => (isset($page->metadata->published) ? $page->metadata->published : TRUE),
        );
        // now get the field data from the page
        if (isset($page->metadata->fields)) {
            foreach ($page->metadata->fields as $key => $item) {
                if ($key == 'theme') {
                    $values[$key] = $item['key'];
                } else {
                    $values[$key] = $item;
                }
            }
        }
        // response as schema and values
        $response = new stdClass();
        $response->haxSchema = $fields;
        $response->values = $values;
        return $response;
    }
    /**
     * License data for common open license
     */
    public function getLicenseData($type = 'select')
    {
        $list = array(
            "by" => array(
                'name' => "Creative Commons: Attribution",
                'link' => "https://creativecommons.org/licenses/by/4.0/",
                'image' => "https://i.creativecommons.org/l/by/4.0/88x31.png"
            ),
            "by-sa" => array(
                'name' => "Creative Commons: Attribution Share a like",
                'link' => "https://creativecommons.org/licenses/by-sa/4.0/",
                'image' => "https://i.creativecommons.org/l/by-sa/4.0/88x31.png"
            ),
            "by-nd" => array(
                'name' => "Creative Commons: Attribution No derivatives",
                'link' => "https://creativecommons.org/licenses/by-nd/4.0/",
                'image' => "https://i.creativecommons.org/l/by-nd/4.0/88x31.png"
            ),
            "by-nc" => array(
                'name' => "Creative Commons: Attribution non-commercial",
                'link' => "https://creativecommons.org/licenses/by-nc/4.0/",
                'image' => "https://i.creativecommons.org/l/by-nc/4.0/88x31.png"
            ),
            "by-nc-sa" => array(
                'name' =>
                    "Creative Commons: Attribution non-commercial share a like",
                'link' => "https://creativecommons.org/licenses/by-nc-sa/4.0/",
                'image' =>
                    "https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png"
            ),
            "by-nc-nd" => array(
                'name' =>
                    "Creative Commons: Attribution Non-commercial No derivatives",
                'link' => "https://creativecommons.org/licenses/by-nc-nd/4.0/",
                'image' =>
                    "https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png"
            )
        );
        $data = array();
        if ($type == 'select') {
            foreach ($list as $key => $item) {
                $data[$key] = $item['name'];
            }
        }
        else {
            $data = $list;
        }
        return $data;
    }
    /**
     * Update page in the manifest list of items. useful if updating some
     * data about an existing entry.
     * @return JSONOutlineSchemaItem or FALSE
     */
    public function updateNode($page)
    {
        foreach ($this->manifest->items as $key => $item) {
            if ($item->id === $page->id) {
                $this->manifest->items[$key] = $page;
                $this->manifest->save(false);
                $this->updateAlternateFormats();
                return $page;
            }
        }
        return false;
    }
    /**
     * Delete a page from the manifest
     * @return JSONOutlineSchemaItem or FALSE
     */
    public function deleteNode($page)
    {
        foreach ($this->manifest->items as $key => $item) {
            if ($item->id === $page->id) {
                unset($this->manifest->items[$key]);
                $this->manifest->save(false);
                $this->updateAlternateFormats();
                return true;
            }
        }
        return false;
    }
    /**
     * Change the directory this site is located in
     */
    public function changeName($new)
    {
        $new = str_replace('./', '', str_replace('../', '', $new));
        // attempt to shift it on the file system
        if ($new != $this->manifest->metadata->site->name) {
            $this->manifest->metadata->site->name = $new;
            return @rename($this->manifest->metadata->site->name, $new);
        }
    }
    /**
     * Test and ensure the name being returned is a location currently unused
     */
    public function getUniqueLocationName($location, $page = null)
    {
        $siteDirectory =
            $this->directory . '/' . $this->manifest->metadata->site->name;
        $loop = 0;
        $original = $location;
        if ($page != null && $page->parent != null && $page->parent != '') {
            $item = $page;
            $pieces = array($original);
            while ($item = $this->manifest->getItemById($item->parent)) {
                $tmp = explode('/', $item->location);
                // drop index.html
                array_pop($tmp);
                array_unshift($pieces, array_pop($tmp));
            }
            $original = implode('/', $pieces);
            $location = $original;
        }
        while (
            file_exists($siteDirectory . '/pages/' . $location . '/index.html')
        ) {
            $loop++;
            $location = $original . '-' . $loop;
        }
        return $location;
    }
    /**
     * Recursive copy to rename high level but copy all files
     */
    public function recurseCopy($src, $dst, $skip = array())
    {
        $dir = opendir($src);
        // see if we can make the directory to start off
        if (!is_dir($dst) && array_search($dst, $skip) === FALSE && @mkdir($dst, 0777, true)) {
            while (false !== ($file = readdir($dir))) {
                if ($file != '.' && $file != '..') {
                    if (is_dir($src . '/' . $file) && array_search($file, $skip) === FALSE) {
                        $this->recurseCopy(
                            $src . '/' . $file,
                            $dst . '/' . $file
                        );
                    } else {
                        copy($src . '/' . $file, $dst . '/' . $file);
                    }
                }
            }
        } else {
            return false;
        }
        closedir($dir);
    }
}