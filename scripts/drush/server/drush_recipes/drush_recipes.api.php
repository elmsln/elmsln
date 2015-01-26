<?php
  /**
   * Drush Recipes API
   *
   * This documents ways you can modify the behavior of drush recipes as well
   * as how to create your own recipes.
   */

// You can define additional dr_locations to search for in your .drush/drushrc.php
// settings file so that you can stash recipes in a shared location like box.com
// to use this add something like:
// $options['dr_locations'] = '/drushstuff';
// or
// $options['dr_locations'] = array('/drushstuff', '/drecipes');

// Environment token prepopulation
// you can send any environment token to be answered automatically in one
// of two ways. either by appending env- to the token name at run time or by
// modifying one's drushrc.php and adding $options['env-TOKENNAME'] = 'VALUE';
// this can be used to allow for environment specific global tokens to be
// automatically set when a recipe is run.
// Example:
//   On dev: the drushrc.php has $options['env-global'] = 0;
//   On prod: the drushrc.php has $options['env-global'] = 1;
//   Command: drush @dev cook core_performance --y
//   On dev this evaluates (automatically) to
//     drush @dev cook core_performance --y --env-global=0
//   Which will automatically populate all calls for token "global" with 0
//   meaning that all caches and performance settings will be disabled.
//
//   On prod this evaluates (automatically) to
//     drush @prod cook core_performance --y --env-global=1
//   Which will automatically populate all calls for token "global" with 1
//   meaning that all caches and performance settings will be enabled

// MadLib token prepopulation
// you can seed any madlib automatically by looking at the token name
// appending mlt- and pushing it through
// Example:
//   "drush [target] status" is found in a status.drecipe
//   drush cook status --mlt-target=@coolstuff --y
// The above will automatically set the default value of the token on-demand!

// LOOPING
// ingredients support looping as an option in the ingredient API
// This means you can tell something to run X number of times
// Why is this useful: running the same command multiple times is NOT useful
// passing things in dynamically via a madlib token array IS useful
// Example:
//  "drush [target] status" is found in a status.drecipe
//  drush cook status --looping-mlt-target=@none,@stuff,@things

// drush recipes upgrade spidering (drup)

// drup allows for spidering a directory and abstracting recipes to run
// based on the name that's been passed in. The basic structure of the file
// name should match the aliases that you have (recommended not required):
//   folder structure:
//   /upgrades/{version}/{alias with . changed to /}/
//   file name to match:
//   {version}_{alias with . changed to _}_{timestamp}.drecipe
//
//   examples:
//
//   alias: @ourwebsite.dev
//   path : /upgrades/d7/ourwebsite/dev/
//   file : d7_ourwebsite_dev_1390936501.drecipe
//   drush: drush @ourwebsite.dev drup d7_ourwebsite_dev /upgrades
//
//   alias: @elmsln.courses-all
//   path : elmsln/scripts/upgrade/drush_recipes/d7/elmsln/courses-all/
//   file : d7_elmsln_courses-all_1630936501.drecipe
//   drush: drush @courses-all drup d7_elmsln_courses-all elmsln/scripts/upgrade/drush_recipes
//
//   alias: @elmsln.courses.art010
//   path : elmsln/scripts/upgrade/drush_recipes/d7/elmsln/courses-all/
//   file : d7_elmsln_courses_art010_1630936991.drecipe
//   drush: drush @courses.art010 drup d7_elmsln_courses_art010 elmsln/scripts/upgrade/drush_recipes
//
// while you can use other conventions for your project, the above ensures
// that your drecipe files never conflict between builds even if you would
// accidentally save one to the wrong location. The name matching in the initial
// call helps ensure this, though the convention has admittedly been produced
// to help with the long term management and maintenance of distributions.

// HOOKS

/**
 * Implements hook_drush_recipes_pre_cook_alter().
 * A list of recipes to cook prior to their actual execution. This would allow
 * you to act upon what has been requested and automatically add other recipes
 * or modify based on your own needs.
 * @param  array $list    a list of recipes to cook
 * @param  bool $recurse  if we are recursing
 */
function hook_drush_recipes_pre_cook_alter(&$list, $recurse) {

}

/**
 * Implements hook_drush_recipes_command_invoke_alter().
 * This hook fires just prior to any command being executed in a drush recipe
 * ingredient list. This fires per command listed and allows the developer to
 * react to the command about to be fired for spidering, listening, and utterly
 * ridiculous branching logic.
 * @param  mixed  $command  a command array / string based on format
 * @param  string $format   DRUSH_RECIPES_FORMAT_ARGUMENT or DRUSH_RECIPES_FORMAT_TARGET
 */
function hook_drush_recipes_command_invoke_alter(&$command, $format) {
  // if you see an sql sync about to execute, we have other things to do
  if ($command['command'] == 'sql-sync') {
    // tap our github hooks / do a new git commit of whatever is laying around
    // so that we can trip travis and get feedback about what's happening here
  }
}

/**
 * Implements hook_drush_recipes_FORMAT_command_invoke_alter().
 * This hook fires just prior to a specifically formatted command command being
 * executed in a drush recipe ingredient list. This is the same as above but
 * more memory performant and a prefered method of invoking this hook unless
 * you REALLY want to parse every command type.
 * @param  mixed  $command  a command array / string based on format
 * @param  string $format   DRUSH_RECIPES_FORMAT_ARGUMENT or DRUSH_RECIPES_FORMAT_TARGET
 */
function hook_drush_recipes_FORMAT_command_invoke_alter(&$command) {
  // if you see an sql sync about to execute, we have other things to do
  if ($command['command'] == 'sql-sync') {
    // tap our github hooks / do a new git commit of whatever is laying around
    // so that we can trip travis and get feedback about what's happening here
  }
}

/**
 * Implements hook_drush_recipes_post_cook_alter().
 * This hook fires just after recipes have finished cooking. Since this function
 * could be fired in a recursive manner this may invoke multiple times so be
 * aware of when you are jumping into the operation.
 * @param  array $list    a list of recipes to cook
 * @param  bool $recurse  if we are recursing
 */
function hook_drush_recipes_post_cook_alter(&$list, $recurse) {

}

/**
 * Implements hook_drush_recipes_locations_alter().
 * Add custom locations for where to spider and look for drecipes.
 * @param  array $locations an array of directories to search for recipes
 */
function hook_drush_recipes_locations_alter(&$locations) {

}

/**
 * Implements hook_drush_recipes_system_recipe_data_alter().
 * This allows you to modify the recipes that are loaded in from files just
 * after they have been loaded in. You can use this to modify recipes or inject
 * your own recipes that you want to add on the fly without the need for
 * .drecipe files.
 * @param  object $recipes loaded file objects referencing recipe arrays
 */
function hook_drush_recipes_system_recipe_data_alter(&$recipes) {

}

/**
 * Implements hook_drush_recipes_after_recipe_loaded_alter().
 * This allows for modification of a recipe just after it has been loaded from
 * a flat file.
 *
 * @param  array $recipe a fully loaded array from a file without file object
 */
function hook_drush_recipes_after_recipe_loaded_alter(&$recipe) {

}

/**
 * Implements hook_drush_recipes_to_drush_alter().
 * This allows for modification of a recipe just before it is converted into
 * drush statements. You could use this to jump in and inject ingredients based
 * on what you see in the current recipe or remove commands that you don't like
 * firing (like a complex security routine where you like all but 1 setting).
 *
 * @param  array $recipe a recipe structure being converted to drush statements
 */
function hook_drush_recipes_to_drush_alter(&$recipe) {

}

/**
 * Implements hook_drush_recipes_encode_alter().
 * This allows for modifying the output just before it is typically written to
 * a file or printed to the screen.
 *
 * @param  string $contents  output of a recipe for export
 * @param  string $format    format of the export data; json, xml, or yaml
 */
function hook_drush_recipes_encode_alter(&$contents, $format) {

}

/**
 * Implements hook_drush_recipes_target_diff_drush_alter().
 * using $drush['__last'][] can be used to force a call to fire at the end
 * but then it will be assuming that this is a valid call format. Use this if
 * you know of calls that need to happen at the end of the routine / after other
 * calls to avoid issues (such as features that define user role permissions).
 *
 * @param  array $drush                array of drush calls to write to recipe
 * @param  array $source_settings      alias / db settings for source
 * @param  array $destination_settings alias / db setings for destination
 */
function hook_drush_recipes_target_diff_drush_alter(&$drush, $source_settings, $destination_settings) {
  // you can use this to add support for custom tables or figuring out the
  // difference in other values that we currently don't support / are
  // very specific to your development workflow.

  // For example, maybe you override a variable in settings.php related to
  // which environment you are on. You could forcibly unset the value in the
  // event that it got written to the variables table earlier.

  // For custom tables you are doing direct comparisons against you can use the
  // _drush_recipes_load_db_table() function which is a helper for pulling a
  // database table from drupal given settings. Below is an example of hitting
  // a custom table and doing a comparison. This example is taken from the way
  // that we compare for variables between the two system tables. This practice
  // is rather similar to how the other commands function but can't be further
  // abstracted due to small variance in how each evaluates whether or not it is
  // the same, different or missing.

  $source_custom = _drush_recipes_load_db_table($source_settings, 'mytable', 'column');
  $destination_custom = _drush_recipes_load_db_table($destination_settings, 'mytable', 'column');
  // compare the source with the destination
  foreach ($source_custom as $name => $data) {
    // ensure A exists on B
    if (array_key_exists($name, $destination_custom) ) {
      $destination_vars[$name]->name = 'found';
      // now check for status
      if ($data->value != $destination_custom[$name]->value) {
        // this means source is different from destination
        $drush['setthings'][$name] = $destination_custom[$name]->value;
      }
    }
    else {
      // now we know we need to delete this
      $drush['deletethings'][$name] = $name;
    }
  }
  // test for destination having value not originally in source
  foreach ($destination_custom as $name => $data) {
    // find things we didn't find previously
    if ($data->name != 'found') {
      $drush['setthings'][$name] = $data->value;
    }
  }
}

/**
 * Implements hook_drush_recipes_to_drush_command_format_alter().
 * @param  array  $drush  a series of drush commands for the recipe to process
 * @param  array  $call   the current ingredient structure from one call
 * @param  string $format a custom call format machine name
 * @param boolean $list   boolean of whether we are listing to the screen
 */
function hook_drush_recipes_to_drush_command_format_alter(&$drush, $call, $format, $list) {
  // this can be used to help setup what to do with the recipe that's being
  // passed in. This fires prior to running the command at the printing to screen
  // phase when it's going to tell the user what is about to be run. Use this
  // when you have a custom recipe format like the one below.
  if ($format == 'btools') {
    $drush[] = $call['superadvancedcallstructureforthesakeofbeingadvanced'];
    if ($list) {
      drush_print('About to execute the super secret custom CMS cluster project known as the btools library. That every site needs but almost no one understands.');
    }
  }
}

/**
 * Implements hook_drush_recipes_detect_format_alter().
 * @param  array $call   the call structure about to be processed
 * @param  string $format machine name format of this call structure
 */
function hook_drush_recipes_detect_format_alter(&$call, $format) {
  // this can be used to define new call formats currently not in the drush
  // recipes specification. Use this to allow drush_recipes to detect that
  // you are providing your own call structure. The only requirement is that
  // in the call sturcture you set $call['_drush_recipes_custom_format']
  // to the machine_name that you want to name your format. an example is
  // provided below.
  $call['_drush_recipes_custom_format'] = 'btools';
}

// this is an example of how you could practically apply the above super secret
// call structure format for btools
function CUSTOMPLUGIN_drush_recipes_btools_command_invoke_alter(&$command) {
  drush_log('Adding super ingredient: ' . $call['superadvancedcallstructureforthesakeofbeingadvanced']['name'], 'ok');
  // this is the simple method for running when non interactive
  drush_shell_exec($call['superadvancedcallstructureforthesakeofbeingadvanced']['evilcommandnooneunderstands']);
  $shell_output = drush_shell_exec_output();
  // print whatever came out of that super secret and misunderstood shell command
  foreach ($shell_output as $shell) {
    drush_print($shell);
  }
  drush_log($call['superadvancedcallstructureforthesakeofbeingadvanced']['name'] . ' probably didn\'t complete but developers everywhere would be wow\'ed that you event attempted those sweet lines of code!', 'warning');
}

// allows for defining of commands that have known issues with running
// interactively in a list of ingredients. This includes the core php-eval
// command as well as anything that requires the batch_api as that requires
// a more sophisticated handling of drush commands then recipes is capable
// of stringing together as a single command. shell_exec will allow the drush
// command to effectively open another process, complete, and then report back
// what happened. exec is just an array of commands that require this processing
function hook_drush_recipes_require_shell_exec_alter(&$exec) {
  $exec[] = 'httprl-self-spider';
}

/**
 * Drush Recipe 1.0
 *
 * name - Human reable name of this recipe; required
 * drush_recipes_api - api version, 1.0 defaults
 * core - drupal core this is compatible with, optional
 * weight - weight relative to other recipes if called in the same block-chain
 *   this defaults to 0
 * dependencies - drush plugin name, drush command, module names, or @site which
 *   means that the command requires a working drupal site to function.
 *   All four are valid dependency types and can be used together but try to
 *   use @site, plugin name or module name when possible, drush command is lazy
 *   and doesn't give good feedback to other developers as to how to meet the
 *   requirement.
 * conflicts - a list of recipes that are known conflicts. Use this if you are
 *   building multiple recipes and you know that they don't play nice together.
 *   This can help save you or others from accidentally trying to run recipes
 *   that do and undo each others functionality (or a security recipe known
 *   to have issues with something that opens up doors).
 * recipe - the structure of commands to execute, this can also be another
 *   recipe filename which will append all the commands in that file ahead of
 *   what is about to execute. There are 4 structures to this listed below
 * env - any environmental variables / tokens that can be defined ahead of time
 *   or at run time. If a value is used multiple times across .drecipe's it will
 *   only be asked for once. If supplied ahead of time, it won't be asked at all.
 * metadata - a series of properties that can be used for front-end integration.
 *   this is entirely optional but helps developers understand what you wrote.
 */
$js = <<<JS
{
  "name": "Security defaults",
  "drush_recipes_api": "1.0",
  "weight": 0,
  "core": "7",
  "dependencies": [
    "seckit",
    "paranoia"
  ],
  "conflicts": [
    "insecure_stuff"
  ],
  "env": {
    "tokens": {
      "[tokenname1]": "Question to ask the user?",
      "[tokenname2]": "Question to ask the user 2?"
    },
    "defaults": {
      "[tokenname1]": "value1",
      "[tokenname2]": "value2"
    }
  },
  "recipe": [
    "dr_admin_update_status.drecipe",
    [
      "vset",
      "user_register",
      "1"
    ],
    [
      "dis",
      "php"
    ],
    [
      "pm-uninstall",
      "php"
    ],
    [
      "en",
      "seckit"
    ],
    [
      "en",
      "paranoia"
    ]
  ],
  "metadata": {
    "descrption": "Disable projects that cause issues, increase h-our defenses cap'in!",
    "version": "1.0",
    "type": "add-on",
    "author": "btopro",
    "logo": "files\/image.png"
  }
}
JS>>>;

$js = <<<JS
// here's the 4 major types of calls you can do in a recipe as of the 1.0 spec.
"recipe": [
    "dr_admin_update_status.drecipe", // reference another recipe
    [
      "vset", // each element is an argument passed into a 1 line call w/ drush as prefix
      "user_register",
      "1"
    ],
    [
      "conditional": [ // allow for user to select which sub-routine to run
        "recipe1.drecipe",
        "recipe2.drecipe",
        "recipe3.drecipe"
      ],
      "prompt": "Which recipe would you like to execute?"
    ],
    [// long call format, this allows user to interact w/ the call
     // only use this for complex call structures that you need to interact with
     // this is the preferred method
      "target": "cool.d7.site", // target
      "command": "en", // command to issue
      "arguments": [ // arguments to pass in, similar to simple structure
        "paranoia"
      ],
      "options": ["y"] // any possible options
    ],
    [// madlib call format, this gets pretty intense but opens a lot of doors
      "madlib": [
        "madlib": "TRUE", // required to detect madlib spec
        "target": "", // target
        "command": "si", // command to issue
        "arguments": [ // arguments to pass in, similar to simple structure
          "[profile]"
        ],
        "options": [
          "db-url": "[db-url]",
          "db-prefix": "[db-prefix]",
          "db-su": "[db-su]",
          "db-su-pw": "[db-su-pw]",
          "account-name": "[account-name]",
          "account-pass": "[account-pass]",
          "account-mail": "[account-mail]",
          "locale": "[locale]",
          "clean-url": "[clean-url]",
          "site-name": "[site-name]",
          "site-mail": "[site-mail]",
          "sites-subdir": "[sites-subdir]"
        ],
        "tokens": [
          "[profile]": "the install profile you wish to run. defaults to 'default' in D6, 'standard' in D7+",
          "[db-prefix]": "",
          "[db-url]": 'Enter the database url in the format of mysql://dbusername:dbpassword@localhost:port/dbname',
          "[db-su]": 'Root level mysql user (this information is not saved)',
          "[db-su-pw]": 'account password (this information is not saved)',
          "[account-name]": 'uid1 name. Defaults to admin',
          "[account-pass]": 'uid1 pass. Defaults to a randomly generated password. If desired, set a fixed password in drushrc.php.',
          "[account-mail]": 'uid1 email. Defaults to admin@example.com',
          "[locale]": 'A short language code. Sets the default site language. Language files must already be present. You may use download command to get them.',
          "[clean-url]": 'Defaults to 1',
          "[site-name]": 'Defaults to Site-Install',
          "[sites-mail]": 'From: for system mailings. Defaults to admin@example.com',
          "[sites-subdir]": "Name of directory under 'sites' which should be created. Only needed when the subdirectory does not already exist. Defaults to 'default'"
        ],
        "defaults": [
          "[profile]": "minimal",
          "[sitename]": "Your new drupal site"
        ]
      ]
    ],
JS>>>;
