<?php

include_once(dirname(__FILE__) . '/includes/bootstrap.inc');

function bootstrap_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  $form['themedev'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Theme development settings'),
  );

  $form['themedev']['bootstrap_rebuild_registry'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Rebuild theme registry on every page.'),
    '#default_value' => theme_get_setting('bootstrap_rebuild_registry'),
    '#description'   => t('During theme development, it can be very useful to continuously <a href="!link">rebuild the theme registry</a>.') . '<div class="alert alert-error">' . t('WARNING: this is a huge performance penalty and must be turned off on production websites. ') . l('Drupal.org documentation on theme-registry.', 'http://drupal.org/node/173880#theme-registry'). '</div>',
  );

  $form['cdn'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Theme cdn settings'),
  );

  $form['cdn']['cdn_bootstrap'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use CDN to load in the bootstrap files'),
    '#default_value' => theme_get_setting('cdn_bootstrap'),
    '#description'   => t('Use cdn (a third party hosting server) to host the bootstrap files, Bootstrap Theme will not use the local CSS files anymore and instead the visitor will download them from ') . l('bootstrapcdn.com', 'http://bootstrapcdn.com')
                        .'<div class="alert alert-error">' . t('WARNING: this technique will give you a performance boost but will also make you dependant on a third party who has no obligations towards you concerning uptime and service quality.') . '</div>',
  );

  $form['cdn']['cdn_bootstrap_version_container'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
       ':input[name="cdn_bootstrap"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['cdn']['cdn_bootstrap_version_container']['cdn_bootstrap_version'] = array(
    '#type' => 'select',
    '#title' => t('Bootstrap version'),
    '#options' => array(
      '2.3.2' => 'v2.3.2',
      '2.3.1' => 'v2.3.1',
      '2.3.0' => 'v2.3.0',
      '2.2.2' => 'v2.2.2',
      '2.2.1' => 'v2.2.1',
      '2.2.0' => 'v2.2.0',
      '2.1.1' => 'v2.1.1',
      '2.1.0' => 'v2.1.0',
    ),
    '#default_value' => theme_get_setting('cdn_bootstrap_version'),
  );

}

