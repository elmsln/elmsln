<div>
<div id="spritz" class="spritz">
  <div id="spritz_word" class="spritz-word"></div>
</div>
<div class="words">
  <div id="spritz_progress" class="progress-bar cis-lmsless-color"></div>
</div>
<div class="controls settings-controls">
  <span class="speed">
    <a id="spritz_slower" href="#spritz-slower" title="<?php print t('Slow Down');?>" data-jwerty-key="ctrl+s" data-voicecommand="speed reader slow down">
    <paper-icon-button icon="av:fast-rewind" alt="<?php print t('Read slower'); ?>"></paper-icon-button>
    </a>
    <a tabindex="-1" id="spritz_pause" href="#spritz-play" title="<?php print t('Pause or Play');?>" data-jwerty-key="ctrl+d" data-voicecommand="speed reader play"><paper-icon-button icon="av:play-arrow" alt="<?php print t('Pause or Play'); ?>">
    </paper-icon-button></a>
    <a id="spritz_faster" href="#spritz-faster" title="<?php print t('Speed Up');?>" data-jwerty-key="ctrl+f" data-voicecommand="speed reader speed up">
      <paper-icon-button icon="av:fast-forward" alt="<?php print t('Read faster'); ?>"></paper-icon-button>
    </a>
    </a>
  </span>
</div>
<input id="spritz_wpm" type="hidden" value="250" class="wpm"/>
</div>