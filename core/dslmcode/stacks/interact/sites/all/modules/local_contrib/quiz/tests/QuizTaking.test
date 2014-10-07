<?php

class QuizTaking extends QuizTestCase {

  public static function getInfo() {
    return array(
      'name' => t('Quiz taking'),
      'description' => t('Unit test for Quiz take behaviors.'),
      'group' => t('Quiz'),
    );
  }

  public function setUp($modules = array()) {
    $modules[] = 'truefalse';
    parent::setUp($modules);
  }

  /**
   * Test the repeat until correct behavior. We do not have to test what type
   * of feedback shows here, that is tested elsewhere.
   */
  public function testQuestionRepeatUntilCorrect() {
    $this->drupalLogin($this->admin);
    $quiz_node = $this->drupalCreateQuiz(array(
      'repeat_until_correct' => 1,
      'review_options' => array('question' => array('answer_feedback' => 'answer_feedback')),
    ));

    $question_node = $this->drupalCreateNode(array(
      'type' => 'truefalse',
      'correct_answer' => 1,
      'feedback' => 'Feedback for repeat until correct.',
    ));
    $this->linkQuestionToQuiz($question_node, $quiz_node);

    $this->drupalLogin($this->user);
    $this->drupalGet("node/{$quiz_node->nid}/take");
    $this->drupalPost(NULL, array(
      "question[$question_node->nid]" => 0,
      ), t('Finish'));
    $this->assertText('Feedback for repeat until correct.');
    $this->assertText('The answer was incorrect. Please try again.');
    // Check that we are still on the question.
    $this->assertUrl("node/{$quiz_node->nid}/take/1");
    $this->drupalPost(NULL, array(
      "question[$question_node->nid]" => 1,
      ), t('Finish'));
    $this->assertNoText('The answer was incorrect. Please try again.');
  }

  /**
   * Test the quiz resuming from database.
   */
  public function testQuizResuming() {
    $this->drupalLogin($this->admin);
    // Resuming is default behavior.
    $quiz_node = $this->drupalCreateQuiz(array('allow_resume' => 1));

    // 2 questions.
    $question_node1 = $this->drupalCreateNode(array('type' => 'truefalse', 'correct_answer' => 1));
    $this->linkQuestionToQuiz($question_node1, $quiz_node);
    $question_node2 = $this->drupalCreateNode(array('type' => 'truefalse', 'correct_answer' => 1));
    $this->linkQuestionToQuiz($question_node2, $quiz_node);

    // Answer a question. Ensure the question navigation restrictions are
    // maintained.
    $this->drupalLogin($this->user);
    $this->drupalGet("node/{$quiz_node->nid}/take");
    $this->drupalGet("node/{$quiz_node->nid}/take/2");
    $this->assertResponse(403);
    $this->drupalGet("node/{$quiz_node->nid}/take/1");
    $this->drupalPost(NULL, array(
      "question[$question_node1->nid]" => 1,
      ), t('Next'));

    // Login again.
    $this->drupalLogin($this->user);
    $this->drupalGet("node/{$quiz_node->nid}/take");
    $this->assertText('Resuming');

    // Assert 2nd question is accessible (indicating the answer to #1 was
    // saved.)
    $this->drupalGet("node/{$quiz_node->nid}/take/2");
    $this->assertResponse(200);
  }

  /**
   * Test the quiz availability tests.
   */
  public function testQuizAvailability() {
    $future = REQUEST_TIME + 86400;
    $past = REQUEST_TIME - 86400;

    // Within range.
    $quiz_node = $this->drupalCreateQuiz(array(
      'quiz_always' => 0,
      'quiz_open' => $past,
      'quiz_close' => $future,
    ));
    $this->drupalGet("node/{$quiz_node->nid}");
    $this->assertNoText('This quiz is closed.');

    // Starts in the future.
    $quiz_node = $this->drupalCreateQuiz(array(
      'quiz_always' => 0,
      'quiz_open' => $future,
      'quiz_close' => $future + 1,
    ));
    $this->drupalGet("node/{$quiz_node->nid}");
    $this->assertText('This quiz is closed.');

    // Ends in the past.
    $quiz_node = $this->drupalCreateQuiz(array(
      'quiz_always' => 0,
      'quiz_open' => $past,
      'quiz_close' => $past + 1,
    ));
    $this->drupalGet("node/{$quiz_node->nid}");
    $this->assertText('This quiz is closed.');

    // Always available.
    $quiz_node = $this->drupalCreateQuiz(array(
      'quiz_always' => 1,
      'quiz_open' => $future,
      'quiz_close' => $past,
    ));
    $this->drupalGet("node/{$quiz_node->nid}");
    $this->assertNoText('This quiz is closed.');
  }

  /**
   * Test the 'view quiz question outside of a quiz' permission.
   */
  function testViewQuestionsOutsideQuiz() {
    $this->drupalLogin($this->admin);
    // Resuming is default behavior.
    $quiz_node = $this->drupalCreateQuiz();

    $question_node1 = $this->drupalCreateNode(array('type' => 'truefalse', 'correct_answer' => 1));
    $this->linkQuestionToQuiz($question_node1, $quiz_node);

    node_access_rebuild(FALSE);

    $this->drupalLogin($this->user);
    $this->drupalGet("node/{$question_node1->nid}");
    $this->assertResponse(403);

    $user_with_privs = $this->drupalCreateUser(array('view quiz question outside of a quiz', 'access quiz'));
    $this->drupalLogin($user_with_privs);
    $this->drupalGet("node/{$question_node1->nid}");
    $this->assertResponse(200);
  }

}
