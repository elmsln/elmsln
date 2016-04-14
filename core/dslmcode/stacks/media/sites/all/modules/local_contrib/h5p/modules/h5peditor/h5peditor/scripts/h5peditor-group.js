var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Create a group of fields.
 *
 * @param {mixed} parent
 * @param {object} field
 * @param {mixed} params
 * @param {function} setValue
 * @returns {ns.Group}
 */
ns.Group = function (parent, field, params, setValue) {
  // Support for events
  H5P.EventDispatcher.call(this);

  if (field.label === undefined) {
    field.label = field.name;
  }
  else if (field.label === 0) {
    field.label = '';
  }

  this.parent = parent;
  this.passReadies = true;
  this.params = params;
  this.setValue = setValue;
  this.library = parent.library + '/' + field.name;

  if (field.deprecated !== undefined && field.deprecated) {
    this.field = H5P.cloneObject(field, true);
    var empties = 0;
    for (var i = 0; i < this.field.fields.length; i++) {
      var f = this.field.fields[i];
      if (params !== undefined && params[f.name] === '') {
        delete params[f.name];
      }
      if (params === undefined || params[f.name] === undefined) {
        f.widget = 'none';
        empties++;
      }
    }
    if (i === empties) {
      this.field.fields = [];
    }
  }
  else {
    this.field = field;
  }

  if (this.field.optional === true) {
    // If this field is optional, make sure child fields are aswell
    for (var j = 0; j < this.field.fields.length; j++) {
      this.field.fields[j].optional = true;
    }
  }
};

// Extends the event dispatcher
ns.Group.prototype = Object.create(H5P.EventDispatcher.prototype);
ns.Group.prototype.constructor = ns.Group;

/**
 * Append group to its wrapper.
 *
 * @param {jQuery} $wrapper
 * @returns {undefined}
 */
ns.Group.prototype.appendTo = function ($wrapper) {
  var that = this;

  if (this.field.fields.length === 0) {
    // No fields or all are deprecated
    this.setValue(this.field);
    return;
  }

  // Add fieldset wrapper for group
  this.$group = ns.$('<fieldset/>', {
    'class': 'field group',
    appendTo: $wrapper
  });

  // Add title expand/collapse button
  ns.$('<div/>', {
    'class': 'title',
    title: ns.t('core', 'expandCollapse'),
    role: 'button',
    tabIndex: 0,
    on: {
      click: function () {
        that.toggle();
      },
      keypress: function (event) {
        if ((event.charCode || event.keyCode) === 32) {
          that.toggle();
        }
      }
    },
    appendTo: this.$group
  });

  // Add content container
  var $content = ns.$('<div/>', {
    'class': 'content',
    appendTo: this.$group
  });

  if (this.field.fields.length === 1) {
    $content.addClass('h5peditor-single');
    this.children = [];
    var field = this.field.fields[0];
    var widget = field.widget === undefined ? field.type : field.widget;
    this.children[0] = new ns.widgets[widget](this, field, this.params, function (field, value) {
      that.setValue(that.field, value);
    });
    this.children[0].appendTo($content);
  }
  else {
    if (this.params === undefined) {
      this.params = {};
      this.setValue(this.field, this.params);
    }
    ns.processSemanticsChunk(this.field.fields, this.params, $content, this);
  }

  // Set summary
  this.findSummary();

  // Check if group should be expanded.
  // Default is to be collapsed unless explicity defined in semantics by optional attribute expanded
  if (this.field.expanded === true) {
    this.expand();
  }
};

/**
 * Toggle expand/collapse for the given group.
 */
ns.Group.prototype.toggle = function () {
  if (this.$group.hasClass('expanded')) {
    this.collapse();
  }
  else {
    this.expand();
  }
};

/**
 * Expand the given group.
 */
ns.Group.prototype.expand = function () {
  this.$group.addClass('expanded');
  this.trigger('expanded');
};

/**
 * Collapse the given group (if valid)
 */
ns.Group.prototype.collapse = function () {
  // Do not collapse before valid!
  var valid = true;
  for (var i = 0; i < this.children.length; i++) {
    if (this.children[i].validate() === false) {
      valid = false;
    }
  }
  if (valid) {
    this.$group.removeClass('expanded');
    this.trigger('collapsed');
  }
};

/**
 * Find summary to display in group header.
 */
ns.Group.prototype.findSummary = function () {
  var that = this;
  var summary;
  for (var j = 0; j < this.children.length; j++) {
    var child = this.children[j];
    if (child.field === undefined) {
      continue;
    }
    var params = this.field.fields.length === 1 ? this.params : this.params[child.field.name];
    var widget = ns.getWidgetName(child.field);

    if (widget === 'text') {
      if (params !== undefined && params !== '') {
        summary = params.replace(/(<([^>]+)>)/ig, "");
      }

      child.$input.change(function () {
        var params = that.field.fields.length === 1 ? that.params : that.params[child.field.name];
        if (params !== undefined && params !== '') {
          that.setSummary(params.replace(/(<([^>]+)>)/ig, ""));
        }
      });
      break;
    }
    else if (widget === 'library') {
      if (params !== undefined) {
        summary = child.$select.children(':selected').text();
      }
      child.change(function (library) {
        that.setSummary(library.title);
      });
      break;
    }
  }
  this.setSummary(summary);
};

/**
 * Set the given group summary.
 *
 * @param {string} summary
 * @returns {undefined}
 */
ns.Group.prototype.setSummary = function (summary) {
  var summaryText;

  // Parse html
  var summaryTextNode = ns.$.parseHTML(summary);

  if (summaryTextNode !== null) {
    summaryText = summaryTextNode[0].nodeValue;
  }

  if (summaryText !== undefined) {
    summaryText = this.field.label + ': ' + (summaryText.length > 48 ? summaryText.substr(0, 45) + '...' : summaryText);
  }
  else {
    summaryText = this.field.label;
  }

  this.$group.children('.title').html(summaryText);
};

/**
 * Validate all children.
 */
ns.Group.prototype.validate = function () {
  var valid = true;

  if (this.children !== undefined) {
    for (var i = 0; i < this.children.length; i++) {
      if (this.children[i].validate() === false) {
        valid = false;
      }
    }
  }

  return valid;
};

/**
 * Allows ancestors and widgets to do stuff with our children.
 *
 * @public
 * @param {Function} task
 */
ns.Group.prototype.forEachChild = function (task) {
  for (var i = 0; i < this.children.length; i++) {
    task(this.children[i], i);
  }
};

/**
 * Collect functions to execute once the tree is complete.
 *
 * @param {function} ready
 * @returns {undefined}
 */
ns.Group.prototype.ready = function (ready) {
  this.parent.ready(ready);
};

/**
 * Remove this item.
 */
ns.Group.prototype.remove = function () {
  if (this.$group !== undefined) {
    ns.removeChildren(this.children);
    this.$group.remove();
  }
};

// Tell the editor what widget we are.
ns.widgets.group = ns.Group;
