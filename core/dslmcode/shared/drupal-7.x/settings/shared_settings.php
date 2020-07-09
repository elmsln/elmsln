<?php
// these settings are dictated by the elmsln project team
// you can override them in your config version of shared_settings
// but it is highly recommended against for system stability

// hide webcomponents messaging about cache rebuilds
$conf['webcomponents_hide_messages'] = TRUE;
// default is PSU's CDN but we want these to come from ELMS for versioning purposes
$conf['webcomponents_project_location'] = 'sites/all/libraries/webcomponents/';
$conf['webcomponents_project_local_build_file'] = TRUE;
// baseline HAX elements
$conf['hax_autoload_element_list'] = '{
  "a11y-figure": "@lrnwebcomponents/a11y-figure/a11y-figure.js",
  "lrndesign-chart": "@lrnwebcomponents/lrndesign-chart/lrndesign-chart.js",
  "accent-card": "@lrnwebcomponents/accent-card/accent-card.js",
  "h5p-element": "@lrnwebcomponents/h5p-element/h5p-element.js",
  "hax-logo": "@lrnwebcomponents/hax-logo/hax-logo.js",
  "a11y-gif-player": "@lrnwebcomponents/a11y-gif-player/a11y-gif-player.js",
  "code-sample": "@lrnwebcomponents/code-sample/code-sample.js",
  "citation-element": "@lrnwebcomponents/citation-element/citation-element.js",
  "hero-banner": "@lrnwebcomponents/hero-banner/hero-banner.js",
  "image-compare-slider": "@lrnwebcomponents/image-compare-slider/image-compare-slider.js",
  "license-element": "@lrnwebcomponents/license-element/license-element.js",
  "lrn-aside": "@lrnwebcomponents/lrn-aside/lrn-aside.js",
  "lrn-math": "@lrnwebcomponents/lrn-math/lrn-math.js",
  "lrn-table": "@lrnwebcomponents/lrn-table/lrn-table.js",
  "lrn-vocab": "@lrnwebcomponents/lrn-vocab/lrn-vocab.js",
  "lrndesign-blockquote": "@lrnwebcomponents/lrndesign-blockquote/lrndesign-blockquote.js",
  "magazine-cover": "@lrnwebcomponents/magazine-cover/magazine-cover.js",
  "media-behaviors": "@lrnwebcomponents/media-behaviors/media-behaviors.js",
  "media-image": "@lrnwebcomponents/media-image/media-image.js",
  "meme-maker": "@lrnwebcomponents/meme-maker/meme-maker.js",
  "grid-plate": "@lrnwebcomponents/grid-plate/grid-plate.js",
  "md-block": "@lrnwebcomponents/md-block/md-block.js",
  "multiple-choice": "@lrnwebcomponents/multiple-choice/multiple-choice.js",
  "paper-audio-player": "@lrnwebcomponents/paper-audio-player/paper-audio-player.js",
  "person-testimonial": "@lrnwebcomponents/person-testimonial/person-testimonial.js",
  "place-holder": "@lrnwebcomponents/place-holder/place-holder.js",
  "q-r": "@lrnwebcomponents/q-r/q-r.js",
  "full-width-image": "@lrnwebcomponents/full-width-image/full-width-image.js",
  "self-check": "@lrnwebcomponents/self-check/self-check.js",
  "stop-note": "@lrnwebcomponents/stop-note/stop-note.js",
  "tab-list": "@lrnwebcomponents/tab-list/tab-list.js",
  "task-list": "@lrnwebcomponents/task-list/task-list.js",
  "video-player": "@lrnwebcomponents/video-player/video-player.js",
  "wikipedia-query": "@lrnwebcomponents/wikipedia-query/wikipedia-query.js",
  "lrndesign-gallery": "@lrnwebcomponents\/lrndesign-gallery\/lrndesign-gallery.js",
  "lrndesign-timeline": "@lrnwebcomponents\/lrndesign-timeline\/lrndesign-timeline.js",
  "html-block": "@lrnwebcomponents\/html-block\/html-block.js",
  "user-action": "@lrnwebcomponents\/user-action\/user-action.js",
  "date-card": "@lrnwebcomponents/date-card/date-card.js",
  "service-card": "@lrnwebcomponents/service-card/service-card.js",
  "rss-items": "@lrnwebcomponents/rss-items/rss-items.js",
  "cms-token": "@lrnwebcomponents/cms-hax/lib/cms-token.js"
}';
// fix for core change in 7.50+
$conf['x_frame_options'] = '';
// allow image cache derivatives without itok token
$conf['image_allow_insecure_derivatives'] = TRUE;
// prevent bakery from giving weird messges
$conf['bakery_status_messages'] = FALSE;
// set a standard bakery token age if that project is in use
$conf['bakery_freshness'] = 86400;
// redirect default error pages to some standard ones
$conf['site_403'] = 'elmsln/error/403';
$conf['site_404'] = 'elmsln/error/404';
// stupid error to present
$conf['drupal_http_request_fails'] = FALSE;
// stupid issues w/ curl and canvas API if using that
$conf['canvas_api_request_method'] = 'curl';
// hide status message about dompdf since we addressed it
$conf['print_pdf_dompdf_secure_06'] = TRUE;
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
// a sane batch size, change this downstream if on limited resources or wanting more per run
$conf['cis_section_roster_processor_batch_size'] = 500;
// COMMENT ALL THIS OUT IF YOU NEED TO REINSTALL A SITE FOR SOME REASON
// cache backends so we know about  apdqc, those we formally support
$conf['cache_backends'][] = 'sites/all/modules/ulmus/apdqc/apdqc.cache.inc';
// Default backend controller to be apdqc
$conf['cache_default_class']    = 'APDQCache';
// THIS MUST BE SERVED FROM DB FOR STABILITY
$conf['cache_class_cache_cis_connector'] = 'DrupalDatabaseCache';
$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
// CIS stability
$conf['cache_class_cache_entity_field_collection_item'] = 'DrupalDatabaseCache';
// issue with APDQC and books / big menus
$conf['cache_class_cache_book'] = 'DrupalDatabaseCache';
$conf['cache_class_cache_mooc_helper_book_nav'] = 'DrupalDatabaseCache';
$conf['cache_class_cache'] = 'DrupalDatabaseCache';
$conf['cache_class_cache_bootstrap'] = 'DrupalDatabaseCache';
$conf['cache_class_cache_entity_node'] = 'DrupalDatabaseCache';
$conf['cache_class_cache_menu'] = 'DrupalDatabaseCache';

// pathcache settings
$conf['path_inc'] = 'sites/all/modules/ulmus/pathcache/path.inc';
// apdqc lock file
$conf['lock_inc'] = 'sites/all/modules/ulmus/apdqc/apdqc.lock.inc';
// apdqc session file
$conf['session_inc'] = 'sites/all/modules/ulmus/apdqc/apdqc.session.inc';

# Drupal overrides php.ini settings so we need to re-override them here...
ini_set('error_reporting', E_ALL & ~E_NOTICE & ~E_STRICT & ~E_DEPRECATED);

// allow user deployment settings to always take priority
include_once "/var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php";
if (file_exists("/var/www/elmsln/_elmsln_env_config/shared_settings.php")) {
  include_once "/var/www/elmsln/_elmsln_env_config/shared_settings.php";
}
