var H5P = H5P || {};

/**
 * Constructor. Initializes the drag and drop menu bar.
 *
 * @param {Array} buttons
 * @param {jQuery} $container
 * @returns {undefined}
 */
H5P.DragNBar = function (buttons, $container) {
  var that = this;

  this.overflowThreshold = 11; // How many buttons to display before we add the more button.

  this.buttons = buttons;
  this.$container = $container;
  this.dnd = new H5P.DragNDrop($container, true);
  this.newElement = false;

  this.dnd.startMovingCallback = function (event) {
    if (that.newElement) {
      that.dnd.adjust.x = 10;
      that.dnd.adjust.y = 10;
    }

    return true;
  };

  this.dnd.stopMovingCallback = function (event) {
    that.stopMoving(event);
    that.newElement = false;
  };
};

/**
 * Attaches the menu bar to the given wrapper.
 *
 * @param {jQuery} $wrapper
 * @returns {undefined}
 */
H5P.DragNBar.prototype.attach = function ($wrapper) {
  $wrapper.html('');

  var $list = H5P.jQuery('<ul class="h5p-dragnbar-ul"></ul>').appendTo($wrapper);

  for (var i = 0; i < this.buttons.length; i++) {
    var button = this.buttons[i];

    if (i === this.overflowThreshold) {
      var $list = H5P.jQuery('<li class="h5p-dragnbar-li"><a href="#" title="' + 'More elements' + '" class="h5p-dragnbar-a h5p-dragnbar-more-button"></a><ul class="h5p-dragnbar-li-ul"></ul></li>').appendTo($list).children(':first').click(function () {
        $list.slideToggle(200);
        return false;
      }).next();
    }

    this.addButton(button, $list);
  }
};

/**
 * Add button.
 *
 * @param {type} button
 * @param {type} $list
 * @returns {undefined}
 */
H5P.DragNBar.prototype.addButton = function (button, $list) {
  var that = this;

  H5P.jQuery('<li class="h5p-dragnbar-li"><a href="#" title="' + button.title + '" class="h5p-dragnbar-a h5p-dragnbar-' + button.id + '-button"></a></li>').appendTo($list).children().click(function () {
    return false;
  }).mousedown(function (event) {
    that.newElement = true;
    that.dnd.press(button.createElement().appendTo(that.$container), event.pageX, event.pageY);
    return false;
  });
};

/**
 * Change container.
 *
 * @param {jQuery} $container
 * @returns {undefined}
 */
H5P.DragNBar.prototype.setContainer = function ($container) {
  this.$container = $container;
  this.dnd.$container = $container;
};

/**
 * Handler for when the dragging stops. Makes sure the element is inside its container.
 *
 * @param {Object} event
 * @returns {undefined}
 */
H5P.DragNBar.prototype.stopMoving = function (event) {
  var x, y, top, left;

  if (this.newElement) {
    x = event.pageX - 10;
    y = event.pageY - 10;
  }
  else {
    x = event.pageX - this.dnd.adjust.x;
    y = event.pageY - this.dnd.adjust.y;
  }

  var offset = this.$container.offset();

  // Check if element is above or below the container.
  var containerHeight = this.$container.height();
  var elementHeight = this.dnd.$element.outerHeight() + 3;
  if (y < offset.top) {
    top = 0;
  }
  else if (y + elementHeight > offset.top + containerHeight) {
    top = containerHeight - elementHeight;
  }
  else {
    top = y - offset.top;
  }

  // Check if element is to the left or to the right of the container.
  var paddingLeft = parseInt(this.$container.css('padding-left'));
  var containerWidth = this.$container.width() + paddingLeft;
  var elementWidth = this.dnd.$element.outerWidth() + 2;

  if (x < offset.left + paddingLeft) {
    left = paddingLeft;
  }
  else if (x + elementWidth > offset.left + containerWidth) {
    left = containerWidth - elementWidth;
  }
  else {
    left = x - offset.left;
  }

  // Calculate percentage
  top = top / (containerHeight / 100);
  left = left / (containerWidth / 100);

  this.dnd.$element.css({top: top + '%', left: left + '%'});

  // Give others the result
  if (this.stopMovingCallback !== undefined) {
    paddingLeft = paddingLeft / (containerWidth / 100);
    this.stopMovingCallback(left - paddingLeft, top);
  }
};