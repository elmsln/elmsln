<?php
/**
 * Self building aliases for on ELMSLN deployments
 */
define ('DRUSH_ELMSLN_ENVIRONMENT', '/var/www/elmsln/_elmsln_env_config/drush_environment.php');

// abstracted to avoid multiple calls against this file due to
// an issue in drush where it's processing this file many many times
// this also makes it easy to static / pervasively cache the calls
// allow for environment specific overrides
if (file_exists(DRUSH_ELMSLN_ENVIRONMENT)) {
  include_once('generate_aliases.php');
  _elmsln_alises_build_server($aliases);
  //print_r($aliases);
  include_once(DRUSH_ELMSLN_ENVIRONMENT);
}
