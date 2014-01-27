<?php
/*
 * Custom theme functions
 *
 */

/**
 * Returns HTML for a set of links.
 */
function theme_bootstrap_links($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];

  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';
    $output .= '<ul' . drupal_attributes($attributes) . '>';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'li',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $children = array();

      if (isset($link['below'])) {
        $children = $link['below'];
      }

      $attributes = array('class' => array($key));

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_links) {
        $attributes['class'][] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
        && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $attributes['class'][] = 'active';
      }

      if (count($children) > 0) {
        $attributes['class'][] = 'dropdown';
        $link['attributes']['data-toggle'] = 'dropdown';
        $link['attributes']['class'][] = 'dropdown-toggle';
      }

      if (!isset($link['attributes'])) {
        $link['attributes'] = array();
      }

      $link['attributes'] = array_merge($link['attributes'], $attributes);

      if (count($children) > 0) {
        $link['attributes']['class'][] = 'dropdown';
      }

      $output .= '<li' . drupal_attributes($attributes) . '>';

      if (isset($link['href'])) {
        if (count($children) > 0) {
          $link['html'] = TRUE;
          $link['title'] .= ' <span class="caret"></span>';
          $output .=  '<a' . drupal_attributes($link['attributes']) . ' href="#">'. $link['title'] .'</a>';
        }
        else {
          // Pass in $link as $options, they share the same keys.
          $output .= l($link['title'], $link['href'], $link);
        }
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }

        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;

      if(count($children) > 0) {
        $attributes = array();
        $attributes['class'] = array('dropdown-menu');

        $output .= theme('bootstrap_links', array('links' => $children, 'attributes' => $attributes));
      }

      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * theme_bootstrap_btn_dropdown
 */
function theme_bootstrap_btn_dropdown($variables) {
  $type_class = '';
  $sub_links ='';

  $variables['attributes']['class'][] = 'btn-group';
  // Type class
  if (isset($variables['type'])) {
    $type_class = ' btn-'. $variables['type'];
  }

  // Start markup
  $output = '<div'. drupal_attributes($variables['attributes']) .'>';

  // Ad as string if its not a link
  if (is_array($variables['label'])) {
    $output .= l($variables['label']['title'], $$variables['label']['href'], $variables['label']);
  }

  $output .= '<a class="btn'. $type_class .' dropdown-toggle" data-toggle="dropdown" href="#">';

  // Its a link so create one
  if (is_string($variables['label'])) {
    $output .= check_plain($variables['label']);
  }

  if (is_array($variables['links'])) {
    $sub_links = theme('links', array('links' => $variables['links'],'attributes' => array('class' => array('dropdown-menu'))));
  }

  // Finish markup
  $output .= '<span class="caret"></span></a>' . $sub_links . '</div>';

  return $output;
}

/*
 * Overwrites the default item list to make it prettier
 */
function bootstrap_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];
  $output = '';

  if (isset($title)) {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme('item_list', array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }

  return $output;
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 */
function bootstrap_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
    'info' => t('Informative message'),
  );

  // Map Drupal message types to their corresponding Bootstrap classes.
  // @see http://twitter.github.com/bootstrap/components.html#alerts
  $status_class = array(
    'status' => 'success',
    'error' => 'error',
    'warning' => 'warning',
    // Not supported, but in theory a module could send any type of message.
    // @see drupal_set_message()
    // @see theme_status_messages()
    'info' => 'info',
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    $class = (isset($status_class[$type])) ? ' alert-' . $status_class[$type] : '';
    $output .= "<div class=\"alert alert-block$class\">\n";
    $output .= "  <a class=\"close\" data-dismiss=\"alert\" href=\"#\">&times;</a>\n";

    if (!empty($status_heading[$type])) {
      $output .= '<h4 class="element-invisible">' . $status_heading[$type] . "</h4>\n";
    }

    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }

    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Implements hook_css_alter().
 */
function bootstrap_css_alter(&$css) {
  $theme_path = drupal_get_path('theme', 'bootstrap');
  // Load excluded CSS files from theme.
  $excludes = _bootstrap_alter(bootstrap_theme_get_info('exclude'), 'css');
  // Add Bootstrap CDN file and overrides.
  if (theme_get_setting('cdn_bootstrap')){
    // Add CDN.
    $cdn = '//netdna.bootstrapcdn.com/twitter-bootstrap/'. theme_get_setting('cdn_bootstrap_version')  .'/css/bootstrap-combined.min.css';
    $css[$cdn] = array(
      'data' => $cdn,
      'type' => 'external',
      'every_page' => TRUE,
      'media' => 'all',
      'preprocess' => FALSE,
      'group' => CSS_THEME,
      'browsers' => array('IE' => TRUE, '!IE' => TRUE),
      'weight' => -2,
    );
    // Add overrides.
    $override = $theme_path . '/css/overrides.css';
    $css[$override] = array(
      'data' => $override,
      'type' => 'file',
      'every_page' => TRUE,
      'media' => 'all',
      'preprocess' => TRUE,
      'group' => CSS_THEME,
      'browsers' => array('IE' => TRUE, '!IE' => TRUE),
      'weight' => -1,
    );
  }
  $css = array_diff_key($css, $excludes);
}

/**
 * Implements hook_js_alter().
 */
function bootstrap_js_alter(&$js) {
  // Load excluded JS files from theme.
  $excludes = _bootstrap_alter(bootstrap_theme_get_info('exclude'), 'js');

  // If bootstrap_ui available, we should not add js from theme info file.
  if (module_exists('bootstrap_ui')) {
    libraries_load('bootstrap', 'minified');
  }

  $theme_path = drupal_get_path('theme', 'bootstrap');

  // Replace core progress bar JS with the Bootstrap equivilent.
  if (isset($js['misc/progress.js']) && !empty($js['misc/progress.js'])) {
    unset($js['misc/progress.js']);
    $progress = $theme_path . '/js/progress.js';
    $js[$progress] = drupal_js_defaults($progress);
  }

  // Fix broken Views AJAX pagers.
  if (module_exists('views') && !empty($js[drupal_get_path('module', 'views') . '/js/ajax_view.js'])) {
    // Override core ajax prototype function to append throbber inside links,
    // instead of after it (floating issues).
    $ajax = $theme_path . '/js/bootstrap_ajax.js';
    $js[$ajax] = drupal_js_defaults($ajax);
    $js[$ajax]['group'] = JS_THEME;
    // Override views prototype function to bind to Bootstrap pagination.
    $ajax_view = $theme_path . '/js/bootstrap_ajax_view.js';
    $js[$ajax_view] = drupal_js_defaults($ajax_view);
    $js[$ajax_view]['group'] = JS_THEME;
  }

  $js = array_diff_key($js, $excludes);

  // Add CDN.
  if (theme_get_setting('cdn_bootstrap')) {
    $cdn = '//netdna.bootstrapcdn.com/twitter-bootstrap/'. theme_get_setting('cdn_bootstrap_version')  .'/js/bootstrap.min.js';
    $js[$cdn] = drupal_js_defaults();
    $js[$cdn]['data'] = $cdn;
    $js[$cdn]['type'] = 'external';
    $js[$cdn]['every_page'] = TRUE;
    $js[$cdn]['weight'] = -100;
  }
}

function _bootstrap_alter($files, $type) {
  $output = array();

  foreach($files as $key => $value) {
    if (isset($files[$key][$type])) {
      foreach ($files[$key][$type] as $file => $name) {
        $output[$name] = FALSE;
      }
    }
  }
  return $output;
}

/**
 * Returns HTML for Bootstrap's progress bar.
 */
function bootstrap_progress_bar($variables) {
  $output = '<div id="progress" class="progress-wrapper">';
  $output .= '  <div class="progress progress-striped progress-info active">';
  $output .= '    <div class="bar" style="width: ' . $variables['percent'] . '%"></div>';
  $output .= '  </div>';
  $output .= '  <div class="percentage pull-right">' . $variables['percent'] . '%</div>';
  $output .= '  <div class="message">' . $variables['message'] . '</div>';
  $output .= '</div>';
  return $output;
}

/**
 * Returns HTML for Bootstrap's modal.
 */
function bootstrap_bootstrap_modal($variables) {
  $body = $variables['body'];
  $links = $variables['footer'];
  $heading = $variables['heading'];
  $attributes = $variables['attributes'];

  if (isset($variables['attributes']['class']) && is_string($variables['attributes']['class'])) { // Convert classes to an array.
    $variables['attributes']['class'] = explode(' ', $variables['attributes']['class']);
  }

  $variables['attributes']['class'][] = 'modal';

  $output = '<div'. drupal_attributes($variables['attributes']) .'>';
  $output .= '<div class="modal-header"> <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>';
  $output .= '<h3>'. $variables['html_heading']? $variables['heading'] : check_plain($variables['heading']) .'</h3>';
  $output .= '</div>';
  $output .= '<div class="modal-body">'. render($variables['body']) .'</div>';
  $output .= '<div class="modal-footer">'. render($variables['footer']) .'</div>';
  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML for Bootstrap's Collapse/Accordion.
 */
function bootstrap_bootstrap_accordion($variables) {
  $elements = $variables['elements'];

  if (empty($variables['id'])) {
    $accordion_id = 'accordion-'. md5($elements);
  }
  else {
    $accordion_id = check_plain($variables['id']);
  }

  $output = '<div class="accordion" id="'.$accordion_id.'">';

  foreach ($elements as $id => $item) {
    $output .= '<div class="accordion-group"><div class="accordion-heading">';
    $output .= '<a class="accordion-toggle" data-toggle="collapse" data-parent="#'. $accordion_id .'" href="#'. $id .'">'. check_plain($item['header']) .'</a></div>';
    $output .= '<div id="'. $id .'" class="accordion-body collapse in"><div class="accordion-inner">';
    $output .= render($item['content']);
    $output .= '</div></div></div>';
  }

  $output .= '</div>';

  return $output;
}

/**
 * Add stripping to tables (in case they don't have .table-no-striping class)
 */
function bootstrap_preprocess_table(&$variables) {

  if (isset($variables['attributes']['class']) && is_string($variables['attributes']['class'])) {
    // Convert classes to an array.
    $variables['attributes']['class'] = explode(' ', $variables['attributes']['class']);
  }

  $variables['attributes']['class'][] = 'table';
  if(!in_array('table-no-striping', $variables['attributes']['class'])) {
    $variables['attributes']['class'][] = 'table-striped';
  }

}
