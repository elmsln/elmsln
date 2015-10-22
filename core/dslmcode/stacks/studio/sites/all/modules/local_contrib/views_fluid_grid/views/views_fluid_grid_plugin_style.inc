<?php

/**
 * @file
 * Contains the fluid grid style plugin.
 */

/**
 * Style plugin to render items in a fluid grid.
 *
 * @ingroup views_style_plugins
 */
class views_fluid_grid_plugin_style extends views_plugin_style {
  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['items_width']     = array('default' => 200);
    $options['items_height']    = array('default' => '');
    $options['advanced_layout'] = array('default' => array());
    $options['list_alignment']  = array('default' => '');
    $options['items_alignment'] = array('default' => '');
    $options['items_h_margin']  = array('default' => '');
    $options['items_v_margin']  = array('default' => '');
    $options['box_shadow']      = array('default' => 0);
    $options['border_radius']   = array('default' => 0);
    return $options;
  }

  /**
   * Provide a form to edit options for this plugin.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $alignment_options    = array('' => t('Inherit'), 'left' => t('Left'), 'right' => t('Right'), 'center' => t('Center'), 'justify' => t('Justify'));
    $items_width_options  = array('' => t('Auto')) + drupal_map_assoc(variable_get('views_fluid_grid_plugin_style_widths', array(100, 150, 180, 200, 250, 300, 350, 400, 450, 500)));
    $items_height_options = array('' => t('Auto')) + drupal_map_assoc(variable_get('views_fluid_grid_plugin_style_heights', array(100, 150, 200, 250, 300, 350, 400, 450, 500)));
    $items_margin_options = array('' => t('None')) + drupal_map_assoc(variable_get('views_fluid_grid_plugin_style_margins', array('0', '2px', '4px', '6px', '8px', '10px', '0.2em', '0.5em', '0.8em', '1em', '1.2em', '1.5em', '1.8em', '2em')));

    $form['size'] = array(
      '#type' => 'fieldset',
      '#title' => t('Items size'),
    );
    $form['size']['items_width'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#options' => $items_width_options,
      '#default_value' => $this->options['items_width'],
    );
    $form['size']['items_height'] = array(
      '#type' => 'select',
      '#title' => t('Height'),
      '#options' => $items_height_options,
      '#default_value' => $this->options['items_height'],
    );

    $form['advanced_layout'] = array(
      '#type' => 'value',
      '#value' => $this->options['advanced_layout'],
    );
    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced layout options'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($this->options['advanced_layout']),
    );

    $form['advanced']['align'] = array(
      '#type' => 'fieldset',
      '#title' => t('Alignment'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($this->options['advanced_layout']['align']),
    );
    $form['advanced']['align']['list_alignment'] = array(
      '#type' => 'select',
      '#title' => t('Items in the list'),
      '#options' => $alignment_options,
      '#default_value' => $this->options['list_alignment'],
      '#description' => t('Horizontal alignment for the items in the list. Note: text-align:justify does not seem to work in IE6.'),
    );
    $form['advanced']['align']['items_alignment'] = array(
      '#type' => 'select',
      '#title' => t('Content of the items'),
      '#options' => $alignment_options,
      '#default_value' => $this->options['items_alignment'],
      '#description' => t('Horizontal alignment for the content of the items.'),
    );

    $form['advanced']['margins'] = array(
      '#type' => 'fieldset',
      '#title' => t('Margins'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($this->options['advanced_layout']['margins']),
    );
    $form['advanced']['margins']['items_h_margin'] = array(
      '#type' => 'select',
      '#title' => t('Horizontal'),
      '#options' => $items_margin_options,
      '#default_value' => $this->options['items_h_margin'],
      '#description' => t('Horizontal margin between items.'),
    );
    $form['advanced']['margins']['items_v_margin'] = array(
      '#type' => 'select',
      '#title' => t('Vertical'),
      '#options' => $items_margin_options,
      '#default_value' => $this->options['items_v_margin'],
      '#description' => t('Vertical margin between items.'),
    );

    $form['advanced']['css3'] = array(
      '#type' => 'fieldset',
      '#title' => t('CSS3 style properties'),
      '#description' => t('Note that these style properties may not be supported by all browsers.'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($this->options['advanced_layout']['css3']),
    );
    $form['advanced']['css3']['box_shadow'] = array(
      '#type' => 'radios',
      '#title' => t('Box shadow'),
      '#options' => array(0 => t('Disabled'), 1 => t('Enabled')),
      '#default_value' => $this->options['box_shadow'],
    );
    $form['advanced']['css3']['border_radius'] = array(
      '#type' => 'radios',
      '#title' => t('Border radius'),
      '#options' => array(0 => t('Disabled'), 1 => t('Enabled')),
      '#default_value' => $this->options['border_radius'],
    );
  }

  /**
   * Process the options form.
   */
  function options_submit(&$form, &$form_state) {
    foreach ($form_state['values']['style_options']['size'] as $key => $value) {
      $form_state['values']['style_options'][$key] = $value;
    }
    unset($form_state['values']['style_options']['size']);

    $advanced_layout_fieldsets = array('align', 'margins', 'css3');
    $advanced_layout_options = array();
    $option_definitions = $this->option_definition();

    foreach ($advanced_layout_fieldsets as $fieldset) {
      if (isset($form_state['values']['style_options']['advanced'][$fieldset])) {
        foreach ($form_state['values']['style_options']['advanced'][$fieldset] as $key => $value) {
          $form_state['values']['style_options'][$key] = $value;

          if ($option_definitions[$key]['default'] != $value) {
            $advanced_layout_options[$fieldset] = TRUE;
          }
        }
      }
    }
    unset($form_state['values']['style_options']['advanced']);
    $form_state['values']['style_options']['advanced_layout'] = $advanced_layout_options;

    parent::options_submit($form, $form_state);
  }
}
