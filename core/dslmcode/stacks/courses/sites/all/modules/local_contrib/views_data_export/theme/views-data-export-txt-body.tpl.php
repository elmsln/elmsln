<?php
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $rows: An array of row items. Each row is an array of content
 *   keyed by field ID.
 * - $header: an array of haeaders(labels) for fields.
 * - $themed_rows: a array of rows with themed fields.
 * @ingroup views_templates
 */

foreach ($themed_rows as $count => $row):
  foreach ($row as $field => $content):
?>
[<?php print $header[$field]; ?>]

<?php print strip_tags($content); // strip html so its plain txt. ?>

<?php endforeach; ?>
----------------------------------------

<?php endforeach;