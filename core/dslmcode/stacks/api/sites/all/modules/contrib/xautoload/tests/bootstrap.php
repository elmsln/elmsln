<?php

use Drupal\xautoload\Discovery\ClassMapGenerator;

require_once dirname(__DIR__) . '/xautoload.early.lib.inc';

_xautoload_register();

xautoload()->finder->addPsr4('Drupal\xautoload\Tests\\', __DIR__ . '/src/');

// Use a non-cached class map generator.
xautoload()->getServiceContainer()->set('classMapGenerator', new ClassMapGenerator());

// Register a one-off class loader for the test PSR-4 classes.
/*
call_user_func(
  function() {
    $addPsr4 = function($namespace, $src) {
      $strlen = strlen($namespace);
      spl_autoload_register(
        function ($class) use ($src, $namespace, $strlen) {
          if (0 === strpos($class, $namespace)) {
            $file = $src . '/' . str_replace('\\', '/', substr($class, $strlen)) . '.php';
            if (file_exists($file)) {
              require_once $file;
              return TRUE;
            }
          }
          return FALSE;
        }
      );
    };
    $addPsr4('Drupal\xautoload\Tests\\', __DIR__ . '/src');
    $addPsr4('Drupal\xautoload\\', dirname(__DIR__) . '/src');
  }
);
*/
