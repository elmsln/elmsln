<?php
/**
 * Self building aliases by reading them from remotes
 */

// to execute ANY command
include_once('generate_aliases.php');
// abstracted to avoid multiple calls against this file due to
// an issue in drush where it's processing this file many many times
// this also makes it easy to static / pervasively cache the calls
_elmsln_alises_build($aliases);
//print_r($aliases);
