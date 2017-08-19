<?php

include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/CleOpenStudioAppSubmissionService.php';

$submission_id = drush_shift();

// Make sure that the submissions parent assignment has it's dependencies met.
$submission_service = new CleOpenStudioAppSubmissionService();
$visible_to_class = $submission_service->submissionVisibleToClass($submission_id);
$message = ($visible_to_class ? 'visible to Class' : 'not visible to class');
drush_print_r('Class Access: ' . $message);

// Check submission visibility for user
$visible = $submission_service->submissionVisibleToUser($submission_id);
$message = ($visible ? 'visible' : 'not visible to class');
drush_print_r('User Access: ' . $message);

// Check the hook_node_access
global $user;
$submission_node = node_load($submission_id);
$node_access = cle_submission_node_access($submission_node, 'view', $user);
$message = ($node_access == NULL ? 'allowed' : $node_access);
drush_print_r('Hook Node Access ' . $message);