<tbody id="quiz-browser-body" class="browser-table">
<?php
/**
 * @file
 * Handles the layout of the quiz question browser.
 *
 *
 * Variables available:
 * - $form
 */

// We need to separate the title and the checkbox. We make a custom options array...
$full_options = array();
foreach ($form['titles']['#options'] as $key => $value) {
  $full_options[$key] = $form['titles'][$key];
  $full_options[$key]['#title'] = '';
}

// We make the question rows
foreach ($form['titles']['#options'] as $key => $value): ?>
  <?php
  // Find nid and vid
  $matches = array();
  preg_match('/([0-9]+)-([0-9]+)/', $key, $matches);
  $quest_nid = $matches[1];
  $quest_vid = $matches[2]; ?>
  
  <tr class="quiz-question-browser-row" id="browser-<?php print $key ?>">
    <td width="35"><?php print drupal_render($full_options[$key]) ?> </td>
    <td>
      <?php if (user_access('view quiz question outside of a quiz')): ?>
        <?php print l($value, "node/$quest_nid", array(
          'html' => TRUE,
          'query' => array('destination' => $_GET['q']),
          'attributes' => array('target' => 'blank')
        )); ?>
      <?php else: ?>
        <?php print check_plain($value); ?>
      <?php endif; ?>
    </td>
    <td><?php print $form['types'][$key]['#value'] ?></td>
    <td><?php print $form['changed'][$key]['#value'] ?></td>
    <td><?php print $form['names'][$key]['#value'] ?></td>
  </tr>
<?php endforeach ?>

<?php if (count($form['titles']['#options']) == 0) {
  print t('No questions were found');
}
?>
</tbody>