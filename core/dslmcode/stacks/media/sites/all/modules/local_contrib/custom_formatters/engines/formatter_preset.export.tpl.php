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
      'label'       => t('<?php echo $item->label; ?>'),
      'field types' => array('<?php echo implode('\', \'', drupal_explode_tags($item->field_types)); ?>'),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function <?php echo $module; ?>_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $formatter = field_info_formatter_types('<?php echo $item->code['formatter'] ?>');
  $function  = "{$formatter['module']}_field_formatter_view";
  if (function_exists($function)) {
    $display['settings'] = unserialize('<?php echo serialize($item->code['settings']) ?>');
    $display['type']     = '<?php echo $item->code['formatter'] ?>';
    $display['module']   = $formatter['module'];

    return $function($obj_type, $object, $field, $instance, $langcode, $items, $display);
  }
}
