/**
 * @file
 * JavaScript for the show replies links on full post entities.
 */

(function($) {
  function harmony_post_toggle_replies() {
    var post_id = $(this).attr('data-post-id');
    $(this).toggleClass('show-replies-active');
    $('#post-' + post_id + '-replies').slideToggle('fast');
    return false;
  }

  Drupal.ajax.prototype.commands.harmony_post_show_replies = function(ajax, response, status) {
    // Run insert.
    response.method = 'html';
    Drupal.ajax.prototype.commands.insert(ajax, response, status);
    // Detach all commands, and attach new ones.
    $(ajax.element).unbind('click').unbind('tap').bind('click', harmony_post_toggle_replies).bind('tap', harmony_post_toggle_replies).addClass('show-replies-active');
  };

  Drupal.behaviors.harmony_core = {
    attach: function(context, settings) {
      $('a.post-show-replies:not(.ajax-processed)', context).addClass('ajax-processed').each(function (){
        var post_id = $(this).attr('data-post-id');
        var base = $(this).attr('id');
        var element_settings = {
          'event': 'click tap',
          'effect': 'slide',
          'speed': 'fast',
          'url': Drupal.settings.basePath + '?q=ajax/harmony/post-replies/' + post_id
        };

        var ajax = new Drupal.ajax(base, this, element_settings);
        Drupal.ajax[base] = ajax;
      });
    }
  };
})(jQuery);
