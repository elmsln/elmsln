<?php
/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 */

/**
 * Implementation of hook_ckeditor_link_TYPE_autocomplete().
 */
function ckeditor_link_ckeditor_link_i18n_taxonomy_autocomplete($string, $limit) {
  // Currently, this function only supports MySQL.
  // TODO: Add support for pgsql.
  if (!in_array(db_driver(), array('mysql'))) {
    return array();
  }

  $matches = array();

  $vocabularies = array_keys(array_filter(variable_get('ckeditor_link_autocomplete_vocabularies', array())));
  if (count($vocabularies)) {
    $query = db_select('taxonomy_term_data', 't');
    $query->innerJoin('locales_source', 'ls', 'ls.context = CONCAT(:prefix, t.tid, :suffix)', array(':prefix' => 'term:', ':suffix' => ':name'));
    $query->innerJoin('locales_target', 'lt', 'lt.lid = ls.lid');
    $query->fields('t', array('tid'));
    $query->addExpression('CONVERT(lt.translation USING utf8)', 'name');
    $query->fields('lt', array('language'));
    $query->where('CONVERT(lt.translation USING utf8) LIKE :pattern', array(':pattern' => '%'. db_like($string) .'%'));
    $query->orderBy('name');
    $query->range(0, $limit);
    $query->addTag('term_access');
    if (!in_array('- any -', $vocabularies)) {
      $query->condition('t.vid', $vocabularies, 'IN');
    }
    $result = $query->execute();
    foreach ($result as $term) {
      $path = ckeditor_link_path_prefix_language('taxonomy/term/'. $term->tid, $term->language);
      $matches[$path] = $term->name;
    }
  }

  return $matches;
}

/**
 * Implementation of hook_ckeditor_link_TYPE_revert().
 */
function ckeditor_link_ckeditor_link_i18n_taxonomy_revert($path, &$langcode) {
  if (!preg_match('`^taxonomy/term/(\d+)$`', $path, $matches)) {
    return;
  }

  $tid = $matches[1];
  $result = db_select('taxonomy_term_data', 't')
    ->fields('t', array('tid', 'vid', 'name', 'language'))
    ->condition('t.tid', $tid)
    ->addTag('term_access')
    ->execute();
  if ($term = $result->fetchObject()) {
    if ($term->language == LANGUAGE_NONE) {
      return i18n_taxonomy_term_name($term, $langcode);
    }
    else {
      $langcode = LANGUAGE_NONE;
      return $term->name;
    }
  }

  return FALSE;
}
