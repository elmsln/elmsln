<?php

// the following variable can be used to utilize curl for requests
// which can get around some issues with SSL on some servers
// there is no UI for this and you have to have curl compiled
// into your version of PHP but you can put the following into
// your settings.php
$conf['canvas_api_request_method'] = 'curl';
// or run this via drush:
// drush vset canvas_api_request_method curl