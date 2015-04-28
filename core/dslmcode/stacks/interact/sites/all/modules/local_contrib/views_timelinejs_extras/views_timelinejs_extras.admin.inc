<?php
/**
 * @file
 * Admin page callbacks for the views_timelinejs_extras module.
 */
function views_timelinejs_extras_admin_settings() {
  $form['views_timelinejs_extras_bce'] = array(
    '#type' => 'checkbox',
    '#title' => t('BCE dates'),
    '#description' => t('This supplies css that hides the parts of the timeline interface that display the actual date it is rendering. This can be used to fake BCE date input (which is oddly impossible otherwise).'),
    '#default_value' => variable_get('views_timelinejs_extras_bce', FALSE),
  );
  return system_settings_form($form);
}
