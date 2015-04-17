<?php
  /**
   * Contextual container for wrapping contextual links into page elements.
   */
?>
  <div id="off-canvas-admin-menu-<?php print $short ?>" data-dropdown-content class="f-dropdown content <?php print $classes; ?>" <?php print $attributes; ?> aria-hidden="true" tabindex="-1">
    <ul class="button-group">
      <?php
      foreach ($cis_links as $link) {
        if (isset($link['warning'])) {
          $li = '<li class="cis-link-warning">';
        }
        else {
          $li = '<li>';
        }
        if (isset($link['title'])) {
          print $li . l(t($link['title']), $link['href']) .'</li>';
        }
      }
      ?>
      <hr>
      <li><a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">Course Settings</a></li>
    </ul>
  </div>

<nav class="top-bar" data-topbar role="navigation">
<section class="right top-bar-section">
<a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="off-canvas-admin-menu-<?php print $short ?>" aria-controls="offcanvas-admin-menu" aria-expanded="false">
<div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
</a>
</section>
</nav>
