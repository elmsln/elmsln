var H5PEditor = H5PEditor || {};

H5PEditor.widgets.select = H5PEditor.Select = (function (E) {
  /**
   * Initialize a new widget.
   *
   * @param {object} parent
   * @param {object} field
   * @param {object} params
   * @param {function} setValue
   * @returns {_L3.C}
   */
  function C(parent, field, params, setValue) {
    this.field = field;
    this.value = params;
    this.setValue = setValue;
  }

  /**
   * Append widget to the DOM.
   *
   * @param {jQuery} $wrapper
   * @returns {undefined}
   */
  C.prototype.appendTo = function ($wrapper) {
    var that = this;

    this.$item = E.$(this.createHtml()).appendTo($wrapper);
    this.$select = this.$item.find('select');
    this.$errors = this.$item.children('.h5p-errors');

    this.$select.change(function () {
      var val = that.validate();
      if (val !== false) {
        that.value = val;
        that.setValue(that.field, val);
      }
    });
  };

  /**
   * Generate HTML for the widget.
   *
   * @returns {String} HTML.
   */
  C.prototype.createHtml = function () {
    if (this.field.optional === true || this.field.default === undefined) {
      var options = E.createOption('-', '-');
    }
    for (var i = 0; i < this.field.options.length; i++) {
      var option = this.field.options[i];
      options += E.createOption(option.value, option.label, option.value === this.value);
    }

    var label = E.createLabel(this.field, '<select>' + options + '</select>');

    return E.createItem(this.field.type, label, this.field.description);
  };


  /**
   * Validate this field.
   *
   * @returns {Boolean}
   */
  C.prototype.validate = function () {
    var value = this.$select.val();
    if (value === '-') {
      value = undefined; // No value selected
    }

    if (this.field.optional !== true && value === undefined) {
      // Not optional and no value selected, print required error
      this.$errors.append(ns.createError(ns.t('core', 'requiredProperty', {':property': ns.t('core', 'textField')})));

      return false;
    }

    // All valid. Remove old errors
    var $errors = this.$errors.children();
    if ($errors.length) {
      $errors.remove();
    }

    return value;
  };


  /**
   * Remove widget from DOM.
   *
   * @returns {undefined}
   */
  C.prototype.remove = function () {
    this.$item.remove();
  };

  return C;
})(H5PEditor);
