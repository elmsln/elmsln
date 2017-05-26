var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Create a number picker field for the form.
 *
 * @param {mixed} parent
 * @param {Object} field
 * @param {mixed} params
 * @param {function} setValue
 * @returns {ns.Number}
 */
ns.Number = function (parent, field, params, setValue) {
  this.field = field;
  this.value = params;
  this.setValue = setValue;
};

/**
 * Append field to wrapper.
 *
 * @param {jQuery} $wrapper
 * @returns {undefined}
 */
ns.Number.prototype.appendTo = function ($wrapper) {
  var that = this;

  this.$item = ns.$(this.createHtml()).appendTo($wrapper);
  this.$errors = this.$item.find('.h5p-errors');
  var $inputs = this.$item.find('input');
  if ($inputs.length === 1) {
    this.$input = $inputs;
  }
  else {
    this.$range = $inputs.filter(':first');
    this.$input = this.$range.next();
  }

  this.$input.change(function () {
    // Validate
    var value = that.validate();

    if (value !== false) {
      // Set param
      that.value = value;
      that.setValue(that.field, value);
      if (that.$range !== undefined) {
        that.$range.val(value);
      }
    }
  });

  if (this.$range !== undefined) {
    if (this.$range.attr('type') === 'range') {
      this.$range.change(function () {
        that.$input.val(that.$range.val()).change();
      });

      // Add some styles for IE.
      if (H5PEditor.isIE) {
        this.$range.css('margin-top', 0);
        this.$input.css('margin-top', '7px');
      }
    }
    else {
      this.$range.remove();
    }
  }
};

/**
 * Create HTML for the field.
 */
ns.Number.prototype.createHtml = function () {
  var input = ns.createText(this.value, 15);
  /* TODO: Add back in when FF gets support for input:range....
   *if (this.field.min !== undefined && this.field.max !== undefined && this.field.step !== undefined) {
    input = '<input type="range" min="' + this.field.min + '" max="' + this.field.max + '" step="' + this.field.step + '"' + (this.value === undefined ? '' : ' value="' + this.value + '"') + '/>' + input;
  }
   */

  return ns.createFieldMarkup(this.field, input);
};

/**
 * Validate the current text field.
 */
ns.Number.prototype.validate = function () {
  var that = this;

  var value = H5P.trim(this.$input.val());
  var decimals = this.field.decimals !== undefined && this.field.decimals;

  if (this.$errors.html().length > 0) {
    this.$input.addClass('error');
  }

  // Clear errors before showing new ones
  this.$errors.html('');

  if (!value.length) {
    if (that.field.optional === true) {
      // Field is optional and does not have a value, nothing more to validate
      return;
    }

    // Field must have a value
    this.$errors.append(ns.createError(ns.t('core', 'requiredProperty', {':property': ns.t('core', 'numberField')})));
  }
  else if (decimals && !value.match(new RegExp('^-?[0-9]+(.|,)[0-9]{1,}$'))) {
    this.$errors.append(ns.createError(ns.t('core', 'onlyNumbers', {':property': that.field.label})));
  }
  else if (!decimals && !value.match(new RegExp('^-?[0-9]+$'))) {
    this.$errors.append(ns.createError(ns.t('core', 'onlyNumbers', {':property': that.field.label})));
  }
  else {
    if (decimals) {
      value = parseFloat(value.replace(',', '.'));
    }
    else {
      value = parseInt(value);
    }

    if (this.field.max !== undefined && value > this.field.max) {
      this.$errors.append(ns.createError(ns.t('core', 'exceedsMax', {':property': that.field.label, ':max': this.field.max})));
    }
    else if (this.field.min !== undefined && value < this.field.min) {
      this.$errors.append(ns.createError(ns.t('core', 'belowMin', {':property': that.field.label, ':min': this.field.min})));
    }
    else if (this.field.step !== undefined && value % this.field.step)  {
      this.$errors.append(ns.createError(ns.t('core', 'outOfStep', {':property': that.field.label, ':step': this.field.step})));
    }
  }

  return ns.checkErrors(this.$errors, this.$input, value);
};

/**
 * Remove this item.
 */
ns.Number.prototype.remove = function () {
  this.$item.remove();
};

// Tell the editor what widget we are.
ns.widgets.number = ns.Number;
