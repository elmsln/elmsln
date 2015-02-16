<?php

/**
 * @file
 * assessment_entity editing UI.
 */

/**
 * UI controller.
 */
class AssessmentEntityUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   *
   * Main reason for doing this is that parent class hook_menu() is, optimized
   * for entity type administration.
   */
  public function hook_menu() {
    // TODO: EntityDefaultUIController controller automatically adds the menu
    // to import entities, but there is a bug with this action and can not work
    // with the version of your entity_api module, track the issue # 2112755
    // https://www.drupal.org/node/2112755
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $items = parent::hook_menu();

    // Change the overview menu type for the list of Assessment Entity.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Replaces default entity title.
    $items[$this->path]['title'] = 'Assessment Entity';

    // Extend the 'add' path.
    $items[$this->path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'entity_ui_bundle_add_page',
      'page arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items[$this->path . '/add/%'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType, $this->id_count + 1),
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array($this->entityType, $this->id_count + 1),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items['assessment_entity/' . $wildcard] = array(
      'title callback' => 'assessment_entity_page_title',
      'title arguments' => array(1),
      'page callback' => 'assessment_entity_page_view',
      'page arguments' => array(1),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
    );

    return $items;
  }
}

/**
 * Form callback: create or edit a Assessment Entity.
 */
function assessment_entity_form($form, &$form_state, $assessment_entity, $op = 'edit', $entity_type) {
  // Add the breadcrumb for the form's location.
  assessment_entity_set_breadcrumb();

  // Add the default field elements.
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Assessment Entity Label'),
    '#default_value' => isset($assessment_entity->label) ? $assessment_entity->label : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['assessment_entity'] = $assessment_entity;
  field_attach_form('assessment_entity', $assessment_entity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Assessment Entity'),
    '#submit' => $submit + array('assessment_entity_edit_form_submit'),
  );

  if (!empty($assessment_entity->label)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Assessment Entity'),
      '#suffix' => l(t('Cancel'), 'admin/content/assessment_entity'),
      '#submit' => $submit + array('assessment_entity_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'] = array('assessment_entity_edit_form_validate');

  return $form;
}

/**
 * Form API validate callback for the Assessment Entity form.
 */
function assessment_entity_edit_form_validate(&$form, &$form_state) {
  $assessment_entity = $form_state['assessment_entity'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('assessment_entity', $assessment_entity, $form, $form_state);
}

/**
 * Form API submit callback for the Assessment Entity form.
 */
function assessment_entity_edit_form_submit(&$form, &$form_state) {
  // Save the entity and go back to the list of Assessment Entity.
  $assessment_entity = entity_ui_controller('assessment_entity')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  $is_new_entity = $assessment_entity->is_new = isset($assessment_entity->is_new) ? $assessment_entity->is_new : 0;
  if ($is_new_entity) {
    $assessment_entity->created = time();
  }

  $assessment_entity->changed = time();

  $assessment_entity->save();

  // Send feedback message to the user.
  $message = t("Assessment Entity :label updated.", array(':label' => $assessment_entity->label));

  if ($is_new_entity) {
    $message = t("Assessment Entity :label created.", array(':label' => $assessment_entity->label));
  }

  drupal_set_message($message);

  $form_state['redirect'] = 'admin/content/assessment_entity';
}

/**
 * Form API submit callback for the delete button.
 */
function assessment_entity_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/assessment_entity/manage/' . $form_state['assessment_entity']->mjid . '/delete';
}

/**
 * Sets the breadcrumb for administrative Assessment Entity pages.
 */
function assessment_entity_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Assessment Entity'), 'admin/content/assessment_entity'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
