<?php
  /**
   * Contextual container for wrapping contextual links into page elements.
   */
?>
  <div id="off-canvas-admin-menu-<?php print $short ?>" data-dropdown-content class="f-dropdown content <?php print $classes; ?>" <?php print $attributes; ?> aria-hidden="true" tabindex="-1">

  </div>

<nav class="top-bar" data-topbar role="navigation">
<section class="right top-bar-section">
<a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="off-canvas-admin-menu-<?php print $short ?>" aria-controls="offcanvas-admin-menu" aria-expanded="false">
<div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
</a>
</section>
</nav>
