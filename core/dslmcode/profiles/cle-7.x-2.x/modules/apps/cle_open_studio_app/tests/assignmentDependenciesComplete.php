<?php

include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/LRNAppOpenStudioAssignmentService.php';

$assignment_id = drush_shift();

// Make sure that the submissions parent assignment has it's dependencies met.
$assignment_service = new LRNAppOpenStudioAssignmentService();
$unmet = $assignment_service->assignmentHasUnmetDependencies($assignment_id);

drush_print_r(($unmet ? 'unmet' : 'good to submit'));