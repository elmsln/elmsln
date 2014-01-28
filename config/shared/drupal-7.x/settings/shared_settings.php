<?php
# APC cache backend
#$conf['apc_show_debug'] = TRUE;
$conf['cache_backends'][] = 'sites/all/modules/ulmus/apc/drupal_apc_cache.inc';
# APC as default container, others are targetted per bin
#$conf['cache_default_class'] = 'DrupalAPCCache';
# APC as default, so these can be commented out
$conf['cache_class_cache'] = 'DrupalAPCCache';
$conf['cache_class_cache_admin_menu'] = 'DrupalAPCCache';
$conf['cache_class_cache_block'] = 'DrupalAPCCache';
$conf['cache_class_cache_bootstrap'] = 'DrupalAPCCache';
$conf['cache_class_cache_entity_file'] = 'DrupalAPCCache';
$conf['cache_class_cache_entity_og_membership'] = 'DrupalAPCCache';
$conf['cache_class_cache_entity_og_membership_type'] = 'DrupalAPCCache';
$conf['cache_class_cache_field'] = 'DrupalAPCCache';
$conf['cache_class_cache_menu'] = 'DrupalAPCCache';
$conf['cache_class_cache_libraries'] = 'DrupalAPCCache';
$conf['cache_class_cache_token'] = 'DrupalAPCCache';
$conf['cache_class_cache_views'] = 'DrupalAPCCache';
$conf['cache_class_cache_path_breadcrumbs'] = 'DrupalAPCCache';
$conf['cache_class_cache_path'] = 'DrupalAPCCache';

# Filecache for ones that are big and don't change much
$conf['cache_backends'][] = 'sites/all/modules/ulmus/filecache/filecache.inc';
# use this for file systems that don't have shared memory
#$conf['filecache_directory'] = '/var/www/drupal_priv/_filecache/' . $conf['cache_prefix'];
# hit file system in the shared memory portion for faster access
$conf['filecache_directory'] = '/dev/shm/drupal_filecache/' . $conf['cache_prefix'];
#$conf['cache_default_class'] = 'DrupalFileCache';
$conf['cache_class_cache_entity_user'] = 'DrupalFileCache';
$conf['cache_class_cache_advagg_aggregates'] = 'DrupalFileCache';
$conf['cache_class_cache_advagg_info'] = 'DrupalFileCache';
$conf['cache_class_cache_update'] = 'DrupalFileCache';
$conf['cache_class_cache_views_data'] = 'DrupalFileCache';
$conf['cache_class_cache_page'] = 'DrupalFileCache';
$conf['cache_class_cache_display_cache'] = 'DrupalFileCache';
$conf['cache_class_cache_entity_node'] = 'DrupalFileCache';

# Default DB for the ones that change too frequently and are small
$conf['cache_default_class']    = 'DrupalDatabaseCache';
# THIS MUST BE SERVED FROM DB FOR STABILITY
$conf['cache_class_cache_cis_connector'] = 'DrupalDatabaseCache';
$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
