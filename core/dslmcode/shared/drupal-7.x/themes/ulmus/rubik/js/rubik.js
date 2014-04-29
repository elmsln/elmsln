/**
 * Implementation of Drupal behavior.
 */
(function($) {
Drupal.behaviors.rubik = {};
Drupal.behaviors.rubik.attach = function(context) {
  // If there are both main column and side column buttons, only show the main
  // column buttons if the user scrolls past the ones to the side.
  $('div.form:has(div.column-main div.form-actions):not(.rubik-processed)').each(function() {
    var form = $(this);
    var offset = $('div.column-side div.form-actions', form).height() + $('div.column-side div.form-actions', form).offset().top;
    $(window).scroll(function () {
      if ($(this).scrollTop() > offset) {
        $('div.column-main div.form-actions', form).show();
      }
      else {
        $('div.column-main div.form-actions', form).hide();
      }
    });
    form.addClass('rubik-processed');
  });

  $('a.toggler:not(.rubik-processed)', context).each(function() {
    var id = $(this).attr('href').split('#')[1];
    // Target exists, add click handler.
    if ($('#' + id).size() > 0) {
      $(this).click(function() {
        var toggleable = $('#' + id);
        toggleable.toggle();
        $(this).toggleClass('toggler-active');
        return false;
      });
    }
    // Target does not exist, remove click handler.
    else {
      $(this).addClass('toggler-disabled');
      $(this).click(function() { return false; });
    }
    // Mark as processed.
    $(this).addClass('rubik-processed');
  });

    // If there's no active secondary tab, make the first one show.
  var activeli = $('.primary-tabs li.active .secondary-tabs li.active');
  if (activeli.length === 0) {
    $('.primary-tabs li.active .secondary-tabs li:first-child a').css('display', 'block');
  }
  
  $('.secondary-tabs li a, .secondary-tabs', context).bind('focus blur', function(){
    $(this).parents('.secondary-tabs').toggleClass('focused');
  });

  // Sticky sidebar
  if ($('#content .column-side .column-wrapper').length !== 0) {
    var rubikColumn = $('#content .column-side .column-wrapper', context);
    var rubikStickySidebar = rubikColumn.offset().top;
    $(window).scroll(function(){
      if( $(window).scrollTop() > rubikStickySidebar ) {
        rubikColumn.each(function() {
          $(this).addClass("fixed");
          $(this).width($(this).parent().width());
        });
      } else {
        rubikColumn.each(function() {
          $(this).removeClass("fixed");
          $(this).width($(this).parent().width());
        });
      }
    });

    // Move fields to sidebar.
    $(".rubik_sidebar_field").each(function() {
      $('.column-side .column-wrapper').append($(this));
    });
  }
  
};
})(jQuery);
