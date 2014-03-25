<?php
  $aliases = array();
  // base address of all domains
  $address = 'example.com';
  // your web root
  $root = '/var/www/elmsln/core/dslmcode/stacks/';
  // grouping item for your stack
  $group = 'ex';
  // stacks you have
  $stacks = array(
    'online',
    'courses',
    'studio',
    'media',
    'interact',
    'blog',
  );
  // loop through known stacks
  foreach ($stacks as $stack) {
    // only include stack if it has things we can step through
    // this helps avoid issues of unused stacks throwing errors
    if (file_exists("$root$stack/sites/$stack/$group")) {
      // build root alias for the stack
      $aliases[$stack] = array(
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
            $aliases["$stack.$basename"] = array(
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
      $aliases["$stack.$group"] = array(
        'parent' => "@$stack",
        'uri' => "$stack.$address",
      );
    }
  }

/**
 * Magic to auto produce additional alias sub-groups
 */
$modifier = '-all';
foreach ($aliases as $key => $values) {
  $parts = explode('.', $key);
  if (count($parts) >= 2) {
    // something that's in a subgroup
    array_push($aliases[$parts[0] . $modifier]['site-list'], '@' . $key);
  }
  else {
    // something is group-able
    $aliases[$key . $modifier] = array('site-list' => array('@' . $key));
  }
}
