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
  <?php if (!empty($username)) : ?>
    <h2><?php print "$username ($userprofile) "; ?><span style="float:right;"><?php print $userlink; ?></span></h2>
    <?php if (isset($userpicturebig)) { print $userpicturebig; } ?>
  <?php endif; ?>
  <?php if (isset($user_roles)) : ?>
  <h2><?php print t('Roles'); ?></h2>
  <div class="user-nav-user-roles">
    <?php print $user_roles; ?>
  </div>
  <?php endif; ?>
  <hr class="pad-1" />
  <?php if (isset($masquerade)) : ?>
  <h2><?php print t('Impersonate'); ?></h2>
  <div class="cis-admin-area user-nav-masquerade">
    <?php print $masquerade; ?>
  </div>
  <?php endif; ?>
  <hr class="pad-1" />
  <?php if (isset($section_title)) : ?>
  <h2><?php print t('Section'); ?></h2>
  <div class="cis-admin-area user-nav-section">
    <?php print $user_section; ?>
  </div>
  <?php endif; ?>
  <hr />