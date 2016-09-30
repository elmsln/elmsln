<?php
  /**
   * CIS LMS-less User block template.
   */
  // support authcache_cookie value that gets dynamically loaded instead
  if (isset($user_name)) {
    $username = $user_name;
  }
?>
  <li class="ferpa-protect">
    <div class="userView">
      <img class="background" src="http://materializecss.com/images/office.jpg" alt="">
      <?php if (isset($userpicturebig)) { print $userpicturebig; } ?>
      <?php if (!empty($username)) : ?>
        <a><span class="white-text name"><?php print "$username"; ?></span></a>
      <?php endif; ?>
      <a><span class="white-text section-title"><?php if (isset($section_title)) { print $section_title; } ?></span></a>
      <a><span class="white-text user-roles"><?php if (!empty($user_roles)) { print $user_roles; } ?></span></a>
    </div>
  </li>
<?php if (!empty($username)) : ?>
  <li><?php print $userprofile; ?></li>
<?php endif; ?>
<?php if (isset($user_section) || !empty($masquerade)) : ?>
  <li><div class="divider cis-lmsless-background"></div></li>
<?php endif; ?>
<?php if (!empty($ferpa_flter)) : ?>
  <li><?php print $ferpa_flter; ?></li>
<?php endif; ?>
<?php if (isset($user_section)) : ?>
  <li><?php print $user_section; ?></li>
<?php endif; ?>
<?php if (!empty($masquerade)) : ?>
  <li><?php print $masquerade; ?></li>
<?php endif; ?>
  <li><div class="divider cis-lmsless-background"></div></li>
  <li><?php print $userlink; ?></li>
