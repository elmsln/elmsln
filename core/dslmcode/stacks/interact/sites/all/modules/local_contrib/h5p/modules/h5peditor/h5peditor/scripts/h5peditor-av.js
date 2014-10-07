var H5PEditor = H5PEditor || {};

/**
 * Audio/Video module.
 * Makes it possible to add audio or video through file uploads and urls.
 *
 */
H5PEditor.widgets.video = H5PEditor.widgets.audio = H5PEditor.AV = (function ($) {

  /**
   * Constructor.
   *
   * @param {mixed} parent
   * @param {object} field
   * @param {mixed} params
   * @param {function} setValue
   * @returns {_L3.C}
   */
  function C(parent, field, params, setValue) {
    this.parent = parent;
    this.field = field;
    this.params = params;
    this.setValue = setValue;
    this.changes = [];
    
    if (params !== undefined && params[0] !== undefined) {
      this.setCopyright(params[0].copyright);
    }
  }

  /**
   * Append widget to given wrapper.
   *
   * @param {jQuery} $wrapper
   */
  C.prototype.appendTo = function ($wrapper) {
    var self = this;

    // Add iframe for uploads.
    H5PEditor.File.addIframe();

    var label = '';
    if (this.field.label !== 0) {
      label = '<span class="h5peditor-label">' + (this.field.label === undefined ? this.field.name : this.field.label) + '</span>';
    }

    var html = H5PEditor.createItem(this.field.type, label + '<div class="file">' + C.createAdd() + '</div><a class="h5p-copyright-button" href="#">' + ns.t('core', 'editCopyright') + '</a><div class="h5p-editor-dialog"><a href="#" class="h5p-close" title="' + ns.t('core', 'close') + '"></a></div>', this.field.description);

    var $container = $(html).appendTo($wrapper);
    var $file = $container.children('.file');
    this.$add = $file.children('.add').click(function () {
      self.uploadFile();
      return false;
    });
    this.$errors = $container.children('.h5p-errors');

    if (this.params !== undefined) {
      for (var i = 0; i < this.params.length; i++) {
        this.addFile(i);
      }
    }
    
    var $dialog = $container.find('.h5p-editor-dialog');
    $container.find('.h5p-copyright-button').add($dialog.find('.h5p-close')).click(function () {
      $dialog.toggleClass('h5p-open');
      return false;
    });
  
    var group = new H5PEditor.widgets.group(self, H5PEditor.copyrightSemantics, self.copyright, function (field, value) {
      self.setCopyright(value);
    });
    group.appendTo($dialog);
    group.expand();
    group.$group.find('.title').remove();
    this.children = [group];
  };

  /**
   * Add file icon with actions.
   *
   * @param {Number} index
   */
  C.prototype.addFile = function (index) {
    var that = this;

    var file = this.params[index];
    var mimeParts = file.mime.split('/');
    var $file = $('<div class="thumbnail"><div class="type" title="' + file.mime + '">' + mimeParts[1] + '</div><a href="#" class="remove" title="' + H5PEditor.t('core', 'removeFile') + '"></a></div>')
      .insertBefore(this.$add)
      .children('.remove')
        .click(function () {
          if (!confirm(H5PEditor.t('core', 'confirmRemoval', {':type': 'file'}))) {
            return false;
          }

          // Remove from params.
          if (that.params.length === 1) {
            delete that.params;
            that.setValue(that.field);
          }
          else {
            that.params.splice(index, 1);
          }

          $file.remove();

          for (var i = 0; i < that.changes.length; i++) {
            that.changes[i]();
          }

          return false;
        })
        .end();
  };

  /**
   * Start a new upload.
   *
   * @returns {unresolved}
   */
  C.prototype.uploadFile = function () {
    var that = this;

    if (H5PEditor.File.$file === 0) {
      return; // Wait for our turn :)
    }

    this.$errors.html('');

    H5PEditor.File.changeCallback = function () {
      that.$uploading = $('<div class="h5peditor-uploading h5p-throbber">' + H5PEditor.t('core', 'uploading') + '</div>').insertAfter(that.$add.hide());
    };

    H5PEditor.File.callback = function (json) {
      try {
        var result = JSON.parse(json);
        if (result['error'] !== undefined) {
          throw(result['error']);
        }

        if (that.params === undefined) {
          that.params = [];
          that.setValue(that.field, that.params);
        }

        var file = {
          path: result.path,
          mime: result.mime,
          copyright: that.copyright
        };
        that.params.push(file);

        that.addFile(that.params.length - 1);

        for (var i = 0; i < that.changes.length; i++) {
          that.changes[i](file);
        }
      }
      catch (error) {
        that.$errors.append(H5PEditor.createError(error));
      }

      if (that.$uploading !== undefined && that.$uploading.length !== 0) {
        that.$uploading.remove();
        that.$add.show();
      }
    };

    if (this.field.mimes !== undefined) {
      var mimes = '';
      for (var i = 0; i < this.field.mimes.length; i++) {
        if (mimes !== '') {
          mimes += ',';
        }
        mimes += this.field.mimes[i];
      }
      H5PEditor.File.$file.attr('accept', mimes);
    }
    else if (this.field.type === 'audio') {
      H5PEditor.File.$file.attr('accept', 'audio/mpeg,audio/x-wav,audio/ogg');
    }
    else if (this.field.type === 'video') {
      H5PEditor.File.$file.attr('accept', 'video/mp4,video/webm,video/ogg');
    }

    H5PEditor.File.$field.val(JSON.stringify(this.field));
    H5PEditor.File.$file.click();
  };

  /**
   * Validate the field/widget.
   *
   * @returns {Boolean}
   */
  C.prototype.validate = function () {
    return true;
  };

  /**
   * Remove this field/widget.
   */
  C.prototype.remove = function () {
    // TODO: Check what happens when removed during upload.
    this.$errors.parent().remove();
  };
  
  /**
   * Sync copyright between all video files.
   *
   * @returns {undefined}
   */
  C.prototype.setCopyright = function (value) {
    this.copyright = value;
    if (this.params !== undefined) {
      for (var i = 0; i < this.params.length; i++) {
        this.params[i].copyright = value;
      }
    }
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
      ready();
    }
  };

  /**
   * HTML for add button.
   *
   * @returns {String}
   */
  C.createAdd = function () {
    return '<a href="#" class="add" title="' + H5PEditor.t('core', 'addFile') + '"></a>';
  };

  return C;
})(H5P.jQuery);
