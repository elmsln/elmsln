var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Create a field where one can select and include another library to the form.
 *
 * @param {mixed} parent
 * @param {Object} field
 * @param {mixed} params
 * @param {function} setValue
 * @returns {ns.Library}
 */
ns.Library = function (parent, field, params, setValue) {
  var that = this;

  if (params === undefined) {
    this.params = {params: {}};
    setValue(field, this.params);
  } else {
    this.params = params;
  }

  this.field = field;
  this.parent = parent;
  this.changes = [];
  this.optionsLoaded = false;
  this.library = parent.library + '/' + field.name;

  this.passReadies = true;
  parent.ready(function () {
    that.passReadies = false;
  });
};

/**
 * Append the library selector to the form.
 *
 * @param {jQuery} $wrapper
 * @returns {undefined}
 */
ns.Library.prototype.appendTo = function ($wrapper) {
  var that = this;

  var html = '';
  if (this.field.label !== 0) {
    html = '<label class="h5peditor-label">' + (this.field.label === undefined ? this.field.name : this.field.label) + '</label>';
  }

  html = '<div class="field ' + this.field.type + '">' + html + '<select>' + ns.createOption('-', 'Loading...') + '</select>';
  if (this.field.description !== undefined) {
    html += '<div class="h5peditor-field-description">' + this.field.description + '</div>';
  }
  // TODO: Remove errors, it is deprecated
  html += '<div class="errors h5p-errors"></div><div class="libwrap"></div></div>';

  var $field = ns.$(html).appendTo($wrapper);
  this.$select = $field.children('select');
  this.$libraryWrapper = $field.children('.libwrap');

  ns.$.post(ns.getAjaxUrl('libraries'), {libraries: that.field.options}, function (data) {
    that.libraries = data;

    var options = ns.createOption('-', '-');
    for (var i = 0; i < data.length; i++) {
      var library = data[i];
      if (library.title !== undefined) {
        options += ns.createOption(library.uberName, library.title, library.uberName === that.params.library);
      }
    }

    that.$select.html(options).change(function () {
      if (that.params.library === undefined || confirm(H5PEditor.t('core', 'confirmChangeLibrary'))) {
        that.loadLibrary(ns.$(this).val());
      }
    });

    if (data.length === 1) {
      that.$select.hide();
      $field.children('.h5peditor-label').hide();
      that.loadLibrary(that.$select.children(':last').val(), true);
    }

    if (that.runChangeCallback === true) {
      // In case a library has been selected programmatically trigger change events, e.g. a default library.
      that.change();
      that.runChangeCallback = false;
    }
  });

  // Load default library.
  if (this.params.library !== undefined) {
    that.loadLibrary(this.params.library, true);
  }
};

/**
 * Load the selected library.
 *
 * @param {String} libraryName On the form machineName.majorVersion.minorVersion
 * @param {Boolean} preserveParams
 * @returns {unresolved}
 */
ns.Library.prototype.loadLibrary = function (libraryName, preserveParams) {
  var that = this;

  this.removeChildren();

  if (libraryName === '-') {
    delete this.params.library;
    delete this.params.params;
    this.$libraryWrapper.attr('class', 'libwrap');
    return;
  }

  this.$libraryWrapper.html(ns.t('core', 'loading', {':type': 'semantics'})).addClass(libraryName.split(' ')[0].toLowerCase().replace('.', '-') + '-editor');

  ns.loadLibrary(libraryName, function (semantics) {
    that.currentLibrary = libraryName;
    that.params.library = libraryName;

    if (preserveParams === undefined || !preserveParams) {
      // Reset params
      that.params.params = {};
    }
    
    ns.processSemanticsChunk(semantics, that.params.params, that.$libraryWrapper.html(''), that);

    if (that.libraries !== undefined) {
      that.change();
    }
    else {
      that.runChangeCallback = true;
    }
  });
};

/**
 * Add the given callback or run
 * @param {type} callback
 * @returns {Number|@pro;length@this.changes}
 */
ns.Library.prototype.change = function (callback) {
  if (callback !== undefined) {
    // Add callback
    this.changes.push(callback);
  }
  else {
    // Find library
    var library;
    for (var i = 0; i < this.libraries.length; i++) {
      if (this.libraries[i].uberName === this.currentLibrary) {
        library = this.libraries[i];
        break;
      }
    }

    // Run callbacks
    for (var i = 0; i < this.changes.length; i++) {
      this.changes[i](library);
    }
  }
};

/**
 * Validate this field and its children.
 */
ns.Library.prototype.validate = function () {
  if (this.params.library === undefined) {
    return false;
  }

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
ns.Library.prototype.ready = function (ready) {
  if (this.passReadies) {
    this.parent.ready(ready);
  }
  else {
    this.readies.push(ready);
  }
};

/**
 * Custom remove children that supports common fields.
 *
 * @returns {unresolved}
 */
ns.Library.prototype.removeChildren = function () {
  if (this.currentLibrary === '-' || this.children === undefined) {
    return;
  }

  var ancestor = ns.findAncestor(this.parent);

  for (var libraryPath in ancestor.commonFields) {
    var library = libraryPath.split('/')[0];

    if (library === this.currentLibrary) {
      var remove = false;

      for (var fieldName in ancestor.commonFields[libraryPath]) {
        var field = ancestor.commonFields[libraryPath][fieldName];
        if (field.parents.length === 1) {
          field.instance.remove();
          remove = true;
        }

        for (var i = 0; i < field.parents.length; i++) {
          if (field.parents[i] === this) {
            field.parents.splice(i, 1);
            field.setValues.splice(i, 1);
          }
        }
      }

      if (remove) {
        delete ancestor.commonFields[libraryPath];
      }
    }
  }
  ns.removeChildren(this.children);
};

/**
 * Called when this item is being removed.
 */
ns.Library.prototype.remove = function () {
  this.removeChildren();
  this.$select.parent().remove();
};

// Tell the editor what widget we are.
ns.widgets.library = ns.Library;
