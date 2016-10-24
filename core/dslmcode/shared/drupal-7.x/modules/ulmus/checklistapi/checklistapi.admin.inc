<?php

/**
 * @file
 * Admin page callback file for the Checklist API module.
 */

/**
 * Page callback: Form constructor for the report form.
 *
 * @see checklistapi_menu()
 *
 * @ingroup forms
 */
function checklistapi_report_form() {
  // Define table header.
  $header = array(
    t('Checklist'),
    t('Progress'),
    t('Last updated'),
    t('Last updated by'),
    t('Operations'),
  );

  // Build table rows.
  $rows = array();
  $definitions = checklistapi_get_checklist_info();
  foreach ($definitions as $id => $definition) {
    $checklist = checklistapi_checklist_load($id);
    $row = array();
    $row[] = array(
      'data' => ($checklist->userHasAccess()) ? l($checklist->title, $checklist->path) : drupal_placeholder($checklist->title),
      'title' => (!empty($checklist->description)) ? $checklist->description : '',
    );
    $row[] = t('@completed of @total (@percent%)', array(
      '@completed' => $checklist->getNumberCompleted(),
      '@total' => $checklist->getNumberOfItems(),
      '@percent' => round($checklist->getPercentComplete()),
    ));
    $row[] = $checklist->getLastUpdatedDate();
    $row[] = $checklist->getLastUpdatedUser();
    $row[] = ($checklist->userHasAccess('edit') && $checklist->hasSavedProgress()) ? l(t('clear saved progress'), $checklist->path . '/clear', array(
      'query' => array('destination' => 'admin/reports/checklistapi'),
    )) : '';
    $rows[] = $row;
  }

  // Compile table.
  $table = array(
    'header' => $header,
    'rows' => $rows,
    'empty' => t('No checklists available.'),
  );

  return theme('table', $table);
}
