<?php
/**
 * @file
 * HTML Structure for rendering the Voicecommander bottom drawer.
 * This is mostly so you can theme it and the options are injected
 * based on what's available when the command is called upon.
 * @variable
 *   $label - translated label for the drawer
 */
?>
<div id="voicecommander-drawer" class="voicecommander-drawer-wrapper">
  <div class="voicecommander-command-drawer">
    <h2 class="voicecommander-drawer-label"><?php print $label;?></h2>
    <div class="jarvis-conversation"></div>
  </div>
</div>