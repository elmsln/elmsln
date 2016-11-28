<section id="<?php print $block_html_id ?>-nav-modal" class="elmsln-scroll-bar elmsln-modal modal" aria-label="<?php print $block->subject; ?>" aria-hidden="true" role="dialog" tabindex="-1">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper cis-lmsless-background cis-lmsless-border">
    <h2 class="flow-text valign elmsln-modal-title"><?php print $block->subject; ?></h2>
    <a href="#close-dialog" class="close-reveal-modal" aria-label="<?php print t('Close'); ?>" data-voicecommand="close" data-jwerty-key="Esc">&#215;</a>
  </div>
  <div class="elmsln-modal-content">
    <div id="spritz" class="spritz">
      <div id="spritz_word" class="spritz-word"></div>
    </div>
    <div class="words">
      <div id="spritz_progress" class="progress-bar cis-lmsless-color"></div>
    </div>
    <div class="controls settings-controls">
      <span class="speed">
        <a id="spritz_slower" href="#spritz-slower" title="<?php print t('Slow Down');?>" data-jwerty-key="ctrl+s" data-voicecommand="speed read slower">
        <i class="material-icons cis-lmsless-text">fast_rewind</i>
        <span class="element-invisible"><?php print t('Read slower'); ?></span></a>
        <a id="spritz_pause" href="#spritz-play" title="<?php print t('Pause/Play');?>" class="pause entypo-pause cis-lmsless-text" data-jwerty-key="ctrl+d" data-voicecommand="speed read (play)(pause)"><span class="element-invisible"><?php print t('Play / pause'); ?></span></a>
        <a id="spritz_faster" href="#spritz-faster" title="<?php print t('Speed Up');?>" data-jwerty-key="ctrl+f" data-voicecommand="speed read faster">
          <i class="material-icons cis-lmsless-text">fast_forward</i>
          <span class="element-invisible"><?php print t('Read faster'); ?></span>
        </a>
      </span>
    </div>
    <input id="spritz_wpm" type="hidden" value="250" class="wpm"/>
  </div>
</section>