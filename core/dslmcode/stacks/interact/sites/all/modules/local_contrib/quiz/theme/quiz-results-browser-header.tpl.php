<thead id="quiz-browser-head">
  <tr>
    <?php foreach ($form['#header'] as $header): ?>
      <th><?php print $header['data'] ?></th>
    <?php endforeach ?>
  </tr>
  <tr id="quiz-question-browser-filters">
    <td class="container-inline" style="white-space: nowrap">
      <?php print drupal_render($form['filters']['all']) . drupal_render($form['filters']['name']) ?>
    </td><td>
      <?php print drupal_render($form['filters']['started']) ?>
    </td><td>
      <?php print drupal_render($form['filters']['finished']) ?>
    </td><td>
      <?php print drupal_render($form['filters']['score']) ?>
    </td><td>
      <?php print drupal_render($form['filters']['evaluated']) ?>
    </td>
  </tr>
</thead>