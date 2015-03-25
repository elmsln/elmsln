<?php

/**
 * @file
 * User land code for the WYSIWYG Filter module.
 */

/**
 * WYSIWYG Filter. Provides filtering of input into accepted HTML.
 *
 * This function is based on Drupal's filter_xss() with a few additions:
 * - Validates HTML input against whitelists of HTML elements, attributes
 *   and style properties.
 * - Optionally apply rel="nofollow" rules to links.
 * - Rules for the above can be specified by site administrators from the
 *   filter settings form.
 *
 * @param string $text
 *   HTML text to be filtered.
 * @param int $format
 *   Input format identifier.
 * @return string
 *   Filtered HTML text.
 */
function wysiwyg_filter_filter_wysiwyg_process($text, $filter, $format, $langcode, $cache, $cache_id) {
  // Only operate on valid UTF-8 strings. This is necessary to prevent cross
  // site scripting issues on Internet Explorer 6.
  if (!drupal_validate_utf8($text)) {
    return '';
  }

  // Load common functions.
  module_load_include('inc', 'wysiwyg_filter');

  // Store input filter options.
  _wysiwyg_filter_xss_split(wysiwyg_filter_get_filter_options($format->format, $filter->settings), TRUE);

  // Remove NUL characters (ignored by some browsers).
  $text = str_replace(chr(0), '', $text);
  // Remove Netscape 4 JS entities.
  $text = preg_replace('%&\s*\{[^}]*(\}\s*;?|$)%', '', $text);

  // Defuse all HTML entities.
  $text = str_replace('&', '&amp;', $text);
  // Change back only well-formed entities in our whitelist
  // Decimal numeric entities.
  $text = preg_replace('/&amp;#([0-9]+;)/', '&#\1', $text);
  // Hexadecimal numeric entities.
  $text = preg_replace('/&amp;#[Xx]0*((?:[0-9A-Fa-f]{2})+;)/', '&#x\1', $text);
  // Named entities.
  $text = preg_replace('/&amp;([A-Za-z][A-Za-z0-9]*;)/', '&\1', $text);

  return preg_replace_callback('%
    (
    <(?=[^a-zA-Z!/])  # a lone <
    |                 # or
    <!--.*?-->        # a comment
    |                 # or
    <[^>]*(>|$)       # a string that starts with a <, up until the > or the end of the string
    |                 # or
    >                 # just a >
    )%x', '_wysiwyg_filter_xss_split', $text);
}

/**
 * Processes an HTML tag.
 *
 * @param $m
 *   An array with various meaning depending on the value of $store.
 *   If $store is TRUE then the array contains the allowed tags.
 *   If $store is FALSE then the array has one element, the HTML tag to process.
 * @param $store
 *   Whether to store $m.
 * @return
 *   If the element isn't allowed, an empty string. Otherwise, the cleaned up
 *   version of the HTML element.
 */
function _wysiwyg_filter_xss_split($m, $store = FALSE) {
  static $filter_options;

  if ($store) {
    _wysiwyg_filter_xss_attributes($filter_options = $m);
    return;
  }

  $string = $m[1];

  if (substr($string, 0, 1) != '<') {
    // We matched a lone ">" character
    return '&gt;';
  }
  else if (strlen($string) == 1) {
    // We matched a lone "<" character
    return '&lt;';
  }

  if (!preg_match('%^<\s*(/\s*)?([a-zA-Z0-9]+)([^>]*)>?|(<!--.*?-->)$%', $string, $matches)) {
    // Seriously malformed
    return '';
  }

  $slash = trim($matches[1]);
  $elem = strtolower($matches[2]);
  $attrlist = &$matches[3];
  $comment = &$matches[4];

  if (!empty($comment)) {
    // Allow or disallow HTML comments.
    return (!empty($filter_options['allow_comments']) ? $comment : '');
  }
  elseif (!isset($filter_options['valid_elements'][$elem])) {
    // Disallowed HTML element.
    return '';
  }

  if ($slash != '') {
    return "</$elem>";
  }

  // Is there a closing XHTML slash at the end of the attributes?
  // In PHP 5.1.0+ we could count the changes, currently we need a separate match
  $xhtml_slash = preg_match('%\s?/\s*$%', $attrlist) ? ' /' : '';
  $attrlist = preg_replace('%(\s?)/\s*$%', '\1', $attrlist);

  // Clean up attributes
  if (($attr2 = _wysiwyg_filter_xss_attributes($attrlist, $elem)) === FALSE) {
    // Disallowed HTML element because it does not contain required attribute.
    return '';
  }
  $attr2 = implode(' ', $attr2);
  $attr2 = preg_replace('/[<>]/', '', $attr2);
  $attr2 = strlen($attr2) ? ' ' . $attr2 : '';

  return "<$elem$attr2$xhtml_slash>";
}

/**
 * Processes a string of HTML attributes.
 *
 * @param mixed $attr
 *   String with attributes list to be checked.
 *   Array with whitelist of all HTML elements and their allowed attributes.
 * @param string $element
 *   Current element for specified attributes lists.
 * @return
 *   Cleaned up version of the HTML attributes.
 */
function _wysiwyg_filter_xss_attributes($attr, $element = '') {
  static $filter_options;

  if (is_array($attr)) {
    $filter_options = $attr;
    return;
  }

  // Shortcuts for filter options.
  $allowed_attributes = &$filter_options['valid_elements'][$element];
  $allowed_properties = &$filter_options['style_properties'];
  $allowed_style_urls = &$filter_options['style_urls'];
  $allowed_class_names = &$filter_options['valid_classes'];
  $allowed_element_ids = &$filter_options['valid_ids'];
  $nofollow_policy = &$filter_options['nofollow_policy'];
  $nofollow_domains = &$filter_options['nofollow_domains'];

  $attrarr = array();
  $mode = 0;
  $attrname = '';

  while (strlen($attr) != 0) {
    // Was the last operation successful?
    $working = 0;

    switch ($mode) {
      case 0:
        // Attribute name, href for instance.
        if (preg_match('/^([-a-zA-Z]+)/', $attr, $match)) {
          $attrname = strtolower($match[1]);
          $skip = (substr($attrname, 0, 2) == 'on' || (!isset($allowed_attributes[$attrname]) && !isset($allowed_attributes['*'])));
          $working = $mode = 1;
          $attr = preg_replace('/^[-a-zA-Z]+/', '', $attr);
        }

        break;

      case 1:
        // Equals sign or valueless ("selected").
        if (preg_match('/^\s*=\s*/', $attr)) {
          $working = 1;
          $mode = 2;
          $attr = preg_replace('/^\s*=\s*/', '', $attr);
          break;
        }

        if (preg_match('/^\s+/', $attr)) {
          $working = 1;
          $mode = 0;
          if (!$skip) {
            $attrarr[$attrname] = array();
          }
          $attr = preg_replace('/^\s+/', '', $attr);
        }

        break;

      case 2:
        // Attribute value, a URL after href= for instance.
        if (preg_match('/^"([^"]*)"(\s+|$)/', $attr, $match)) {
          if (!$skip) {
            $attrarr[$attrname] = array(
              'value' => $match[1],
              'delimiter' => '"',
            );
          }
          $working = 1;
          $mode = 0;
          $attr = preg_replace('/^"[^"]*"(\s+|$)/', '', $attr);
          break;
        }

        if (preg_match("/^'([^']*)'(\s+|$)/", $attr, $match)) {
          if (!$skip) {
            $attrarr[$attrname] = array(
              'value' => $match[1],
              'delimiter' => '\'',
            );
          }
          $working = 1;
          $mode = 0;
          $attr = preg_replace("/^'[^']*'(\s+|$)/", '', $attr);
          break;
        }

        if (preg_match("%^([^\s\"']+)(\s+|$)%", $attr, $match)) {
          if (!$skip) {
            $attrarr[$attrname] = array(
              'value' => $match[1],
              'delimiter' => '"',
            );
          }
          $working = 1;
          $mode = 0;
          $attr = preg_replace("%^[^\s\"']+(\s+|$)%", '', $attr);
        }

        break;
    }

    if ($working == 0) {
      // not well formed, remove and try again.
      $attr = preg_replace('/
        ^
        (
        "[^"]*("|$)     # - a string that starts with a double quote, up until the next double quote or the end of the string
        |               # or
        \'[^\']*(\'|$)| # - a string that starts with a quote, up until the next quote or the end of the string
        |               # or
        \S              # - a non-whitespace character
        )*              # any number of the above three
        \s*             # any number of whitespaces
        /x', '', $attr);
      $mode = 0;
    }
  }

  // The attribute list ends with a valueless attribute like "selected".
  if ($mode == 1 && !$skip) {
    $attrarr[$attrname] = array();
  }

  // Check the current HTML element for required attributes.
  foreach ($allowed_attributes as $attrname => $attrinfo) {
    if (!empty($attrinfo['required']) && !isset($attrarr[$attrname])) {
      // Ignore the whole element if required attribute is not present.
      return FALSE;
    }

    // When no attribute value has been specified in parsed HTML stream,
    // then supply default value if provided by input format settings.
    if (!isset($attrinfo['value']) && isset($allowed_attributes[$attrname]['default'])) {
      $attrarr[$attrname] = array(
        'value' => $allowed_attributes[$attrname]['default'],
        'delimiter' => '"',
      );
    }
  }

  // Check the current HTML element for additional attribute rules.
  $parsed_attributes = array();
  $add_nofollow = FALSE;
  foreach ($attrarr as $attrname => $attrinfo) {
    $parsed_attribute = $attrname;
    $attribute_options = (isset($allowed_attributes[$attrname]) ? $allowed_attributes[$attrname] : array());

    if (isset($attrinfo['value'])) {
      // Supply forced attribute value as defined by input format?
      if (isset($attribute_options['forced'])) {
        $attrinfo['value'] = $attribute_options['forced'];
      }
      else if (isset($attribute_options['values']) && !in_array($attrinfo['value'], $attribute_options['values'])) {
        // Ignore attribute if value is not present in whitelist.
        continue;
      }

      // Additional validation of attribute values.
      if ($attrname == 'style') {
        // Ok, let us validate individual style properties (decode entities now).
        $dirty_properties = array_filter(array_map('trim', explode(';', decode_entities($attrinfo['value']))));
        $sanitized_properties = array();
        foreach ($dirty_properties as $dirty_property) {
          // Separate property name from its value.
          if (!preg_match('#^([a-zA-Z][-a-zA-Z]*)\s*:\s*(.*)$#', $dirty_property, $property_matches)) {
            // Ignore properties that do not match the format "property-name: value".
            continue;
          }
          $property_name = strtolower($property_matches[1]);
          $property_value = &$property_matches[2];
          if (!isset($allowed_properties[$property_name])) {
            // Ignore property if not whitelisted in filter settings.
            continue;
          }

          // Check style property syntax.
          if (!preg_match($allowed_properties[$property_name], $property_value)) {
            // Ignore property if value does not match syntax rules.
            continue;
          }

          // If property value comes with url(...), then we want to check if it's allowed or not.
          if (strpos($property_value, 'url(') !== FALSE) {
            if (count($allowed_style_urls) <= 0) {
              // Ignore property if no rules have been specified.
              continue;
            }

            // This is like $regexp_uri in wysiwyg_filter_get_style_property_groups(), but it now contains 2 capturing
            // groups [1] for the URL itself (including delimiters) and [2] the first delimiter (if any).
            if (!preg_match('`url\(\s*(([\'"]?)(?:[^)]|(?<=\\\\)\\))+[\'"]?)\s*\)`', $property_value, $url) || empty($url[1])) {
              // Ignore property if found to be malformed here.
              continue;
            }
            if (!empty($url[2])) {
              if (substr($url[1], -1) != $url[2]) {
                // Ignore property if start and end delimiters don't match.
                continue;
              }
              // Remove delimiters.
              $url[1] = substr($url[1], 1, -1);
            }
            // Remove backslashes that could have been used to escape parentheses,
            // commas, whitespace characters, single quotes or double quotes.
            // http://www.w3.org/TR/CSS2/syndata.html#uri
            $url = preg_replace('`\\\\([(),\'"\s])`', '\1', $url[1]);

            // Ignore property if URL fails the check for bad protocols.
            if (wysiwyg_filter_xss_bad_protocol($url) != $url) {
              continue;
            }

            // Check URL against advanced filter rules.
            $match_found = FALSE;
            foreach ($allowed_style_urls as $regexp) {
              if (preg_match($regexp, $url)) {
                $match_found = TRUE;
                break;
              }
            }
            if (!$match_found) {
              // Ignore property if URL does not match any rule.
              continue;
            }
          }
          else {
            // Filter property value for bad protocols (note that property value has already been decoded).
            $property_value = wysiwyg_filter_xss_bad_protocol($property_value);
          }

          // Sanitized property name and value (check_plain'd here).
          $sanitized_properties[] = $property_name . ':' . check_plain($property_value);
        }

        if (empty($sanitized_properties)) {
          // Ignore the whole style attribute if no property remains.
          continue;
        }

        $attrinfo['value'] = implode('; ', $sanitized_properties);
      }
      else if ($attrname == 'class') {
        // Validate class names based on advanced rules specified in filter settings panel.
        // Note that property value is decoded now and check_plain'd at end. Since the colon
        // sign is not allowed, there's no need here to check for bad protocols.
        $dirty_names = array_filter(array_map('trim', explode(' ', decode_entities($attrinfo['value']))));
        $valid_names = array();
        foreach ($dirty_names as $dirty_name) {
          foreach ($allowed_class_names as $regexp) {
            if (preg_match($regexp, $dirty_name)) {
              $valid_names[] = $dirty_name;
            }
          }
        }
        if (empty($valid_names)) {
          // Ignore attribute if no class name remains after validation.
          continue;
        }
        $attrinfo['value'] = check_plain(implode(' ', $valid_names));
      }
      else if ($attrname == 'id') {
        // Validate element IDs based on advanced rules specified in filter settings panel.
        // Note that property value is decoded now and check_plain'd at end. Since the colon
        // sign is not allowed, there's no need here to check for bad protocols.
        if (count($allowed_element_ids) <= 0) {
          // Ignore attribute if no rules have been specified.
          continue;
        }
        // Decode value so we can easilly check it.
        $attrinfo['value'] = decode_entities($attrinfo['value']);
        // Pattern starts valid, but it should match all specified rules.
        $match_found = FALSE;
        foreach ($allowed_element_ids as $regexp) {
          if (preg_match($regexp, $attrinfo['value'])) {
            $match_found = TRUE;
            break;
          }
        }
        if (!$match_found) {
          // Ignore attribute if it contains invalid value.
          continue;
        }
        // Element ID is valid, check_plain result.
        $attrinfo['value'] = check_plain($attrinfo['value']);
      }
      else {
        // All attribute values are checked for bad protocols. This is the same
        // exact method used by Drupal's filter_xss().
        $attrinfo['value'] = filter_xss_bad_protocol($attrinfo['value']);

        // If this is <a href> element, then check domain name for rel="nofollow" policies in effect.
        if ($element == 'a' && $attrname == 'href' && $nofollow_policy != 'disabled' && !$add_nofollow) {
          $domain_found = FALSE;
          foreach ($nofollow_domains as $domain) {
            $domain = str_replace('.', '\.', $domain); // escape dots
            if (preg_match('#://.*' . $domain . '([^a-z0-9]|$)#i', $attrinfo['value'])) {
              $domain_found = TRUE;
              break;
            }
          }
          if (($nofollow_policy == 'blacklist' && $domain_found) || ($nofollow_policy == 'whitelist' && !$domain_found)) {
            $add_nofollow = TRUE;
          }
        }
      }

      // Build parsed attribute value.
      $parsed_attribute .= '=' . $attrinfo['delimiter'] . $attrinfo['value'] . $attrinfo['delimiter'];
    }

    $parsed_attributes[$attrname] = $parsed_attribute;
  }

  // Do we have a link where rel="nofollow" should be added?
  if ($add_nofollow) {
    if (empty($parsed_attributes['rel'])) {
      $parsed_attributes['rel'] = 'rel="nofollow"';
    }
    else if (strpos($parsed_attributes['rel'], 'nofollow') === FALSE) {
      // Since we know the attribute is well formed, we can use substr(), which is faster than preg_replace().
      $parsed_attributes['rel'] = substr($parsed_attributes['rel'], 0, -1) . ' nofollow' . substr($parsed_attributes['rel'], -1);
    }
  }

  return $parsed_attributes;
}

/**
 * Processes an style property value and ensures it does not contain an URL
 * with a disallowed protocol (only http/https are allowed here).
 *
 * This function is based on Drupal's filter_xss_bad_protocol(). Differences are:
 * 1) It does not decode input string.
 *    It should be done by the caller before calling us.
 * 2) It does not apply check_plain() to result.
 *    It should be done by the caller after calling us.
 * 3) It allows a lot less protocols.
 *
 * @param $string
 *   The string with the style property value.
 * @return
 *   Cleaned up version of $string.
 */
function wysiwyg_filter_xss_bad_protocol($string) {
  $allowed_protocols = array(
    'http' => 1,
    'https' => 1,
  );

  // Iteratively remove any invalid protocol found.

  do {
    $before = $string;
    $colonpos = strpos($string, ':');
    if ($colonpos > 0) {
      // We found a colon, possibly a protocol. Verify.
      $protocol = substr($string, 0, $colonpos);
      // If a colon is preceded by a slash, question mark or hash, it cannot
      // possibly be part of the URL scheme. This must be a relative URL,
      // which inherits the (safe) protocol of the base document.
      if (preg_match('![/?#]!', $protocol)) {
        break;
      }
      // Per RFC2616, section 3.2.3 (URI Comparison) scheme comparison must be case-insensitive
      // Check if this is a disallowed protocol.
      if (!isset($allowed_protocols[strtolower($protocol)])) {
        $string = substr($string, $colonpos + 1);
      }
    }
  } while ($before != $string);
  return $string;
}
