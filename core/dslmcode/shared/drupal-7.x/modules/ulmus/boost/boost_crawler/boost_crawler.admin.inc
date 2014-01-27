<?php

/**
 * @file
 * Admin page callbacks for the boost_crawler module.
 */

/**
 * Form builder; Configure boost_crawler settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function boost_crawler_admin_settings() {
  $form['boost_crawl_on_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the cron crawler'),
    '#default_value' => variable_get('boost_crawl_on_cron', FALSE),
    '#description'   => t("Pre-cache the pages of the website so they get cached before anyone accesses them."),
  );

  $form['boost_crawl_queue_seconds'] = array(
    '#type' => 'textfield',
    '#title' => t('Time (in seconds) to use for crawling on every cron run'),
    '#default_value' => variable_get('boost_crawl_queue_seconds', 30),
    '#description'   => t("If this it too long, it may cause problems with other tasks that run during the cron runs."),
  );

  return system_settings_form($form);
}

