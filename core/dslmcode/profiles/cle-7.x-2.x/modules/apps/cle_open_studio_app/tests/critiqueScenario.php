<?php

include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/CleOpenStudioAppAssignmentService.php';
include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/CleOpenStudioAppProjectService.php';
include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/CleOpenStudioAppSubmissionService.php';

$project_service = new CleOpenStudioAppProjectService();
$assignment_service = new CleOpenStudioAppAssignmentService();
$submission_service = new CleOpenStudioAppSubmissionService();

// Delete Assignments
$assignments = $assignment_service->getAssignments();
foreach ($assignments as $assignment) {
  node_delete($assignment->nid);
}
// Delete Submissions
$submissions = $submission_service->getSubmissions();
foreach ($submissions as $submission) {
  node_delete($submission->nid);
}

// Project 1
$project1 = $project_service->createStubProject();
drush_print_r($project1);
// Create Assignments
// $assignment1 = $assignment_service->createStubAssignment();