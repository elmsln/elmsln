<?php

/**
 * @file
 * Contains geofieldProximityOtherGeofield.
 */

class geofieldProximityOtherGeofield extends geofieldProximityBase implements geofieldProximityPluginInterface {
  public function option_definition(&$options, $views_plugin) {
    $options['geofield_proximity_other_geofield'] = array(
      'default' => '',
    );
  }

  public function options_form(&$form, &$form_state, $views_plugin) {
    $handlers = $views_plugin->view->display_handler->get_handlers('field');
    $other_geofield_options = array(
      '' => '- None -',
    );

    foreach ($handlers as $handle) {
      if (!empty($handle->field_info['type']) && $handle->field_info['type'] == 'geofield') {
        $other_geofield_options[$handle->options['id']] = (!empty($handle->options['label'])) ? $handle->options['label'] : $handle->options['id'];
      }
    }
    $form['geofield_proximity_other_geofield'] = array(
      '#type' => 'select',
      '#title' => t('Other Geofield'),
      '#description' => t('List of other geofields attached to this view.'),
      '#default_value' => $views_plugin->options['geofield_proximity_other_geofield'],
      '#options' => $other_geofield_options,
      '#dependency' => array(
        'edit-options-source' => array('other_geofield'),
      ),
    );
  }

  public function options_validate(&$form, &$form_state, $views_plugin) {
    if ($form_state['values']['options']['geofield_proximity_other_geofield'] == '') {
      form_set_error('options][geofield_proximity_other_geofield', t('Please select a geofield.'));
    }
  }

  public function getSourceValue($views_plugin) {
    if (!empty($views_plugin->options['geofield_proximity_other_geofield'])) {
      $other_geofield = $views_plugin->view->display_handler->get_handler('field', $views_plugin->options['geofield_proximity_other_geofield']);
      $views_plugin->query->add_field($other_geofield->table, $other_geofield->definition['field_name'] . '_lat');
      $views_plugin->query->add_field($other_geofield->table, $other_geofield->definition['field_name'] . '_lon'); // @TODO: Not sure if we need 2nd add field.

      return array(
        'latitude' => $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lat',
        'longitude' => $other_geofield->table . '.' . $other_geofield->definition['field_name'] . '_lon',
      );
    }

    return FALSE;
  }
}
