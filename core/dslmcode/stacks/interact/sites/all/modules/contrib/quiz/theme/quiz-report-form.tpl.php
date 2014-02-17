<?php

/**
 * @file
 * Themes the question report
 *
 * Available variables:
 * $form - FAPI array
 *
 * All questions are in form[x] where x is an integer.
 * Useful values:
 * $form[x]['question'] - the question as a FAPI array(usually a form field of type "markup")
 * $form[x]['score'] - the users score on the current question.(FAPI array usually of type "markup" or "textfield")
 * $form[x]['max_score'] - the max score for the current question.(FAPI array of type "value")
 * $form[x]['response'] - the users response, usually a FAPI array of type markup.
 * $form[x]['#is_correct'] - If the users response is correct(boolean)
 * $form[x]['#is_evaluated'] - If the users response has been evaluated(boolean)
 */
// $td_classes = array('quiz-report-odd-td', 'quiz-report-even-td');
// $td_class_i = 0;
$p = drupal_get_path('module', 'quiz') .'/theme/';
$q_image = $p. 'question_bg.png';
?>
<h2><?php print t('Question Results');?></h2>
<div class="quiz-report">
<?php
foreach ($form as $key => $sub_form):
  if (!is_numeric($key) || isset($sub_form['#no_report'])) continue;
  unset($form[$key]);
  $c_class = ($sub_form['#is_evaluated']) ? ($sub_form['#is_correct']) ? 'q-correct' : 'q-wrong' : 'q-waiting';
  $skipped = $sub_form['#is_skipped'] ? '<span class="quiz-report-skipped">'. t('(skipped)') .'</span>' : ''?>

	<div class="dt">
	  <div class="quiz-report-score-container <?php print $c_class?>">
	  	<span>
	      <?php print t('Score')?>
        <?php print drupal_render($sub_form['score'])?>
        <?php print t('of') .' '. $sub_form['max_score']['#value']?>
        <?php print '<br><em>'. $skipped .'</em>'?>
      </span>
    </div>
	  <p class="quiz-report-question"><strong><?php print t('Question')?>: </strong></p>
	  <?php print drupal_render($sub_form['question']);?>
	</div>
  <div class="dd">
    <p><strong><?php print t('Response')?>: </strong></p>
    <?php print drupal_render($sub_form['response']); ?>
  </div>
  <div class="dd">
    <?php print drupal_render($sub_form['answer_feedback']); ?>
  </div>
<?php endforeach; ?>
</div>
<div class="quiz-score-submit"><?php print drupal_render_children($form);?></div>
