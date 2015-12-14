<?php
 /**
  * Pretty specific to speedreader block since it has a certain structure
  * in order to react correctly to the page's content.
  */
?>
  <h1><?php print $name; ?></h1>
  <hr></hr>
  <div id="spritz" class="spritz">
    <div id="spritz_word" class="spritz-word"></div>
  </div>
  <div class="settings">
    <div class="words">
      <div id="spritz_progress" class="progress-bar"></div>
    </div>
    <div class="controls settings-controls">
      <span class="speed">
        <a id="spritz_slower" href="#" title="<?php print t('Slow Down');?>" class="slower entypo-fast-backward"></a>
        <a id="spritz_pause" href="#" title="<?php print t('Pause/Play');?>" class="pause entypo-pause"></a>
        <a id="spritz_faster" href="#" title="<?php print t('Speed Up');?>" class="faster entypo-fast-forward"></a>
      </span>
    </div>
  </div>
  <input id="spritz_wpm" type="hidden" value="300" step="50" min="50" class="wpm"/>
  <a class="close-reveal-modal" aria-label="<?php print t('Close');?>">&#215;</a>

