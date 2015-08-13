/**
 * Above the Fold CSS parser
 *
 * Based on criticalcss-bookmarklet-devtool-snippet.js by Paul Kinlan
 * @see https://gist.github.com/PaulKinlan/6284142
 *
 * Part of the critical-css project
 * @see https://github.com/attila/critical-css
 */
;(function(root) {
  'use strict';

  /**
   * CSS Critical Path constructor function.
   *
   * @param Object w    The global window object in the browser.
   * @param Object d    The document object in the browser.
   * @param Object opts Options for parsing:
   *   - excludeSelectors: An array of strings which are used as patterns to
   *     exclude matching style rules from the resulting stylesheet. Defaults to
   *     an empty array.
   *   - enabledOrigins: An array of strings representing host names used to
   *     exclude external stylesheets originating from. This only works if run
   *     in PhantomJS or a similar headless browser where cross origin related
   *     security limitations can be lifted. Defaults to an empty array.
   *   - keepInlineStyles: Boolean value determining if style rules originating
   *     from non-external stylesheets should be included. These rules mostly
   *     originate from inline styles or style attributes added by JavaScript.
   *     Defaults to false.
   * @constructor
   */
  var CSSCriticalPath = function(w, d, opts) {
    if (typeof w.getMatchedCSSRules !== 'function') {
      throw new Error('Browser is incompatible');
    }

    var opt = opts || {};
    var css = {};

    var pushCSS = function(r) {
      if (!css[r.selectorText]) {
        css[r.selectorText] = {};
      }

      var styles = r.style.cssText.split(/;(?![A-Za-z0-9])/);
      for (var i = 0; i < styles.length; i++) {
        if (!styles[i].trim()) {
          continue;
        }
        var pair = styles[i].split(': ');
        pair[0] = pair[0].trim();
        pair[1] = pair[1].trim();
        css[r.selectorText][pair[0]] = pair[1];
      }
    };

    /**
     * Parse the DOM tree and process all matching CSS rules on each Above the
     * Fold element.
     * @return {[type]} [description]
     */
    var parseTree = function() {
      // Get a list of all the elements in the view.
      var height = w.innerHeight;
      var walker = d.createTreeWalker(d, w.NodeFilter.SHOW_ELEMENT, function() {
        return w.NodeFilter.FILTER_ACCEPT;
      }, true);

      while (walker.nextNode()) {
        var node = walker.currentNode;
        var rect = node.getBoundingClientRect();
        if (rect.top < height || opt.scanFullPage) {
          var rules = [];

          // Add matching element rules.
          rules.push.apply(rules, ruleListToArray(w.getMatchedCSSRules(node)));

          // Going forward, add pseudo-element rules too.
          rules.push.apply(rules, ruleListToArray(w.getMatchedCSSRules(node, 'before')));
          rules.push.apply(rules, ruleListToArray(w.getMatchedCSSRules(node, 'after')));

          // Do not include if the style is not from an external stylesheet.
          // This means that the rule is either inline already or inlined by JS.
          if (!opt.keepInlineStyles && rules.length > 0) {
            rules = rules.filter(function(e) {
              return (e.parentStyleSheet && e.parentStyleSheet.href);
            });
          }

          // Only include CSS originating from whitelisted host names. This only
          // works from phantomjs as security can be disabled in there.
          if (opt.enabledOrigins instanceof Array && opt.enabledOrigins.length > 0) {
            rules = rules.filter(function(e) {
              var out = false, re;
              opt.enabledOrigins.forEach(function(v) {
                re = new RegExp('^(https?:)?\/\/' + escapeRegExp(v) + '\/', 'i');
                if (!e.parentStyleSheet || !e.parentStyleSheet.href || e.parentStyleSheet.href.match(re)) {
                  out = true;
                }
              });
              return out;
            });
          }

          // Do not include blacklisted selectors.
          if (opt.excludeSelectors) {
            rules = rules.filter(function(e) {
              var out = true, re;
              opt.excludeSelectors.forEach(function(v) {
                re = new RegExp(escapeRegExp(v), 'i');
                if (e.selectorText.match(re)) {
                  out = false;
                }
              });
              return out;
            });
          }

          if (!!rules) {
            for (var r = 0; r < rules.length; r++) {
              pushCSS(rules[r]);
            }
          }
        }
      }
    };

    /**
     * Convert CSSRuleList objects to Arrays to ensure backwards compatibility.
     *
     * @param  Object ruleset A CSSRuleList object.
     * @return Array          An array with CSSRuleList
     */
    var ruleListToArray = function(ruleset) {
      if (!ruleset || !ruleset.item) {
        return;
      }
      var ruleList = [];
      for (var i = 0; i < ruleset.length; i++) {
        ruleList.push(ruleset.item(i));
      }

      return ruleList;
    };

    /**
     * Escape characters in a string which translate to regular expression
     * modifiers.
     *
     * @param  String str The string to escape characters in
     * @return String     The processed string which can be safely used in
     *   regular expressions as patterns.
     */
    var escapeRegExp = function(str) {
      return str.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, '\\$&');
    };

    this.generateCSS = function() {
      var finalCSS = '';
      for (var k in css) {
        finalCSS += k + ' { ';
        for (var j in css[k]) {
          finalCSS += j + ': ' + css[k][j] + '; ';
        }
        finalCSS += '}\u000A';
      }

      return finalCSS;
    };

    parseTree();
  };

  root.CSSCriticalPath = CSSCriticalPath;

}(this));
