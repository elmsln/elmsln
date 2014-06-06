<?php
  /**
   * CIS LMS-less template file
   *
   * @todo Add course slogan to button's link div.
   */
?>
<a class="main-nav button split" href="<?php print $front_page; ?>"><?php print $site_name; ?> <div class="slogan-lmsless-button"><?php print $slogan; ?></div><span data-dropdown="lmsless-button"></span></a>
<ul id="lmsless-button" class="f-dropdown" <?php print $attributes; ?> data-dropdown-content>
  <!-- <li class="cis-lmsless-item cis-lmsless-site-name"><?php print $site_name; ?></li> -->
  <!-- <li class="cis-lmsless-item cis-lmsless-active-section"> <?php print $section; ?></li> -->
    <?php foreach ($services as $service) : ?>
      <li><a href="<?php print $service['url']; ?>"><?php print $service['title']; ?></a><li>
    <?php endforeach ?>
</ul>
