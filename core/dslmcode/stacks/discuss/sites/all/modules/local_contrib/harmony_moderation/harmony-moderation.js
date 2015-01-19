/**
 * @file
 * JavaScript for the custom replace with command without wrapper.
 */

(function ($) {
  // This is a duplicate of Drupal.ajax.prototype.commands.insert. Comments
  // have been removed but are present in core misc/ajax.js.
  Drupal.ajax.prototype.commands.insertNoWrapper = function(ajax, response, status) {
    var wrapper = response.selector ? $(response.selector) : $(ajax.wrapper);
    var method = response.method || ajax.method;
    var effect = ajax.getEffect(response);

    // The line that follows is the only change.
    var new_content_wrapped = $(response.data);
    var new_content = new_content_wrapped.contents();

    if (new_content.length != 1 || new_content.get(0).nodeType != 1) {
      new_content = new_content_wrapped;
    }

    switch (method) {
      case 'html':
      case 'replaceWith':
      case 'replaceAll':
      case 'empty':
      case 'remove':
        var settings = response.settings || ajax.settings || Drupal.settings;
        Drupal.detachBehaviors(wrapper, settings);
    }

    wrapper[method](new_content);

    if (effect.showEffect != 'show') {
      new_content.hide();
    }

    if ($('.ajax-new-content', new_content).length > 0) {
      $('.ajax-new-content', new_content).hide();
      new_content.show();
      $('.ajax-new-content', new_content)[effect.showEffect](effect.showSpeed);
    }
    else if (effect.showEffect != 'show') {
      new_content[effect.showEffect](effect.showSpeed);
    }

    if (new_content.parents('html').length > 0) {
      var settings = response.settings || ajax.settings || Drupal.settings;
      Drupal.attachBehaviors(new_content, settings);
    }
  };
})(jQuery);
