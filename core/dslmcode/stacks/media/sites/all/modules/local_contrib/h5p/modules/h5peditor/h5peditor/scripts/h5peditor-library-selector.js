/* global ns */
/**
 * Construct a library selector.
 *
 * @param {Array} libraries
 * @param {String} defaultLibrary
 * @param {Object} defaultParams
 * @returns {ns.LibrarySelector}
 */
ns.LibrarySelector = function (libraries, defaultLibrary, defaultParams) {
  var that = this;

  this.libraries = libraries;

  H5P.EventDispatcher.call(this);

  try {
    this.defaultParams = JSON.parse(defaultParams);
    if (!(this.defaultParams instanceof Object)) {
      throw true;
    }
  }
  catch (event) {
    // Content parameters are broken. Reset. (This allows for broken content to be reused without deleting it)
    this.defaultParams = {};
  }

  this.defaultLibrary = this.currentLibrary = defaultLibrary;
  this.defaultLibraryParameterized = defaultLibrary ? defaultLibrary.replace('.', '-').toLowerCase() : undefined;

  //Add tutorial and example link:
  this.$tutorialUrl = ns.$('<a class="h5p-tutorial-url" target="_blank">' + ns.t('core', 'tutorial') + '</a>').hide();
  this.$exampleUrl = ns.$('<a class="h5p-example-url" target="_blank">' + ns.t('core', 'example') + '</a>').hide();

  // Create confirm dialog
  var changeLibraryDialog = new H5P.ConfirmationDialog({
    headerText: H5PEditor.t('core', 'changeLibrary'),
    dialogText: H5PEditor.t('core', 'confirmChangeLibrary')
  }).appendTo(document.body);

  if (H5PIntegration.hubIsEnabled) {
    this.selector = new ns.SelectorHub(libraries, defaultLibrary, changeLibraryDialog);
  }
  else {
    this.selector = new ns.SelectorLegacy(libraries, defaultLibrary, changeLibraryDialog);
  }

  this.$selector = ns.$(this.selector.getElement());

  /**
   * @private
   * @param {object} library
   */
  var librarySelectHandler = function (library) {
    that.currentLibrary = library.uberName;
    that.loadSemantics(library.uberName, that.selector.getParams(), that.selector.getMetadata());

    that.$tutorialUrl.attr('href', library.tutorialUrl ? library.tutorialUrl : '#').toggle(!!library.tutorialUrl);
    that.$exampleUrl.attr('href', library.exampleUrl ? library.exampleUrl : '#').toggle(!!library.exampleUrl);
  };

  /**
   * Event handler for loading a new library editor
   * @private
   */
  var loadLibrary = function () {
    that.trigger('editorload', that.selector.currentLibrary);
    that.selector.getSelectedLibrary(librarySelectHandler);
  };

  /**
   * Event handler for loading a new library editor
   *
   * @param {Object} clipboard
   * @return {boolean}
   */
  this.canPaste = function (clipboard) {
    var i, uberName;
    if (clipboard && clipboard.generic) {
      if (libraries.libraries !== undefined) {
        // HUB
        for (i = 0; i < libraries.libraries.length; i++) {
          uberName = libraries.libraries[i].machineName + ' ' + libraries.libraries[i].localMajorVersion + '.' + libraries.libraries[i].localMinorVersion;
          if (uberName === clipboard.generic.library) {
            return true;
          }
        }
      }
      else {
        // Legacy
        for (i = 0; i < libraries.length; i++) {
          uberName = libraries[i].name + ' ' + libraries[i].majorVersion + '.' + libraries[i].minorVersion;
          if (uberName === clipboard.generic.library) {
            return true;
          }
        }
      }
    }
    return false;
  };

  /**
   * Confirm replace if there is content selected
   *
   * @param {number} top Offset
   * @param {function} next Next callback
   */
  this.confirmPasteError = function (message, top, next) {
    // Confirm changing library
    var confirmReplace = new H5P.ConfirmationDialog({
      headerText: H5PEditor.t('core', 'pasteError'),
      dialogText: message,
      cancelText: ' ',
      confirmText: H5PEditor.t('core', 'ok')
    }).appendTo(document.body);
    confirmReplace.on('confirmed', next);
    confirmReplace.show(top);
  };

  // Change library on confirmation
  changeLibraryDialog.on('confirmed', loadLibrary);

  // Revert selector on cancel
  changeLibraryDialog.on('canceled', function () {
    that.selector.resetSelection(that.currentLibrary, that.defaultParams, that.form.metadata, true);
  });

  // First time a library is selected in the editor
  this.selector.on('selected', loadLibrary);

  this.selector.on('resize', function () {
    that.trigger('resize');
  });

  this.on('select', loadLibrary);

  H5P.externalDispatcher.on('datainclipboard', function (event) {
    var disable = !event.data.reset;
    if (disable) {
      // Check if content type is supported here
      disable = that.canPaste(H5P.getClipboard());
    }
    that.$pasteButton.toggleClass('disabled', !disable);
    if (that.selector.setCanPaste) {
      that.selector.setCanPaste(disable);
    }
  });

  this.selector.on('paste', function () {
    that.pasteContent();
  });
};

// Extends the event dispatcher
ns.LibrarySelector.prototype = Object.create(H5P.EventDispatcher.prototype);
ns.LibrarySelector.prototype.constructor = ns.LibrarySelector;

/**
 * Sets the current library
 *
 * @param {string} library
 */
ns.LibrarySelector.prototype.setLibrary = function (library) {
  this.trigger('select');
};

/**
 * Append the selector html to the given container.
 *
 * @param {jQuery} $element
 * @returns {undefined}
 */
ns.LibrarySelector.prototype.appendTo = function ($element) {
  var self = this;
  this.$parent = $element;

  this.$selector.appendTo($element);
  this.$tutorialUrl.appendTo($element);
  this.$exampleUrl.appendTo($element);

  if (window.localStorage) {
    var $buttons = ns.$(ns.createCopyPasteButtons()).appendTo($element);

    // Hide copy paste until library is selected:
    $buttons.addClass('hidden');
    self.on('editorloaded', function () {
      $buttons.removeClass('hidden');
    });

    this.$copyButton = $buttons.find('.h5peditor-copy-button').click(function () {
      if (this.classList.contains('disabled')) {
        return;
      }
      H5P.clipboardify({
        library: self.getCurrentLibrary(),
        params: self.getParams(),
        metadata: self.getMetadata()
      });
      ns.attachToastTo(
        self.$copyButton.get(0),
        H5PEditor.t('core', 'copiedToClipboard'),
        {position: {
          horizontal: 'center',
          vertical: 'above',
          noOverflowX: true
        }}
      );
    });
    this.$pasteButton = $buttons.find('.h5peditor-paste-button').click(function () {
      // Notify user why paste is not possible
      if (this.classList.contains('disabled')) {
        const pasteCheck = ns.canPastePlus(H5P.getClipboard(), self.libraries);
        if (pasteCheck.canPaste !== true) {
          if (pasteCheck.reason === 'pasteTooOld' || pasteCheck.reason === 'pasteTooNew') {
            self.confirmPasteError(pasteCheck.description, self.$parent.offset().top, function () {});
          }
          else {
            ns.attachToastTo(
              self.$pasteButton.get(0),
              pasteCheck.description,
              {position: {
                horizontal: 'center',
                vertical: 'above',
                noOverflowX: true
              }}
            );
          }
          return;
        }
      }

      self.pasteContent();
    });

    if (this.canPaste(H5P.getClipboard())) {
      // Toggle paste button when libraries are loaded
      this.$pasteButton.toggleClass('disabled', false);
      if (this.selector.setCanPaste) {
        this.selector.setCanPaste(true);
      }
    }
  }
};

/**
 * Sets the current library
 *
 * @param {string} library
 */
ns.LibrarySelector.prototype.pasteContent = function () {
  var self = this;
  var clipboard = H5P.getClipboard();

  // Tell user why paste is not possible
  const pasteCheck = ns.canPastePlus(H5P.getClipboard(), self.libraries);
  if (pasteCheck.canPaste !== true) {
    if (pasteCheck.reason === 'pasteTooOld' || pasteCheck.reason === 'pasteTooNew') {
      self.confirmPasteError(pasteCheck.description, self.$parent.offset().top, function () {});
    }
    else {
      ns.attachToastTo(
        document.getElementById('h5peditor-hub-paste-button'),
        pasteCheck.description,
        {position: {
          horizontal: 'center',
          vertical: 'above',
          noOverflowX: true,
          overflowReference: document.body}
        }
      );
    }
    return;
  }

  ns.confirmReplace(self.getCurrentLibrary(), self.$parent.offset().top, function () {
    self.selector.resetSelection(clipboard.generic.library, clipboard.generic.params, clipboard.generic.metadata, false);
    self.setLibrary();
  });
};

/**
 * Display loading message and load library semantics.
 *
 * @param {String} library
 * @param {Object} params Pass in params to semantics
 * @returns {unresolved}
 */
ns.LibrarySelector.prototype.loadSemantics = function (library, params, metadata) {
  var that = this;

  if (this.form !== undefined) {
    // Remove old form.
    this.form.remove();
  }

  if (library === '-') {
    // No library chosen.
    this.$parent.attr('class', 'h5peditor');
    return;
  }
  this.$parent.attr('class', 'h5peditor ' + library.split(' ')[0].toLowerCase().replace('.', '-') + '-editor');

  // Display loading message
  var $loading = ns.$('<div class="h5peditor-loading h5p-throbber">' + ns.t('core', 'loading') + '</div>').appendTo(this.$parent);

  this.$selector.attr('disabled', true);

  ns.resetLoadedLibraries();
  ns.loadLibrary(library, function (semantics) {
    if (!semantics) {
      that.form = ns.$('<div/>', {
        'class': 'h5p-errors',
        text: H5PEditor.t('core', 'noSemantics'),
        insertAfter: $loading
      });
    }
    else {
      var overrideParams = {};
      if (params) {
        overrideParams = params;
        that.defaultParams = overrideParams;
      }
      else if (library === that.defaultLibrary || library === that.defaultLibraryParameterized) {
        overrideParams = that.defaultParams;
      }

      if (!metadata) {
        metadata = overrideParams.metadata;
      }
      const defaultLanguage = metadata && metadata.defaultLanguage
        ? metadata.defaultLanguage
        : null;
      that.form = new ns.Form(
        library,
        ns.libraryCache[library].languages,
        defaultLanguage
      );
      that.form.replace($loading);
      that.form.currentLibrary = library;
      that.form.processSemantics(semantics, overrideParams, metadata);
      if (window.localStorage) {
        that.$copyButton.toggleClass('disabled', false);
        that.$pasteButton.text(ns.t('core', 'pasteAndReplaceButton'));
        that.$pasteButton.attr('title', ns.t('core', 'pasteAndReplaceFromClipboard'));
      }
    }

    that.$selector.attr('disabled', false);
    $loading.remove();
    that.trigger('editorloaded', library);
  });
};

/**
 * Returns currently selected library
 *
 * @returns {string} Currently selected library
 */
ns.LibrarySelector.prototype.getCurrentLibrary = function () {
  return this.currentLibrary;
};

/**
 * Return params needed to start library.
 */
ns.LibrarySelector.prototype.getParams = function () {
  if (this.form === undefined) {
    return;
  }

  // Only return if all fields has validated.
  //var valid = true;

  if (this.form.metadataForm.children !== undefined) {
    for (var i = 0; i < this.form.metadataForm.children.length; i++) {
      if (this.form.metadataForm.children[i].validate() === false) {
        //valid = false;
      }
    }
  }

  if (this.form.children !== undefined) {
    for (var i = 0; i < this.form.children.length; i++) {
      if (this.form.children[i].validate() === false) {
        //valid = false;
      }
    }
  }

  //return valid ? this.form.params : false;
  return this.form.params; // TODO: Switch to the line above when we are able to tell the user where the validation fails
};

/**
 * Get the metadata of the main form.
 *
 * @return {object} Metadata object.
 */
ns.LibrarySelector.prototype.getMetadata = function () {
  if (this.form === undefined) {
    return;
  }

  return this.form.metadata;
};

/**
 *
 * @param content
 * @param library
 * @returns {H5PEditor.Presave} Result after processing library and content
 */
ns.LibrarySelector.prototype.presave = function (content, library) {
  return (new ns.Presave).process(library, content);
};
