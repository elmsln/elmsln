<?php

/**
 * Controller for a single quiz question response.
 */
class QuizResultAnswerController extends EntityAPIController {

  /**
   * Build the response content with feedback.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $out = parent::buildContent($entity, $view_mode, $langcode, $content);
    $node = node_load($entity->question_nid, $entity->question_vid);
    $entity_info = entity_get_info('node');
    // @kludge
    // We check for an instance first. This is probably not the best way to do
    // this but we need to sometimes show feedback for an answer not stored.
    // For example when taking quizzes with "repeat until correct".
    if (!isset($entity->instance)) {
      $instance = _quiz_question_response_get_instance($entity->result_id, $node);
    }
    else {
      $instance = $entity->instance;
    }
    foreach ($entity_info['view modes'] as $view_mode => $info) {
      if ($instance->canReview("quiz_question_view_" . $view_mode)) {
        $build = node_view($node, $view_mode);
        unset($build['#theme']);
        unset($build['answers']);
        unset($build['links']);

        $out["quiz_question_view_" . $view_mode] = $build;
      }
    }

    $rows = array();

    $labels = array(
      'attempt' => t('Your answer'),
      'choice' => t('Choice'),
      'correct' => t('Correct?'),
      'score' => t('Score'),
      'answer_feedback' => t('Feedback'),
      'solution' => t('Correct answer'),
    );
    drupal_alter('quiz_feedback_labels', $labels);

    foreach ($instance->getFeedbackValues() as $idx => $row) {
      foreach ($labels as $reviewType => $label) {
        if ((isset($row[$reviewType]) && $instance->canReview($reviewType))) {
          $rows[$idx][$reviewType] = $row[$reviewType];
          if (!empty($row[$reviewType])) {
            $out[$reviewType] = array(
              '#title' => $label,
              '#type' => 'item',
              '#markup' => $row[$reviewType],
            );
          }
        }
      }
    }

    if ($instance->isEvaluated()) {
      $score = $instance->getScore();
      if ($instance->isCorrect()) {
        $class = 'q-correct';
      }
      else {
        $class = 'q-wrong';
      }
    }
    else {
      $score = t('?');
      $class = 'q-waiting';
    }

    $quiz_result = quiz_result_load($entity->result_id);

    if ($instance->canReview('score') || quiz_access_to_score($quiz_result)) {
      $out['score']['#title'] = '';
      $out['score']['#markup'] = theme('quiz_question_score', array('score' => $score, 'max_score' => $instance->getMaxScore(), 'class' => $class));
    }

    if ($rows) {
      $headers = array_intersect_key($labels, $rows[0]);
      $type = $instance->getQuizQuestion()->node->type;
      $out['table']['#markup'] = theme('quiz_question_feedback__' . $type, array('labels' => $headers, 'data' => $rows));
    }

    if ($instance->canReview('question_feedback')) {
      if ($properties = entity_load('quiz_question', FALSE, array('nid' => $instance->quizQuestion->node->nid, 'vid' => $instance->quizQuestion->node->vid))) {
        $quiz_question = reset($properties);
        $account = user_load($quiz_result->uid);
        $token_types = array(
          'global' => NULL,
          'node' => $instance->quizQuestion->node,
          'user' => $account,
        );
        $quiz_question->feedback = token_replace($quiz_question->feedback, $token_types);
        $out['question_feedback']['#markup'] = check_markup($quiz_question->feedback, $quiz_question->feedback_format);
      }
    }

    if ($instance->canReview('score')) {
      $out['max_score'] = array(
        '#type' => 'value',
        '#value' => $instance->getMaxScore(),
      );
    }

    return $out;
  }

}
