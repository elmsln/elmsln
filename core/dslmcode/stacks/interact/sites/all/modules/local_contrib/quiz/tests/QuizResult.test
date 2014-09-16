<?php

class QuizResult extends QuizTestCase {

  public static function getInfo() {
    return array(
      'name' => t('Quiz results'),
      'description' => t('Unit test for Quiz results.'),
      'group' => t('Quiz'),
    );
  }

  function setUp($modules = array(), $admin_permissions = array(), $user_permissions = array()) {
    $modules[] = 'truefalse';
    parent::setUp($modules);
  }

  /**
   * Test the various result summaries and pass rate.
   */
  public function testPassRateSummary() {
    // By default, the feedback is after the quiz.
    $quiz_node = $this->drupalCreateQuiz(array(
      'pass_rate' => 75,
      'summary_pass' => 'This is the summary if passed',
      'summary_pass_format' => 'plain_text',
      'summary_default' => 'This is the default summary text',
      'summary_default_format' => 'plain_text',
      'resultoptions' => array(
        array(
          'option_name' => '90 and higher',
          'option_summary' => 'You got 90 or more on the quiz',
          'option_summary_format' => 'filtered_html',
          'option_start' => 90,
          'option_end' => 100,
        ),
        array(
          'option_name' => '50 and higher',
          'option_summary' => 'You got between 50 and 89',
          'option_summary_format' => 'filtered_html',
          'option_start' => 50,
          'option_end' => 89,
        ),
        array(
          'option_name' => 'Below 50',
          'option_summary' => 'You failed bro',
          'option_summary_format' => 'filtered_html',
          'option_start' => 0,
          'option_end' => 49,
        ),
      ),
    ));

    // 3 questions.
    $question_node1 = $this->drupalCreateNode(array('type' => 'truefalse', 'correct_answer' => 1, 'feedback' => 'Q1Feedback'));
    $this->linkQuestionToQuiz($question_node1, $quiz_node);
    $question_node2 = $this->drupalCreateNode(array('type' => 'truefalse', 'correct_answer' => 1, 'feedback' => 'Q2Feedback'));
    $this->linkQuestionToQuiz($question_node2, $quiz_node);
    $question_node3 = $this->drupalCreateNode(array('type' => 'truefalse', 'correct_answer' => 1, 'feedback' => 'Q3Feedback'));
    $this->linkQuestionToQuiz($question_node3, $quiz_node);

    // Test 100%
    $this->drupalLogin($this->user);
    $this->drupalGet("node/$quiz_node->nid/take");
    $this->drupalPost(NULL, array(
      "question[$question_node1->nid]" => 1,
      ), t('Next'));
    $this->drupalPost(NULL, array(
      "question[$question_node2->nid]" => 1,
      ), t('Next'));
    $this->drupalPost(NULL, array(
      "question[$question_node3->nid]" => 1,
      ), t('Finish'));
    $this->assertText('You got 90 or more on the quiz');
    $this->assertText('This is the summary if passed');
    $this->assertNoText('This is the default summary text');

    // Test 66%
    $this->drupalGet("node/$quiz_node->nid/take");
    $this->drupalPost(NULL, array(
      "question[$question_node1->nid]" => 1,
      ), t('Next'));
    $this->drupalPost(NULL, array(
      "question[$question_node2->nid]" => 1,
      ), t('Next'));
    $this->drupalPost(NULL, array(
      "question[$question_node3->nid]" => 0,
      ), t('Finish'));
    $this->assertText('You got between 50 and 89');
    $this->assertNoText('This is the summary if passed');
    $this->assertText('This is the default summary text');

    // Test 33%
    $this->drupalGet("node/$quiz_node->nid/take");
    $this->drupalPost(NULL, array(
      "question[$question_node1->nid]" => 1,
      ), t('Next'));
    $this->drupalPost(NULL, array(
      "question[$question_node2->nid]" => 0,
      ), t('Next'));
    $this->drupalPost(NULL, array(
      "question[$question_node3->nid]" => 0,
      ), t('Finish'));
    $this->assertText('You failed bro');
    $this->assertNoText('This is the summary if passed');
    $this->assertText('This is the default summary text');
  }

}
