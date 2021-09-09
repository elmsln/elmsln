<?php
/**
 * @OA\Info(
 *     title="HAXcms API",
 *     version="",
 *     description="API for interfacing with HAXcms end points",
 *     termsOfService="https://haxtheweb.org",
 *     @OA\Contact(
 *       email="hax@psu.edu"
 *     ),
 *     @OA\License(
 *       name="Apache 2.0",
 *       url="http://www.apache.org/licenses/LICENSE-2.0.html"
 *     )
 * ),
 * @OA\ExternalDocumentation(
 *     description="HAXcms and all things HAX documentations",
 *     url="https://haxtheweb.org/"
 * ),
 * @OA\Tag(
 *     name="hax",
 *     description="Operations required for HAX editor to work",
 *     @OA\ExternalDocumentation(
 *         description="Find out more about hax editor integrations",
 *         url="https://haxtheweb.org/integrations/create-new-ones"
 *     )
 * ),
 * @OA\Tag(
 *     name="cms",
 *     description="Operations for the CMS side"
 * ),
 * @OA\Tag(
 *     name="site",
 *     description="Operations for sites"
 * ),
 * @OA\Tag(
 *     name="node",
 *     description="Operations for individual nodes in a site"
 * ),
 * @OA\Tag(
 *     name="file",
 *     description="Operations for files related to CMS or HAX"
 * ),
 * @OA\Tag(
 *     name="form",
 *     description="Operations related to form submission or generation"
 * ),
 * @OA\Tag(
 *     name="meta",
 *     description="Operations related to metadata management or processes"
 * ),
 * @OA\Tag(
 *     name="git",
 *     description="Operations related to git / version control of the site"
 * ),
 * @OA\Tag(
 *     name="user",
 *     description="Operations for the user account / object"
 * ),
 * @OA\Tag(
 *     name="api",
 *     description="endpoint to generate the API or surrounding API callbacks"
 * ),
 * @OA\Tag(
 *     name="settings",
 *     description="Internal settings related to configuration of this HAXcms deployment"
 * ),
 * @OA\Tag(
 *     name="authenticated",
 *     description="Operations requiring authentication"
 * )
 */
class Operations {
  public $params;
  public $rawParams;
  /**
   * 
   * @OA\Post(
   *    path="/options",
   *    tags={"api"},
   *    @OA\Response(
   *        response="200",
   *        description="API bandaid till we get all the APIs documented. This is an array of callbacks"
   *    )
   * )
   */
  public function options() {
    return get_class_methods($this);
  }
  /**
   * Generate the swagger API documentation for this site
   * 
   * @OA\Post(
   *    path="/",
   *    tags={"api"},
   *    @OA\Response(
   *        response="200",
   *        description="API documentation in YAML"
   *    )
   * )
   * @todo generate JSON:API
   */   
  public function api() {
    $this->openapi();
  }
  /**
   * Generate the swagger API documentation for this site
   * 
   * @OA\Post(
   *    path="/openapi/json",
   *    tags={"api"},
   *    @OA\Response(
   *        response="200",
   *        description="API documentation in JSON"
   *    )
   * )
   */
  public function openapi() {
    // scan this document in order to build the Swagger docs
    // @todo make this scan multiple sources to surface user defined microservices
    $openapi = \OpenApi\scan(dirname(__FILE__) . '/Operations.php');
    // dynamically add the version
    $openapi->info->version = $GLOBALS['HAXCMS']->getHAXCMSVersion();
    $openapi->servers = Array();
    $openapi->servers[0] = new stdClass();
    // generate url dynamically w/ path to the API route
    $openapi->servers[0]->url = $GLOBALS['HAXCMS']->protocol . '://' . $GLOBALS['HAXCMS']->domain . $GLOBALS['HAXCMS']->basePath . $GLOBALS['HAXCMS']->systemRequestBase;
    $openapi->servers[0]->description = "Site list / dashboard for administrator user";
    // output, yaml we have to exit early or we'll get encapsulation
    if (isset($this->params['args']) && $this->params['args'][1] == 'json') {
      return json_decode($openapi->toJson());
    }
    else if (isset($this->params['args']) && $this->params['args'][1] == 'haxSchema') {
      $haxSchema = array('configure' => array());
      $target = null; 
      // support a specific endpoint that a form is desired for
      if (isset($this->params['args'][2]) && !is_null($this->params['args'][2])) {
        $target = $this->params['args'][2];
        $haxSchema = array();
      }
      foreach ($openapi->paths as $obj) {
        if (!is_null($target) && str_replace('/','', $obj->path) != $target) {
          continue;
        }
        $haxSchema[$obj->path] = array();
        $params = array();
        if (isset($obj->post) && isset($obj->post->parameters)) {
          $params = $obj->post->parameters;
        }
        else if (isset($obj->get) && isset($obj->get->parameters)) {
          $params = $obj->get->parameters;
        }
        if (is_array($params)) {
          foreach ($params as $param) {
            $haxSchema[$obj->path][] = json_decode('{
              "property": "' . $param->name . '",
              "title": "' . ucfirst($param->name) . '",
              "description": "' . $param->description . '",
              "inputMethod": "' . $GLOBALS['HAXCMS']->getInputMethod($param->schema->type) . '",
              "required": ' . (isset($param->required) ? (bool) $param->required : 'false') . '
            }');
          }
        }
      }
      return $haxSchema;
    }
    else {
      echo $openapi->toYaml();
      exit;
    }
  }
  /**
   * @OA\Post(
   *    path="/saveManifest",
   *    tags={"cms","authenticated"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Save the manifest of the site"
   *   )
   * )
   */
  public function saveManifest() {
    // load the site from name
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    // standard form submit
    // @todo 
    // make the form point to a form submission endpoint with appropriate name
    // add a hidden field to the output that always has the haxcms_form_id as well
    // as a dynamically generated Request token relative to the name of the
    // form
    // pull the form schema for the form itself internally
    // ensure ONLY the things that appear in that schema get set
    // if something DID NOT COME ACROSS, don't unset it, only set what shows up
    // if something DID COME ACROSS WE DIDN'T SET, kill the transaction (xss)

    // - snag the form
    // @todo see if we can dynamically save the valus in the same format we loaded
    // the original form in. This would involve removing the vast majority of
    // what's below
    /*if ($GLOBALS['HAXCMS']->validateRequestToken(null, 'form')) {
      $context = array(
        'site' => array(),
        'node' => array(),
      );
      if (isset($this->params['site'])) {
        $context['site'] = $this->params['site'];
      }
      if (isset($this->params['node'])) {
        $context['node'] = $this->params['node'];
      }
      $form = $GLOBALS['HAXCMS']->loadForm($this->params['haxcms_form_id'], $context);
    }*/
    if ($GLOBALS['HAXCMS']->validateRequestToken($this->params['haxcms_form_token'], $this->params['haxcms_form_id'])) {
      $site->manifest->title = strip_tags(
          $this->params['manifest']['site']['manifest-title']
      );
      $site->manifest->description = strip_tags(
          $this->params['manifest']['site']['manifest-description']
      );
      // store some version data here just so we can find it later
      $site->manifest->metadata->site->version = $GLOBALS['HAXCMS']->getHAXCMSVersion();
      $site->manifest->metadata->site->domain = filter_var(
          $this->params['manifest']['site']['manifest-metadata-site-domain'],
          FILTER_SANITIZE_STRING
      );
      $site->manifest->metadata->site->logo = filter_var(
          $this->params['manifest']['site']['manifest-metadata-site-logo'],
          FILTER_SANITIZE_STRING
      );
      if (!isset($site->manifest->metadata->site->static)) {
        $site->manifest->metadata->site->static = new stdClass();
      }
      if (!isset($site->manifest->metadata->site->settings)) {
        $site->manifest->metadata->site->settings = new stdClass();
      }
      $site->manifest->metadata->site->static->cdn = filter_var(
          $this->params['manifest']['static']['manifest-metadata-site-static-cdn'],
          FILTER_SANITIZE_STRING
      );
      $site->manifest->metadata->site->static->offline = filter_var(
          $this->params['manifest']['static']['manifest-metadata-site-static-offline'],
          FILTER_VALIDATE_BOOLEAN
      );
      if (isset($this->params['manifest']['site']['manifest-domain'])) {
          $domain = filter_var(
              $this->params['manifest']['site']['manifest-domain'],
              FILTER_SANITIZE_STRING
          );
          // support updating the domain CNAME value
          if ($site->manifest->metadata->site->domain != $domain) {
              $site->manifest->metadata->site->domain = $domain;
              @file_put_contents(
                  $site->directory .
                      '/' .
                      $site->manifest->site->name .
                      '/CNAME',
                  $domain
              );
          }
      }
      // look for a match so we can set the correct data
      foreach ($GLOBALS['HAXCMS']->getThemes() as $key => $theme) {
        if (
            filter_var($this->params['manifest']['theme']['manifest-metadata-theme-element'], FILTER_SANITIZE_STRING) ==
            $key
        ) {
            $site->manifest->metadata->theme = $theme;
        }
      }
      if (!isset($site->manifest->metadata->theme->variables)) {
        $site->manifest->metadata->theme->variables = new stdClass();
      }
      $site->manifest->metadata->theme->variables->image = filter_var(
          $this->params['manifest']['theme']['manifest-metadata-theme-variables-image'],FILTER_SANITIZE_STRING
      );
      if (isset($this->params['manifest']['theme']['manifest-metadata-theme-variables-hexCode'])) {
        $site->manifest->metadata->theme->variables->hexCode = filter_var(
          $this->params['manifest']['theme']['manifest-metadata-theme-variables-hexCode'],FILTER_SANITIZE_STRING
        );
      }
      $site->manifest->metadata->theme->variables->cssVariable = "--simple-colors-default-theme-" . filter_var(
        $this->params['manifest']['theme']['manifest-metadata-theme-variables-cssVariable'], FILTER_SANITIZE_STRING
      ). "-7";
      $site->manifest->metadata->theme->variables->icon = filter_var(
        $this->params['manifest']['theme']['manifest-metadata-theme-variables-icon'],FILTER_SANITIZE_STRING
      );
      if (isset($this->params['manifest']['author']['manifest-license'])) {
          $site->manifest->license = filter_var(
              $this->params['manifest']['author']['manifest-license'],
              FILTER_SANITIZE_STRING
          );
          if (!isset($site->manifest->metadata->author)) {
            $site->manifest->metadata->author = new stdClass();
          }
          $site->manifest->metadata->author->image = filter_var(
              $this->params['manifest']['author']['manifest-metadata-author-image'],
              FILTER_SANITIZE_STRING
          );
          $site->manifest->metadata->author->name = filter_var(
              $this->params['manifest']['author']['manifest-metadata-author-name'],
              FILTER_SANITIZE_STRING
          );
          $site->manifest->metadata->author->email = filter_var(
              $this->params['manifest']['author']['manifest-metadata-author-email'],
              FILTER_SANITIZE_STRING
          );
          $site->manifest->metadata->author->socialLink = filter_var(
              $this->params['manifest']['author']['manifest-metadata-author-socialLink'],
              FILTER_SANITIZE_STRING
          );
      }
      if (isset($this->params['manifest']['seo']['manifest-metadata-site-settings-pathauto'])) {
          $site->manifest->metadata->site->settings->pathauto = filter_var(
          $this->params['manifest']['seo']['manifest-metadata-site-settings-pathauto'],
          FILTER_VALIDATE_BOOLEAN
          );
      }
      if (isset($this->params['manifest']['seo']['manifest-metadata-site-settings-publishPagesOn'])) {
        $site->manifest->metadata->site->settings->publishPagesOn = filter_var(
        $this->params['manifest']['seo']['manifest-metadata-site-settings-publishPagesOn'],
        FILTER_VALIDATE_BOOLEAN
        );
      }
      if (isset($this->params['manifest']['seo']['manifest-metadata-site-settings-sw'])) {
        $site->manifest->metadata->site->settings->sw = filter_var(
        $this->params['manifest']['seo']['manifest-metadata-site-settings-sw'],
        FILTER_VALIDATE_BOOLEAN
        );
      }
      if (isset($this->params['manifest']['seo']['manifest-metadata-site-settings-forceUpgrade'])) {
        $site->manifest->metadata->site->settings->forceUpgrade = filter_var(
        $this->params['manifest']['seo']['manifest-metadata-site-settings-forceUpgrade'],
        FILTER_VALIDATE_BOOLEAN
        );
      }
      // more importantly, this is where the field UI stuff is...
      if (isset($this->params['manifest']['fields']['manifest-metadata-node-fields'])) {
          $fields = array();
          // establish a fields block, replacing with whatever is there now
          $site->manifest->metadata->node->fields = new stdClass();
          foreach ($this->params['manifest']['fields']['manifest-metadata-node-fields'] as $key => $field) {
              array_push($fields, $field);
          }
          if (count($fields) > 0) {
              $site->manifest->metadata->node->fields = $fields;
          }
      }
      $site->manifest->metadata->site->git->autoPush = filter_var(
        $this->params['manifest']['git']['manifest-metadata-site-git-autoPush'],
        FILTER_VALIDATE_BOOLEAN
      );
      $site->manifest->metadata->site->git->branch = filter_var(
        $this->params['manifest']['git']['manifest-metadata-site-git-branch'],
        FILTER_SANITIZE_STRING
      );
      $site->manifest->metadata->site->git->staticBranch = filter_var(
        $this->params['manifest']['git']['manifest-metadata-site-git-staticBranch'],
        FILTER_SANITIZE_STRING
      );
      $site->manifest->metadata->site->git->vendor = filter_var(
        $this->params['manifest']['git']['manifest-metadata-site-git-vendor'],
        FILTER_SANITIZE_STRING
      );
      $site->manifest->metadata->site->git->publicRepoUrl = filter_var(
        $this->params['manifest']['git']['manifest-metadata-site-git-publicRepoUrl'],
        FILTER_SANITIZE_STRING
      );
      $site->manifest->metadata->site->updated = time();
      // don't reorganize the structure
      $site->manifest->save(false);
      $site->gitCommit('Manifest updated');
      // rebuild the files that twig processes
      $site->rebuildManagedFiles();
      $site->gitCommit('Managed files updated');
      // check git remote if it came across as a possible setting
      if (isset($this->params['manifest']['git']['manifest-metadata-site-git-url'])) {
        if (
          filter_var($this->params['manifest']['git']['manifest-metadata-site-git-url'], FILTER_SANITIZE_STRING) &&
          (!isset($site->manifest->metadata->site->git->url) ||
            $site->manifest->metadata->site->git->url !=
              filter_var(
                $this->params['manifest']['git']['manifest-metadata-site-git-url'],
                FILTER_SANITIZE_STRING
              ))
        ) {
          $site->gitSetRemote(
              filter_var($this->params['manifest']['git']['manifest-metadata-site-git-url'], FILTER_SANITIZE_STRING)
          );
        }
        $site->manifest->metadata->site->git->url =
        filter_var(
          $this->params['manifest']['git']['manifest-metadata-site-git-url'],
          FILTER_SANITIZE_STRING
        );
        $site->manifest->save(false);
        $site->gitCommit('origin updated');
      }
      return $site->manifest;
    }
    else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'invalid request token',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/saveOutline",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Save an entire site outline"
   *   )
   * )
   */
  public function saveOutline() {
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    $original = $site->manifest->items;
    $items = $this->rawParams['items'];
    $itemMap = array();
    // items from the POST
    foreach ($items as $key => $item) {
      // get a fake item
      if (!($page = $site->loadNode($item->id))) {
        $page = $GLOBALS['HAXCMS']->outlineSchema->newItem();
        $itemMap[$item->id] = $page->id;
      }
      // set a crappy default title
      $page->title = $item->title;
      $cleanTitle = $GLOBALS['HAXCMS']->cleanTitle($page->title);
      if ($item->parent == null) {
        $page->parent = null;
        $page->indent = 0;
      } else {
        // check the item map as backend dictates unique ID
        if (isset($itemMap[$item->parent])) {
          $page->parent = $itemMap[$item->parent];
        } else {
          // set to the parent id
          $page->parent = $item->parent;
        }
        // move it one indentation below the parent; this can be changed later if desired
        $page->indent = $item->indent;
      }
      if (isset($item->order)) {
        $page->order = $item->order;
      } else {
        $page->order = $key;
      }
      // keep location if we get one already
      if (isset($item->location) && $item->location != '') {
        $page->location = $item->location;
      } else {
        // generate a logical page slug
        $page->location = 'pages/' . $page->id . '/index.html';
      }
      // keep location if we get one already
      if (isset($item->slug) && $item->slug != '') {
      } else {
          // generate a logical page slug
          $page->slug = $site->getUniqueSlugName($cleanTitle, $page, true);
      }
      // verify this exists, front end could have set what they wanted
      // or it could have just been renamed
      $siteDirectory = $site->directory . '/' . $site->manifest->metadata->site->name;
      // if it doesn't exist currently make sure the name is unique
      if (!$site->loadNode($page->id)) {
        $site->recurseCopy(
            HAXCMS_ROOT . '/system/boilerplate/page/default',
            $siteDirectory . '/' . str_replace('/index.html', '', $page->location)
        );
      }
      // this would imply existing item, lets see if it moved or needs moved
      else {
          $moved = false;
          foreach ($original as $key => $tmpItem) {
              // see if this is something moving as opposed to brand new
              if (
                  $tmpItem->id == $page->id &&
                  $tmpItem->slug != ''
              ) {
                  // core support for automatically managing paths to make them nice
                  if (isset($site->manifest->metadata->site->settings->pathauto) && $site->manifest->metadata->site->settings->pathauto) {
                      $moved = true;
                      $page->slug = $site->getUniqueSlugName($GLOBALS['HAXCMS']->cleanTitle($page->title), $page, true);
                  }
                  else if ($tmpItem->slug != $page->slug) {
                      $moved = true;
                      $page->slug = $tmpItem->slug;
                  }
              }
          }
          // it wasn't moved and it doesn't exist... let's fix that
          // this is beyond an edge case
          if (
              !$moved &&
              !file_exists($siteDirectory . '/' . $page->location)
          ) {
              $pAuto = false;
              if (isset($site->manifest->metadata->site->settings->pathauto) && $site->manifest->metadata->site->settings->pathauto) {
                $pAuto = true;
              }
              $tmpTitle = $site->getUniqueSlugName($cleanTitle, $page, $pAuto);
              $page->location = 'pages/' . $page->id . '/index.html';
              $page->slug = $tmpTitle;
              $site->recurseCopy(
                  HAXCMS_ROOT . '/system/boilerplate/page/default',
                  $siteDirectory . '/' . str_replace('/index.html', '', $page->location)
              );
          }
      }
      // check for any metadata keys that did come over
      foreach ($item->metadata as $key => $value) {
          $page->metadata->{$key} = $value;
      }
      // safety check for new things
      if (!isset($page->metadata->created)) {
          $page->metadata->created = time();
      }
      // always update at this time
      $page->metadata->updated = time();
      if ($site->loadNode($page->id)) {
          $site->updateNode($page);
      } else {
          $site->manifest->addItem($page);
      }
    }
    $site->manifest->metadata->site->updated = time();
    $site->manifest->save();
    $site->gitCommit('Outline updated in bulk');
    return $site->manifest->items;
  }
  /**
   * @OA\Post(
   *     path="/createNode",
   *     tags={"cms","authenticated","node"},
   *     @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *     ),
   *     @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 @OA\Property(
   *                     property="node",
   *                     type="object"
   *                 ),
   *                 @OA\Property(
   *                     property="indent",
   *                     type="number"
   *                 ),
   *                 @OA\Property(
   *                     property="order",
   *                     type="number"
   *                 ),
   *                 @OA\Property(
   *                     property="parent",
   *                     type="string"
   *                 ),
   *                 @OA\Property(
   *                     property="description",
   *                     type="string"
   *                 ),
   *                 @OA\Property(
   *                     property="metadata",
   *                     type="object"
   *                 ),
   *                 required={"site","node"},
   *                 example={
   *                    "site": {
   *                      "name": "mysite"
   *                    },
   *                    "node": {
   *                      "id": null,
   *                      "title": "Cool post",
   *                      "location": null
   *                    },
   *                    "indent": null,
   *                    "order": null,
   *                    "parent": null,
   *                    "description": "An example description for the post",
   *                    "metadata": {"tags": "metadata,can,be,whatever,you,want","other":"stuff"}
   *                 }
   *             )
   *         )
   *     ),
   *    @OA\Response(
   *        response="200",
   *        description="object with full properties returned"
   *   )
   * )
   */
  public function createNode() {
    $site = $GLOBALS['HAXCMS']->loadSite(strtolower($this->params['site']['name']));
    // get a new item prototype
    $item = $GLOBALS['HAXCMS']->outlineSchema->newItem();
    // set the title
    $item->title = str_replace("\n", '', $this->params['node']['title']);
    if (isset($this->params['node']['id']) && $this->params['node']['id'] != '' && $this->params['node']['id'] != null) {
        $item->id = $this->params['node']['id'];
    }
    $item->location = 'pages/' . $item->id . '/index.html';
    if (isset($this->params['indent']) && $this->params['indent'] != '' && $this->params['indent'] != null) {
        $item->indent = $this->params['indent'];
    }
    if (isset($this->params['order']) && $this->params['order'] != '' && $this->params['order'] != null) {
        $item->order = $this->params['order'];
    }
    if (isset($this->params['parent']) && $this->params['parent'] != '' && $this->params['parent'] != null) {
        $item->parent = $this->params['parent'];
    } else {
        $item->parent = null;
    }
    if (isset($this->params['description']) && $this->params['description'] != '' && $this->params['description'] != null) {
        $item->description = str_replace("\n", '', $this->params['description']);
    }
    if (isset($this->params['order']) && $this->params['metadata'] != '' && $this->params['metadata'] != null) {
        $item->metadata = $this->params['metadata'];
    }
    if (isset($this->params['node']['location']) && $this->params['node']['location'] != '' && $this->params['node']['location'] != null) {
      $cleanTitle = $GLOBALS['HAXCMS']->cleanTitle($this->params['node']['location']);
      $item->slug = $site->getUniqueSlugName($cleanTitle);
    } else {
      $cleanTitle = $GLOBALS['HAXCMS']->cleanTitle($item->title);
      $item->slug = $site->getUniqueSlugName($cleanTitle, $item, true);
    }
    $item->metadata->created = time();
    $item->metadata->updated = time();
    // add the item back into the outline schema
    // @todo fix logic here to actually create the page based on 1 call
    // this logic should be cleaned up in addPage to allow for
    // passing in arguments
    $site->recurseCopy(
        HAXCMS_ROOT . '/system/boilerplate/page/default',
        $site->directory .
            '/' .
            $site->manifest->metadata->site->name .
            '/' .
            str_replace('/index.html', '', $item->location)
    );
    $site->manifest->addItem($item);
    $site->manifest->save();
    $site->gitCommit('Page added:' . $item->title . ' (' . $item->id . ')');
    return $item;
  }
  /**
   * @OA\Post(
   *    path="/saveNode",
   *    tags={"cms","authenticated","node"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Save a node"
   *   )
   * )
   */
  public function saveNode() {
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    $schema = array();
    if (isset($this->params['node']['body'])) {
      $body = $this->params['node']['body'];
      // we ship the schema with the body
      if (isset($this->params['node']['schema'])) {
        $schema = $this->params['node']['schema'];
      }
    }
    $details = array();
    // if we have details object then merge configure and advanced
    if (isset($this->params['node']['details'])) {
      foreach ($this->params['node']['details']['node']['configure'] as $key => $value) {
        $details[$key] = $value;
      }
      foreach ($this->params['node']['details']['node']['advanced'] as $key => $value) {
        $details[$key] = $value;
      }
    }
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    if ($page = $site->loadNode($this->params['node']['id'])) {
      // convert web location for loading into file location for writing
      if (isset($body)) {
        $bytes = $page->writeLocation(
          $body,
          HAXCMS_ROOT .
          '/' .
          $GLOBALS['HAXCMS']->sitesDirectory .
          '/' .
          $site->name .
          '/'
        );
        if ($bytes === false) {
          return array(
            '__failed' => array(
              'status' => 500,
              'message' => 'failed to write',
            )
          );
        } else {
            // sanity check
            if (!isset($page->metadata)) {
              $page->metadata = new stdClass();
            }
            // update the updated timestamp
            $page->metadata->updated = time();
            // auto generate a text only description from first 200 chars
            $clean = strip_tags($body);
            $page->description = str_replace(
                "\n",
                '',
                substr($clean, 0, 200)
            );
            $readtime = round(str_word_count($clean) / 200);
            // account for uber small body
            if ($readtime == 0) {
              $readtime = 1;
            }
            $page->metadata->readtime = $readtime;
            // assemble other relevent content detail by skimming it off
            $contentDetails = new stdClass();
            $contentDetails->headings = 0;
            $contentDetails->paragraphs = 0;
            $contentDetails->schema = array();
            $contentDetails->tags = array();
            $contentDetails->elements = count($schema);
            // pull schema apart and store the relevent pieces
            foreach ($schema as $element) {
              switch($element['tag']) {
                case 'h1':
                case 'h2':
                case 'h3':
                case 'h4':
                case 'h5':
                case 'h6':
                    $contentDetails->headings++;
                break;
                case 'p':
                    $contentDetails->paragraphs++;
                break;
              }
              if (!isset($contentDetails->tags[$element['tag']])) {
                  $contentDetails->tags[$element['tag']] = 0;
              }
              $contentDetails->tags[$element['tag']]++;
              $newItem = new stdClass();
              $hasSchema = false;
              if (isset($element['properties']['property'])) {
                $hasSchema = true;
                $newItem->property = $element['properties']['property'];
              }
              if (isset($element['properties']['typeof'])) {
                $hasSchema = true;
                $newItem->typeof = $element['properties']['typeof'];
              }
              if (isset($element['properties']['resource'])) {
                $hasSchema = true;
                $newItem->resource = $element['properties']['resource'];
              }
              if (isset($element['properties']['prefix'])) {
                $hasSchema = true;
                $newItem->prefix = $element['properties']['prefix'];
              }
              if (isset($element['properties']['vocab'])) {
                $hasSchema = true;
                $newItem->vocab = $element['properties']['vocab'];
              }
              if ($hasSchema) {
                $contentDetails->schema[] = $newItem;
              }
            }
            $page->metadata->contentDetails = $contentDetails;
            $site->updateNode($page);
            $site->gitCommit(
              'Page updated: ' . $page->title . ' (' . $page->id . ')'
            );
            return $bytes;
        }
      } elseif (isset($details)) {
        // update the updated timestamp
        $page->metadata->updated = time();
        foreach ($details as $key => $value) {
            // sanitize both sides
            $key = filter_var($key, FILTER_SANITIZE_STRING);
            switch ($key) {
                case 'node-configure-slug':
                  // check on name
                  $value = $GLOBALS['HAXCMS']->cleanTitle(filter_var($value, FILTER_SANITIZE_STRING));
                  $page->slug = $value;
                  if ($value == '') {
                    $pAuto = false;
                    if (isset($site->manifest->metadata->site->settings->pathauto) && $site->manifest->metadata->site->settings->pathauto) {
                      $pAuto = true;
                    }
                    $page->slug = $site->getUniqueSlugName($GLOBALS['HAXCMS']->cleanTitle(filter_var($details['node-configure-title'], FILTER_SANITIZE_STRING)), $page, $pAuto);
                  }
                break;
                case 'node-configure-title':
                    $value = filter_var($value, FILTER_SANITIZE_STRING);
                    $page->title = $value;
                break;
                case 'node-configure-description':
                    $value = filter_var($value, FILTER_SANITIZE_STRING);
                    $page->description = $value;
                break;
                case 'node-configure-published':
                    $value = filter_var($value, FILTER_VALIDATE_BOOLEAN);
                    $page->metadata->published = $value;
                break;
                case 'node-advanced-created':
                    $value = filter_var($value, FILTER_VALIDATE_INT);
                    $page->metadata->created = $value;
                break;
                case 'node-advanced-theme':
                  $themes = $GLOBALS['HAXCMS']->getThemes();
                  $value = filter_var($value, FILTER_SANITIZE_STRING);
                  // support for removing the custom theme or applying none
                  if ($value == '_none_') {
                    unset($page->metadata->theme);
                  }
                  else if (isset($themes->{$value})) {
                    $page->metadata->theme = $themes->{$value};
                    $page->metadata->theme->key = $value;
                  }
                  break;
                default:
                    // ensure ID is never changed
                    if ($key != 'id') {
                        // support for saving fields
                        if (!isset($page->metadata->fields)) {
                            $page->metadata->fields = new stdClass();
                        }
                        switch (gettype($value)) {
                            case 'array':
                            case 'object':
                                $page->metadata->fields->{$key} = new stdClass();
                                foreach ($value as $key2 => $val) {
                                    $page->metadata->fields->{$key}->{$key2} = new stdClass();
                                    $key2 = filter_var(
                                        $key2,
                                        FILTER_VALIDATE_INT
                                    );
                                    foreach ($val as $key3 => $deepVal) {
                                        $key3 = filter_var(
                                            $key3,
                                            FILTER_SANITIZE_STRING
                                        );
                                        $deepVal = filter_var(
                                            $deepVal,
                                            FILTER_SANITIZE_STRING
                                        );
                                        $page->metadata->fields->{$key}->{$key2}->{$key3} = $deepVal;
                                    }
                                }
                                break;
                            case 'integer':
                            case 'double':
                                $value = filter_var(
                                    $value,
                                    FILTER_VALIDATE_INT
                                );
                                $page->metadata->fields->{$key} = $value;
                                break;
                            default:
                                $value = filter_var(
                                    $value,
                                    FILTER_SANITIZE_STRING
                                );
                                $page->metadata->fields->{$key} = $value;
                                break;
                        }
                    }
                    break;
            }
        }
        $site->updateNode($page);
        $site->gitCommit(
            'Page details updated: ' . $page->title . ' (' . $page->id . ')'
        );
        // make sure we return the "theme" if set back to null
        // we do this so that the front end can reset to the default theme
        // but also so we don't save this data for no reason in the piecea above
        if (!isset($page->metadata->theme)) {
          $themes = $GLOBALS['HAXCMS']->getThemes();
          $page->metadata->theme = $themes->{$site->manifest->metadata->theme->element};
          $page->metadata->theme->key = $site->manifest->metadata->theme->element;
        }
        return $page;
      }
    }
  }
  /**
   * @OA\Post(
   *    path="/deleteNode",
   *    tags={"cms","authenticated","node"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Delete a node"
   *   )
   * )
   */
  public function deleteNode() {
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    // update the page's content, using manifest to find it
    // this ensures that writing is always to what the file system
    // determines to be the correct page
    if ($page = $site->loadNode($this->params['node']['id'])) {
        if ($site->deleteNode($page) === false) {
          return array(
            '__failed' => array(
              'status' => 500,
              'message' => 'failed to delete',
            )
          );
        } else {
          $site->gitCommit(
            'Page deleted: ' . $page->title . ' (' . $page->id . ')'
          );
          return $page;
        }
        exit();
    } else {
      return array(
        '__failed' => array(
          'status' => 500,
          'message' => 'failed to load',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/siteUpdateAlternateFormats",
   *    tags={"cms","authenticated","meta"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Update the alternative formats surrounding a site"
   *   )
   * )
   */
  public function siteUpdateAlternateFormats() {
    $format = NULL;
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    if (isset($this->params['format'])) {
      $format = $this->params['format'];
    }
    $site->updateAlternateFormats($format);
  }
  /**
   * @OA\Post(
   *    path="/revertCommit",
   *    tags={"cms","authenticated","meta","git","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Revert the last commit to the git repo backing the site"
   *   )
   * )
   */
  public function revertCommit() {
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    // this will revert the top commit
    $site->gitRevert();
    return TRUE;
  }
  /**
   * @OA\Post(
   *    path="/getNodeFields",
   *    tags={"cms","authenticated","node","form"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Update the alternative formats surrounding a site"
   *   )
   * )
   */
  public function getNodeFields() {
    if ($GLOBALS['HAXCMS']->validateRequestToken(null, 'form')) {
      $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
      if ($page = $site->loadNode($this->params['node']['id'])) {
        $schema = $site->loadNodeFieldSchema($page);
        return $schema;
      }
    } else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'invalid request token',
        )
      );
    }
  }
  /**
   * @OA\Get(
   *    path="/connectionSettings",
   *    tags={"cms"},
   *    @OA\Response(
   *        response="200",
   *        description="Generate the connection settings dynamically for implying we have a PHP backend"
   *   )
   * )
   */
  public function connectionSettings() {
    // need to return this as if it was a javascript file, weird looking for sure
    return array(
      '__noencode' => array(
        'status' => 200,
        'contentType' => 'application/javascript',
        'message' => 'window.appSettings = ' . json_encode($GLOBALS['HAXCMS']->appJWTConnectionSettings()) . ';',
      )
    );
  }
  /**
   * 
   * HAX EDITOR CALLBACKS
   * 
   */

  /**
   * @OA\GET(
   *    path="/generateAppStore",
   *    tags={"hax","api"},
   *    @OA\Parameter(
   *         name="app-store-token",
   *         description="security token for appstore",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Generate the AppStore spec for HAX editor directions"
   *   )
   * )
   */
  public function generateAppStore() {
    // test if this is a valid user login with this specialty token that HAX looks for
    if (
      isset($this->params['app-store-token']) &&
      $GLOBALS['HAXCMS']->validateRequestToken($this->params['app-store-token'], 'appstore')
    ) {
      $haxService = new HAXAppStoreService();
      $apikeys = array();
      $baseApps = $haxService->baseSupportedApps();
      foreach ($baseApps as $key => $app) {
        if (
          isset($GLOBALS['HAXCMS']->config->appStore->apiKeys->{$key}) &&
          $GLOBALS['HAXCMS']->config->appStore->apiKeys->{$key} != ''
        ) {
          $apikeys[$key] = $GLOBALS['HAXCMS']->config->appStore->apiKeys->{$key};
        }
      }
      $appStore = $haxService->loadBaseAppStore($apikeys);
      // pull in the core one we supply, though only upload works currently
      $tmp = json_decode($GLOBALS['HAXCMS']->siteConnectionJSON());
      array_push($appStore, $tmp);
      if (isset($GLOBALS['HAXCMS']->config->appStore->stax)) {
          $staxList = $GLOBALS['HAXCMS']->config->appStore->stax;
      } else {
          $staxList = $haxService->loadBaseStax();
      }
      if (isset($GLOBALS['HAXCMS']->config->appStore->blox)) {
          $bloxList = $GLOBALS['HAXCMS']->config->appStore->blox;
      } else {
          $bloxList = $haxService->loadBaseBlox();
      }
      if (isset($GLOBALS['HAXCMS']->config->appStore->autoloader)) {
          $autoloaderList = $GLOBALS['HAXCMS']->config->appStore->autoloader;
      } else {
          $autoloaderList = json_decode('
        [
          "video-player",
          "meme-maker",
          "lrn-aside",
          "grid-plate",
          "magazine-cover",
          "image-compare-slider",
          "license-element",
          "self-check",
          "multiple-choice",
          "oer-schema",
          "hero-banner",
          "task-list",
          "lrn-table",
          "media-image",
          "lrndesign-blockquote",
          "a11y-gif-player",
          "wikipedia-query",
          "lrn-vocab",
          "full-width-image",
          "person-testimonial",
          "citation-element",
          "stop-note",
          "place-holder",
          "lrn-math",
          "q-r",
          "lrndesign-gallery",
          "lrndesign-timeline"
        ]
        ');
      }
      return array(
          'status' => 200,
          'apps' => $appStore,
          'stax' => $staxList,
          'blox' => $bloxList,
          'autoloader' => $autoloaderList
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/getUserData",
   *    tags={"cms","authenticated","user","settings"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Load data about the logged in user"
   *   )
   * )
   */
  public function getUserData() {
    return array(
      'status' => 200,
      'data' => $GLOBALS['HAXCMS']->userData
    );
  }
  /**
   * @OA\Post(
   *    path="/formLoad",
   *    tags={"cms","authenticated","form"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Load a form based on ID"
   *   )
   * )
   */
  public function formLoad() {
    if ($GLOBALS['HAXCMS']->validateRequestToken(null, 'form')) {
      $context = array(
        'site' => array(),
        'node' => array(),
      );
      if (isset($this->params['site'])) {
        $context['site'] = $this->params['site'];
      }
      if (isset($this->params['node'])) {
        $context['node'] = $this->params['node'];
      }
      // @todo add support for hooking in multiple
      $form = $GLOBALS['HAXCMS']->loadForm($this->params['haxcms_form_id'], $context);
      if (isset($form->fields['__failed'])) {
        return array(
          $form->fields
        );
      }
      return array(
        'status' => 200,
        'data' => $form
      );
    }
    else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'invalid request token',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/formProcess",
   *    tags={"cms","authenticated","form"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Process a form based on ID and input data"
   *   )
   * )
   */
  public function formProcess() {
    if ($GLOBALS['HAXCMS']->validateRequestToken($this->params['haxcms_form_token'], $this->params['haxcms_form_id'])) {
      $context = array(
        'site' => array(),
        'node' => array(),
      );
      if (isset($this->params['site'])) {
        $context['site'] = $this->params['site'];
      }
      if (isset($this->params['node'])) {
        $context['node'] = $this->params['node'];
      }
      $form = $GLOBALS['HAXCMS']->processForm($this->params['haxcms_form_id'], $this->params, $context);
      if (isset($form->fields['__failed'])) {
        return array(
          $form->fields
        );
      }
      return array(
        'status' => 200,
        'data' => $form
      );
    }
    else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'invalid request token',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/listFiles",
   *    tags={"hax","authenticated","file"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Load existing files for presentation in HAX find area"
   *   )
   * )
   */
  public function listFiles() {
    $files = array();
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    $search = (isset($this->params['filename'])) ? $this->params['filename'] : '';
    // build files directory path
    $fileDir = $site->directory . '/' . $site->manifest->metadata->site->name . '/files';
    if ($handle = opendir($fileDir)) {
      while (false !== ($file = readdir($handle))) {
        // ignore system files
          if (
              $file != "." &&
              $file != ".." &&
              $file != '.gitkeep' &&
              $file != '._.DS_Store' &&
              $file != '.DS_Store'
          ) {
              // ensure this is a file and if we are searching for results then return only exact ones
              if (is_file($fileDir . '/' . $file) && ($search == "" || strpos($file, $search) || strpos($file, $search) === 0)) {
                // @todo thumbnail support for non image media / thumbnails in general via internal cache / file call
                $files[] = array(
                  'path' => 'files/' . $file,
                  'fullUrl' =>
                      $GLOBALS['HAXCMS']->basePath .
                      $GLOBALS['HAXCMS']->sitesDirectory .
                      $fileDir . '/' .
                      $file,
                  'url' => 'files/' . $file,
                  'mimetype' => mime_content_type($fileDir . '/' . $file),
                  'name' => $file
                );
              }
          }
      }
      closedir($handle);
  }
    return $files;
  }
  /**
   * @OA\Post(
   *    path="/login",
   *    tags={"cms","user"},
   *    description="Attempt a user login",
   *    @OA\Parameter(
   *     description="User name",
   *     example="admin",
   *     name="u",
   *     in="query",
   *     required=true,
   *     @OA\Schema(type="string")
   *   ),
   *   @OA\Parameter(
   *     description="Password",
   *     example="admin",
   *     name="p",
   *     in="query",
   *     required=true,
   *     @OA\Schema(type="string")
   *   ),
   *    @OA\Response(
   *        response="200",
   *        description="JWT token as response"
   *   ),
   *    @OA\Response(
   *        response="403",
   *        description="Invalid token / Login is required"
   *   )
   * )
   */
  public function login() {
    // if we don't have a user and the don't answer, bail
    if (isset($this->params['u']) && isset($this->params['p'])) {
      // _ paranoia
      $u = $this->params['u'];
      // driving me insane
      $p = $this->params['p'];
      // _ paranoia ripping up my brain
      // test if this is a valid user login
      if (!$GLOBALS['HAXCMS']->testLogin($u, $p, true)) {
        return array(
          '__failed' => array(
            'status' => 403,
            'message' => 'Access denied',
          )
        );
      } else {
          // set a refresh_token COOKIE that will ship w/ all calls automatically
          setcookie('haxcms_refresh_token', $GLOBALS['HAXCMS']->getRefreshToken($u), $_expires = 0, $_path = '/', $_domain = '', $_secure = false, $_httponly = true);
          return $GLOBALS['HAXCMS']->getJWT($u);
      }
    }
    // login end point requested yet a jwt already exists
    // this is something of a revalidate case
    else if (isset($this->params['jwt'])) {
      return $GLOBALS['HAXCMS']->validateJWT();
    }
    else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'Login is required',
        )
      );
    } 
  }
  /**
   * @OA\Post(
   *    path="/logout",
   *    tags={"cms","user"},
   *    @OA\Response(
   *        response="200",
   *        description="User logout, front end will kill token"
   *   )
   * )
   */
  public function logout() {
    return 'loggedout';
  }
  /**
   * @OA\Post(
   *    path="/refreshAccessToken",
   *    tags={"cms","user"},
   *    @OA\Response(
   *        response="200",
   *        description="User access token for refreshing JWT when it goes stale"
   *   )
   * )
   */
  public function refreshAccessToken() {
    // check that we have a valid refresh token
    $validRefresh = $GLOBALS['HAXCMS']->validateRefreshToken(FALSE);
    // if we have a valid refresh token then issue a new access token
    if ($validRefresh) {
      return $GLOBALS['HAXCMS']->getJWT($validRefresh->user);
    }
    else {
      // this failed so unset the cookie
      setcookie('haxcms_refresh_token', '', 1);
      return array(
        '__failed' => array(
          'status' => 401,
          'message' => 'haxcms_refresh_token:invalid',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/setUserPhoto",
   *    tags={"cms","authenticated","user"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Set the user's uploaded photo"
   *   )
   * )
   */
  public function setUserPhoto() {
    // @todo might want to scrub prior to this level but not sure
    if (isset($_FILES['file-upload'])) {
      $upload = $_FILES['file-upload'];
      $file = new HAXCMSFile();
      $fileResult = $file->save($upload, 'system/user/files', null, 'thumbnail');
      if ($fileResult['status'] == 500) {
        return array(
          '__failed' => array(
            'status' => 500,
            'message' => 'failed to write',
          )
        );
      }
      // save this back to the user data object
      $values = new stdClass();
      $values->userPicture = $fileResult['data']['file']['fullUrl'];
      $GLOBALS['HAXCMS']->setUserData($values);
      return $fileResult;
    }
  }
  /**
   * @OA\Post(
   *    path="/saveFile",
   *    tags={"hax","authenticated","file"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Parameter(
   *         name="file-upload",
   *         description="File to upload",
   *         in="header",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 @OA\Property(
   *                     property="node",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                    "node": {
   *                      "id": ""
   *                    }
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="User is uploading a file to present in a site"
   *   )
   * )
   */
  public function saveFile() {
    // @todo might want to scrub prior to this level but not sure
    if (isset($_FILES['file-upload'])) {
      $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
      // update the page's content, using manifest to find it
      // this ensures that writing is always to what the file system
      // determines to be the correct page
      $page = $site->loadNode($this->params['node']['id']);
      $upload = $_FILES['file-upload'];
      $file = new HAXCMSFile();
      $fileResult = $file->save($upload, $site, $page);
      if ($fileResult['status'] == 500) {
        return array(
          '__failed' => array(
            'status' => 500,
            'message' => $fileResult['data'],
          )
        );
      }
      $site->gitCommit('File added: ' . $upload['name']);
      return $fileResult;
    }
  }

  /**
   * 
   * SITE LISTING CALLBACKS
   * 
   */

  /**
   * @OA\Get(
   *    path="/listSites",
   *    tags={"cms"},
   *    @OA\Response(
   *        response="200",
   *        description="Load a list of all sites the user has created"
   *   )
   * )
   */
  public function listSites() {
    // top level fake JOS
    $return = array(
      "id" => "123-123-123-123",
      "title" => "My sites",
      "author" => "me",
      "description" => "All of my micro sites I know and love.",
      "license" => "by-sa",
      "metadata" => array(),
      "items" => array()
    );
    // loop through files directory so we can cache those things too
    if ($handle = opendir(HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory)) {
      while (false !== ($item = readdir($handle))) {
        if ($item != "." && $item != ".." && is_dir(HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $item) && file_exists(HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $item . '/site.json')) {
          $json = file_get_contents(HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $item . '/site.json');
          $site = json_decode($json);
          if (isset($site->title)) {
            $site->indent = 0;
            $site->order = 0;
            $site->parent = null;
            $site->location = $GLOBALS['HAXCMS']->basePath . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $item . '/';
            $site->slug = $GLOBALS['HAXCMS']->basePath . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $item . '/';
            $site->metadata->pageCount = count($site->items);
            unset($site->items);
            $return['items'][] = $site;
          }
        }
      }
      closedir($handle);
    }
    return $return;
  }
  /**
   * @OA\Post(
   *    path="/createSite",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *     @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 @OA\Property(
   *                     property="theme",
   *                     type="object"
   *                 ),
   *                 required={"site","node"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite",
   *                      "description": "The description",
   *                      "domain": ""
   *                    },
   *                    "theme": {
   *                      "name": "clean-one",
   *                      "variables": {
   *                        "image":"",
   *                        "icon":"",
   *                        "hexCode":"",
   *                        "cssVariable":"",
   *                        }                   
   *                    }
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Create a new site"
   *   )
   * )
   */
  public function createSite() {
    if ($GLOBALS['HAXCMS']->validateRequestToken()) {
      $domain = null;
      // woohoo we can edit this thing!
      if (isset($this->params['site']['domain']) && $this->params['site']['domain'] != null && $this->params['site']['domain'] != '') {
        $domain = $this->params['site']['domain'];
      }
      // sanitize name
      $name = $GLOBALS['HAXCMS']->generateMachineName($this->params['site']['name']);
      $site = $GLOBALS['HAXCMS']->loadSite(
          strtolower($name),
          true,
          $domain
      );
      // now get a new item to reference this into the top level sites listing
      $schema = $GLOBALS['HAXCMS']->outlineSchema->newItem();
      $schema->id = $site->manifest->id;
      $schema->title = $name;
      $schema->location =
          $GLOBALS['HAXCMS']->basePath .
          $GLOBALS['HAXCMS']->sitesDirectory .
          '/' .
          $site->manifest->metadata->site->name .
          '/index.html';
      $schema->metadata->site = new stdClass();
      $schema->metadata->theme = new stdClass();
      $schema->metadata->site->name = $site->manifest->metadata->site->name;
      if (isset($this->params['site']['theme']) && is_string($this->params['site']['theme'])) {
        $theme = $this->params['site']['theme'];
      }
      else {
        $theme = HAXCMS_DEFAULT_THEME;
      }
      // look for a match so we can set the correct data
      foreach ($GLOBALS['HAXCMS']->getThemes() as $key => $themeObj) {
          if ($theme == $key) {
              $schema->metadata->theme = $themeObj;
          }
      }
      $schema->metadata->theme->variables = new stdClass();
      // description for an overview if desired
      if (isset($this->params['site']['description']) && $this->params['site']['description'] != '' && $this->params['site']['description'] != null) {
          $schema->description = strip_tags($this->params['site']['description']);
      }
      // background image / banner
      if (isset($this->params['theme']['image']) && $this->params['theme']['image'] != '' && $this->params['theme']['image'] != null) {
        $schema->metadata->site->logo = $this->params['theme']['image'];
      }
      else {
        $schema->metadata->site->logo = 'assets/banner.jpg';
      }
      // icon to express the concept / visually identify site
      if (isset($this->params['theme']['icon']) && $this->params['theme']['icon'] != '' && $this->params['theme']['icon'] != null) {
          $schema->metadata->theme->variables->icon = $this->params['theme']['icon'];
      }
      // slightly style the site based on css vars and hexcode
      if (isset($this->params['theme']['hexCode']) && $this->params['theme']['hexCode'] != '' && $this->params['theme']['hexCode'] != null) {
          $hex = $this->params['theme']['hexCode'];
      } else {
          $hex = '#aeff00';
      }
      $schema->metadata->theme->variables->hexCode = $hex;
      if (isset($this->params['theme']['cssVariable']) && $this->params['theme']['cssVariable'] != '' && $this->params['theme']['cssVariable'] != null) {
          $cssvar = $this->params['theme']['cssVariable'];
      } else {
          $cssvar = '--simple-colors-default-theme-light-blue-7';
      }
      $schema->metadata->theme->variables->cssVariable = $cssvar;
      $schema->metadata->site->created = time();
      $schema->metadata->site->updated = time();
      // check for publishing settings being set globally in HAXCMS
      // this would allow them to fork off to different locations down stream
      $schema->metadata->site->git = new stdClass();
      if (isset($GLOBALS['HAXCMS']->config->site->git->vendor)) {
          $schema->metadata->site->git =
              $GLOBALS['HAXCMS']->config->site->git;
          unset($schema->metadata->site->git->keySet);
          unset($schema->metadata->site->git->email);
          unset($schema->metadata->site->git->user);
      }
      // mirror the metadata information into the site's info
      // this means that this info is available to the full site listing
      // as well as this individual site. saves on performance / calls
      // later on if we only need to hit 1 file each time to get all the
      // data we need.
      foreach ($schema->metadata as $key => $value) {
          $site->manifest->metadata->{$key} = $value;
      }
      $site->manifest->metadata->node = new stdClass();
      $site->manifest->metadata->node->fields = new stdClass();
      $site->manifest->description = $schema->description;
      // save the outline into the new site
      $site->manifest->save(false);
      // main site schema doesn't care about publishing settings
      unset($schema->metadata->site->git);
      $git = new Git();
      $repo = $git->open(
          $site->directory . '/' . $site->manifest->metadata->site->name
      );
      $repo->add('.');
      $site->gitCommit(
          'A new journey begins: ' .
              $site->manifest->title .
              ' (' .
              $site->manifest->id .
              ')'
      );
      // make a branch but dont use it
      if (isset($site->manifest->metadata->site->git->staticBranch)) {
          $repo->create_branch(
              $site->manifest->metadata->site->git->staticBranch
          );
      }
      if (isset($site->manifest->metadata->site->git->branch)) {
          $repo->create_branch(
              $site->manifest->metadata->site->git->branch
          );
      }
      return $schema;
    }
    else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'invalid request token',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/gitImportSite",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "git": {
   *                        "url": ""
   *                      }
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Create a new site from a git repo reference"
   *   )
   * )
   */
  public function gitImportSite() {
    if ($GLOBALS['HAXCMS']->validateRequestToken()) {
      if (isset($this->params['site']['git']['url'])) {
        $repoUrl = $this->params['site']['git']['url'];
        // make sure there's a .git in the address
        if (filter_var($repoUrl, FILTER_VALIDATE_URL) !== false &&
            strpos($repoUrl, '.git')
          ) {
          $ary = explode('/', str_replace('.git', '', $repoUrl));
          $repo_path = array_pop($ary);
          $git = new Git();
          // @todo check if this fails
          $directory = HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $repo_path;
          $repo = @$git->create($directory);
          $repo = @$git->open($directory, true);
          @$repo->set_remote("origin", $repoUrl);
          @$repo->pull('origin', 'master');
          
          // this ensures that our repo doesn't get squashed by a sanitization
          // check that's baked into site loading.
          // This is safe / nessecary because the git repo url could be
          // any name for the repo but we do a lot of security checks when
          // user input is involved. As this is user input but from a valid git
          // url (which would have failed above if it wasn't real)
          // working with JSON Outline Schema instead of the extrapolations
          include_once 'JSONOutlineSchema.php';
          $manifest = new JSONOutlineSchema();
          $manifest->load(HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $repo_path . '/site.json');
          // repo name matches site->manifest->site->name value as they don't
          // have to be identical but also is a crud test for if this is a valid
          // site.json format in the first place
          if (isset($manifest->metadata) && $repo_path != $manifest->metadata->site->name) {
            // move directory from the git repo based name to the folder name
            // that the system will expect
            rename(
              HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $repo_path,
              HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $manifest->metadata->site->name);
            // update this to ensure it works when we do a full site load
            $repo_path = $manifest->metadata->site->name;
          }
          // load the site that we SHOULD have just pulled in
          if ($site = $GLOBALS['HAXCMS']->loadSite($repo_path)) {
            return array(
              'manifest' => $site->manifest
            );
          }
          else {
            return array(
              '__failed' => array(
                'status' => 500,
                'message' => 'invalid url',
              )
            );
          }
        }
      }
      return array(
        '__failed' => array(
          'status' => 500,
          'message' => 'invalid url',
        )
      );
    }
    else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'invalid request token',
        )
      );
    }
  }
  /**
   * Get configuration related to HAXcms itself
   */
  /**
   * @OA\Post(
   *    path="/getConfig",
   *    tags={"cms","authenticated","settings"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Get configuration for HAXcms itself"
   *   )
   * )
   */
  public function getConfig() {
    $response = new stdClass();
    $response->schema = $GLOBALS['HAXCMS']->getConfigSchema();
    $response->values = $GLOBALS['HAXCMS']->config;
    foreach ($response->values->appStore as $key => $val) {
      if ($key !== 'apiKeys') {
        unset($response->values->appStore->{$key});
      }
    }
    return $response;
  }
  /**
   * Get configuration related to HAX appstore. This allows the user to set valid
   * configuration via a front-end presented form.
   */
  /**
   * @OA\Get(
   *    path="/haxConfigurationSelectionData",
   *    tags={"editor","authenticated","settings"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Get configuration for HAX in how appstore is constructed"
   *   )
   * )
   */
  public function haxConfigurationSelectionData() {
    $response = new stdClass();
    return $response;
  }
  /**
   * @OA\Post(
   *    path="/setConfig",
   *    tags={"cms","authenticated","form","settings"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="values",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "values": {}
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Set configuration for HAXcms"
   *   )
   * )
   */
  public function setConfig() {
    if ($GLOBALS['HAXCMS']->validateRequestToken()) {
      $values = $this->rawParams['values'];
      $val = new stdClass();
      if (isset($values->apis) && isset($values->appStore->apiKeys)) {
        $val->apis = $values->apis;
      }
      if (isset($values->publishing)) {
        $val->publishing = $values->publishing;
      }
      $response = $GLOBALS['HAXCMS']->setConfig($val);
      return $response;
    } else {
      return array(
        '__failed' => array(
          'status' => 403,
          'message' => 'failed to validate request token',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/syncSite",
   *    tags={"cms","authenticated","git","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Sync the site using the git config settings in the site.json file"
   *   )
   * )
   */
  public function syncSite() {
    // ensure we have something we can load and ship back out the door
    if ($site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name'])) {
      // local publishing options, then defer to system, then make some up...
      if (isset($site->manifest->metadata->site->git)) {
          $gitSettings = $site->manifest->metadata->site->git;
      } elseif (isset($GLOBALS['HAXCMS']->config->site->git)) {
          $gitSettings = $GLOBALS['HAXCMS']->config->site->git;
      } else {
          $gitSettings = new stdClass();
          $gitSettings->vendor = 'github';
          $gitSettings->branch = 'master';
          $gitSettings->staticBranch = 'gh-pages';
          $gitSettings->url = '';
      }
      if (isset($gitSettings)) {
          $git = new Git();
          $siteDirectoryPath = $site->directory . '/' . $site->manifest->metadata->site->name;
          $repo = $git->open($siteDirectoryPath, true);
          // ensure we're on branch, most likley master
          $repo->checkout($gitSettings->branch);
          $repo->pull('origin', $gitSettings->branch);
          $repo->push('origin', $gitSettings->branch);
          return TRUE;
      }
    } else {
      return array(
        '__failed' => array(
          'status' => 500,
          'message' => 'Unable to load site',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/publishSite",
   *    tags={"cms","authenticated","git","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Publishes the site to a remote source using git settings from site.json for details "
   *   )
   * )
   */
  public function publishSite() {
    // ensure we have something we can load and ship back out the door
    if ($site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name'])) {
        // local publishing options, then defer to system, then make some up...
        if (isset($site->manifest->metadata->site->git)) {
            $gitSettings = $site->manifest->metadata->site->git;
        } elseif (isset($GLOBALS['HAXCMS']->config->site->git)) {
            $gitSettings = $GLOBALS['HAXCMS']->config->site->git;
        } else {
            $gitSettings = new stdClass();
            $gitSettings->vendor = 'github';
            $gitSettings->branch = 'master';
            $gitSettings->staticBranch = 'gh-pages';
            $gitSettings->url = '';
        }
        if (isset($gitSettings)) {
            $git = new Git();
            $siteDirectoryPath =
                $site->directory . '/' . $site->manifest->metadata->site->name;
            $repo = $git->open($siteDirectoryPath, true);
            // ensure we're on master and everything is added
            $repo->checkout('master');
            // Try to build a reasonable "domain" value
            if (
                isset($gitSettings->url) &&
                $gitSettings->url != '' &&
                $gitSettings->url != false &&
                $gitSettings->url !=
                    '/' . $site->manifest->metadata->site->name . '.git'
            ) {
                $domain = $gitSettings->url;
                if (
                    isset($site->manifest->metadata->site->domain) &&
                    $site->manifest->metadata->site->domain != ''
                ) {
                    $domain = $site->manifest->metadata->site->domain;
                } else {
                    // support blowing up github addresses correctly
                    $parts = explode(
                        '/',
                        str_replace(
                            'git@github.com:',
                            '',
                            str_replace('.git', '', $domain)
                        )
                    );
                    if (count($parts) === 2) {
                        $domain =
                            'https://' . $parts[0] . '.github.io/' . $parts[1];
                    }
                }
            }
            // implies the domain is actually on the system locally
            else {
                $domain =
                    $GLOBALS['HAXCMS']->basePath .
                    $GLOBALS['HAXCMS']->publishedDirectory .
                    '/' .
                    $site->manifest->metadata->site->name .
                    '/';
            }
            // ensure we have the latest dynamic element loader since it may have improved from
            // when we first launched this site, HAX would have these definitions as well but
            // when in production, appstore isn't around so the user may have added custom
            // things that they care about but now magically in a published state its gone
            // set last published time to now
            if (!isset($site->manifest->metadata->site->static)) {
              $site->manifest->metadata->site->static = new stdClass();
            }
            $site->manifest->metadata->site->static->lastPublished = time();
            $site->manifest->metadata->site->static->publishedLocation = $domain;
            $site->manifest->save(false);
            // just to be safe in case the push isn't successful
            try {
                $repo->add('.');
                $repo->commit('Clean up pre-publishing..');
                @$repo->push('origin', 'master');
            } catch (Exception $e) {
                // do nothing, we might be offline or something
                // @tood when we get into logging this would be worth logging
            }
            // now check out the publishing branch, it can't be master or our file will get mixed up
            // rather rapidly..
            if ($gitSettings->staticBranch != 'master') {
                // try to check it out, if not then we need to create it
                try {
                    $repo->checkout($gitSettings->staticBranch);
                    // on that branch now we need to forcibly get the master branch over top of this
                    $repo->reset($gitSettings->branch, 'origin');
                    // now we can merge safely because we've already got the files over top
                    // as if they originated here
                    $repo->merge($gitSettings->branch);
                } catch (Exception $e) {
                    $repo->create_branch($gitSettings->staticBranch);
                    $repo->checkout($gitSettings->staticBranch);
                }
            }
            // werid looking I know but if we have a CDN then we need to "rewrite" this file
            if (isset($site->manifest->metadata->site->static->cdn)) {
                $cdn = $site->manifest->metadata->site->static->cdn;
            } else {
                $cdn = 'custom';
            }
            // sanity check
            if (
                file_exists(
                    HAXCMS_ROOT . '/system/boilerplate/cdns/' . $cdn . '.html'
                )
            ) {
                // move the index.html and unlink the symlinks otherwise we'll get build failures
                if (is_link($siteDirectoryPath . '/build')) {
                    @unlink($siteDirectoryPath . '/build');
                }
                if (is_link($siteDirectoryPath . '/dist')) {
                    @unlink($siteDirectoryPath . '/dist');
                }
                if (is_link($siteDirectoryPath . '/node_modules')) {
                    @unlink($siteDirectoryPath . '/node_modules');
                }
                if (is_link($siteDirectoryPath . '/wc-registry.json')) {
                  @unlink($siteDirectoryPath . '/wc-registry.json');
                }
                if (is_link($siteDirectoryPath . '/assets/babel-top.js')) {
                    @unlink($siteDirectoryPath . '/assets/babel-top.js');
                }
                if (is_link($siteDirectoryPath . '/assets/babel-bottom.js')) {
                    @unlink($siteDirectoryPath . '/assets/babel-bottom.js');
                }
                // copy these things because we have a local routine
                if ($cdn == 'custom') {
                    @copy(
                        HAXCMS_ROOT . '/babel/babel-top.js',
                        $siteDirectoryPath . '/assets/babel-top.js'
                    );
                    @copy(
                        HAXCMS_ROOT . '/babel/babel-bottom.js',
                        $siteDirectoryPath . '/assets/babel-bottom.js'
                    );
                    $GLOBALS['fileSystem']->mirror(
                        HAXCMS_ROOT . '/build',
                        $siteDirectoryPath . '/build'
                    );
                }
                // additional files to move to ensure we don't screw things up
                $templates = $site->getManagedTemplateFiles();
                // overwrite these files with their boilerplate versions
                // so that our templateVars can be relative to a published state
                // as opposed to a local working state
                foreach ($templates as $file) {
                  copy(HAXCMS_ROOT . '/system/boilerplate/site/' . $file, $siteDirectoryPath . '/' . $file);
                }
                // support for index as that comes from a CDN defining what to do
                // remove current index, then pull a new one
                // this ensures that the php file won't be in the published copy while it is in master
                $GLOBALS['fileSystem']->remove([$siteDirectoryPath . '/index.html', $siteDirectoryPath . '/index.php']);
                copy(HAXCMS_ROOT . '/system/boilerplate/cdns/' . $cdn . '.html', $siteDirectoryPath . '/index.html');
                // process twig variables for static publishing
                $licenseData = $site->getLicenseData('all');
                $licenseLink = '';
                $licenseName = '';
                if (isset($site->manifest->license) && isset($licenseData[$site->manifest->license])) {
                  $licenseLink = $licenseData[$site->manifest->license]['link'];
                  $licenseName = 'License: ' . $licenseData[$site->manifest->license]['name'];
                }
                $templateVars = array(
                    'hexCode' => HAXCMS_FALLBACK_HEX,
                    'version' => $GLOBALS['HAXCMS']->getHAXCMSVersion(),
                    'basePath' =>
                        '/' . $site->manifest->metadata->site->name . '/',
                    'title' => $site->manifest->title,
                    'short' => $site->manifest->metadata->site->name,
                    'domain' => $site->manifest->metadata->site->domain,
                    'description' => $site->manifest->description,
                    'forceUpgrade' => $site->getForceUpgrade(),
                    'swhash' => array(),
                    'ghPagesURLParamCount' => 1,
                    'licenseLink' => $licenseLink,
                    'licenseName' => $licenseName,
                    'serviceWorkerScript' => $site->getServiceWorkerScript('/' . $site->manifest->metadata->site->name . '/', TRUE),
                    'bodyAttrs' => $site->getSitePageAttributes(),
                    'metadata' => $site->getSiteMetadata(),
                    'logo512x512' => $site->getLogoSize('512','512'),
                    'logo310x310' => $site->getLogoSize('310','310'),
                    'logo192x192' => $site->getLogoSize('192','192'),
                    'logo150x150' => $site->getLogoSize('150','150'),
                    'logo144x144' => $site->getLogoSize('144','144'),
                    'logo96x96' => $site->getLogoSize('96','96'),
                    'logo72x72' => $site->getLogoSize('72','72'),
                    'logo70x70' => $site->getLogoSize('70','70'),
                    'logo48x48' => $site->getLogoSize('48','48'),
                    'logo36x36' => $site->getLogoSize('36','36'),
                    'favicon' => $site->getLogoSize('16','16'),
                );
                // custom isn't a regex by design
                if ($cdn != 'custom') {
                  // special fallback for HAXtheWeb since it cheats in order to demo the solution
                  if ($cdn == 'cdn.webcomponents.psu.edu') {
                    $templateVars['cdn'] = $cdn . 'cdn/';
                  }
                  else {
                    $templateVars['cdn'] = $cdn;
                  }
                  $templateVars['metadata'] = $site->getSiteMetadata(NULL, $domain, 'https://' . $templateVars['cdn']);
                  // build a regex so that we can do fully offline sites and cache the cdn requests even
                  $templateVars['cdnRegex'] =
                    "(https?:\/\/" .
                    str_replace('.', '\.', $templateVars['cdn']) .
                    "(\/[A-Za-z0-9\-\._~:\/\?#\[\]@!$&'\(\)\*\+,;\=]*)?)";
                  // support for disabling regex via offline setting
                  if (isset($site->manifest->metadata->site->static->offline) && !$site->manifest->metadata->site->static->offline) {
                    unset($templateVars['cdnRegex']);
                  }
                }
                // if we have a custom domain, try and engineer the base path
                // correctly for the manifest / service worker
                // @todo need to support domains that have subdomains in them
                if (
                    isset($site->manifest->metadata->site->domain) &&
                    $site->manifest->metadata->site->domain != ''
                ) {
                    $parts = parse_url($site->manifest->metadata->site->domain);
                    $templateVars['basePath'] = '/';
                    if (isset($parts['base'])) {
                        $templateVars['basePath'] = $parts['base'];
                    }
                    if ($templateVars['basePath'] == null || $templateVars['basePath'] == '' || $templateVars['basePath'] == false) {
                      $templateVars['basePath'] = "/";
                    }
                    if ($templateVars['basePath'] == '/') {
                        $templateVars['ghPagesURLParamCount'] = 0;
                    }
                    // now we need to update the SW to match
                    $templateVars['serviceWorkerScript'] = $site->getServiceWorkerScript($templateVars['basePath'], TRUE);
                }
                if (isset($site->manifest->metadata->theme->variables->hexCode)) {
                    $templateVars['hexCode'] =
                        $site->manifest->metadata->theme->variables->hexCode;
                }
                $swItems = $site->manifest->items;
                // the core files you need in every SW manifest
                $coreFiles = array(
                    'index.html',
                    'manifest.json',
                    'site.json',
                    $site->getLogoSize('512','512'),
                    $site->getLogoSize('310','310'),
                    $site->getLogoSize('192','192'),
                    $site->getLogoSize('150','150'),
                    $site->getLogoSize('144','144'),
                    $site->getLogoSize('96','96'),
                    $site->getLogoSize('72','72'),
                    $site->getLogoSize('70','70'),
                    $site->getLogoSize('48','48'),
                    $site->getLogoSize('36','36'),
                    $site->getLogoSize('16','16'),
                    '404.html',
                );
                // loop through files directory so we can cache those things too
                if ($handle = opendir($siteDirectoryPath . '/files')) {
                    while (false !== ($file = readdir($handle))) {
                        if (
                            $file != "." &&
                            $file != ".." &&
                            $file != '.gitkeep' &&
                            $file != '._.DS_Store' &&
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
                try {
                    $repo->add('.');
                    $repo->commit('Published using CDN: ' . $cdn);
                } catch (Exception $e) {
                    // do nothing, maybe there was nothing to commit
                }
            }
            // mirror over to the publishing directory
            // @todo need to make a way of doing this in a variable fashion
            // this way we could publish to multiple locations or intentionally to a location
            // which will be important when allowing for open, closed, or other server level configurations
            // that happen automatically as opposed to when the user hits publish
            // also for delivery of the "click to access site" link
            $GLOBALS['fileSystem']->mirror(
                $siteDirectoryPath,
                $GLOBALS['HAXCMS']->configDirectory . '/../_published/' . $site->manifest->metadata->site->name
            );
            // remove the .git version control from this, it's not needed
            $GLOBALS['fileSystem']->remove([
                $GLOBALS['HAXCMS']->configDirectory . '/../_published/' . $site->manifest->metadata->site->name . '/.git'
            ]);
            // rewrite the base path to ensure it is accurate based on a local build publish vs web
            $index = file_get_contents(
                $GLOBALS['HAXCMS']->configDirectory . '/../_published/' .
                    $site->manifest->metadata->site->name .
                    '/index.html'
            );
            // replace if it was publishing with the name in it
            $index = str_replace(
                '<base href="/' . $site->manifest->metadata->site->name . '/"',
                '<base href="' . $GLOBALS['HAXCMS']->basePath . '_published/' .
                    $site->manifest->metadata->site->name .
                    '/"',
                $index
            );
            // replace if it has a vanity domain
            $index = str_replace(
                '<base href="/"',
                '<base href="' . $GLOBALS['HAXCMS']->basePath . '_published/' .
                    $site->manifest->metadata->site->name .
                    '/"',
                $index
            );
            // rewrite the file
            @file_put_contents(
                $GLOBALS['HAXCMS']->configDirectory . '/../_published/' .
                    $site->manifest->metadata->site->name .
                    '/index.html',
                $index
            );
            // tag, attempt to push, and set things up for next time
            $repo->add_tag(
                'version-' . $site->manifest->metadata->site->static->lastPublished
            );
            @$repo->push(
                'origin',
                'version-' . $site->manifest->metadata->site->static->lastPublished,
                "--force"
            );
            if ($gitSettings->staticBranch != 'master') {
                @$repo->push('origin', $gitSettings->staticBranch, "--force");
                // now put it back plz... and master shouldn't notice any source changes
                $repo->checkout($gitSettings->branch);
            }
            // restore these silly things if we need to
            if (!is_link($siteDirectoryPath . '/dist')) {
                @symlink('../../dist', $siteDirectoryPath . '/dist');
            }
            if (!is_link($siteDirectoryPath . '/node_modules')) {
                @symlink(
                    '../../node_modules',
                    $siteDirectoryPath . '/node_modules'
                );
            }
            if (is_link($siteDirectoryPath . '/wc-registry.json')) {
              @unlink($siteDirectoryPath . '/wc-registry.json');
            }
            if (is_link($siteDirectoryPath . '/assets/babel-top.js')) {
                @unlink($siteDirectoryPath . '/assets/babel-top.js');
            }
            if (is_link($siteDirectoryPath . '/assets/babel-bottom.js')) {
                @unlink($siteDirectoryPath . '/assets/babel-bottom.js');
            }
            if (is_link($siteDirectoryPath . '/build')) {
                @unlink($siteDirectoryPath . '/build');
            }
            else {
                $GLOBALS['fileSystem']->remove([$siteDirectoryPath . '/build']);
            }
            @symlink('../../wc-registry.json', $siteDirectoryPath . '/wc-registry.json');
            @symlink(
                '../../../babel/babel-top.js',
                $siteDirectoryPath . '/assets/babel-top.js'
            );
            @symlink(
                '../../../babel/babel-bottom.js',
                $siteDirectoryPath . '/assets/babel-bottom.js'
            );
            @symlink('../../build', $siteDirectoryPath . '/build');
            // reset the templated file for the index.html
            // since the "CDN" cleaned up how this worked most likely at run time
            $GLOBALS['fileSystem']->remove([$siteDirectoryPath . '/index.html']);
            copy(HAXCMS_ROOT . '/system/boilerplate/site/index.html', $siteDirectoryPath . '/index.html');
            // this ensures that the php file wasn't in version control for the published copy
            copy(HAXCMS_ROOT . '/system/boilerplate/site/index.php', $siteDirectoryPath . '/index.php');
            return array(
                'status' => 200,
                'url' => $domain,
                'label' => 'Click to access ' . $site->manifest->title,
                'response' => 'Site published!',
                'output' => 'Site published successfully if no errors!'
            );
        }
    } else {
      return array(
            '__failed' => array(
              'status' => 500,
              'message' => 'Unable to load site',
            )
          );
    }
  }
  /**
   * @OA\Post(
   *    path="/cloneSite",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Clone a site by copying and renaming the folder on file system"
   *   )
   * )
   */
  public function cloneSite() {
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    $siteDirectoryPath = $site->directory . '/' . $site->manifest->metadata->site->name;
    $cloneName = $GLOBALS['HAXCMS']->getUniqueName($site->name);
    // ensure the path to the new folder is valid
    $GLOBALS['fileSystem']->mirror(
        HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $site->name,
        HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $cloneName
    );
    // we need to then load and rewrite the site name var or it will conflict given the name change
    $site = $GLOBALS['HAXCMS']->loadSite($cloneName);
    $site->manifest->metadata->site->name = $cloneName;
    $site->save();
    return array(
      'link' =>
        $GLOBALS['HAXCMS']->basePath .
        $GLOBALS['HAXCMS']->sitesDirectory .
        '/' .
        $cloneName,
      'name' => $cloneName
    );
  }
  /**
   * @OA\Post(
   *    path="/deleteSite",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Delete a site from the file system"
   *   )
   * )
   */
  public function deleteSite() {
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    if ($site->name) {
      $GLOBALS['fileSystem']->remove([
        $site->directory . '/' . $site->manifest->metadata->site->name
      ]);
      return array(
        'name' => $site->name,
        'detail' => 'Site deleted',
      );
    }
    else {
      return array(
        '__failed' => array(
          'status' => 500,
          'message' => 'Site does not exist!',
        )
      );
    }
  }
  /**
   * @OA\Post(
   *    path="/downloadSite",
   *    tags={"cms","authenticated","site","meta"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Download the site folder as a zip file"
   *   )
   * )
   */
  public function downloadSite() {
    // load site
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    // helpful boilerplate https://stackoverflow.com/questions/29873248/how-to-zip-a-whole-directory-and-download-using-php
    $dir = HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $site->name;
    // form a basic name
    $zip_file =
      HAXCMS_ROOT .
      '/' .
      $GLOBALS['HAXCMS']->publishedDirectory .
      '/' .
      $site->name .
      '.zip';
    // Get real path for our folder
    $rootPath = realpath($dir);
    // Initialize archive object
    $zip = new ZipArchive();
    $zip->open($zip_file, ZipArchive::CREATE | ZipArchive::OVERWRITE);
    // Create recursive directory iterator
    $directory = new RecursiveDirectoryIterator($rootPath);
    $filtered = new DirFilter($directory, array('node_modules'));
    $files = new RecursiveIteratorIterator($filtered);
    foreach ($files as $name => $file) {
      // Skip directories (they would be added automatically)
      if (!$file->isDir()) {
        // Get real and relative path for current file
        $filePath = $file->getRealPath();
        $relativePath = substr($filePath, strlen($rootPath) + 1);
        // Add current file to archive
        if ($filePath != '' && $relativePath != '') {
          $zip->addFile($filePath, $relativePath);
        }
      }
    }
    // Zip archive will be created only after closing object
    $zip->close();
    return array(
      'link' =>
        $GLOBALS['HAXCMS']->basePath .
        $GLOBALS['HAXCMS']->publishedDirectory .
        '/' .
        basename($zip_file),
      'name' => basename($zip_file)
    );
  }
  /**
   * @OA\Post(
   *    path="/archiveSite",
   *    tags={"cms","authenticated","site"},
   *    @OA\Parameter(
   *         name="jwt",
   *         description="JSON Web token, obtain by using  /login",
   *         in="query",
   *         required=true,
   *         @OA\Schema(type="string")
   *    ),
   *    @OA\RequestBody(
   *        @OA\MediaType(
   *             mediaType="application/json",
   *             @OA\Schema(
   *                 @OA\Property(
   *                     property="site",
   *                     type="object"
   *                 ),
   *                 required={"site"},
   *                 example={
   *                    "site": {
   *                      "name": "mynewsite"
   *                    },
   *                 }
   *             )
   *         )
   *    ),
   *    @OA\Response(
   *        response="200",
   *        description="Archive a site by moving it on the file system"
   *   )
   * )
   */
  public function archiveSite() {
    $site = $GLOBALS['HAXCMS']->loadSite($this->params['site']['name']);
    if ($site->name) {
      rename(
        HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->sitesDirectory . '/' . $site->manifest->metadata->site->name,
        HAXCMS_ROOT . '/' . $GLOBALS['HAXCMS']->archivedDirectory . '/' . $site->manifest->metadata->site->name);
      return array(
        'name' => $site->name,
        'detail' => 'Site archived',
      );
    }
    else {
      return array(
        '__failed' => array(
          'status' => 500,
          'message' => 'Site does not exist',
        )
      );
    }
  }
}