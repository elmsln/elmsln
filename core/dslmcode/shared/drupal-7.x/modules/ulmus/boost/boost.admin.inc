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
function boost_admin_settings() {
  drupal_add_js(drupal_get_path('module', 'system') . '/system.js');

  $form['cacheability'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Boost cacheability settings'),
  );
  // See http://api.drupal.org/api/function/block_admin_configure/7
  $access = user_access('use PHP for settings');
  $options = array(
    BOOST_VISIBILITY_NOTLISTED => t('All pages except those listed'),
    BOOST_VISIBILITY_LISTED => t('Only the listed pages'),
  );
  $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  if (module_exists('php') && $access) {
    $options += array(BOOST_VISIBILITY_PHP => t('Pages on which this PHP code returns <code>TRUE</code> (experts only)'));
    $title = t('Pages or PHP code');
    $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
  }
  else {
    $title = t('Pages');
  }
  $form['cacheability']['boost_cacheability_option'] = array(
    '#type' => 'radios',
    '#title' => t('Cache specific pages'),
    '#options' => $options,
    '#default_value' => variable_get('boost_cacheability_option', BOOST_VISIBILITY_NOTLISTED),
  );
  $form['cacheability']['boost_cacheability_pages'] = array(
    '#type' => 'textarea',
    '#title' => '<span class="element-invisible">' . $title . '</span>',
    '#default_value' => variable_get('boost_cacheability_pages', BOOST_CACHEABILITY_PAGES),
    '#description' => $description,
  );


  $types = boost_get_storage_types();
  $period = drupal_map_assoc(array(0, 60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 64800, 86400, 2*86400, 3*86400, 4*86400, 5*86400, 6*86400, 604800, 2*604800, 3*604800, 4*604800, 8*604800, 16*604800, 52*604800), 'format_interval');

  $form['cache_types'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Boost cache type settings'),
  );
  foreach ($types as $title => $content_types) {
    $form['cache_types'][$title] = array(
      '#type'          => 'fieldset',
      '#title'         => t('@title settings', array('@title' => $title)),
      '#collapsible' => TRUE,
    );
    $collapsed = TRUE;
    foreach ($content_types as $type => $values) {
      $form['cache_types'][$title][$type] = array(
        '#type'           => 'fieldset',
        '#title'          => t('@type settings', array('@type' => $type)),
        '#description'    => t('Cache @description of type @type',
          array(
            '@description' => $values['description'],
            '@type' => $type,
          )
        ),
      );
      // This content type enabled?
      $form['cache_types'][$title][$type]['boost_enabled_' . $type] = array(
        '#type'          => 'checkbox',
        '#title'         => t('Cache Enabled'),
        '#default_value' => $values['enabled'],
      );

      // Content type extension
      $form['cache_types'][$title][$type]['boost_extension_' . $type] = array(
        '#type'          => 'textfield',
        '#title'         => t('Filename Extension',
          array(
            '@title' => $title,
            '@description' => $values['description'],
            '@type' => $type,
          )
        ),
        '#default_value' => $values['extension'],
      );

      // Maximum cache lifetime
      $form['cache_types'][$title][$type]['boost_lifetime_max_' . $type] = array(
        '#type'          => 'select',
        '#options' => $period,
        '#title'         => t('@type - Maximum Cache Lifetime',
          array(
            '@title' => $title,
            '@description' => $values['description'],
            '@type' => $type,
          )
        ),
        '#default_value' => $values['lifetime_max'],
      );

      // Minimum cache lifetime
      $form['cache_types'][$title][$type]['boost_lifetime_min_' . $type] = array(
        '#type'          => 'select',
        '#options' => $period,
        '#title'         => t('@type - Minimum Cache Lifetime',
          array(
            '@title' => $title,
            '@description' => $values['description'],
            '@type' => $type,
          )
        ),
        '#default_value' => $values['lifetime_min'],
      );
      if ($values['enabled']) {
        $collapsed = !$values['enabled'];
      }
    }
    $form['cache_types'][$title]['#collapsed'] = $collapsed;
  }

  // reset htaccess on submit;
  $form['#submit'][] = 'boost_form_submit_handler';
  return system_settings_form($form);
}
