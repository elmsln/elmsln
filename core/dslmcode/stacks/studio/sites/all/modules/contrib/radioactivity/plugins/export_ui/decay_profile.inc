<?php

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'radioactivity_decay_profile',
  'access' => 'administer radioactivity',
  'menu' => array(
    'menu item' => 'radioactivity',
    'menu title' => 'Radioactivity',
    'menu description' => 'Administer Radioactivity decay profiles.',
  ),
  'title singular' => t('decay profile'),
  'title plural' => t('decay profiles'),
  'title singular proper' => t('Radioactivity decay profile'),
  'title plural proper' => t('Radioactivity decay profiles'),
  'form' => array(
    'settings' => 'radioactivity_admin_edit_profile_form',
    'validate' => 'radioactivity_admin_edit_profile_form_validate',
  ),
);

/**
 * Implements form callback
 */
function radioactivity_admin_edit_profile_form(&$form, &$form_state) {

  $profile = $form_state['item'];

  unset($form['info']['machine_name']);

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
    '#maxlength' => 128,
    '#default_value' => $profile->name,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine name'),
    '#default_value' => $profile->machine_name,
    '#maxlength' => 21,
    '#machine_name' => array(
      'exists' => 'radioactivity_decay_profile_exists',
    ),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $profile->description,
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'radioactivity') . '/js/jquery.sparkline.min.js',
        drupal_get_path('module', 'radioactivity') . '/js/radioactivity-admin.js',
      ),
    ),
  );

  // Profile selection

  $opts = array(
    'Live' => 'Live storage - write directly to the field database.',
    'Deferred' => 'Deferred storage - write to a database table for scheduled processing.',
    'File' => 'File storage - write incidents to a file in php temporary directory',
  );

  if (class_exists('Memcache') || class_exists('Memcached')) {
    $opts['Memcached'] = 'Memcached storage - write incidents to memcached';
  }

  // Disabled since not ready yet
  if (module_exists('redis')) {
    $opts['Redis'] = 'Redis storage - write incidents to a Redis db';
  }

  $form['storage'] = array(
    '#type' => 'select',
    '#title' => t('Incident storage'),
    '#default_value' => $profile->storage,
    '#required' => TRUE,
    '#description' => t('Select the storage where all of the incidents are stored before processing them.'),
    '#options' => $opts,
  );

  $form['enable_decay'] = array(
    '#type' => 'select',
    '#title' => t('Profile mode'),
    '#description' => t('Mode chooses the way the profile works.'),
    '#default_value' => $profile->enable_decay,
    '#options' => array(
      0 => t('Simple - No decaying, works a simple counter'),
      1 => t('Basic - Choose a time period for decay'),
      2 => t('Advanced - Fully customizable decaying'),
    ),
  );

  // Basic settings

  $opts = array(
    21600 => t('Six hours'),
    86400 => t('A day'),
    172800 => t('Two days'),
    604800 => t('A week'),
    2419200 => t('A month'),
  );

  $basic['time_period'] = array(
    '#type' => 'select',
    '#title' => t('Time period'),
    '#default_value' => $profile->half_life * 10,
    '#options' => $opts,
    '#description' => t(
      'Select the time period in which the item should fall to the bottom.'
      . ' As a rule of a thumb the more content is created the shorter the time '
      . ' period should be.'
      . ' You can change the emitter to advanced mode for fine tuning afterwards.'
      . ' Please note that this value is used to calculate the correct values and'
      . ' it will not appear in the advanced modes form.'
    ),
  );

  // Advanced settings

  $advanced['half_life'] = array(
    '#type' => 'textfield',
    '#title' => t('Half life'),
    '#default_value' => $profile->half_life,
    '#required' => TRUE,
    '#description' => t('Determines the decay rate of the radioactivity. For exaple, if the decay rate is ' .
      '3600 (one hour), the radioactivity halves once an hour. If it is now 1000, it will ' .
      'be 500 after an hour, 250 after two hours, and so on. The default is 6 hours.'
    ),
  );

  $advanced['granularity'] = array(
    '#type' => 'textfield',
    '#title' => t('Decay granularity'),
    '#default_value' => $profile->granularity,
    '#required' => TRUE,
    '#description' => t('This setting determines how often at most the radioactivity is decreased by the decay formula. ' .
      'The shorter the time, the more accurate the modeling will be, but the more database ' .
      'activity is required. The default (1 minute) should be a good starting point.'
    ),
  );

  $advanced['cut_off'] = array(
    '#type' => 'textfield',
    '#title' => t('Energy cut off'),
    '#default_value' => $profile->cut_off,
    '#required' => TRUE,
    '#description' => t('Defines the energy lever under which the energy is assumed nonexistent.'),
  );

  $form['mode_simple'] = array(
    '#type' => 'fieldset',
    '#title' => t('Simple mode'),
    '#description' => t('This profile will act as a simple counter so that fields using this profile may act as for example view counters. Energy does not decay in this mode.'),
    '#states' => array(
      'visible' => array(
         ':input[name="enable_decay"]' => array('value' => '0'),
      ),
    ),
  );

  $form['mode_basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic mode'),
    '#description' => t('This profile will lower the energies of fields using it by decaying them to be a fraction their original value during the given amount of time.'),
    '#states' => array(
      'visible' => array(
         ':input[name="enable_decay"]' => array('value' => '1'),
      ),
    ),
  ) + $basic;

  $form['mode_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced mode'),
    '#description' => t('This profile will give you extra control over the decaying.'),
    '#states' => array(
      'visible' => array(
         ':input[name="enable_decay"]' => array('value' => '2'),
      ),
    ),
  ) + $advanced;

}

/**
 * Implements form callback
 */
function radioactivity_admin_edit_profile_form_validate(&$form, &$form_state) {
  if ($form_state['values']['enable_decay'] == 1) {

    $time = $form_state['values']['time_period'];

    $halflife = $time / 10;
    $granularity = 60;
    $cutoff = 10;

    $form_state['values']['half_life'] = (int)$halflife;
    $form_state['values']['granularity'] = (int)$granularity;
    $form_state['values']['cut_off'] = (int)$cutoff;

  }
}
