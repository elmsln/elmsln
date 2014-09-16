<tbody id="quiz-browser-body">
<?php
// We need to separate the title and the checkbox. We make a custom options array...
$full_options = array();
foreach ($form['name']['#options'] as $key => $value) {
  $full_options[$key] = $form['name'][$key];
  $full_options[$key]['#title'] = '';
}
foreach ($form['name']['#options'] as $key => $value): ?>
  <tr class="quiz-results-browser-row" id="browser-<?php print $key ?>">
    <td valign="top">
      <?php
      // Find nid and rid
      $matches = array();
      preg_match('/([0-9]+)-([0-9]+)/', $key, $matches);
      $res_nid = $matches[1];
      $res_rid = $matches[2];?>
      <span class = "container-inline" style = "white-space: nowrap;"><?php print drupal_render($full_options[$key]) . $value?></span>
      <div class = "quiz-hover-menu"><?php print $form['hover_menu'][$key]['#value']?></div>
    </td><td valign="top">
      <?php print$form['started'][$key]['#value'] ?>
    </td><td valign="top">
      <?php print $form['finished'][$key]['#value'] ?>
      <?php if ($form['finished'][$key]['#value'] != t('In progress')): ?>
        <br/><em>(<?php print t('Duration') ?>: <?php print $form['duration'][$key]['#value'] ?>')</em>
      <?php endif ?>
    </td><td valign ="top">
      <?php if (!is_numeric($form['score'][$key]['#value'])): ?>
        <?php print $form['score'][$key]['#value'] ?>
      <?php elseif ($form['evaluated'][$key]['#value'] == t('No')): ?>
        <?php print t('Not evaluated') ?>
      <?php else: ?>
        <?php if (!empty($form['pass_rate'][$key]['#value']) && is_numeric($form['score'][$key]['#value'])) {
          $pre_score = $form['score'][$key]['#value'] >= $form['pass_rate'][$key]['#value'] ? '<span class = "quiz-passed">' : '<span class = "quiz-failed">';
          $post_score = $form['score'][$key]['#value'] >= $form['pass_rate'][$key]['#value'] ?' %<br><em>'. t('Passed') .'</em></span>' : ' %<br><em>'. t('Failed') .'</em></span>';
        }
        else {
          $post_score = ' %';
        } 
        print $pre_score . $form['score'][$key]['#value'] . $post_score ?>
      <?php endif ?>
    </td><td valign="top">
      <?php print $form['evaluated'][$key]['#value'] ?>
    </td>
  </tr>
<?php endforeach; ?>
</tbody>