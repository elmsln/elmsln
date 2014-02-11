
(function($) {

/**
 * Highlight words in search results with jQuery.
 */
Drupal.behaviors.DSSearchHighlight = {
  attach: function (context) {
    var selector = Drupal.settings.ds_search['selector'];
    var search = Drupal.settings.ds_search['search'];
    var $selector = $(selector);
    // Split word.

    words = search.split(' ');
    for (i = 0; i < words.length; i++) {
      // Match only valid words. Do not match special search operators or words less than three characters.
      if (words[i] != '' && words[i] != 'AND' && words[i] != 'OR' && words[i].length >= 3) {
        $selector.highlight(words[i]);
      }
    }
  }
};

/*

highlight v3

Highlights arbitrary terms.

<http://johannburkard.de/blog/programming/javascript/highlight-javascript-text-higlighting-jquery-plugin.html>

MIT license.

Johann Burkard
<http://johannburkard.de>
<mailto:jb@eaio.com>

*/

jQuery.fn.highlight = function(pat) {
 function innerHighlight(node, pat) {
  var skip = 0;
  if (node.nodeType == 3) {
   var pos = node.data.toUpperCase().indexOf(pat);
   if (pos >= 0) {
    var spannode = document.createElement('span');
    spannode.className = 'ds-search-highlight';
    var middlebit = node.splitText(pos);
    var endbit = middlebit.splitText(pat.length);
    var middleclone = middlebit.cloneNode(true);
    spannode.appendChild(middleclone);
    middlebit.parentNode.replaceChild(spannode, middlebit);
    skip = 1;
   }
  }
  else if (node.nodeType == 1 && node.childNodes && !/(script|style)/i.test(node.tagName)) {
   for (var i = 0; i < node.childNodes.length; ++i) {
    i += innerHighlight(node.childNodes[i], pat);
   }
  }
  return skip;
 }
 return this.each(function() {
  innerHighlight(this, pat.toUpperCase());
 });
};

})(jQuery);

