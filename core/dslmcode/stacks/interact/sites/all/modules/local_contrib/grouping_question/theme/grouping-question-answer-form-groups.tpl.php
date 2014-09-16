<?php

/**
 * @file
 * Handles the layout of the grouping creation form.
 *
 *
 * Variables available:
 *  - $members: array of items to be sorted by the user key'd by their id
 *  - $answer_titles: array of groups the items need to be dragged into
 */
?>
<div class="quiz-grouping-container">
<?php foreach ($members as $i => $member) : ?>
  <div class="quiz-grouping-member" id="quiz-grouping-member-<?php print $i; ?>"><?php print $member; ?></div>
<?php endforeach; ?>

<?php foreach ($answer_titles as $id => $title) : ?>
  <div class="quiz-grouping-group" id="quiz-grouping-group-<?php print $id; ?>"><?php print $title; ?></div>
<?php endforeach; ?>

<div class="quiz-grouping-answer-fields"><?php print $answers; ?></div>
</div>
