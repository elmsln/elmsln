<?php

/**
 * @file
 * A sample panel layout template, to see how to build your own.
 */
?>

<div class="panel-layout aurora-sample-layout <?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print 'id="' . $css_id . '"'; } ?>>
  <section class="aurora-sample-section aurora-section-first">
    <?php print $content['first']; ?>
  </section>
  <section class="aurora-sample-section aurora-section-second">
    <?php print $content['second']; ?>
  </section>
  <section class="aurora-sample-section aurora-section-third">
    <?php print $content['third']; ?>
  </section>
</div>
