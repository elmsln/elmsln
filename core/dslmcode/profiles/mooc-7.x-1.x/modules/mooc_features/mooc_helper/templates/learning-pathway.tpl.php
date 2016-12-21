<div class="row elmsln-learning-pathway-wrapper">
<?php foreach ($tree as $link) : ?>
<div class="col s6 m3 l2 elmsln-learning-pathway-badge-wrapper">
  <a href="<?php print base_path() . $link['link']['link_path'];?>" class="tooltipped" data-position="bottom" data-delay="50" data-tooltip="<?php print $link['link']['link_title'];?>">
    <div class="elmsln-system-badge elmsln-learning-pathway-badge">
      <div class="elmsln-icon icon-content-outline <?php print $lmsless_classes['text'];?> elmsln-badge"></div>
      <div class="elmsln-badge-inner">
        <div class="elmsln-badge-top white-border"></div>
        <div class="elmsln-badge-middle white"></div>
        <div class="elmsln-badge-bottom white-border"></div>
      </div>
      <div class="elmsln-badge-outer">
        <div class="elmsln-badge-top <?php print $lmsless_classes['color'];?>-border"></div>
        <div class="elmsln-badge-middle <?php print $lmsless_classes['color'];?>"></div>
        <div class="elmsln-badge-bottom <?php print $lmsless_classes['color'];?>-border"></div>
      </div>
    </div>
  </a>
</div>
<?php endforeach;?>
</div>