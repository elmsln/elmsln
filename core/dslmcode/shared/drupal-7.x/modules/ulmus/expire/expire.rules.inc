<?php

/**
 * @file
 * Integration with the rules module
 */

/**
 * Implementation of hook_rules_action_info().
 *
 * @ingroup rules
 */
function expire_rules_action_info() {
  return array(
    'expire_flush_url' => array(
      'base' => 'expire_rules_action_flush_url',
      'label' => t('Clear URL(s) from the page cache.'),
      'parameter' => array(
        'urls' => array(
          'type' => 'text',
          'label' => t('URL of page to clear'),
          'description' => t('Full URL (including http://); node/8; taxonomy/term/3; user/5; path alias; & <front> will work. One Per line.'),
        ),
      ),
      'group' => 'Expire',
    ),
  );
}

/**
 * Expire a URL from the page cache.
 */
function expire_rules_action_flush_url($urls, $settings) {
  global $base_root, $base_path;
  $urls = preg_replace("/\r\n/", "\n", $urls);
  $urls = explode("\n", $urls);
  $urls = array_map('trim', $urls);
  $urls = array_filter($urls);
  $urls_parsed = array_map('parse_url', $urls);

  // Figure out what kind of URL's these are and act accordingly.
  $full_urls = array();
  $bad_paths = array();
  $internal = array();
  foreach ($urls_parsed as $key => $parts) {
    if (!empty($parts['host'])) {
      $full_urls[] = $urls[$key];
    }
    elseif (!empty($parts['path'])) {
      // Strip base path from path.
      $parts['path'] = preg_replace('/^' . preg_quote($base_path, '/') .'/i', '', $parts['path']);
      if (empty($parts['path']) || $parts['path'] == '<front>') {
        $internal[$key] = variable_get('site_frontpage', 'node');
      }
      else {
        $normal = expire_normal_path_check($parts['path']);
        if (is_array($normal)) {
          $internal[$key] = $urls[$key];
        }
        else {
          $normal = drupal_get_normal_path($parts['path']);
          if ($normal == $parts['path']) {
            // Bad path given
            $bad_paths[$key] = $urls[$key];
          }
          else {
            $internal[$key] = $normal;
          }
        }
      }
    }
  }

  if (!empty($bad_paths)){
    watchdog('expire', 'Bad URL(s) given. !url do not match any given paths or aliases', array('!url' => expire_print_r($bad_paths)));
  }

  // Process internal paths
  foreach ($internal as $key => $path) {
    $arg = arg(NULL, $path);
    if ($arg[0] == 'node' && !empty($arg[1]) && is_numeric($arg[1])) {
      $node = node_load($arg[1]);
      expire_node($node);
      unset($internal[$key]);
    }
  }
  if (!empty($internal)) {
    $flushed = expire_cache_derivative($internal);
  }

  // Process Full URLs
  // hook_expire_cache
  $modules = module_implements('expire_cache');
  foreach ($modules as $module) {
    module_invoke($module, 'expire_cache', $full_urls);
  }
  watchdog('expire', 'Output: !urls <br /> Modules Using hook_expire_cache(): !modules', array(
    '!urls' => expire_print_r($full_urls),
    '!modules' => expire_print_r($modules),
  ));

}
