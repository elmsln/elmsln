var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

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
  var firstTime = true;
  var options = '<option value="-">-</option>';

  try {
    this.defaultParams = JSON.parse(defaultParams);
    if (!(this.defaultParams instanceof Object)) {
      throw true;
    }
  }
  catch (event) {
    // Content parameters are broken. Reset. (This allows for broken content to be reused without deleting it)
    this.defaultParams = {};
    // TODO: Inform the user?
  }

  this.defaultLibrary = this.currentLibrary = defaultLibrary;
  this.defaultLibraryParameterized = defaultLibrary ? defaultLibrary.replace('.', '-').toLowerCase() : undefined;

  for (var i = 0; i < libraries.length; i++) {
    var library = libraries[i];
    var libraryName = ns.libraryToString(library);

    // Never deny editing existing content
    // For new content deny old or restricted libs.
    if (this.defaultLibrary === libraryName ||
       ((library.restricted === undefined || !library.restricted) &&
         library.isOld !== true
      )
    ) {
      options += '<option value="' + libraryName + '"';
      if (libraryName === defaultLibrary || library.name === this.defaultLibraryParameterized) {
        options += ' selected="selected"';
      }
      if (library.tutorialUrl !== undefined) {
        options += ' data-tutorial-url="' + library.tutorialUrl + '"';
      }
      options += '>' + library.title + (library.isOld===true ? ' (deprecated)' : '') + '</option>';
    }
  }

  //Add tutorial link:
  this.$tutorialUrl = ns.$('<a class="h5p-tutorial-url" target="_blank">' + ns.t('core', 'tutorialAvailable') + '</a>').hide();

  // Create confirm dialog
  var changeLibraryDialog = new H5P.ConfirmationDialog({
    headerText: H5PEditor.t('core', 'changeLibrary'),
    dialogText: H5PEditor.t('core', 'confirmChangeLibrary')
  }).appendTo(document.body);

  // Change library on confirmed
  changeLibraryDialog.on('confirmed', function () {
    changeLibraryToSelector();
  });

  // Revert selector on cancel
  changeLibraryDialog.on('canceled', function () {
    that.$selector.val(that.currentLibrary);
  });

  // Change library to selected
  var changeLibraryToSelector = function () {
    var library = that.$selector.val();
    that.loadSemantics(library);
    that.currentLibrary = library;

    if (library !== '-') {
      firstTime = false;
    }

    var tutorialUrl = that.$selector.find(':selected').data('tutorial-url');
    that.$tutorialUrl.attr('href', tutorialUrl).toggle(tutorialUrl !== undefined && tutorialUrl !== null && tutorialUrl.length !== 0);
  };

  this.$selector = ns.$('<select name="h5peditor-library" title="' + ns.t('core', 'selectLibrary') + '">' + options + '</select>').change(function () {
    // Use timeout to avoid bug in Chrome >44, when confirm is used inside change event.
    // Ref. https://code.google.com/p/chromium/issues/detail?id=525629
    setTimeout(function () {
      if (!firstTime) {
        changeLibraryDialog.show(that.$selector.offset().top);
      }
      else {
        changeLibraryToSelector();
      }
    }, 0);
  });
};

/**
 * Append the selector html to the given container.
 *
 * @param {jQuery} $element
 * @returns {undefined}
 */
ns.LibrarySelector.prototype.appendTo = function ($element) {
  this.$parent = $element;

  this.$selector.appendTo($element);
  this.$tutorialUrl.appendTo($element);

  $element.append('<div class="h5p-more-libraries">' + ns.t('core', 'moreLibraries') + '</div>');
};

/**
 * Display loading message and load library semantics.
 *
 * @param {String} library
 * @returns {unresolved}
 */
ns.LibrarySelector.prototype.loadSemantics = function (library) {
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

  ns.loadLibrary(library, function (semantics) {
    if (!semantics) {
      that.form = ns.$('<div/>', {
        'class': 'h5p-errors',
        text: H5PEditor.t('core', 'noSemantics'),
        insertAfter: $loading
      });
    }
    else {
      that.form = new ns.Form();
      that.form.replace($loading);
      that.form.processSemantics(semantics, (library === that.defaultLibrary || library === that.defaultLibraryParameterized ? that.defaultParams : {}));
    }

    that.$selector.attr('disabled', false);
    $loading.remove();
  });
};

/**
 * Return params needed to start library.
 */
ns.LibrarySelector.prototype.getParams = function () {
  if (this.form === undefined) {
    return;
  }

  // Only return if all fields has validated.
  var valid = true;

  if (this.form.children !== undefined) {
    for (var i = 0; i < this.form.children.length; i++) {
      if (this.form.children[i].validate() === false) {
        valid = false;
      }
    }
  }

  //return valid ? this.form.params : false;
  return this.form.params; // TODO: Switch to the line above when we are able to tell the user where the validation fails
};
