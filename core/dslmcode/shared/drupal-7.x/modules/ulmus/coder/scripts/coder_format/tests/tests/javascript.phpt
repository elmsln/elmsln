<?php
TEST: JavaScript

--INPUT--
function _locale_rebuild_js($langcode = NULL) {
  if (!empty($translations)) {

    $data = "Drupal.locale = { ";

    if (!empty($language->formula)) {
      $data .= "'pluralFormula': function(\$n) { return Number({$language->formula}); }, ";
    }

    $data .= "'strings': ". drupal_to_js($translations) ." };";
    $data_hash = md5($data);
  }
}

