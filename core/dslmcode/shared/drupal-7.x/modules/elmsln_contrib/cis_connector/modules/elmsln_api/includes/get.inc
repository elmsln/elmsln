<?php
/**
 * @file
 * get.inc
 */

/**
 * Handler for JS GET requests.
 *
 * @return array|int
 *   The render array for the system_main page contents or an integer if an
 *   error occurred.
 */
function elmsln_api_get_page() {
  global $_elmsln;

  // To avoid having to reinitialize most of Drupal to return the correct
  // page request, the bootstrap state remains as minimal as possible until
  // we reach this point so we can override the necessary server sent variables
  // with the real requested path. After that has occurred, Drupal can be
  // fully bootstrapped.
  $path = implode('/', $_elmsln['args']);
  $_GET['q'] = $path;
  if (isset($_SERVER['REQUEST_URI'])) {
    $_SERVER['REQUEST_URI'] = '/' . $path;
  }
  else {
    if (isset($_SERVER['argv'])) {
      $_SERVER['argv'][0] = $path;
    }
    elseif (isset($_SERVER['QUERY_STRING'])) {
      $_SERVER['QUERY_STRING'] = 'q=' . $path;
    }
  }

  // At this point we can fully bootstrap Drupal safely.
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

  // Retrieve the results for the active menu handler. This is identical to
  // index.php, expect that we do not deliver the page here. The results must
  // be rendered manually below so we just return the main content for the page.
  $page = menu_execute_active_handler(NULL, FALSE);

  // If the result is an integer (error), return it immediately so JS module can
  // deliver the proper JSON results.
  if (is_int($page)) {
    if ($page === ELMSLN_MENU_NOT_FOUND) {
      drupal_set_message(t('The requested URL "!url" could not be found.', array(
        '!url' => url(current_path()),
      )), 'error', FALSE);
    }
    elseif ($page === ELMSLN_MENU_ACCESS_DENIED) {
      drupal_set_message(t('You are not authorized to access the requested URL "!url".', array(
        '!url' => url(current_path()),
      )), 'error', FALSE);
    }
    return $page;
  }

  // The result was successful. The contents of this request must be rendered
  // here to mimic what Drupal normally returns. This code is almost identical
  // to drupal_render_page(), except that it only renders the "system_main"
  // section of the page and nothing else.
  // @see drupal_render_page()
  $main_content_display = &drupal_static('system_main_content_added', FALSE);
  if (is_string($page) || (is_array($page) && (!isset($page['#type']) || ($page['#type'] != 'page')))) {
    drupal_set_page_content($page);
    $page = element_info('page');
  }
  foreach (module_implements('page_build') as $module) {
    $function = $module . '_page_build';
    $function($page);
  }
  drupal_alter('page', $page);
  if (!$main_content_display) {
    $page['content']['system_main'] = drupal_set_page_content();
  }
  // Remove the "block" theme wrapper. This prevents a duplicate "system main"
  // block from appearing while still rendering the content inside it.
  if (isset($page['content']['system_main']['#theme_wrappers']) && ($key = array_search('block', $page['content']['system_main']['#theme_wrappers']))) {
    unset($page['content']['system_main']['#theme_wrappers'][$key]);
  }
  return $page['content']['system_main'];
}
