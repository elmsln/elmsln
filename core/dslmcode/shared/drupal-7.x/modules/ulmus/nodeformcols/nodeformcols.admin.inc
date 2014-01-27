<?php

/**
 * @file
 * Contains the admin functions for Node form columns
 */

function _nodeformcols_get_node_type_form($type) {
  module_load_include('inc', 'node', 'node.pages');

  global $user;
  $node = new stdClass();
  $node->uid = $user->uid;
  $node->name = isset($user->name) ? $user->name : '';
  $node->type = $type;
  $node->language = '';
  $nfid = $type . '_node_form';
  $fs = array(
    'build_info' => array('args' => array($node)),
    'input' => array(),
  );
  $fs += form_state_defaults();
  $nf = drupal_retrieve_form($nfid, $fs);
  drupal_prepare_form($nfid, $nf, $fs);
  drupal_process_form($nfid, $nf, $fs);
  return $nf;
}

function nodeformcols_update_placements($type, $variant, &$placements) {
  $form = _nodeformcols_get_node_type_form($type);
  drupal_alter('nodeformcols_base_form', $form, $variant);
  $default_region = variable_get('nodeformcols_default_region', NODEFORMCOLS_DEFAULT_REGION);

  foreach (element_children($form) as $key) {
    $field = $form[$key];
    if (
      substr($key, 0, 8) == 'section_' ||
      (isset($field['#type']) && in_array($field['#type'], array('value', 'hidden', 'token'))) ||
      (isset($field['#type'], $field['#group']) && $field['#type'] === 'fieldset')
    ) {
      // Remove placements that meet exclusion rules.
      if (isset($placements[$key])) {
        unset($placements[$key]);
      }
      continue;
    }

    // Ensure a weight so that we don't have to worry about it later
    $field['#weight'] = isset($field['#weight']) ? $field['#weight'] : 0;

    if (!isset($placements[$key])) {
      // If the element is unknown we'll add it to
      // the field placement list
      $placements[$key] = array(
        'region' => $default_region,
        'weight' => $field['#weight'],
      );
      // Make sure that we don't auto-place the field below the buttons.
      if ($placements['actions']['region'] == $default_region && $placements[$key]['weight'] >= $placements['actions']['weight']) {
        $placements[$key]['weight'] = $placements['actions']['weight'] - .1;
      }
    }
    elseif (!isset($placements[$key]['weight'])) {
      $placements[$key]['weight'] = $field['#weight'];
    }

    $placements[$key]['has_required'] = _nodeformcols_has_required($field);

    // Get the element title
    $placements[$key]['title'] = _nodeformcols_get_element_title($field);

    if (isset($field['#collapsible']) && $field['#collapsible']) {
      if (!isset($placements[$key]['collapsed'])) {
        $placements[$key]['collapsed'] =  isset($field['#collapsed']) && $field['#collapsed'];
      }
    }
    else {
      unset($placements[$key]['collapsed']);
    }
  }

  // Remove fields that have disappeared from
  // the placements list.
  foreach ($placements as $key => $info) {
    if (!isset($form[$key])) {
      unset($placements[$key]);
    }
  }
}

function _nodeformcols_get_element_title($element) {
  if (!empty($element['#title'])) {
    return $element['#title'];
  }
  if (isset($element['#type']) && $element['#type'] == 'submit') {
    return $element['#value'];
  }
  if (isset($element['#type']) && $element['#type'] == 'vertical_tabs') {
    return t('Vertical tabs');
  }
  foreach (element_children($element) as $key) {
    if ($title = _nodeformcols_get_element_title($element[$key])) {
      return $title;
    }
  }
}

function nodeformcols_configuration_form($form, $form_state, $node_type, $variant = 'default') {
  $type = $node_type->type;
  $variants = array();
  drupal_alter('nodeformcols_variants', $variants, $type);

  $form = array();
  if (!empty($variants)) {
    $variant_links = array(
      'default' => array(
        'title' => t('Default'),
        'href' => 'admin/structure/types/manage/' . $type . '/form',
      ),
    );
    foreach ($variants as $id => $title) {
      $variant_links[] = array(
        'title' => $title,
        'href' => 'admin/structure/types/manage/' . $type . '/form/' . $id,
      );
    }

    $form['variant'] = array(
      '#type' => 'item',
      '#title' => t('Select a form variant'),
      '#value' => theme('links', array('links' => $variant_links)),
    );
  }

  if (empty($variant)) {
    $variant = 'default';
  }
  $form['#variant'] = $variant;

  $placements = nodeformscols_field_placements($type, $variant);
  nodeformcols_update_placements($type, $variant, $placements);

  $regions = nodeformcols_form_regions();

  $form['type'] = array(
    '#type' => 'value',
    '#value' => $type,
  );
  $form['#after_build'][] = '_nodeformcols_configuration_form_after_build';
  $form['conf'] = array(
    '#theme' => array('nodeformcols_configuration'),
  );

  foreach ($placements as $name => $info) {
    $key = 'field_' . $name;
    $weight = isset($info['weight']) ? $info['weight'] : 0;
    $form['conf'][$info['region']][$key] = array(
      '#weight' => $weight,
      $key . '_name' => array(
        '#markup' => !empty($info['title']) ? $info['title'] : $name,
      ),
      $key . '_region' => array(
        '#type' => 'select',
        '#options' => $regions,
        '#default_value' => $info['region'],
        '#attributes' => array(
          'class' => array('field-region-select field-region-' . $info['region']),
        ),
      ),
      $key . '_weight' => array(
        '#type' => 'textfield',
        '#default_value' => $weight,
        '#size' => 3,
        '#attributes' => array(
          'class' => array('field-weight field-weight-' . $info['region']),
        ),
      ),
    );

    if (!$info['has_required']) {
      $form['conf'][$info['region']][$key][$key . '_hidden'] = array(
        '#type' => 'checkbox',
        '#title' => t('Hide'),
        '#default_value' => isset($info['hidden']) ? $info['hidden'] : FALSE,
      );
    }

    if (isset($info['collapsed'])) {
      $form['conf'][$info['region']][$key][$key . '_collapsed'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show collapsed'),
        '#default_value' => isset($info['collapsed']) ? $info['collapsed'] : FALSE,
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Checks if a form element or any of it's children are required
 *
 * @param array $element
 * @return bool
 */
function _nodeformcols_has_required($element) {
  if (isset($element['#required']) && $element['#required']) {
    return TRUE;
  }
  $children = element_children($element);
  foreach ($children as $child) {
    if (_nodeformcols_has_required($element[$child])) {
      return TRUE;
    }
  }
  return FALSE;
}

function _nodeformcols_configuration_form_after_build($form) {
  drupal_add_js('misc/tableheader.js');
  drupal_add_js(drupal_get_path('module', 'nodeformcols') . '/js/nodeformcols.js');
  drupal_add_css(drupal_get_path('module', 'nodeformcols') . '/css/nodeformcols.admin.css');

  $regions = nodeformcols_form_regions();
  foreach ($regions as $region => $title) {
    if (isset($form['conf'][$region]) && is_array($form['conf'][$region])) {
      uasort($form['conf'][$region], "element_sort");
    }
    drupal_add_tabledrag('fields', 'match', 'sibling', 'field-region-select', 'field-region-' . $region, NULL, FALSE);
    drupal_add_tabledrag('fields', 'order', 'sibling', 'field-weight', 'field-weight-' . $region);
  }
  return $form;
}

function nodeformcols_configuration_form_submit($form, $form_state) {
  $values = $form_state['values'];
  $type = $values['type'];
  $placements = nodeformscols_field_placements($type, $form['#variant']);
  nodeformcols_update_placements($type, $form['#variant'], $placements);

  foreach ($placements as $name => &$opt) {
    $field = 'field_' . $name;
    $opt['region'] = $values[$field . '_region'];
    $opt['weight'] = $values[$field . '_weight'];
    if (isset($values[$field . '_hidden'])) {
      $opt['hidden'] = $values[$field . '_hidden'];
    }
    if (isset($values[$field . '_collapsed'])) {
      $opt['collapsed'] = $values[$field . '_collapsed'];
    }
  }

  variable_set('nodeformscols_field_placements_' . $type .
    '_' . $form['#variant'], $placements);
}
