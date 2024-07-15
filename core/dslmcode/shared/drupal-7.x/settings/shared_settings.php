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
    "multiple-choice": "@haxtheweb/multiple-choice/multiple-choice.js",
    "true-false-question": "@haxtheweb/multiple-choice/lib/true-false-question.js",
    "short-answer-question": "@haxtheweb/multiple-choice/lib/short-answer-question.js",
    "sorting-question": "@haxtheweb/sorting-question/sorting-question.js",
    "tagging-question": "@haxtheweb/tagging-question/tagging-question.js",
    "matching-question": "@haxtheweb/matching-question/matching-question.js",
    "mark-the-words": "@haxtheweb/mark-the-words/mark-the-words.js",
    "fill-in-the-blanks": "@haxtheweb/fill-in-the-blanks/fill-in-the-blanks.js",
    "haxcms-site-disqus": "@haxtheweb/disqus-embed/lib/haxcms-site-disqus.js",
    "discord-embed": "@haxtheweb/discord-embed/discord-embed.js",
    "page-anchor": "@haxtheweb/page-break/lib/page-anchor.js",
    "collection-list": "@haxtheweb/collection-list/collection-list.js",
    "collection-item": "@haxtheweb/collection-list/lib/collection-item.js",
    "page-section": "@haxtheweb/page-section/page-section.js",
    "simple-cta": "@haxtheweb/simple-cta/simple-cta.js",
    "spotify-embed": "@haxtheweb/spotify-embed/spotify-embed.js",
    "media-image": "@haxtheweb/media-image/media-image.js",
    "simple-icon": "@haxtheweb/simple-icon/simple-icon.js",
    "play-list": "@haxtheweb/play-list/play-list.js",
    "inline-audio": "@haxtheweb/inline-audio/inline-audio.js",
    "audio-player": "@haxtheweb/audio-player/audio-player.js",
    "moar-sarcasm": "@haxtheweb/moar-sarcasm/moar-sarcasm.js",
    "learning-component": "@haxtheweb/course-design/lib/learning-component.js",
    "simple-tags": "@haxtheweb/simple-fields/lib/simple-tags.js",
    "twitter-embed": "@haxtheweb/twitter-embed/twitter-embed.js",
    "self-check": "@haxtheweb/self-check/self-check.js",
    "course-model": "@haxtheweb/course-model/course-model.js",
    "stop-note": "@haxtheweb/stop-note/stop-note.js",
    "video-player": "@haxtheweb/video-player/video-player.js",
    "a11y-collapse": "@haxtheweb/a11y-collapse/a11y-collapse.js",
    "accent-card": "@haxtheweb/accent-card/accent-card.js",
    "a11y-gif-player": "@haxtheweb/a11y-gif-player/a11y-gif-player.js",
    "code-sample": "@haxtheweb/code-sample/code-sample.js",
    "ebook-button": "@haxtheweb/course-design/lib/ebook-button.js",
    "worksheet-download": "@haxtheweb/course-design/lib/worksheet-download.js",
    "image-compare-slider": "@haxtheweb/image-compare-slider/image-compare-slider.js",
    "license-element": "@haxtheweb/license-element/license-element.js",
    "lrn-math": "@haxtheweb/lrn-math/lrn-math.js",
    "vocab-term": "@haxtheweb/vocab-term/vocab-term.js",
    "meme-maker": "@haxtheweb/meme-maker/meme-maker.js",
    "grid-plate": "@haxtheweb/grid-plate/grid-plate.js",
    "lrndesign-timeline": "@haxtheweb/lrndesign-timeline/lrndesign-timeline.js",
    "person-testimonial": "@haxtheweb/person-testimonial/person-testimonial.js",
    "place-holder": "@haxtheweb/place-holder/place-holder.js",
    "q-r": "@haxtheweb/q-r/q-r.js",
    "wikipedia-query": "@haxtheweb/wikipedia-query/wikipedia-query.js",
    "date-card": "@haxtheweb/date-card/date-card.js",
    "h5p-element": "@haxtheweb/h5p-element/h5p-element.js",
    "md-block": "@haxtheweb/md-block/md-block.js",
    "rpg-character": "@haxtheweb/rpg-character/rpg-character.js"
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
// default timeout for certain cis_filter requests
$conf['cis_filter_query_timeout'] = 5000;
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
//$conf['path_inc'] = 'sites/all/modules/ulmus/pathcache/path.inc';
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
