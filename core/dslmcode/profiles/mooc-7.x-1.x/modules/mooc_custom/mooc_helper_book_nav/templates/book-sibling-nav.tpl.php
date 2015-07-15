<?php
  /**
   * Print book items that are on the same level so we can keep context
   * of pacing through a lesson of instruction.
   *
   * Variables
   * $items - Array of items to render with the following array positions
   *     nid -- node id
   *     mlid -- menu id of the node / book page
   *     title -- title of the node
   *     icon -- icon to use for visualization
   *     active -- class name to append to represent where they are in the lesson
   *     print-title -- boolean if the page title should be printed
   *     tree - tree of child links
   */
?>
<div class="small-12 medium-12 large-centered large-10 columns book-sibling-nav-container">
<?php
  foreach ($items as $item) {
    $icon = '<div class="book-menu-item-' . $item['mlid'] . ' icon-' . $item['icon'] . '-black outline-nav-icon"></div>';
    if (isset($item['print-title']) && $item['print-title']) {
      $icon .= $item['title'];
    }
    if (is_numeric($item['nid'])) {
      $link = l($icon,
        'node/' . $item['nid'],
        array('html' => TRUE,
          'attributes' => array(
            'class' => array(
              'book-sibling-nav-link'
            ),
            'title' => $item['title']
          )
        )
      );
    }
    else {
      $link = $icon;
    }
    if (!empty($item['tree'])) {
        $link .='<li class="toolbar-menu-icon book-parent-tree-wrapper"><a href="#" class="off-canvas-toolbar-item book-parent-tree" data-dropdown="book-sibling-children-' . $item['mlid'] . '" aria-controls="middle-section-buttons" aria-expanded="false">
          <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
        </a></li>
        <div id="book-sibling-children-' . $item['mlid'] . '" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">' . "\n" .
        $item['tree'] . "\n" .
        '</div>' . "\n";
    }
  ?>
    <div class="book-sibling-nav-item book-sibling-nav-<?php print $item['active'];?>"><?php print $link; ?></div>
<?php
  }
?>
</div>
