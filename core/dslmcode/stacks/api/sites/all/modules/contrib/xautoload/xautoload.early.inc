<?php

/**
 * You can include this file as early in the request as you wish,
 * e.g. from your site's settings.php, to make the class loader available for
 * external libraries during bootstrap.
 *
 * This will *not* register any Drupal modules, because information about these
 * might not be available yet.
 */

require_once __DIR__ . '/xautoload.early.lib.inc';

_xautoload_register();