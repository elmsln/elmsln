<?php

/**
 * @file
 * Template to display a view as a Harmony responsive table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */

?>
<div<?php if ($classes) { print ' class="'. $classes . '" '; } ?><?php print $attributes; ?>>
  <?php if (!empty($title) || !empty($caption)) : ?>
  <caption class="element-invisible sr-only"><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
  <div class="table-list-head">
    <ul class="list-unstyled table-list-row">
      <?php foreach ($header as $field => $label): ?>
      <li<?php if ($header_classes[$field]) { print ' class="'. $header_classes[$field] . '" '; } ?>><?php print $label; ?></li>
      <?php endforeach; ?>
    </ul>
  </div>
  <?php endif; ?>
  <ol class="list-unstyled table-list-body">
    <?php foreach ($rows as $row_count => $row): ?>
    <li<?php if ($row_classes[$row_count]) { print ' class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>
      <?php foreach ($row as $field => $content): ?>
      <div<?php if ($field_classes[$field][$row_count]) { print ' class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
        <?php print $content; ?>
      </div>
      <?php endforeach; ?>
    </li>
    <?php endforeach; ?>
  </ol>
</div>
