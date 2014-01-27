<?php

//a script to read the sites array, then run drush cron on each site defined.
//used as a workaround to @sites not working on subsites that live below the
///sites directory.
include "sites.php";

foreach ($sites as $key=>$value) {
  // only apply this to non-data addresses as they are the same
  if (strpos($key, 'data') === FALSE) {
    exec("drush --r=" . substr(getcwd(), 0, -5) . " --uri=http://$key -y cron &");
    exec("drush --r=" . substr(getcwd(), 0, -5) . " --uri=http://$key -y hss &");
  }
}
