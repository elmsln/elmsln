<?php
namespace Grav\Plugin;

use \Grav\Common\Plugin;
use \Grav\Common\Grav;
use \Grav\Common\Utils;
use \Grav\Common\Page\Page;

define('WEBCOMPONENTS_CLASS_IDENTIFIER', 'webcomponent-plugin-selector');
define('WEBCOMPONENTS_APP_PATH', 'apps');

class WebcomponentsPlugin extends Plugin
{
  public $activeApp;
  /**
   * @return array
   */
  public static function getSubscribedEvents()
  {
    return [
      'onThemeInitialized' => ['onThemeInitialized', 0],
      'onTwigTemplatePaths' => ['onTwigTemplatePaths', 100],
      'onPluginsInitialized' => ['onPluginsInitialized', 100000]
    ];
  }

  /**
   * Initialize the plugin
   */
  public function onPluginsInitialized()
  {
    // Don't proceed if we are in the admin plugin
    if ($this->isAdmin()) {
      return;
    }

    $uri = $this->grav['uri'];
    // load autoloaded paths from manifest files in our apps
    $routes = $this->loadWebcomponentApps();
    foreach ($routes as $machine_name => $app) {
      // if our route matches one we have, load up
      if ("/apps/$machine_name" == $uri->path()) {
        $this->activeApp = (array)$app;
        $this->enable([
            'onPageInitialized' => ['onPageInitialized', 0]
        ]);
      }
      // check for data endpoints if they exist
      if (isset($app['endpoints'])) {
        foreach ($app['endpoints'] as $path => $endpoint) {
          if ("/apps/$machine_name/$path" == $uri->path()) {
            $this->activeApp = (array)$app;
            $this->enable([
                'onPageInitialized' => ['onPageInitializedData', 0]
            ]);
          }
        }
      }
    }
  }
  /**
   * Add current directory to twig lookup paths.
   */
  public function onTwigTemplatePaths()
  {
      $this->grav['twig']->twig_paths[] = __DIR__ . '/templates';
  }


  /**
   * Autoload a webcomponent app.
   */
  public function onPageInitialized()
  {
    // set a dummy page
    $page = new Page;
    $page->init(new \SplFileInfo(__DIR__ . '/pages/webcomponents-app.md'));
    unset($this->grav['page']);
    $this->grav['page'] = $page;
  }

  /**
   * Autoload a webcomponent app data path.
   */
  public function onPageInitializedData()
  {
    // return data
    $return = array();
    // validate CSRF token and ensure we have something
    if (is_array($this->activeApp) || Utils::getNonce('webcomponentapp') == $_GET['token']) {
      $app = $this->activeApp;
      $machine_name = $app['machine_name'];
      $args = explode('?', str_replace($this->grav['base_url'], '', $_SERVER['REQUEST_URI']));
      $args = explode('/', $args[0]);
      // this ensures that apps/machine-name get shifted off
      array_shift($args);
      array_shift($args);
      array_shift($args);
      // match the route that was specified in $app['endpoints']
      $endpointpath = NULL;
      if (isset($app['endpoints'])) {
        foreach ($app['endpoints'] as $path => $endpoint) {
          // we're going to compare the args array and the endpoint.
          // to do this we are going to convert the path to an array.
          $path_ary = explode('/', $path);
          // see if args and path are the same length
          if (count($path_ary) == count($args)) {
            // see if there are any differences between the two
            $ary_diff = array_diff($path_ary, $args);
            // if no differences then we found the path and we should exit
            // immediately
            if (empty($ary_diff)) {
              $endpointpath = $path;
              break;
            }
            // if there is a difference in the path but the only differences
            // are wildcards then it's a match
            else {
              $mismatch = false;
              foreach ($ary_diff as $diff) {
                if ($diff != '%') {
                  $mismatch = true;
                }
              }
              // if we went through the diffs and there were no
              // matches other than % then it's a match
              if (!$mismatch) {
                $endpointpath = $path;
              }
            }
          }
        }
      }
      // attempt autoload here in the event this was invoked via a load all
      if (isset($app['autoload']) && $app['autoload'] === TRUE) {
        include_once $app['filepath'] . $machine_name . '.php';
      }
      // make sure the machine name and the data callback both exist
      if (!empty($machine_name) && !empty($app) && isset($app['endpoints']) && function_exists($app['endpoints'][$endpointpath]->callback)) {
        $params = filter_var_array($_GET, FILTER_SANITIZE_STRING);
        // include additional url arguments to downstream
        // check for extended args on this call
        $return = call_user_func($app['endpoints'][$endpointpath]->callback, $machine_name, WEBCOMPONENTS_APP_PATH . '/' . $machine_name, $params, $args);
      }
      else {
        $return = array(
          'status' => '404',
          'detail' => 'Not a valid callback',
        );
      }
    }
    else {
      $return = array(
        'status' => '403',
        'detail' => 'Invalid CSRF token',
      );
    }
    // nothing set so make it 200 even though it already is
    if (empty($return['status'])) {
      $return['status'] = '200';
    }
    // ensure there's some form of detail even if empty
    if (empty($return['detail'])) {
      $return['detail'] = '';
    }
    // ensure there's some form of detail even if empty
    if (empty($return['environment'])) {
      $return['environment'] = array();
    }
    // set output headers as JSON
    header('Content-Type: application/json');
    header('Status: ' . $return['status']);
    // return JSON!
    echo json_encode($return);
    exit();
  }

  /**
   * Initialize configuration
   */
  public function onThemeInitialized()
  {
    if ($this->isAdmin()) {
      return;
    }

    $load_events = false;

    // if not always_load see if the theme expects to load the webcomponents plugin
    if (!$this->config->get('plugins.webcomponents.always_load')) {
      $theme = $this->grav['theme'];
      if (isset($theme->load_webcomponents_plugin) && $theme->load_webcomponents_plugin) {
        $load_events = true;
      }
    }
    else {
      $load_events = true;
    }

    if ($load_events) {
      $this->enable([
        'onTwigSiteVariables' => ['onTwigSiteVariables', 0]
      ]);
    }
  }

  /**
   * If enabled on this page, load the JS + CSS and set the selectors.
   */
  public function onTwigSiteVariables() {
    // see if we're actually rendering an app instead of loading dependencies
    if (is_array($this->activeApp)) {
      $twig = $this->grav['twig'];
      $twig->template = 'webcomponents-app.html.twig';
      $twig->twig_vars['webcomponents'] = $this->renderApp($this->activeApp);
    }
    $config = $this->config->get('plugins.webcomponents');
    // discover and autoload our components
    $assets = $this->grav['assets'];
    // directory they live in physically
    $dir = $this->webcomponentsDir();
    $polyfill = $this->getBaseURL() . 'webcomponentsjs/webcomponents-lite.js';
    // find all files
    $files = $this->findWebcomponentFiles($dir, $this->getBaseURL());
    $imports = '';
    // include our elements
    foreach ($files as $file) {
      $imports .= $this->createHTMLImport($file) . "\n";
    }
    // build the inline import
    $inline = "
// simple performance imporvements for Polymer
window.Polymer = {
  dom: 'shady',
  lazyRegister: true
};
window.onload = function() {
  if ('registerElement' in document
    && 'import' in document.createElement('link')
    && 'content' in document.createElement('template')) {
    // platform is good!
  }
  else {
    // polyfill the platform!
    var e = document.createElement('script');
    e.src = '$polyfill';
    document.head.appendChild(e);
  }
};
</script>" . $imports . "<script>";
    // add it into the document
    $assets->addInlineJs($inline, array('priority' => 102, 'group' => 'head'));
  }

  /**
   * Return the base url for forming paths on the front end.
   * @return string  The base path to the user / webcomponents directory
   */
  public function getBaseURL() {
    return $this->grav['base_url'] . '/user/webcomponents/';
  }

  /**
   * Return the file system directory for forming paths on the front end.
   * @return string  The base path to the user / webcomponents directory
   */
  public function webcomponentsDir() {
    return getcwd() . '/user/webcomponents/';
  }
  /**
   * Simple HTML Import render.
   */
  public function createHTMLImport($path, $rel = 'import') {
    return '<link rel="' . $rel . '" href="' . $path . '">';
  }

  /**
   * Sniff out html files in a directory
   * @param  string $dir a directory to search for .html includes
   * @return array       an array of html files to look for web components in
   */
  public function findWebcomponentFiles($dir, $base, $ignore = array(), $find = '.html') {
    $files = array();
    // common things to ignore
    $ignore[] = '.';
    $ignore[] = '..';
    $ignore[] = 'index.html';
    if (is_dir($dir)) {
      // step into the polymer directory and find all html templates
      $di = new \DirectoryIterator($dir);
      foreach ($di as $fileinfo) {
        $fname = $fileinfo->getFilename();
        // check for our find value skipping ignored values
        if (strpos($fname, $find) && !in_array($fname, $ignore)) {
          $files[] = $base . $fileinfo->getFilename();
        }
        elseif (is_dir($dir . $fname) && !in_array($fname, $ignore)) {
          $di2 = new \DirectoryIterator($dir . $fname);
          foreach ($di2 as $fileinfo2) {
            $fname2 = $fileinfo2->getFilename();
            // check for our find value skipping ignored values
            if (strpos($fname2, $find) && !in_array($fname2, $ignore)) {
              $files[] = $base . $fname . '/' . $fname2;
            }
            elseif (is_dir($dir . $fname . '/' . $fname2) && !in_array($fname2, $ignore)) {
              $di3 = new \DirectoryIterator($dir . $fname . '/' . $fname2);
              foreach ($di3 as $fileinfo3) {
                $fname3 = $fileinfo3->getFilename();
                // check for our find value skipping ignored values
                if (strpos($fname3, $find) && !in_array($fname3, $ignore)) {
                  $files[] = $base . $fname . '/' . $fname2 . '/' . $fname3;
                }
              }
            }
          }
        }
      }
    }
    return $files;
  }

  /**
   * Load all apps where we find a manifest.json file
   */
  public function discoverWebcomponentApps() {
    $return = array();
    $dir = $this->webcomponentsDir() . 'polymer/apps/';
    $files = $this->findWebcomponentFiles($dir, $this->getBaseURL() . 'polymer/apps/', array(), '.json');
    // walk the files
    foreach ($files as $file) {
      // read in the manifest file
      if (strpos($file, 'manifest.json')) {
        // load the manifest json file
        $tmp = str_replace($this->grav['base_url'], '', $file);
        $tmp = getcwd() . $tmp;
        $manifest = json_decode(file_get_contents($tmp));
        $manifest = (array)$manifest;
        $return[$manifest['name']] = array(
          'title' => $manifest['short_name'],
          'description' => $manifest['description'],
          'path' => str_replace('manifest.json', '', $file),
          'filepath' => str_replace('manifest.json', '', $tmp),
        );
        $return[$manifest['name']]['machine_name'] = $manifest['name'];
        // support for specific properties to be set in manifest
        if (isset($manifest['app_integration'])) {
          $app = (array)$manifest['app_integration'];
          // support for more expressive title specific to integrations
          if (isset($app['title'])) {
            $return[$manifest['name']]['title'] = $app['title'];
          }
          // support for opa-root integrations
          if (isset($app['opa-root'])) {
            $return[$manifest['name']]['opa-root'] = $app['opa-root'];
          }
          // support for generating a visualized menu item in the system
          if (isset($app['menu'])) {
            $return[$manifest['name']]['menu'] = $app['menu'];
          }
          // support for additional properties
          if (isset($app['properties'])) {
            $return[$manifest['name']]['properties'] = (array)$app['properties'];
          }
          // support for additional slots
          if (isset($app['slots'])) {
            $return[$manifest['name']]['slots'] = (array)$app['slots'];
          }
          // support for a endpoint paths for getting data into the app
          if (isset($app['endpoints'])) {
            $return[$manifest['name']]['endpoints'] = (array)$app['endpoints'];
          }
          // support for discovering and autoloading an element-name.php file
          // to make decoupled development even easier!
          if (file_exists(str_replace('manifest.json', $manifest['name'] . '.php', $tmp))) {
            $return[$manifest['name']]['autoload'] = TRUE;
          }
          // support automatically making a block for this element
          if (isset($app['block'])) {
            $return[$manifest['name']]['block'] = $app['block'];
          }
          // general support for anything you want to store for context
          if (isset($app['context'])) {
            $return[$manifest['name']]['context'] = $app['context'];
          }
        }
      }
    }
    return $return;
  }

  /**
   * Load an app based on machine name
   */
  public function loadWebcomponentApps($machine_name = NULL, $force_rebuild = FALSE) {
    // load all app definitions
    $apps = $this->discoverWebcomponentApps();
    if (!is_null($machine_name)) {
      // validate that this bucket exists
      if (isset($apps[$machine_name])) {
        // check for autoloading flag if so then load the file which should contain
        // the functions needed to make the call happen
        if (isset($apps[$machine_name]['autoload']) && $apps[$machine_name]['autoload'] === TRUE) {
          include_once $apps[$machine_name]['filepath'] . $machine_name . '.php';
        }
        $apps[$machine_name]['machine_name'] = $machine_name;
        return $apps[$machine_name];
      }
      // nothing at this point, return nothing since we don't know that machine name
      return array();
    }
    // validate apps were found
    if (!empty($apps)) {
      return $apps;
    }
    // nothing at this point, return nothing
    return array();
  }

  /**
   * Render an app based on machine name.
   */
  public function renderApp($app = array()) {
    $return = '';
    $vars = array();
    $machine_name = $app['machine_name'];
    $assets = $this->grav['assets'];
    // set a custom is_app property so other render alters can realize
    // this is an app rendering being modified and not a normal page component
    $app['is_app'] = TRUE;
    // ensure this exists
    if (!empty($machine_name) && !empty($app)) {
      $hash = filesize($app['filepath'] . 'manifest.json');
      $return['manifest'] = $app['path'] . 'manifest.json?h' . $hash;
      $hash = filesize($app['filepath'] . 'src/' . $machine_name . '/' . $machine_name . '.html');
      $return['import'] = $app['path'] . 'src/' . $machine_name . '/' . $machine_name . '.html?h' . $hash;
      // construct the tag base to be written
      $vars = array(
        'tag' => $machine_name,
        'properties' => array(),
      );
      // support for properties to be mixed in automatically
      if (isset($app['properties'])) {
        foreach ($app['properties'] as $key => $property) {
          $property = (array)$property;
          // support for simple function based callbacks for properties from functions
          if (is_array($property) && isset($property['callback'])) {
            // ensure it exists of that would be bad news bears
            if (function_exists($property['callback'])) {
              // only allow for simple function callbacks
              $vars['properties'][$key] = call_user_func($property['callback']);
            }
            else {
              // well it failed but at least set it to nothing
              $vars['properties'][$key] = NULL;
              // missing function, let's log this to the screen or watchdog if its debug mode
              $this->grav['debugger']->addMessage("The $machine_name app wants to hit the callback " . $property['callback'] . " for property $key but this function could not be found");
            }
          }
          else {
            $vars['properties'][$key] = $property;
          }
        }
      }
      // support for slots to be mixed in automatically
      if (isset($app['slots'])) {
        foreach ($app['slots'] as $key => $slot) {
          if (is_object($slot)) {
            $slot = (array)$slot;
          }
          // support for simple function based callbacks for slots from functions
          if (is_array($slot) && isset($slot['callback'])) {
            // ensure it exists of that would be bad news bears
            if (function_exists($slot['callback'])) {
              // only allow for simple function callbacks
              $vars['slots'][$key] = call_user_func($slot['callback']);
            }
            else {
              // well it failed but at least set it to nothing
              $vars['slots'][$key] = NULL;
              // missing function, let's log this to the screen or watchdog if its debug mode
              $this->grav['debugger']->addMessage("The $machine_name app wants to hit the callback " . $slot['callback'] . " for slot $key but this function could not be found");
            }
          }
          else {
            $vars['slots'][$key] = $slot;
          }
        }
      }
      // special properties that register endpoints
      if (isset($app['endpoints'])) {
        // all end points will be able to use this for simple, secure construction
        // @see secure-request webcomponent for behavior details if doing app development
        $vars['properties']['csrf-token'] = Utils::getNonce('webcomponentapp');
        $vars['properties']['end-point'] = $this->grav['base_url'] . '/' . WEBCOMPONENTS_APP_PATH . '/' . $machine_name;
        $vars['properties']['base-path'] = $this->grav['base_url'] . '/' . WEBCOMPONENTS_APP_PATH . '/';
        // see if anything needs ripped into the element
        foreach ($app['endpoints'] as $endpointpath => $endpoint) {
          if (isset($endpoint->property)) {
            $vars['properties'][$endpoint->property] = $vars['properties']['end-point'] . '/' . $endpointpath . '?token=' . $vars['properties']['csrf-token'];
          }
        }
      }
      // support for one page apps to pass down their root correctly
      else if (isset($app['opa-root'])) {
        $vars['properties']['csrf-token'] = Utils::getNonce('webcomponentapp');
        $vars['properties']['base-path'] = $this->grav['base_url'] . '/' . WEBCOMPONENTS_APP_PATH . '/';
      }
      // support compressing slots into the innerHTML tag
      if (isset($vars['slots'])) {
        // support single slot name
        if (is_string($vars['slots'])) {
          $vars['innerHTML'] = $vars['slots'];
        }
        // support for multiple slot names
        else if (is_array($vars['slots'])) {
          $vars['innerHTML'] = '';
          foreach ($vars['slots'] as $name => $content) {
            $vars['innerHTML'] .= '<span slot="' . $name . '">' . $content . '</span>';
          }
        }
      }
      else {
        $vars['innerHTML'] = '';
      }
      // add on custom class to help idenfity we delivered this
      if (!isset($vars['properties']['class'])) {
        $vars['properties']['class'] = WEBCOMPONENTS_CLASS_IDENTIFIER;
      }
      else {
        $vars['properties']['class'] .= ' ' . WEBCOMPONENTS_CLASS_IDENTIFIER;
      }

      $vars['properties'] = $this->webcomponentAttributes($vars['properties']);
      $return['app'] = $vars;
    }
    return $return;
  }
  /**
   * Render a webcomponent to the screen.
   * @param  [type] $vars [description]
   * @return [type]       [description]
   */
  public function renderWebcomponent($vars) {
    return '<' . $vars['tag'] . ' ' . $this->webcomponentAttributes($vars['properties']) . '>' . "\n" . $vars['innerHTML'] . "\n" . '</' . $vars['tag'] . '>' . "\n";
  }
  /**
   * Convert array into attributes for placement in an HTML tag.
   * @param  array  $attributes array of attribute name => value pairs
   * @return string             HTML name="value" output
   */
  protected function webcomponentAttributes(array $attributes = array()) {
    foreach ($attributes as $attribute => &$data) {
      $data = implode(' ', (array) $data);
      $data = $attribute . '="' . htmlspecialchars($data, ENT_QUOTES, 'UTF-8') . '"';
    }
    return $attributes ? ' ' . implode(' ', $attributes) : '';
  }
}
