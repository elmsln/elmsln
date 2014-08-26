<?php

/**
 * @file
 * CSS Embedded Images module.
 */

// Helper Functions.
/**
 * Helper function to store collected CSS declarations.
 */
function _css_emimage_collect_static($data = NULL) {
  static $store = array();
  if (!is_null($data)) {
    $store = $data;
  }
  return $store;
}

/**
 * Generates CSS with data URIs inline with the declarations.
 *
 * @return
 *   string CSS with inline data URIs
 */
function _css_emimage_build_inline($css, $declarations) {
  foreach ($declarations as $data) {
    if ($data['base64']) {
      $css = str_replace($data['token'], 'url(data:' . $data['mime_type'] . ';base64,' . $data['base64'] . ')', $css);
    }
    else {
      $css = str_replace($data['token'], $data['url'], $css);
    }
  }
  return $css;
}

/**
 * Generates CSS with external data URIs.
 *
 * @return array a tuple where the first element is the updated CSS and the
 *     second element is the CSS declarations containing only data URIs
 */
function _css_emimage_build_external($css, $declarations) {
  $datauri_css = '';
  foreach ($declarations as $data) {
    if ($data['base64']) {
      $css = str_replace($data['token'], 'none', $css);
      $insert_string = implode(',', $data['selectors']) . '{' . $data['property'] . ':url(data:' . $data['mime_type'] . ';base64,' . $data['base64'] . ')' . ($data['important'] ? ' !important' : '') . ";}\n";
      if (!empty($data['media_query'])) {
        $insert_string = $data['media_query'] . ' { ' . $insert_string . ' } ';
      }
      $datauri_css .= $insert_string;
    }
    elseif ($datauri_css) {
      // Only add these if the CSS has at least one data URI.
      $css = str_replace($data['token'], 'none', $css);
      $insert_string = implode(',', $data['selectors']) . '{' . $data['property'] . ':' . $data['url'] . ($data['important'] ? ' !important' : '') . ";}\n";
      if (!empty($data['media_query'])) {
        $insert_string = $data['media_query'] . ' { ' . $insert_string . ' } ';
      }
      $datauri_css .= $insert_string;
    }
    else {
      $css = str_replace($data['token'], $data['url'], $css);
    }
  }
  return array($css, $datauri_css);
}

/**
 * preg_replace_callback() callback to replace URLs with data URIs.
 */
function _css_emimage_replace($matches) {
  list($declaration, $selector, $properties) = $matches;
  $pattern = '/(background(?:-image)?|list-style(?:-image)?):[^{};)]*?((?:none|url\([\'"]?(.+?)[\'"]?\)))([^{};]*)/i';
  preg_match_all($pattern, $properties, $matches);
  foreach ($matches[1] as $i => $property) {
    $url = $matches[2][$i];
    $file = $matches[3][$i];
    $important = stripos($matches[4][$i], '!important') !== FALSE;
    if ($file && (strpos($file, base_path()) === 0) && ($image = image_get_info($file = substr($file, strlen(base_path()))))) {
      $ielimit = variable_get('css_emimage_ielimit', 1); // only embed data URIs less than 32KB, thanks IE
      if ($ielimit && ($image['file_size']*1.3333) >= CSS_EMIMAGE_IE_DATAURI_LIMIT) {
        $image = NULL;
      }
      $token = _css_emimage_collect(array($selector, $property, $url, $file, $important, $image));
      $declaration = str_replace($url, $token, $declaration);
    }
    else {
      _css_emimage_collect(array($selector, $property, $url, $file, $important, NULL));
    }
  }
  return $declaration;
}

/**
 * Helper function to collect CSS declarations to replace with data URIs.
 *
 * @return
 *   string a token used during the replacement process
 */
function _css_emimage_collect($info) {
  list($declarations, $file_stats) = _css_emimage_collect_static();
  if (!$declarations) {
    $declarations = array();
  }
  if (!$file_stats) {
    $file_stats = array();
  }

  if (is_array($info)) {
    list($selector, $property, $url, $file, $important, $image) = $info;

    $selector = trim($selector);

    // Normalize the CSS property name - allows us to collapse declarations in
    // some cases, and generated CSS is more consistent.
    if ($property == 'background' || $property == 'list-style') {
      $property .= '-image';
    }

    $current = array_pop($declarations);
    switch (TRUE) {
      case $current && ($current['property'] != $property || $current['file'] != $file || $current['important'] != $important):
        array_push($declarations, $current);
      case !$current:
        $pos = count($declarations);
        $current = array(
          'pos' => $pos,
          'token' => "[css_emimage:$pos]",
          'selectors' => array($selector),
          'property' => $property,
          'url' => $url,
          'file' => $file,
          'important' => $important,
          'base64' => $image ? base64_encode(file_get_contents($file)) : '',
          'mime_type' => $image ? $image['mime_type'] : '',
        );
        if ($current['base64']) {
          if (!isset($file_stats[$file])) {
            $file_stats[$file] = array('indices' => array($pos), 'total_length' => strlen($current['base64']));
          }
          else {
            $file_stats[$file]['indices'][] = $pos;
            $file_stats[$file]['total_length'] += strlen($current['base64']);
          }
        }
        break;
      default:
        $current['selectors'][] = $selector;
        break;
    }

    array_push($declarations, $current);
    _css_emimage_collect_static(array($declarations, $file_stats));
    return $current['token'];
  }

  return FALSE;
}

/**
 * Split up as CSS string by @media queries.
 *
 * @see http://stackoverflow.com/questions/14145620/regular-expression-for-media-queries-in-css
 *
 * @return
 *   array of css with only media queries.
 */
function parse_media_blocks($css) {
  $media_blocks = array();

  $start = 0;
  while (($start = strpos($css, "@media", $start)) !== FALSE) {
    // stack to manage brackets
    $s = array();

    // get the first opening bracket
    $i = strpos($css, "{", $start);

    // if $i is false, then there is probably a css syntax error
    if ($i !== FALSE) {
      // push bracket onto stack
      array_push($s, $css[$i]);

      // move past first bracket
      $i++;

      while (!empty($s)) {
        // if the character is an opening bracket, push it onto the stack, otherwise pop the stack
        if ($css[$i] == "{") {
          array_push($s, "{");
        }
        elseif ($css[$i] == "}") {
          array_pop($s);
        }
        $i++;
      }

      // cut the media block out of the css and store
      $media_blocks[] = substr($css, $start, ($i + 1) - $start);

      // set the new $start to the end of the block
      $start = $i;
    }
  }

  return $media_blocks;
}
