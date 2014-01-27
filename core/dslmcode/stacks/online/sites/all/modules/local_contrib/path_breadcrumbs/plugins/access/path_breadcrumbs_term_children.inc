<?php
/**
 * @file
 * Plugin to provide access control based on children terms.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Taxonomy: term has children"),
  'description' => t('Control access if a term has a specific child term.'),
  'callback' => 'path_breadcrumbs_term_has_children_ctools_access_check',
  'default' => array('vid' => array(), 'negate' => 0),
  'settings form' => 'path_breadcrumbs_term_has_children_ctools_access_settings',
  'settings form submit' => 'path_breadcrumbs_term_has_children_ctools_access_submit',
  'summary' => 'path_breadcrumbs_term_has_children_ctools_access_summary',
  'required context' => new ctools_context_required(t('Term'), array('taxonomy_term', 'terms')),
);

/**
 * Settings form for the 'Taxonomy: term has children' access plugin.
 */
function path_breadcrumbs_term_has_children_ctools_access_settings($form, &$form_state, $conf) {
  // If no configuration was saved before, set some defaults.
  if (empty($conf)) {
    $conf = array(
      'vid' => 0,
    );
  }
  if (!isset($conf['vid'])) {
    $conf['vid'] = 0;
  }

  $form['settings']['vid'] = array(
    '#title' => t('Vocabulary'),
    '#type' => 'select',
    '#options' => array(),
    '#description' => t('Select the vocabulary for this form.'),
    '#id' => 'ctools-select-vid',
    '#default_value' => $conf['vid'],
    '#required' => TRUE,
  );

  ctools_include('dependent');
  $options = array();

  // A note: Dependency works strangely on these forms as they have never been
  // updated to a more modern system so they are not individual forms of their
  // own like the content types.
  $form['settings']['#tree'] = TRUE;

  // Loop over each of the configured vocabularies.
  foreach (taxonomy_get_vocabularies() as $vid => $vocabulary) {
    $options[$vid] = $vocabulary->name;
    $form['settings']['vid_' . $vid] = array(
      '#type' => 'fieldset',
      '#title' => t('Select a term or terms from @vocabulary.', array('@vocabulary' => $vocabulary->name)),
      '#dependency' => array('ctools-select-vid' => array($vocabulary->vid)),
    );

    $term_groups = array();
    $current_parent_tid = 0;
    foreach (taxonomy_get_tree($vocabulary->vid) as $term) {
      if ($term->depth == 0) {
        $current_parent_tid = $term->tid;
        $term_groups[$current_parent_tid]['parent_name'] = $term->name;
        $term_groups[$current_parent_tid]['children'] = array();
      }
      else {
        $term_groups[$current_parent_tid]['children'][$term->tid] = str_repeat('-', $term->depth) . ($term->depth ? ' ' : '') . $term->name;
      }
    }

    foreach ($term_groups as $parent_tid => $group) {
      if (!count($group['children'])) {
        continue;
      }

      $form['settings']['vid_' . $vid]['parent_' . $parent_tid] = array(
        '#prefix' => '<strong>' . $group['parent_name'] . '</strong>',
        '#type' => 'checkboxes',
        '#default_value' => !empty($conf['vid_' . $vid]) ? $conf['vid_' . $vid] : '',
        '#size' => 10,
      );
      $form['settings']['vid_' . $vid]['parent_' . $parent_tid]['#options'] = $group['children'];
    }

  }
  $form['settings']['vid']['#options'] = $options;

  $form['settings']['include_self'] = array(
    '#title' => t('Include these term(s) as candidates?'),
    '#description' => t('When this rule is evaluated, should the term(s) you select be included as candidates for access?'),
    '#default_value' => !empty($conf['include_self']) ? $conf['include_self'] : FALSE,
    '#type' => 'checkbox',
  );

  return $form;
}

/**
 * Filters values to store less.
 */
function path_breadcrumbs_term_has_children_ctools_access_submit($form, &$form_state) {

  foreach ($form_state['values']['settings'] as $key => $value) {
    if (strpos($key, 'vid_') === 0) {
      $tids = array();
      foreach ($form_state['values']['settings'][$key] as $children) {
        $tids += array_filter($children);
      }
      $form_state['values']['settings'][$key] = $tids;
    }
  }

}

/**
 * Check for access.
 */
function path_breadcrumbs_term_has_children_ctools_access_check($conf, $context) {
  if (empty($context) || empty($context->data) || empty($context->data->vid) || empty($context->data->tid)) {
    return FALSE;
  }

  // Get the $vid.
  if (!isset($conf['vid'])) {
    return FALSE;
  }
  $vid = $conf['vid'];

  // We'll start looking up the hierarchy from our context term id.
  $current_term = $context->data->tid;

  // Check the term selected, if the user asked it to.
  if (!empty($conf['include_self']) && isset($conf['vid_' . $vid][$current_term])) {
    return TRUE;
  }

  foreach ($conf['vid_' . $conf['vid']] as $child_tid) {
    $tid = $child_tid;

    while ($parents = taxonomy_get_parents($tid)) {
      $parent = reset($parents);
      if ($parent->tid == $current_term) {
        return TRUE;
      }

      $tid = $parent->tid;
    }
  }

  return FALSE;
}

/**
 * Provide a summary description based upon the checked terms.
 */
function path_breadcrumbs_term_has_children_ctools_access_summary($conf, $context) {
  $vid = (int) $conf['vid'];
  $terms = array();
  foreach ($conf['vid_' . $vid] as $tid) {
    $term = taxonomy_term_load($tid);
    $terms[] = $term->name;
  }

  return format_plural(count($terms),
    '@term has child "@terms"',
    '@term has one of these children: @terms',
    array(
      '@terms' => implode(', ', $terms),
      '@term' => $context->identifier,
    )
  );
}
