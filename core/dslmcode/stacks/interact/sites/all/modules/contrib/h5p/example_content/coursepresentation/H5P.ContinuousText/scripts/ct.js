var H5P = H5P || {};

/**
 * Constructor.
 *
 * @param {object} params Options for this library.
 * @param {int} id Content identifier
 */
H5P.ContinuousText = function (params, id) {
  this.text = params.text === undefined ? '<div class="ct"><em>New text</em></div>' : '<div class="ct">'+params.text+'</div>';
};

/**
 * Wipe out the content of the wrapper and put our HTML in it.
 *
 * @param {jQuery} $wrapper
 */
H5P.ContinuousText.prototype.attach = function ($wrapper) {
  $wrapper.addClass('h5p-ct').html(this.text);
};

H5P.ContinuousText.Engine = (function() {

  // Fit nodes from $document into $target while preventing $target from
  // overflowing $container.  Will call itself recursively to add child nodes
  // if the parent node does not fit.
  function fitText($container, $target, $document) {
    var containerBottom = $container.offset().top + $container.innerHeight();
    $document.contents().each(function () {
      var thisBottom, $node, $clone, words,
        i = 0,
        text = "",
        rest = "";

      // Proper DOM node. Attempt to fit.
      if (this.nodeType === 1) {
        $node = H5P.jQuery(this);
        $target.append($node); // Need to append it here to get height calculated by browser.
        thisBottom = $node.offset().top + $node.outerHeight();
        if (thisBottom > containerBottom) {
          // Pull back to the document.
          $clone = $node.clone();
          $document.prepend($clone);
          $node.empty();
          fitText($container, $node, $clone);
          return false;
        }
      } else if (this.nodeType === 3) {
        // Text node. Might need to split.
        $target.append(this);
        // Test if $target overflows.
        thisBottom = $target.offset().top + $target.outerHeight();
        if (thisBottom > containerBottom) {
          words = this.data.split(' ');
          do {
              i++;
              text = words.slice(0, i).join(" ");
              rest = words.slice(i).join(" ");
              this.replaceData(0, this.data.length, text);
              thisBottom = $target.offset().top + $target.outerHeight();
          } while (thisBottom < containerBottom && i < words.length);
          // Need to backtrack one word.
          text = words.slice(0, i-1).join(" ");
          rest = words.slice(i-1).join(" ");
          this.replaceData(0, this.data.length, text);
          $document.prepend(rest);

          return false;
        }
      } else {
        // Ignore. Probably a comment.
      }
    });
  }

  return {
    run: function (cpEditor) {
      
      // If there are no CT-elements, this functions 
      // does not need to run. Also, if we let it run, there will
      // be some undefined-errors in the console.
      if(cpEditor.ct === undefined) {
        return;
      }
      
      var slides = cpEditor.params,
        wrappers = cpEditor.ct.wrappers,
        content = cpEditor.params[0].ct,
        $temporaryDocument = H5P.jQuery('<div/>').html(content),
        ctElements = [];

      // Find all ct elements.
      H5P.jQuery.each(slides, function(slideIdx, slide){
        ctElements = ctElements.concat(slide.elements.filter(function (element) {
          return element.action.library.split('.')[1].split(' ')[0] === 'ContinuousText';
        }));
      });
      // TODO: This is heavy, consider using a single for loop instead.

      H5P.jQuery.each(ctElements, function (idx, element) {
        var $container = wrappers[element.index],
          $elementClone = $container.clone(),
          $innerContainer = $elementClone.find('.ct');

        $elementClone.appendTo(cpEditor.cp.$current);

        // Remaining blocks in the temporary document.
        var $blocks = $temporaryDocument.children();
        if ($blocks.length === 0) {
          $container.addClass('no-more-content');
          $container.find('.ct').html('<em>No more content</em>');
          element.action.params.text = '';
        }
        else {
          $innerContainer.html('');
          fitText($elementClone, $innerContainer, $temporaryDocument);

          // Store data on element
          element.action.params.text = $innerContainer.html();
          $container.find('.ct').html(element.action.params.text);
        }
        // Cleanup
        $elementClone.remove();
      });
      // Cleanup Temporary document.
      $temporaryDocument.remove();
    }
  };
})();
