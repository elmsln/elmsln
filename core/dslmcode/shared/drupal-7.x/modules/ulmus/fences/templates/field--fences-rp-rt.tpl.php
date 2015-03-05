<?php
/**
 * @file field--fences-rp-rt.tpl.php
 * Wrap each field value in the <rt> element with adjacent <rp> elements.
 *
 * @see http://developers.whatwg.org/text-level-semantics.html#the-rp-element
 * @see http://developers.whatwg.org/text-level-semantics.html#the-rt-element
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
  <rp>(</rp><rt class="<?php print $classes; ?>"<?php print $attributes; ?>>
    <?php print render($item); ?>
  </rt><rp>)</rp>
<?php endforeach; ?>
