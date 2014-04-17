var H5PEditor = H5PEditor || {};

var H5P = H5P || {};
if (H5P.getPath === undefined) {
  /**
   * Find the path to the content files based on the id of the content
   *
   * Also identifies and returns absolute paths
   *
   * @param {String} path Absolute path to a file, or relative path to a file in the content folder
   * @param {Number} contentId Identifier of the content requesting the path
   * @returns {String} The path to use.
   */
  H5P.getPath = function (path, contentId) {
    if (path.substr(0, 7) === 'http://' || path.substr(0, 8) === 'https://') {
      return path;
    }

    return H5PIntegration.getContentPath(contentId) + path;
  };
}
if (H5P.newInstance === undefined) {
  /**
   * Helps create new instance of H5P library.
   *
   * @param {Object} library Container library (the über name of the library(namespace, name and versionnumber)) and .
   * @returns {Object} Instance of library
   */
  H5P.newInstance = function (library) {
    // TODO: Add some try catching?
    // TODO: Dynamically try to load libraries currently not loaded?
    return new (H5P.classFromName(library.library.split(' ')[0]))(library.params, H5PEditor.contentId);
  };
}

// TODO: Rewrite to use H5P.DragQuestion for previewing!

/**
 * Interactive Video editor widget module
 *
 * @param {jQuery} $
 */
H5PEditor.widgets.dragQuestion = H5PEditor.DragQuestion = (function ($) {
  /**
   * Initialize interactive video editor.
   *
   * @param {Object} parent
   * @param {Object} field
   * @param {Object} params
   * @param {function} setValue
   * @returns {_L8.C}
   */
  function C(parent, field, params, setValue) {
    var that = this;

    // Set params
    if (params === undefined) {
      this.params = {
        elements: [],
        dropZones: []
      };
      setValue(field, this.params);
    }
    else {
      this.params = params;
    }

    // Get updates for fields
    H5PEditor.followField(parent, 'settings/background', function (params) {
      that.setBackground(params);
    });
    H5PEditor.followField(parent, 'settings/size', function (params) {
      that.setSize(params);
    });

    // Get options from semantics, clone since we'll be changing values.
    this.elementFields = H5P.cloneObject(field.fields[0].field.fields, true);
    this.dropZoneFields = H5P.cloneObject(field.fields[1].field.fields, true);
    this.elementLibraryOptions = this.elementFields[0].options;
    this.elementDropZoneFieldWeight = 5;
    this.elementFields[this.elementDropZoneFieldWeight].options = [];
    this.dropZoneElementFieldWeight = 6;
    this.elementOptions = [];

    this.parent = parent;
    this.field = field;

    this.passReadies = true;
    parent.ready(function () {
      that.passReadies = false;
    });
  };

  /**
   * Append field to wrapper.
   *
   * @param {jQuery} $wrapper
   * @returns {undefined}
   */
  C.prototype.appendTo = function ($wrapper) {
    var that = this;

    this.$item = $(this.createHtml()).appendTo($wrapper);
    this.$editor = this.$item.children('.h5peditor-dragquestion');
    this.$dnbWrapper = this.$item.children('.h5peditor-dragnbar');
    this.$dialog = this.$item.children('.h5peditor-fluid-dialog');
    this.$dialogInner = this.$dialog.children('.h5peditor-fd-inner');
    this.$errors = this.$item.children('.h5p-errors');

    // Handle click events for dialog buttons.
    this.$dialog.find('.h5peditor-done').click(function () {
      if (that.doneCallback() !== false) {
        that.hideDialog();
      }
      return false;
    }).end().find('.h5peditor-remove').click(function () {
      that.removeCallback();
      that.hideDialog();
      return false;
    });

    // Get editor default font size.
    this.fontSize = parseInt(this.$editor.css('fontSize'));
  };

  /**
   * Create HTML for the field.
   *
   * @returns {@exp;H5PEditor@call;createItem}
   */
  C.prototype.createHtml = function () {
    var html = '';
    if (this.field.label !== 0) {
      html += '<span class="h5peditor-label">' + this.field.label + '</span>';
    }

    html += '<div class="h5peditor-dragnbar"></div>'
      + '<div class="h5peditor-dragquestion">' + C.t('noTaskSize') + '</div>'
      + '<div class="h5peditor-fluid-dialog">'
      + '  <div class="h5peditor-fd-inner"></div>'
      + '  <div class="h5peditor-fd-buttons">'
      + '    <a href="#" class="h5peditor-fd-button h5peditor-done">' + C.t('done') + '</a>'
      + '    <a href="#" class="h5peditor-fd-button h5peditor-remove">' + C.t('remove') + '</a>'
      + '  </div>'
      + '</div>';

    if (this.field.description !== undefined) {
      html += '<div class="h5peditor-field-description">' + this.field.description + '</div>';
    }

    return H5PEditor.createItem(this.field.widget, html);
  };

  /**
   * Set current background.
   *
   * @param {Object} params
   * @returns {undefined}
   */
  C.prototype.setBackground = function (params) {
    var path = params === undefined ? '' : params.path;
    if (path !== '') {
      // Add correct base path
      path = 'url("' + H5P.getPath(path, H5PEditor.contentId) + '")';
    }

    this.$editor.css({
      backgroundImage: path
    });
  };

  /**
   * Set current dimensions.
   *
   * @param {Object} params
   * @returns {undefined}
   */
  C.prototype.setSize = function (params) {
    this.size = params;
  };

  /**
   * Apply new size to task editor once visible.
   *
   * @returns {undefined}
   */
  C.prototype.setActive = function () {
    if (this.size === undefined || this.size.width === undefined) {
      return;
    }
    var maxWidth = this.$item.width();
    if (this.size.width < maxWidth) {
      this.$editor.css({
        width: this.size.width,
        height: this.size.height,
        fontSize: this.fontSize
      });
      this.$dnbWrapper.css({
        width: this.size.width
      });
    }
    else {
      this.$editor.css({
        width: '100%',
        height: maxWidth * (this.size.height / this.size.width),
        fontSize: this.fontSize * (maxWidth / this.size.width)
      });
      this.$dnbWrapper.css({
        width: '100%'
      });
    }


    // TODO: Should we care about resize events? Will only be an issue for responsive designs.

    if (this.dnb === undefined) {
      this.activateEditor();
    }

    // TODO: Move elements that is outside inside.
  };

  /**
   * Activate DragNBar and add elements.
   *
   * @returns {undefined}
   */
  C.prototype.activateEditor = function () {
    var that = this;
    this.$editor.html('').addClass('h5p-ready');

    // Create new bar
    this.dnb = new H5P.DragNBar(this.getButtons(), this.$editor);

    // Add event handling
    this.dnb.stopMovingCallback = function (x, y) {
      // Update params when the element is dropped.
      var id = that.dnb.dnd.$element.data('id');
      var params = that.dnb.dnd.$element.hasClass('h5p-dq-dz') ? that.params.dropZones[id] : that.params.elements[id];
      params.x = x;
      params.y = y;
    };
    this.dnb.dnd.releaseCallback = function () {
      // Edit element when it is dropped.
      if (that.dnb.newElement) {
        setTimeout(function () {
          that.dnb.dnd.$element.dblclick();
        }, 1);
        that.dnb.newElement = false;
      }
    };
    this.dnb.attach(this.$dnbWrapper);

    // Init resize
    this.dnr = new H5P.DragNResize(this.$editor);
    this.dnr.resizeCallback = function (newWidth, newHeight) {
      var id = that.dnr.$element.data('id');
      var params = that.dnr.$element.hasClass('h5p-dq-dz') ? that.params.dropZones[id] : that.params.elements[id];
      params.width = newWidth;
      params.height = newHeight;
    };

    // Add Elements
    this.elements = [];
    for (var i = 0; i < this.params.elements.length; i++) {
      this.insertElement(i);
    }

    // Add Drop Zones
    this.dropZones = [];
    for (var i = 0; i < this.params.dropZones.length; i++) {
      this.insertDropZone(i);
    }
  };

  /**
   * Generate sub forms that's ready to use in the dialog.
   *
   * @param {Object} semantics
   * @param {Object} params
   * @returns {_L8.C.prototype.generateElementForm.Anonym$2}
   */
  C.prototype.generateForm = function (semantics, params) {
    var $form = $('<div></div>');
    H5PEditor.processSemanticsChunk(semantics, params, $form, this);
    var $lib = $form.children('.library:first');
    if ($lib.length !== 0) {
      $lib.children('label, select, .h5peditor-field-description').hide().end().children('.libwrap').css('margin-top', '0');
    }

    return {
      $form: $form,
      children: this.children
    };
  };

  /**
   * Generate a list of buttons for DnB.
   *
   * @returns {Array} Buttons
   */
  C.prototype.getButtons = function () {
    var that = this;

    var buttons = [{
      id: 'dropzone',
      title: 'Drop Zone',
      createElement: function () {
        that.params.dropZones.push({
          x: 0,
          y: 0,
          width: 5,
          height: 2.5,
          correctElements: ''
        });

        return that.insertDropZone(that.params.dropZones.length - 1);
      }
    }];

    for (var i = 0; i < this.elementLibraryOptions.length; i++) {
      buttons.push(this.getButton(this.elementLibraryOptions[i]));
    }

    return buttons;
  };

  /**
   * Generate a single element button for the DnB.
   *
   * @param {String} library Library name + version
   * @returns {Object} DnB button semantics
   */
  C.prototype.getButton = function (library) {
    var that = this;
    var id = library.split(' ')[0].split('.')[1].toLowerCase();
    var h = id == 'text' ? 1.25 : 5;
    return {
      id: id,
      title: C.t('insertElement', {':type': id}),
      createElement: function () {
        that.params.elements.push({
          type: {
            library: library,
            params: {}
          },
          x: 0,
          y: 0,
          width: 5,
          height: h,
          dropZones: []
        });

        return that.insertElement(that.params.elements.length - 1);
      }
    };
  };

  /**
   * Insert element at given params index.
   *
   * @param {int} index
   * @returns {jQuery} The element's DOM
   */
  C.prototype.insertElement = function (index) {
    var that = this;
    var elementParams = this.params.elements[index];
    var element = this.generateForm(this.elementFields, elementParams);

    var library = this.children[0];

    // Get image aspect ratio
    var libraryChange = function () {
      if (library.children[0].field.type === 'image') {
        library.children[0].changes.push(function (params) {
          if (params === undefined) {
            return;
          }

          if (params.width !== undefined && params.height !== undefined) {
            elementParams.height = elementParams.width * (params.height / params.width);
            element.$element.css('height', elementParams.height + 'em');
          }
        });
      }
    };

    if (library.children === undefined) {
      library.changes.push(libraryChange);
    }
    else {
      libraryChange();
    }

    element.$element = $('<div class="h5p-dq-element" style="width:' + elementParams.width + 'em;height:' + elementParams.height + 'em;top:' + elementParams.y + '%;left:' + elementParams.x + '%">' + index + '</div>')
    .appendTo(this.$editor)
    .data('id', index)
    .mousedown(function (event) {
      that.dnb.dnd.press(element.$element, event.pageX, event.pageY);
      return false;
    }).dblclick(function () {
      that.editElement(element);
    });

    // Update element
    that.updateElement(element, index);

    this.elements[index] = element;
    return element.$element;
  };

  /**
   * Set callbacks and open dialog with the form for the given element.
   *
   * @param {Object} element
   * @returns {undefined}
   */
  C.prototype.editElement = function (element) {
    var that = this;
    var id = element.$element.data('id');

    this.doneCallback = function () {
      // Validate form
      var valid = true;
      for (var i = 0; i < element.children.length; i++) {
        if (element.children[i].validate() === false) {
          valid = false;
          break;
        }
      }
      if (!valid) {
        return false;
      }

      // Update element
      that.updateElement(element, id);
    };

    this.removeCallback = function () {
      var i, j, oldid;

      // Remove element form
      H5PEditor.removeChildren(element.children);

      // Remove element
      element.$element.remove();
      that.elements.splice(id, 1);
      that.params.elements.splice(id, 1);

      // Remove from options
      this.elementOptions.splice(id, 1);

      // If element was the answer for a dropZone, remove it from answer.
      for (i = 0; i < that.params.dropZones.length; i++) {
        if (that.params.dropZones[i].correctElements === '' + id) {
          that.params.dropZones[i].correctElements = '';
        }
      }

      // Reindex all elements
      for (i = 0; i < that.elements.length; i++) {
        // If index changes, and element is answer for dropZone, change in dropZone too.
        oldid = that.elements[i].$element.data('id');
        that.elements[i].$element.data('id', i);

        for (j = 0; j < that.params.dropZones.length; j++) {
          if (that.params.dropZones[j].correctElements === '' + oldid) {
            that.params.dropZones[j].correctElements = '' + i;
          }
        }
      }
    };

    element.children[this.elementDropZoneFieldWeight].setActive();
    this.showDialog(element.$form);
  };

  /**
   * Update the element with new data.
   *
   * @param {Object} element
   * @param {int} id
   * @returns {undefined}
   */
  C.prototype.updateElement = function (element, id) {
    var params = this.params.elements[id];
    // Create and add new instance
    element.instance = H5P.newInstance(params.type);
    element.instance.attach(element.$element);

    // Make resize possible
    this.dnr.add(element.$element);

    var type = params.type.library.split(' ')[0] === 'H5P.Text' ? 'text' : 'image';
    var label = type === 'text' ? $('<div>' + params.type.params.text + '</div>').text() : params.type.params.alt + '';

    // Update correct element options
    this.elementOptions[id] = {
      value: '' + id,
      label: C.t(type) + ': ' + (label.length > 32 ? label.substr(0, 32) + '...' : label)
    };

    if (params.dropZones !== undefined && params.dropZones.length) {
      element.$element.addClass('h5p-draggable');
    }
    else {
      element.$element.removeClass('h5p-draggable');
    }
  };

  /**
   * Insert the drop zone at the given index.
   *
   * @param {int} index
   * @returns {unresolved}
   */
  C.prototype.insertDropZone = function (index) {
    var that = this,
      dropZoneParams = this.params.dropZones[index],
      dropZone = this.generateForm(this.dropZoneFields, dropZoneParams);

    dropZone.$dropZone = $('<div class="h5p-dq-dz" style="width:' + dropZoneParams.width + 'em;height:' + dropZoneParams.height + 'em;top:' + dropZoneParams.y + '%;left:' + dropZoneParams.x + '%"></div>')
    .appendTo(this.$editor)
    .data('id', index)
    .mousedown(function (event) {
      that.dnb.dnd.press(dropZone.$dropZone, event.pageX, event.pageY);
      return false;
    }).dblclick(function () {
      // Edit
      that.editDropZone(dropZone);
    });

    // Make resize possible
    this.dnr.add(dropZone.$dropZone);

    // Add label
    this.updateDropZone(dropZone, index);

    this.dropZones[index] = dropZone;
    return dropZone.$dropZone;
  };

  /**
   * Set callbacks and open dialog with the form for the given drop zone.
   *
   * @param {Object} dropZone
   * @returns {undefined}
   */
  C.prototype.editDropZone = function (dropZone) {
    var that = this,
      id = dropZone.$dropZone.data('id');

    this.doneCallback = function () {
      // Validate form
      var valid = true;
      for (var i = 0; i < dropZone.children.length; i++) {
        if (dropZone.children[i].validate() === false) {
          valid = false;
          break;
        }
      }
      if (!valid) {
        return false;
      }

      that.updateDropZone(dropZone, id);
    };

    this.removeCallback = function () {
      var i, j;
      // Remove element form
      H5PEditor.removeChildren(dropZone.children);

      // Remove element
      dropZone.$dropZone.remove();
      that.dropZones.splice(id, 1);
      that.params.dropZones.splice(id, 1);

      // Remove from elements
      this.elementFields[this.elementDropZoneFieldWeight].options.splice(id, 1);

      // Remove dropZone from element params properly
      for (i = 0; i < that.params.elements.length; i++) {
        pos = ns.$.inArray(id, that.params.elements[i].dropZones)
        if (pos !== -1) {
          that.params.elements[i].dropZones.splice(pos, 1);
          i--;
        }
      }

      // Reindex all dropzones
      for (i = 0; i < that.dropZones.length; i++) {
        that.dropZones[i].$dropZone.data('id', i);
      }
    };

    // Add only available options
    var options = this.dropZoneFields[this.dropZoneElementFieldWeight].options = [];
    var dropZones;
    for (i = 0; i < this.elementOptions.length; i++) {
      dropZones = this.params.elements[i].dropZones;
      for (j = 0; j < dropZones.length; j++) {
        if (dropZones[j] === (id + '')) {
          options.push(this.elementOptions[i]);
          break;
        }
      }
    }

    dropZone.children[this.dropZoneElementFieldWeight].setActive();
    this.showDialog(dropZone.$form);
  };

  /**
   * Remove old label and add new.
   *
   * @param {Object} dropZone
   * @param {int} id
   * @returns {undefined}
   */
  C.prototype.updateDropZone = function (dropZone, id) {
    var params = this.params.dropZones[id];

    // Remove old label and add new.
    dropZone.$dropZone.children('.h5p-dq-dz-label').remove();
    if (params.showLabel === true) {
      $('<div class="h5p-dq-dz-label">' + params.label + '</div>').appendTo(dropZone.$dropZone);
    }

    this.elementFields[this.elementDropZoneFieldWeight].options[id] = {
      value: '' + id,
      label: params.label
    };
  };

  /**
   * Attach form to dialog and show.
   *
   * @param {jQuery} $form
   * @returns {undefined}
   */
  C.prototype.showDialog = function ($form) {
    this.$currentForm = $form;
    $form.appendTo(this.$dialogInner);
    this.$dialog.show();
    this.$editor.add(this.$dnbWrapper).hide();
    if (this.dnb !== undefined && this.dnb.dnd.$coordinates !== undefined) {
      this.dnb.dnd.$coordinates.remove();
      delete this.dnb.dnd.$coordinates;
    }
  };

  /**
   * Hide dialog and detach form.
   *
   * @returns {undefined}
   */
  C.prototype.hideDialog = function () {
    // Attempt to find and close CKEditor instances before detaching.
    if (H5PEditor.Html) {
      H5PEditor.Html.removeWysiwyg();
    }

    this.$currentForm.detach();
    this.$dialog.hide();
    this.$editor.add(this.$dnbWrapper).show();
  };

  /**
   * Validate the current field.
   *
   * @returns {Boolean}
   */
  C.prototype.validate = function () {
    return true;
  };

  /**
   * Remove the field from DOM.
   *
   * @returns {undefined}
   */
  C.prototype.remove = function () {
    this.$item.remove();
  };

  /**
   * Collect functions to execute once the tree is complete.
   *
   * @param {function} ready
   * @returns {undefined}
   */
  C.prototype.ready = function (ready) {
    if (this.passReadies) {
      this.parent.ready(ready);
    }
    else {
      this.readies.push(ready);
    }
  };

  /**
   * Translate UI texts for this library.
   *
   * @param {String} key
   * @param {Object} vars
   * @returns {@exp;H5PEditor@call;t}
   */
  C.t = function (key, vars) {
    return H5PEditor.t('H5PEditor.DragQuestion', key, vars);
  };

  return C;
})(H5P.jQuery);

// Default english translations
H5PEditor.language['H5PEditor.DragQuestion'] = {
  libraryStrings: {
    insertElement: 'Insert :type',
    done: 'Done',
    remove: 'Remove',
    image: 'Image',
    text: 'Text',
    noTaskSize: 'Please specify task size first.'
  }
};