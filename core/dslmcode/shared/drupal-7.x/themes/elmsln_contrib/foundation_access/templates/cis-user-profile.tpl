<a class="button split" href="<?php print $front_page; ?>">
	<?php
		global $user;
		print t('!username', array('!username' => theme('username', array('account' => $user)))),
	?>
<span data-dropdown="drop"></span></a><br>
<ul id="drop" class="f-dropdown" <?php print $attributes; ?> data-dropdown-content>
  <!-- <li class="cis-lmsless-item cis-lmsless-site-name"><?php print $site_name; ?></li> -->
  <!-- <li class="cis-lmsless-item cis-lmsless-active-section"> <?php print $section; ?></li> -->
    <?php foreach ($services as $service) : ?>
      <li><a href="<?php print $service['url']; ?>"><?php print $service['title']; ?></a><li>
    <?php endforeach ?>
</ul>
