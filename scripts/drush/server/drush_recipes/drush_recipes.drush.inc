<?php

/**
 * @file
 * Drush Recipe format.
 *
 * This format allows you to call a series of drush calls to fire in
 * succession. This allows them to be packaged along with modules and
 * themes and is a complementary format to .make files. Where .make is
 * for describing how to make a site. drush recipe files are for producing a
 * structured, reusable, desired result.
 *
 * Much of what you can do with drecipes can be done via features but
 * this obviously is far less packaging cruft. It also allows you to be
 * intentionally destructive with your calls instead of worrying about
 * being in "override hell" with features and features_override.
 */

define('DRUSH_RECIPE_EXTENSION', 'drecipe');
define('DRUSH_RECIPES_API_VERSION', '1.0');
define('DRUSH_RECIPES_CORE_COMPATIBILITY', '7');
define('DRUSH_RECIPES_MAX_RECURSION', 5);
define('DRUSH_RECIPES_INVALID', FALSE);
define('DRUSH_RECIPES_VALID', TRUE);
define('DRUSH_RECIPES_DEFAULT_URL', 'http://drush.recipes/recipes.xml');
define('DRUSH_RECIPES_COMMAND_CID', 'recorded-commands');
define('DRUSH_RECIPES_LOGGING_CID', 'command-recording');
// listing of the types of drush recipe formats we support
define('DRUSH_RECIPES_FORMAT_REFERENCE', 'reference');
define('DRUSH_RECIPES_FORMAT_TARGET', 'command');
define('DRUSH_RECIPES_FORMAT_MADLIB', 'madlib');
define('DRUSH_RECIPES_FORMAT_CONDITIONAL', 'conditional');
define('DRUSH_RECIPES_FORMAT_CONDITIONAL_QUESTION', 'prompt');
define('DRUSH_RECIPES_FORMAT_ARGUMENT', 'argument');

/**
 * Implements hook_drush_command().
 */
function drush_recipes_drush_command() {
  $items = array();
  $items['drush-list-recipes'] = array(
    'description' => dt('List the available recipes and where they are loaded from'),
    'arguments' => array(
      'list' => dt('Recipies to list, comma separated'),
    ),
    'options' => array(
      'more-detail' => dt('Show all info available'),
      'dr-locations' => dt('User defined list of other locations to load in from'),
    ),
    'aliases' => array('dlr'),
    'examples' => array(
      'drush drush-list-recipes' =>
        'A nicely printed listing of available recipes',
      'drush dlr dr_security,dr_admin_update_status' =>
        'Only list these two recipes',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
  );
  $items['drush-recipes-url'] = array(
    'description' => dt('Import recipes from a remote service like drush.recipes'),
    'arguments' => array(
      'url' => dt('A URL to return results from.'),
    ),
    'aliases' => array('drurl'),
    'examples' => array(
      'drush drurl ' . DRUSH_RECIPES_DEFAULT_URL . '&uid=10' =>
        'Display a list of recipes for user 10 from the drush.recipes service.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  // @todo issue about this https://www.drupal.org/node/2326463
  /*$items['drush-dl'] = array(
    'description' => dt('Simple download of something'),
    'arguments' => array(
      'url' => dt('A URL to download from.'),
      'desintation' => dt('Destination to save the download'),
      'cache_duration' => dt('How long til we check for a fresh copy, 0 is default'),
    ),
    'aliases' => array('dl'),
    'examples' => array(
      'drush drurl ' . DRUSH_RECIPES_DEFAULT_URL . '&uid=10' =>
        'Display a list of recipes for user 10 from the drush.recipes service.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );*/
  $items['drush-write-recipe'] = array(
    'description' => dt('Interactive prompt to create a new recipe'),
    'aliases' => array('dwr'),
    'options' => array(
      'for-drup' => dt('Flag to indicate that this is an upgrade routine for use with the drup command.'),
    ),
    'examples' => array(
      'drush dwr' =>
        'An interactive prompt will follow',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['drush-validate-recipes'] = array(
    'description' => dt('Validate a saved recipe will run if built from scratch'),
    'aliases' => array('valid-recipe'),
    'examples' => array(
      'drush valid-recipe dr_security' =>
        'Validate that dr_security will work if cooked.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['drush-recipe-recorder'] = array(
    'description' => dt('Toggle recording drush commands for a new recipe'),
    'aliases' => array('dvr'),
    'arguments' => array(
      'state' => dt('State of recording, whether to start, save, watch, pause, delete or stop'),
    ),
    'options' => array(
      'test-run' => dt('Use this to test run recipe saving'),
      'command' => dt('Used with dvr delete; either the command to delete or an array position'),
    ),
    'allow-additional-options' => TRUE,
    'examples' => array(
      'drush dvr start' =>
        'Start recording drush commands to cache',
      'drush dvr save' =>
        'Save recording but don\'t stop recording after the fact',
      'drush dvr save --test-run' =>
        'Simulate saving recipe, this will be get printed to the screen',
      'drush dvr watch' =>
        'See what\'s currently been recorded',
      'drush dvr pause' =>
        'Save recording but don\'t stop recording after the fact',
      'drush dvr delete' =>
        'Delete the current recordings, this doesn\'t stop recording though',
      'drush dvr delete --command=12' =>
        'Delete the recorded command in the 12th array slot, if confirmed.',
      'drush dvr delete --command=sql-sync' =>
        'Delete sql-sync commands from the current recording, if confirmed.',
      'drush dvr stop' =>
        'Stop recording to save a recipe then delete commandlist',
      'drush dvr stop --test-run' =>
        'Simulate stop/ saving recipe, this will be get printed to the screen',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['drush-diff-targets-recipe'] = array(
    'description' => dt('Analyze two targets and create a recipe to chart a course from one to another. Great for figuring out what a client changed after a distro was installed.'),
    'aliases' => array('ddt'),
    'options' => array(
      'components' => dt('Components that you want to include in the diff. possible core values: modules, variables, roles, features'),
      'test-run' => dt('This will quickly print it to the screen without asking questions.'),
      'make-it-so' => dt('Apply the change between source and destination to make the source the same as the destination'),
    ),
    'examples' => array(
      'drush @target1 ddt @target2' =>
        'Analysis will occur of how target2 is different then target1 and a suggested recipe to follow how to get target1 to be target2 will be generated (either to the screen or written to a file.',
      'drush @target1 ddt --components=modules,variables' =>
        'Export the module and variable definitions in target1 and create a recipe that would allow it to be recreated in a future system.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['drush-cook-recipes'] = array(
    'description' => dt('"cook" up a drush recipe'),
    'arguments' => array(
      'recipes' => dt("List of recipes to run, in order and comma separated"),
    ),
    'options' => array(
      'dr-locations' => dt('User defined list of other locations to load in from'),
      'simple-uncook' => dt('Allow for a simple recipe reversal, like swapping enables for disables; good for lazy devs with simple recipes.'),
      'dr-skip-checks' => dt('Allow user to skip dependency checks, useful for debugging calls.'),
    ),
    'allow-additional-options' => TRUE,
    'aliases' => array('cook', 'c'),
    'examples' => array(
      'drush drush-cook-recipes dr_security' =>
        'Run the dr_security recipe',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
  );
  $items['drush-recipes-upgrade'] = array(
    'description' => dt('Search for recipes to execute against targets'),
    'arguments' => array(
      'pattern' => dt("Pattern of recipes to find"),
      'location' => dt("Location to search against for matching recipes"),
    ),
    'options' => array(
      'replay-from' => dt("Replay from a certain timestamp forward. This is useful if an update fails to apply for some reason."),
    ),
    'aliases' => array('drup'),
    'examples' => array(
      'drush @devsite drup d7_dev /var/www/deployments/' =>
        'Search in /var/www/deployments/ for .drecipe files that include d7_dev in the name and then execute them against @devsite. Wow.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function drush_recipes_drush_help($section) {
  switch ($section) {
    case 'drush:drush-list-recipes':
      return dt('List the available recipes');
    case 'drush:drush-recipes-url':
      return dt('Sync recipes from a remote service like drush.recipes');
    case 'drush:drush-write-recipe':
      return dt('Write a new recipe from commandline');
    case 'drush:drush-diff-targets-recipe':
      return dt('Create a recipe to calculate the diff between systems.');
    case 'drush:drush-cook-recipes':
      return dt('Perform a series of drush recipes');
    case 'drush:drush-recipes-upgrade':
      return dt('Apply upgrades by spidering for aliases that match');
  /*  case 'drush:drush-dl':
      return dt('Download a file from a url');*/
    case 'drush:drush-validate-recipes':
      return dt('Validate a recipe is in the correct format.');
    case 'drush-recipe-recorder':
      return dt('Activate the Drush Recipe DVR to never miss a call again!');
  }
}

/**
 * Drush command callback for drush-recipes-upgrade.
 */
function drush_drush_recipes_upgrade($pattern, $location) {
  if (is_null($pattern) || is_null($location)) {
    drush_log(dt('A partial file name and location must be supplied.'), 'error');
    return FALSE;
  }
  // ensure we at least reached a drupal site bootstrap
  $bootstrap = drush_get_context('DRUSH_BOOTSTRAP_PHASE');
  if ($bootstrap == DRUSH_BOOTSTRAP_DRUSH) {
    drush_log(dt('You must have a fully loaded site to use this command.'), 'error');
    return FALSE;
  }
  $command = array(
    'command' => 'cook',
  );
  _drush_recipes_command_defaults($command);
  if (empty($command['target'])) {
    drush_log(dt('You must define a site alias to use this command.'), 'error');
    return FALSE;
  }
  $recipe_pattern = '/^' . DRUPAL_PHP_FUNCTION_PATTERN . '\.' . DRUSH_RECIPE_EXTENSION . '/';
  // find recipes in the drecipes directory
  $recipes = _drush_recipes_drupal_system_listing($recipe_pattern, $location);
  // see if we've upgraded anything previously
  $last = variable_get('drup_last_upgrade', array());
  $install_time = variable_get('install_time', 0);
  if ($install_time == 0) {
    drush_log(dt("install_time is not set for the site which means that if any updates are found, ALL of them will be applied. This is only possible on an installation that's corrupted in some way. Just letting you know!"), 'warning');
  }
  // alert the user upgrades of this nature have never run previously
  if (empty($last)) {
    drush_log(dt('Drush upgrade command has never been run on this site, just letting you know!'), 'ok');
    // default the last time updates were applied to the site's install time
    $last = array($pattern => $install_time);
  }
  else {
    // alert them they've never run upgrades of this pattern previously
    if (!isset($last[$pattern])) {
      drush_log(dt('Drush upgrades of this pattern have never run previously, just letting you know!'), 'ok');
      $last[$pattern] = $install_time;
    }
  }
  // allow for replaying from a certain point in time via flag
  $replay = drush_get_option('replay-from', FALSE);
  if ($replay !== FALSE) {
    $last[$pattern] = $replay;
  }
  $matches = array();
  // scan each and match it against the alias if we can
  foreach ($recipes as $recipe) {
    // look for the alias in the recipe name
    if (strpos($recipe->name, $pattern) !== FALSE) {
      $basename = $recipe->basename;
      $num = array_pop(explode('_', str_replace('.' . DRUSH_RECIPE_EXTENSION, '', $basename)));
      // if num is higher then stored value, we have new recipes to run!
      if (is_numeric($num) && $num > $last[$pattern]) {
        $matches[$recipe->name] = array(
          'name' => $recipe->name,
          'path' => str_replace($recipe->basename, '', $recipe->filename),
          'num' => $num,
          'basename' => $recipe->basename,
        );
      }
    }
  }
  ksort($matches);
  // drop out if nothing matched this upgrade pattern
  if (empty($matches)) {
    drush_log(dt('No recipes matched the supplied pattern for site upgrade'), 'warning');
    return TRUE;
  }
  // confirm they want to do this
  drush_print_r($matches);
  if (drush_confirm(dt('You are about to execute the above recipes as part of this upgrade'))) {
    foreach ($matches as $recipe_info){
      $tmpcommand = $command;
      $tmpcommand['arguments'][] = $recipe_info['name'];
      $tmpcommand['options']['dr-locations'] = $recipe_info['path'];
      $last[$pattern] = $recipe_info['num'];
      // invoke this process for the command
      drush_invoke_process($tmpcommand['target'], $tmpcommand['command'], $tmpcommand['arguments'], $tmpcommand['options']);
      variable_set('drup_last_upgrade', $last);
    }
    drush_log(dt('Upgrade complete!'), 'ok');
    return TRUE;
  }
  return drush_user_abort();
}

/**
 * Drush command callback for drush-diff-targets-recipe.
 */
function drush_drush_recipes_drush_diff_targets_recipe($source = NULL, $destination = NULL) {
  // test for source being provided by target
  $alias = drush_get_context('DRUSH_TARGET_SITE_ALIAS');
  $drush = array();
  // if alias is not empty / @none and destination is empty
  if (!empty($alias) && $alias != '@none' && empty($destination)) {
    $destination = $source;
    $source = $alias;
  }
  // test for null case target diffing via lazy method
  if ((empty($destination) || $destination == '@none') && !empty($source)) {
    $destination = $source;
    $source = '@none';
  }
  // edge case, ddt run without a target defined, needs to be self
  if (empty($destination) || $destination == '@none') {
    $destination = '@self';
  }
  // edge case, ddt run without a target defined, needs to be self
  if (empty($source)) {
    $source = '@none';
  }
  // test for components option
  $components = explode(',', drush_get_option('components', 'modules,variables,roles,features'));

  // preflight destination in case it defines the alias used by the source
  _drush_sitealias_get_record($destination);
  // after preflight, get source and destination settings
  $source_settings = drush_sitealias_get_record($source);
  $destination_settings = drush_sitealias_get_record($destination);
  // apply command-specific options.
  drush_sitealias_command_default_options($source_settings, 'source-');
  drush_sitealias_command_default_options($destination_settings, 'target-');
  // see if we shold export module differences
  if (in_array('modules', $components)) {
    // select module / themes / profiles in use via system table
    $fields = array('name', 'type', 'status');
    $source_system = _drush_recipes_load_db_table($source_settings, 'system', 'name', $fields);
    $destination_system = _drush_recipes_load_db_table($destination_settings, 'system', 'name', $fields);
    // compare the source with the destination
    foreach ($source_system as $project => $data) {
      // ensure A exists on B at least
      if (array_key_exists($project, $destination_system) ) {
        $destination_system[$project]->type = 'found';
        // now check for status
        if ($data->status != $destination_system[$project]->status) {
          // this means source is on, destination is off
          if ($data->status == 1) {
            $drush['dis'][$project] = $project;
          }
          else {
            $drush['en'][$project] = $project;
          }
        }
      }
      else {
        // now we know we need to download something
        $drush['dl'][$project] = $project;
      }
    }
    // test for destination having modules not originally in source
    foreach ($destination_system as $project => $data) {
      // find things we didn't find previously
      if ($data->type != 'found') {
        $drush['dl'][$project] = $project;
        // if enabled then let's mark that it needs enabled
        if ($data->status) {
          $drush['en'][$project] = $project;
        }
      }
    }
  }
  // see if we shold export variables differences
  if (in_array('variables', $components)) {
    // do a variable comparison
    $source_vars = _drush_recipes_load_db_table($source_settings, 'variable', 'name');
    $destination_vars = _drush_recipes_load_db_table($destination_settings, 'variable', 'name');
    // compare the source with the destination
    foreach ($source_vars as $name => $data) {
      // ensure variable A exists on B
      if (array_key_exists($name, $destination_vars) ) {
        $destination_vars[$name]->name = 'found';
        // now check for status
        if ($data->value != $destination_vars[$name]->value) {
          // this means source is different from destination
          $drush['vset'][$name] = $destination_vars[$name]->value;
        }
      }
      else {
        // now we know we need to delete this variable
        $drush['vdel'][$name] = $name;
      }
    }
    // test for destination having variables not originally in source
    foreach ($destination_vars as $name => $data) {
      // find things we didn't find previously
      if ($data->name != 'found') {
        $drush['vset'][$name] = $data->value;
      }
    }
  }
  // see if we shold export role / permission differences
  if (in_array('roles', $components)) {
    // compare permissions and roles
    // load up the source db / roles / permissions
    if ($source_settings['#name'] == 'none') {
      $source_roles = array();
      $source_perms = array();
    }
    else {
      _drush_recipes_db_set_active($source_settings);
      drupal_static_reset('user_role_permissions');
      $source_roles = user_roles();
      $source_perms = user_role_permissions($source_roles);
    }
    // load up the destination db / roles / permissions
    _drush_recipes_db_set_active($destination_settings);
    drupal_static_reset('user_role_permissions');
    $destination_roles = user_roles();
    $destination_perms = user_role_permissions($destination_roles);
    // return to default just to be safe
    db_set_active();

    // comparison, this can be a bit evil..
    foreach ($source_perms as $rid => $permissions) {
      // ensure variable A exists on B
      if (array_key_exists($rid, $destination_perms) ) {
        // dig deeper into permissions arrays
        foreach ($permissions as $permission => $bool) {
          // check that a permission is set
          if (array_key_exists($permission, $destination_perms[$rid]) ) {
            // store the fact that we found this role in some fashion
            $destination_perms[$rid][$permission] = 'found';
          }
          else {
            // this means destination DOES NOT have a perm in source
            $drush['rmp'][$destination_roles[$rid]][$permission] = TRUE;
          }
        }
        $destination_perms[$rid]['_drush_found'] = 'found';
        // test for destination having permissions not originally in source
        foreach ($destination_perms[$rid] as $permission => $bool) {
          // find things we didn't find previously
          if ($bool != 'found') {
            // a permission exists in destination but not source
            $drush['rap'][$destination_roles[$rid]][$permission] = TRUE;
          }
        }
      }
      else {
        // a role was deleted
        $drush['rdel'][$rid] = $rid;
      }
    }
    // test for destination having roles not originally in source
    foreach ($destination_perms as $rid => $permissions) {
      // find things we didn't find previously
      if (!isset($permissions['_drush_found'])) {
        // a role exists in destination that's not in source
        $drush['rcrt'][$destination_roles[$rid]] = $destination_roles[$rid];
        unset($permissions['_drush_found']);
        $drush['rap'][$destination_roles[$rid]] = $permissions;
      }
    }
  }
  // see if we shold export module differences
  if (in_array('features', $components) && function_exists('features_menu')) {
    // @todo do a features comparison (if applicable)
    // not entirely sure how this would work but seems possible
    // drush_features_diff();
  }

  // allow developers working w/ custom comparisons to jump in and do things
  // we may not immediately support in the core plugin; like custom tables
  // or contributed modules that are rare to see in the wild. You could also
  // use this in order to take out calls found above that you want to ignore.
  // Like if you were doing dev to prod target diffing and don't care about
  // permissions differences for the admin user role.
  drush_command_invoke_all_ref('drush_recipes_target_diff_drush_alter', $drush, $source_settings, $destination_settings);
  $calls = $end_calls = $role_calls = $perm_calls = array();
  // now we convert these into drush calls and feed it to its own recipe
  foreach ($drush as $call => $items) {
    switch ($call) {
      // set variables the long way
      case 'vset':
        // optional sanitization by profiler_builder
        if (module_exists('profiler_builder')) {
          $kill = _profiler_builder_ignore_list();
          // unset values we know should never transition
          foreach ($items as $name => $value) {
            if (in_array($name, $kill)) {
              unset($items[$name]);
            }
          }
        }
        else {
          drush_print(dt('While Profiler Builder is not required, it is highly recommended so that it can automatically sanitize variables you don\' want to ship around between builds (like cron keys).'));
          if (drush_confirm(dt('Would you like to run drush en profiler_builder now?'))) {
            drush_invoke_process(drush_get_context('DRUSH_TARGET_SITE_ALIAS'), 'en', array('profiler_builder'), array('y' => TRUE));
            drush_invoke_process(drush_get_context('DRUSH_TARGET_SITE_ALIAS'), 'cc', array('drush'), array('y' => TRUE));
            drush_print(dt('Run the command again, now with profiler builder able to process the output.'));
            return drush_user_abort();
          }
        }
        // loop through items and build variables with full set statements
        foreach ($items as $name => $value) {
          $val = unserialize($value);
          $calls[] = array(
            'command' => 'ev',
            'arguments' => array(
              '"variable_set(\"' . $name . '\", ' . var_export($val, TRUE) . ');"'
            )
          );
        }
      break;
      // delete variables
      case 'vdel':
        foreach ($items as $name => $value) {
          $calls[] = array(
            'command' => 'vdel',
            'arguments' => array(
              $name
            )
          );
        }
      break;
      // create roles
      case 'rcrt':
        // remove the built in roles
        unset($items['anonymous user']);
        unset($items['authenticated user']);
        foreach ($items as $rid => $name) {
          $role_calls[] = array(
            'command' => 'rcrt',
            'arguments' => array(
              "$rid",
              "$name" // only used in D8
            )
          );
        }
      break;
      // delete roles
      case 'rdel':
        foreach ($items as $rid) {
          $calls[] = array(
            'command' => 'rdel',
            'arguments' => array(
              $rid
            )
          );
        }
      break;
      // add permissions
      case 'rap':
        foreach ($items as $rid => $permissions) {
          foreach ($permissions as $permission => $bool) {
            $perm_calls[$rid . $permission] = array(
              'command' => 'rap',
              'arguments' => array(
                "$rid",
                "$permission"
              )
            );
          }
        }
      break;
      // remove permissions
      case 'rmp':
        foreach ($items as $rid => $permissions) {
          foreach ($permissions as $permission => $bool) {
            $calls[$rid . $permission] = array(
              'command' => 'rmp',
              'arguments' => array(
                "$rid",
                "$permission"
              )
            );
          }
        }
      break;
      // special developer case for things that should fire last
      case '_last':
        // these are special calls and are already formed and are added to
        // an array that will be added after everything is done
        foreach ($items as $item) {
          $end_calls[] = $item;
        }
      break;
      default:
        // need to shift call to the front
        array_unshift($items, $call);
        $calls[] = _drush_recipes_argument_to_target($items);
      break;
    }
  }
  // shift roles to end but before perms and _last at the end
  foreach ($role_calls as $rcall) {
    array_push($calls, $rcall);
  }
  foreach ($perm_calls as $pcall) {
    array_push($calls, $pcall);
  }
  foreach ($end_calls as $end) {
    array_push($calls, $end);
  }
  // insanely rare use case where we have an exact copy of a site..
  if (!empty($calls)) {
    ksort($calls);
    // allow for automatic applying of 1 thing to be the other
    if (drush_get_option('make-it-so', FALSE)) {
      // print what's about to happen to the screen
      _drush_drush_recipes_drush_write_recipe($calls, TRUE);
      // ask if they are super sure they want to do this since it is destructive
      if (drush_confirm(dt('Are you sure you want to apply the difference between @source and @destination? This means that @source will have the above recipe applied to it, effectively making it the same site as @destination.', array('@destination' => $destination, '@source' => $source)))) {
        drush_drush_recipes_drush_cook_recipes('', TRUE, array($calls));
        return dt('@source should now be largely the same as @destination!', array('@destination' => $destination, '@source' => $source));
      }
      else {
        return drush_user_abort();
      }
    }
    return _drush_drush_recipes_drush_write_recipe($calls, drush_get_option('test-run', FALSE));
  }
  else {
    drush_print(dt('The sites are exactly the same, most likely something went wrong unless you were testing if they are the same.'));
    return FALSE;
  }
}

/**
 * load table data from a source
 * @return array an array of database info
 */
function _drush_recipes_load_db_table($alias_settings, $table, $key, $fields = '*') {
  // skip out early if this isn't against a target
  if ($alias_settings['#name'] == 'none') {
    return array();
  }
  _drush_recipes_db_set_active($alias_settings);
  $ary = array();
  // selec the fields from the table and convert to an array of values
  $rsc = drush_db_select($table, $fields);
  while ($row = drush_db_fetch_object($rsc)) {
    $ary[$row->{$key}] = $row;
  }
  db_set_active();

  return $ary;
}

/**
 * set active db based on the settings of an alias
 */
function _drush_recipes_db_set_active($alias_settings) {
  // set the context to the alias in question
  drush_sitealias_set_alias_context($alias_settings);
  // get the database credentials from the alias
  sitealias_get_databases_from_record($alias_settings);
  // bootstrap to the max possible for this alias
  drush_bootstrap_max_to_sitealias($alias_settings);
  // @todo look into drush core sql-sync commands for how we might
  // be able to set an active db connection without needing to do
  // the Database:: object since it will fail
  // drush_sitealias_get_db_spec may also have the answer
  Database::addConnectionInfo($alias_settings['#name'], 'default', $alias_settings['databases']['default']['default']);
  db_set_active($alias_settings['#name']);
  return 1;
}

/**
 * Drush command callback for drush-recipes-url.
 */
function drush_drush_recipes_url($url = DRUSH_RECIPES_DEFAULT_URL) {
  //pseudo code for now til we build the service out
  $response = file_get_contents($url);
  $contents = utf8_encode($response);
  $recipexml = simplexml_load_string($contents);
  if (!$response->error) {
    $recipe_items = $recipexml->drush_recipe;
    foreach ($recipe_items as $recipes) {
      $recipes = (array) $recipes;
      $location = drush_prompt(dt('Location to write recipes'), drush_get_context('DRUSH_PER_USER_CONFIGURATION') . '/drecipes/_SERVICE-drush.recipes');
      // test directory exists / create it if we can
      if (is_dir("$location") || mkdir("$location")) {
        // loop through recipes that come across
        foreach ($recipes as $recipe) {
          $recipe = (array) $recipe;
          foreach ($recipe as $key => $item) {
            if (gettype($item) == 'object') {
              $recipe[$key] = (array) $item;
            }
            // account for deep nested recipes
            if ($key == 'recipe') {
              foreach ($item as $key2 => $item2) {
                if (gettype($item2) == 'object') {
                  $arytmp = (array) $item2;
                  // see if we need to mash this
                  if (count($arytmp) == 1) {
                    $str = array_pop($arytmp);
                    $recipe[$key][$key2] = explode(' ', $str);
                  }
                }
              }
            }
          }
          // need a file wrapper style call
          // usually these are loaded from the file system
          $objtmp = (object) array('name' => '', 'drecipe' => array());
          $objtmp->name = trim($recipe['machine_name']);
          $objtmp->drecipe = $recipe;
          _drush_recipes_recipe_to_drush($objtmp);
          if (drush_confirm("Are you sure you want to save the above recipe? (this will overwrite your local copy in that directory if its allowed)")) {
            // start writing to file if they selected that
            $file = trim($recipe['machine_name']) . '.' . DRUSH_RECIPE_EXTENSION;
            unset($recipe['machine_name']);
            // validate that this is an actual recipe format
            if (!_drush_recipes_validate_recipe($recipe)) {
              drush_log(dt('The returned recipe message was not a valid recipe, this has been ignored and will not be written to file.'), 'error');
            }
            else {
              // try to write recipe to the file
              $output = _drush_recipes_encode($recipe, 'json');
              if (!file_put_contents("$location/$file", $output)) {
                drush_log(dt("Unable to write file @file", array('@file' => $file)), 'error');
              }
              else {
                // success! tell them how to use this
                drush_log(dt("New recipe written to @file. call `drush cook @machine` to cook up this recipe.", array('@file' => "$location/$file", '@machine' => $machine_name)), 'ok');
              }
            }
          }
        }
      }
      else {
        drush_log(dt("Unable to write folder @location", array('@location' => $location)), 'error');
      }
    }
  }
  else {
    drush_log(dt("Unable to connect to @url", array('@url' => $url)), 'error');
  }
  return 1;
}
/**
 * Drush command callback for drush-write-recipe.
 */
function drush_drush_recipes_drush_write_recipe() {
  // dwr command has no arguments but we reuse the writing capabilities
  _drush_drush_recipes_drush_write_recipe();
}

/**
 * Helper to write recipe to file
 */
function _drush_drush_recipes_drush_write_recipe($items = NULL, $test_run = FALSE) {
  // allow for test runs for debugging other functions and copy / paste ease
  if (!$test_run) {
    $machine_name = drush_prompt(dt('Enter a machine name'));
    //get the first character of machine name and check if it is a number
    $first_char_machine_name = substr($machine_name, 0, 1);
    if (!ctype_alpha($first_char_machine_name)){
      //echo that input cannot start with a number.
      drush_log('Syntax Error: Please enter a machine name that does not start with a number.', 'error');
      // we return to effectively start a recursive loop but cancel out this one.
      return drush_drush_recipes_drush_write_recipe();
    }
    else {
      $original_machine = $machine_name;
      $machine_name = strtolower($machine_name);
      // check for spaces and replace with underscores.
      $machine_name = preg_replace("/[^a-z0-9_]/" , '_', $machine_name);
      // verify that user wants the converted string; if not start over.
      if (($original_machine != $machine_name) && !drush_confirm(dt('Is @machine the machine name you want?', array('@machine' => $machine_name)))) {
        return drush_drush_recipes_drush_write_recipe();
      }
    }
    $name = drush_prompt(dt('Enter recipe name'));
    // description, version, weight and core are optional
    $description = drush_prompt(dt('Enter a description'), NULL, FALSE);
    $version = drush_prompt(dt('Enter version'), '1.0');
    $weight = drush_prompt(dt('Weight'), '0', FALSE);
    // description and version are optional
    if (!$major_version = drush_drupal_major_version()) {
      $major_version = DRUSH_RECIPES_CORE_COMPATIBILITY;
    }
    $core = drush_prompt(dt('Drupal core'), $major_version);
    if (drush_get_option('for-drup', FALSE)) {
      $type = 'upgrade';
    }
    else {
      $recipe_types = array(
        1 => 'add-on',
        2 => 'routine',
        3 => 'utility',
      );
      // prompt for the user with the default option
      while (!$type = drush_choice_with_custom_defaults($recipe_types, 'add-on', dt('What type of recipe is this?'), '!value'));
    }
    // author is optional
    $author = drush_prompt(dt('Recipe author'), NULL, FALSE);
  }
  else {
    $machine_name = 'test_run';
    $name = 'Test run';
    $description = 'This is a test run';
    $version = '0.0';
    $weight = '0';
    $core = 'test';
    $type = 'test';
    $author = 'test';
  }
  $call = '';
  if (empty($items)) {
    while ($call != 'x') {
      $call = drush_prompt(dt('Write the full drush command you want to add (c for conditional, x when done)'));
      // if we didn't get told to stop
      if ($call != 'x') {
        // check for conditional vs complex so we can write these in via the write
        // command
        $item = explode(' ', $call);
        // this means its a reference to an another drecipe
        if (count($item) == 1 && strpos($item[0], '.' . DRUSH_RECIPE_EXTENSION)) {
          $item = (string)$item[0];
        }
        // support referencing make files which we shorthand to a drush call
        else if (count($item) == 1 && strpos($item[0], '.make')) {
          $item = array(
            'command' => 'make',
            'arguments' => array(str_replace('.make', '', $item[0])),
          );
        }
        // support conditionals
        else if (count($item) == 1 && strpos($item[0], 'c') === 0) {
          $conditions = array();
          $condkey = 0;
          while ($condinput != 'x') {
            $condinput = drush_prompt(dt('CONDITIONAL: Add a drush recipe to add to this conditional (type x when done)'));
            // if we didn't get told to stop and we got a recipe looking entry
            if ($condinput != 'x' && strpos($condinput, '.' . DRUSH_RECIPE_EXTENSION)) {
              // this helps ensure conditions are written starting with key 1
              // can help avoid conflicts with drush options later on
              $condkey++;
              $conditions[$condkey] = (string)$condinput;
            }
            else if ($condinput == 'x') {
              drush_log(dt('Conditional complete'), 'ok');
            }
            else {
              // ignore input as it wasn't something we understood
              drush_log(dt('Invalid conditional, recipe references only'), 'warning');
              continue;
            }
          }
          // account for no input in case of a mistake
          if (empty($conditions)) {
            continue;
          }
          // add grouping of conditions to the array
          $item = array(
            DRUSH_RECIPES_FORMAT_CONDITIONAL => $conditions,
            DRUSH_RECIPES_FORMAT_CONDITIONAL_QUESTION => drush_prompt(dt("What question are you asking for this conditional?"), 'Which would you like to run?'),
          );
        }
        // easiest case
        else if ($item[0] == 'drush') {
          array_shift($item);
          $item = _drush_recipes_argument_to_target($item);
        }
        else {
          // ignore input as it wasn't something we understood
          drush_log(dt('Invalid command'), 'warning');
          continue;
        }
        // add to array
        $items[] = $item;
      }
    }
  }
  // assemble the recipe
  $recipe = array(
    'name' => $name,
    'drush_recipes_api' => DRUSH_RECIPES_API_VERSION,
    'weight' => $weight,
    'core' => $core,
    'recipe' => $items,
    'metadata' => array(
      'type' => $type,
      'version' => $version,
    )
  );
  // ensure that author and description aren't set to null
  if (!is_null($author)) {
    $recipe['metadata']['author'] = $author;
  }
  if (!is_null($description)) {
    $recipe['metadata']['description'] = $description;
  }

  $formats = array(
    'json' => 'json',
    'xml' => 'xml'
  );
  // test for yaml since we support that format too
  if (function_exists('yaml_emit')) {
    // allow for writing to file or screen
    $formats['yaml'] = 'yaml';
  }
  if (!$test_run) {
    while (!$format = drush_choice_with_custom_defaults($formats, 'json', dt('Which recipe encoding?'), '!value'));
  }
  else {
    $format = 'json';
  }
  // allow for writing to file or screen
  $output_locations = array(
    1 => 'write to file',
    2 => 'print',
  );
  // start writing to file if they selected that
  if (!$test_run && drush_choice_with_custom_defaults($output_locations, 'write to file', dt('Write to file or print to screen?')) === 'write to file') {
    // allow for-drup flag to auto append timestamp
    if (drush_get_option('for-drup', FALSE)) {
      $machine_name .= '_' . time();
    }
    $file = $machine_name . '.' . DRUSH_RECIPE_EXTENSION;
    $location = drush_prompt(dt('Location to write recipe'), drush_get_context('DRUSH_PER_USER_CONFIGURATION') . '/drecipes');
    // test directory exists / create it if we can
    if (is_dir("$location") || mkdir("$location")) {
      // try to write recipe to the file
      $output = _drush_recipes_encode($recipe, $format);
      if (!file_put_contents("$location/$file", $output)) {
        drush_log(dt("Unable to write file @file", array('@file' => $file)), 'error');
        drush_print(_drush_recipes_encode($recipe, $format));
      }
      else {
        // success! tell them how to use this
        drush_log(dt("New recipe written to @file. call `drush cook @machine` to cook up this recipe.", array('@file' => "$location/$file", '@machine' => $machine_name)), 'ok');
      }
    }
    else {
      drush_log(dt("Unable to write folder @location", array('@location' => $location)), 'error');
      drush_print(_drush_recipes_encode($recipe, $format));
    }
  }
  else {
    // just write it to the screen though this is mostly just for debugging
    drush_print(_drush_recipes_encode($recipe, $format));
  }
  return TRUE;
}

/**
 * Drush command callback for drush-list-recipes.
 */
function drush_drush_recipes_drush_list_recipes($list = '') {
  $recipes = _drush_recipes_system_rebuild_recipe_data();
  $list = (!empty($list) ? explode(',', $list) : '');
  $rows = array();
  // get option flag for more detail
  $more = drush_get_option('more-detail');
  // make sure we find any
  if (empty($recipes)) {
    drush_log(dt('You have no recipes! Run `drush dwr` to create a new one!'), 'error');
    return FALSE;
  }
  $header = $rows = array();
  // format recipe data as a table array
  foreach ($recipes as $machine_name => $recipe) {
    $row = $recipe->drecipe;
    // clean up data for output
    if ($more) {
      $row['dependencies'] = implode(' ', $row['dependencies']);
      $row['conflicts'] = implode(' ', $row['conflicts']);
      $row['recipe'] = implode("\n", _drush_recipes_recipe_to_drush($row), 0, FALSE, FALSE);
      $row['metadata'] = implode(' ', $row['metadata']);
    }
    else {
      unset($row['dependencies']);
      unset($row['conflicts']);
      unset($row['recipe']);
      unset($row['metadata']);
      unset($row['core']);
      unset($row['drush_recipes_api']);
      unset($row['weight']);
      unset($row['env']);
    }
    $row['machine_name'] = $machine_name;
    $row['uri'] = $recipe->filename;
    // allow for limiting what they care about from commandline
    if (!empty($list) && !in_array($machine_name, $list)) {
      continue;
    }
    $rows[] = $row;
  }
  if (empty($rows)) {
    drush_log(dt('No results matched the list you wanted to see'), 'error');
    return FALSE;
  }
  array_unshift($rows, array_keys($row));
  // pretty print the columns
  if ($more) {
    $widths = array(
      'uri' => '30',
      'machine_name' => '8',
      'name' => '10',
      'conflicts' => '10',
      'core' => '3',
      'drush_recipes_api' => '3',
      'metadata' => '30',
      'recipe' => '40',
      'dependencies' => '10',
      'weight' => '2',
      'env' => '10',
    );
  }
  else {
    $widths = array();
  }
  drush_print_table($rows, TRUE, $widths);
}

/**
 * Drush command callback for drush-cook-recipes.
 */
function drush_drush_recipes_drush_cook_recipes($list = '', $recurse = FALSE, $recipe_list = array()) {
  if (empty($recipe_list)) {
    $commands = array();
    $list = explode(',', $list);
    if (empty($list)) {
      drush_log('You must specify recipes to cook! try running drush dlr for a listing of commands to cook.', 'error');
      return FALSE;
    }
    // allow projects to alter the list
    drush_command_invoke_all_ref('drush_recipes_pre_cook_alter', $list, $recurse);

    $recipes = _drush_recipes_system_rebuild_recipe_data();
    $cook = array_intersect_key($recipes, array_flip($list));
    if (empty($cook)) {
      // it's not in this system, let's test it for a local path
      if (file_exists($list[0])) {
        $cook[0] = array(
          'name' => dt('local file'),
          'drecipe' => array(),
        );
        $cook[0] = (object) $cook[0];
        $cook[0]->drecipe = _drush_recipes_load_recipe($list[0]);
      }
      else if (filter_var($list[0], FILTER_VALIDATE_URL)) {
        $cook[0] = array(
          'name' => dt('remote file'),
          'drecipe' => array(),
        );
        $cook[0] = (object) $cook[0];
        // load file from remote location
        $url = basename(current(explode('?', $list[0], 2)));
        $destination = drush_get_context('DRUSH_PER_USER_CONFIGURATION') .'/drecipes/' . basename($url);
        $file = drush_download_file($list[0], $destination);
        $cook[0]->drecipe = _drush_recipes_load_recipe($file);
      }
      else {
        drush_log('The recipes you have specified don\'t exist, try running drush dlr for a listing of available commands or use --dr-locations to include a location that might have the recipe you just tried to cook.', 'error');
        return FALSE;
      }
    }
    // validate recipes we are going to cook are valid recipe formatted items
    foreach ($cook as $recipe) {
      if (!_drush_recipes_validate_recipe($recipe->drecipe)) {
        // this wasn't a valid format
        return drush_user_abort();
      }
    }
    $dependencies = $conflicts = $weight = array();
    // ensure that they are listed based on weight to form a block chain
    foreach ($cook as $key => $recipe) {
      $weight[$key]  = $recipe->drecipe['weight'];
      $dependencies = array_merge($dependencies,(isset($recipe->drecipe['dependencies']) ? $recipe->drecipe['dependencies'] : array()));
      $conflicts = array_merge($conflicts,(isset($recipe->drecipe['conflicts']) ? $recipe->drecipe['conflicts'] : array()));
    }
    // Sort the data with weight descending
    array_multisort($weight, SORT_ASC, $cook);
    // test for conflicts
    foreach ($conflicts as $conflict) {
      foreach ($cook as $recipe) {
        if ($recipe->name == $conflict) {
          drush_log(dt('Recipes could not be run, @name is listed as a known conflict of one of the included recipes. Review the conflict and try again.', array('@name' => $recipe->name)), 'error');
          return drush_user_abort();
        }
      }
    }
    // allow for developers to ignore dependencies, useful in debugging
    if (!drush_get_option('dr-skip-checks', FALSE)) {
      // ensure dependencies are met
      $notmet = array();
      // build a list of what plugins supply what commands
      $commandlist = drush_get_commands();
      foreach ($commandlist as $command) {
        $drush_projects[] = $command['commandfile'];
      }
      foreach ($dependencies as $dependency) {
        if (drush_is_command($dependency) || in_array($dependency, $drush_projects) || (function_exists('module_exists') && module_exists($dependency)) || (function_exists('module_exists') && $dependency == '@site')) {
          // do nothing, this command exists in some fashion
        }
        else {
          // if we require a working site and didn't get one fail immediately
          if ($dependency == '@site') {
            drush_print(dt('This requires a working drupal site to function!'));
            return drush_user_abort();
          }
          else {
            $notmet[] = $dependency;
          }
        }
      }
      // if anything has failed then we need to tell the user why it didn't run
      if (!empty($notmet)) {
        drush_log(dt("Recipes could not be cooked because the following dependencies have not been met:\n@name\nTry:\ndrush dl @dls\n\nOr did you maybe mean to run this against a site target?", array('@name' => implode("\n", $notmet), '@dls' => implode(',', $notmet))), 'error');
        return drush_user_abort();
      }
    }

    // convert cooking list into commands to run
    drush_print("\n" . dt('Ingredients list to cook: @list', array('@list' => implode(',', $list))));
    $envs = array();
    // see if we got passed a recipe list ahead of time
    foreach ($cook as $recipe) {
      $recipe_list[] = _drush_recipes_recipe_to_drush($recipe);
      // build environment registry if one exists
      if (isset($recipe->drecipe['env']) && !empty($recipe->drecipe['env'])) {
        $envs[] = $recipe->drecipe['env'];
      }
    }
  }
  // confirm cooking as this can be a ton of drush commands
  if ($recurse || drush_confirm('Are you sure you want to cook these recipes with the above call structure? ' . implode(' ', array_keys($cook)))) {
    $env_tokens = array();
    // pull in the context of the operation
    $context = drush_get_context();
    // loop through environmental tokens requesting input from the user
    foreach ($envs as $env) {
      // only pass through tokens if its actually set, this opens the door
      // for future functionality to be packed into the env settings bin
      if (isset($env['tokens'])) {
        foreach ($env['tokens'] as $token => $description) {
          $default = $context_env = NULL;
          $default_set = FALSE;
          $prompt = FALSE;
          // assemble the actual token from the options that we would see
          $strip_token = str_replace('[', '', str_replace(']', '', $token));
          // check the larger context, then trickle down to local scope
          if (isset($context['cli']['env-' . $strip_token])) {
            $context_env = $context['cli']['env-' . $strip_token];
          }
          // check for option at commandline, this overrides empty AND default values
          // this means you can cook a recipe with these values downsteam by supplying
          // the option at run time: drush cook recipe --env-token=value
          $default = drush_get_option('env-' . $strip_token, $context_env);
          // use the env-token style so long as its not NULL
          if ($default !== NULL) {
            // in this instance we just use the default value because it's an
            // environmental setting and if it was supplied via cli / option
            // then we don't question otherwise (this is the point of a global)
            $env_tokens['env-' . $strip_token] = $default;
          }
          else if (isset($env['defaults'][$token])) {
            // we have a defined default but it wasn't manually entered, prompt
            $default = $env['defaults'][$token];
            // stupid but this allows for NULL string setting as the default case
            $default_set = TRUE;
            $prompt = TRUE;
          }
          else {
            $prompt = TRUE;
          }
          // no default supplied, prompt for input
          if ($prompt) {
            // prompt for input, only requiring it if a default is not set
            $env_tokens['env-' . $strip_token] = drush_prompt(dt('ENV token @token: @description', array('@token' => $strip_token, '@description' => $description)), $default, ($default_set ? FALSE : TRUE));
          }
          // set this option so that it can be passed down / checked later
          drush_set_option('env-' . $strip_token, $env_tokens['env-' . $strip_token]);
        }
      }
    }
    // to use this we'll do something like the name has to be global-token
    // this would allow for definition either at runtime via mlt-global-token
    // (which would just populate the global token call and skip it) or in
    // the new global token area
    foreach ($recipe_list as $commands) {
      foreach ($commands as $command) {
        if (is_array($command)) {
          // evil time, let's support looping ingredient statements
          $command['loop_pos'] = 1;
          $finished = FALSE;
          if (isset($command['loop'])) {
            // 'x' means that we loop and allow user to keep doing it!
            if ($command['loop'] == 'x') {
              // do nothing we want this to let them keep running it
            }
            else if (is_int( (int) $command['loop'])) {
              $command['loop'] = (int) $command['loop'];
            }
            else {
              drush_print('Loop value invalid, skipping capability', 'warning');
            }
          }
          // support for looping each ingredient if requested
          while (!$finished) {
            if (isset($command[DRUSH_RECIPES_FORMAT_MADLIB])) {
              // allow for super simple uncooking of recipe
              if (drush_get_option('simple-uncook')) {
                _drush_recipes_simple_uncook($command['command']);
              }
              // allow for generic overriding of this command
              drush_command_invoke_all_ref('drush_recipes_command_invoke_alter', $command, DRUSH_RECIPES_FORMAT_MADLIB);
              // allow for targetted type overriding
              drush_command_invoke_all_ref('drush_recipes_' . DRUSH_RECIPES_FORMAT_MADLIB . '_command_invoke_alter', $command);
              // ensure defaults are set for command object
              _drush_recipes_command_defaults($command);
              $option_out = '';
              foreach ($command['options'] as $key => $val) {
                $option_out .= ' --' . $key . '=' . $val;
              }
              drush_log(dt('Adding Madlib ingredient: drush ') . $command['target'] . ' ' . $command['command'] . ' ' . implode(' ', $command['arguments']) . ' ' . $option_out, 'ok');
              // special exception for commands that run batch jobs as they will
              // exit into the background process silently
              if (!in_array($command['command'], _drush_recipes_require_shell_exec())) {
                drush_invoke_process($command['target'], $command['command'], $command['arguments'], $command['options']);
              }
              else {
                // this is the simple method for running when non interactive
                $smash_command = 'drush ' . $command['target'] . ' ' . $command['command'] . ' ' . implode(' ', $command['arguments']) . ' ' . $option_out;
                drush_print($smash_command);
                drush_shell_exec($smash_command);
                $shell_output = drush_shell_exec_output();
                foreach ($shell_output as $shell) {
                  drush_print($shell);
                }
              }
            }
            else if (isset($command[DRUSH_RECIPES_FORMAT_TARGET])) {
              // allow for super simple uncooking of recipe
              if (drush_get_option('simple-uncook')) {
                _drush_recipes_simple_uncook($command['command']);
              }
              // allow for generic overriding of this command
              drush_command_invoke_all_ref('drush_recipes_command_invoke_alter', $command, DRUSH_RECIPES_FORMAT_TARGET);
              // allow for targetted type overriding
              drush_command_invoke_all_ref('drush_recipes_' . DRUSH_RECIPES_FORMAT_TARGET . '_command_invoke_alter', $command);
              // ensure defaults are set for command object
              _drush_recipes_command_defaults($command);
              $option_out = '';
              foreach ($command['options'] as $key => $val) {
                $option_out .= ' --' . $key . '=' . $val;
              }
              drush_log(dt('Adding ingredient: drush ') . $command['target'] . ' ' . $command['command'] . ' ' . implode(' ', $command['arguments']) . ' ' . $option_out, 'ok');
              // special exception for commands that run batch jobs as they will
              // exit into the background process silently
              if (!in_array($command['command'], _drush_recipes_require_shell_exec())) {
                drush_invoke_process($command['target'], $command['command'], $command['arguments'], $command['options']);
              }
              else {
                // this is the simple method for running when non interactive
                $smash_command = 'drush ' . $command['target'] . ' ' . $command['command'] . ' ' . implode(' ', $command['arguments']) . ' ' . $option_out;
                drush_print($smash_command);
                drush_shell_exec($smash_command);
                $shell_output = drush_shell_exec_output();
                foreach ($shell_output as $shell) {
                  drush_print($shell);
                }
              }
            }
            else if (isset($command[DRUSH_RECIPES_FORMAT_CONDITIONAL])) {
              $default = FALSE;
              // check for a default case which allows us to pass --y successfully
              if (isset($command[DRUSH_RECIPES_FORMAT_CONDITIONAL]['default'])) {
                $default = $command[DRUSH_RECIPES_FORMAT_CONDITIONAL]['default'];
              }
              // allow for this to be defined as an optional conditional
              if (isset($command['optional']) && $command['optional']) {
                // if we don't have a default, make none the default
                if (!$default) {
                  $default = '-none-';
                }
                $command[DRUSH_RECIPES_FORMAT_CONDITIONAL][] = '-none-';
              }
              while (!$which = drush_choice_with_custom_defaults($command[DRUSH_RECIPES_FORMAT_CONDITIONAL], $default, $command[DRUSH_RECIPES_FORMAT_CONDITIONAL_QUESTION]));
              drush_print($which);
              // @todo fix inconsistent return data from drush_choice_with_custom_defaults
              if (isset($command[DRUSH_RECIPES_FORMAT_CONDITIONAL][$which])) {
                $which = $command[DRUSH_RECIPES_FORMAT_CONDITIONAL][$which];
              }
              // see if they chose to skip an optional recipe
              if ($which == '-none-') {
                drush_log(dt('Skipping optional ingredient'), 'ok');
              }
              else {
                drush_log(dt('Adding ingredient: ') . $which, 'ok');
                // recursive since they just selected a reference
                drush_drush_recipes_drush_cook_recipes(str_replace('.' . DRUSH_RECIPE_EXTENSION, '', $which), TRUE);
              }
            }
            // allow for custom format or else assume argument based
            else if (isset($call['_drush_recipes_custom_format'])) {
              // allow for generic overriding of this command
              drush_command_invoke_all_ref('drush_recipes_command_invoke_alter', $command, $call['_drush_recipes_custom_format']);
              // we put faith in the developer to know why they just did
              // this but it will allow for custom call structures beyond those
              // provided by the base plugin
              drush_command_invoke_all_ref('drush_recipes_' . $call['_drush_recipes_custom_format'] . '_command_invoke_alter', $command);
            }
            // should we stop looping?
            if ($command['loop'] == 'x') {
                $answers = array('nope', 'again');
                while (!$answer = drush_choice_with_custom_defaults($answers, 'nope', dt('Run this ingredient again?'), '!value'));
                if ($answer == 'nope') {
                  $finished = TRUE;
                }
            }
            else if ($command['loop_pos'] < $command['loop']) {
              $command['loop_pos']++;
            }
            else {
              $finished = TRUE;
            }
          }
        }
        else {
          // allow for super simple uncooking of commands
          if (drush_get_option('simple-uncook')) {
            $tmp = explode(' ', $command);
            _drush_recipes_simple_uncook($tmp[1]);
            $command = implode(' ', $tmp);
          }
          $command .= ' --y';
          drush_log('Adding ingredient: ' . $command, 'ok');
          // allow for generic overriding of this command
          drush_command_invoke_all_ref('drush_recipes_command_invoke_alter', $command, DRUSH_RECIPES_FORMAT_ARGUMENT);
          // allow for targetted type overriding
          drush_command_invoke_all_ref('drush_recipes_' . DRUSH_RECIPES_FORMAT_ARGUMENT . '_command_invoke_alter', $command);
          // this is the simple method for running when non interactive
          drush_shell_exec($command);
          $shell_output = drush_shell_exec_output();
          foreach ($shell_output as $shell) {
            drush_print($shell);
          }
        }
      }
    }
  }
  else {
    return drush_user_abort();
  }
  // allow projects to react after cooking
  drush_command_invoke_all_ref('drush_recipes_post_cook_alter', $list, $recurse);
}

/**
 * Helper function to list commands that require exec in order to finish
 * @return array  drush commands that require shell to run correctly.
 */
function _drush_recipes_require_shell_exec() {
  // core commands with known issues
  $exec = array(
    'php-eval',
    'eval',
    'ev',
    'updb',
    'updatedb'
  );
  // hook for commands that require background execution
  drush_command_invoke_all_ref('drush_recipes_require_shell_exec_alter', $exec);
  return $exec;
}

/**
 * Implements hook_drush_recipes_require_shell_exec_alter().
 * @param  array $exec drush commands that require shell to run correctly.
 */
function drush_recipes_drush_recipes_require_shell_exec_alter(&$exec) {
  // contrib commands I know that have issues otherwise
  // these require batch processing which fails if interactive
  $exec[] = 'httprl-self-spider';
  $exec[] = 'hss';
  $exec[] = 'httprl-self-request';
  $exec[] = 'hsr';
  $exec[] = 'entitycache-load';
  $exec[] = 'ecl';
}

/**
 * Ensure that defaults are set for the command object
 * @param  array $command The command about to be executed
 */
function _drush_recipes_command_defaults(&$command) {
  // ensure process invoking won't fail
  if (!isset($command['target'])) {
    $command['target'] = drush_get_context('DRUSH_TARGET_SITE_ALIAS');
  }
  // if no target is set we should utilize @self
  if (empty($command['target'])) {
    $command['target'] = '@self';
  }
  if (!isset($command['arguments'])) {
    $command['arguments'] = array();
  }
  if (!isset($command['options'])) {
    $command['options'] = array();
  }
  // these are the options that we support passing down
  $options = array(
    'uri' => 'l',
    'root' => 'r',
    'verbose' => 'v',
    'debug' => 'd',
    'yes' => 'y',
    'no' => 'n',
    'simulate' => 's',
    'pipe' => 'p',
    'interactive' => 'ia',
  );
  // test if these are set as options globally
  foreach ($options as $key => $short) {
    if (($val = drush_get_option($key, NULL)) !== NULL && !isset($command['options'][$key])) {
      $command['options'][$key] = $val;
    }
    if (($val = drush_get_option($short, NULL)) !== NULL && !isset($command['options'][$short])) {
      $command['options'][$short] = $val;
    }
  }
  // pull in the context of the operation
  $context = drush_get_context();
  // test for madlib tokens which should be passed downward so that future
  // defaults in the block-chain are inherited from parent calls
  foreach ($context['cli'] as $key => $val) {
    if (strpos($key, 'mlt-') === 0 || strpos($key, 'looping-mlt-') === 0) {
      $command['options'][$key] = $val;
      // mlt is outside of the traditional global optionset, turn strict off
      $command['options']['strict'] = 0;
    }
  }

  // to get the appropriate root/uri
  // this can be missed in the event that a command calls for two aliases
  // such as a ddt command which wants to execute the command against the
  // first target but drush pulls the options from the 2nd, effectively
  // making the command compare A to B but then always applying the command
  // to B and A was the intended target.
  // This is required to allow the --make-it-so option flag on ddt function
  // correctly, but would potentially trip up other complex calls; hence this
  // windy explaination
  if (in_array($context['arguments'][0], array('drush-diff-targets-recipe', 'ddt')) && drush_get_option('make-it-so', FALSE)) {
    if (isset($context['site-aliases'][$command['target']])) {
      if (isset($context['site-aliases'][$command['target']]['root'])) {
        unset($command['options']['r']);
        $command['options']['root'] = $context['site-aliases'][$command['target']]['root'];
      }
      if (isset($context['site-aliases'][$command['target']]['uri'])) {
        unset($command['options']['l']);
        $command['options']['uri'] = $context['site-aliases'][$command['target']]['uri'];
      }
    }
  }
}

/**
 * Take a command and convert it to its inverse command for simple uncooking
 * @param  string $command the drush command to perform uncooking on.
 * @return string          the new drush command to perform
 */
function _drush_recipes_simple_uncook(&$command) {
  // switch the easy cases
  switch ($command) {
    case 'pm-enable':
    case 'en':
      $command = 'dis';
    break;
    case 'variable-set':
    case 'vset':
      $command = 'vdel';
    break;
    case 'pm-disable':
    case 'dis':
      $command = 'en';
    break;
  }
}

/**
 * Helper to rebuild drecipe data
 *
 * This is similar to how core handles modules / themes but forked to provide
 * support for modules, themes, and "drecipes" directory structures.
 */
function _drush_recipes_system_rebuild_recipe_data() {
  // // we allow for this command to run regardless of site scope
  $bootstrap = drush_get_context('DRUSH_BOOTSTRAP_PHASE');
  if ($bootstrap != DRUSH_BOOTSTRAP_DRUSH) {
    // test for static cache of output
    $recipes = &drupal_static(__FUNCTION__);
    if (isset($recipes)) {
      return $recipes;
    }
    // find recipes in drush specific locations
    $locations = array(
      'drush-system',
      'drecipes',
      'themes',
      'modules',
    );
    $function_pattern = DRUPAL_PHP_FUNCTION_PATTERN;
  }
  else {
    // we can only check in the drush sub-system for recipes
    $locations = array(
      'drush-system',
    );
    $function_pattern = '[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*';
  }
  // see if the user has defined any additional locations at run time
  if ($dr_locations = drush_get_option('dr-locations', FALSE)) {
    // We have this set with --dr-locations on the cli
    $dr_locations = explode(',', $dr_locations);
    if (is_array($dr_locations)) {
      $locations = array_merge($locations, $dr_locations);
    }
    else {
      $locations[] = $dr_locations;
    }
  }
  // allow drushrc.php options to also be used
  if ($dr_locations = drush_get_option('dr_locations', FALSE)) {
    // We have this set in the drushrc.php file
    if (is_array($dr_locations)) {
      $locations = array_merge($locations, $dr_locations);
    }
    else {
      $locations[] = $dr_locations;
    }
  }

  // rare but check for environmental var
  if (isset($_ENV['DR_LOCATIONS'])) {
    if (is_array($_ENV['DR_LOCATIONS'])) {
      $locations = array_merge($locations, $_ENV['DR_LOCATIONS']);
    }
    else {
      $locations[] = $_ENV['DR_LOCATIONS'];
    }
  }
  // allow projects to inject their own locations
  drush_command_invoke_all_ref('drush_recipes_locations_alter', $locations);

  $recipes = array();
  // file preg_match pattern
  $pattern = '/^' . $function_pattern . '\.' . DRUSH_RECIPE_EXTENSION . '/';
  // loop through each directory and find recipes
  foreach ($locations as $directory) {
    // find recipes in the drecipes directory
    $recipes += _drush_recipes_drupal_system_listing($pattern, $directory, 'name', 0);
  }
  // Set defaults for recipes.
  $defaults = array(
    'drush_recipes_api' => DRUSH_RECIPES_API_VERSION,
    'weight' => 0,
    'core' => DRUSH_RECIPES_CORE_COMPATIBILITY,
    'dependencies' => array(),
    'conflicts' => array(),
    'recipe' => array(),
    'metadata' => array(),
    'env' => array(),
  );

  // Read recipe files for each module/theme/drecipes.
  foreach ($recipes as $key => $recipe) {
    // Look for the info file.
    $recipe->drecipe = _drush_recipes_load_recipe(dirname($recipe->filename) . '/' . $recipe->basename);
    // Skip $recipes that don't provide info or are malformed.
    if (empty($recipe->drecipe) || empty($recipe->drecipe['recipe'])) {
      unset($recipes[$key]);
      continue;
    }
    // Merge in defaults and save.
    $recipes[$key]->drecipe = $recipe->drecipe + $defaults;
    krsort($recipes[$key]->drecipe);
    // check for the lazy metadata property
    if (isset($recipes[$key]->drecipe['metadata']['lazy'])) {
      $recipes[$recipes[$key]->drecipe['metadata']['lazy']] = $recipes[$key];
    }
  }
  // allow last minute recipe data modification
  drush_command_invoke_all_ref('drush_recipes_system_recipe_data_alter', $recipes);
  return $recipes;
}

/**
 * Fork of drupal_system_listing to parse files
 * @param  [type]  $mask      [preg_match for file pattern matching]
 * @param  [type]  $directory [directory to search in]
 * @param  string  $key       [file key]
 * @param  integer $min_depth [depth into the directory to traverse]
 * @return [array]             [an array of objects relating to recipe files]
 */
function _drush_recipes_drupal_system_listing($mask, $directory, $key = 'name', $min_depth = 0) {
  $searchdir = array();
  $files = array();
  // drush based paths need to be discovered in a different manner
  if ($directory == 'drush-system') {
    $searchdir[] = drush_get_context('DRUSH_PER_USER_CONFIGURATION');
    $searchdir[] = drush_get_context('DRUSH_SITE_WIDE_CONFIGURATION');
    $searchdir[] = dirname(__FILE__) . '/..';
  }
  else if (!in_array($directory, array('drush-system', 'drecipes', 'themes', 'modules'))) {
    $searchdir[] = $directory;
  }
  else {
    $searchdir = array($directory);
    $profiles = array();
    // edge case where call is in a drupal directory but drupal isn't installed
    if (function_exists('drupal_get_profile')) {
      $profile = drupal_get_profile();
      // In case both profile directories contain the same extension, the actual
      // profile always has precedence.
      $profiles[] = $profile;
      foreach ($profiles as $profile) {
        if (file_exists("profiles/$profile/$directory")) {
          $searchdir[] = "profiles/$profile/$directory";
        }
      }
    }

    // Always search sites/all/* as well as the global directories.
    $searchdir[] = 'sites/all/' . $directory;
    $config = conf_path();
    if (file_exists("$config/$directory")) {
      $searchdir[] = "$config/$directory";
    }
  }
  foreach ($searchdir as $dir) {
    $files_to_add = drush_scan_directory($dir, $mask, array('.', '..', 'CVS'), 0, TRUE, $key, $min_depth);
    // Duplicate files found in later search directories take precedence over
    // earlier ones, so we want them to overwrite keys in our resulting
    // $files array.
    // The exception to this is if the later file is from a module or theme not
    // compatible with Drupal core. This may occur during upgrades of Drupal
    // core when new modules exist in core while older contrib modules with the
    // same name exist in a directory such as sites/all/modules/.
    foreach (array_intersect_key($files_to_add, $files) as $file_key => $file) {
      // If it has no drecipe file, then we just behave liberally and accept the
      // new resource on the list for merging.
      if (file_exists($recipe_file = dirname($file->filename) . '/' . $file->basename)) {
        // Get the .DRUSH_RECIPE_EXTENSION file for the module or theme this file belongs to.
        $recipe = _drush_recipes_load_recipe($recipe_file);
        // If the module or theme is incompatible with Drupal core, remove it
        // from the array for the current search directory, so it is not
        // overwritten when merged with the $files array.
        if (isset($recipe['core']) && $recipe['core'] != DRUSH_RECIPES_CORE_COMPATIBILITY) {
          unset($files_to_add[$file_key]);
        }
      }
    }
    $files = array_merge($files, $files_to_add);
  }

  return $files;
}

/**
 * Helper function to load a file.
 * @param  string  $path     path to a recipe to load
 * @param  boolean $validate whether this is part of validating the recipe spec
 * @return array decoded array from one of the formats listed.
 */
function _drush_recipes_load_recipe($path, $validate = FALSE) {
  // if we are attempting a validation we just want to try and load an item
  // back and assert that it is the same as what was passed in
  if ($validate) {
    $contents = $path;
  }
  else {
    // loading as usual, this is a recipe file
    $contents = file_get_contents($path);
    // ensure utf8 to avoid issues
    $contents = utf8_encode($contents);
  }
  // to avoid issues w/ format extension names we trickle down based on support
  $recipe = drush_json_decode($contents);
  // if empty, lets try a yaml parser
  if (empty($recipe) && function_exists('yaml_parse')) {
    // test for yaml capabilities
    $recipe = yaml_parse($contents);
  }
  // lets try xml as a last ditch
  if (empty($recipe)) {
    $recipe = simplexml_load_string($contents);
  }
  // if still empty now we have a REAL problem
  if (empty($recipe)) {
    // something went wrong, we couldn't read the file
    drush_log(dt('There is a problem with the recipe located at @file', array('@file' => $path)), 'error');
    return FALSE;
  }
  drush_command_invoke_all_ref('drush_recipes_after_recipe_loaded_alter', $recipe);
  return $recipe;
}

/**
 * Helper function to export to a certain format.
 *
 * @return array encoded contents for export.
 */
function _drush_recipes_encode($contents, $format = 'json') {
  // allow other advanced tweaks just prior to encoding
  drush_command_invoke_all_ref('drush_recipes_encode_alter', $contents, $format);
  switch ($format) {
    case 'json':
      return _drush_recipes_pretty_json(drush_json_encode($contents));
    break;
    case 'yaml':
      if (function_exists('yaml_emit')) {
        return yaml_emit($contents);
      }
    break;
    case 'xml':
      $xml = new SimpleXMLElement('<drush_recipe/>');
      _drush_recipes_array_to_xml($contents, $xml);
      return $xml->asXML();
    break;
  }
  return FALSE;
}

/**
 * Helper function to convert array to XML
 * @param  array $array any old array
 * @param  object $xml   SimpleXMLElement object type
 * @return object        returns a populated XML object with values from array
 */
function _drush_recipes_array_to_xml($array, &$xml) {
  foreach($array as $key => $value) {
    if(is_array($value)) {
      if(!is_numeric($key)){
        $subnode = $xml->addChild("$key");
        _drush_recipes_array_to_xml($value, $subnode);
      }
      else {
        _drush_recipes_array_to_xml($value, $xml);
      }
    }
    else {
      if(!is_numeric($key)){
        $xml->addChild("$key","$value");
      }
      else {
        $xml->addChild("num$key","$value");
      }
    }
  }
}

/**
 * convert a recipe array to drush calls
 * @param  array $recipe  a recipe file fully loaded with recipe array
 * @param  int   $indent  the level to indent / levels of recursion down
 * @param  bool  $recurse if the functionc all should be recursive
 * @param  bool  $list    if calls should be printed as they are found
 * @return array $drush   array of drush calls in order they should cook
 */
function _drush_recipes_recipe_to_drush($recipe, $indent = 1, $recurse = TRUE, $list = TRUE) {
  drush_command_invoke_all_ref('drush_recipes_to_drush_alter', $recipe);
  // catch to make sure we don't fall into a deep infinite loop of recursive calls
  if ($indent > DRUSH_RECIPES_MAX_RECURSION) {
    // tell people in the event they triggered this and are confused
    drush_log(dt('There is most likely a problem with your logic for this recipe series. It was about to make a call @num levels down in its referenced call logic, and prevented this from happening to avoid an infinite loop. If you know what you are doing, increase DRUSH_RECIPES_MAX_RECURSION. If you think the current value is too low, please file an issue in the issue queue.', array('@num' => DRUSH_RECIPES_MAX_RECURSION)), 'error');
    return array();
  }
  if ($list && $indent === 1) {
    drush_print(_drush_recipes_indent($indent) . '<' . $recipe->name . '>');
  }
  $drush = array();
  foreach ($recipe->drecipe['recipe'] as $call) {
    switch ($format = _drush_recipes_detect_format($call)) {
      // a recipe with a reference to another recipe
      case DRUSH_RECIPES_FORMAT_REFERENCE:
        // we have a recipe nested, lets look up how to build it and recurse
        // but only if told to do so, may just want to reference the command
        if ($recurse) {
          // pull data for full object, fortunately it's static cached
          $recipes = _drush_recipes_system_rebuild_recipe_data();
          // loop through items to cross reference with filename
          foreach ($recipes as $machine_name => $item) {
            // if call matches filename we recurse through that filename's recipe
            if ($machine_name == str_replace('.' . DRUSH_RECIPE_EXTENSION, '', $call)) {
              if ($list) {
                drush_print(_drush_recipes_indent($indent) . '<' . $machine_name . '>');
              }
              $drush += _drush_recipes_recipe_to_drush($item, $indent+1);
              if ($list) {
                drush_print(_drush_recipes_indent($indent) . '</' . $machine_name . '>');
              }
              continue;
            }
          }
        }
        else {
          $print = 'drush cook '  . str_replace('.' . DRUSH_RECIPE_EXTENSION, '', $call);
          if ($list) {
            drush_print(_drush_recipes_indent($indent) . $print);
          }
          $drush[] = array(
            'command' => 'cook',
            'arguments' => array(str_replace('.' . DRUSH_RECIPE_EXTENSION, '', $call)),
          );
        }
      break;
      case DRUSH_RECIPES_FORMAT_MADLIB:
        $drush[] = $call;
        // see if we should print nicely formatted debug stuff
        if ($list) {
          $print = 'MADLIB ';
          if (isset($call['loop'])) {
            if ($call['loop'] == 'x') {
              $loop = 'unlimited';
            }
            else {
              $loop = $call['loop'];
            }
            $print .= "LOOP ($loop) ";
          }
          $print .= ': drush';
          // target is optional and will inherit higher level context if not set
          if (isset($call['target']) && !empty($call['target'])) {
            $print .= ' ' . $call['target'];
          }
          // command is required
          $print .= ' ' . $call['command'];
          // args are optional
          if (isset($call['arguments']) && !empty($call['arguments'])) {
            $print .= ' ' . implode(' ', $call['arguments']);
          }
          // options are optional
          if (isset($call['options']) && !empty($call['options'])) {
            foreach ($call['options'] as $key => $value) {
              $print .= ' --' . $key . '=' . $value;
            }
          }
          // defaults
          if (isset($call['defaults']) && !empty($call['defaults'])) {
            $print .= "\n" . _drush_recipes_indent($indent+1) . dt('defaults: ');
            foreach ($call['defaults'] as $key => $val) {
              $default = drush_get_option('mlt-' . str_replace('[', '', str_replace(']', '', $key)));
              if ($default !== NULL) {
                $val = $default;
              }
              // make sure first option gets the dashes it needs
              $print .= "\n" . _drush_recipes_indent($indent+1) . ' ' . $key . ' => ' . $val;
            }
          }
          drush_print(_drush_recipes_indent($indent+1) . $print);
        }
      break;
      case DRUSH_RECIPES_FORMAT_TARGET:
        $drush[] = $call;
        // see if we should print nicely formatted debug stuff
        if ($list) {
          $print = '';
          if (isset($call['loop'])) {
            if ($call['loop'] == 'x') {
              $loop = 'unlimited';
            }
            else {
              $loop = $call['loop'];
            }
            $print .= "LOOP ($loop) : ";
          }
          $print .= 'drush';
          // target is optional and will inherit higher level context if not set
          if (isset($call['target']) && !empty($call['target'])) {
            $print .= ' ' . $call['target'];
          }
          // command is required
          $print .= ' ' . $call['command'];
          // args are optional
          if (isset($call['arguments']) && !empty($call['arguments'])) {
            $print .= ' ' . implode(' ', $call['arguments']);
          }
          // options are optional
          if (isset($call['options']) && !empty($call['options'])) {
            foreach ($call['options'] as $key => $value) {
              $print .= ' --' . $key . '=' . $value;
            }
          }
          drush_print(_drush_recipes_indent($indent+1) . $print);
        }
      break;
      case DRUSH_RECIPES_FORMAT_CONDITIONAL:
        $print = 'CONDITIONAL';
        // support optional conditional
        if (isset($call['optional']) && $call['optional']) {
          $print .= dt(' (optional)');
        }
        if (isset($call['loop'])) {
          if ($call['loop'] == 'x') {
            $loop = 'unlimited';
          }
          else {
            $loop = $call['loop'];
          }
          $print .= " LOOP ($loop)";
        }
        $print .= ' : drush';
        //  conditional is complex so processing has to happen at run time
        $drush[] = $call;
        if ($list) {
          $print .= implode(' OR ', $call[DRUSH_RECIPES_FORMAT_CONDITIONAL]);
          // communicate the default value if one is set
          if (isset($call[DRUSH_RECIPES_FORMAT_CONDITIONAL]['default'])) {
            $print = str_replace($call[DRUSH_RECIPES_FORMAT_CONDITIONAL]['default'], '(default) ' . $call[DRUSH_RECIPES_FORMAT_CONDITIONAL]['default'], $print);
          }
          drush_print(_drush_recipes_indent($indent+1) . $print);
        }
      break;
      case DRUSH_RECIPES_FORMAT_ARGUMENT:
        // we've effectively killed off this case at this point via the
        // functionality below that now tries to convert it into the target spec

        // see if we should print nicely formatted debug stuff
        if ($list) {
          drush_print(_drush_recipes_indent($indent+1) . 'drush ' . implode(' ', $call));
        }
        // convert the call to a target based call
        $new_call = _drush_recipes_argument_to_target($call);
        // add the new call into the array
        $drush[] = $new_call;
      break;
      default:
        // we didn't pass any of the known recipe specifications
        // this could be because you know what you are doing and are writing
        // your own drush recipes plugin. In the future we'll have an actual
        // plugin architecture but for now we just provide hook support
        drush_command_invoke_all_ref('drush_recipes_to_drush_command_format_alter', $drush, $call, $format, $list);
      break;
    }
  }
  if ($list && $indent === 1) {
    drush_print(_drush_recipes_indent($indent) . '</' . $recipe->name . ">\n");
  }
  return $drush;
}

/**
 * Helper for indenting
 */
function _drush_recipes_indent($count) {
  $output = '';
  $counter = 0;
  while ($counter < $count) {
    $output .= '  ';
    $counter++;
  }
  return $output;
}
/**
 * Print json nicely regardless of PHP version
 */
function _drush_recipes_pretty_json($json) {
  $result = '';
  $level = 0;
  $in_quotes = false;
  $in_escape = false;
  $ends_line_level = NULL;
  $json_length = strlen($json);
  for ($i = 0; $i < $json_length; $i++) {
    $char = $json[$i];
    $new_line_level = NULL;
    $post = "";
    if ($ends_line_level !== NULL) {
      $new_line_level = $ends_line_level;
      $ends_line_level = NULL;
    }
    if ($in_escape) {
      $in_escape = false;
    }
    else if ($char === '"') {
      $in_quotes = !$in_quotes;
    }
    else if (!$in_quotes) {
      switch ($char) {
        case '}':
        case ']':
          $level--;
          $ends_line_level = NULL;
          $new_line_level = $level;
        break;

        case '{':
        case '[':
          $level++;
        case ',':
          $ends_line_level = $level;
        break;

        case ':':
          $post = " ";
        break;

        case " ":
        case "\t":
        case "\n":
        case "\r":
          $char = "";
          $ends_line_level = $new_line_level;
          $new_line_level = NULL;
        break;
      }
    }
    else if ($char === '\\') {
      $in_escape = true;
    }

    if ($new_line_level !== NULL) {
        $result .= "\n".str_repeat("\t", $new_line_level);
    }
    $result .= $char . $post;
  }

  return $result;
}

/**
 * Detect the format of the call.
 */
function _drush_recipes_detect_format($call) {
  // hardest to easiest with exception of it not being an array
  if (!is_array($call)) {
    return DRUSH_RECIPES_FORMAT_REFERENCE;
  }
  else if (isset($call[DRUSH_RECIPES_FORMAT_MADLIB])) {
    return DRUSH_RECIPES_FORMAT_MADLIB;
  }
  else if (isset($call[DRUSH_RECIPES_FORMAT_TARGET])) {
    return DRUSH_RECIPES_FORMAT_TARGET;
  }
  else if (isset($call[DRUSH_RECIPES_FORMAT_CONDITIONAL])) {
    return DRUSH_RECIPES_FORMAT_CONDITIONAL;
  }
  // allow other developers to write their own formats
  drush_command_invoke_all_ref('drush_recipes_detect_format_alter', $call);
  if (isset($call['_drush_recipes_custom_format'])) {
    return $call['_drush_recipes_custom_format'];
  }
  // fallback case is that it's an array of arguments
  return DRUSH_RECIPES_FORMAT_ARGUMENT;
}

/**
 * Implements hook_drush_recipes_FORMAT_command_invoke_alter().
 */
function drush_recipes_drush_recipes_madlib_command_invoke_alter(&$command) {
  $selection = array();
  // allow for falling back if they make a mistake
  $original = $command;
  $print = 'drush ';
  // pull in the context of the operation
  $context = drush_get_context();
  // loop through tokens requesting input from the user
  foreach ($command['tokens'] as $token => $description) {
    $default = $context_mlt = NULL;
    $default_set = FALSE;
    // assemble the actual token from the options that we would see
    $strip_token = str_replace('[', '', str_replace(']', '', $token));
    // start by checking the larger context, then trickle down to local scope
    if (isset($context['cli']['mlt-' . $strip_token])) {
      $context_mlt = $context['cli']['mlt-' . $strip_token];
    }
    // now test for the looping context which has priority
    if (isset($context['cli']['looping-mlt-' . $strip_token])) {
      $context_mlt = $context['cli']['looping-mlt-' . $strip_token];
    }
    // if we have an environmental variable we skip the question and
    // assume the answer is the global value
    $env_default = drush_get_option('env-' . $strip_token);
    if (!is_null($env_default)) {
      $context_mlt = $env_default;
      if (!isset($command['_retry'])) {
        $selection[$token] = $context_mlt;
        continue;
      }
    }
    // check for option at commandline, this overrides empty AND default values
    // this means you can cook a recipe with these values downsteam by supplying
    // the option at run time: drush cook recipe --mlt-token=value
    $default = drush_get_option('mlt-' . $strip_token, $context_mlt);
    // support for looping if we are looping
    if (isset($command['loop']) && isset($command['loop_pos'])) {
      // if we only have 1 item then don't bother
      $tmp = drush_get_option('looping-mlt-' . $strip_token);
      if (!empty($tmp)) {
        $default_array = explode(',', $tmp);
        $default = $default_array[$command['loop_pos']-1];
        // AUTOMATIC SETTING BASED ON THE AVAILABLE OPTIONS IN THE LOOP!!!
        if ($command['loop'] == 'x' && drush_get_option('yes', FALSE)) {
          $command['loop'] = count($default_array);
        }
      }
    }
    // use the mlt-token style so long as its not NULL
    if ($default !== NULL) {
      $default_set = TRUE;
    }
    // see if we have a supplied default if the user is skipping through
    else if (isset($command['defaults'][$token])) {
      $default = $command['defaults'][$token];
      // stupid but this allows for NULL string setting as the default case
      $default_set = TRUE;
    }
    // prompt for input, only requiring it if a default is not set
    $selection[$token] = drush_prompt(dt($description), $default, ($default_set ? FALSE : TRUE));
  }
  // loop through each selected token and scan the target, command, arguments
  // and options (key | value) for matches. None of these are required
  // properties so test each one
  foreach ($selection as $token => $value) {
    // replace tokens we find in the target; rare
    if (isset($command['target'])) {
      $command['target'] = str_replace($token, $value, $command['target']);
    }
    // replace tokens we find in the command itself; also rare
    if (isset($command['command'])) {
      $command['command'] = str_replace($token, $value, $command['command']);
    }
    if (isset($command['arguments'])) {
      // loop through the arguments, these only can be matched on the value (arg)
      foreach ($command['arguments'] as $key => $arg) {
        $command['arguments'][$key] = str_replace($token, $value, $arg);
      }
    }
    if (isset($command['options'])) {
      // loop through the options; these can be match on the key OR value OR both
      foreach ($command['options'] as $key => $option) {
        // first the option value, this is the easy part
        $command['options'][$key] = str_replace($token, $value, $option);
        // now the key, a bit more tricky but doable
        $tmp = str_replace($token, $value, $key);
        // check that a replacement was made to the key and that $tmp isn't set
        if ($tmp != $key && !isset($command['options'][$tmp])) {
          // set the new key pair to the value of the old one
          $command['options'][$tmp] = $command['options'][$key];
          // now unset the key as the old key has been token replaced
          unset($command['options'][$key]);
        }
      }
    }
  }
  // build the output for confirmation of command execution

  // target is not required
  if (isset($command['target'])) {
    $print .= $command['target'] . ' ';
  }
  // replace tokens we find in the command itself; rare
  if (isset($command['command'])) {
    $print .= $command['command'] . ' ';
  }
  // tokens can live in arguemnts though this would be rare
  if (isset($command['arguments'])) {
    $print .= implode(' ', $command['arguments']);
  }
  // run through options separately
  if (isset($command['options'])) {
    foreach ($command['options'] as $key => $option) {
      $print .= ' --' . $key . '=' . $option;
    }
  }
  drush_print(dt("You are about to execute this madlib:\n") . $print);
  // confirm decision; if they abort it'll ask the question again
  if (!drush_confirm("\nHit 'y' to execute or 'n' to fill it out again.")) {
    $original['_retry'] = TRUE;
    drush_recipes_drush_recipes_madlib_command_invoke_alter($original);
    $command = $original;
  }
}

 /**
 * Replacement callback for drush_choice with better default handling.
 * @todo  there seems to be some issues w/ this function when it comes to
 * the output that it displays for selection. It is inconsistent as to if key
 * or actual value should be supplied for the default. some times it returns
 * the default, sometimes it returns the key selected but only if the key
 * isn't the default. Default case seems wrong
 *
 * @param  array $options       an array of input
 * @param  string $default_value the default value if nothing selected
 * @param  string $prompt        question to ask the user
 * @param  string $label         !value, !key or !number for listing
 * @return string                value selected, otherwise $default_value
 */
function drush_choice_with_custom_defaults($options, $default_value, $prompt = 'Enter a number.', $label = '!value') {
  print dt($prompt) . "\n";
  // Make sure array has the correct row and column padding layout.
  $array_pad = 0;
  foreach ($options as $key => $option) {
    if (is_array($option) && (count($option) > $array_pad)) {
      $array_pad = count($option);
    }
  }
  // check to see if the $default_value is not set.  If no, populate with cancel
  if (is_null($default_value)) {
    $default_value_test = 'Cancel';
  }
  else {
    // else we set the $default_value to the inputted value.
     $default_value_test = $default_value;
  }

  // may have to change the following values to meet standard of array syntax.
  $default_array = array('[0]', ':', $default_value_test);
  $rows[] = array_pad($default_array, $array_pad + 2, '');
  $selection_number = 0;
  foreach ($options as $key => $option) {
    if ((substr($key, 0, 3) == '-- ') && (substr($key, -3) == ' --')) {
      $rows[] = array_pad(array('', '', $option), $array_pad + 2, '');
    }
    else if ($option != $default_value_test) {
      $selection_number++;
      $row = array("[$selection_number]", ':');
      if (is_array($option)) {
        $row = array_merge($row, $option);
      }
      else {
        $row[] = dt($label, array('!number' => $selection_number, '!key' => $key, '!value' => $option));
      }
      $rows[] = $row;
      $selection_list[$selection_number] = $key;
    }
  }
  foreach ($rows as $row) {
    // gets the intial value of the array.
    if (current($row) == '[0]') {
      for ($i = 0; $i < 1; $i++) {
       $initial_rows_value = $row[2];
      }
    }
    else{
      // check to see if intital string and current string are equal.
      if (strcmp($initial_rows_value, end($row)) == 0) {
        array_splice($rows, 1, -1);
        // if we split, then we have to rebuild the numbering of the array.
      }
    }
  }
  drush_print_table($rows);
  drush_print_pipe(array_keys($options));

  // If user specifies choice (eg choice that isn't default)
  // then make a selection and reprompt if the choice is not an available option
  if (($choice = drush_get_option('choice', FALSE)) !== FALSE) {
    // first see if choice is one of the symbolic options
    if (array_key_exists($choice, $options)) {
      return $choice;
    }
    else if (array_key_exists($choice, $selection_list)) {
      return $selection_list[$choice];
    }
    // do something here to reprompt
    return FALSE;
  }

  // if the user supplied the default answer
  if (!drush_get_context('DRUSH_NEGATIVE') && !drush_get_context('DRUSH_AFFIRMATIVE') && !drush_get_context('DRUSH_PIPE')) {
    while ($line = trim(fgets(STDIN))) {
      return $selection_list[$line];
    }
  }

  // if only one option in the array
  if (drush_get_context('DRUSH_AFFIRMATIVE') && (count($options) == 1)) {
    return $selection_list[0];
  }
  // change this to be the default.
  if ($default_value == 'Cancel') {
     drush_print(dt('Cancelled'));
     return FALSE;
  }

  return $default_array[2];
}

/**
 * Drush command callback for drush-validate-recipes.
 */
function drush_drush_recipes_drush_validate_recipes($list = '') {
  $commands = array();
  $list = explode(',', $list);
  if (empty($list)) {
    drush_log('You must specify recipes to validate! try running drush dlr for a listing of commands to test.', 'error');
    return FALSE;
  }
  $recipes = _drush_recipes_system_rebuild_recipe_data();
  $validate = array_intersect_key($recipes, array_flip($list));
  if (empty($validate)) {
    drush_log('The recipes you have specified don\'t exist, try running drush dlr for a listing of available commands or use --dr-locations to include a location that might have the recipe you just tried to validate.', 'error');
    return FALSE;
  }
  // validate recipes we are going to cook are valid recipe formatted items
  foreach ($validate as $recipe) {
    if (!_drush_recipes_validate_recipe($recipe->drecipe)) {
      // this wasn't a valid format
      return drush_user_abort();
    }
  }
  drush_log(dt('All recipes were valid!'), 'ok');
  return TRUE;
}

/**
 * Drush command callback for drush-recipe-recorder.
 */
function drush_drush_recipes_drush_recipe_recorder($state = 'start') {
  switch ($state) {
    case 'start':
      drush_cache_set(drush_get_cid(DRUSH_RECIPES_LOGGING_CID), TRUE, 'drush_recipes');
      drush_log(dt('Commands are now being logged'), 'ok');
    break;
    case 'save':
      // save the recipe
      _drush_recipes_write_recorded_recipe();
    break;
    case 'watch':
      // print the current recording to the screen
      $calls = _drush_recipes_get_recorded_commands();
      drush_log(dt('Here\'s what you have currently logged:'), 'ok');
      drush_print_r($calls);
    break;
    case 'pause':
      drush_cache_clear_all(drush_get_cid(DRUSH_RECIPES_LOGGING_CID), 'drush_recipes');
      drush_log(dt('Command recording has been paused'), 'ok');
    break;
    case 'delete':
      // allow for option to delete certain calls only
      $deleted_command = FALSE;
      if (($delete = drush_get_option('command')) !== NULL) {
        $commands = _drush_recipes_get_recorded_commands();
        // allow for key targetting which you'd know based on watch command
        if (is_numeric($delete)) {
          if (!isset($commands[$delete])) {
            drush_log(dt('Array position for deleting was not set!'), 'error');
            return FALSE;
          }
          drush_print_r($commands[$delete]);
          if (drush_confirm("Are you sure you want to delete the following command from your dvr history?")) {
            unset($commands[$delete]);
            $deleted_command = TRUE;
          }
          else {
            return drush_user_abort();
          }
        }
        else {
          foreach ($commands as $key => $command) {
            // test each command as we may be deleted cruft
            if ($command['command'] == $delete) {
              drush_print(dt('Array position @pos', array('@pos' => $key )));
              drush_print_r($commands[$key]);
              if (drush_confirm("Are you sure you want to delete the following command from your dvr history?")) {
                unset($commands[$key]);
                $deleted_command = TRUE;
              }
            }
          }
        }
        // reset keys to be in order
        foreach ($commands as $command) {
          $tmp[] = $command;
        }
        // write this back to the cache
        drush_cache_set(drush_get_cid(DRUSH_RECIPES_COMMAND_CID), $tmp, 'drush_recipes');
        // see if we found a command and deleted it
        if ($deleted_command) {
          drush_log(dt('@delete has been deleted from your dvr', array('@delete' => $delete)), 'ok');
          return TRUE;
        }
        else{
          drush_log(dt('@delete command not found / removed from your dvr', array('@delete' => $delete)), 'warning');
          return FALSE;
        }
      }
      else {
        // clear whats been recorded
        if (drush_confirm(dt('Are you sure you want to delete all recorded commands?'))) {
          drush_cache_clear_all(drush_get_cid(DRUSH_RECIPES_COMMAND_CID), 'drush_recipes');
          drush_log(dt('Command recording has been deleted'), 'ok');
          return TRUE;
        }
        else {
          return drush_user_abort();
        }
      }
    break;
    case 'stop':
      // clear the state of command recording to stop recording
      drush_cache_clear_all(drush_get_cid(DRUSH_RECIPES_LOGGING_CID), 'drush_recipes');
      $commands = _drush_recipes_get_recorded_commands();
      // if not empty save the recipe
      if(!empty($commands)){
        _drush_recipes_write_recorded_recipe();
        drush_cache_clear_all(drush_get_cid(DRUSH_RECIPES_COMMAND_CID), 'drush_recipes');
      }
      // if comand array value is empty, do not write to a recipe.
      else{
        drush_log(dt('Cannot write: No commands recorded in dvr'), 'error');
      }
    break;
    default:
      drush_log(dt('Invalid recorder state.'), 'error');
      return FALSE;
    break;
  }

  return TRUE;
}

/**
 * Helper function to automatically save commands to recipe format
 */
function _drush_recipes_write_recorded_recipe() {
  $calls = _drush_recipes_get_recorded_commands();
  return _drush_drush_recipes_drush_write_recipe($calls, drush_get_option('test-run', FALSE));
}

/**
 * Helper function to validate a drush recipe
 */
function _drush_recipes_validate_recipe($recipe) {
  // generic validation that it can be loaded and reloaded from source
  // encode the recipe to json
  $original_recipe = _drush_recipes_encode($recipe, 'json');
  // attempt to load the recipe from json
  $loaded_recipe = _drush_recipes_load_recipe($original_recipe, TRUE);
  // now load again off of this item that was just loaded in
  $new_recipe = _drush_recipes_encode($loaded_recipe, 'json');
  // attempt to load the recipe from json
  $processed_recipe = _drush_recipes_encode(_drush_recipes_load_recipe($new_recipe, TRUE));
  // if this item is not IDENTICAL after being reloaded it must be corrupt
  if ($original_recipe != $processed_recipe) {
     drush_log(dt('Recipe format you attempted to import was corrupt! Check source'), 'error');
     return DRUSH_RECIPES_INVALID;
  }
  // ensure the major api version is set
  if (!isset($recipe['drush_recipes_api'])) {
    drush_log(dt('All recipes must include the `drush_recipes_api` property. Please review drush_recipes.api.php if building a complex recipe by hand.'), 'error');
     return DRUSH_RECIPES_INVALID;
  }
  // check the API of this recipe and validate accordingly
  switch ($recipe['drush_recipes_api']) {
    // in the future we can add additional support for future specs
    case DRUSH_RECIPES_API_VERSION:
      // ensure the required parts of the array are intact
      if (!isset($recipe['name']) || !isset($recipe['recipe'])) {
        drush_log(dt('name and recipe properties are required!'), 'error');
        return DRUSH_RECIPES_INVALID;
      }
      // check for invalid properties, custom stuff belongs in metadata
      // this helps ensure consistency and security
      foreach ($recipe as $key => $value) {
        switch($key) {
          case 'name':
          case 'drush_recipes_api':
          case 'core':
          case 'weight':
          case 'conflicts':
          case 'dependencies':
          case 'recipe':
          case 'metadata':
          case 'env':
            // do nothing, these are valid properties in 1.0
          break;
          default:
            drush_log(dt('A property was defined that version @api does not support!', array('@api' => DRUSH_RECIPES_API_VERSION)), 'error');
            return DRUSH_RECIPES_INVALID;
          break;
        }
      }
      // nothing was able to invalidate the recipe so assumption it is safe
      return DRUSH_RECIPES_VALID;
    break;
    default:
      // a specification verison is being defined that we don't know about yet
      // this either signals someone building against their own verison of
      // the spec or that a recipe is corrupt because it has the wrong version
      // number
      drush_log(dt('The supplied API version number of @api is not currently known to the drush recipes plugin. Validation can\'t happen as a result but this is not preventing it from running as you may know why you are doing this (like experimenting with a new API method).', array('@api' => $recipe['drush_recipes_api'])), 'warning');
      return DRUSH_RECIPES_VALID;
    break;
  }
  // we got here, something went wrong
  return DRUSH_RECIPES_INVALID;
}

/**
 * Wrapper around drush_cache_get to get the recorded commands
 * @return array commands that have been saved in cache throughout recording
 */
function _drush_recipes_get_recorded_commands() {
  $commands = array();
  $command_object = drush_cache_get(drush_get_cid(DRUSH_RECIPES_COMMAND_CID), 'drush_recipes');
  // ensure cache bin data isset
  if (isset($command_object->data)) {
    $commands = $command_object->data;
  }
  return $commands;
}

/**
 * See if we are currently recording commands.
 * @return bool if we should be recording commands currently
 */
function _drush_recipes_record_commands() {
  $recording = FALSE;
  $recording_object = drush_cache_get(drush_get_cid(DRUSH_RECIPES_LOGGING_CID), 'drush_recipes');
  if ($recording_object) {
    $recording = $recording_object->data;
  }
  return $recording;
}

/**
 * Implements hook_drush_exit()
 * See if we should be recording commands and if we should, add our command
 * to the list that's currently in cache.
 */
function drush_recipes_drush_exit() {
  // see if we should be recording commands in the first place
  if (_drush_recipes_record_commands()) {
    // load current command
    $command_object = drush_get_command();
    // exit early if this is a command for recording
    if (in_array($command_object['command'], array('dvr', 'drush-recipe-recorder'))) {
      return TRUE;
    }
    // build the object for writing to command cache
    $command = array(
      'command' => $command_object['command'],
    );
    // load arguments and options at run time
    $args = drush_get_original_cli_args_and_options();
    // split options and arguments into buckets we can rip to a recipe
    foreach ($args as $arg) {
      // check for option
      if (strpos($arg, '--') === 0) {
        if (strpos($arg, '=')) {
          $parts = explode('=', $arg);
          $command['options'][str_replace('--', '', $parts[0])] = $parts[1];
        }
        else {
          $command['options'][str_replace('--', '', $arg)] = TRUE;
        }
      }
      else {
        $command['arguments'][] = $arg;
      }
    }
    // pull in the active alias of this command if it is set
    $target = drush_get_context('DRUSH_TARGET_SITE_ALIAS');
    // ensure we have a target declared before setting this
    if (!empty($target)) {
      $command['target'] = $target;
    }
    // load existing commands
    $commands = _drush_recipes_get_recorded_commands();
    $commands[] = $command;
    drush_cache_set(drush_get_cid(DRUSH_RECIPES_COMMAND_CID), $commands, 'drush_recipes');
    drush_log(dt('Command logged to command recorder.'), 'ok');
  }
}

/**
 * Helper to convert an argument based call to a target based call
 * @param  array $call simple array of a drush call as an array of arguments
 * @return array       command / target based method of running a drush call
 */
function _drush_recipes_argument_to_target($call) {
  // temp place to work with the call
  $tmp = $call;
  $new_call = array();
  // look for a drush alias target
  if (strpos($tmp[0], '@') === 0) {
    $new_call['target'] = $tmp[0];
    array_shift($tmp);
  }
  // now we have a command
  $new_call['command'] = $tmp[0];
  array_shift($tmp);
  // ensure we handle these differently since it encapsulates stuff commonly
  if (in_array($new_call['command'], array('php-eval', 'eval', 'ev', 'rap', 'role-add-perm', 'rmp', 'role-remove-perm'))) {
    // loop through the rest
    foreach ($tmp as $key =>  $item) {
      // look for options vs arguments
      if (strpos($item, '--') === 0) {
        // see if this is setting anything
        if (strpos($item, '=')) {
          $parts = explode('=', $item);
          $new_call['options'][str_replace('--', '', $parts[0])] = $parts[1];
        }
        else {
          $new_call['options'][str_replace('--', '', $item)] = TRUE;
        }
        unset($tmp[$key]);
      }
    }
    $new_call['arguments'] = array(implode(' ', $tmp));
  }
  else {
    // loop through the rest
    foreach ($tmp as $item) {
      // look for options vs arguments
      if (strpos($item, '--') === 0) {
        // see if this is setting anything
        if (strpos($item, '=')) {
          $parts = explode('=', $item);
          $new_call['options'][str_replace('--', '', $parts[0])] = $parts[1];
        }
        else {
          $new_call['options'][str_replace('--', '', $item)] = TRUE;
        }
      }
      else {
        $new_call['arguments'][] = $item;
      }
    }
  }

  return $new_call;
}

/**
 * Implements hook_drush_recipes_target_diff_drush_alter().
 */
function drush_recipes_drush_recipes_target_diff_drush_alter(&$drush, $source_settings, $destination_settings) {
  // remove problem modules from being enabled via drush
  $problems = array('apc', 'filecache', 'entitycache', 'eck_entitycache');
  foreach ($problems as $problem) {
    if (isset($drush['en'][$problem])) {
      unset($drush['en'][$problem]);
    }
  }
  // if a new drush recipes instance, move these to the end!
  if (isset($drush['en']['drush_recipes_service'])) {
    unset($drush['en']['drush_recipes_service']);
    unset($drush['en']['drush_recipes_defaults']);
    unset($drush['en']['drush_recipes_displays']);
    unset($drush['en']['drush_recipes_entity']);
    $drush['_last'][] = array(
      'command' => 'en',
      'arguments' => array('drush_recipes_entity')
    );
    $drush['_last'][] = array(
      'command' => 'en',
      'arguments' => array('drush_recipes_service')
    );
  }
}

/**
 * Drush command callback for drush-dl.
 */
/*function drush_drush_recipes_drush_dl($url, $destination, $overwrite = TRUE) {
  // attempt download and saving of file
  if (_drush_download_file($url, $destination, $overwrite)) {
    drush_print(dt('@url successfully saved to @dest', array('@url' => $url, '@dest' => $destination)));
    return TRUE;
  }
  drush_print(dt('Download failed!'));
  return FALSE;
}*/
