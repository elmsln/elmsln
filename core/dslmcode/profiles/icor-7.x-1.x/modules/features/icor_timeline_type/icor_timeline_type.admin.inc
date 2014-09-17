<?php
/**
 * @file
 * Admin page callbacks for the icor_timeline_type module.
 */
function icor_timeline_type_admin_settings() {
  $form['icor_timeline_type_bce'] = array(
    '#type' => 'checkbox',
    '#title' => t('BCE dates'),
    '#description' => t('This supplies css that hides the parts of the timeline interface that display the actual date it is rendering. This can be used to fake BCE date input (which is oddly impossible otherwise).'),
    '#default_value' => variable_get('icor_timeline_type_bce', FALSE),
  );
  return system_settings_form($form);
}
