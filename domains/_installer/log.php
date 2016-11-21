<?php
  header("Content-Type:application/json");
  $log = file_get_contents('/var/www/elmsln/config/tmp/INSTALL-LOG.txt');
  print json_encode($log);
?>