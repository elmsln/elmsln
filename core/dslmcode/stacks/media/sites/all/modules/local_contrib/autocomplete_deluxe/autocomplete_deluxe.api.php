<?php

/**
 * @file
 * This contains documentation only.
 */

/**
 * Using the Autocomplete Deluxe element.
 *
 * When you want to use the Autocomplete Deluxe element, you have to specify
 * an Ajax Callback as the source for the suggestion data:
 * - #autocomplete_deluxe_path expects a string with a url that points to the
 *   ajax callback. The response should be encoded as json (like for the core
 *   autocomplete).
 *
 * Besides this, there are four other options which autocomplete deluxe
 * accepts:
 * - #multiple Indicates whether the user may select more than one item. Expects
 *   TRUE or FALSE, by default it is set to FALSE.
 * - #min_length Indicates how many characters must be entered
 *   until, the suggesion list can be opened. Especially helpful, when your
 *   ajax callback returns only valid suggestion for a minimum characters.
 *   The default is 0.
 * - #delimiter If #multiple is TRUE, then you can use this option to set a
 *   seperator for multiple values. By default a string with the following
 *   content will be used: ', '.
 * - #not_found_message The message text which will be displayed if the entered
 *   term was not found.
 */
function somefunction() {
  $element = array(
    '#type' => 'autocomplete_deluxe',
    '#autocomplete_deluxe_path' => url('some_uri', array('absolute' => TRUE)),
    '#multiple' => TRUE,
    '#min_length' => 1,
    '#delimiter' => '|',
    '#not_found_message' => "The term '@term' will be added.",
  );
}
