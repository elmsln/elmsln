(function ($) {
  Drupal.behaviors.joyrideManualTrigger = {
    attach:function (context, settings) {
      $('a.joyride-start-link').live('click', function(event) {
        event.preventDefault();

        var tips_content = Drupal.settings.joyrideContext.tips_content || 'undefined';
        if (tips_content == 'undefined') return false;

        if($('ol#joyride-tips-content').length > 0) $('ol#joyride-tips-content').remove();

        $('body', context).append(tips_content);

        $('ol#joyride-tips-content').joyride();

        return false;
      });
    }
  };
}(jQuery));