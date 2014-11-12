<?php
/**
 * Self building aliases for on ELMSLN deployments
 */

include_once('generate_aliases.php');
// abstracted to avoid multiple calls against this file due to
// an issue in drush where it's processing this file many many times
// this also makes it easy to static / pervasively cache the calls
_elmsln_alises_build_server($aliases);
//print_r($aliases);
