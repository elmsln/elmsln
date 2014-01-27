<?php

/**
 * @file
 * Hooks provided by the Coder module.
 */

/**
 * General description of arrays used by coder_review:
 *
 * Each Review array is keyed by the name of code review, e.g., 'production',
 * 'comment', 'security', etc.  The value for each key is another associative
 * array, which is required to have the following keys:
 * - #title:
 * - #link:
 * - #rules: An array of one or more Rule arrays, as defined below.
 * - #version:
 * - #image:
 * - #description:
 * - #file:

 *
 * Each Rule array must have the following keys:
 * - #type: (required) A string that describes the type of coder check. Possible
 *     values include:
 *     - callback:
 *       @todo Where do we document the form of the function for #type callback?
 *     - grep:
 *     - grep_invert:
 *     - regex:
 * - #value: (required) A string that varies depending on the value of #type. If
 *     the #type is:
 *     - callback: This string will be interpreted as the name of the callback
 *       function to be called.
 *     - regex: This string will be used in the regex evaluation.
 *
 * In addition, each rule can optionally also have the following keys:
 * - #function: (optional)
 * - #never: (optional)
 * - #not: (optional)
 * - #severity: (optional) A string representing the severity level.  Possible
 *     values include: 'critical', 'normal' and 'minor'.
 * - #source: (required) A string like 'all', 'allphp', and 'quote'.
 *     @todo: Where in the code is this string checked for validity?
 * - #warning: (optional) Can be either be a callback (e.g., foo_callback()),
 *     or an array with the following keys:
 *     - #text: (required)
 *     - #args: (required)
 *     - #link: (optional)
 *
 * A Results array is an associative array ...
 *
 */

/**
 * Perform a custom review on a module or a theme.
 *
 * This hook allows a module to implement its own custom code review(s). This is
 * accomplished by specifying a Coder settings array that consists of one or
 * more Review arrays, which in turn may contain one or more Rule arrays.
 *
 * @return array
 *   A Coder settings array with information about the reviews and rules
 *   provided by the module that implements this hook.
 */
function hook_reviews() {
  $review = array(
  );
  return $review;
}
