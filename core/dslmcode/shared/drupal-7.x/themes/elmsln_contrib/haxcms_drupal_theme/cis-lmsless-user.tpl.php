<ul style="margin:-24px">
  <li class="ferpa-protect">
    <div class="user-drawer-block">
      <div class="details white">
        <div class="user-details-image">
          <?php if (isset($userpicturebig)) { print $userpicturebig; } ?>
        </div>
        <div class="user-details-text">
          <?php if (!empty($username)) : ?>
            <div class="name"><?php print "$username"; ?></div>
          <?php endif; ?>
          <div class="section-title"><?php if (isset($section_title)) { print $section_title; } ?></div>
          <div class="user-roles"><?php if (!empty($user_roles)) { print $user_roles; } ?></div>
        </div>
      </div>
    </div>
  </li>
  <?php if (!empty($username) && $username !== t("Anonymous")) : ?>
  <li>
    <lrnsys-button label="<?php print $userprofile['label']; ?>" href="<?php print $userprofile['href']; ?>" class="<?php if (is_array($userprofile['class'])) { print implode(' ', $userprofile['class']); } ?>" icon="<?php print $userprofile['icon']; ?>" hover-class="<?php if(is_array($userprofile['hover-class'])) {print implode(' ', $userprofile['hover-class']);} ?>"></lrnsys-button>
  </li>
  <?php endif; ?>
  <?php if (isset($user_section)) : ?>
  <li><div class="divider"></div></li>
  <li>
    <lrnsys-dialog header="<?php print t('Change section');?>">
      <div slot="button" class="lrnsys-dialog-button">
        <simple-icon icon="perm-identity"></simple-icon>
        <span><?php print t('Change section');?></span>
      </div>
      <div slot="content">
        <?php print $user_section; ?>
      </div>
    </lrnsys-dialog>
  </li>
  <?php endif; ?>
  <?php if (!empty($masquerade)) : ?>
    <li><div class="divider"></div></li>
  <li>
    <lrnsys-dialog header="<?php print t('Impersonate account');?>">
      <div slot="button" class="lrnsys-dialog-button">
        <simple-icon icon="supervisor-account"></simple-icon>
        <span><?php print t('Impersonate account');?></span>
      </div>
      <div slot="content">
        <?php print $masquerade; ?>
      </div>
    </lrnsys-dialog>
  </li>
  <?php endif; ?>
  <?php if (!empty($masquerade_logout)) : ?>
  <li><?php print $masquerade_logout; ?></li>
  <?php endif; ?>
  <li><div class="divider"></div></li>
  <li>
    <lrnsys-button label="<?php print $userlink['label']; ?>" href="<?php print $userlink['href']; ?>" class="<?php print implode(' ', $userlink['class']); ?>" icon="<?php print $userlink['icon']; ?>" hover-class="<?php print implode(' ', $userlink['hover-class']); ?>"></lrnsys-button>
  </li>
</ul>
