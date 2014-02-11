<?php
/**
 * @file
 * Contextual links module integration.
 */

/**
 * Implements hook_custom_formatters_form_alter_alter() on behalf of
 * contextual.module.
 */
function contextual_custom_formatters_form_alter_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'custom_formatters_settings_form') {
    $settings = variable_get('custom_formatters_settings', array('contextual' => 1));

    $form['settings']['contextual'] = array(
      '#type' => 'radios',
      '#title' => t('Contextual links integration'),
      '#default_value' => isset($settings['contextual']) ? $settings['contextual'] : 1,
      '#options' => array(
        0 => t('Disabled'),
        1 => t('Enabled on all Formatters except those listed'),
        2 => t('Enabled on only the listed Formatters'),
      ),
    );

    $form['settings']['contextual_list'] = array(
      '#type' => 'textarea',
      '#default_value' => isset($settings['contextual_list']) ? $settings['contextual_list'] : '',
      '#description' => t('Specify Formatters by using their machine names. Enter one machine name per line.'),
      '#states' => array(
        'visible' => array(
          'input[name="settings[contextual]"]' => array('checked' => FALSE),
        ),
      ),
    );
  }
}

/**
 * Implements hook_custom_formatters_field_formatter_view_element_alter() on
 * behalf of contextual.module.
 *
 * Adds contextual links to Custom Formatter fields.
 */
function contextual_custom_formatters_field_formatter_view_element_alter(&$element, $formatter) {
  if (_custom_formatters_contextual_access($formatter->name, $element)) {
    foreach (element_children($element) as $delta) {
      $element[$delta] = array(
        'markup' => $element[$delta],
        'contextual_links' => array(
          '#type' => 'contextual_links',
          '#contextual_links' => array('custom_formatters' => array('admin/structure/formatters/list', array($formatter->name, 'edit'))),
          '#element' => $element[$delta],
        ),
        '#prefix' => '<div class="contextual-links-region">',
        '#suffix' => '</div>',
      );
    }
  }
}

function _custom_formatters_contextual_access($name, $element) {
  if (isset($element[0]['#cf_options']['#contextual_links']) && $element[0]['#cf_options']['#contextual_links'] == FALSE) {
    return FALSE;
  }

  $user_access = user_access('access contextual links') && user_access('administer custom formatters');
  if (!$user_access) {
    return FALSE;
  }

  $settings = variable_get('custom_formatters_settings', array('contextual' => 1));
  $contextual = isset($settings['contextual']) ? $settings['contextual'] : 1;
  $list = array_unique(explode("\r\n", isset($settings['contextual_list']) ? $settings['contextual_list'] : ''));

  switch ($contextual) {
    case 0:
      return FALSE;

    case 1:
      return !in_array($name, $list) ? TRUE : FALSE;

    case 2:
      return in_array($name, $list) ? TRUE : FALSE;
  }
}

/**
 * Implements hook_menu_contextual_links_alter().
 */
function custom_formatters_menu_contextual_links_alter(&$links, $router_item, $root_path) {
  if ($root_path == 'admin/structure/formatters/list/%/edit') {
    $links['custom_formatters-edit'] = array_merge(
      $router_item,
      array(
        'title' => 'Edit formatter',
      )
    );
  }
}
