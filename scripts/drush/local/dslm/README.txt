DSLM - Drupal Symlink Manager
=============================
DSLM is a set of Drush commands for managing symlinking Drupal sites back to a central set of Drupal cores and installation profiles.


Dependencies
============
 - Drush: http://drupal.org/project/drush


Configuration and Installation
==============================
The first thing you'll want to do is set up your DSLM base folder. The DSLM base folder must contain, at the very least,  a "cores" directory which contains direct checkouts of drupal core. You may also add a "profiles" directory to hold any shared installation profiles you might want to use. Profiles and Cores must be suffixed with a version number, like this:

-- dslm_base
  -- cores
    -- drupal-6.18
    -- drupal-6.20
    -- drupal-7.12
  -- profiles
    -- myInstallProfile-6.x-1.0
    -- myInstallProfile-6.x-1.1
    -- myInstallProfile-7.x-1.0
    -- myInstallProfile-7.x-1.1
      -- myInstallProfile.profile
      -- modules
      -- themes
      -- libraries

Once your base is set up as described above, you'll need to pass it to drush dslm in order to run commands. There are three ways to set the location of your base.

The base can be set using any of the options below. It will first look for the cli switch, then in your drushrc.php and finally for an enviro var.

- The cli switch --dslm-base=/path/to/dslm_base
- The drushrc.php file $options['dslm_base'] = /path/to/dslm_base;
- The DSLM_BASE system environment variable

DSLM Commands
=============
drush dslm-new [site-directory] [core]
Creates a new site within the directory of your choice using the Drupal core-version of your choice. If you pass the --latest flag, the latest core will automatically be chosen. If you do not specify a Drupal core-version, you will be prompted for a choice. (example usage: "drush dslm-new newSite drupal-7.12")

drush dslm-cores
Returns a listing of available DSLM cores. --format compatible

drush dslm-profiles
Returns a listing of available DSLM profiles. --format compatible

<<< Execute the following commands within a site set up with DSLM >>>

drush dslm-info
Returns the current core and any managed profiles symlinked to the site of your cwd. --format compatible

drush dslm-switch-core [core]-[version]
Switches the core symlinks within your cwd's site, to a different version of Drupal core. If you do not specify a core, an interactive prompt will ask. (example usage: "drush dslm-switch-core drupal-7.15")

drush dslm-add-profile [profile name]-[profile version]
Creates a symlink within the 'profiles' directory to a DSLM managed installation profile. If you do not specify a profile name and/or version, you will be prompted for a choice. If the option "--upgrade" is passed, DSLM will remove the already symlinked profile and add your new specified (or prompted) version. (example usage: "drush dslm-add-profile myInstallProfile-2.0 --upgrade")

drush dslm-remove-profile [profile name]
Removes a managed profile.
