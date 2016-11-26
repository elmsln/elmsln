<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */

?>
<div class ="user-profile--wrapper">
  <div class="parallax-container ferpa-protect">
    <div class="parallax"><?php print render($banner);?></div>
  </div>
  <div class ="user-profile--photo--wrapper">
    <div class ="user-profile--photo circle">
      <?php print $photo; ?>
    </div>
  </div>
  <div class="user-profile--name ferpa-protect">
    <?php print $displayname; ?>
  </div>
  <div class="row">
    <div class="col s12">
      <ul class="tabs">
      <?php foreach ($tabs as $key => $tab) : ?>
        <li class="tab col s3"><a href="#user__<?php print $key;?>"><?php print $tab;?></a></li>
      <?php endforeach; ?>
      </ul>
    </div>
    <?php foreach ($tabs_content as $key => $tab_content) : ?>
    <div id="user__<?php print $key;?>" class="user-profile--<?php print $key;?> col s12 ferpa-protect">
      <?php print render($tab_content);?>
    </div>
    <?php endforeach; ?>
  </div>
</div>
