// DEPRECATED: This widget will be removed and replaced with the HTML widget
var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Create a text field for the form.
 *
 * @param {mixed} parent
 * @param {Object} field
 * @param {mixed} params
 * @param {function} setValue
 * @returns {ns.Textarea}
 */
ns.Textarea = function (parent, field, params, setValue) {
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
ns.Textarea.prototype.appendTo = function ($wrapper) {
  var that = this;

  this.$item = ns.$(this.createHtml()).appendTo($wrapper);
  this.$input = this.$item.children('label').children('textarea');
  this.$errors = this.$item.children('.h5p-errors');

  this.$input.change(function () {
    // Validate
    var value = that.validate();

    if (value !== false) {
      // Set param
      that.setValue(that.field, ns.htmlspecialchars(value));
    }
  });
};

/**
 * Create HTML for the text field.
 */
ns.Textarea.prototype.createHtml = function () {
  var input = '<textarea cols="30" rows="4"';
  if (this.field.placeholder !== undefined) {
    input += ' placeholder="' + this.field.placeholder + '"';
  }
  input += '>';
  if (this.value !== undefined) {
    input += this.value;
  }
  input += '</textarea>';

  var label = ns.createLabel(this.field, input);

  return ns.createItem(this.field.type, label, this.field.description);
};

/**
 * Validate the current text field.
 */
ns.Textarea.prototype.validate = function () {
  var value = H5P.trim(this.$input.val());

  if ((this.field.optional === undefined || !this.field.optional) && !value.length) {
    this.$errors.append(ns.createError(ns.t('core', 'requiredProperty', {':property': 'text field'})));
  }
  else if (value.length > this.field.maxLength) {
    this.$errors.append(ns.createError(ns.t('core', 'tooLong', {':max': this.field.maxLength})));
  }
  else if (this.field.regexp !== undefined && !value.match(new RegExp(this.field.regexp.pattern, this.field.regexp.modifiers))) {
    this.$errors.append(ns.createError(ns.t('core', 'invalidFormat')));
  }

  return ns.checkErrors(this.$errors, this.$input, value);
};

/**
 * Remove this item.
 */
ns.Textarea.prototype.remove = function () {
  this.$item.remove();
};

// Tell the editor what semantic field we are.
ns.widgets.textarea = ns.Textarea;