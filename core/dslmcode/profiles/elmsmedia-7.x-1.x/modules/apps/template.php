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

/**
 * Implements template_field__field_accessible_fallback.
 */
function foundation_access_iframe_field__field_accessible_fallback(&$variables) {
  if (isset($variables['element']['#object']->nid)) {
    if ($variables['element']['#formatter'] == 'entityreference_entity_id') {
      return l(t('Enable more accessible form of this media.'), 'entity_iframe/node/' . $variables['element']['#object']->nid . '/accessible_fallback', array('attributes' => array('icon' => 'accessibility')));
    }
    else {
      print l(t('Switch to more interactive form of this media.'), 'entity_iframe/node/' . $variables['element']['#object']->nid, array('attributes' => array('icon' => 'touch-app')));
    }
  }
}

