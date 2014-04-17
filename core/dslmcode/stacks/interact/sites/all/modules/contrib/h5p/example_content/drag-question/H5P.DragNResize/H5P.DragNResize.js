var H5P = H5P || {};

/**
 * Drag'N Resize module
 *
 * @param {jQuery} $
 */
H5P.DragNResize = (function ($) {

  /**
   *
   * @param {type} $container
   * @returns {undefined}
   */
  function C($container) {
    this.$container = $container;
  };

  /**
   * Gives the given element a resize handle.
   *
   * @param {jQuery} $element
   * @returns {undefined}
   */
  C.prototype.add = function ($element) {
    var that = this;

    $('<div class="h5p-dragnresize-handle"></div>').appendTo($element).mousedown(function (event) {
      that.$element = $element;
      that.press(event.clientX, event.clientY);

      return false;
    });
  };

  C.prototype.press = function (x, y) {
    var eventData = {
      instance: this
    };

    H5P.$body.bind('mouseup', eventData, C.release)
    .bind('mouseleave', eventData, C.release)
    .css({
      '-moz-user-select': 'none',
      '-webkit-user-select': 'none',
      'user-select': 'none',
      '-ms-user-select': 'none'
    })
    .mousemove(eventData, C.move)
    .attr('unselectable', 'on')[0]
    .onselectstart = function () {
      return false;
    };

    this.startX = x;
    this.startY = y;
    this.startWidth = this.$element.width();
    this.startHeight = this.$element.height();
    this.left = parseInt(this.$element.css('left'));
    this.top = parseInt(this.$element.css('top'));

    this.containerEm = parseInt(this.$container.css('fontSize'));
    this.containerWidth = this.$container.width();
    this.containerHeight = this.$container.height();
  };

  C.move = function (event) {
    var that = event.data.instance;

    that.newWidth = that.startWidth + event.clientX - that.startX;
    that.newHeight = that.startHeight + event.clientY - that.startY;

    if (that.newWidth < that.containerEm) {
      // Make sure our width is not to small.
      that.newWidth = that.containerEm;
    }
    else if (that.newWidth + that.left > that.containerWidth) {
      // Make sure we're not outside the container.
      that.newWidth = that.containerWidth - that.left;
    }

    if (that.newHeight < that.containerEm) {
      // Make sure height is not to small.
      that.newHeight = that.containerEm;
    }
    else if (that.newHeight + that.top > that.containerHeight) {
      // Make sure we're not outside the container.
      that.newHeight = that.containerHeight - that.top;
    }

    // Calculate percentage
    that.newWidth = that.newWidth / that.containerEm;
    that.newHeight = that.newHeight / that.containerEm;

    if (that.newWidth > 100) {
      that.newWidth = 100;
    }
    if (that.newHeight > 100) {
      that.newHeight = 100;
    }

    that.$element.css({
      width: that.newWidth + 'em',
      height: that.newHeight + 'em'
    });
  };

  C.release = function (event) {
    var that = event.data.instance;

    H5P.$body.unbind('mousemove', C.move)
    .unbind('mouseup', C.release)
    .unbind('mouseleave', C.release)
    .css({
      '-moz-user-select': '',
      '-webkit-user-select': '',
      'user-select': '',
      '-ms-user-select': ''
    })
    .removeAttr('unselectable')[0]
    .onselectstart = null;

    if (that.resizeCallback !== undefined) {
      that.resizeCallback(that.newWidth, that.newHeight);
    }
  };

  return C;
})(H5P.jQuery);