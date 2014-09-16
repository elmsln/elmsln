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
};

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

  this.$group = ns.$('<fieldset class="field group"><div class="title"><a href="#" class="expand" title="' + ns.t('core', 'expandCollapse') + '"></a><span class="text"></span></div><div class="content"></div></fieldset>')
  .appendTo($wrapper).find('.expand').click(function () {
    that.expand();
    return false;
  }).end();

  if (this.field.fields.length === 1) {
    this.children = [];
    var field = this.field.fields[0];
    var widget = field.widget === undefined ? field.type : field.widget;
    this.children[0] = new ns.widgets[widget](this, field, this.params, function (field, value) {
      that.setValue(that.field, value);
    });
    this.children[0].appendTo(this.$group.children('.content'));
  }
  else {
    if (this.params === undefined) {
      this.params = {};
      this.setValue(this.field, this.params);
    }
    ns.processSemanticsChunk(this.field.fields, this.params, this.$group.children('.content'), this);
  }

  // Set summary
  this.findSummary();
};

/**
 * Expand the given group.
 */
ns.Group.prototype.expand = function () {
  var expandedClass = 'expanded';

  if (this.$group.hasClass(expandedClass)) {
    // Do not collapse before valid!
    var valid = true;
    for (var i = 0; i < this.children.length; i++) {
      if (this.children[i].validate() === false) {
        valid = false;
      }
    }
    if (valid) {
      this.$group.removeClass(expandedClass);
    }
  }
  else {
    this.$group.addClass(expandedClass);
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
  if (summary !== undefined) {
    summary = this.field.label + ': ' + (summary.length > 48 ? summary.substr(0, 45) + '...' : summary);
  }
  else {
    summary = this.field.label;
  }

  this.$group.children('.title').children('.text').text(summary);
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
