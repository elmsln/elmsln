<?php
/**
 * @file
 * assessment_quiz_perms.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function assessment_quiz_perms_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access quiz'.
  $permissions['access quiz'] = array(
    'name' => 'access quiz',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'administer quiz configuration'.
  $permissions['administer quiz configuration'] = array(
    'name' => 'administer quiz configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'create long_answer content'.
  $permissions['create long_answer content'] = array(
    'name' => 'create long_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create multichoice content'.
  $permissions['create multichoice content'] = array(
    'name' => 'create multichoice content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create quiz content'.
  $permissions['create quiz content'] = array(
    'name' => 'create quiz content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create quiz_ddlines content'.
  $permissions['create quiz_ddlines content'] = array(
    'name' => 'create quiz_ddlines content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create quiz_directions content'.
  $permissions['create quiz_directions content'] = array(
    'name' => 'create quiz_directions content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create quiz_page content'.
  $permissions['create quiz_page content'] = array(
    'name' => 'create quiz_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create scale content'.
  $permissions['create scale content'] = array(
    'name' => 'create scale content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create short_answer content'.
  $permissions['create short_answer content'] = array(
    'name' => 'create short_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create truefalse content'.
  $permissions['create truefalse content'] = array(
    'name' => 'create truefalse content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any long_answer content'.
  $permissions['delete any long_answer content'] = array(
    'name' => 'delete any long_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any multichoice content'.
  $permissions['delete any multichoice content'] = array(
    'name' => 'delete any multichoice content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz content'.
  $permissions['delete any quiz content'] = array(
    'name' => 'delete any quiz content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz results'.
  $permissions['delete any quiz results'] = array(
    'name' => 'delete any quiz results',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'delete any quiz_ddlines content'.
  $permissions['delete any quiz_ddlines content'] = array(
    'name' => 'delete any quiz_ddlines content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz_directions content'.
  $permissions['delete any quiz_directions content'] = array(
    'name' => 'delete any quiz_directions content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz_page content'.
  $permissions['delete any quiz_page content'] = array(
    'name' => 'delete any quiz_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any scale content'.
  $permissions['delete any scale content'] = array(
    'name' => 'delete any scale content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any short_answer content'.
  $permissions['delete any short_answer content'] = array(
    'name' => 'delete any short_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any truefalse content'.
  $permissions['delete any truefalse content'] = array(
    'name' => 'delete any truefalse content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own long_answer content'.
  $permissions['delete own long_answer content'] = array(
    'name' => 'delete own long_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own multichoice content'.
  $permissions['delete own multichoice content'] = array(
    'name' => 'delete own multichoice content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own quiz content'.
  $permissions['delete own quiz content'] = array(
    'name' => 'delete own quiz content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own quiz_ddlines content'.
  $permissions['delete own quiz_ddlines content'] = array(
    'name' => 'delete own quiz_ddlines content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own quiz_directions content'.
  $permissions['delete own quiz_directions content'] = array(
    'name' => 'delete own quiz_directions content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own quiz_page content'.
  $permissions['delete own quiz_page content'] = array(
    'name' => 'delete own quiz_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own scale content'.
  $permissions['delete own scale content'] = array(
    'name' => 'delete own scale content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own short_answer content'.
  $permissions['delete own short_answer content'] = array(
    'name' => 'delete own short_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own truefalse content'.
  $permissions['delete own truefalse content'] = array(
    'name' => 'delete own truefalse content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete results for own quiz'.
  $permissions['delete results for own quiz'] = array(
    'name' => 'delete results for own quiz',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'edit any long_answer content'.
  $permissions['edit any long_answer content'] = array(
    'name' => 'edit any long_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any multichoice content'.
  $permissions['edit any multichoice content'] = array(
    'name' => 'edit any multichoice content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any quiz content'.
  $permissions['edit any quiz content'] = array(
    'name' => 'edit any quiz content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any quiz_ddlines content'.
  $permissions['edit any quiz_ddlines content'] = array(
    'name' => 'edit any quiz_ddlines content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any quiz_directions content'.
  $permissions['edit any quiz_directions content'] = array(
    'name' => 'edit any quiz_directions content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any quiz_page content'.
  $permissions['edit any quiz_page content'] = array(
    'name' => 'edit any quiz_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any scale content'.
  $permissions['edit any scale content'] = array(
    'name' => 'edit any scale content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any short_answer content'.
  $permissions['edit any short_answer content'] = array(
    'name' => 'edit any short_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any truefalse content'.
  $permissions['edit any truefalse content'] = array(
    'name' => 'edit any truefalse content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own long_answer content'.
  $permissions['edit own long_answer content'] = array(
    'name' => 'edit own long_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own multichoice content'.
  $permissions['edit own multichoice content'] = array(
    'name' => 'edit own multichoice content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own quiz content'.
  $permissions['edit own quiz content'] = array(
    'name' => 'edit own quiz content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own quiz_ddlines content'.
  $permissions['edit own quiz_ddlines content'] = array(
    'name' => 'edit own quiz_ddlines content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own quiz_directions content'.
  $permissions['edit own quiz_directions content'] = array(
    'name' => 'edit own quiz_directions content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own quiz_page content'.
  $permissions['edit own quiz_page content'] = array(
    'name' => 'edit own quiz_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own scale content'.
  $permissions['edit own scale content'] = array(
    'name' => 'edit own scale content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own short_answer content'.
  $permissions['edit own short_answer content'] = array(
    'name' => 'edit own short_answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own truefalse content'.
  $permissions['edit own truefalse content'] = array(
    'name' => 'edit own truefalse content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit question titles'.
  $permissions['edit question titles'] = array(
    'name' => 'edit question titles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'manual quiz revisioning'.
  $permissions['manual quiz revisioning'] = array(
    'name' => 'manual quiz revisioning',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'score any quiz'.
  $permissions['score any quiz'] = array(
    'name' => 'score any quiz',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'score own quiz'.
  $permissions['score own quiz'] = array(
    'name' => 'score own quiz',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'score taken quiz answer'.
  $permissions['score taken quiz answer'] = array(
    'name' => 'score taken quiz answer',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view any quiz question correct response'.
  $permissions['view any quiz question correct response'] = array(
    'name' => 'view any quiz question correct response',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view any quiz results'.
  $permissions['view any quiz results'] = array(
    'name' => 'view any quiz results',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view own quiz results'.
  $permissions['view own quiz results'] = array(
    'name' => 'view own quiz results',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view quiz question outside of a quiz'.
  $permissions['view quiz question outside of a quiz'] = array(
    'name' => 'view quiz question outside of a quiz',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view results for own quiz'.
  $permissions['view results for own quiz'] = array(
    'name' => 'view results for own quiz',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'quiz',
  );

  return $permissions;
}
