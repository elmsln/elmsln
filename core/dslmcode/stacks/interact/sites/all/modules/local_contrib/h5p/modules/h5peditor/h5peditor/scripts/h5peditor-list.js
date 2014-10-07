var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Create a ordered list of fields for the form.
 *
 * @param {mixed} parent
 * @param {Object} field
 * @param {mixed} params
 * @param {function} setValue
 * @returns {ns.List}
 */
ns.List = function (parent, field, params, setValue) {
  var that = this;

  if (field.entity === undefined) {
    field.entity = 'item';
  }

  if (params === undefined) {
    this.params = [];
    setValue(field, this.params);
  } else {
    this.params = params;
  }

  if (field.defaultNum === undefined && field.min !== undefined) {
    // Use min as defaultNum if defaultNum isn't set.
    field.defaultNum = field.min;
  }

  this.field = field;
  this.parent = parent;
  this.$items = [];
  this.children = [];
  this.library = parent.library + '/' + field.name;

  this.passReadies = true;
  parent.ready(function () {
    that.passReadies = false;
  });
};

/**
 * Append list to wrapper.
 *
 * @param {jQuery} $wrapper
 * @returns {undefined}
 */
ns.List.prototype.appendTo = function ($wrapper) {
  var that = this;

  var label = '';
  if (this.field.label !== 0) {
    label = '<label class="h5peditor-label">' + (this.field.label === undefined ? this.field.name : this.field.label) + '</label>';
  }

  var html = ns.createItem(this.field.type, label + '<ul class="h5p-ul"></ul><input type="button" value="' + ns.t('core', 'addEntity', {':entity': this.field.entity}) + '"/>', this.field.description);

  this.$list = ns.$(html).appendTo($wrapper).children('ul');
  this.$add = this.$list.next().click(function () {
    if (that.field.max !== undefined && that.params.length >= that.field.max) {
      return;
    }
    var item = that.addItem();
    if (item instanceof ns.Group) {
      item.expand();
    }
  });

  if (this.params.length) {
    for (var i = 0; i < this.params.length; i++) {
      this.addItem(i);
    }
  }
  else {
    // Add default number of fields.
    for (var i = 0; i < this.field.defaultNum; i++) {
      that.$add.click();
    }
  }
};

/**
 * Move the item around.
 *
 * @param {jQuery} $item
 * @param {jQuery} $placeholder
 * @param {Integer} x
 * @param {Integer} y
 * @returns {unresolved}
 */
ns.List.prototype.move = function ($item, $placeholder, x, y) {
  var oldIndex, newIndex;

  // Adjust so the mouse is placed on top of the icon.
  x = x - this.adjustX;
  y = y - this.adjustY;
  $item.css({top: y - this.marginTop - this.formOffset.top, left: x - this.formOffset.left});

  // Try to move up.
  var $prev = $item.prev().prev();
  if ($prev.length && y < $prev.offset().top + ($prev.height() / 2)) {
    $prev.insertAfter($item);

    oldIndex = this.getIndex($item);
    newIndex = oldIndex - 1;
    this.swap(this.$items, oldIndex, newIndex);
    this.swap(this.params, oldIndex, newIndex);
    this.swap(this.children, oldIndex, newIndex);

    return;
  }

  // Try to move down.
  var $next = $item.next();
  if ($next.length && y + $item.height() > $next.offset().top + ($next.height() / 2)) {
    $next.insertBefore($placeholder);

    oldIndex = this.getIndex($item);
    newIndex = oldIndex + 1;
    this.swap(this.$items, oldIndex, newIndex);
    this.swap(this.params, oldIndex, newIndex);
    this.swap(this.children, oldIndex, newIndex);
  }
};

ns.List.prototype.swap = function (list, oldIndex, newIndex) {
  var oldItem = list[oldIndex];
  list[oldIndex] = list[newIndex];
  list[newIndex] = oldItem;
};

/**
 * Add an item to the list.
 *
 * @param {integer} i
 * @returns {unresolved}
 */
ns.List.prototype.addItem = function (i) {
  var that = this;
  var $item, $placeholder;

  if (i === undefined) {
    i = this.$items.length;
  }

  var move = function (event) {
    that.move($item, $placeholder, event.pageX, event.pageY);
  };
  var up = function () {
    // Stop tracking mouse
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

  $item = ns.$('<li class="h5p-li"><a href="#" class="order"></a><a href="#" class="remove"></a><div class="content"></div></li>')
    .appendTo(this.$list)
    .children('.order')
      .mousedown(function (event) {
        if (event.which !== 1) {
          return; // Only allow left mouse button
        }
        
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
        that.adjustX = event.pageX - offset.left;
        that.adjustY = event.pageY - offset.top;
        that.marginTop = parseInt($item.css('marginTop'));
        that.formOffset = that.$list.offsetParent().offset();

        var width = $item.width();
        var height = $item.height();

        $item.addClass('moving').css({width: width, height: height});
        $placeholder = ns.$('<li class="placeholder h5p-li" style="width:' + width + 'px;height:' + height + 'px"></li>').insertBefore($item);

        move(event);
        return false;
      })
      .click(function () {
        console.log('click');
        return false;
      })
        .next()
        .click(function () {
          that.removeItem(that.getIndex($item));
          return false;
        })
        .end()
      .end();

  if (!this.passReadies) {
    this.readies = [];
  }

  var widget = this.field.field.widget === undefined ? this.field.field.type : this.field.field.widget;
  this.children[i] = new ns.widgets[widget](this, this.field.field, this.params[i], function (field, value) {
    that.params[that.getIndex($item)] = value;
  });
  this.children[i].appendTo($item.children('.content'));
  if (!this.passReadies) {
    for (var j = 0; j < this.readies.length; j++) {
      this.readies[j]();
    }
    delete this.readies;
  }
  this.$items[i] = $item;

  return this.children[i];
};

/**
 * Remove an item from the list.
 *
 * @param {int} i
 * @returns {unresolved}
 */
ns.List.prototype.removeItem = function (i) {
  if (!confirm(ns.t('core', 'confirmRemoval', {':type': this.field.entity}))) {
    return;
  }

  this.children[i].remove();
  this.$items[i].remove();

  this.$items.splice(i, 1);
  this.params.splice(i, 1);
  this.children.splice(i, 1);
};

/**
 * Get the index for the given item.
 *
 * @param {jQuery} $item
 * @returns {Integer}
 */
ns.List.prototype.getIndex = function ($item) {
  for (var i = 0; i < this.$items.length; i++) {
    if (this.$items[i] === $item) {
      break;
    }
  }

  return i;
};

/**
 * Validate all fields in the list.
 */
ns.List.prototype.validate = function () {
  var valid = true;

  for (var i = 0; i < this.children.length; i++) {
    if (this.children[i].validate() === false) {
      valid = false;
    }
  }

  return valid;
};

/**
 * Collect functions to execute once the tree is complete.
 *
 * @param {function} ready
 * @returns {undefined}
 */
ns.List.prototype.ready = function (ready) {
  if (this.passReadies) {
    this.parent.ready(ready);
  }
  else {
    this.readies.push(ready);
  }
};

/**
 * Remove this item.
 */
ns.List.prototype.remove = function () {
  ns.removeChildren(this.children);
  this.$list.parent().remove();
};

// Tell the editor what widget we are.
ns.widgets.list = ns.List;
// TODO: Type should be list, widget should be orderedList or unorderedList.
