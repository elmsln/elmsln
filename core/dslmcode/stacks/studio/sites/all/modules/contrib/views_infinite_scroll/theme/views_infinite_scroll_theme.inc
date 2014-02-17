<?php
/**
 * @file
 * Theme infinite scroll page
 */
function theme_views_infinite_scroll_pager($variables) {
  $tags = $variables['tags'];
  $limit = isset($variables['limit']) ? $variables['limit'] : 10;
  $view_name = $variables['view_name'];
  $element = isset($variables['element']) ? $variables['element'] : 0;
  $current_display = $variables['current_display'];
  $content_selector = isset($variables['content_selector']) ? $variables['content_selector'] : 'div.view-content';
  $items_selector = isset($variables['items_selector']) ? $variables['items_selector'] : 'div.view-content .views-row';
  $img_path = $variables['img_path'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];

  $PAGER_CLASS = 'pager';
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  $li_previous = theme('pager_previous',
    array(
      'text' => (isset($tags[1]) ? $tags[1] : t('‹‹')),
      'limit' => $limit,
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
    )
  );
  if (empty($li_previous)) {
    $li_previous = "&nbsp;";
  }

  $li_next = theme('pager_next',
    array(
      'text' => (isset($tags[3]) ? $tags[3] : t('››')),
      'limit' => $limit,
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
    )
  );
  if (empty($li_next)) {
    $li_next = "&nbsp;";
  }


  if ($pager_total[$element] > 1) {
    $items[] = array(
      'class' => array('pager-previous'),
      'data' => $li_previous,
    );

    $items[] = array(
      'class' => array('pager-current'),
      'data' => t('@current of @max', array('@current' => $pager_current, '@max' => $pager_max)),
    );

    $items[] = array(
      'class' => array('pager-next'),
      'data' => $li_next,
    );

    $settings = array(
      'views_infinite_scroll' => array(
        array(
          'view_name' => $view_name,
          'display' => $current_display,
          'pager_selector' => 'ul.' . $PAGER_CLASS,
          'next_selector' => 'li.pager-next a:first',
          'content_selector' => $content_selector,
          'items_selector' => $items_selector,
          'img_path' => $img_path,
        ),
      ),
    );
    drupal_add_css(drupal_get_path('module', 'views_infinite_scroll') . '/css/views_infinite_scroll.css');
    drupal_add_js($settings, array('type' => 'setting', 'scope' => JS_DEFAULT));

    // Add Autopager jQuery plugin
    // If libraries module is installed, check for the plugin in libraries dir.
    if (module_exists('libraries') && file_exists(libraries_get_path('autopager') .'/jquery.autopager-1.0.0.js')) {
      drupal_add_js(libraries_get_path('autopager') .'/jquery.autopager-1.0.0.js');
    }
    // else, load it from views_infinite_scroll/js dir.
    else {
      $autopager_module_path = drupal_get_path('module', 'views_infinite_scroll') . '/js/jquery.autopager-1.0.0.js';
      drupal_add_js($autopager_module_path);
    }

    drupal_add_js(drupal_get_path('module', 'views_infinite_scroll') . '/js/views_infinite_scroll.js');

    return theme('item_list', array('items' => $items, 'title' => NULL, 'type' => 'ul', 'attributes' => array('class' => array($PAGER_CLASS))));
  }
}
