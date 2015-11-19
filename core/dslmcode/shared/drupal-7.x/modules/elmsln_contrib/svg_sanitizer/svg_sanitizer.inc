<?php

/**
 * Class SvgSanitizerAttributes
 *
 * Add custom attributes to the list of allowed attributes.
 */
class SvgSanitizerAttributes implements enshrined\svgSanitize\data\AttributeInterface {
  /**
   * Returns an array of attributes
   *
   * @return array
   */
  public static function getAttributes() {
    $allowed = enshrined\svgSanitize\data\AllowedAttributes::getAttributes();
    $custom_attributes = variable_get('svg_sanitizer_allowedattrs', NULL);

    foreach ($custom_attributes as $attribute) {
      array_push($allowed, $attribute);
    }

    return $allowed;
  }
}