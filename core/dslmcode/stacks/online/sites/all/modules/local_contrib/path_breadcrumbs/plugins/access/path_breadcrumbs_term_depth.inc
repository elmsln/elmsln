<?php
/**
 * @file
 * Plugin to provide access control based on term depth.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Taxonomy: term depth"),
  'description' => t('Control access by the depth of a term.'),
  'callback' => 'path_breadcrumbs_term_depth_ctools_access_check',
  'default' => array('depth' => 0, 'operator' => '='),
  'settings form' => 'path_breadcrumbs_term_depth_ctools_access_settings',
  'settings form validate' => 'path_breadcrumbs_term_depth_ctools_access_validate',
  'summary' => 'path_breadcrumbs_term_depth_ctools_access_summary',
  'required context' => new ctools_context_required(t('Term'), array('taxonomy_term', 'terms')),
);

/**
 * Settings form for the 'Taxonomy: term depth' access plugin.
 */
function path_breadcrumbs_term_depth_ctools_access_settings($form, &$form_state, $conf) {

  $form['settings']['operator'] = array(
    '#title' => t('Operator'),
    '#type' => 'select',
    '#default_value' => $conf['operator'],
    '#options' => _path_breadcrumbs_term_depth_operators(),
    '#required' => TRUE,
  );

  $form['settings']['depth'] = array(
    '#title' => t('Depth'),
    '#type' => 'textfield',
    '#description' => t('Set the required depth (integer >=1) of the term. If the term exists at the right depth, this access check will succeed.'),
    '#default_value' => $conf['depth'],
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Validate callback for settings form.
 */
function path_breadcrumbs_term_depth_ctools_access_validate(&$form, &$form_state) {
  $element = $form['settings']['depth'];
  element_validate_integer_positive($element, $form_state);
}

/**
 * Check for access.
 */
function path_breadcrumbs_term_depth_ctools_access_check($conf, $context) {
  if (empty($context) || empty($context->data) || empty($context->data->vid) || empty($context->data->tid)) {
    return FALSE;
  }

  $depth = _path_breadcrumbs_term_depth($context->data->tid);

  switch ($conf['operator']) {
    case '<=':
      if ($depth <= $conf['depth']) {
        return TRUE;
      }
      break;

    case '>=':
      if ($depth >= $conf['depth']) {
        return TRUE;
      }
      break;

    case '=':
    default:
      if ($depth == $conf['depth']) {
        return TRUE;
      }
  }

  return FALSE;
}

/**
 * Provide a summary description.
 */
function path_breadcrumbs_term_depth_ctools_access_summary($conf, $context) {
  return t('@term depth %operator @depth', array(
    '@term' => $context->identifier,
    '%operator' => drupal_strtolower(_path_breadcrumbs_term_depth_operators($conf['operator'])),
    '@depth' => $conf['depth'],
  ));
}

/**
 * Find the depth of a term.
 */
function _path_breadcrumbs_term_depth($tid) {
  static $depths = array();

  if (!isset($depths[$tid])) {
    $parent = db_select('taxonomy_term_hierarchy', 'th')
      ->fields('th', array('parent'))
      ->condition('tid', $tid)
      ->execute()->fetchField();

    if ($parent == 0) {
      $depths[$tid] = 1;
    }
    else {
      $depths[$tid] = 1 + _path_breadcrumbs_term_depth($parent);
    }
  }

  return $depths[$tid];
}

/**
 * Available comparison operators.
 */
function _path_breadcrumbs_term_depth_operators($operator = NULL) {
  $operators = array(
    '=' => t('Is equal to'),
    '<=' => t('Is less than or equal to'),
    '>=' => t('Is greater than or equal to'),
  );

  if (isset($operator)) {
    return $operators[$operator];
  }

  return $operators;
}
