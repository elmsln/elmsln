<?php

/**
 * @file
 * Chosen administration pages.
 */

/**
 * Returns with the general configuration form.
 */
function chosen_admin_settings($form, &$form_state) {

  $chosen_path = chosen_get_chosen_path();
  if (!$chosen_path) {
    drupal_set_message(t('The library could not be detected. You need to download the !chosen and extract the entire contents of the archive into the %path directory on your server.',
    array('!chosen' => l(t('Chosen JavaScript file'), CHOSEN_WEBSITE_URL), '%path' => 'sites/all/libraries')
    ), 'error');
    return;
  }

  $form['chosen_minimum_single'] = array(
    '#type' => 'select',
    '#title' => t('Minimum number of options for single select'),
    '#options' => array_merge(array('0' => t('Always apply')), drupal_map_assoc(range(1, 25))),
    '#default_value' => variable_get('chosen_minimum_single', 20),
    '#description' => t('The minimum number of options to apply Chosen for single select fields. Example : choosing 10 will only apply Chosen if the number of options is greater or equal to 10.'),
  );

  $form['chosen_minimum_multiple'] = array(
    '#type' => 'select',
    '#title' => t('Minimum number of options for multi select'),
    '#options' => array_merge(array('0' => t('Always apply')), drupal_map_assoc(range(1, 25))),
    '#default_value' => variable_get('chosen_minimum_multiple', 20),
    '#description' => t('The minimum number of options to apply Chosen for multi select fields. Example : choosing 10 will only apply Chosen if the number of options is greater or equal to 10.'),
  );

  $form['chosen_disable_search_threshold'] = array(
    '#type' => 'select',
    '#title' => t('Minimum number to show Search on Single Select'),
    '#options' => array_merge(array('0' => t('Never apply')), drupal_map_assoc(range(1, 25))),
    '#default_value' => variable_get('chosen_disable_search_threshold', 0),
    '#description' => t('The minimum number of options to apply Chosen search box. Example : choosing 10 will only apply Chosen search if the number of options is greater or equal to 10.'),
  );

  $form['chosen_minimum_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum width of widget'),
    '#field_suffix' => 'px',
    '#required' => TRUE,
    '#size' => 3,
    '#default_value' => variable_get('chosen_minimum_width', 200),
    '#description' => t('The minimum width of the Chosen widget.'),
  );

  $form['chosen_jquery_selector'] = array(
    '#type' => 'textarea',
    '#title' => t('Apply Chosen to the following elements'),
    '#description' => t('A comma-separated list of jQuery selectors to apply Chosen to, such as <code>select#edit-operation, select#edit-type</code> or <code>.chosen-select</code>. Defaults to <code>select</code> to apply Chosen to all <code>&lt;select&gt;</code> elements.'),
    '#default_value' => variable_get('chosen_jquery_selector', 'select:visible'),
  );

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chosen options'),
  );
  $form['options']['chosen_search_contains'] = array(
    '#type' => 'checkbox',
    '#title' => t('Search also in the middle of words'),
    '#default_value' => variable_get('chosen_search_contains', FALSE),
    '#description' => t('Per default chosen searches only at beginning of words. Enable this option will also find results in the middle of words.
      Example: Search for <em>land</em> will also find <code>Switzer<strong>land</strong></code>.'),
  );
  $form['options']['chosen_disable_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable search box'),
    '#default_value' => variable_get('chosen_disable_search', FALSE),
    '#description' => t('Enable or disable the search box in the results list to filter out possible options.'),
  );
  $form['options']['chosen_use_theme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the default chosen theme'),
    '#default_value' => variable_get('chosen_use_theme', TRUE),
    '#description' => t('Enable or disable the default chosen CSS file. Disable this option if your theme contains custom styles for Chosen replacements.'),
  );

  $form['strings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chosen strings'),
  );
  $form['strings']['chosen_placeholder_text_multiple'] = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder text of multiple selects'),
    '#required' => TRUE,
    '#default_value' => variable_get('chosen_placeholder_text_multiple', 'Choose some options'),
  );
  $form['strings']['chosen_placeholder_text_single'] = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder text of single selects'),
    '#required' => TRUE,
    '#default_value' => variable_get('chosen_placeholder_text_single', 'Choose an option'),
  );
  $form['strings']['chosen_no_results_text'] = array(
    '#type' => 'textfield',
    '#title' => t('No results text'),
    '#required' => TRUE,
    '#default_value' => variable_get('chosen_no_results_text', 'No results match'),
  );

  return system_settings_form($form);
}
