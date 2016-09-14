<?php 
// fix for core change in 7.50
$conf['x_frame_options'] = '';
// allow user deployment settings to always take priority
include_once "/var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php";

