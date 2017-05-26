<?php

/**
 * @file
 * Fivestar field formatter specific code for schema.org.
 */

function schemaorg_contrib_field_preprocess_fivestar(&$variables) {
  $element = $variables['element'];

  foreach ($element['#items'] as $delta => $item) {
    // Add typeof attribute to the field item wrapper.
    $variables['item_attributes_array'][$delta]['typeof'] = 'schema:AggregateRating';
    // Generate RDFa markup for the vote average and count.
    $metadata_markup = '';
    if (!empty($element['#items'][$delta]['average'])) {
      $average = round(($element['#items'][$delta]['average']/100) * 5, 1);
      $metadata_markup .= '<meta property="schema:ratingValue" content="' . $average . '"/>';
    }
    if (!empty($element['#items'][$delta]['count'])) {
      $metadata_markup .= '<meta property="schema:ratingCount" content="' . $element['#items'][$delta]['count'] . '"/>';
    }
    // Insert markup after fivestar summary.
    if ($metadata_markup) {
      // The render array can differ depending on the field formatter settings,
      // such as for example whether users can vote while viewing (form).
      if (!empty($variables['items'][$delta]['average']['#description'])) {
        $variables['items'][$delta]['average']['#description'] .= $metadata_markup;
      }
      elseif (!empty($variables['items'][$delta]['vote']['vote']['#description'])) {
        $variables['items'][$delta]['vote']['vote']['#description'] .= $metadata_markup;
      }
    }
  }
}
