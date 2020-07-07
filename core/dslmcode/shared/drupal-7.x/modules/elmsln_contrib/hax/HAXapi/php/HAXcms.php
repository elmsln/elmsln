<?php
/**
 * HAXcms
 */
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
        $this->basePath = base_path();
        $this->systemRequestBase = 'haxapi';
        $this->config = new stdClass();
        $this->config->themes = array(
            'clean-one' => t('Course theme'),
            'clean-two' => t('Course theme two'),
            'learn-two-theme' => t('Course theme three'),
            'outline-player' => t('Documentation theme'),
            'haxor-slevin' => t('Developer Blog theme'),
        );
    }
    /**
     * Load theme location data as mix of config and system
     */
    public function getThemes()
    {
        return $this->config->themes;
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
        $settings->connectionSettings = $path . 'connectionSettings';
        $settings->redirectUrl = $this->basePath; // enables redirecting back to site root if JWT really is dead
        $settings->themes = $this->getThemes();
        $settings->saveNodePath = $path . 'saveNode/' . drupal_get_token('hax');
        $settings->saveManifestPath = $path . 'saveManifest';
        $settings->saveOutlinePath = $path . 'saveOutline';
        $settings->setConfigPath = $path . 'setConfig';
        $settings->getConfigPath = $path . 'getConfig';
        $settings->getNodeFieldsPath = $path . 'getNodeFields';
        $settings->getSiteFieldsPath = $path . 'formLoad?haxcms_form_id=siteSettings';
        // form token to validate form submissions as unique to the session
        $settings->getFormToken = drupal_get_token('hax');
        $settings->createNodePath = $path . 'createNode/' . drupal_get_token('hax');
        $settings->deleteNodePath = $path . 'deleteNode/' . drupal_get_token('hax');
        $settings->getUserDataPath = $path . 'getUserData/' . drupal_get_token('hax');
        // not an actual jwt but fakes it correctly for session based Drupal to function
        $settings->jwt = drupal_get_token('hax');
        //$settings->syncSitePath = $path . 'syncSite';
        //$settings->publishSitePath = $path . 'publishSite';
        //$settings->revertSitePath = $path . 'revertCommit';
        //$settings->setUserPhotoPath = $path . 'setUserPhoto';
        //$settings->createNewSitePath = $path . 'createSite';
        //$settings->gitImportSitePath = $path . 'gitImportSite';
        //$settings->downloadSitePath = $path . 'downloadSite';
        //$settings->archiveSitePath = $path . 'archiveSite';
        //$settings->cloneSitePath = $path . 'cloneSite';
        //$settings->deleteSitePath = $path . 'deleteSite';
        $settings->appStore = array(
          'url' => base_path() . 'haxapi/generateAppStore/' . drupal_get_token('hax'),
        );
        return $settings;
    }
}