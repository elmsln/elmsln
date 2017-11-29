<?php

/**
 * @file CLE Submission drush test script to check the visiblity
 * of a submission for a user
 *
 * Example Usage:
 * $ drush @studio.math033 scr submissionVisible.php [submission_nid] --user=[uid]
 * $ drush @studio.math033 scr submissionVisible.php 89 --user=4
 */

include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/LRNAppOpenStudioSubmissionService.php';

// Get the submission id from the drush arguments
$submission_id = drush_shift();

// Make sure that the submissions parent assignment has it's dependencies met.
$submission_service = new LRNAppOpenStudioSubmissionService();
$visible_to_class = $submission_service->submissionVisibleToClass($submission_id);
$message = ($visible_to_class ? 'visible' : 'hidden');
drush_print_r('Class Access: ' . $message);

// Check submission visibility for user
$visible = $submission_service->submissionVisibleToUser($submission_id);
$message = ($visible ? 'visible' : 'hidden');
drush_print_r('User Access: ' . $message);

// Check the hook_node_access
global $user;
$submission_node = node_load($submission_id);
$node_access = node_access('view', $submission_node, $user);
$message = ($node_access ? 'visible' : 'hidden');
drush_print_r('Hook Node Access: ' . $message);