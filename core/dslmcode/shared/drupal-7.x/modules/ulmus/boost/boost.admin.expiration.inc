<?php

/**
 * @file
 * Admin page callbacks for the boost module.
 */

/**
 * Form builder; Configure boost settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function boost_admin_expiration_settings() {

  $form['boost_ignore_flush'] = array(
    '#type' => 'checkbox',
    '#title' => t('Ignore a cache flush command if cron issued the request.'),
    '#default_value' => variable_get('boost_ignore_flush', BOOST_IGNORE_FLUSH),
    '#description' => t('Drupal will flush all caches when cron is executed, depending on the <a href="!urlcore">core minimum cache lifetime</a> setting. To ignore the request to flush the cache on cron runs, enable this option. If enabled, pages in the Boost cache will be flushed only when their <a href="!urlboost">Boost maximum cache lifetime</a> expires.',
      array(
        '!urlcore'  => url('admin/config/development/performance'),
        '!urlboost' => url('admin/config/system/boost'),
      )),
  );
  $form['boost_expire_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove old cache files on cron.'),
    '#default_value' => variable_get('boost_expire_cron', BOOST_EXPIRE_CRON),
    '#description' => t('If enabled, each time cron runs Boost will check each cached page and delete those that have expired (maximum cache lifetime). The expiration time is displayed in the comment that Boost adds to the bottom of the html pages it creates. This setting is recommended for most sites.'),
  );

  // reset htaccess on submit;
  $form['#submit'][] = 'boost_form_submit_handler';
  return system_settings_form($form);
}
