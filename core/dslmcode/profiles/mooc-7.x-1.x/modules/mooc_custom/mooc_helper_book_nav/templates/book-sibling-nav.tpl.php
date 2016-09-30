<?php
  /**
   * Print book items that are on the same level so we can keep context
   * of pacing through a lesson of instruction.
   *
   * Variables
   * $parent - menu item that is the parent of all these child items
   * $items - an array of menu items, optionally with count and icon defined
   */
  $parent_count = '';
  $parent_icon = '';
  $parent_title = check_plain($parent['link_title']);
  // support for ... with screen readers
  if ($parent['mlid'] == -1) {
    $ptitle = t('Pages nested below the current one.');
  }
  else {
    $ptitle = t('Pages on the same level as @name', array('@name' => $parent_title));
  }
  // support for count on the lowest level parent
  if (isset($outline_count) && $outline_count) {
    if (isset($parent['_count'])) {
      $parent_count = $parent['_count'] . '. ';
    }
  }
  // support for icon on lowest level parent
  if (isset($parent['_icon'])) {
    $parent_icon = '<div class="book-sibling-parent-icon book-menu-item-' . $parent['mlid'] . ' icon-' . $parent['_icon'] . '-black outline-nav-icon"></div>';
  }
  // make sure this isset
  if (!isset($outline_label)) {
    $outline_label = '';
  }
?>
<li class="toolbar-menu-icon book-sibling-parent book-sibling-parent-<?php print $count ?>">
    <a href="#" title="<?php print $ptitle ?>" class="elmsln-dropdown-button <?php print (isset($parent['_class']) ? $parent['_class'] : ''); ?>" aria-controls="book-sibling-children-<?php print $parent['mlid'] ?>" aria-expanded="false" data-activates="book-sibling-children-<?php print $parent['mlid'] ?>">
      <div class="book-sibling-parent-text"><?php print $outline_label; ?> <?php print $parent_count; ?> <?php print $parent_title ?></div>
      <?php if ($parent_icon !== ''): ?><?php print $parent_icon ?><?php endif; ?>
      <div class="book-sibling-parent-arrow icon--dropdown off-canvas-toolbar-item-icon"></div>
    </a>
</li>
<ul id="book-sibling-children-<?php print $parent['mlid'] ?>" class="content dropdown-content book-sibling-children elmsln-scroll-bar" aria-hidden="true" tabindex="-1">
<?php
  foreach ($items as $item) {
    // look for active trail item
    if ($parent['link_path'] == $item['link_path']) {
      $active = 'book-menu-item-active';
    }
    else {
      $active = 'book-item';
    }
    $pre = '';
    if (isset($outline_count) && $outline_count && isset($item['_count'])) {
      $pre .= $item['_count'] . '. ';
    }
    // check for icon, we only render these at lowest level
    if (isset($item['_icon'])) {
      $pre .= '<div class="book-menu-item-' . $item['mlid'] . ' icon-' . $item['_icon'] . '-black outline-nav-icon"></div>';
    }
    $link_title = check_plain($item['link_title']);
    $link = '<li class="' . $active . '">' . l($pre . $link_title,
        $item['link_path'],
        array('html' => TRUE,
          'attributes' => array(
            'title' => $link_title,
            'class' => array($active . '-link'),
          )
        )
      ) . '</li>' . "\n";
    print $link;
  }
?>
</ul>
