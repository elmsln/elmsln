<?php
/**
 * Implements template_process_page.
 */
function foundation_access_iframe_process_page(&$variables) {
  // remove the "Home" button when in iframe mode if its there
  if (isset($variables['page']['header'])) {
    $keys = array_keys($variables['page']['header']);
    $keyname = array_shift($keys);
    unset($variables['page']['header'][$keyname]['#prefix']);
  }
}
