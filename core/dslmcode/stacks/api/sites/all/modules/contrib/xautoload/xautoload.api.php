<?php

/**
 * @file
 * Hooks provided by X Autoload.
 */

/**
 * Example method showing how to register namespaces from anywhere.
 */
function EXAMPLE_foo() {
  // Register stuff directly to the class finder.
  xautoload()->finder->addPsr4('Aaa\Bbb\\', 'sites/all/libraries/aaa-bbb/src');

  // Or use an adapter with more powerful methods.
  xautoload()->adapter->composerDir('sites/all/vendor/composer');
}

/**
 * Implements hook_xautoload()
 *
 * Register additional classes, namespaces, autoload patterns, that are not
 * already registered by default.
 *
 * @param \Drupal\xautoload\Adapter\LocalDirectoryAdapter $adapter
 *   An adapter object that can register stuff into the class loader.
 */
function hook_xautoload($adapter) {

  // Register a namespace with PSR-0.
  $adapter->add(
    // Namespace of a 3rd party package included in the module directory.
    'Acme\GardenKit\\',
    // Path to the 3rd party package, relative to the module directory.
    'shrubbery/lib');

  // Register a namespace with PSR-4.
  $adapter->absolute()->addPsr4(
    // The namespace.
    'Acme\ShrubGardens\\',
    // Absolute path to the PSR-4 base directory.
    '/home/karnouffle/php/shrub-gardens/src');

  // Scan sites/all/vendor/composer for Composer-generated autoload files, e.g.
  // 'sites/all/vendor/composer/autoload_namespaces.php', etc.
  $adapter->absolute()->composerDir('sites/all/vendor/composer');
}


/**
 * Implements hook_libraries_info()
 *
 * Allows to register PSR-0 (or other) class folders for your libraries.
 * (those things living in sites/all/libraries)
 *
 * The original documentation for this hook is at libraries module,
 * libraries.api.php
 *
 * X Autoload extends the capabilities of this hook, by adding an "xautoload"
 * key. This key takes a callback or closure function, which has the same
 * signature as hook_xautoload($adapter).
 * This means, you can use the same methods on the $api object.
 *
 * @return array[]
 *   Same as explained in libraries module, but with added key 'xautoload'.
 */
function mymodule_libraries_info() {

  return array(
    'ruebenkraut' => array(
      'name' => 'Rübenkraut library',
      'vendor url' => 'http://www.example.com',
      'download url' => 'http://github.com/example/ruebenkraut',
      'version' => '1.0',
      'xautoload' => function($adapter) {
          /**
           * @var \Drupal\xautoload\Adapter\LocalDirectoryAdapter $adapter
           *   An adapter object that can register stuff into the class loader.
           */
          // Register a namespace with PSR-0 root in
          // 'sites/all/libraries/ruebenkraut/src'.
          $adapter->add('Rueben\Kraut\\', 'src');
        },
    ),
    'gurkentraum' => array(
      'name' => 'Gurkentraum library',
      'xautoload' => function($adapter) {
          /** @var \Drupal\xautoload\Adapter\LocalDirectoryAdapter $adapter */
          // Scan sites/all/libraries/ruebenkraut/composer.json to look for
          // autoload information.
          $adapter->composerJson('composer.json');
        }
    )
  );
}
