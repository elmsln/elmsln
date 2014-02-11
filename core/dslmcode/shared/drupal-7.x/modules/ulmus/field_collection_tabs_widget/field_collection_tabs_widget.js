/**
 * @file
 * Provides js for tabs
 */

(function ($) {
/**
 * JS related to the tabs.
 */
Drupal.behaviors.fieldCollectionTabsWidget = {
  attach: function (context, settings) {
    for (idkey in settings.fieldCollectionTabsWidgetIds) {
      var idvalue = settings.fieldCollectionTabsWidgetIds[idkey];
      // The ERTA magic happens here.
      $('#' + idvalue).once().easyResponsiveTabs();
      $('#' + idvalue + ' ul.resp-tabs-list').sortable({
        // The 'Add a new tab' tab is not sortable
        items: '>li:not(.last)',
        // Update the fields' weight on sorting.
        update: function(event, ui) {
          var counter = 0;
          $(ui.item[0]).closest('.resp-tabs-list').find('li:not(.last)').each(function() {
            var aria_controls = $(this).attr('aria-controls');
            $(this).closest('ul').next('.resp-tabs-container').find('div[aria-labelledby="' + aria_controls + '"] select.fctw-weight').val(counter++);
          });
        }
      });

      // Clicking on the 'Add a new tab' tab a mousedown event on the
      // field collection's 'Add a new item' button is triggered.
      $('#' + idvalue + ' li.last').click(function(event) {
        // Add a throbber
        if ($(this).find('div .ajax-progress').length === 0) {
          $(this).find('div').append('<div class="ajax-progress"><div class="throbber">&nbsp;</div></div>');
        }
        // Trigger a click on the Add new item button. For some reason click() does not work here.
        $(this).closest('ul.resp-tabs-list').siblings('div.resp-tabs-container').find('input.field-add-more-submit').mousedown();
      });

      // Clicking on the 'Add a new tab' accordion a mousedown event on the
      // field collection's 'Add a new item' button is triggered.
      $('#' + idvalue + ' .resp-tabs-container > h2:nth-last-of-type(1)').click(function(event) {
        // Add a throbber
        if ($(this).find('div .ajax-progress').length === 0) {
          $(this).find('div').append('<div class="ajax-progress"><div class="throbber">&nbsp;</div></div>');
        }
        // Trigger a click on the Add new item button. For some reason click() does not work here.
        $(this).next('div').find('input.field-add-more-submit').mousedown();
      });

      // After clicking on the 'Add a new tab' the newly created tab
      // is made active.
      $(document).ajaxComplete(function(event, xhr, ajaxsettings) {
        if (typeof ajaxsettings.extraData !== 'undefined') {
          if (typeof ajaxsettings.extraData._triggering_element_name !== 'undefined') {
            if ($('input[name="' + ajaxsettings.extraData._triggering_element_name + '"]').hasClass('field-add-more-submit')) {
              $('input[name="' + ajaxsettings.extraData._triggering_element_name + '"]').closest('.resp-tabs-container').prev('ul').find('li.last').prev().click();
            }
          }
        }
      });

    }
  }
};

})(jQuery);
