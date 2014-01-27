<?php

/**
 * @file
 * Template for the configuration table
 */

$regions = nodeformcols_form_regions();
?>
<table id="fields" class="sticky-enabled">
  <thead>
    <tr>
      <th><?php print t('Field'); ?></th>
      <th><?php print t('Options'); ?></th>
      <th><?php print t('Region'); ?></th>
      <th><?php print t('Weight'); ?></th>
    </tr>
  </thead>
  <tbody>
    <?php $row = 0; ?>
    <?php foreach ($regions as $region => $title): ?>
      <tr class="region region-<?php print $region?>">
        <td colspan="4" class="region"><?php print $title; ?></td>
      </tr>
      <tr class="region-message region-<?php print $region?>-message <?php print empty($element[$region]) ? 'region-empty' : 'region-populated'; ?>">
        <td colspan="4"><em><?php print t('No fields in this region'); ?></em></td>
      </tr>
      <?php if (!empty($element[$region])): ?>
        <?php foreach ($element[$region] as $field => $data): ?>
          <?php
            if (substr($field, 0, 1) == '#') {
              continue;
            }
          ?>
        <tr class="draggable <?php print $row % 2 == 0 ? 'odd' : 'even'; ?>">
          <td><?php print drupal_render($data[$field . '_name']) ?></td>
          <td><?php
            if (isset($data[$field . '_collapsed'])) {
              print drupal_render($data[$field . '_collapsed']);
            }
            if (isset($data[$field . '_hidden'])) {
              print drupal_render($data[$field . '_hidden']);
            }
          ?></td>
          <td><?php print drupal_render($data[$field . '_region']) ?></td>
          <td><?php print drupal_render($data[$field . '_weight']) ?></td>
        </tr>
        <?php $row++; ?>
        <?php endforeach; ?>
      <?php endif; ?>
    <?php endforeach; ?>
  </tbody>
</table>
