<?php
/**
 * HAXCMS - The worlds smallest, most nothing yet most empowering CMS.
 * Simply a tremendous CMS. The greatest.
 */
// system constants
include_once 'Variables.php';
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
// basic request validation / handling
include_once 'Request.php';
// basic cache writing to file system
include_once 'Cache.php';
// composer...ugh
include_once dirname(__FILE__) . "/../vendor/autoload.php";
use Symfony\Component\Filesystem\Filesystem;
use Symfony\Component\Filesystem\Exception\IOExceptionInterface;
global $fileSystem;
$fileSystem = new Filesystem();

class HAXCMS
{
    private $validArgs;             // list of allowed CLI arguments
    private $events;                // array of events we are listening for globally in PHP
    private $cache;                 // Cache object
    public $cdn;                    // optional cdn for all paths even while developing sites
    public $appStoreFile;           // location of the HAX appstore API call which powers the editor
    public $salt;                   // salt to mix into all calls
    public $outlineSchema;          // JSONOutlineSchema object to make it easier to call helper functions
    public $privateKey;             // private key
    public $refreshPrivateKey;      // refresh token private key
    public $config;                 // system level configuration, API keys, etc
    public $userData;               // user data object like picture
    public $superUser;              // super user object
    public $user;                   // user object
    public $sitesDirectory;         // sites directory
    public $archivedDirectory;      // archived directory
    public $publishedDirectory;     // published directory
    public $developerMode;          // developer mode flag for deep interal validation bypasses
    public $developerModeAdminOnly; // if developer mode should only be on for the super user
    public $configDirectory;        // location of the _config directory
    public $sitesJSON;              // endpoint to obtain a listing of sites in json format
    public $domain;                 // domain to write urls off of
    public $protocol;               // http or https
    public $basePath;               // directory that haxcms is installed in on the server
    public $safePost;               // sanitized _POST data
    public $safeGet;                // sanitized _GET data
    public $safeCLI;                // sanitized data from CLI arguments
    public $safeInputStream;        // sanitized php input stream
    public $sessionJwt;             // session jwt; set via POST if it exists
    public $sessionToken;           // token for the request coming in; not a JWT but for form validation / XSS
    public $siteListingAttr;        // additional attributes allowed to be injected into the site-listing page
    public $systemRequestBase;      // base path to the API backend
    public $acceptedHAXFileTypes;   // array of accepted file types via HAX types
    public $coreConfigPath;         // coreConfig path
    /**
     * Establish defaults for HAXCMS
     */
    public function __construct()
    {
      $this->developerMode = FALSE;
      $this->developerModeAdminOnly = FALSE;
      $this->cdn = './';
      // critical for the CLI operations to validate
      $this->validArgs = array('op:', 'siteName::', 'iamUser::', 'theme:');
      // test for CLI and bring in arg data correctly
        if ($this->isCLI()) {
            // global but shift off the required pieces for usage
            array_shift($GLOBALS['argv']);
            array_shift($GLOBALS['argv']);
            array_shift($GLOBALS['argv']);
            $this->safeCLI = getopt('', $this->validArgs) + array('args' => $GLOBALS['argv']);
        }
        // stupid session less handling thing
        $_POST = (array) json_decode(file_get_contents('php://input'));
        // handle sanitization on request data, drop security things
        $this->safePost = $this->object_to_array($this->sanitizeArrayValues($_POST));
        if (isset($this->safePost['jwt'])) {
          $this->sessionJwt = $this->safePost['jwt'];
        }
        unset($this->safePost['jwt']);
        if (isset($this->safePost['token'])) {
          $this->sessionToken = $this->safePost['token'];
        }
        unset($this->safePost['token']);
        $this->safeGet = $this->object_to_array($this->sanitizeArrayValues($_GET));
        // Get HTTP/HTTPS (the possible values for this vary from server to server)
        $this->protocol =
            isset($_SERVER['HTTPS']) &&
            $_SERVER['HTTPS'] &&
            !in_array(strtolower($_SERVER['HTTPS']), array('off', 'no'))
                ? 'https'
                : 'http';
        // fallback test for https
        if ($this->protocol == 'http' && isset($_SERVER["HTTP_USESSL"]) && $_SERVER["HTTP_USESSL"]) {
          $this->protocol = 'https';
        }
        // CLIs dont have a domain argument
        if (isset($_SERVER['HTTP_HOST'])) {
          $this->domain = $_SERVER['HTTP_HOST'];
        }
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
        $this->systemRequestBase = 'system/api';
        $this->coreConfigPath = HAXCMS_ROOT . '/system/coreConfig/';
        $this->acceptedHAXFileTypes = array(
          "image",
          "video",
          "audio",
          "pdf",
          "svg",
          "document",
          "csv",
          "archive",
          "markdown",
          "html"
        );
        // end point to get the sites data
        $this->sitesJSON = $this->systemRequestBase . '/listSites';
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
            // setup cache bin
            try {
              $this->cache = new Cache(array(
                'name'      => 'haxcms',
                'path'      => $this->configDirectory . '/cache/',
                'extension' => '.cache'
              ));  
            }
            catch(Exception $e) {
              $this->cache = null;
            }
            // add in the auto-generated app store file
            $this->appStoreFile = $this->systemRequestBase . '/generateAppStore';
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
                        $this->coreConfigPath . 'themes.json'
                    )
                );
                foreach ($themeData as $name => $data) {
                    $this->config->themes->{$name} = $data;
                }
                // dynamicImporter
                if (!isset($this->config->node)) {
                    $this->config->node = new stdClass();
                    $this->config->node->dynamicElementLoader = new stdClass();
                    $this->config->node->fields = new stdClass();
                }
                // load in core dynamicElementLoader data
                $dynamicElementLoader = json_decode(
                    file_get_contents(
                      $this->coreConfigPath . 'dynamicElementLoader.json'
                    )
                );
                foreach ($dynamicElementLoader as $name => $data) {
                    $this->config->node->dynamicElementLoader->{$name} = $data;
                }
                // publishing endpoints
                if (!isset($this->config->site)) {
                    $this->config->site = new stdClass();
                    $this->config->site->settings = new stdClass();
                    $this->config->site->git = new stdClass();
                    $this->config->site->static = new stdClass();
                }
                if (!isset($this->config->site->publishers)) {
                  $this->config->site->publishers = new stdClass();
                }
                // load in core publishing data
                $publishingData = json_decode(
                    file_get_contents(
                      $this->coreConfigPath . 'publishers.json'
                    )
                );
                foreach ($publishingData as $name => $data) {
                    $this->config->site->publishers->{$name} = $data;
                }
                // importer formats to ingest
                if (!isset($this->config->site->importers)) {
                    $this->config->site->importers = new stdClass();
                }
                // load in core importers data
                $importersData = json_decode(
                    file_get_contents(
                      $this->coreConfigPath . 'importers.json'
                    )
                );
                foreach ($importersData as $name => $data) {
                    $this->config->site->importers->{$name} = $data;
                }
                // site fields in HAXschema format
                if (!isset($this->config->site->fields)) {
                    $this->config->site->fields = array(new stdClass());
                }
                // load in core importers data
                $fieldsData = json_decode(
                    file_get_contents(
                      $this->coreConfigPath . 'siteFields.json'
                    )
                );
                foreach ($fieldsData as $name => $data) {
                    $this->config->site->fields[0]->{$name} = $data;
                }
                $themeSelect = array();
                // ensure field schema has correct theme options
                foreach ($this->config->themes as $name => $data) {
                  $themeSelect[$name] = $data->name;
                }
                // @todo this is VERY hacky specific placement of the theme options
                $this->config->site->fields[0]->properties[1]->properties[0]->options = $themeSelect;
                // userData object
                // load in core dynamicElementLoader data
                if (
                !($this->userData = json_decode(
                    file_get_contents($this->configDirectory . '/userData.json')
                ))) {
                  $this->userData = new stdClass();
                }
            }
            $this->dispatchEvent('haxcms-init', $this);
        }
    }
    /**
     * recursively convert an object to an array, deeply
     */
    private function object_to_array($obj) {
        //only process if it's an object or array being passed to the function
        if(is_object($obj) || is_array($obj)) {
            $ret = (array) $obj;
            foreach($ret as &$item) {
                //recursively process EACH element regardless of type
                $item = $this->object_to_array($item);
            }
            return $ret;
        }
        //otherwise (i.e. for scalar values) return without modification
        else {
            return $obj;
        }
    }
    /**
     * Deep sanitize array values
     */
    public function sanitizeArrayValues($values) {
        foreach ($values as $key => $value) {
            if (is_array($value)) {
                if (is_array($values)) {
                    $values[$key] = $this->sanitizeArrayValues($value);
                }
                else if (is_object($values)) {
                    $values->{$key} = $this->sanitizeArrayValues($value);
                }
            }
            else if (is_object($value)) {
                if (is_array($values)) {
                    $values[$key] = $this->sanitizeArrayValues($value);
                }
                else if (is_object($values)) {
                    $values->{$key} = $this->sanitizeArrayValues($value);
                }
            }
            else {
                if (is_array($values)) {
                    $values[$key] = filter_var($value);
                }
                else if (is_object($values)) {
                    $values->{$key} = filter_var($value);
                }
            }
        }
        return $values;
    }
    /**
     * If we are a cli
     */
    private function isCLI() {
        return !isset($_SERVER['SERVER_SOFTWARE']) && (php_sapi_name() == 'cli' || is_numeric($_SERVER['argc']) && $_SERVER['argc'] > 0);
    }
    public function executeRequest($op = null) {
      $usedGet = FALSE;
      // calculate the correct params to use
      if ($this->isCLI()) {
        $params = $this->safeCLI;
      }
      else if (is_array($this->safePost) && count($this->safePost)) {
        $params = $this->safePost;
      }
      else if (is_array($this->safeGet) && count($this->safeGet)) {
        $usedGet = TRUE;
        $params = $this->safeGet;
      }
      else {
        $params = array();
      }
      // raw params too incase the request needs them
      if ($this->isCLI()) {
        $rawParams = $this->safeCLI;
      }
      else if (is_array($_POST) && count($_POST)) {
        $rawParams = $_POST;
      }
      else if (is_array($_GET) && count($_GET)) {
        $rawParams = $_GET;
      }
      else {
        $rawParams = array();
      }
      // support parameters setting the operation
      if ($op == null) {
        if (isset($params['op'])) {
          $op = $params['op'];
        }
        else if (isset($_GET['op'])) {
          $op = $this->safeGet['op'];
        }
      }
      // remove api/ from the op
      if (strpos($op, 'api/') === 0) {
        $op = substr($op, 4);
      }
      if ($op == '') {
        $op = 'api';
      }
      // look for any paths and only return 1st
      if (strpos($op, '/')) {
        $tmp = explode('/', $op);
        $op = $tmp[0];
        // store as args bc this will be common to want access to
        $params['args'] = $tmp;
      }
      // loop through other potential GET based args so long as they aren't set yet
      // this ensures that post has priority for security but allowing us to develop
      // faster when it comes to pulling across other arguments like form_id
      if (!$usedGet) {
        foreach ($this->safeGet as $key => $arg) {
          if (!isset($params[$key])) {
            $params[$key] = $arg;
          }
        }
      }
      // execute the request with contextual params mixed in
      // based on how the request was formulated
      $request = new Request();
      // this will output the response headers and everything
      $request->execute($op, $params, $rawParams);
    }
    /**
     * load form and spitting out HAXschema + values in our standard transmission method
     */
    public function loadForm($form_id, $context = array()) {
      $fields = array();
      $value = new stdClass();
      // @todo add future support for dependency injection as far as allowed forms
      if (method_exists($this, $form_id . "Form")) {
        $fields = $this->{$form_id . "Form"}($context);
        // reserved so we know what form is being submitted
        $fields['haxcms_form_id'] = json_decode(
          '{
            "property": "haxcms_form_id",
            "title": "haxcms_form_id",
            "description": "",
            "inputMethod": "textfield",
            "hidden": true
          }'
        );
        // reserved so we know what form is being submitted
        $fields['haxcms_form_token'] = json_decode(
          '{
            "property": "haxcms_form_token",
            "title": "haxcms_form_token",
            "description": "",
            "inputMethod": "textfield",
            "hidden": true
          }'
        );
      }
      else {
        $fields = array(
          '__failed' => array(
            'status' => 500,
            'message' => $form_id . ' does not exist',
          )
        );
      }
      if (method_exists($this, $form_id . "Value")) {
        $value = $this->{$form_id . "Value"}($context);
      }
      // ensure values are set for the hidden internal fields
      $value->haxcms_form_id = $form_id;
      $value->haxcms_form_token = $this->getRequestToken($form_id);
      return array(
        'fields' => $fields,
        'value' => $value,
      );
    }
    /**
     * Process the form submission data
     */
    public function processForm($form_id, $params, $context = array()) {
      // make sure we have the original value / key pairs for the form
      if (method_exists($this, $form_id . "Value")) {
        $value = $this->{$form_id . "Value"}($context);

      }
      else {
        $fields = array(
          '__failed' => array(
            'status' => 500,
            'message' => $form_id . ' does not exist',
          )
        );
      }
    }
    /**
     * Magic function that will convert foo.bar.zzz into $obj->foo->bar->zzz with look up.
     */
    private function deepObjectLookUp($obj, $path) {
      return array_reduce(explode('-', $path), function ($o, $p) { return is_numeric($p) ? ($o[$p] ?? null) : ($o->$p ?? null); }, $obj);
    }

    /**
     * Return the form for the siteSettings
     */
    private function siteSettingsForm($context) {
      return $this->config->site->fields;
    }
    /**
     * Return the form for the siteSettings
     */
    private function siteSettingsValue($context) {
      $site = $this->loadSite($context['site']['name']);
      // passing in as JSON for sanity
      $jsonResponse = json_decode('{
        "manifest": {
          "site": {
            "manifest-title": null,
            "manifest-description": null,
            "manifest-metadata-site-domain": null,
            "manifest-metadata-site-logo": null
          },
          "author": {
            "manifest-license": null,
            "manifest-metadata-author-image": null,
            "manifest-metadata-author-name": null,
            "manifest-metadata-author-email": null,
            "manifest-metadata-author-socialLink": null
          },
          "theme": {
            "manifest-metadata-theme-element": null,
            "manifest-metadata-theme-variables-image": null,
            "manifest-metadata-theme-variables-hexCode": null,
            "manifest-metadata-theme-variables-cssVariable": null,
            "manifest-metadata-theme-variables-icon": null
          },
         "fields": {
            "manifest-metadata-node-fields": []
          },
          "seo": {
            "manifest-metadata-site-settings-pathauto": null,
            "manifest-metadata-site-settings-publishPagesOn": null,
            "manifest-metadata-site-settings-sw": null,
            "manifest-metadata-site-settings-forceUpgrade": null
          },
          "static": {
            "manifest-metadata-site-static-cdn": null,
            "manifest-metadata-site-static-offline": null,
            "publishacopy": "<h2>Publish a copy</h2><div style=\"border: solid 1px #cb2431; padding:16px;\"><p>This will publish your site, overwriting the previous copy living in your \"published\" storage location.</p><user-action track=\"click\" every eventname=\"haxcms-publish-site\"><paper-button style=\"color:#cb2431;\" class=\"full warning\" raised role=\"button\" tabindex=\"0\" animated elevation=\"1\" aria-disabled=\"false\"><iron-icon icon=\"icons:cloud-upload\"></iron-icon> Publish</paper-button></user-action></div>"
          },
          "git": {
            "manifest-metadata-site-git-vendor": null,
            "manifest-metadata-site-git-branch": null,
            "manifest-metadata-site-git-staticBranch": null,
            "manifest-metadata-site-git-autoPush": null,
            "manifest-metadata-site-git-url": null,
            "manifest-metadata-site-git-publicRepoUrl": null,
            "dangerzone": "<h2>Danger zone</h2><div style=\"border: solid 1px #cb2431; padding:16px;\"><p>This will sync the local copy of the site with the git repository is backing it</p><user-action track=\"click\" every eventname=\"haxcms-sync-site\"><paper-button style=\"color:#cb2431;\" class=\"full warning\" raised role=\"button\" tabindex=\"0\" animated elevation=\"1\" aria-disabled=\"false\"><iron-icon icon=\"notification:sync\"></iron-icon> Sync git origin</paper-button></user-action><p>This wil revert the git history powering the site by 1 commit. This is a destructive command, only use this if you just saved something you didn\'t mean to.</p><user-action track=\"click\" every eventname=\"haxcms-git-revert-last-commit\"><paper-button style=\"color:#cb2431;\" class=\"full warning\" raised role=\"button\" tabindex=\"0\" animated elevation=\"1\" aria-disabled=\"false\"><iron-icon icon=\"icons:cloud-upload\"></iron-icon> Revert last commit</paper-button></user-action></div>"
          }
        }
      }');
      // this will process the form values and engineer them out of
      // the manifest based on key location to value found there (if any)
      return $this->populateManifestValues($site, $jsonResponse);
    }
    /**
     * Populate values based on the structure of the form schema values
     * established previously. This REQUIRES that the key in the end
     * is a string in the form of "manifest-what-ever-value-this-needs"
     * which it then takes ANY structure and recursively populates it
     * with the appropriate values to match
     */
    private function populateManifestValues($site, $manifestKeys) {
      foreach ($manifestKeys as $key => $value) {
        // cascade of our methodology for building out forms
        // which peg to the internal workings of JSON outline schema
        // while still being presented in a visually agnostic manner
        // this is some crazy S..
        // test if we have deeper items to traverse at this level
        if (!is_string($value) && count((array)$value) > 0) {
          $manifestKeys->{$key} = $this->populateManifestValues($site, $value);
        }
        else if (is_string($key) && $lookup = $this->deepObjectLookUp($site, $key)) {
          $manifestKeys->{$key} = $lookup;
        }
      }
      // @todo needs to not be a hack :p
      if (isset($manifestKeys->{"manifest-metadata-theme-variables-cssVariable"})) {
        $manifestKeys->{"manifest-metadata-theme-variables-cssVariable"} = str_replace("-7", "", str_replace("--simple-colors-default-theme-", "", $manifestKeys->{"manifest-metadata-theme-variables-cssVariable"}));
      }
      return $manifestKeys;
    }
    /**
     * Get input method for HAXSchema based on a data type
     * @var $type [string]
     */
    public function getInputMethod($type = null) {
      switch ($type) {
        case 'string':
          return 'textfield';
        break;
        case 'number':
          return 'number';
        break;
        case 'date':
          return 'datepicker';
        break;
        case 'boolean':
          return 'boolean';
        break;
        default:
          return 'textfield';
        break;
      }
    }
    /**
     * Get the current version number
     */
    public function getHAXCMSVersion()
    {
      $version = &$this->staticCache(__FUNCTION__);
      if (!isset($version)) {
        // sanity
        $vFile = HAXCMS_ROOT . '/VERSION.txt';
        if (file_exists($vFile)) {
          $version = filter_var(file_get_contents($vFile));
        }
      }
      return $version;
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
            if (isset($this->config->site->git->{$key})) {
                $props->value = $this->config->site->git->{$key};
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
            if ($key == 'pass' && isset($this->config->site->git->user)) {
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
    public function setUserData($values)
    {
      // only support user picture for the moment
      if (isset($values->userPicture)) {
        $this->userData->userPicture = $values->userPicture;
      }
      $this->saveUserDataFile();
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
        if (!isset($this->config->site)) {
          $this->config->site = new stdClass();
        }
        if (!isset($this->config->site->git)) {
          $this->config->site->git = new stdClass();
        }
        if ($values->publishing) {
          foreach ($values->publishing as $key => $val) {
            $this->config->site->git->{$key} = $val;
          }
        }
        // test for a password in order to do the git hook up this one time
        if (
          isset($this->config->site->git->email) &&
          isset($this->config->site->git->pass)
        ) {
          $email = $this->config->site->git->email;
          $pass = $this->config->site->git->pass;
          // ensure we never save the password, this is just a 1 time pass through
          unset($this->config->site->git->pass);
        }
        // save config to the file
        $this->saveConfigFile();
        // see if we need to set a github key for publishing
        // this is a one time thing that helps with the workflow
        if (
          isset($email) &&
          isset($pass) &&
          !isset($this->config->site->git->keySet) &&
          isset($this->config->site->git->vendor) &&
          $this->config->site->git->vendor == 'github'
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
                $this->config->site->git->keySet = true;
                $this->saveConfigFile();
                // set global config for username / email if we can
                $gitRepo = new GitRepo();
                $gitRepo->run(
                    'config --global user.name "' .
                        $this->config->site->git->user .
                        '"'
                );
                $gitRepo->run(
                    'config --global user.email "' .
                        $this->config->site->git->email .
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
    private function saveUserDataFile()
    {
        return @file_put_contents(
            $this->configDirectory . '/userData.json',
            json_encode($this->userData, JSON_PRETTY_PRINT)
        );
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
                    $this->config->site->git->email .
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
        "tags": ["media"]
      },
      "connection": {
        "protocol": "' . $this->protocol . '",
        "url": "' . $this->domain . $this->basePath . '",
        "operations": {
          "browse": {
            "method": "GET",
            "endPoint": "system/api/loadFiles",
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
            "endPoint": "system/api/saveFile",
            "acceptsGizmoTypes": ' . json_encode($this->acceptedHAXFileTypes) . ',
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
    public function appStoreConnection() {
        $connection = new stdClass();
        // support for remote appstores if a developer overrides the location
        // of the appstore then we can't assum eit exists on this server
        if ($this->appStoreFile == $this->systemRequestBase . '/generateAppStore') {
          $connection->url = $this->basePath . $this->appStoreFile . '?app-store-token=' . $this->getRequestToken('appstore');
        }
        else {
          $connection->url = $this->appStoreFile;
        }
        return $connection;
    }
    /**
     * Return the active URI if it exists
     */
    public function getURI() {
      if (isset($_SERVER['SCRIPT_URI'])) {
        return $_SERVER['SCRIPT_URI'];
      }
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
            $site->load(HAXCMS_ROOT . '/' . $this->sitesDirectory,
                $this->basePath . $this->sitesDirectory . '/',
                $tmpname);
            $siteDirectoryPath = $site->directory . '/' . $site->manifest->metadata->site->name;
            // sanity checks to ensure we'll actually deliver a site
            if (!is_link($siteDirectoryPath . '/build')) {
              if (is_dir($siteDirectoryPath . '/build')) {
                $GLOBALS['fileSystem']->remove([$siteDirectoryPath . '/build']);
              }
              @symlink('../../build', $siteDirectoryPath . '/build');
              if (!is_link($siteDirectoryPath . '/dist')) {
                  @symlink('../../dist', $siteDirectoryPath . '/dist');
              }
              if (!is_link($siteDirectoryPath . '/node_modules')) {
                @symlink(
                    '../../node_modules',
                    $siteDirectoryPath . '/node_modules'
                );
              }
              if (!is_link($siteDirectoryPath . '/assets/babel-top.js')) {
                @unlink($siteDirectoryPath . '/assets/babel-top.js');
                @symlink(
                  '../../../babel/babel-top.js',
                    $siteDirectoryPath . '/assets/babel-top.js'
                );
              }
              if (!is_link($siteDirectoryPath . '/assets/babel-bottom.js')) {
                @unlink($siteDirectoryPath . '/assets/babel-bottom.js');
                @symlink(
                    '../../../babel/babel-bottom.js',
                    $siteDirectoryPath . '/assets/babel-bottom.js'
                );
              }
            }
            return $site;
        } elseif ($create) {
            // attempt to create site
            return $this->createSite($name, $domain);
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
    private function createSite($name, $domain = null, $git = null)
    {
        // try and make the folder
        $site = new HAXCMSSite();
        // see if we can get a remote setup on the fly
        if (!isset($git->url) && isset($this->config->site->git)) {
            $git = $this->config->site->git;
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
        if ($this->isCLI()) {
            return TRUE;
        }
        // default token is POST
        if ($token == null && isset($_POST['token'])) {
          $token = $_POST['token'];
        }
        if ($token != null) {
          if ($token == $this->getRequestToken($value)) {
            return TRUE;
          }
        }
        return TRUE;
    }
    /**
     * Generate machine name
     */
    public function generateMachineName($name) {
        return strtolower(preg_replace(array(
        '/[^a-zA-Z0-9]+/',
        '/-+/',
        '/^-+/',
        '/-+$/',
        ), array('-', '-', '', ''), $name));
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
            // this is for SaaS providers to provide global validation
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
    public function getJWT($name = null)
    {
        $token = array();
        $token['id'] = $this->getRequestToken('user');
        // used at time
        $token['iat'] = time();
        // expiration time, 15 minutes
        $token['exp'] = time() + (15 * 60);
        // if the user was supplied then add to token, if not it's relatively worthless but oh well :)
        if (!is_null($name)) {
            $token['user'] = $name;
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
     * Get user's Refresh Token
     */
    public function getRefreshToken($name = null) {
      $token = array();
      $token['user'] = $name;
      $token['iat'] = time();
      $token['exp'] = time() + (7 * 24 * 60 * 60);
      $this->dispatchEvent('haxcms-refresh-token-get', $token);
      return JWT::encode($token, $this->refreshPrivateKey . $this->salt);
    }
    /**
     * Decode the JWT to ensure accuracy, return false if an error happens
     */
    private function decodeRefreshToken($key) {
      // if it can decode, it'll be an object, otherwise it's false
      try {
        return JWT::decode($key, $this->refreshPrivateKey . $this->salt);
      }
      catch (Exception $e) {
        return FALSE;
      }
    }
    /**
     * Validate a JTW during POST
     */
    public function validateRefreshToken($endOnInvalid = TRUE) {
      if ($this->isCLI()) {
        return TRUE;
      }
      // get the refresh token from cookie
      $refreshToken = $_COOKIE['haxcms_refresh_token'];
      // if there isn't one then we have to bail hard
      if (!$refreshToken) {
        header('Status: 401');
        print 'haxcms_refresh_token:not_found';
        exit();
      }
      // if there is a refresh token then decode it
      $refreshTokenDecoded = $this->decodeRefreshToken($refreshToken);
      // validate the token
      // make sure token has issued and expiration dates
      if (isset($refreshTokenDecoded->iat) && isset($refreshTokenDecoded->exp)) {
        // issued at date is less than or equal to now
        if ($refreshTokenDecoded->iat <= time()) {
          // expiration date is greater than now
          if (time() < $refreshTokenDecoded->exp) {
            // it's valid
            return $refreshTokenDecoded;
          }
        }
      }
      // kick back the end if its invalid
      if ($endOnInvalid) {
        setcookie('haxcms_refresh_token', '', 1);
        header('Status: 401');
        print 'haxcms_refresh_token:invalid:end_on_invalid_flag';
        exit();
      }
      return FALSE;
    }
    /**
     * Get Front end JWT based connection settings
     */
    public function appJWTConnectionSettings()
    {
        $path = $this->basePath . $this->systemRequestBase . '/';
        $settings = new stdClass();
        $settings->login = $path . 'login';
        $settings->refreshUrl = $path . 'refreshAccessToken';
        $settings->logout = $path . 'logout';
        $settings->redirectUrl = $this->basePath; // enables redirecting back to site root if JWT really is dead
        $settings->themes = $this->getThemes();
        $settings->saveNodePath = $path . 'saveNode';
        $settings->saveManifestPath = $path . 'saveManifest';
        $settings->saveOutlinePath = $path . 'saveOutline';
        $settings->publishSitePath = $path . 'publishSite';
        $settings->syncSitePath = $path . 'syncSite';
        $settings->setConfigPath = $path . 'setConfig';
        $settings->getConfigPath = $path . 'getConfig';
        $settings->getNodeFieldsPath = $path . 'getNodeFields';
        $settings->getSiteFieldsPath = $path . 'formLoad?haxcms_form_id=siteSettings';
        $settings->revertSitePath = $path . 'revertCommit';
        // form token to validate form submissions as unique to the session
        $settings->getFormToken = $this->getRequestToken('form');
        $settings->createNodePath = $path . 'createNode';
        $settings->getUserDataPath = $path . 'getUserData';
        $settings->setUserPhotoPath = $path . 'setUserPhoto';
        $settings->deleteNodePath = $path . 'deleteNode';
        $settings->createNewSitePath = $path . 'createSite';
        $settings->gitImportSitePath = $path . 'gitImportSite';
        $settings->downloadSitePath = $path . 'downloadSite';
        $settings->archiveSitePath = $path . 'archiveSite';
        $settings->cloneSitePath = $path . 'cloneSite';
        $settings->deleteSitePath = $path . 'deleteSite';
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
     * Get cache data from file system
     */
    public function getCache($key) {
      // sanity check that we can cache data locally
      if (is_null($this->cache)) {
        return null;
      }
      return $this->cache->retrieve($key);
    }
    /**
     * Set cache data on file system
     */
    public function setCache($key, $data, $expiration = 86400) {
      // sanity check that we can cache data locally
      if (is_null($this->cache)) {
        return null;
      }
      return $this->cache->store($key, $data, $expiration);
    }
    /**
     * Static cache a variable that may be called multiple times
     * in one transaction yet has same result
     */
    public function &staticCache($name, $default_value = NULL, $reset = FALSE) {
      static $data = array(), $default = array();
      if (isset($data[$name]) || array_key_exists($name, $data)) {
        if ($reset) {
          $data[$name] = $default[$name];
        }
        return $data[$name];
      }
      if (isset($name)) {
        if ($reset) {
          return $data;
        }
        $default[$name] = $data[$name] = $default_value;
        return $data[$name];
      }
      foreach ($default as $name => $value) {
        $data[$name] = $value;
      }
      return $data;
    }
    /**
     * Return the link to the cdn to use for serving dynamic pages
     */
    public function getCDNForDynamic() {
      return $this->cdn;
    }
    /**
     * generate a hash based on the SHA of the git commit
     */
    public function cacheBusterHash($prepend = '?') {
      $buster = &$this->staticCache(__FUNCTION__);
      if (!isset($buster)) {
        $buster = $this->getCache('git-sha');
        if (is_null($buster)) {
          $buster = $prepend;
          // open the system itself
          $git = new Git();
          $repo = $git->open(HAXCMS_ROOT, false);
          $buster .= $this->getRequestToken($repo->currentSHA());
          $this->setCache('git-sha', $buster);
        }
      }
      return $buster;
    }
    /**
     * Test and ensure the name being returned is a location currently unused
     */
    public function getUniqueName($name)
    {
        $location = $name;
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
      if ($this->isCLI()) {
        return TRUE;
      }
      $request = FALSE;
      if (isset($this->sessionJwt) && $this->sessionJwt != null && $request = $this->decodeJWT($this->sessionJwt)) {
      }
      else if (isset($_POST['jwt']) && $_POST['jwt'] != null && $request = $this->decodeJWT($_POST['jwt'])) {
      }
      else if (isset($_GET['jwt']) && $_GET['jwt'] != null && $request = $this->decodeJWT($_GET['jwt'])) {
      }
      // if we were able to find a valid JWT in that mess, try and validate it
      if (  
          $request != FALSE &&
          isset($request->id) &&
          $request->id == $this->getRequestToken('user') &&
          isset($request->user) &&
          $this->validateUser($request->user)) {
        return TRUE;
      }
      $code = 403;
      // allow for rewriting this
      if ($code == 403 && $endOnInvalid) {
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
        // Adding or removing a callback
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