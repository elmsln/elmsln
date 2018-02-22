<section id="<?php print $block_html_id ?>-nav-modal" class="elmsln-scroll-bar elmsln-modal modal" aria-label="<?php print $block->subject; ?>" aria-hidden="true" role="dialog" tabindex="-1">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper black">
    <h2 class="valign elmsln-modal-title white-text"><?php print $block->subject; ?></h2>
    <a tabindex="-1" href="#close-dialog" class="close-reveal-modal" aria-label="<?php print t('Close'); ?>" data-voicecommand="close" data-jwerty-key="Esc"><paper-button>&#215;</paper-button></a>
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
        <a id="spritz_slower" href="#spritz-slower" title="<?php print t('Slow Down');?>" data-jwerty-key="ctrl+s" data-voicecommand="speed reader slow down">
        <i class="material-icons cis-lmsless-text">fast_rewind</i>
        <span class="element-invisible"><?php print t('Read slower'); ?></span></a>
        <a tabindex="-1" id="spritz_pause" href="#spritz-play" title="<?php print t('Pause/Play');?>" data-jwerty-key="ctrl+d" data-voicecommand="speed reader play"><paper-icon-button icon="av:play-arrow" class="blue-text text-darken-4">
        </paper-icon-button></a>
        <a id="spritz_faster" href="#spritz-faster" title="<?php print t('Speed Up');?>" data-jwerty-key="ctrl+f" data-voicecommand="speed reader speed up">
          <i class="material-icons cis-lmsless-text">fast_forward</i>
          <span class="element-invisible"><?php print t('Read faster'); ?></span>
        </a>
      </span>
    </div>
    <input id="spritz_wpm" type="hidden" value="250" class="wpm"/>
  </div>
</section>