/**
 * @file
 * CIS tokens helper for mouse-over
 */
(function ($) {
  /**
   * Add hover effect
   */
  Drupal.behaviors.cisTokens = {
    attach: function(context, settings) {
      // On option change, switch location
      $('span.cis_token_dynamic_value').mouseover(function(event) {
        /* Act on the event */
        $(this).html('Token: ' + $(this).attr('data-cis-token') + '&nbsp;&nbsp;&nbsp;Scope: ' + $(this).attr('data-cis-token-scope'));
      });
      $('span.cis_token_dynamic_value').mouseout(function(event) {
        /* Act on the event */
        $(this).html($(this).attr('data-cis-token-value'));
      });
    }
  };

})(jQuery);
