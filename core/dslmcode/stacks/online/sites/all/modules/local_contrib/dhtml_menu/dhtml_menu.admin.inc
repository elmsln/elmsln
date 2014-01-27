<?php
// $Id: dhtml_menu.admin.inc,v 1.22 2010/11/09 21:24:51 arancaytar Exp $


/**
 * @file dhtml_menu.admin.inc
 * Functions that are only called on the admin pages.
 */

/**
 * Module settings form.
 */
function dhtml_menu_settings($form, &$form_state) {
  $settings = variable_get('dhtml_menu_settings');

  $options['nav'] = array(
    '#type' => 'radios',
    '#title' => t('Static navigation'),
    '#options' => array(
      'open' => t('<strong>No Collapsing:</strong> Menu items cannot be collapsed dynamically. Instead, clicking on an already expanded item will take you to the page.'),
      'bullet' => t('<strong>Expand on Bullet:</strong> All links will continue to function as static links. To expand an item, click the bullet icon next to the link.'),
      'clone' => t('<strong>Cloned Menu Link:</strong> At the top of each menu, an extra link will be generated that leads to the page of the parent item.'),
      'hover' => t('<strong>Expand on Hover:</strong> Items expand when the cursor hovers over them. Links function normally. <em>This is unfamiliar and causes accessibility problems!</em>'),
      'double-click' => t('<strong>Doubleclick:</strong> To expand an item, click the link once. To navigate to the page, click it twice. <em>This will be difficult to find for your users!</em>'),
      'none' => t('<strong>None:</strong> Clicking the link will expand the item. Navigating to the page is not possible at all. <em>This will make pages with sub-items very difficult to reach!</em>'),
    ),
    '#default_value' => $settings['nav'],
    '#description' => t('Dynamic expansion of menus competes with the static navigation of content. Choose how to resolve this conflict.'),
  );

  $options['animation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Animation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $options['animation']['effects'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Effects'),
    '#options' => array(
      'height' => t('Slide in vertically'),
      'width' => t('Slide in horizontally'),
      'opacity' => t('Fade in'),
    ),
    '#description' => t('You may pick any number of animation effects that will accompany the opening and closing of a menu.'),
    '#default_value' => $settings['animation']['effects'],
  );

  $options['animation']['speed'] = array(
    '#type' => 'select',
    '#title' => t('Speed'),
    '#options' => array(
      100  => t('Very Fast (@seconds s)', array('@seconds' => 0.1)), 
      500  => t('Fast (@seconds s)', array('@seconds' => 0.5)), 
      1000 => t('Medium (@seconds s)', array('@seconds' => 1)),
      1500 => t('Slow (@seconds s)', array('@seconds' => 1.5)), 
      2000 => t('Very Slow (@seconds s)', array('@seconds' => 2)),
    ),
    '#default_value' => $settings['animation']['speed'],
    '#description' => t('Choose how quickly the menus should expand and collapse.'),
  );

  $options['effects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other effects'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $options['effects']['siblings'] = array(
    '#type' => 'radios',
    '#title' => t('When a menu opens'),
    '#options' => array(
      'none' => t('Keep other menus open.'),
      'close-all' => t('Close all other open menus on the page.'),
      'close-same-tree' => t('Close other open menus in the same tree.'),
    ),
    '#default_value' => $settings['effects']['siblings'],
  );

  $options['effects']['children'] = array(
    '#type' => 'radios',
    '#title' => t('When a menu closes'),
    '#options' => array(
      'none' => t('Remember which sub-items were expanded when it next opens.'),
      'close-children' => t('Close all its sub-items, too.'),
    ),
    '#default_value' => $settings['effects']['children'],
  );

  $options['effects']['remember'] = array(
    '#type' => 'radios',
    '#title' => t('When a new page is loaded'),
    '#options' => array(
      'remember' => t('Remember which items were expanded on the last page.'),
      0 => t('Expand only the currently active path.'),
    ),
    '#default_value' => $settings['effects']['remember'],
  );

  $options['filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Disabling DHTML'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $options['filter']['type'] = array(
    '#type' => 'radios',
    '#title' => t('Filter type'),
    '#options' => array(
      'blacklist' => t('Disable DHTML on the menus checked below.'),
      'whitelist' => t('Enable DHTML on the menus checked below.'),
    ),
    '#default_value' => $settings['filter']['type'],
  );

  $options['filter']['list'] = array(
    '#type' => 'checkboxes',
    '#title' => t('List'),
    '#options' => _dhtml_menu_menus(),
    '#default_value' => $settings['filter']['list'],
    '#description' => t('DHTML will be used for all menus by default, but can be switched off for specific menus.'),
  );

  $options['#tree'] = TRUE;
  $form['dhtml_menu_settings'] = $options;

  // Disable automatic defaults, which don't work with nested values.
  return system_settings_form($form, FALSE);
}

/**
 * Build a human-readable option list for all non-empty menus.
 * Custom menus and book menus are included if the respective modules are enabled.
 */
function _dhtml_menu_menus() {
  if (function_exists('menu_get_menus')) {
    // If the menu module is enabled, list custom menus.
    $menus = menu_get_menus();
  }
  else {
    // Otherwise, list only system menus.
    $menus = menu_list_system_menus();
  }

  // If the book module is enabled, also include book menus.
  if (function_exists('book_get_books')) {
    foreach (book_get_books() as $bid => $link) {
      $menus["book-toc-$bid"] = t('Book: %title', array('%title' => $link['title']));
    }
  }

  // menu_get_names() filters out empty menus, and adds any menus not found using the above calls (edge case).
  foreach (menu_get_names() as $menu) {
    $menu_names[$menu] = isset($menus[$menu]) ? $menus[$menu] : t('Other menu: %menu', array('%menu' => $menu));
  }

  return $menu_names;
}

