<?php

include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/LRNAppOpenStudioAssignmentService.php';
include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/LRNAppOpenStudioProjectService.php';
include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/LRNAppOpenStudioSubmissionService.php';

$project_service = new LRNAppOpenStudioProjectService();
$assignment_service = new LRNAppOpenStudioAssignmentService();
$submission_service = new LRNAppOpenStudioSubmissionService();

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