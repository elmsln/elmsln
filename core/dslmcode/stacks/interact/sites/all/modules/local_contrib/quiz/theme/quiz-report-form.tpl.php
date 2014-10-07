<?php
/**
 * @file
 * Themes the question report
 *
 */
/*
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
?>
<h2><?php print t('Question Results'); ?></h2>
<div class="quiz-report">
  <?php
  foreach ($form as $key => $sub_form):
    if (!is_numeric($key) || isset($sub_form['#no_report']))
      continue;
    unset($form[$key]);
    ?>
    <div class="dt">
      <?php print drupal_render($sub_form['score_display']); ?>
      <h3 class="quiz-report-question"><strong><?php print t('Question') ?></strong></h3>
      <?php print drupal_render($sub_form['question']); ?>
    </div>
    <div class="dd">
      <h3><strong><?php print t('Response') ?>:</strong></h3>
      <?php print drupal_render($sub_form['response']); ?>
    </div>
    <div class="dd">
      <?php print drupal_render($sub_form['score']); ?>
      <?php print drupal_render($sub_form['answer_feedback']); ?>
    </div>
    <hr/>
  <?php endforeach; ?>
</div>
<div class="quiz-score-submit"><?php print drupal_render_children($form); ?></div>
