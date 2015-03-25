<?php

/**
 * @file
 * Common functions for the WYSIWYG Filter module.
 */

/**
 * Helper function to get information about fields that implement
 * advanced rules.
 *
 * @see wysiwyg_filter_get_filter_options()
 * @see wysiwyg_filter_settings_filter()
 * @see wysiwyg_filter_settings_filter_validate()
 * @see wysiwyg_filter_settings_filter_submit()
 */
function wysiwyg_filter_get_advanced_rules() {
  global $base_url, $base_path;
  return array(
    'valid_classes' => array(
      'title' => t('Rules for Class Names'),
      'description' => t('Enter a comma separated list of rules for <em>Class Names</em>. Whitespaces and line-breaks are ignored. <em>Class Names</em> should start with an upper or lower case letter &quot;a to z&quot; and can be followed by one or more upper or lower case letters &quot;a to z&quot;, digits &quot;0 to 9&quot;, hyphens &quot;-&quot; and/or underscores &quot;_&quot;. The asterisk character &quot;*&quot; can be used in rules to represent any number of characters from the second position of the rule. Example: &quot;userclass*, my-font-*&quot; are valid rules for <em>Class Names</em>, whereas &quot;*class&quot; is invalid.'),
      'validate_regexp' => '`^[a-zA-Z][-_a-zA-Z0-9?*]*$`',
      'asterisk_expansion' => '[-_a-zA-Z0-9]*',
      'required_by' => 'class',
      'required_by_message' => t('The <strong>class</strong> attribute is used in your <em>HTML elements and attributes</em> rules. You should specify the <em>Rules for Class Names</em> field in the &quot;Advanced rules&quot; section below. Leaving it unspecified will result in all class attributes filtered out.'),
    ),
    'valid_ids' => array(
      'title' => t('Rules for Element IDs'),
      'description' => t('Enter a comma separated list of rules for <em>Element IDs</em>. Whitespaces and line-breaks are ignored. <em>Element IDs</em> should start with an upper or lower case letter &quot;a to z&quot; and can be followed by one or more upper or lower case letters &quot;a to z&quot;, digits &quot;0 to 9&quot;, hyphens &quot;-&quot; and/or underscores &quot;_&quot;. The asterisk character &quot;*&quot; can be used in rules to represent any number of characters from the second position of the rule. Example: &quot;foo*&quot; is a valid rule for <em>Element IDs</em>, whereas &quot;*bar&quot; is invalid.'),
      'validate_regexp' => '`^[a-zA-Z][-_a-zA-Z0-9?*]*$`',
      'asterisk_expansion' => '[-_a-zA-Z0-9]*',
      'required_by' => 'id',
      'required_by_message' => t('The <strong>id</strong> attribute is used in your <em>HTML elements and attributes</em> rules. You should specify the <em>Rules for Element IDs</em> field in the &quot;Advanced rules&quot; section below. Leaving it unspecified will result in all id attributes filtered out.'),
    ),
    'style_urls' => array(
      'title' => t('Rules for URLs used within inline styles'),
      'description' => t('Enter a comma separated list of rules for <em>URLs used within inline styles</em>. Whitespaces and line-breaks are ignored. These rules affect the following style properties: &quot;background&quot;, &quot;background-image&quot;, &quot;list-style&quot; and &quot;list-style-image&quot;. Each rule represents a single path or URL. The asterisk character &quot;*&quot; can be used to represent any number of characters. Examples: use &quot;/*&quot; for local URLs only, use &quot;/images/*&quot; for one particular directory, use &quot;http://www.example.com/*&quot; for URLs of an external site, use &quot;@base-path*, @base-url*&quot; for URLs of your own site.', array('@base-path' => $base_path, '@base-url' => $base_url)),
      'validate_regexp' => '`^.*$`',
      'asterisk_expansion' => '.*',
      'required_by' => 'style',
      'required_by_styles' => array('background', 'background-image', 'list-style', 'list-style-image'),
      'required_by_message' => t('The <strong>style</strong> attribute is used in your <em>HTML elements and attributes</em> rules, and you have enabled one of the following style properties: &quot;background&quot;, &quot;background-image&quot;, &quot;list-style&quot; or &quot;list-style-image&quot;. You should specify the <em>Rules for URLs used within inline styles</em> field in the &quot;Advanced rules&quot; section below. Leaving it unspecified will result in all URLs used within inline styles filtered out.'),
    ),
  );
}

/**
 * Obtain a string with default valid_elements.
 */
function wysiwyg_filter_default_valid_elements() {
  return <<<EOT
a[!href|target<_blank|title],
div[align<center?justify?left?right],
p[align<center?justify?left?right],
br,span,em,strong,cite,code,blockquote,ul,ol,li,dl,dt,dd
EOT;
}

/**
 * Get HTML elements blacklist.
 */
function wysiwyg_filter_get_elements_blacklist() {
  return array(
    'applet',
    'area',
    'base',
    'basefont',
    'body',
    'button',
    'embed',
    'form',
    'frame',
    'frameset',
    'head',
    'html',
    'iframe',
    'input',
    'isindex',
    'label',
    'link',
    'map',
    'meta',
    'noframes',
    'noscript',
    'object',
    'optgroup',
    'option',
    'param',
    'script',
    'select',
    'style',
    'textarea',
    'title',
  );
}

/**
 * Parse valid_elements string in TinyMCE format.
 *
 * @link http://wiki.moxiecode.com/index.php/TinyMCE:Configuration/valid_elements
 *
 * @param string $valid_elements
 *
 * @return array
 *   Information about allowed HTML elements and attributes.
 *   Each HTML element contains a whitelist of attributes or '*' meaning all
 *   attributes are allowed for that element.
 *   Each attribute contains an array with one or more of the following items
 *   of information:
 *   - required   boolean   TRUE when attribute is required.
 *   - default    string    Default value that will be applied when only the
 *                          attribute name is specified.
 *   - forced     string    Value that will be applied when the attribute is
 *                          present in the parsed HTML stream.
 *   - values     array     Whitelist of attribute values.
 *   This information is used by the WYSIWYG Filter itself to filter out
 *   disallowed HTML elements and attributes.
 *
 * @see wysiwyg_filter_process()
 */
function wysiwyg_filter_parse_valid_elements($valid_elements) {
  // Remove whitespaces and split valid elements from a comma separate list of items into an array.
  $valid_elements = array_map('drupal_strtolower', array_filter(explode(',', preg_replace('#\s+#', '', $valid_elements))));
  $parsed_elements = array();
  $common_attributes = array();
  foreach ($valid_elements as $valid_element) {
    // Extract the element name and its allowed attributes list
    // including special characters that will be parsed later.
    if (preg_match('`^(@|[#+-]{0,1}[a-z0-9/]+)(\[([^]]*)\])*$`', $valid_element, $matches)) {
      // Element names can be specified by the special character "@" (used
      // to allow a common set of attributes for all valid HTML elements)
      // or a list of names separated by the special character "/".
      $elements = array_unique(array_filter(explode('/', $matches[1])));

      // Parse allowed attributes list (empty list means no attributes are allowed).
      $attributes = array();
      if (!empty($matches[3])) {
        // More than one attribute can be specified in the list (separator: "|").
        foreach (array_filter(explode('|', $matches[3])) as $attribute) {
          // Split item into attribute name and (optional) attribute options.
          $attribute_options = array();
          if (preg_match('`^([-a-z]+)([=:<].*)$`', $attribute, $match)) {
            $attribute = $match[1];

            // Parse attribute options.
            if (strpos('=:<', $match[2][0]) !== FALSE) {
              $operator = $match[2][0];
              if ($operator == '=') {
                // Default value for the attribute (applied when present without explicit value).
                $attribute_options['default'] = substr($match[2], 1);
              }
              else if ($operator == ':') {
                // Forced value for the attribute (applied when present regardless of the specified value).
                $attribute_options['forced'] = substr($match[2], 1);
              }
              else if ($operator == '<') {
                // This attribute accepts only the specified list of values (separator: "?").
                $attribute_options['values'] = array_unique(array_filter(explode('?', substr($match[2], 1))));
              }
            }
          }

          // Are all attributes allowed for this element?
          if ($attribute == '*') {
            $attributes['*'] = array();
            continue;
          }

          if (substr($attribute, 0, 1) == '!') {
            // If this attribute is not present in parsed HTML, then
            // the whole HTML element will be stripped out.
            $attribute = substr($attribute, 1);
            $attribute_options['required'] = TRUE;
          }

          // Ignore malformed attribute names.
          if (!preg_match('`^[a-z][-a-z]*$`', $attribute)) {
            continue;
          }

          // Attributes related to DOM events (on*) are not allowed here.
          if (substr($attribute, 0, 2) == 'on') {
            continue;
          }

          // Collect attribute options.
          if (!isset($attributes[$attribute])) {
            $attributes[$attribute] = array();
          }
          foreach ($attribute_options as $option_type => $option_value) {
            $attributes[$attribute][$option_type] = $option_value;
          }
        }
      }

      // Obtain list of element names/synonyms (separated by /).
      // Consider synonyms as different elements with same exact attributes.
      foreach ($elements as $element) {
        if ($element == '@') {
          // These attributes should be enabled for all elements.
          foreach ($attributes as $attribute => $attribute_options) {
            if (!isset($common_attributes[$attribute])) {
              $common_attributes[$attribute] = array();
            }
            foreach ($attribute_options as $option_type => $option_value) {
              $common_attributes[$attribute][$option_type] = $option_value;
            }
          }
        }
        else {
          // Ignore element name prefixes (+ - #) that are allowed for the
          // TynyMCE valid_elements parameter, but for the sake of simplicity,
          // our server side filter ignores them.
          if (strpos('+-#', $element[0]) !== FALSE) {
            $element = substr($element, 1);
          }
          if (!isset($parsed_elements[$element])) {
            $parsed_elements[$element] = array();
          }
          if (!isset($parsed_elements[$element]['*'])) {
            foreach ($attributes as $attribute => $attribute_options) {
              if ($attribute == '*') {
                $parsed_elements[$element] = array('*' => array());
                break;
              }
              if (!isset($parsed_elements[$element][$attribute])) {
                $parsed_elements[$element][$attribute] = array();
              }
              foreach ($attribute_options as $option_type => $option_value) {
                $parsed_elements[$element][$attribute][$option_type] = $option_value;
              }
            }
          }
        }
      }
    }
  }

  // Append commonly allowed attributes to each allowed element.
  if (!empty($common_attributes)) {
    foreach ($parsed_elements as $element => &$attributes) {
      // Do not append common attributes when all are allowed.
      if (isset($parsed_elements[$element]['*'])) {
        continue;
      }
      foreach ($common_attributes as $attribute => $attribute_options) {
        if (!isset($attributes[$attribute])) {
          $attributes[$attribute] = array();
        }
        foreach ($attribute_options as $option_type => $option_value) {
          $attributes[$attribute][$option_type] = $option_value;
        }
      }
    }
  }

  // Sort HTML elements alphabetically (for filter tips).
  ksort($parsed_elements);

  return $parsed_elements;
}

/**
 * Obtain list of style properties along their syntax rules.
 *
 * Style property information in compiled in logical groups, so it's
 * easier to build the filter settings form.
 *
 * Note that regular expression quantifiers are limited by number
 * of digits/characters. This is to prevent users from posting
 * big numbers/strings in property values that could cause browsers
 * to crash due to overflows, or any other kind of issue. Note that
 * users will still be able to break page layouts when using certain
 * combinations of numbers and units (ie. 100em, etc.), but nothing
 * more than that, hopefully.
 * This kind of issues may also happen when validating HTML attributes
 * where values are just checked for bad protocols. This is the same
 * exact measure taken by Drupal's filter_xss(), which has been a
 * friend of us for a long time. It's a matter of balance between
 * performance, code complexity, etc.
 *
 * All regular expressions are aimed to be delimited by `^ and $`.
 *
 * @return array
 *
 * @see wysiwyg_filter_get_style_properties()
 * @see wysiwyg_filter_settings_filter()
 */
function wysiwyg_filter_get_style_property_groups() {
  $regexp_integer = '[-]?[0-9]{1,3}';
  $regexp_number = '[-]?(?:[0-9]{0,3}|[0-9]{0,3}\.[0-9]{1,4})';
  $regexp_length = $regexp_number . '(?:px|pt|em|ex|in|cm|mm|pc)?';
  $regexp_percent = '[-]?[12]?[0-9]{1,2}%';
  $regexp_color = '#[a-fA-F0-9]{3}|#[a-fA-F0-9]{6}|rgb\(\s*[0-9]{0,3}%?(?:\s*,\s*[0-9]{0,3}%?){2}\s*\)|[a-zA-Z]+';
  $regexp_bgcolor = $regexp_color . '|transparent';
  $regexp_border_width = $regexp_length . '|thin|medium|thick';
  $regexp_border_style = 'none|hidden|dotted|dashed|solid|double|groove|ridge|inset|outset';
  $regexp_uri = 'url\(\s*[\'"]?(?:[^)]|(?<=\\\\)\\))+[\'"]?\s*\)';
  $regexp_shape = 'rect\(\s*(?:auto|' . $regexp_length . ')(?:\s+(?:auto|' . $regexp_length . ')){3}\s*\)';
  $regexp_list_style_type = 'none|disc|circle|square|decimal(?:-leading-zero)?|lower-(?:alpha|greek|latin|roman)|upper-(?:alpha|latin|roman)|hebrew|armenian|georgian|cjk-ideographic|hiragana(?:-iroha)?|katakana(?:-iroha)?';

  // Note that shorthand properties such as background and font are built
  // below, so we can reuse regular expression definitions.
  $groups = array(
    'color' => array(
      'title' => t('Color and background properties'),
      'properties' => array(
        'color' => '(?:' . $regexp_color . ')',
        'background' => '', // See this property expanded below.
        'background-color' => '(?:' . $regexp_bgcolor . ')',
        'background-image' => '(?:none|' . $regexp_uri . ')',
        'background-repeat' => '(?:no-repeat|repeat(?:-x|-y)?)',
        'background-attachment' => '(?:scroll|fixed)',
        'background-position' => '(?:(?:(?:top|center|bottom|left|right)(?:\s+(?:top|center|bottom|left|right))?)|(?:(?:' . $regexp_length . '|' . $regexp_percent . ')(?:\s+(?:' . $regexp_length . '|' . $regexp_percent . '))?))',
      ),
    ),
    'font' => array(
      'title' => t('Font properties'),
      'properties' => array(
        'font' => '', // See this property expanded below.
        'font-family' => '(?:[-_a-zA-Z0-9"\' ]*(?:\s*,\s*[-_a-zA-Z0-9"\' ]*)*)',
        'font-size' => '(?:(?:x-|xx-)?(?:small|large)(?:er)?|medium|' . $regexp_length . '|' . $regexp_percent . ')',
        'font-size-adjust' => '(?:none|' . $regexp_number . ')',
        'font-stretch' => '(?:normal|wider|narrower|(?:ultra-|extra-|semi-)?(?:condensed|expanded))',
        'font-style' => '(?:normal|italic|oblique)',
        'font-variant' => '(?:normal|small-caps)',
        'font-weight' => '(?:normal|bold|bolder|lighter|[1-9]00)',
      ),
    ),
    'text' => array(
      'title' => t('Text properties'),
      'properties' => array(
        'text-align' => '(?:left|right|center|justify)',
        'text-decoration' => '(?:none|underline|overline|line-through|blink)',
        'text-indent' => '(?:' . $regexp_length . '|' . $regexp_percent . ')',
        'text-transform' => '(?:none|capitalize|(?:upper|lower)case)',
        'letter-spacing' => '(?:normal|' . $regexp_length . ')',
        'word-spacing' => '(?:normal|' . $regexp_length . ')',
        'white-space' => '(?:normal|pre|nowrap)',
        'direction' => '(?:ltr|rtl)',
        'unicode-bidi' => '(?:normal|embed|bidi-override)',
      ),
    ),
    'box' => array(
      'title' => t('Box properties'),
      'properties' => array(
        'margin' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')(?:\s+(?:auto|' . $regexp_length . '|' . $regexp_percent . ')){0,3}',
        'margin-top' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'margin-right' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'margin-bottom' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'margin-left' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'padding' => '(?:' . $regexp_length . '|' . $regexp_percent . ')(?:\s+(?:' . $regexp_length . '|' . $regexp_percent . ')){0,3}',
        'padding-top' => '(?:' . $regexp_length . '|' . $regexp_percent . ')',
        'padding-right' => '(?:' . $regexp_length . '|' . $regexp_percent . ')',
        'padding-bottom' => '(?:' . $regexp_length . '|' . $regexp_percent . ')',
        'padding-left' => '(?:' . $regexp_length . '|' . $regexp_percent . ')',
      ),
    ),
    'border-1' => array(
      'title' => t('Border properties (1)'),
      'properties' => array(
        'border' => '(?:(?:' . $regexp_border_width . ')?(?:\s*(?:' . $regexp_border_style . ')?(?:\s*(?:' . $regexp_bgcolor . ')?)))',
        'border-top' => '(?:(?:' . $regexp_border_width . ')?(?:\s*(?:' . $regexp_border_style . ')?(?:\s*(?:' . $regexp_bgcolor . ')?)))',
        'border-right' => '(?:(?:' . $regexp_border_width . ')?(?:\s*(?:' . $regexp_border_style . ')?(?:\s*(?:' . $regexp_bgcolor . ')?)))',
        'border-bottom' => '(?:(?:' . $regexp_border_width . ')?(?:\s*(?:' . $regexp_border_style . ')?(?:\s*(?:' . $regexp_bgcolor . ')?)))',
        'border-left' => '(?:(?:' . $regexp_border_width . ')?(?:\s*(?:' . $regexp_border_style . ')?(?:\s*(?:' . $regexp_bgcolor . ')?)))',
        'border-width' => '(?:' . $regexp_border_width . ')(?:\s+(?:' . $regexp_border_width . ')){0,3}',
        'border-top-width' => '(?:' . $regexp_border_width . ')',
        'border-right-width' => '(?:' . $regexp_border_width . ')',
        'border-bottom-width' => '(?:' . $regexp_border_width . ')',
        'border-left-width' => '(?:' . $regexp_border_width . ')',
      ),
    ),
    'border-2' => array(
      'title' => t('Border properties (2)'),
      'properties' => array(
        'border-color' => '(?:' . $regexp_bgcolor . ')(?:\s+(?:' . $regexp_bgcolor . ')){0,3}',
        'border-top-color' => '(?:' . $regexp_bgcolor . ')',
        'border-right-color' => '(?:' . $regexp_bgcolor . ')',
        'border-bottom-color' => '(?:' . $regexp_bgcolor . ')',
        'border-left-color' => '(?:' . $regexp_bgcolor . ')',
        'border-style' => '(?:' . $regexp_border_style . ')(?:\s+(?:' . $regexp_border_style . ')){0,3}',
        'border-top-style' => '(?:' . $regexp_border_style . ')',
        'border-right-style' => '(?:' . $regexp_border_style . ')',
        'border-bottom-style' => '(?:' . $regexp_border_style . ')',
        'border-left-style' => '(?:' . $regexp_border_style . ')',
      ),
    ),
    'dimension' => array(
      'title' => t('Dimension properties'),
      'properties' => array(
        'height' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'line-height' => '(?:normal|' . $regexp_number . '|' . $regexp_length . '|' . $regexp_percent . ')',
        'max-height' => '(?:none|' . $regexp_length . '|' . $regexp_percent . ')',
        'max-width' => '(?:none|' . $regexp_length . '|' . $regexp_percent . ')',
        'min-height' => '(?:' . $regexp_length . '|' . $regexp_percent . ')',
        'min-width' => '(?:' . $regexp_length . '|' . $regexp_percent . ')',
        'width' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
      ),
    ),
    'positioning' => array(
      'title' => t('Positioning properties'),
      'properties' => array(
        'bottom' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'clip' => '(?:auto|' . $regexp_shape . ')',
        'left' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'overflow' => '(?:visible|hidden|scroll|auto)',
        'right' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'top' => '(?:auto|' . $regexp_length . '|' . $regexp_percent . ')',
        'vertical-align' => '(?:baseline|sub|super|middle|(?:text-)?(?:top|bottom)|' . $regexp_length . '|' . $regexp_percent . ')',
        'z-index' => '(?:auto|' . $regexp_integer . ')',
      ),
    ),
    'layout' => array(
      'title' => t('Layout properties'),
      'properties' => array(
        'clear' => '(?:left|right|both|none)',
        'display' => '(?:none|inline|block|list-item|run-in|compact|marker|table-(?:(?:row|header|group|column)-group|row|column|cell|caption)|(?:inline-)?table)',
        'float' => '(?:left|right|none)',
        'position' => '(?:static|relative|absolute|fixed)',
        'visibility' => '(?:visible|hidden|collapse)',
      ),
    ),
    'list' => array(
      'title' => t('List properties'),
      'properties' => array(
        'list-style' => '(?:(?:' . $regexp_list_style_type . ')?(?:\s*(?:(?:in|out)side)?(?:\s*(?:none|' . $regexp_uri . ')?)))',
        'list-style-image' => '(?:none|' . $regexp_uri . ')',
        'list-style-position' => '(?:inside|outside)',
        'list-style-type' => '(?:' . $regexp_list_style_type . ')',
      ),
    ),
    'table' => array(
      'title' => t('Table properties'),
      'properties' => array(
        'border-collapse' => '(?:collapse|separate)',
        'border-spacing' => '(?:' . $regexp_length . '(?:\s+' . $regexp_length . ')?)',
        'caption-side' => '(?:top|bottom|left|right)',
        'empty-cells' => '(?:show|hide)',
        'table-layout' => '(?:auto|fixed)',
      ),
    ),
    'user' => array(
      'title' => t('User interface properties'),
      'properties' => array(
        'cursor' => '(?:auto|crosshair|default|pointer|move|(?:e|ne|nw|n|se|sw|s|w)-resize|text|wait|help)',
        'outline' => '(?:(?:' . $regexp_color . '|invert)?(?:\s*(?:' . $regexp_border_style . ')?(?:\s*(?:' . $regexp_border_width . ')?)))',
        'outline-width' => '(?:' . $regexp_border_width . ')',
        'outline-style' => '(?:' . $regexp_border_style . ')',
        'outline-color' => '(?:' . $regexp_color . '|invert)',
        'zoom' => '(?:normal|' . $regexp_number . '|' . $regexp_percent . ')',
      ),
    ),
  );

  // 'background' property.
  $regexp = '(?:' .
    $groups['color']['properties']['background-color'] . '|' .
    $groups['color']['properties']['background-image'] . '|' .
    $groups['color']['properties']['background-repeat'] . '|' .
    $groups['color']['properties']['background-attachment'] . '|' .
    $groups['color']['properties']['background-position'] . ')';
  $groups['color']['properties']['background'] = '(?:' . $regexp . ')(?:(?:\s+' . $regexp . ')+)';

  // 'font' property.
  $regexp = '(?:' .
    $groups['font']['properties']['font-style'] . '|' .
    $groups['font']['properties']['font-variant'] . '|' .
    $groups['font']['properties']['font-weight'] . '|' .
    '(?:' . $groups['font']['properties']['font-size'] . ')(?:\s*/\s*' . $groups['dimension']['properties']['line-height'] . ')?|' .
    $groups['font']['properties']['font-family'] . ')';
  $groups['font']['properties']['font'] = '(?:' . $regexp . ')(?:(?:\s+' . $regexp . ')+)';

  return $groups;
}

/**
 * Get filter options.
 *
 * @param int $format_name
 *   Input format identifier.
 * @param int $settings
 *   Filter settings.
 * @return array
 */
function wysiwyg_filter_get_filter_options($format_name, $settings) {
  $filter_options = array(
    'valid_elements' => wysiwyg_filter_parse_valid_elements($settings['valid_elements']),
    'allow_comments' => $settings['allow_comments'],
    'style_properties' => wysiwyg_filter_get_style_properties($format_name, $settings),
    'nofollow_policy' => $settings['nofollow_policy'],
    'nofollow_domains' => $settings['nofollow_domains'],
  );
  foreach (wysiwyg_filter_get_advanced_rules() as $rule_key => $rule_info) {
    $filter_options[$rule_key] = array();
    foreach ($settings["rule_$rule_key"] as $rule) {
      $filter_options[$rule_key][] = '`^' . str_replace("\xFF", $rule_info['asterisk_expansion'], preg_quote(str_replace('*', "\xFF", $rule), '`')) . '$`';
    }
  }
  return $filter_options;
}

/**
 * Get allowed style properties.
 *
 * @param int $format_name
 *   Input format identifier.
 * @param int $settings
 *   Filter settings.
 * @return array
 */
function wysiwyg_filter_get_style_properties($format_name, $settings) {
  static $style_properties = array();
  if (!isset($style_properties[$format_name])) {
    $style_properties[$format_name] = array();
    foreach (wysiwyg_filter_get_style_property_groups() as $group => $group_info) {
      $allowed_styles = array_filter($settings["style_$group"]);
      foreach ($group_info['properties'] as $property => $regexp) {
        if (isset($allowed_styles[$property])) {
          $style_properties[$format_name][$property] = '`^' . $regexp . '$`';
        }
      }
    }
    // Sort style properties alphabetically (for filter tips).
    ksort($style_properties[$format_name]);
  }
  return $style_properties[$format_name];
}
