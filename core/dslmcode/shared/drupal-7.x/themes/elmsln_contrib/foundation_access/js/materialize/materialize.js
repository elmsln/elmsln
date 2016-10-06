(function($) {
'use strict';
  Drupal.settings.activeSideNav = null;
  // apply all the materialize javascript
  Drupal.behaviors.materializeJS = {
    attach: function(context) {
      // select lists but not the chosen ones
      $('select').not('.chosen').not('.cke_dialog_body select').material_select();
      // enable parallax
      $('.parallax').parallax();
      // normal carousel
      $('.carousel').not('.carousel-slider').carousel();
      // full size slider carousel
      $('.carousel-slider').carousel({full_width: true});
      // collapsible sets
      $('.collapsible').collapsible({
        accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
      });
      // dropdown items
      $('.elmsln-dropdown-button').dropdown({
        inDuration: 150,
        outDuration: 50,
        constrain_width: false,
        hover: false,
        gutter: 0,
        belowOrigin: true,
        alignment: 'left'
      });
      // side triggers
      $('.elmsln-right-side-nav-trigger').bind('click', function() {
          $('#' + $(this).attr('data-activates')).removeClass('elmsln-modal-hidden').focus();
          Drupal.settings.activeSideNav = $(this).attr('data-activates');
        }).sideNav({
        menuWidth: 400, // Default is 240
        edge: 'right', // Choose the horizontal origin
        closeOnClick: false // Closes side-nav on <a> clicks, useful for Angular/Meteor
      });
      $('.elmsln-left-side-nav-trigger').bind('click', function() {
          $('#' + $(this).attr('data-activates')).removeClass('elmsln-modal-hidden').focus();
          Drupal.settings.activeSideNav = $(this).attr('data-activates');
        }).sideNav({
        menuWidth: 280, // Default is 240
        edge: 'left', // Choose the horizontal origin
        closeOnClick: false // Closes side-nav on <a> clicks, useful for Angular/Meteor
      });
      // modal items
      $('.elmsln-modal-trigger').bind('click', function() {
        // hide all currently visible modals
        $('.close-reveal-modal:visible').trigger('click');
      }).leanModal({
        dismissible: true, // Modal can be dismissed by clicking outside of the modal
        opacity: .5, // Opacity of modal background
        in_duration: 150, // Transition in duration
        out_duration: 50, // Transition out duration
        starting_top: '8rem', // Starting top style attribute
        ending_top: '8rem', // Ending top style attribute
        ready: function() { $('.close-reveal-modal:visible').parents().focus(); }, // Callback for Modal open
      });
      // close x's for modals
      $('.close-reveal-modal').click(function(){
        $('#' + $(this).parents().parents().attr('id')).closeModal();
        $('[href=#' + $(this).parents().attr('id') + ']').focus();
      });
      // close x's for the side-nav items
      $('.close-reveal-side-nav').click(function(){
        $('[data-activates=' + Drupal.settings.activeSideNav + ']').focus().sideNav('hide');
        setTimeout(function() {
          $('#' + Drupal.settings.activeSideNav).addClass('elmsln-modal-hidden');
          Drupal.settings.activeSideNav = null;
        }, 150);
      });
    }
  };
  // add support for accessibility of materialized components
  $(document).bind('keydown', function(event) {
    if (event.keyCode == 27) {
      $('.elmsln-dropdown-button.active').dropdown('close');
      // try closing all lightboxes
      var lightboxes = $('.lightbox--is-open .imagelightbox__close').trigger('click');
      if (lightboxes.length == 0) {
        var modals = $('.close-reveal-modal:visible').trigger('click');
        // test that there were modals to close, this allows us to do multiple escapes
        if (modals.length == 0) {
          $('#' + Drupal.settings.activeSideNav + ' .close-reveal-side-nav').trigger('click');
        }
      }
    }
  });
  // events that help with teeing up materialize styles the first run
  $(document).ready(function(){
    // apply color styling for this tool to accent the interface
    $('.cis-lmsless-text, .dropdown-content .nolink').addClass(Drupal.settings.cis_lmsless['text']);
    // color text icons that want it
    $('i.cis-lmsless-text').addClass('text-' + Drupal.settings.cis_lmsless['dark']);
    // apply waves to things that want its color
    $('.cis-lmsless-waves').addClass('waves-' + Drupal.settings.cis_lmsless['color'] + ' waves-light');
    // apply background to things that want our background
    $('.cis-lmsless-background').addClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light']);

    $('.cis-lmsless-color').addClass(Drupal.settings.cis_lmsless['color']);
    // apply border to things that want our background
    $('.cis-lmsless-border, .tabs li.tab a').addClass(Drupal.settings.cis_lmsless['color'] + '-border');
    // color chips
    $('.chip,ul li a.active, .book-menu-item-active-link').not('.book-parent-tree').addClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light']);
    // color back to top item
    $('#backtotop').addClass('circle').addClass('waves-' + Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['dark']);

    // hover state for tables to match styling
    $('tr.even, tr.odd, ul.menu li a').not('.active,.elmsln-fixed-action-btn a').hover(
      function() {
        $(this).addClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light']);
      }, function() {
        $(this).removeClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light']);
      }
    );
    // tab slide effect
    $('.tabs li.tab a').hover(
      function() {
        $(this).addClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light']);
      }, function() {
        $(this).removeClass(Drupal.settings.cis_lmsless['color'] + ' ' + Drupal.settings.cis_lmsless['light']);
      }
    );
    // focus event
    $('a,i,button,li').not('li.expanded, .scrollspy-toc li').on('focusin', function() {
      $(this).addClass(Drupal.settings.cis_lmsless['outline']);
    }).on('focusout', function() {
      $(this).removeClass(Drupal.settings.cis_lmsless['outline']);
    });
    // remove tab index from lightbox link
    $('[href="javascript:;"]').attr('tabindex','-1');
  });
})(jQuery);
