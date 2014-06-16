<?php
  $style = '';
  $width = '';
  $height = '';
  $border = '';
  $show_nav = FALSE;
  $show_toc = FALSE;
  if (isset($node->sco_options['show_toc']) && $node->sco_options['show_toc']) {
    $show_toc = TRUE;
  }
  if (isset($node->sco_options['show_nav']) && $node->sco_options['show_nav']) {
    $show_nav = TRUE;
  }
  if (isset($node->sco_options['width']) && $node->sco_options['width']) {
    $width = ' width: ' . $node->sco_options['width'] . ';';
  }
  if (isset($node->sco_options['height']) && $node->sco_options['height']) {
    $height = ' height: ' . $node->sco_options['height'] . ';';
  }
  if (isset($node->sco_options['show_border']) && $node->sco_options['show_border']) {
  }
  else {
    $border = ' border: none;';
  }
  if ($width != '' || $height != '') {
    $style = ' style="' . $width . $height . '"';
  }
  drupal_add_js(sco_node_nav_info($node), array('type' => 'inline', 'preprocess' => FALSE, 'cache' => FALSE));
?>
<div id="sco-node-wrapper" <?php print $style; ?>>

  <?php if (arg(2) == 'review') { ?>
  <div id="sco-node-review">Review Mode - Not Scored or Recorded</div>
  <?php } ?>

  <noscript>
    <div class="sco-node-noscript">
      Javascript is not enabled on this browser or device.
      Please enable Javascript under Settings or Internet Options and refresh this page to continue.
    </div>
  </noscript>
  
  <?php if ($show_toc) { ?>

  <?php $style = ''; if ($border != '') $style = ' style="' . $border . '"'; ?>
  <div id="sco-node-toc-wrapper" <?php print $style; ?>>
    <?php print sco_node_toc_tree($node); ?>
  </div>

  <div id="sco-node-content-wrapper">

  <?php } ?>

    <?php $style = ''; if ($border != '') { $style = $border; } ?>
    <?php if (!$show_nav) { $style .= ' height: 100%;'; } ?>
    <div id="sco-node-content" <?php if ($style != '') { print ' style="' . $style . '"'; } ?>>
      <?php print sco_node_content_start($node); ?>
    </div>

    <?php if ($show_nav) { ?>
    <?php $style = ''; if ($border != '') $style = ' style="' . $border . '"'; ?>
    <div id="sco-node-nav-wrapper" <?php print $style; ?>>
      <div id="sco-node-nav">
        <input type="button" id="sco-node-nav-first" class="sco-node-nav-button" value="<<">
        <input type="button" id="sco-node-nav-prev" class="sco-node-nav-button" value="<">
        <input type="button" id="sco-node-nav-next" class="sco-node-nav-button" value=">">
        <input type="button" id="sco-node-nav-last" class="sco-node-nav-button" value=">>">
      </div>
    </div>
    <?php } ?>

  <?php if ($show_toc) { ?>
  </div>
  <?php } ?>

</div>

<?php if (isset($node->sco_options['show_exit_link']) && $node->sco_options['show_exit_link']) { ?>
<div id="sco-node-exit"><?php echo l('Exit Presentation', 'node/' . $node->nid); ?></div>
<?php } ?>

<?php if (isset($node->sco_options['debug']) && $node->sco_options['debug']) { ?>
<div id="sco-node-log"></div>
<?php } ?>


