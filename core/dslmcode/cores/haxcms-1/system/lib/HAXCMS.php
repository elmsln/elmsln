<?php
/**
 * HAXCMS - The worlds smallest, most nothing yet most empowering CMS.
 * Simply a tremendous CMS. The greatest.
 */
// service creation / HAX app store service abstraction
include_once 'HAXService.php';
// working with sites
include_once 'HAXCMSSite.php';
// working with files
include_once 'HAXCMSFile.php';
// working with JSON Outline Schema
include_once 'JSONOutlineSchema.php';
// working with json web tokens
include_once 'JWT.php';
// working with git operators
include_once 'Git.php';
// composer...ugh
include_once dirname(__FILE__) . "/../../vendor/autoload.php";
use Symfony\Component\Filesystem\Filesystem;
use Symfony\Component\Filesystem\Exception\IOExceptionInterface;
global $fileSystem;
$fileSystem = new Filesystem();

class HAXCMS
{
    public $appStoreFile;
    public $salt;
    public $outlineSchema;
    public $privateKey;
    public $config;
    public $superUser;
    public $user;
    public $sitesDirectory;
    public $archivedDirectory;
    public $publishedDirectory;
    public $sites;
    public $data;
    public $configDirectory;
    public $sitesJSON;
    public $domain;
    public $protocol;
    public $basePath;
    public $safePost;
    public $safeGet;
    public $safeInputStream;
    public $sessionJwt;
    public $sessionToken;
    public $siteListingAttr;
    private $events;
    /**
     * Establish defaults for HAXCMS
     */
    public function __construct()
    {
        // stupid session less handling thing
        $_POST = (array) json_decode(file_get_contents('php://input'));
        // handle sanitization on request data, drop security things
        $this->safePost = filter_var_array($_POST, FILTER_SANITIZE_STRING);
        if (isset($this->safePost['jwt'])) {
          $this->sessionJwt = $this->safePost['jwt'];
        }
        unset($this->safePost['jwt']);
        if (isset($this->safePost['token'])) {
          $this->sessionToken = $this->safePost['token'];
        }
        unset($this->safePost['token']);
        $this->safeGet = filter_var_array($_GET, FILTER_SANITIZE_STRING);
        // Get HTTP/HTTPS (the possible values for this vary from server to server)
        $this->protocol =
            isset($_SERVER['HTTPS']) &&
            $_SERVER['HTTPS'] &&
            !in_array(strtolower($_SERVER['HTTPS']), array('off', 'no'))
                ? 'https'
                : 'http';
        $this->domain = $_SERVER['HTTP_HOST'];
        $this->siteListing = new stdClass();
        $this->siteListing->attr = '';
        $this->siteListing->slot = '';
        // auto generate base path
        $this->basePath = '/';
        $this->config = new stdClass();
        // set up user account stuff
        $this->superUser = new stdClass();
        $this->superUser->name = null;
        $this->superUser->password = null;
        $this->user = new stdClass();
        $this->user->name = null;
        $this->user->password = null;
        $this->outlineSchema = new JSONOutlineSchema();
        // end point to get the sites data
        $this->sitesJSON = 'system/listSites.php';
        // sites directory
        if (is_dir(HAXCMS_ROOT . '/_sites')) {
            $this->sitesDirectory = '_sites';
        }
        // archived directory
        if (is_dir(HAXCMS_ROOT . '/_archived')) {
            $this->archivedDirectory = '_archived';
        }
        // published directory
        if (is_dir(HAXCMS_ROOT . '/_published')) {
            $this->publishedDirectory = '_published';
        }
        /// support the nicer looking symlink paths if they exist
        if (is_link(HAXCMS_ROOT . '/sites')) {
            $this->sitesDirectory = 'sites';
        }
        if (is_link(HAXCMS_ROOT . '/archived')) {
            $this->archivedDirectory = 'archived';
        }
        if (is_link(HAXCMS_ROOT . '/published')) {
            $this->publishedDirectory = 'published';
        }
        // set default config directory to look in if there
        if (is_dir(HAXCMS_ROOT . '/_config')) {
            $this->configDirectory = HAXCMS_ROOT . '/_config';
            // add in the auto-generated app store file
            $this->appStoreFile = 'system/generateAppStore.php';
            // ensure appstore file is there, then make salt size of this file
            if (file_exists($this->configDirectory . '/SALT.txt')) {
                $this->salt = file_get_contents(
                    $this->configDirectory . '/SALT.txt'
                );
            }
            // check for a config json file to populate all configurable settings
            if (
                !($this->config = json_decode(
                    file_get_contents($this->configDirectory . '/config.json')
                ))
            ) {
                print $this->configDirectory . '/config.json missing';
            } else {
                // theme data
                if (!isset($this->config->themes)) {
                    $this->config->themes = new stdClass();
                }
                if (!isset($this->config->appJWTConnectionSettings)) {
                    $this->config->appJWTConnectionSettings = new stdClass();
                }
                // load in core theme data
                $themeData = json_decode(
                    file_get_contents(
                        HAXCMS_ROOT . '/system/coreConfig/themes.json'
                    )
                );
                foreach ($themeData as $name => $data) {
                    $this->config->themes->{$name} = $data;
                }
                // dynamicImporter
                if (!isset($this->config->dynamicElementLoader)) {
                    $this->config->dynamicElementLoader = new stdClass();
                }
                // load in core dynamicElementLoader data
                $dynamicElementLoader = json_decode(
                    file_get_contents(
                        HAXCMS_ROOT . '/system/coreConfig/dynamicElementLoader.json'
                    )
                );
                foreach ($dynamicElementLoader as $name => $data) {
                    $this->config->dynamicElementLoader->{$name} = $data;
                }
                // publishing endpoints
                if (!isset($this->config->publishing)) {
                    $this->config->publishing = new stdClass();
                }
                // load in core publishing data
                $publishingData = json_decode(
                    file_get_contents(
                        HAXCMS_ROOT . '/system/coreConfig/publishing.json'
                    )
                );
                foreach ($publishingData as $name => $data) {
                    $this->config->publishing->{$name} = $data;
                }
                // importer formats to ingest
                if (!isset($this->config->importers)) {
                    $this->config->importers = new stdClass();
                }
                // load in core importers data
                $importersData = json_decode(
                    file_get_contents(
                        HAXCMS_ROOT . '/system/coreConfig/importers.json'
                    )
                );
                foreach ($importersData as $name => $data) {
                    $this->config->importers->{$name} = $data;
                }
            }
            $this->dispatchEvent('haxcms-init', $this);
        }
    }
    /**
     * Load theme location data as mix of config and system
     */
    public function getThemes()
    {
        return $this->config->themes;
    }
    /**
     * Build valid JSON Schema for the config we have knowledge of
     */
    public function getConfigSchema()
    {
        $schema = new stdClass();
        $schema->{'$schema'} = "http://json-schema.org/schema#";
        $schema->title = "HAXCMS Config";
        $schema->type = "object";
        $schema->properties = new stdClass();
        $schema->properties->publishing = new stdClass();
        $schema->properties->publishing->title = "Publishing settings";
        $schema->properties->publishing->type = "object";
        $schema->properties->publishing->properties = new stdClass();
        $schema->properties->apis = new stdClass();
        $schema->properties->apis->title = "API Connectivity";
        $schema->properties->apis->type = "object";
        $schema->properties->apis->properties = new stdClass();
        // establish some defaults if nothing set internally
        $publishing = array(
            'vendor' => array(
                'name' => 'Vendor',
                'description' =>
                    'Name for this provided (github currently supported)',
                'value' => 'github'
            ),
            'branch' => array(
                'name' => 'Branch',
                'description' =>
                    'Project code branch (like master or gh-pages)',
                'value' => 'gh-pages'
            ),
            'url' => array(
                'name' => 'Repo url',
                'description' =>
                    'Base address / organization that new sites will be saved under',
                'value' => 'git@github.com:elmsln'
            ),
            'user' => array(
                'name' => 'User / Org',
                'description' => 'User name or organization to publish to',
                'value' => ''
            ),
            'email' => array(
                'name' => 'Email',
                'description' => 'Email address of your github account',
                'value' => ''
            ),
            'pass' => array(
                'name' => 'Password',
                'description' =>
                    'Only use this if you want to automate SSH key setup. This is not stored',
                'value' => ''
            ),
            'cdn' => array(
                'name' => 'CDN',
                'description' => 'A CDN address that supports HAXCMS',
                'value' => 'webcomponents.psu.edu'
            )
        );
        // publishing
        foreach ($publishing as $key => $value) {
            $props = new stdClass();
            $props->title = $value['name'];
            $props->type = 'string';
            if (isset($this->config->publishing->git->{$key})) {
                $props->value = $this->config->publishing->git->{$key};
            } else {
                $props->value = $value['value'];
            }
            $props->component = new stdClass();
            $props->component->name = "paper-input";
            $props->component->valueProperty = "value";
            $props->component->slot =
                '<div slot="suffix">' . $value['description'] . '</div>';
            if ($key == 'pass') {
                $props->component->attributes = new stdClass();
                $props->component->attributes->type = 'password';
            }
            if ($key == 'pass' && isset($this->config->publishing->git->user)) {
                // keep moving but if we already have a user name we don't need this
                // we only ask for a password on the very first run through
                $schema->properties->publishing->properties->user->component->slot =
                    '<div slot="suffix">Set, to change this manually edit _config/config.json.</div>';
                $schema->properties->publishing->properties->user->component->attributes = new stdClass();
                $schema->properties->publishing->properties->user->component->attributes->disabled =
                    'disabled';
                $schema->properties->publishing->properties->email->component->attributes = new stdClass();
                $schema->properties->publishing->properties->email->component->attributes->disabled =
                    'disabled';
                $schema->properties->publishing->properties->email->component->slot =
                    '<div slot="suffix">Set, to change this manually edit _config/config.json.</div>';
            } else {
                $schema->properties->publishing->properties->{$key} = $props;
            }
        }
        // API keys
        $hax = new HAXService();
        $apiDocs = $hax->baseSupportedApps();
        foreach ($apiDocs as $key => $value) {
            $props = new stdClass();
            $props->title = $key;
            $props->type = 'string';
            // if we have this value loaded internally then set it
            if (isset($this->config->appStore->apiKeys->{$key})) {
                $props->value = $this->config->appStore->apiKeys->{$key};
            }
            $props->component = new stdClass();
            // look for our documentation object name
            if (isset($apiDocs[$key])) {
                $props->title = $apiDocs[$key]['name'];
                $props->component->slot =
                    '<div slot="suffix"><a href="' .
                    $apiDocs[$key]['docs'] .
                    '" target="_blank">See ' .
                    $props->title .
                    ' developer docs.</a></div>';
            }
            $props->component->name = "paper-input";
            $props->component->valueProperty = "value";
            $schema->properties->apis->properties->{$key} = $props;
        }
        return $schema;
    }
    /**
     * Set and validate config
     */
    public function setConfig($values)
    {
        if (isset($values->apis)) {
            foreach ($values->apis as $key => $val) {
                $this->config->appStore->apiKeys->{$key} = $val;
            }
        }
        if (!isset($this->config->publishing)) {
            $this->config->publishing = new stdClass();
        }
        if (!isset($this->config->publishing->git)) {
            $this->config->publishing->git = new stdClass();
        }
        if ($values->publishing) {
            foreach ($values->publishing as $key => $val) {
                $this->config->publishing->git->{$key} = $val;
            }
        }
        // test for a password in order to do the git hook up this one time
        if (
            isset($this->config->publishing->git->email) &&
            isset($this->config->publishing->git->pass)
        ) {
            $email = $this->config->publishing->git->email;
            $pass = $this->config->publishing->git->pass;
            // ensure we never save the password, this is just a 1 time pass through
            unset($this->config->publishing->git->pass);
        }
        // save config to the file
        $this->saveConfigFile();
        // see if we need to set a github key for publishing
        // this is a one time thing that helps with the workflow
        if (
            $email &&
            $pass &&
            !isset($this->config->publishing->git->keySet) &&
            isset($this->config->publishing->git->vendor) &&
            $this->config->publishing->git->vendor == 'github'
        ) {
            $json = new stdClass();
            $json->title = 'HAXCMS Publishing key';
            $json->key = $this->getSSHKey();
            $client = new GuzzleHttp\Client();
            $body = json_encode($json);
            $response = $client->request(
                'POST',
                'https://api.github.com/user/keys',
                [
                    'auth' => [$email, $pass],
                    'body' => $body
                ]
            );
            // we did it, now store that it worked so we can skip all this setup in the future
            if ($response->getStatusCode() == 201) {
                $this->config->publishing->git->keySet = true;
                $this->saveConfigFile();
                // set global config for username / email if we can
                $gitRepo = new GitRepo();
                $gitRepo->run(
                    'config --global user.name "' .
                        $this->config->publishing->git->user .
                        '"'
                );
                $gitRepo->run(
                    'config --global user.email "' .
                        $this->config->publishing->git->email .
                        '"'
                );
            }

            return $response->getStatusCode();
        }
        return 'saved';
    }
    /**
     * Write configuration to the config file
     */
    private function saveConfigFile()
    {
        return @file_put_contents(
            $this->configDirectory . '/config.json',
            json_encode($this->config, JSON_PRETTY_PRINT)
        );
    }
    /**
     * get SSH Key that was created during install
     */
    private function getSSHKey()
    {
        if (file_exists($this->configDirectory . '/.ssh/haxyourweb.pub')) {
            return @file_get_contents(
                $this->configDirectory . '/.ssh/haxyourweb.pub'
            );
        } else {
            // try to build it dynamically
            shell_exec(
                'ssh-keygen -f ' .
                    $this->configDirectory .
                    '/.ssh/haxyourweb -t rsa -N "" -C "' .
                    $this->config->publishing->git->email .
                    '"'
            );
            // check if it exists now
            if (file_exists($this->configDirectory . '/.ssh/haxyourweb.pub')) {
                $git = new GitRepo();
                // establish this new key location as the one to use for all git calls
                $git->run(
                    "config core.sshCommand " .
                        $this->configDirectory .
                        "/.ssh/haxyourweb"
                );
                return @file_get_contents(
                    $this->configDirectory . '/.ssh/haxyourweb.pub'
                );
            }
        }
        return false;
    }
    /**
     * Generate a valid HAX App store specification schema for connecting to this site via JSON.
     */
    public function siteConnectionJSON()
    {
        return '{
      "details": {
        "title": "Local files",
        "icon": "perm-media",
        "color": "light-blue",
        "author": "HAXCMS",
        "description": "HAXCMS integration for HAX",
        "tags": ["media", "hax"]
      },
      "connection": {
        "protocol": "' .
            $this->protocol .
            '",
        "url": "' .
            $this->domain .
            $this->basePath .
            '",
        "operations": {
          "browse": {
            "method": "GET",
            "endPoint": "system/loadFiles.php",
            "pagination": {
              "style": "link",
              "props": {
                "first": "page.first",
                "next": "page.next",
                "previous": "page.previous",
                "last": "page.last"
              }
            },
            "search": {
            },
            "data": {
            },
            "resultMap": {
              "defaultGizmoType": "image",
              "items": "list",
              "preview": {
                "title": "name",
                "details": "mime",
                "image": "url",
                "id": "uuid"
              },
              "gizmo": {
                "source": "url",
                "id": "uuid",
                "title": "name",
                "type": "type"
              }
            }
          },
          "add": {
            "method": "POST",
            "endPoint": "system/saveFile.php",
            "acceptsGizmoTypes": [
              "image",
              "video",
              "audio",
              "pdf",
              "svg",
              "document",
              "csv"
            ],
            "resultMap": {
              "item": "data.file",
              "defaultGizmoType": "image",
              "gizmo": {
                "source": "url",
                "id": "uuid"
              }
            }
          }
        }
      }
    }';
    }
    /**
     * Generate appstore connection information. This has to happen at run time.
     * to get into account _config / environmental overrides
     */
    public function appStoreConnection()
    {
        $connection = new stdClass();
        $connection->url =
            $this->basePath .
            $this->appStoreFile .
            '?app-store-token=' .
            $this->getRequestToken('appstore');
        return $connection;
    }
    /**
     * Load a site off the file system with option to create
     */
    public function loadSite($name, $create = false, $domain = null)
    {
        $tmpname = urldecode($name);
        $tmpname = $this->cleanTitle($tmpname, false);
        // check if this exists, load but fallback for creating on the fly
        if (
            is_dir(
                HAXCMS_ROOT . '/' . $this->sitesDirectory . '/' . $tmpname
            ) &&
            !$create
        ) {
            $site = new HAXCMSSite();
            $site->load(
                HAXCMS_ROOT . '/' . $this->sitesDirectory,
                $this->basePath . $this->sitesDirectory . '/',
                $tmpname
            );
            return $site;
        } elseif ($create) {
            // attempt to create site
            return $this->createNewSite($name, $domain);
        }
        return false;
    }
    /**
     * Attempt to create a new site on the file system
     *
     * @var $name name of the new site to create
     * @var $domain optional domain name to utilize during setup
     * @var $git git object details
     *
     * @return boolean true for success, false for failed
     */
    private function createNewSite($name, $domain = null, $git = null)
    {
        // try and make the folder
        $site = new HAXCMSSite();
        // see if we can get a remote setup on the fly
        if (!isset($git->url) && isset($this->config->publishing->git)) {
            $git = $this->config->publishing->git;
            // getting really into fallback mode here
            if (isset($git->url)) {
                $git->url .= '/' . $name . '.git';
            }
        }

        if (
            $site->newSite(
                HAXCMS_ROOT . '/' . $this->sitesDirectory,
                $this->basePath . $this->sitesDirectory . '/',
                $name,
                $git,
                $domain
            )
        ) {
            return $site;
        }
        return false;
    }
    /**
     * Validate a security token
     */
    public function validateRequestToken($token = null, $value = '')
    {
        // default token is POST
        if ($token == null && isset($_POST['token'])) {
          $token = $_POST['token'];
        }
        if ($token != null) {
          if ($token == $this->getRequestToken($value)) {
            return true;
          }
        }
        return false;
    }
    /**
     * Clean up a title / sanitize the input string for file system usage
     */
    public function cleanTitle($value, $stripPage = true)
    {
        $cleanTitle = trim($value);
        // strips off the identifies for a page on the file system
        if ($stripPage) {
            $cleanTitle = str_replace(
                'pages/',
                '',
                str_replace('/index.html', '', $cleanTitle)
            );
        }
        $cleanTitle = strtolower(str_replace(' ', '-', $cleanTitle));
        $cleanTitle = preg_replace('/[^\w\-\/]+/u', '-', $cleanTitle);
        $cleanTitle = mb_strtolower(
            preg_replace('/--+/u', '-', $cleanTitle),
            'UTF-8'
        );
        // ensure we don't return an empty title or it could break downstream things
        if ($cleanTitle == '') {
            $cleanTitle = 'blank';
        }
        return $cleanTitle;
    }
    /**
     * test the active user login based on session.
     */
    public function testLogin($name, $pass, $adminFallback = false)
    {
        if (
            $this->user->name === $name &&
            $this->user->password === $pass
        ) {
            return true;
        }
        // if fallback is allowed, meaning the super admin then let them in
        // the default is to strictly test for the login in question
        // the fallback being allowable is useful for managed environments
        elseif (
            $adminFallback &&
            $this->superUser->name === $name &&
            $this->superUser->password === $pass
        ) {
            return true;
        }
        else {
            $usr = new stdClass();
            $usr->name = $name;
            $usr->password = $pass;
            $usr->adminFallback = $adminFallback;
            $usr->grantAccess = false;
            // fire custom event for things to respond to as needed
            $this->dispatchEvent('haxcms-login-test', $usr);
            return $usr->grantAccess;
        }
        return false;
    }
    /**
     * Validate that a user name that came across in a JWT decode is legit
     */
    private function validateUser($name)
    {
        if (
            $this->user->name === $name
        ) {
            return true;
        }
        elseif (
            $this->superUser->name === $name
        ) {
            return true;
        }
        else {
            $usr = new stdClass();
            $usr->name = $name;
            $usr->grantAccess = false;
            // fire custom event for things to respond to as needed
            $this->dispatchEvent('haxcms-validate-user', $usr);
            return $usr->grantAccess;
        }
        return false;
    }
    /**
     * Get a secure key based on session and two private values
     */
    public function getRequestToken($value = '')
    {
        return $this->hmacBase64($value, $this->privateKey . $this->salt);
    }
    /**
     * Get user's JWT
     */
    public function getJWT()
    {
        $token = array();
        $token['id'] = $this->getRequestToken('user');
        if (is_array($this->safePost) && isset($this->safePost['u'])) {
            $token['user'] = $this->safePost['u'];
        }
        $this->dispatchEvent('haxcms-jwt-get', $token);
        return JWT::encode($token, $this->privateKey . $this->salt);
    }
    /**
     * Decode the JWT to ensure accuracy, return false if an error happens
     */
    private function decodeJWT($key) {
      // if it can decode, it'll be an object, otherwise it's false
      try {
        return JWT::decode($key, $this->privateKey . $this->salt);
      }
      catch (Exception $e) {
        return FALSE;
      }
    }
    /**
     * Get Front end JWT based connection settings
     */
    public function appJWTConnectionSettings()
    {
        $settings = new stdClass();
        $settings->login = $this->basePath . 'system/login.php';
        $settings->logout = $this->basePath . 'system/logout.php';
        $settings->themes = $this->getThemes();
        $settings->saveNodePath = $this->basePath . 'system/saveNode.php';
        $settings->saveManifestPath =
            $this->basePath . 'system/saveManifest.php';
        $settings->saveOutlinePath = $this->basePath . 'system/saveOutline.php';
        $settings->publishSitePath = $this->basePath . 'system/publishSite.php';
        $settings->setConfigPath = $this->basePath . 'system/setConfig.php';
        $settings->getConfigPath = $this->basePath . 'system/getConfig.php';
        $settings->getNodeFieldsPath =
            $this->basePath . 'system/getNodeFields.php';
        $settings->getSiteFieldsPath =
            $this->basePath . 'system/getSiteFields.php';
            $settings->revertSitePath =
            $this->basePath . 'system/revertCommit.php';
        $settings->getFieldsToken = $this->getRequestToken('fields');
        $settings->createNodePath = $this->basePath . 'system/createNode.php';
        $settings->deleteNodePath = $this->basePath . 'system/deleteNode.php';
        $settings->createNewSitePath = $this->basePath . 'system/createNewSite.php';
        $settings->downloadSitePath = $this->basePath . 'system/downloadSite.php';
        $settings->archiveSitePath = $this->basePath . 'system/archiveSite.php';
        $settings->cloneSitePath = $this->basePath . 'system/cloneSite.php';
        $settings->deleteSitePath = $this->basePath . 'system/deleteSite.php';
        $settings->appStore = $this->appStoreConnection();
        // allow for overrides in config.php
        if (isset($this->config->appJWTConnectionSettings)) {
            foreach ($this->config->appJWTConnectionSettings as $key => $value) {
                if (isset($this->config->appJWTConnectionSettings->{$key})) {
                    // defer to the config.php setting
                    $settings->{$key} = $value;
                }
            }
        }
        $this->dispatchEvent('haxcms-connection-settings', $settings);
        return $settings;
    }
    /**
     * Test and ensure the name being returned is a location currently unused
     */
    public function getUniqueName($siteName)
    {
        $location = $siteName;
        $loop = 0;
        $original = $location;
        while (
            file_exists(HAXCMS_ROOT . '/' . $this->sitesDirectory . '/' . $location)
        ) {
            $loop++;
            $location = $original . '-' . $loop;
        }
        return $location;
    }
    /**
     * Validate a JTW during POST
     */
    public function validateJWT($endOnInvalid = TRUE)
    {
      $post = FALSE;
      if (isset($this->sessionJwt) && $this->sessionJwt != null && $post = $this->decodeJWT($this->sessionJwt)) {
      }
      else if (isset($_POST['jwt']) && $_POST['jwt'] != null && $post = $this->decodeJWT($_POST['jwt'])) {
      }
      else if (isset($_GET['jwt']) && $_GET['jwt'] != null && $post = $this->decodeJWT($_GET['jwt'])) {
      }
      // if we were able to find a valid JWT in that mess, try and validate it
      if (
          $post != FALSE &&
          isset($post->id) &&
          $post->id == $this->getRequestToken('user') &&
          $this->validateUser($post->user)) {
        return TRUE;
      }
      // kick back the end if its invalid
      if ($endOnInvalid) {
        header('Status: 403');
        print 'Invalid token';
        exit();
      }
      return FALSE;
    }

    /**
     * Generate a base 64 hash
     */
    private function hmacBase64($data, $key)
    {
        // generate the hash
        $hmac = base64_encode(
            hash_hmac('sha256', (string) $data, (string) $key, true)
        );
        // strip unsafe content post encoding
        return strtr($hmac, array(
            '+' => '-',
            '/' => '_',
            '=' => ''
        ));
    }
    /**
     * Add an event listener
     */
    public function addEventListener($event, $callback = NULL) {
        // Adding or removing a callback?
        if ($callback !== NULL) {
            if ($callback) {
                $this->events[$event][] = $callback;
            }
            else {
                unset($this->events[$event]);
            }
        }
    }
    /**
     * Tell an event to fire so that things can respond to it.
     * This will pass value around by reference and each event invoking
     * has a chance to modify the value in place
     */
    public function dispatchEvent($event, &$value = NULL) {
        if (isset($this->events[$event])) // Fire a callback
        {
            foreach($this->events[$event] as $function)
            {
                call_user_func_array($function, array(&$value));
            }
            return $value;
        }
    }
}
class DirFilter extends RecursiveFilterIterator
{
    protected $exclude;
    public function __construct($iterator, array $exclude)
    {
        parent::__construct($iterator);
        $this->exclude = $exclude;
    }
    public function accept()
    {
        return !($this->isDir() && in_array($this->getFilename(), $this->exclude));
    }
    public function getChildren()
    {
        return new DirFilter($this->getInnerIterator()->getChildren(), $this->exclude);
    }
}