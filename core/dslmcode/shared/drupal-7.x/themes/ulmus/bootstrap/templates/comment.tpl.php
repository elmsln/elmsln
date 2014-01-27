<article class="<?php print $classes . ' ' . $zebra; ?>"<?php print $attributes; ?>>
  
  <header>
    <p class="submitted">
      <?php print $picture; ?>
      <?php print $submitted; ?>
      <?php print $permalink; ?>
    </p>

    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h3<?php print $title_attributes; ?>>
        <?php print $title; ?>
        <?php if ($new): ?>
          <mark class="new label label-important"><?php print $new; ?></mark>
        <?php endif; ?>
      </h3>
    <?php elseif ($new): ?>
      <mark class="new label label-important"><?php print $new; ?></mark>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
  </header>

  <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['links']);
    print render($content);
  ?>

  <?php if ($signature): ?>
    <footer class="user-signature clearfix">
      <?php print $signature; ?>
    </footer>
  <?php endif; ?>

  <?php print render($content['links']) ?>
</article> <!-- /.comment -->
