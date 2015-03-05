<?php
/**
 * @file field--fences-figcaption.tpl.php
 * Wrap each field value in the <figcaption> element.
 *
 * @see http://developers.whatwg.org/grouping-content.html#the-figcaption-element
 *
 * Only one figcaption is allowed per figure element, so multiple field values
 * are placed within a single figcaption.
 */
?>
<figcaption class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php if ($element['#label_display'] == 'inline'): ?>
    <span class="field-label"<?php print $title_attributes; ?>>
      <?php print $label; ?>:
    </span>
  <?php elseif ($element['#label_display'] == 'above'): ?>
    <h3 class="field-label"<?php print $title_attributes; ?>>
      <?php print $label; ?>
    </h3>
  <?php endif; ?>

  <?php foreach ($items as $delta => $item): ?>
    <?php print render($item); ?>
  <?php endforeach; ?>

</figcaption>
