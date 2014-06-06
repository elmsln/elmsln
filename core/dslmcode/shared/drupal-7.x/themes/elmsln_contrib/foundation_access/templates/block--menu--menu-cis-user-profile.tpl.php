<!-- <ul class="main-nav left" <?php print $attributes; ?>>
	<li class="has-dropdown">
		<a href="#"><?php print check_plain($GLOBALS['user']->name); ?></a>
		<ul class="dropdown">
			<?php print $content; ?>
		</ul>
	</li>
</ul>
 -->

<a href="#" data-dropdown="user-profile-dropdown" class="button dropdown user-profile-dropdown"><?php print check_plain($GLOBALS['user']->name); ?></a><br>
<ul id="user-profile-dropdown" data-dropdown-content class="f-dropdown">
  <?php print $content; ?>
</ul>