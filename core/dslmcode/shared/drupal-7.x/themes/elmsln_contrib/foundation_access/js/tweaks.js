/**
 * This file should be used instead of foundation_access/js/tweaks.js
 * if you are not using the grunt task runner.
 */

(function ($) {
  Drupal.behaviors.foundationAccessClickField = {
    attach: function(context) {
      $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').focus(function() { $(this).select() });
      $('input#edit-elmsln-share-section,input.cis_shortcodes_embed').mouseup(function(e){
        e.preventDefault();
      });
    }
  };
  Drupal.behaviors.accessibilityCheckHide = {
    attach: function(context, settings) {
      if ($(".cis_accessibility_check a").length == 0) {
        $(".accessibility-content-toggle a").appendTo( ".cis_accessibility_check" );
      }
      $(".accessibility-content-toggle").hide();
    }
  };
  // resize event
  $(document).on('frame-resize', function(){
    Drupal.offcanvasHeight.attach();
  });
  // behavior frame resize
  Drupal.behaviors.frameResize = {
    attach: function(context, settings) {
      Drupal.offcanvasHeight.attach();
    }
  };
  // calculate the color difference between items
  // based on https://www.sitepoint.com/javascript-generate-lighter-darker-color/
  Drupal.ColorLuminance = function(hex, lum) {
    // validate hex string
    hex = String(hex).replace(/[^0-9a-f]/gi, '');
    if (hex.length < 6) {
      hex = hex[0]+hex[0]+hex[1]+hex[1]+hex[2]+hex[2];
    }
    lum = lum || 0;

    // convert to decimal and change luminosity
    var rgb = "#", c, i;
    for (i = 0; i < 3; i++) {
      c = parseInt(hex.substr(i*2,2), 16);
      c = Math.round(Math.min(Math.max(0, c + (c * lum)), 255)).toString(16);
      rgb += ("00"+c).substr(c.length);
    }

    return rgb;
  };
  // loop through each list and then jump from one color through the bottom
  $(document).ready(function(){
    $('.list-colorluminance[data-colorluminance]').each(function(){
      var color=$(this).attr('data-colorluminance');
      var count = $(this).children('li').length;
      $(this).children('li').each(function(index, el) {
        var floor = (index/count);
        if (floor > .7) {
          floor = .7;
        }
        var luminance = Drupal.ColorLuminance(color, floor);
        $("<style type='text/css'> li.luminance-" + luminance.replace('#', '') + ":before { border-color:" + luminance + " !important; background:" + luminance + " !important;}</style>").appendTo("head");
        $(this).addClass('luminance-' + luminance.replace('#', ''));
      });
    });
  });
  // nice UI element to let us select users
  $('#edit-elmsln-view-user').click(function(event) {
    // prevent empty submission though this won't block incorrect submissions which would be page not found
    if ($('#edit-masquerade-user-field').val() != '' && $('#edit-masquerade-user-field').val() != 'Anonymous') {
      // force browser to this location, though we aren't garenteed this is a real place
      // but should be most of the time unless someone mistypes
      window.location = Drupal.settings.basePath + 'users/' + $('#edit-masquerade-user-field').val();
    }
  });
})(jQuery);
