/** @namespace H5PEditor */
var H5PEditor = H5PEditor || {};

H5PEditor.ListEditor = (function ($) {

  /**
   * Draws the list.
   *
   * @class
   * @param {List} list
   */
  function ListEditor(list) {
    var self = this;

    var entity = list.getEntity();

    // Create list html
    var $list = $('<ul/>', {
      'class': 'h5p-ul'
    });

    // Create add button
    var $button = $('<button/>', {
      text: H5PEditor.t('core', 'addEntity', {':entity': entity})
    }).click(function () {
      list.addItem();
    });

    // Used when dragging items around
    var adjustX, adjustY, marginTop, formOffset;

    /**
     * @private
     * @param {jQuery} $item
     * @param {jQuery} $placeholder
     * @param {Number} x
     * @param {Number} y
     */
    var moveItem = function ($item, $placeholder, x, y) {
      var currentIndex;

      // Adjust so the mouse is placed on top of the icon.
      x = x - adjustX;
      y = y - adjustY;
      $item.css({
        top: y - marginTop - formOffset.top,
        left: x - formOffset.left
      });

      // Try to move up.
      var $prev = $item.prev().prev();
      if ($prev.length && y < $prev.offset().top + ($prev.height() / 2)) {
        $prev.insertAfter($item);

        currentIndex = $item.index();
        list.moveItem(currentIndex, currentIndex - 1);

        return;
      }

      // Try to move down.
      var $next = $item.next();
      if ($next.length && y + $item.height() > $next.offset().top + ($next.height() / 2)) {
        $next.insertBefore($placeholder);

        currentIndex = $item.index() - 2;
        list.moveItem(currentIndex, currentIndex + 1);
      }
    };

    /**
     * Adds UI items to the widget.
     *
     * @public
     * @param {Object} item
     */
    self.addItem = function (item) {
      var $placeholder;
      var $item = $('<li/>', {
        'class' : 'h5p-li',
      });

      // Create confirmation dialog for removing list item
      var confirmRemovalDialog = new H5P.ConfirmationDialog({
        dialogText: H5PEditor.t('core', 'confirmRemoval', {':type': entity})
      }).appendTo(document.body);

      // Remove list item on confirmation
      confirmRemovalDialog.on('confirmed', function () {
        list.removeItem($item.index());
        $item.remove();
      });

      /**
       * Mouse move callback
       *
       * @private
       * @param {Object} event
       */
      var move = function (event) {
        moveItem($item, $placeholder, event.pageX, event.pageY);
      };

      /**
       * Mouse button release callback
       *
       * @private
       */
      var up = function () {
        H5P.$body
          .unbind('mousemove', move)
          .unbind('mouseup', up)
          .unbind('mouseleave', up)
          .attr('unselectable', 'off')
          .css({
            '-moz-user-select': '',
            '-webkit-user-select': '',
            'user-select': '',
            '-ms-user-select': ''
          })
          [0].onselectstart = H5P.$body[0].ondragstart = null;

        $item.removeClass('moving').css({
          width: 'auto',
          height: 'auto'
        });
        $placeholder.remove();
      };

      /**
       * Mouse button down callback
       *
       * @private
       */
      var down = function (event) {
        if (event.which !== 1) {
          return; // Only allow left mouse button
        }

        // Prevent wysiwyg becoming unresponsive
        H5PEditor.Html.removeWysiwyg();

        // Start tracking mouse
        H5P.$body
          .attr('unselectable', 'on')
          .mouseup(up)
          .bind('mouseleave', up)
          .css({
            '-moz-user-select': 'none',
            '-webkit-user-select': 'none',
            'user-select': 'none',
            '-ms-user-select': 'none'
          })
          .mousemove(move)
          [0].onselectstart = H5P.$body[0].ondragstart = function () {
            return false;
          };

        var offset = $item.offset();
        adjustX = event.pageX - offset.left;
        adjustY = event.pageY - offset.top;
        marginTop = parseInt($item.css('marginTop'));
        formOffset = $list.offsetParent().offset();
        // TODO: Couldn't formOffset and margin be added?

        var width = $item.width();
        var height = $item.height();

        $item.addClass('moving').css({
          width: width,
          height: height
        });
        $placeholder = $('<li/>', {
          'class': 'placeholder h5p-li',
          css: {
            width: width,
            height: height
          }
        }).insertBefore($item);

        move(event);
        return false;
      };

      // List item title bar
      var $titleBar = $('<div/>', {
        'class': 'list-item-title-bar',
        appendTo: $item
      });

      // Append order button
      $('<div/>', {
        'class' : 'order',
        role: 'button',
        tabIndex: 1,
        on: {
          mousedown: down
        }
      }).appendTo($titleBar);

      // Append remove button
      $('<div/>', {
        'class' : 'remove',
        role: 'button',
        tabIndex: 1,
        on: {
          click: function () {
            confirmRemovalDialog.show($(this).offset().top);
          }
        }
      }).appendTo($titleBar);

      // Append new field item to content wrapper
      if (item instanceof H5PEditor.Group) {
        // Append to item
        item.appendTo($item);
        $item.addClass('listgroup');

        // Move label
        $item.children('.field').children('.title').appendTo($titleBar).addClass('h5peditor-label');

        // Handle expand and collapse
        item.on('expanded', function () {
          $item.addClass('expanded').removeClass('collapsed');
        });
        item.on('collapsed', function () {
          $item.removeClass('expanded').addClass('collapsed');
        });
      }
      else {
        // Append content wrapper
        var $content = $('<div/>', {
          'class' : 'content'
        }).appendTo($item);

        // Append field
        item.appendTo($content);

        if (item.field.label !== 0) {
          // Try to find and move the label to the title bar
          $content.children('.field').find('.h5peditor-label:first').appendTo($titleBar);
        }
      }

      // Append item to list
      $item.appendTo($list);

      // Good UX: automatically expand groups if not explicitly disabled by semantics
      if (item instanceof H5PEditor.Group) {
        item.expand();
      }
    };

    /**
     * Puts this widget at the end of the given container.
     *
     * @public
     * @param {jQuery} $container
     */
    self.appendTo = function ($container) {
      $list.appendTo($container);
      $button.appendTo($container);
    };

    /**
     * Remove this widget from the editor DOM.
     *
     * @public
     */
    self.remove = function () {
      $list.remove();
      $button.remove();
    };
  }

  return ListEditor;
})(H5P.jQuery);
