<?php
// these settings are dictated by the elmsln project team
// you can override them in your config version of shared_settings
// but it is highly recommended against for system stability

// fix for core change in 7.50
$conf['x_frame_options'] = '';
// allow image cache derivatives without itok token
$conf['image_allow_insecure_derivatives'] = TRUE;
// prevent bakery from giving weird messges
$conf['bakery_status_messages'] = FALSE;

// use this to debug restws issues
#$conf['restws_debug_log'] = '/var/www/elmsln/config/tmp/rest.debug';

// Allow RestWS calls to pass through on bakery installs, otherwise webservices
// reroute looking for the bakery login cookie and fail.
// If bakery isn't installed this does nothing and can be ignored.
if (isset($conf['restws_basic_auth_user_regex'])) {
  $conf['bakery_is_master'] = TRUE;
}
$conf['restws_basic_auth_user_regex'] = '/.*/';
// httprl setting to avoid really long timeouts
$conf['httprl_install_lock_time'] = 1;
// make authcache happy with the safer controller if we're using it
$conf['authcache_p13n_frontcontroller_path'] = 'authcache.php';

// cache backends so we know about authcache and apdqc, those we formally support
$conf['cache_backends'][] = 'sites/all/modules/ulmus/apdqc/apdqc.cache.inc';
$conf['cache_backends'][] = 'sites/all/modules/ulmus/authcache/authcache.cache.inc';
$conf['cache_backends'][] = 'sites/all/modules/ulmus/authcache/modules/authcache_builtin/authcache_builtin.cache.inc';

// Default backend controller to be apdqc
$conf['cache_default_class']    = 'APDQCache';
// THIS MUST BE SERVED FROM DB FOR STABILITY
$conf['cache_class_cache_cis_connector'] = 'APDQCache';
$conf['cache_class_cache_form'] = 'APDQCache';

// pathcache settings
$conf['path_inc'] = 'sites/all/modules/ulmus/pathcache/path.inc';
// apdqc lock file
$conf['lock_inc'] = 'sites/all/modules/ulmus/apdqc/apdqc.lock.inc';
// apdqc session file
$conf['session_inc'] = 'sites/all/modules/ulmus/apdqc/apdqc.session.inc';

// allow user deployment settings to always take priority
include_once "/var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php";
