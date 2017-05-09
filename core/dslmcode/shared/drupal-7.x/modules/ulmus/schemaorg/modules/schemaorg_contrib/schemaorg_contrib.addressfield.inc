<?php

/**
 * @file
 * Addressfield field formatter specific code for schema.org.
 */

function schemaorg_contrib_field_preprocess_addressfield(&$variables) {
  $element = $variables['element'];

  foreach ($element['#items'] as $delta => $item) {
    // Add typeof attribute to the field item wrapper.
    $variables['item_attributes_array'][$delta]['typeof'] = 'schema:PostalAddress';
    // Inject property RDFa attribute on each element of the address field
    // formatter output.
    _schemaorg_contrib_addressfield_add_attributes($variables['items'][$delta], $element['#items'][$delta]);
  }
}

/**
 * Helper function to recursively inject RDFa attributes in an address item.
 */
function _schemaorg_contrib_addressfield_add_attributes(&$address, $values) {
  // Define schema.org mappings which will be injected in the addressfield
  // formatter output.
  static $mappings = array(
    'thoroughfare' => 'schema:streetAddress',
    // 'premise' => // not defined on schema.org
    'postal_code' => 'schema:postalCode',
    'locality' => 'schema:addressLocality',
    'administrative_area' => 'schema:addressRegion',
    'country' => 'schema:addressCountry',
  );

  foreach (element_children($address) as $key) {
    $child = &$address[$key];
    // Automatically add RDFa property attribute to each address element.
    if (in_array($key, array_keys($mappings), TRUE)) {
      $child['#attributes']['property'][] = $mappings[$key];
      // Use ISO country code as country value.
      if ($key == 'country' && $values['country']) {
        $child['#attributes']['content'] = $values['country'];
      }
    }

    // Recurse through the child.
    _schemaorg_contrib_addressfield_add_attributes($child, $values);
  }
}
