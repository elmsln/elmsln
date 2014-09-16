<thead>
  <tr>
    <?php foreach ($form['#header'] as $header): ?>
      <th><?php print $header['data'] ?></th>
    <?php endforeach ?>
  </tr>
  <tr id="quiz-question-browser-filters">
    <td><?php print drupal_render($form['filters']['all']) ?></td>
    <td><?php print drupal_render($form['filters']['title']) ?></td>
    <td><?php print drupal_render($form['filters']['type']) ?></td>
    <td><?php print drupal_render($form['filters']['changed']) ?></td>
    <td><?php print drupal_render($form['filters']['name']) ?></td>
  </tr>
</thead>

