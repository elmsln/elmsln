<?php
/**
 * @file
 * assessment_assignment.features.conditional_fields.inc
 */

/**
 * Implements hook_conditional_fields_default_fields().
 */
function assessment_assignment_conditional_fields_default_fields() {
  $items = array();

  $items["node:assessment_assignment"] = array(
    array(
      'entity' => 'node',
      'bundle' => 'assessment_assignment',
      'dependent' => 'field_elmsln_system',
      'dependee' => 'field_evidence',
      'options' => array(
        'state' => 'visible',
        'condition' => 'value',
        'grouping' => 'AND',
        'effect' => 'show',
        'effect_options' => array(),
        'element_view' => array(
          1 => 1,
          2 => 2,
          5 => 0,
          3 => 0,
          4 => 0,
        ),
        'element_view_per_role' => 0,
        'element_view_roles' => array(
          1 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          2 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          6065076 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          135574917 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          66784200 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          67296478 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          75987638 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          166149871 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          30037204 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          76550217 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
        ),
        'element_edit' => array(
          1 => 1,
          3 => 0,
        ),
        'element_edit_per_role' => 0,
        'element_edit_roles' => array(
          1 => array(
            1 => 1,
            3 => 0,
          ),
          2 => array(
            1 => 1,
            3 => 0,
          ),
          6065076 => array(
            1 => 1,
            3 => 0,
          ),
          135574917 => array(
            1 => 1,
            3 => 0,
          ),
          66784200 => array(
            1 => 1,
            3 => 0,
          ),
          67296478 => array(
            1 => 1,
            3 => 0,
          ),
          75987638 => array(
            1 => 1,
            3 => 0,
          ),
          166149871 => array(
            1 => 1,
            3 => 0,
          ),
          30037204 => array(
            1 => 1,
            3 => 0,
          ),
          76550217 => array(
            1 => 1,
            3 => 0,
          ),
        ),
        'selector' => '',
        'values_set' => 1,
        'value_form' => 'submission',
        'value' => array(
          0 => array(
            'value' => 'submission',
          ),
        ),
        'values' => array(),
      ),
    ),
    array(
      'entity' => 'node',
      'bundle' => 'assessment_assignment',
      'dependent' => 'field_xapi_statements',
      'dependee' => 'field_evidence',
      'options' => array(
        'state' => 'visible',
        'condition' => 'value',
        'grouping' => 'AND',
        'effect' => 'show',
        'effect_options' => array(),
        'element_view' => array(
          1 => 1,
          2 => 2,
          5 => 0,
          3 => 0,
          4 => 0,
        ),
        'element_view_per_role' => 0,
        'element_view_roles' => array(
          1 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          2 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          6065076 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          135574917 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          66784200 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          67296478 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          75987638 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          166149871 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          30037204 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
          76550217 => array(
            1 => 1,
            2 => 2,
            5 => 0,
            3 => 0,
            4 => 0,
          ),
        ),
        'element_edit' => array(
          1 => 1,
          3 => 0,
        ),
        'element_edit_per_role' => 0,
        'element_edit_roles' => array(
          1 => array(
            1 => 1,
            3 => 0,
          ),
          2 => array(
            1 => 1,
            3 => 0,
          ),
          6065076 => array(
            1 => 1,
            3 => 0,
          ),
          135574917 => array(
            1 => 1,
            3 => 0,
          ),
          66784200 => array(
            1 => 1,
            3 => 0,
          ),
          67296478 => array(
            1 => 1,
            3 => 0,
          ),
          75987638 => array(
            1 => 1,
            3 => 0,
          ),
          166149871 => array(
            1 => 1,
            3 => 0,
          ),
          30037204 => array(
            1 => 1,
            3 => 0,
          ),
          76550217 => array(
            1 => 1,
            3 => 0,
          ),
        ),
        'selector' => '',
        'values_set' => 1,
        'value_form' => 'XAPI',
        'value' => array(
          0 => array(
            'value' => 'XAPI',
          ),
        ),
        'values' => array(),
      ),
    ),
  );

  return $items;
}
