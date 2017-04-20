<?php

/**
 * @file
 * Theme callbacks for the scanner module.
 */

/**
 * Theme the search results.
 */
function theme_scanner_results($variables) {
  $results = $variables['results'];
  $output = NULL;
  if (is_array($results)) {
    $total = count($results);

    drupal_set_message(filter_xss('Found matches in ' . $total . ' fields. <a href="#results">See below</a> for details.', $allowed_tags = array('a')));
    $output = '<p>Found matches in ' . $total . ' fields:</p>';
    $output .= '<ol class="scanner-results scanner-search-results">';
    foreach ($results as $item) {
      $output .= theme('scanner_item', array('item' => $item));
    }
    $output .= '</ol>';
    // TODO: use pager to split up results
  }
  else {
    drupal_set_message(t('No matches found. Check the !url for fields that can be searched.', array('!url' => l(t('settings'), 'admin/content/scanner/settings'))), 'warning');
  }

  return $output;
}

/**
 * Theme each search result hit.
 */
function theme_scanner_item($variables) {
  $output = '';
  $item = $variables['item'];
  $item['count'] = $item['count'] > 0 ? $item['count'] : 'One or more';
  $output .= '<li class="scanner-result">';
  $output .=   '<span class="scanner-title">' . l($item['title'], 'node/' . $item['nid']) . '</span><br />';
  $output .=   '<span class="scanner-info">[' . $item['count'] . ' matches in ' . $item['type'] . ' ' . $item['field_label'] . ' field:]</span><br />';
  $output .=   '<span class="scanner-text">' . $item['text'] . '</span>';
  $output .= '</li>';

  return $output;
}

/**
 * Theme the replace results.
 */
function theme_scanner_replace_results($variables) {
  $results = $variables['results'];
  $output = '';
  if (is_array($results)) {
    drupal_set_message(filter_xss('Replaced items in ' . count($results) . ' fields. <a href="#results">See below</a> for details.', $allowed_tags = array('a')));
    $output = '<p>Replaced items in ' . count($results) . ' fields:</p>';
    $output .= '<ol class="scanner-results scanner-replace-results">';
    foreach ($results as $item) {
      $output .= theme('scanner_replace_item', array('item' => $item));
    }
    $output .= '</ol>';
    // TODO: use pager to split up results
  }
  else {
    drupal_set_message(t('No matches found. Check the !url for fields that can be searched.', array('!url' => l(t('settings'), 'admin/content/scanner/settings'))), 'warning');
  }

  return $output;
}

/**
 * Theme each replace result hit.
 */
function theme_scanner_replace_item($variables) {
  $output = '';
  $item = $variables['item'];
  $item['count'] = $item['count'] > 0 ? $item['count'] : 'One or more';
  $output .= '<li class="scanner-result">';
  $output .=   '<span class="scanner-title">' . l($item['title'], 'node/' . $item['nid']) . '</span><br />';
  $output .=   '<span class="scanner-info">[' . $item['count'] . ' replacements in ' . $item['type'] . ' ' . $item['field_label'] . ' field]</span>';
  $output .= '</li>';

  return $output;
}
