(function (Drupal, $) {
  "use strict";

  Drupal.behaviors.clientStatus = {
    attach: function (context, settings) {
      // Connect checkbox wrapper to table-drag wrapper
      $('.clients-status-wrapper', context).once('clients-status-wrapper', function() {
        var $clients_order_wrapper = $('#' + $(this).attr('id').replace(/-status-wrapper$/, '-order-wrapper'), context);
        var $clients_status_warning = $(this).find('.authcache-p13n-clients-warning');

        $(this).bind('click.clientUpdate', function() {
          var $checked = $(this).find('input.form-checkbox:checked');
          if ($checked.length > 1) {
            $clients_order_wrapper.show();
          }
          else {
            $clients_order_wrapper.hide();
          }

          if ($checked.length === 0) {
            $clients_status_warning.show();
          }
          else {
            $clients_status_warning.hide();
          }
        });

        $(this).triggerHandler('click.clientUpdate');
      });

      // Connect checkboxes to rows
      $('.clients-status-wrapper input.form-checkbox', context).once('clients-status-checkbox', function () {
        var $checkbox = $(this);
        // Retrieve the tabledrag row belonging to this client.
        var $row = $('#' + $checkbox.attr('id').replace(/-status$/, '-weight'), context).closest('tr');

        // Bind click handler to this checkbox to conditionally show and hide the
        // client's tableDrag row and vertical tab pane.
        $checkbox.bind('click.clientUpdate', function () {
          if ($checkbox.is(':checked')) {
            $row.show();
          }
          else {
            $row.hide();
          }
          // Restripe table after toggling visibility of table row.
          var $clients_order_table = $row.closest('.clients-order-table');
          Drupal.tableDrag[$clients_order_table.attr('id')].restripeTable();
        });

        // Trigger our bound click handler to update elements to initial state.
        $checkbox.triggerHandler('click.clientUpdate');
      });
    }
  };

}(Drupal, jQuery));
