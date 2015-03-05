<?php
/**
 * @file field--fences-small.tpl.php
 * Wrap each field value in the <small> element.
 *
 * @see http://developers.whatwg.org/text-level-semantics.html#the-small-element
 */
?>
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
  <small class="<?php print $classes; ?>"<?php print $attributes; ?>>
    <?php print render($item); ?>
  </small>
<?php endforeach; ?>
