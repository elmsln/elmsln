<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>">

  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>

  <?php if ($display_submitted): ?><span class="submitted">On <?php print $date; ?></span><?php endif; ?>

  <?php 
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    print render($content);
  ?>

  <?php if (!empty($content['links']['terms'])): ?>
    <?php print render($content['links']['terms']); ?>
  <?php endif;?>

  <?php if (!empty($content['links'])): ?>
    <?php print render($content['links']); ?>
  <?php endif; ?>

</div> <!-- /node-->

<?php print render($content['comments']); ?>
