<?php

/**
 * Override or insert variables into page templates.
 */
function adaptivetheme_admin_preprocess_page(&$vars) {
  // RFC2822 date format
  if ($rfc = date("r" , time())) {
    $vars['datetime_rfc'] = t('@time', array('@time' => $rfc));
  }
  else {
    $rfc = '';
    $vars['datetime_rfc'] = '';
  }
  // ISO 8601 date format
  if ($iso = gmdate('Y-m-d\TH:i:sO')) {
    $vars['datetime_iso'] = $iso;
  }
  else {
    $iso = '';
    $vars['datetime_iso'] = '';
  }
  
  $vars['content_header_attributes_array']['class'][] = 'branding-elements';
  $vars['content_header_attributes_array']['role'][] = 'banner';
}

/**
 * Alter the search block form.
 */
function adaptivetheme_admin_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_block_form') {
    $form['search_block_form']['#title'] = t('Search');
    $form['search_block_form']['#title_display'] = 'invisible';
    $form['search_block_form']['#size'] = 20;
    $form['search_block_form']['#attributes']['placeholder'] = t('Search');
    $form['actions']['submit']['#value'] = t('Go');
  }
}
