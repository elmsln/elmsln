var H5P = H5P || {};

/**
 * A class that easily helps your create awesome drag and drop.
 *
 * @param {jQuery} $container
 * @param {type} showCoordinates
 * @returns {undefined}
 */
H5P.DragNDrop = function ($container, showCoordinates) {
  this.moveThreshold = 4;
  this.$container = $container;
  this.scrollLeft = 0;
  this.scrollTop = 0;
  this.showCoordinates = showCoordinates === undefined ? false : showCoordinates;
};

/**
 * Start tracking the mouse.
 *
 * @param {jQuery} $element
 * @param {int} x Start X coordinate
 * @param {int} y Start Y coordinate
 * @returns {undefined}
 */
H5P.DragNDrop.prototype.press = function ($element, x, y) {
  var that = this;
  var eventData = {
    instance: this
  };

  H5P.$body
  .bind('mouseup', eventData, H5P.DragNDrop.release)
  .bind('mouseleave', eventData, H5P.DragNDrop.release)
  // With user-select: none uncommented, after moving a drag and drop element, if I hover over something that changes transparancy on hover IE10 on WIN7 crashes
  // TODO: Add user-select and -ms-user-select later if IE10 stops bugging
  .css({'-moz-user-select': 'none', '-webkit-user-select': 'none'/*, 'user-select': 'none', '-ms-user-select': 'none'*/})
  .mousemove(eventData, H5P.DragNDrop.move)
  .attr('unselectable', 'on')[0]
  .onselectstart = function () {
    return false;
  };

  that.containerOffset = $element.offsetParent().offset();

  this.$element = $element;
  this.moving = false;
  this.startX = x;
  this.startY = y;

  this.marginX = parseInt($element.css('marginLeft')) + parseInt($element.css('marginRight'));
  this.marginY = parseInt($element.css('marginTop')) + parseInt($element.css('marginBottom'));

  var offset = $element.offset();
  this.adjust = {
    x: x - offset.left + this.marginX,
    y: y - offset.top - this.marginY
  };

  // Add coordinates picker
  if (this.showCoordinates) {
    if (this.$coordinates !== undefined) {
      this.$coordinates.remove();
      delete this.$coordinates;
    }
    var pos = $element.position();
    var posX = Math.round(pos.left - parseInt(this.$container.css('padding-left')));
    var posY = Math.round(pos.top);
    this.$coordinates = H5P.jQuery('<div class="h5p-coordinates-editor" style="top: ' + (y - this.adjust.y) + 'px; left: ' + (x - this.adjust.x) + 'px;"><input class="h5p-coordinate h5p-x-coordinate" type="text" value="' + posX + '">, <input class="h5p-coordinate h5p-y-coordinate" type="text" value="' + posY + '"></div>');
    this.$xCoordinate = this.$coordinates.children('.h5p-x-coordinate').on('change keydown', function(event) {
      if (event.type === 'change' || event.which === 13) {
        that.moveToCoordinates();
      }
    });
    this.$yCoordinate = this.$coordinates.children('.h5p-y-coordinate').on('change keydown', function(event) {
      if (event.type === 'change' || event.which === 13) {
        that.moveToCoordinates();
      }
    });

    H5P.jQuery('body').append(this.$coordinates);
  }
};

/**
 * Move the draggable element to coordinates typed in by the user
 */
H5P.DragNDrop.prototype.moveToCoordinates = function () {
  var x = parseInt(this.$xCoordinate.val());
  var y = parseInt(this.$yCoordinate.val());
  if (isNaN(x) || isNaN(y)) {
    // Make sure that the NaN doesn't get saved...
    return;
  }
  var event = {
    data: {
      instance: this
    },
    pageX: this.adjust.x + this.containerOffset.left + this.scrollLeft + parseInt(this.$container.css('padding-left')) + x,
    pageY: this.adjust.y + this.containerOffset.top + this.scrollTop + y
  };
  H5P.DragNDrop.move(event);
  H5P.DragNDrop.release(event);
};

/**
 * Handles mouse movements.
 *
 * @param {object} event
 * @returns {undefined}
 */
H5P.DragNDrop.move = function (event) {
  event.stopPropagation();
  var that = event.data.instance;

  if (!that.moving) {
    if (event.pageX > that.startX + that.moveThreshold || event.pageX < that.startX - that.moveThreshold || event.pageY > that.startY + that.moveThreshold || event.pageY < that.startY - that.moveThreshold) {
      if (that.startMovingCallback !== undefined && !that.startMovingCallback(event)) {
        return;
      }

      // Start moving
      that.moving = true;
      that.$element.addClass('h5p-moving');
    }
    else {
      return;
    }
  }

  var x = event.pageX - that.adjust.x;
  var y = event.pageY - that.adjust.y;
  var posX = x - that.containerOffset.left + that.scrollLeft;
  var posY = y - that.containerOffset.top + that.scrollTop;
  var paddingLeft = parseInt(that.$container.css('padding-left'));
  that.$element.css({left: posX, top: posY});

  if (that.showCoordinates) {
    that.$xCoordinate.val(Math.round(posX - paddingLeft));
    that.$yCoordinate.val(Math.round(posY));
    that.$coordinates.css({left: x, top: y});
  }

  if (that.moveCallback !== undefined) {
    that.moveCallback(x, y);
  }
};

/**
 * Stop tracking the mouse.
 *
 * @param {object} event
 * @returns {undefined}
 */
H5P.DragNDrop.release = function (event) {
  var that = event.data.instance;

  H5P.$body
  .unbind('mousemove', H5P.DragNDrop.move)
  .unbind('mouseup', H5P.DragNDrop.release)
  .unbind('mouseleave', H5P.DragNDrop.release)
  .css({'-moz-user-select': '', '-webkit-user-select': ''/*, 'user-select': '', '-ms-user-select': ''*/})
  .removeAttr('unselectable')[0]
  .onselectstart = null;

  if (that.releaseCallback !== undefined) {
    that.releaseCallback();
  }

  if (that.moving) {
    that.$element.removeClass('h5p-moving');
    if (that.stopMovingCallback !== undefined) {
      var oldPos = that.$element.position();
      that.stopMovingCallback(event);
      if (that.showCoordinates) {
        // If stop moving callback moved the element coordinates must be updated with the change
        var newPos = that.$element.position();
        var coordinatesOldPos = that.$coordinates.position();
        that.$coordinates.css('left', parseInt(coordinatesOldPos.left - oldPos.left + newPos.left));
        that.$coordinates.css('top', parseInt(coordinatesOldPos.top - oldPos.top + newPos.top));
        var oldX = parseInt(that.$xCoordinate.val());
        var oldY = parseInt(that.$yCoordinate.val());
        that.$xCoordinate.val(Math.round(oldX - oldPos.left + newPos.left));
        that.$yCoordinate.val(Math.round(oldY - oldPos.top + newPos.top));
      }
    };
  }
};