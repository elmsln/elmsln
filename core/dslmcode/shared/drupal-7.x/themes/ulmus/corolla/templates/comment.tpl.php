<article class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $unpublished; ?>

  <?php print $picture; ?>

  <?php print render($title_prefix); ?>
  <?php if ($title || $new || $submitted): ?>
  <header<?php print $header_attributes; ?>>
 
    <?php if ($title): ?>
      <h3<?php print $title_attributes; ?>><?php print $title ?></h3>
    <?php endif; ?>

    <?php if ($new): ?>
      <em class="new"><?php print $new ?></em>
    <?php endif; ?>
    
    <p class="comment-submitted"><?php print $submitted; ?><p>
  </header>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div<?php print $content_attributes; ?>>
    <?php
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php if ($signature): ?>
    <div class="user-signature"><?php print $signature ?></div>
  <?php endif; ?>

  <?php if ($links = render($content['links'])): ?>
    <nav<?php print $links_attributes; ?>><?php print $links; ?></nav>
  <?php endif; ?>

</article>
