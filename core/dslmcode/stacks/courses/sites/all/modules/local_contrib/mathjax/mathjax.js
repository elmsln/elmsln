/**
 * @file
 * JavaScript file for the MathJax module.
 */

/**
 * Typeset MathJax if ajax executes.
 */
Drupal.behaviors.mathjaxBehavior = {
  attach: function (context, settings) {
    jQuery(document).ajaxComplete(function() {
      MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
    });
  }
};
