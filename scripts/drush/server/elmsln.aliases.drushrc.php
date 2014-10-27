<?php
  // @todo look into pulling the stacks array from config.cfg
  // @todo look into static storing of this value since the file
  // appears to be running up to 3x for some reason
  // @todo run a simple increment command so that we take a bs variable
  // and increment it every time this is currently run under a @stack-all
  // target. I get the feeling that these sites are run 2-3x per site.
  // While not a problem, we could be much more efficient then currently.
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
        $config[$tmp[0]] = $tmp[1];
      }
    }
  }
  $aliases = array();
  // base address of all domains
  $address = $config['address'];
  // your web root
  $root = $config['stacks'] . '/';
  // grouping item for your stack
  $group = $config['host'];
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
    $aliases[$key . $modifier] = array('site-list' => array());
  }
}
