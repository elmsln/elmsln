/**
 * @file
 * same wrapper as submission_overview by for this page.
 */
(function ($) {
  Drupal.behaviors.cleTileWrapper = {
    attach: function(context, settings) {
      $('.cle-tile-wrapper', context).hover(function(){
      // on hovering a tile
      $(this).addClass('cle-visible-tile');
      $(this).find('.views-field-title, .views-field-comment-count, .views-field-value').slideDown(200, 'linear');
    }, function(){
      // off a tile
      $(this).removeClass('cle-visible-tile');
      $(this).find('.views-field-title, .views-field-comment-count, .views-field-value').delay(800).slideUp(400, 'linear');
    });
    }
  };
})(jQuery);