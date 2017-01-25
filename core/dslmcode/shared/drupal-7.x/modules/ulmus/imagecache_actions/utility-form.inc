<?php
/**
 * @file Utility form, conversion and rendering functions for image processes.
 */

/**
 * Prepares a sub form for displaying positioning fields.
 *
 * @param array $data
 *   Effect data of the effect where this sub form will be integrated.
 *
 * @return array
 *   The form definition for this sub form.
 */
function imagecache_actions_pos_form(array $data) {
  $defaults = array(
    'xpos' => 'center',
    'ypos' => 'center',
  );
  $data = array_merge($defaults, (array) $data);

  $description1 = t('Enter an offset in pixels (e.g. 10, 10px), a percentage (e.g. 25%), or one of the keywords: <em>left</em>, <em>center</em>, or <em>right</em> wih an optional offset (e.g. center, right - 10%).');
  $description2 = t('Enter an offset in pixels (e.g. 10, 10px), a percentage (e.g. 25%), or one of the keywords: <em>top</em>, <em>center</em>, or <em>bottom</em> wih an optional offset (e.g. center, bottom - 10%).');
  $form = array(
    'xpos' => array(
      '#type' => 'textfield',
      '#title' => t('X offset'),
      '#default_value' => $data['xpos'],
      '#size' => 6,
      '#description' => $description1,
      '#element_validate' => array('imagecache_actions_validate_number'),
    ),
    'ypos' => array(
      '#type' => 'textfield',
      '#title' => t('Y offset'),
      '#default_value' => $data['ypos'],
      '#size' => 6,
      '#description' => $description2,
      '#element_validate' => array('imagecache_actions_validate_number'),
    ),
  );
  return $form;
}

/**
 * Form element validator that checks for a valid number.
 *
 * @param array $element
 * @param $form_state
 */
function imagecache_actions_validate_number(&$element, &$form_state) {
  if (empty($element['#value'])) {
    form_set_value($element, 0, $form_state);
  }
}

/**
 * Form element validator that checks a transparency percentage value.
 *
 * @param array $element
 */
function imagecache_actions_validate_alpha(&$element/*, &$form_status*/) {
  if (!is_numeric($element['#value']) || $element['#value'] < 1 || $element['#value'] > 100) {
    form_set_error(join('][', $element['#parents']), t('Opacity must be a number between 1 and 100.'));
  }
}
