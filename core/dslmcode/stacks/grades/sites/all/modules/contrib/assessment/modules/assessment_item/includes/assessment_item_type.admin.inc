<?php

/**
 * @file
 * Assessment Item type editing UI.
 */

/**
 * UI controller.
 */
class AssessmentItemTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Assessment Item entity types, including adding and removing fields and the display of fields.';

    return $items;
  }
}

/**
 * Generates the Assessment Item type editing form.
 */
function assessment_item_type_form($form, &$form_state, $assessment_item_type, $op = 'edit') {
  if ($op == 'clone') {
    $assessment_item_type->label .= ' (cloned)';
    $assessment_item_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $assessment_item_type->label,
    '#description' => t('The human-readable name of this Assessment Item type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($assessment_item_type->type) ? $assessment_item_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'assessment_item_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Assessment Item type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Assessment Item type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function assessment_item_type_form_submit(&$form, &$form_state) {
  $assessment_item_type = entity_ui_form_submit_build_entity($form, $form_state);
  $assessment_item_type->save();
  $form_state['redirect'] = 'admin/structure/assessment_item_types';
}

/**
 * Form API submit callback for the delete button.
 */
function assessment_item_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/assessment_item_types/manage/' . $form_state['assessment_item_type']->type . '/delete';
}
