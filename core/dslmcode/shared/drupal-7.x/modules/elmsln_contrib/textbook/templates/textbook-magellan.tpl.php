<?php
  /**
   * Textbook Magellan template
   * This controls the output of a block that's useful for magellan
   * sub-navigation.
   *
   * Provides the variable $items which should be of the form
   * $items = array(
   *   array(
   *     'title' => 'stuff',
   *     'anchor' => 'things',
   *   ),
   * )
   */
?>
<div class="magellan-wrap" data-magellan-expedition="fixed">
  <dl class="sub-nav">
  <?php foreach ($items as $item) { ?>
    <dd data-magellan-arrival="<?php print $item['anchor']; ?>">
      <a href="#<?php print $item['anchor']; ?>"><?php print $item['title']; ?></a>
    </dd>
  <?php } ?>
  </dl>
</div>