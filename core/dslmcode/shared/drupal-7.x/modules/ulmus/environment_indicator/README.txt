
-- SUMMARY --

Environment Indicator adds a coloured strip to the site informing the user which
environment they are in (Development, Staging Production etc).

For a full description visit the project page:
  http://drupal.org/project/environment_indicator
  
Bug reports, feature suggestions and latest developments:
  http://drupal.org/project/issues/environment_indicator


-- REQUIREMENTS --

* CTools


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

You may configure the environment at /admin/settings/environment-indicator

You can also override settings in settings.php, allowing you to have different
settings for each of your environments. If you choose to detect your environment
using settings.php, then all configuration variables can be overridden in
settings.php, but the most common three are:

  - environment_indicator_overwrite
      A boolean value indicating whether the Environment Indicator should use
      the settings.php variables for the indicator. On your production
      environment, you should probably set this to FALSE. e.g:
      $conf['environment_indicator_overwrite'] = FALSE
  - environment_indicator_overwritten_name
      The text that will be displayed on the indicator. e.g:
      $conf['environment_indicator_overwritten_name'] = 'Staging'
  - environment_indicator_overwritten_color
      A valid css color. e.g:
      $conf['environment_indicator_overwritten_color'] = '#ff5555'
  - environment_indicator_overwritten_position
      Where your indicator may appear. Allowed values are "top" and "bottom".
      e.g:
      $conf['environment_indicator_overwritten_position'] = 'top'
  - environment_indicator_overwritten_fixed
      A boolean value indicating whether the Environment Indicator should be
      fixed at the top/bottom of the screen. e.g:
      $conf['environment_indicator_overwritten_fixed'] = FALSE
  - environment_indicator_favicon_overlay
      A boolean value indicating whether the Environment Indicator should
      overlay the favicon with the current environment's information. e.g.:
      $conf['environment_indicator_favicon_overlay'] = TRUE

-- ACQUIA CLOUD INTEGRATION --

Copy the file in samples/environment-indicator.sh to your
hooks/[your-environment]/post-code-deploy folder and give it execution
permissions. Replace [your-environment] by your environment site alias or use
'common' to use it in all your environments (recommended). This integration
relies on the presence of the environment variable AH_SITE_ENVIRONMENT.

You can read more about Cloud Hooks in
https://github.com/acquia/cloud-hooks/blob/master/README.md

-- CONTACT --

Author maintainers:
* Tom Kirkpatrick (mrfelton), www.systemseed.com. Branches 6.x-1.x, 7.x-1.x
* Mateu Aguiló (e0ipso). Branch 7.x-2.x


This project has been partially sponsored by:
* SystemSeed - Visit http://www.systemseed.com for more information. Branches
  6.x-1.x, 7.x-1.x
* Lullabot - Visit http://www.lullabot.com for more information. Branch 7.x-2.x
