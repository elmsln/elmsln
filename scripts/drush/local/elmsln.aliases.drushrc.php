<?php
/**
 * Self building aliases by reading them from removes
 */

// @todo THIS NEEDS TO BE CACHED unless doing a SA command
// otherwise this will have to connect to all hosts in order
// to execute ANY command
include_once('generate_aliases.php');
// abstracted to avoid multiple calls against this file due to
// an issue in drush where it's processing this file many many times
_elmsln_alises_build($aliases);
