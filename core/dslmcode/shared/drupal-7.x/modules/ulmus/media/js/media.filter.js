/**
 *  @file
 *  File with utilities to handle media in html editing.
 */
(function ($) {

  Drupal.media = Drupal.media || {};
  /**
   * Utility to deal with media tokens / placeholders.
   */
  Drupal.media.filter = {
    /**
     * Replaces media tokens with the placeholders for html editing.
     * @param content
     */
    replaceTokenWithPlaceholder: function(content) {
      var tagmap = Drupal.media.filter.ensure_tagmap(),
        matches = content.match(/\[\[.*?\]\]/g),
        media_definition,
        id = 0;

      if (matches) {
        var i = 1;
        for (var macro in tagmap) {
          var index = $.inArray(macro, matches);
          if (index !== -1) {
            var media_json = macro.replace('[[', '').replace(']]', '');

            // Make sure that the media JSON is valid.
            try {
              media_definition = JSON.parse(media_json);
            }
            catch (err) {
              media_definition = null;
            }
            if (media_definition) {
              // Apply attributes.
              var element = Drupal.media.filter.create_element(tagmap[macro], media_definition);
              var markup = Drupal.media.filter.outerHTML(element);

              content = content.replace(macro, Drupal.media.filter.getWrapperStart(i) + markup + Drupal.media.filter.getWrapperEnd(i));
            }
          }
          i++;
        }
      }
      return content;
    },

    /**
     * Replaces the placeholders for html editing with the media tokens to store.
     * @param content
     */
    replacePlaceholderWithToken: function(content) {
      var tagmap = Drupal.media.filter.ensure_tagmap();
      var i = 1;
      for (var macro in tagmap) {
        var startTag = Drupal.media.filter.getWrapperStart(i), endTag = Drupal.media.filter.getWrapperEnd(i);
        var startPos = content.indexOf(startTag), endPos = content.indexOf(endTag);
        if (startPos !== -1 && endPos !== -1) {
          // If the placeholder wrappers are empty, remove the macro too.
          if (endPos - startPos - startTag.length === 0) {
            macro = '';
          }
          content = content.substr(0, startPos) + macro + content.substr(endPos + (new String(endTag)).length);
        }
        i++;
      }
      return content;
    },

    getWrapperStart: function(i) {
      return '<!--MEDIA-WRAPPER-START-' + i + '-->';
    },

    getWrapperEnd: function(i) {
      return '<!--MEDIA-WRAPPER-END-' + i + '-->';
    },

    /**
     * Register new element and returns the placeholder markup.
     *
     * @param formattedMedia a formatted media object as given by the onSubmit
     * function of the media Style popup.
     * @param fid the file id.
     *
     * @return The registered element.
     */
    registerNewElement: function (formattedMedia, fid) {
      var element = Drupal.media.filter.create_element(formattedMedia.html, {
        fid: fid,
        view_mode: formattedMedia.type,
        attributes: formattedMedia.options
      });

      var markup = Drupal.media.filter.outerHTML(element),
        macro = Drupal.media.filter.create_macro(element);

      // Store macro/markup pair in the tagmap.
      Drupal.media.filter.ensure_tagmap();
      Drupal.settings.tagmap[macro] = markup;

      return element;
    },

    /**
     * Serializes file information as a url-encoded JSON object and stores it as a
     * data attribute on the html element.
     *
     * @param html (string)
     *    A html element to be used to represent the inserted media element.
     * @param info (object)
     *    A object containing the media file information (fid, view_mode, etc).
     */
    create_element: function (html, info) {
      if ($('<div></div>').append(html).text().length === html.length) {
        // Element is not an html tag. Surround it in a span element
        // so we can pass the file attributes.
        html = '<span>' + html + '</span>';
      }
      var element = $(html);

      // Move attributes from the file info array to the placeholder element.
      if (info.attributes) {
        $.each(Drupal.media.filter.allowed_attributes(), function(i, a) {
          if (info.attributes[a]) {
            element.attr(a, info.attributes[a]);
          }
        });
        delete(info.attributes);
      }

      // Important to url-encode the file information as it is being stored in an
      // html data attribute.
      info.type = info.type || "media";
      element.attr('data-file_info', encodeURI(JSON.stringify(info)));

      // Adding media-element class so we can find markup element later.
      var classes = ['media-element'];

      if(info.view_mode){
        classes.push('file-' + info.view_mode.replace(/_/g, '-'));
      }
      element.addClass(classes.join(' '));

      return element;
    },

    /**
     * Create a macro representation of the inserted media element.
     *
     * @param element (jQuery object)
     *    A media element with attached serialized file info.
     */
    create_macro: function (element) {
      var file_info = Drupal.media.filter.extract_file_info(element);
      if (file_info) {
        return '[[' + JSON.stringify(file_info) + ']]';
      }
      return false;
    },

    /**
     * Extract the file info from a WYSIWYG placeholder element as JSON.
     *
     * @param element (jQuery object)
     *    A media element with attached serialized file info.
     */
    extract_file_info: function (element) {
      var file_json = $.data(element, 'file_info') || element.data('file_info'),
        file_info,
        value;

      try {
        file_info = JSON.parse(decodeURIComponent(file_json));
      }
      catch (err) {
        file_info = null;
      }

      if (file_info) {
        file_info.attributes = {};

        // Extract whitelisted attributes.
        $.each(Drupal.media.filter.allowed_attributes(), function(i, a) {
          if (value = element.attr(a)) {
            file_info.attributes[a] = value;
          }
        });
        delete(file_info.attributes['data-file_info']);
      }

      return file_info;
    },

    /**
     * Gets the HTML content of an element.
     *
     * @param element (jQuery object)
     */
    outerHTML: function (element) {
      return $('<div>').append(element.eq(0).clone()).html();
    },

    /**
     * Gets the wrapped HTML content of an element to insert into the wysiwyg.
     *
     * It also registers the element in the tag map so that the token
     * replacement works.
     *
     * @param element (jQuery object) The element to insert.
     *
     * @see Drupal.media.filter.replacePlaceholderWithToken()
     */
    getWysiwygHTML: function (element) {
      // Create the markup and the macro.
      var markup = Drupal.media.filter.outerHTML(element),
        macro = Drupal.media.filter.create_macro(element);

      // Store macro/markup in the tagmap.
      Drupal.media.filter.ensure_tagmap();
      var i = 1;
      for (var key in Drupal.settings.tagmap) {
        i++;
      }
      Drupal.settings.tagmap[macro] = markup;

      // Return the wrapped html code to insert in an editor and use it with
      // replacePlaceholderWithToken()
      return Drupal.media.filter.getWrapperStart(i) + markup + Drupal.media.filter.getWrapperEnd(i);
    },

    /**
     * Ensures the tag map has been initialized and returns it.
     */
    ensure_tagmap: function () {
      Drupal.settings.tagmap = Drupal.settings.tagmap || {};
      return Drupal.settings.tagmap;
    },

    /**
     * Ensures the wysiwyg_allowed_attributes and returns it.
     * In case of an error the default settings are returned.
     */
    allowed_attributes: function () {
      Drupal.settings.wysiwyg_allowed_attributes = Drupal.settings.wysiwyg_allowed_attributes || ['height', 'width', 'hspace', 'vspace', 'border', 'align', 'style', 'alt', 'title', 'class', 'id', 'usemap'];
      return Drupal.settings.wysiwyg_allowed_attributes;
    }
  }
})(jQuery);
