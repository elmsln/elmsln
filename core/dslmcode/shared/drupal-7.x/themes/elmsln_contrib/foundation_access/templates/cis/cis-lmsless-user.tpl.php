<?php
  /**
   * CIS LMS-less User block template.
   */
  // support authcache_cookie value that gets dynamically loaded instead
  if (isset($user_name)) {
    $username = $user_name;
  }
?>
  <h1><?php print t('Account'); ?></h1>
  <hr class="pad-1" />
  <?php if (empty($username)) : ?>
    <h2><span style="float:right;"><?php print $userlink; ?></span></h2>
  <?php endif; ?>
  <?php if (!empty($username)) : ?>
    <h2 class="ferpa-protect"><?php print "$username ($userprofile) "; ?><span style="float:right;"><?php print $userlink; ?></span></h2>
    <?php if (isset($userpicturebig)) { print $userpicturebig; } ?>
  <?php endif; ?>
  <?php if (!empty($user_roles)) : ?>
  <h2><?php print t('Roles'); ?></h2>
  <div class="user-nav-user-roles">
    <?php print $user_roles; ?>
  </div>
  <?php endif; ?>
  <?php if (!empty($masquerade)) : ?>
  <hr class="pad-1" />
  <h2><?php print t('Impersonate'); ?></h2>
    <?php print $masquerade; ?>
  <?php endif; ?>
  <?php if (!empty($ferpa_flter)) : ?>
  <hr class="pad-1" />
  <h2><?php print t('Privacy settings'); ?></h2>
    <?php print $ferpa_flter; ?>
  <?php endif; ?>
  <?php if (isset($section_title)) : ?>
  <hr class="pad-1" />
  <h2><?php print t('Section'); ?></h2>
  <div class="user-nav-section ferpa-protect">
    <?php print $user_section; ?>
  </div>
  <?php endif; ?>
  <hr />