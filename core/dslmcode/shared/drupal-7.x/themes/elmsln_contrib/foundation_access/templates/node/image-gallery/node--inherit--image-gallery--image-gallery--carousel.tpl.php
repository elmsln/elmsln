<div class="row elmsln-carousel-wrapper">
  <div class="carousel">
  <?php foreach ($images as $key => $image) : ?>
    <a class="carousel-item" href="#carousel-<?php print $nid . '-' . $key;?>"><?php print render($image); ?></a>
  <?php endforeach; ?>
  </div>
</div>