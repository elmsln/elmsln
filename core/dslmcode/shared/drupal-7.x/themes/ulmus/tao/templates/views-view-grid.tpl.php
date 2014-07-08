<?php
reset($rows);
$gridsize = count($rows[0]);
?>
<?php if (!empty($title)) : ?>
  <h3 class="grid-title"><?php print $title; ?></h3>
<?php endif; ?>
<table class="views-view-grid grid-<?php print $gridsize ?>">
  <tbody>
    <?php foreach ($rows as $row_number => $columns): ?>
      <?php
        $row_class = 'row-' . ($row_number + 1);
        if ($row_number == 0 && count($rows) > 1) {
          $row_class .= ' row-first';
        }
        elseif (count($rows) == ($row_number + 1)) {
          $row_class .= ' row-last';
        }
      ?>
      <tr class="<?php print $row_class; ?>">
        <?php foreach ($columns as $column_number => $item): ?>
          <td class="<?php print 'col-'. ($column_number + 1); ?>">
            <div class="grid-item"><?php print $item; ?></div>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
