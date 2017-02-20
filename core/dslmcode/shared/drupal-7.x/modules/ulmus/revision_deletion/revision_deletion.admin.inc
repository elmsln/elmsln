<?php
// $Id: revision_deletion.admin.inc,v 1.1.2.9 2009/09/05 21:46:51 nancyw Exp $

/**
 * @file
 * Node Revision Deletion admin page.
 */

/**
 * Settings form.
 */
function revision_deletion_settings_form() {
  // Intervals (in seconds).
  $minute = 60;
  $hour = 60 * $minute;
  $day = 24 * $hour;
  $week = 7 * $day;

  $form['rev_del'] = array(
    '#type' => 'fieldset',
    '#title' => t('Revision Mass Delete settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    );

  $node_types = array();
  foreach (node_type_get_types() as $name => $type) {
    $options = variable_get("node_options_$name", array());
    $enabled = in_array('revision', $options);
    $node_types[$name] = $enabled ? '<strong>'. $type->name .'</strong>' : $type->name;
  }
  $form['rev_del']['revision_delete'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#default_value' => variable_get('revision_delete', array()),
    '#multiple' => TRUE,
    '#options' => $node_types,
    '#description' => t('Select which content types are subject to revision deletion. Types in <strong>bold</strong> have revisions enabled by default. Multiple types may be selected.'),
    );

  // Set revision frequency interval.
  $frequency = array(0 => t('Disabled'));
  $frequency += drupal_map_assoc(array(1 * $day, 2 * $day, 4 * $day, 1 * $week, 2 * $week, 30 * $day, 60 * $day), 'format_interval');
  $form['rev_del']['revision_delete_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Automatic deletion frequency'),
    '#default_value' => variable_get('revision_delete_frequency', 0),
    '#options' => $frequency,
    '#description' => t('Frequency of the scheduled mass revision deletion.'),
    );

  // Set revision age for deletion.
  $age = drupal_map_assoc(array(15 * $minute, 30 * $minute, 1 * $hour, 2 * $hour, 1 * $day, 4 * $day, 1 * $week, 2 * $week, 30 * $day, 60 * $day, 120 * $day, 180 * $day, 365 * $day), 'format_interval');
  $form['rev_del']['revision_delete_age'] = array(
    '#type' => 'select',
    '#title' => t('Minimum age of revision to delete'),
    '#default_value' => variable_get('revision_delete_age', 30 * $day),
    '#options' => $age,
    '#description' => t('Revisions of this age and older will be deleted.'),
    );

  // Set age for current revision.
  $current_age = array(0 => t('Always'));
  $current_age += drupal_map_assoc(array(1 * $hour, 2 * $hour, 4 * $hour, 12 * $hour, 1 * $day, 4 * $day, 1 * $week, 2 * $week, 30 * $day, 60 * $day, 180 * $day), 'format_interval');
  $form['rev_del']['revision_delete_list_keep_current'] = array(
    '#type' => 'select',
    '#title' => t('Minimum age of current revision'),
    '#default_value' => variable_get('revision_delete_list_keep_current', 2 * $week),
    '#options' => $current_age,
    '#description' => t('If the current revision is not older than specified here, its older revisions will not be deleted, even if they are old enough. If set to "Always", older revisions will be deleted regardless of the age of the current revision.'),
    );

  // Settings for "list revisions".
  $form['list'] = array(
    '#type' => 'fieldset',
    '#title' => t('List settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These options are used on revisions lists.'),
    );

  // Take over core list function.
  $override = variable_get('revision_delete_list_override', 0);
  $form['list']['revision_delete_list_override_before'] = array(
    '#type' => 'hidden',
    '#value' => $override,
    );
  $form['list']['revision_delete_list_override'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override revisions forms'),
    '#default_value' => $override,
    '#description' => t('If checked, the original Drupal revisions forms are replaced by those provided by this module.'),
    );

  // Show notes.
  $form['list']['revision_delete_list_show_notes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show revision notes'),
    '#default_value' => variable_get('revision_delete_list_show_notes', 1),
    '#description' => t('Revisions forms tables will show an extra column with notes like "current" or "last for date". <em>To themers:</em> CSS classes are added to these rows to make it possible to style them differently.'),
    );

  // Keep original.
  $form['list']['revision_delete_list_keep_original'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep original version'),
    '#default_value' => variable_get('revision_delete_list_keep_original', 0),
    '#description' => t('The original version of content will be unchecked by default in deletion lists.'),
    );

  // Keep last per date.
  $form['list']['revision_delete_list_keep_date_last'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep last revision of the day'),
    '#default_value' => variable_get('revision_delete_list_keep_date_last', 0),
    '#description' => t('The last version of content of the same day will be unchecked by default in deletion lists. It is not advisable to use this option together with the <em>Keep original version</em> above.'),
    );

  $form = system_settings_form($form);
  $form['#submit'][] = 'revision_deletion_settings_submit';
  return $form;
}

/**
 * Settings form submission.
 */
function revision_deletion_settings_submit($form, &$form_state) {
  // If the override option has changed, rebuild the menu.
  if ($form_state['values']['revision_delete_list_override_before'] != $form_state['values']['revision_delete_list_override']) {
    menu_rebuild();
  }
}
