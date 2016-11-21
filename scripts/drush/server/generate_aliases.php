<?php
require_once '/var/www/elmsln/core/dslmcode/elmsln_environment/elmsln_environment.php';

/**
 * Automatically find and create drush aliases on the server.
 * @param  array $aliases  array of drush aliases
 */
function _elmsln_alises_build_server(&$aliases, &$authorities = array()) {
  global $elmslncfg;
  // static cache assembled aliases as this can get tripped often
  static $pulledaliases = array();
  static $pulledauthorities = array();
  static $config = array();
  // check for pervasive cache if static is empty
  if (empty($pulledaliases)) {
    // assumption here is that it lives where we expect
    // change this line if that's not the case though we really don't
    // support changes to that part of the install routine
    $config = $elmslncfg;
    // base address of all domains
    $address = $config['address'];
    // your web root
    $root = $config['stacks'] . '/';
    // calculate the stacks we have
    $stacks = array();
    $stackfinder = new DirectoryIterator("$root");

    while ($stackfinder->valid()) {
      // Look for directories that are stacks
      if ($stackfinder->isDir() && !$stackfinder->isDot() && !$stackfinder->isLink()) {
        $stacks[] = $stackfinder->getBasename();
      }
      $stackfinder->next();
    }
    // loop through known stacks
    foreach ($stacks as $stack) {
      // step through sites directory assuming it isn't the 'default'
      if ($stack != 'default' && is_dir("$root$stack/sites/$stack")) {
        try {
          $stackdir = new DirectoryIterator("$root$stack/sites/$stack");
          while ($stackdir->valid()) {
            // Look for directories containing a 'settings.php' file
            if ($stackdir->isDir() && !$stackdir->isDot() && !$stackdir->isLink()) {
              $group = $stackdir->getBasename();
              // only include stack if it has things we can step through
              // this helps avoid issues of unused stacks throwing errors
              if (file_exists("$root$stack/sites/$stack/$group")) {
                // build root alias for the stack
                $pulledauthorities[$stack] = array(
                  'root' => $root . $stack,
                  'uri' => "$stack.$address",
                );

                // step through sites directory
                if (is_dir("$root$stack/sites/$stack/$group")) {
                  $site = new DirectoryIterator("$root$stack/sites/$stack/$group");
                  while ($site->valid()) {
                    // Look for directories containing a 'settings.php' file
                    if ($site->isDir() && !$site->isDot() && !$site->isLink()) {
                      if (file_exists($site->getPathname() . '/settings.php')) {
                        // Add site alias
                        $basename = $site->getBasename();
                        // test that this isn't actually something like coursename = host
                        if ($basename == $config['host'] && !is_dir("$root$stack/sites/$stack/$group/$group")) {
                          $pulledaliases["$stack.$basename"] = array(
                            'root' => $root . $stack,
                            'uri' => "$stack.$address",
                          );
                        }
                        else {
                          $pulledaliases["$stack.$basename"] = array(
                            'root' => $root . $stack,
                            'uri' => "$stack.$address.$basename",
                          );
                        }
                      }
                    }
                    $site->next();
                  }
                }
              }
            }
            $stackdir->next();
          }
        } catch (Exception $e) {
          // that tool doesn't have a directory, oh well
        }
      }
    }
  }
  $aliases = $pulledaliases;
  $authorities = $pulledauthorities;
  return $config;
}
