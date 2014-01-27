<?php
/**
 * @file
 */
?>
/**
 * Implements hook_field_formatter_info().
 */
function <?php echo $module; ?>_field_formatter_info() {
  return array(
    '<?php echo $module; ?>_<?php echo $item->name; ?>' => array(
      'label' => t('<?php echo $item->label; ?>'),
      'field types' => array('<?php echo implode('\', \'', drupal_explode_tags($item->field_types)); ?>'),
<?php if (isset($item->form)) : ?>
      'settings' => array(
<?php foreach ($item->form as $form_key => $element) : ?>
        '<?php echo $form_key; ?>' => <?php if (is_array($element['#default_value'])) : ?>
array(
<?php foreach ($element['#default_value'] as $key => $value) : ?>
          <?php echo is_integer($key) ? $key : "'{$key}'"; ?> => '<?php echo $value; ?>',
<?php endforeach; ?>
        ),
<?php else: ?>
'<?php echo $element['#default_value']; ?>',
<?php endif; ?>
<?php endforeach; ?>
      ),
<?php endif; ?>
    ),
  );
}

<?php if (isset($item->form)) : ?>
/**
 * Implements hook_field_formatter_settings_summary().
 */
function <?php echo $module; ?>_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = '';

  if ($display['type'] == '<?php echo $module; ?>_<?php echo $item->name; ?>') {
<?php foreach (element_children($item->form) as $key) : ?>
    // <?php echo $item->form[$key]['#title'] ?>.
    $value = empty($settings['<?php echo $key; ?>']) ? '<em>' . t('Empty') . '</em>' : $settings['<?php echo $key; ?>'];
    $value = is_array($value) ? implode(', ', array_filter($value)) : $value;
    $summary .= "<?php echo $item->form[$key]['#title'] ?>: {$value}<br />";
<?php endforeach; ?>
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function <?php echo $module; ?>_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

<?php foreach (explode("\n", $item->fapi) as $line) : ?>
  <?php echo $line . "\n"; ?>
<?php endforeach; ?>
  return $form;
}
<?php endif; ?>

/**
 * Implements hook_field_formatter_view().
 */
function <?php echo $module; ?>_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $element = array();

  // Build variables array for formatter.
  $variables = array(
    '#obj_type' => $obj_type,
    '#object' => $object,
    '#field' => $field,
    '#instance' => $instance,
    '#langcode' => $langcode,
    '#items' => $items,
    '#display' => $display,
  );

  if (function_exists($function = "{$display['module']}_field_formatter_{$display['type']}")) {
    $element[0] = array(
      '#markup' => $function($variables),
    );
  }

  return $element;
}

/**
 * Field Formatter; <?php echo $item->label; ?>.
 */
function <?php echo $module; ?>_field_formatter_<?php echo $module; ?>_<?php echo $item->name; ?>($variables) {
<?php foreach (explode("\n", $item->code) as $line) : ?>
  <?php echo $line . "\n"; ?>
<?php endforeach; ?>
}
