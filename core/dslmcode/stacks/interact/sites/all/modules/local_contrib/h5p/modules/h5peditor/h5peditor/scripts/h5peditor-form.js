var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Construct a form from library semantics.
 */
ns.Form = function () {
  this.params = {};
  this.passReadies = false;
  this.commonFields = {};
  this.$form = ns.$('<div class="h5peditor-form"><div class="tree"></div><div class="common"><div class="h5peditor-label">' + ns.t('core', 'commonFields') + '</div></div></div>');
  this.$common = this.$form.children('.common');
  this.library = '';
};

/**
 * Replace the given element with our form.
 *
 * @param {jQuery} $element
 * @returns {undefined}
 */
ns.Form.prototype.replace = function ($element) {
  $element.replaceWith(this.$form);
  this.offset = this.$form.offset();
  // Prevent inputs and selects in an h5peditor form from submitting the main
  // framework form.
  this.$form.on('keydown', 'input,select', function (event) {
    if (event.keyCode === 13) {
      // Prevent enter key from submitting form.
      return false;
    }
  });
};

/**
 * Remove the current form.
 */
ns.Form.prototype.remove = function () {
  this.$form.remove();
};

/**
 * Wrapper for processing the semantics.
 *
 * @param {Array} semantics
 * @param {Object} defaultParams
 * @returns {undefined}
 */
ns.Form.prototype.processSemantics = function (semantics, defaultParams) {
  try {
    this.params = defaultParams;
    ns.processSemanticsChunk(semantics, this.params, this.$form.children('.tree'), this);
  }
  catch (error) {
    if (window['console'] !== undefined && typeof console.error === 'function') {
      console.error(error.stack);
    }

    var $error = ns.$('<div class="h5peditor-error">' + ns.t('core', 'semanticsError', {':error': error}) + '</div>');
    this.$form.replaceWith($error);
    this.$form = $error;
  }
};

/**
 * Collect functions to execute once the tree is complete.
 *
 * @param {function} ready
 * @returns {undefined}
 */
ns.Form.prototype.ready = function (ready) {
  this.readies.push(ready);
};
