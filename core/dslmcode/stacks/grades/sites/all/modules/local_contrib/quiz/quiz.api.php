<?php

/**
 * @file quiz.api.php
 * Hooks provided by Quiz module.
 *
 * These entity types provided by Quiz also have entity API hooks. There are a
 * few additional Quiz specific hooks defined in this file.
 *
 * quiz (settings for quiz nodes)
 * quiz_result (quiz attempt/result)
 * quiz_result_answer (answer to a specific question in a quiz result)
 * quiz_question (generic settings for question nodes)
 * quiz_question_relationship (relationship from quiz to question)
 *
 * So for example
 *
 * hook_quiz_result_presave($quiz_result)
 *   - Runs before a result is saved to the DB.
 * hook_quiz_question_relationship_insert($quiz_question_relationship)
 *   - Runs when a new question is added to a quiz.
 *
 * You can also use Rules to build conditional actions based off of these
 * events.
 *
 * Enjoy :)
 */

/**
 * Implements hook_quiz_begin().
 *
 * Fired when a new quiz result is created.
 *
 * @deprecated
 *
 * Use hook_quiz_result_insert().
 */
function hook_quiz_begin($quiz, $result_id) {

}

/**
 * Implements hook_quiz_finished().
 *
 * Fired after the last question is submitted.
 *
 * @deprecated
 *
 * Use hook_quiz_result_update().
 */
function hook_quiz_finished($quiz, $score, $data) {

}

/**
 * Implements hook_quiz_scored().
 *
 * Fired when a quiz is evaluated.
 *
 * @deprecated
 *
 * Use hook_quiz_result_update().
 */
function hook_quiz_scored($quiz, $score, $result_id) {

}

/**
 * Implements hook_quiz_question_info().
 *
 * Define a new question type. The question provider must extend QuizQuestion,
 * and the response provider must extend QuizQuestionResponse. See those classes
 * for additional implementation details.
 */
function hook_quiz_question_info() {
  return array(
    'long_answer' => array(
      'name' => t('Example question type'),
      'description' => t('An example question type that does something.'),
      'question provider' => 'ExampleAnswerQuestion',
      'response provider' => 'ExampleAnswerResponse',
      'module' => 'quiz_question',
    ),
  );
}

/**
 * Expose a feedback option to Quiz so that Quiz administrators can choose when
 * to show it to Quiz takers.
 *
 * @return array
 *   An array of feedback options keyed by machine name.
 */
function hook_quiz_feedback_options() {
  return array(
    'percentile' => t('Percentile'),
  );
}

/**
 * Allow modules to alter the quiz feedback options.
 *
 * @param array $review_options
 *   An array of review options keyed by a machine name.
 */
function hook_quiz_feedback_options_alter(&$review_options) {
  // Change label.
  $review_options['quiz_feedback'] = t('General feedback from the Quiz.');

  // Disable showing correct answer.
  unset($review_options['solution']);
}

/**
 * Allow modules to define feedback times.
 *
 * Feedback times are configurable by Rules.
 *
 * @return array
 *   An array of feedback times keyed by machine name.
 */
function hook_quiz_feedback_times() {
  return array(
    '2_weeks_later' => t('Two weeks after finishing'),
  );
}

/**
 * Allow modules to alter the feedback times.
 *
 * @param array $feedback_times
 */
function hook_quiz_feedback_times_alter(&$feedback_times) {
  // Change label.
  $feedback_times['end'] = t('At the end of a quiz');

  // Do not allow question feedback.
  unset($feedback_times['question']);
}

/**
 * Allow modules to alter the feedback labels.
 *
 * These are the labels that are displayed to the user, so instead of
 * "Answer feedback" you may want to display something more learner-friendly.
 *
 * @param $feedback_labels
 *   An array keyed by the feedback option. Default keys are the keys from
 *   quiz_get_feedback_options().
 */
function hook_quiz_feedback_labels_alter(&$feedback_labels) {
  $feedback_labels['solution'] = t('The answer you should have chosen.');
}

/**
 * Implements hook_quiz_access().
 *
 * Control access to Quizzes.
 *
 * @see quiz_quiz_access() for default access implementations.
 *
 * Modules may implement Quiz access control hooks to block access to a Quiz or
 * display a non-blocking message. Blockers are keyed by a blocker name, and
 * must be an array keyed by 'success' and 'message'.
 */
function hook_quiz_access($op, $quiz, $account) {
  if ($op == 'take') {
    $today = date('l');
    if ($today == 'Monday') {
      return array(
        'monday' => array(
          'success' => FALSE,
          'message' => t('You cannot take quizzes on Monday.'),
        ),
      );
    }
    else {
      return array(
        'not_monday' => array(
          'success' => TRUE,
          'message' => t('It is not Monday so you may take quizzes.'),
        ),
      );
    }
  }
}

/**
 * Implements hook_quiz_access_alter().
 *
 * Alter the access blockers for a Quiz.
 *
 */
function hook_quiz_access_alter(&$hooks, $op, $quiz, $account) {
  if ($op == 'take') {
    unset($hooks['monday']);
  }
}
