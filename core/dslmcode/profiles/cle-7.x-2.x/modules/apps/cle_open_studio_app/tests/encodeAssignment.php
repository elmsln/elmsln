<?php

include_once drupal_get_path('module', 'cle_open_studio_app') . '/apps/services/CleOpenStudioAppAssignmentService.php';

$assignment_id = drush_shift();
$assignment_service = new CleOpenStudioAppAssignmentService();
$assignment = node_load($assignment_id);
$encoded_assignment = $assignment_service->encodeAssignment($assignment);
drush_print_r($encoded_assignment);