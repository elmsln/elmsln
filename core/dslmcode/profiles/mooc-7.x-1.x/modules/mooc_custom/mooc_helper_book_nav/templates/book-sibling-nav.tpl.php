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
  $parent_title = filter_xss($parent['link_title'], array('iron-icon'));
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
  // make sure this isset
  if (!isset($outline_label)) {
    $outline_label = '';
  }
?>
<li id="book-sibling-children-<?php print $parent['mlid'] ?>-container" class="toolbar-menu-icon book-sibling-parent book-sibling-parent-<?php print $parent_count ?>">
  <lrnsys-button href="#" class="black-text elmsln-dropdown-button <?php print (isset($parent['_class']) ? $parent['_class'] : ''); ?> no-padding" aria-controls="book-sibling-children-<?php print $parent['mlid'] ?>" aria-expanded="false" data-activates="book-sibling-children-<?php print $parent['mlid'] ?>" hover-class="grey darken-3 white-text" inner-class="no-padding">
    <span class="element-invisible"><?php print $ptitle ?></span>
    <span class="book-sibling-parent-text"><?php print $outline_label; ?> <?php print $parent_count; ?> <?php print $parent_title ?></span>
  </lrnsys-button>
</li>
<li>
  <ul id="book-sibling-children-<?php print $parent['mlid'] ?>" class="content dropdown-content book-sibling-children elmsln-scroll-bar" aria-hidden="true" tabindex="-1">
  <?php
    foreach ($items as $item) {
      // look for active trail item
      if ($parent['link_path'] == $item['link_path']) {
        $active = 'book-menu-item-active ';
      }
      else {
        $active = 'book-item ';
      }
      $pre = '';
      if (isset($outline_count) && $outline_count && isset($item['_count'])) {
        $pre .= $item['_count'] . '. ';
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
</li>