<?php

/**
 * Implements hook_form_alter().
 */
function zurb_foundation_form_alter(&$form, &$form_state, $form_id) {
  // Id's of forms that should be ignored
  $form_ids = array(
    'node_form',
    'system_site_information_settings',
    'user_profile_form',
    'node_delete_confirm',
    'views_ui_edit_form',
  );

  // Allow other modules to alter this.
  drupal_alter('zurb_foundation_ignored_forms', $form_ids);

  // Only wrap in container for certain form
  if (isset($form['#form_id']) && !in_array($form['#form_id'], $form_ids) && !isset($form['#node_edit_form'])) {
    $form['actions']['#theme_wrappers'] = array();
  }

  // Sexy submit buttons
  if (!empty($form['actions']) && !empty($form['actions']['submit'])) {
    $form['actions']['submit']['#attributes']['class'] []= 'secondary';
    $form['actions']['submit']['#attributes']['class'] []=  'button';
    $form['actions']['submit']['#attributes']['class'] []=  'radius';
  }

  // Search Block Fixes
  if (isset($form['#form_id']) && ($form['#form_id'] == 'search_block_form')) {
    $form['search_block_form'] += array(
      '#prefix' => '<div class="row collapse"><div class="small-8 columns">',
      '#suffix' => '</div>',
    );
    $form['actions']['submit'] += array(
      '#prefix' => '<div class="small-4 columns">',
      '#suffix' => '</div></div>',
    );
    $form['actions']['submit']['#attributes']['class'] []= 'postfix';
    $form['actions']['submit']['#attributes']['class'] []= 'expand';
  }

  // Mantain compatibility with Quick Edit module.
  if ($form_id === 'quickedit_field_form') {
    $form['actions']['submit']['#attributes']['class'][] = 'quickedit-form-submit';
  }

  // Add tooltips to form elements.
  if (theme_get_setting('zurb_foundation_tooltip_enable')
    && theme_get_setting('zurb_foundation_tooltip_mode') === 'element') {
    // Get tooltip settings.
    $position = theme_get_setting('zurb_foundation_tooltip_position');
    $touch = theme_get_setting('zurb_foundation_tooltip_touch');

    foreach (element_children($form) as $item) {
      foreach (element_children($form[$item]) as $i) {
        $element =& $form[$item][$i];

        if (!empty($element['#description'])) {
          $element['#attributes']['data-tooltip'] = NULL;
          $element['#attributes']['class'][] = 'has-tip';
          $element['#attributes']['class'][] = $position;
          $element['#attributes']['title'] = $element['#description'];

          if ($touch) {
            $element['#attributes']['data-options'] = 'disable-for-touch:true';
          }
        }
      }
    }
  }
}

/**
 * Implements theme_form_element_label().
 */
function zurb_foundation_form_element_label($variables) {
  // Add tooltips to form elements.
  if (theme_get_setting('zurb_foundation_tooltip_enable')) {
    _zurb_foundation_add_tooltips($variables);
  }
  return theme_form_element_label($variables);
}

/**
 * Implements theme_text_format_wrapper().
 */
function zurb_foundation_text_format_wrapper($variables) {
  // Add tooltips to form elements.
  if (theme_get_setting('zurb_foundation_tooltip_enable')) {
    _zurb_foundation_add_tooltips($variables);
  }
  return theme_text_format_wrapper($variables);
}

/**
 * Implements theme_field_multiple_value_form().
 */
function zurb_foundation_field_multiple_value_form($variables) {
  // Add tooltips to form elements.
  if (theme_get_setting('zurb_foundation_tooltip_enable')) {
    _zurb_foundation_add_tooltips($variables);
  }
  return theme_field_multiple_value_form($variables);
}

/**
 * Modifies description to display the description in a tooltip.
 */
function _zurb_foundation_add_tooltips(&$variables) {
  if (!empty($variables['element']['#title']) && !empty($variables['element']['#description'])) {
    $text = theme_get_setting('zurb_foundation_tooltip_text');
    $position = theme_get_setting('zurb_foundation_tooltip_position');
    $touch = theme_get_setting('zurb_foundation_tooltip_touch') ? 'data-options="disable-for-touch:true"' : '';
    if (theme_get_setting('zurb_foundation_tooltip_mode') === 'element') {
      // Not sure whats up with the colon. Probably a JSON issue.
      $safe_text = str_replace(':', '', check_plain(strip_tags($variables['element']['#description'])));
      $variables['element']['#title'] = '<label>' . ' <span data-tooltip ' . $touch . 'class="has-tip ' . $position . '" title="' . $safe_text . '">' . $variables['element']['#title'] . '</span>' . '</label>';
      $variables['element']['#description'] = '';
    } else {
      $variables['element']['#title'] = '<label>' . $variables['element']['#title'] . '</label>';
      $variables['element']['#description'] = ' <span data-tooltip ' . $touch . 'class="has-tip ' . $position . '" title="' . check_plain(strip_tags($variables['element']['#description'])) . '">' . t($text) . '</span>';
    }
  }
}

/**
 * Returns HTML for a button form element.
 */
function zurb_foundation_button($variables) {
  $element = $variables['element'];
  $label = check_plain($element['#value']);
  element_set_attributes($element, array('id', 'name', 'value', 'type'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  // Prepare input whitelist - added to ensure ajax functions don't break
  $whitelist = _zurb_foundation_element_whitelist();

  if (isset($element['#id']) && in_array($element['#id'], $whitelist)) {
    return '<input' . drupal_attributes($element['#attributes']) . ">\n"; // This line break adds inherent margin between multiple buttons
  }
  else {
    return '<button' . drupal_attributes($element['#attributes']) . '>'. $label ."</button>\n"; // This line break adds inherent margin between multiple buttons
  }
}

/**
 * Returns an array containing ids of any whitelisted drupal elements
 */
function _zurb_foundation_element_whitelist() {
/**
 * Why whitelist an element?
 * The reason is to provide a list of elements we wish to exclude
 * from certain modifications made by the bootstrap theme which
 * break core functionality - e.g. ajax.
 */
  $whitelist = array(
    'edit-refresh',
    'edit-pass-pass1',
    'edit-pass-pass2',
    'panels-ipe-cancel',
    'panels-ipe-customize-page',
    'panels-ipe-save',
    'panelizer-save-default',
    'panelizer-ipe-revert',
  );

  // Allow other modules and themes to alter return value.
  drupal_alter('zurb_foundation_element_whitelist', $whitelist);

  return $whitelist;
}
