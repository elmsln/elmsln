(function($) {
  /**
   * Make the views pager work inside the widget form.
   */
  Drupal.behaviors.entityreferenceViewWidgetPager = {
    attach: function (context, settings) {
      // When a pager link is clicked, store its 'page' value in a hidden
      // form element, and submit the form via ajax to trigger the rebuild.
      $('ul.pager a', context).click(function(event) {
        var match = this.href.match(/page=([0-9]*)/);
        var page = 0;
        if (match) {
          var page = match[1];
        }
        var widget = $(this).closest('.entityreference-view-widget', context);
        $('.entityreference-view-widget-page', widget).val(page);
        $('.pager-submit', widget).trigger('mousedown');

        event.preventDefault();
      });
    }
  };

  /**
   * Custom tableDrag behavior for the widget.
   */
  Drupal.behaviors.entityreferenceViewWidgetDrag = {
    attach: function (context, settings) {
      // If tableDrag is not initialized, abort.
      if (typeof Drupal.tableDrag == 'undefined') {
        return;
      }

      // Hide the "Show row weights" link.
      $('.entityreference-view-widget .widget-left .tabledrag-toggle-weight').hide();

      // Remove the message that gets added before the table after a row
      // has been dragged. Unfortunatelly, this will remove the message
      // for other tabledrag elements (such as filefield) on the page as well.
      Drupal.theme.tableDragChangedWarning = function () {
        return '';
      };
    }
  };

})(jQuery);
