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
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function <?php echo $module; ?>_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $pattern = "<?php echo addslashes($item->code); ?>";

  $info = token_get_info("{$field['type']}-field");
  $field_value = $info['field-value-type'];

  $output = '';
  foreach ($items as $item) {
    $output .= token_replace($pattern, array(
      $obj_type => $object,
      $field_value => $item,
      'item' => $item,
    ));
  }
  $element[0] = array(
    '#markup' => $output,
  );

  return $element;
}
