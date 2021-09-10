<?php

/**
 * @file
 * Default theme implementation for printed version of entity iframe.
 *
 * Available variables:
 * - $title: Top level node title.
 * - $language: Language code. e.g. "en" for english.
 * - $language_rtl: TRUE or FALSE depending on right to left language scripts.
 * - $base_url: URL to home page.
 * - $contents: Nodes within the current outline rendered through
 *   entity-iframe.tpl.php.
 *
 * @see template_preprocess_entity_iframe()
 *
 * @ingroup themeable
 */
?>
<?php if ($messages): ?>
  <div class="messages">
    <?php print $messages; ?>
  </div>
<?php endif; ?>
<div class="entity_iframe_container">
<?php print $contents; ?>
</div>