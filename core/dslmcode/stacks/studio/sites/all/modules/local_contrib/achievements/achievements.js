jQuery(function($) {
    var height = 104, margin = 10, timeout,
      notifications = $('.achievement-notification').dialog({
        dialogClass:    'achievement-notification-dialog',
        autoOpen:       false,
        show:           'fade',
        hide:           'fade',
        closeOnEscape:  false,
        draggable:      false,
        resizable:      false,
        height:         height,
        width:          500,
        position:       ['right', 'bottom'],
        closeText:      '',
        close:          onClose
      });

    function showDialogs() {
      var length = notifications.length;

      notifications.eq(length - 1).bind('dialogopen', function() {
        var i, notification, top;

        for (i = 0; i < length; i += 1) {
          notification = notifications.eq(i).dialog('widget');
          if (i === 0) {
            top = parseFloat(notification.css('top'));
          }
          else {
            top -= height + margin;
            notification.css('top', top + 'px');
          }
        }

        // the longer the list, longer the onscreen time.
        timeout = setTimeout(closeDialog, 5000 + (length * 500));
      });

      notifications.dialog('open').hover(
        function () {
          clearTimeout(timeout);
        },
        function () {
          // the longer the list, longer the onscreen time.
          timeout = setTimeout(closeDialog, 1500 + (notifications.length * 500));
        }
      );
    }

    function onClose() {
      var i, length, properties, widget;
      notifications = notifications.not(notifications[0]);
      length = notifications.length;

      function close() {
         timeout = setTimeout(closeDialog, 1500);
      }

      if (length) {
        properties = {
          top: '+=' + (height + margin)
        };
        for (i = 0; i < length; i += 1) {
          widget = notifications.eq(i).dialog('widget');
          if (i === 0) {
            widget.animate(properties, close);
          }
          else {
            widget.animate(properties)
          }
        }
      }
    }

    function closeDialog() {
      notifications.eq(0).dialog('close');
    }

    setTimeout(showDialogs, 500);
});