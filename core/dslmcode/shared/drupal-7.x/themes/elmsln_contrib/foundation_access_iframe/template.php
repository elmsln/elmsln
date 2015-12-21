<?php
/**
 * Implements template_process_page.
 */
function foundation_access_iframe_process_page(&$variables) {
  // remove the "Home" button when in iframe mode
  $keys = array_keys($variables['page']['header']);
  $keyname = array_shift($keys);
  unset($variables['page']['header'][$keyname]['#prefix']);
}
