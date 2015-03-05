<?php
/**
 * @file
 * Hooks provided by the Fences module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Provide theme hook suggestions for various theme hooks.
 *
 * @return array
 *   A nested array containing information about the theme hook suggestions
 *   provided by the implementing module.
 */
function hook_fences_suggestion_info() {
  // The suggestions for the "field" theme hook.
  $fences['field'] = array(
    // This key will be appended to THEMEHOOK__fences_ to make the theme hook
    // suggestion, field__fences_p in this case. The corresponding template
    // files should be have all underscores changed to dashes and be named
    // field--fences-p.tpl.php and field--fences-p-multiple.tpl.php.
    'p' => array(
      // The label used in the UI when selecting a suggestion. The label must
      // only contain English words to enable multilingual translations.
      'label' => t('paragraph'),
      // The HTML element(s) used by the suggestion. This will be added to the
      // label in the UI to provide additional context. If multiple elements are
      // used they should be seperated by spaces, e.g. 'pre code'.
      'element' => 'p',
      // A short description used in the UI when selecting a suggestion.
      'description' => t('A paragraph; multiple values are each wrapped in a <p>'),
      // An array of groups to place the element into.
      'groups' => array(t('Block-level')),
    ),
  );
  return $fences;
}

/**
 * Alter the theme hook suggestions used by the fences module.
 *
 * @param $fences
 *   An array containing the data returned by hook_fences_suggestion_info().
 */
function hook_fences_suggestion_info_alter(&$fences) {
}

/**
 * @} End of "addtogroup hooks".
 */
