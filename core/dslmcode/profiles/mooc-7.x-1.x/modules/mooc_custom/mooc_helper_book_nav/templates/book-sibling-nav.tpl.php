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
   */
?>
<div class="content-element-region small-12 medium-12 large-centered large-10 columns book-sibling-nav-container">
  <?php
  foreach ($items as $item) {
    $link = l('<div class="book-menu-item-' . $item['mlid'] . ' icon-' . $item['icon'] . '-black outline-nav-icon"></div>',
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
    print '<div class="book-sibling-nav-item book-sibling-nav-' . $item['active'] . '">' . $link . '</div>';
  }
?>
</div>
