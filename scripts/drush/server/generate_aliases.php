<?php
/**
 * Automatically find and create drush aliases on the server.
 * @param  array $aliases  array of drush aliases
 */
function _elmsln_alises_build_server(&$aliases) {
  // static cache assembled aliases as this can get tripped often
  static $pulledaliases = array();
  // check for pervasive cache if static is empty
  if (empty($pulledaliases)) {
    // assumption here is that it lives where we expect
    // change this line if that's not the case though we really don't
    // support changes to that part of the install routine
    $cfg = file_get_contents('/var/www/elmsln/config/scripts/drush-create-site/config.cfg');
    $lines = explode("\n", $cfg);
    $config = array();
    // read each line of the config file
    foreach ($lines as $line) {
      // make sure this line isn't a comment and has a=
      if (strpos($line, '#') !== 0 && strpos($line, '=')) {
        $tmp = explode('=', $line);
        // ensure we have 2 settings before doing this
        if (count($tmp) == 2) {
          // never pass around the dbsu
          if (!in_array($tmp[0], array('dbsu', 'dbsupw'))) {
            // strip encapsulation if it exists
            $config[$tmp[0]] = str_replace('"', '', str_replace("'", '', $tmp[1]));
          }
        }
      }
    }
    // support the fact that $elmsln is used to reference in many bash vars
    foreach ($config as $key => $value) {
      if (strpos($value, '$elmsln') !== FALSE) {
        $config[$key] = str_replace('$elmsln', $config['elmsln'], $value);
      }
    }
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
    }
    // loop through known stacks
    foreach ($stacks as $stack) {
      // step through sites directory
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
              $pulledaliases[$stack] = array(
                'root' => $root . $stack,
                'uri' => "$stack.$address",
              );
              // step through sites directory
              $site = new DirectoryIterator("$root$stack/sites/$stack/$group");
              while ($site->valid()) {
                // Look for directories containing a 'settings.php' file
                if ($site->isDir() && !$site->isDot() && !$site->isLink()) {
                  if (file_exists($site->getPathname() . '/settings.php')) {
                    // Add site alias
                    $basename = $site->getBasename();
                    $pulledaliases["$stack.$basename"] = array(
                      'parent' => "@$stack",
                      'uri' => "$stack.$address.$basename",
                    );
                  }
                }
                $site->next();
              }
            }
            // account for stacks that function more like CIS
            if (file_exists("$root$stack/sites/$stack/$group/settings.php")) {
              $pulledaliases["$stack.$group"] = array(
                'parent' => "@$stack",
                'uri' => "$stack.$address",
              );
            }
          }
          $stackdir->next();
        }
      } catch (Exception $e) {
        // that tool doesn't have a directory, oh well
      }
    }
  }

  /**
   * Magic to auto produce additional alias sub-groups
   */
  $modifier = '-all';
  foreach ($pulledaliases as $key => $values) {
    $aliases[$key] = $values;
    $parts = explode('.', $key);
    if (count($parts) >= 2) {
      // something that's in a subgroup
      array_push($aliases[$parts[0] . $modifier]['site-list'], '@' . $key);
    }
    else {
      // something is group-able
      $aliases[$key . $modifier] = array('site-list' => array());
    }
  }
}
