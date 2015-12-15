<?php
/**
 * @file
 * Admin page callbacks for the Node.js module.
 */

/**
 * Form builder function for module settings.
 */
function nodejs_settings() {
  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node.js server'),
  );
  $form['server']['nodejs_server_scheme'] = array(
    '#type' => 'radios',
    '#title' => t('Protocol used by Node.js server'),
    '#default_value' => variable_get('nodejs_server_scheme', 'http'),
    '#options' => array('http' => t('http'), 'https' => t('https')),
    '#description' => t('The protocol used to communicate with the Node.js server.'),
  );
  $form['server']['nodejs_server_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Node.js server host'),
    '#default_value' => variable_get('nodejs_server_host', 'localhost'),
    '#size' => 40,
    '#required' => TRUE,
    '#description' => t('The hostname of the Node.js server.'),
  );
  $form['server']['nodejs_server_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Node.js server port'),
    '#default_value' => variable_get('nodejs_server_port', '8080'),
    '#size' => 10,
    '#required' => TRUE,
    '#description' => t('The port of the Node.js server.'),
  );
  $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard.
                    Example paths are %blog for the blog page and %blog-wildcard for every personal blog.
                    %front is the front page.",
                    array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  $form['server']['nodejs_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages on which to enable nodejs'),
    '#default_value' => variable_get('nodejs_pages', '*'),
    '#required' => TRUE,
    '#description' => $description,
  );

  return system_settings_form($form);
}

