<ul>
  <li class="ferpa-protect">
    <div class="user-drawer-block">
      <?php print $userbackground; ?>
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
  <?php if (!empty($username)) : ?>
  <li>
    <lrnsys-button label="<?php print $userprofile['label']; ?>" href="<?php print $userprofile['href']; ?>" class="<?php print implode(' ', $userprofile['label']); ?>" icon="<?php print $userprofile['icon']; ?>" hover-class="<?php print implode(' ', $userprofile['label']); ?>"></lrnsys-button>
  </li>
  <?php endif; ?>
  <?php if (isset($user_section) || !empty($masquerade)) : ?>
  <li><div class="divider"></div></li>
  <?php endif; ?>
  <li>
    <lrnsys-dialog header="<?php print t('Preferences'); ?>" class="black-text" hover-class="<?php print $lmsless_classes[$distro]['color'] . ' ' . $lmsless_classes[$distro]['dark'];?> white-text" data-jwerty-key="a" data-voicecommand="open preferences (menu)">
      <span slot="button">
        <iron-icon icon="accessibility"></iron-icon>
        <span><?php print t('Preferences');?></span>
      </span>
      <span slot="content">
        <?php print $a11y; ?>
      </span>
    </lrnsys-dialog>
  </li>
  <?php if (isset($user_section)) : ?>
  <li>
    <lrnsys-dialog header="<?php print t('Change section');?>" class="black-text" hover-class="<?php print $lmsless_classes[$distro]['color'] . ' ' . $lmsless_classes[$distro]['dark'];?> white-text">
      <span slot="button">
        <iron-icon icon="perm-identity"></iron-icon>
        <span><?php print t('Change section');?></span>
      </span>
      <span slot="content">
        <?php print $user_section; ?>
      </span>
    </lrnsys-dialog>
  </li>
  <?php endif; ?>
  <?php if (!empty($masquerade)) : ?>
  <li>
    <lrnsys-dialog header="<?php print t('Impersonate account');?>" class="black-text" hover-class="<?php print $lmsless_classes[$distro]['color'] . ' ' . $lmsless_classes[$distro]['dark'];?> white-text">
      <span slot="button">
        <iron-icon icon="supervisor-account"></iron-icon>
        <span><?php print t('Impersonate account');?></span>
      </span>
      <span slot="content">
        <?php print $masquerade; ?>
      </span>
    </lrnsys-dialog>
  </li>
  <?php endif; ?>
  <?php if (!empty($masquerade_logout)) : ?>
  <li><?php print $masquerade_logout; ?></li>
  <?php endif; ?>
  <li><div class="divider"></div></li>
  <li>
    <lrnsys-button label="<?php print $userlink['label']; ?>" href="<?php print $userlink['href']; ?>" class="<?php print implode(' ', $userlink['label']); ?>" icon="<?php print $userlink['icon']; ?>" hover-class="<?php print implode(' ', $userlink['label']); ?>"></lrnsys-button>
  </li>
</ul>
