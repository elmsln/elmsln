<?php
  /**
   * CIS LMS-less template file
   *
   * @todo dropdowns for available sections to switch.
   * @todo replace home text with icon.
   * Available variables
   * $services - an array containing the url and title of all other services
   * the user currently has access to.
   * $front_page - link to the front page of the current site
   * $site_name - the name of the site
   * $section - the active section of the current user
   * $active - the part of the services array relating to the current system
   * being worked with.
   */
?>
<div class="cis-lmsless-container cis-lmsless-bar <?php print $classes; ?>" <?php print $attributes; ?>>
  <div class="cis-lmsless-item cis-lmsless-home"><?php print l('HOME', $front_page); ?></div>
  <div class="cis-lmsless-item cis-lmsless-site-name"><?php print $site_name; ?></div>
  <div class="cis-lmsless-item cis-lmsless-active-section"> <?php print $section; ?></div>
  <select class="cis-lmsless-item cis-lmsless-bar-services">
  <?php foreach ($services as $service) : ?>
    <option class="cis-lmsless-bar-service" value="<?php print $service['url']; ?>"><?php print $service['title']; ?></option>
  <?php endforeach ?>
  </select>
</div>
