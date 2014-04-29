<?php
/*
 * Implements hook_preprocess_html().
 */
function rubik_preprocess_html(&$vars) {
  if (theme_get_setting('rubik_inline_field_descriptions')) {
    $vars['classes_array'][] = 'rubik-inline-field-descriptions';
  }
}

/**
 * Implements hook_css_alter().
 * @TODO: Do this in .info once http://drupal.org/node/575298 is committed.
 */
function rubik_css_alter(&$css) {
  if (isset($css['modules/overlay/overlay-child.css'])) {
    $css['modules/overlay/overlay-child.css']['data'] = drupal_get_path('theme', 'rubik') . '/overlay-child.css';
  }
  if (isset($css['modules/shortcut/shortcut.css'])) {
    $css['modules/shortcut/shortcut.css']['data'] = drupal_get_path('theme', 'rubik') . '/shortcut.css';
  }
}

/**
 * Implementation of hook_theme().
 */
function rubik_theme() {
  $items = array();

  // Content theming.
  $items['help'] =
  $items['node'] =
  $items['comment'] =
  $items['comment_wrapper'] = array(
    'path' => drupal_get_path('theme', 'rubik') .'/templates',
    'template' => 'object',
  );
  $items['node']['template'] = 'node';

  // Help pages really need help. See preprocess_page().
  $items['help_page'] = array(
    'variables' => array('content' => array()),
    'path' => drupal_get_path('theme', 'rubik') .'/templates',
    'template' => 'object',
    'preprocess functions' => array(
      'template_preprocess',
      'rubik_preprocess_help_page',
    ),
    'process functions' => array('template_process'),
  );

  if (!theme_get_setting('rubik_disable_sidebar_in_form')) {
    // Form layout: default (2 column).
    $items['block_add_block_form'] =
    $items['block_admin_configure'] =
    $items['comment_form'] =
    $items['contact_admin_edit'] =
    $items['contact_mail_page'] =
    $items['contact_mail_user'] =
    $items['filter_admin_format_form'] =
    $items['forum_form'] =
    $items['locale_languages_edit_form'] =
    $items['menu_edit_menu'] =
    $items['menu_edit_item'] =
    $items['node_type_form'] =
    $items['path_admin_form'] =
    $items['system_settings_form'] =
    $items['system_themes_form'] =
    $items['system_modules'] =
    $items['system_actions_configure'] =
    $items['taxonomy_form_term'] =
    $items['taxonomy_form_vocabulary'] =
    $items['user_profile_form'] =
    $items['user_admin_access_add_form'] = array(
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'rubik') .'/templates',
      'template' => 'form-default',
      'preprocess functions' => array(
        'rubik_preprocess_form_buttons',
      ),
    );

    // These forms require additional massaging.
    $items['confirm_form'] = array(
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'rubik') .'/templates',
      'template' => 'form-simple',
      'preprocess functions' => array(
        'rubik_preprocess_form_confirm'
      ),
    );
    $items['node_form'] = array(
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'rubik') .'/templates',
      'template' => 'form-default',
      'preprocess functions' => array(
        'rubik_preprocess_form_buttons',
        'rubik_preprocess_form_node',
      ),
    );
  }
  return $items;
}

/**
 * Preprocessor for theme('page').
 */
function rubik_preprocess_page(&$vars) {
  // Show a warning if base theme is not present.
  if (!function_exists('tao_theme') && user_access('administer site configuration')) {
    drupal_set_message(t('The Rubik theme requires the !tao base theme in order to work properly.', array('!tao' => l('Tao', 'http://drupal.org/project/tao'))), 'warning');
  }

  // Set a page icon class.
  $vars['page_icon_class'] = ($item = menu_get_item()) ? implode(' ' , _rubik_icon_classes($item['href'])) : '';

  // Help pages. They really do need help.
  if (strpos($_GET['q'], 'admin/help/') === 0 && isset($vars['page']['content']['system_main']['main']['#markup'])) {
    $vars['page']['content']['system_main']['main']['#markup'] = theme('help_page', array('content' => $vars['page']['content']['system_main']['main']['#markup']));
  }

  // Clear out help text if empty.
  if (empty($vars['help']) || !(strip_tags($vars['help']))) {
    $vars['help'] = '';
  }

  // Process local tasks. This will get called for rubik and its subthemes.
  _rubik_local_tasks($vars);

  // Overlay is enabled.
  $vars['overlay'] = (module_exists('overlay') && overlay_get_mode() === 'child');
}

/**
 * Preprocessor for theme('fieldset').
 */
function rubik_preprocess_fieldset(&$vars) {
  if (!empty($vars['element']['#collapsible'])) {
    $vars['title'] = "<span class='icon'></span>" . $vars['title'];
  }
}

/**
 * Preprocessor for handling form button for most forms.
 */
function rubik_preprocess_form_buttons(&$vars) {
  if (!empty($vars['form']['actions'])) {
    $vars['actions'] = $vars['form']['actions'];
    unset($vars['form']['actions']);
  }
}

/**
 * Preprocessor for theme('confirm_form').
 */
function rubik_preprocess_form_confirm(&$vars) {
  // Move the title from the page title (usually too big and unwieldy)
  $title = filter_xss_admin(drupal_get_title());
  $vars['form']['description']['#type'] = 'item';
  $vars['form']['description']['#value'] = empty($vars['form']['description']['#value']) ?
    "<strong>{$title}</strong>" :
    "<strong>{$title}</strong><p>{$vars['form']['description']['#value']}</p>";
  drupal_set_title(t('Please confirm'));
}

/**
 * Preprocessor for theme('node_form').
 */
function rubik_preprocess_form_node(&$vars) {
  $vars['sidebar'] = isset($vars['sidebar']) ? $vars['sidebar'] : array();
  // Support field_group if present.
  if (module_exists('field_group')) {
    $map = array(
      'group_sidebar' => 'sidebar',
      'group_footer' => 'footer',
    );
  }
  // Support nodeformcols if present.
  elseif (module_exists('nodeformcols')) {
    $map = array(
      'nodeformcols_region_right' => 'sidebar',
      'nodeformcols_region_footer' => 'footer',
      'nodeformcols_region_main' => NULL,
    );
  }
    if (isset($map)) {
    foreach ($map as $region => $target) {
      if (isset($vars['form'][$region])) {
        if (isset($vars['form'][$region]['#prefix'], $vars['form'][$region]['#suffix'])) {
          unset($vars['form'][$region]['#prefix']);
          unset($vars['form'][$region]['#suffix']);
        }
        if (isset($vars['form'][$region]['actions'], $vars['form'][$region]['actions'])) {
          $vars['actions'] = $vars['form'][$region]['actions'];
          unset($vars['form'][$region]['actions']);
        }
        if (isset($target)) {
          $vars[$target] = $vars['form'][$region];
          unset($vars['form'][$region]);
        }
      }
    }
  }
  // Default to showing taxonomy in sidebar if nodeformcols is not present.
  elseif (isset($vars['form']['taxonomy']) && empty($vars['sidebar'])) {
    $vars['sidebar']['taxonomy'] = $vars['form']['taxonomy'];
    unset($vars['form']['taxonomy']);
  }
}

/**
 * Preprocessor for theme('button').
 */
function rubik_preprocess_button(&$vars) {
  if (isset($vars['element']['#value'])) {
    $classes = array(
      t('Save') => 'yes',
      t('Submit') => 'yes',
      t('Yes') => 'yes',
      t('Add') => 'add',
      t('Delete') => 'remove',
      t('Remove') => 'remove',
      t('Cancel') => 'no',
      t('No') => 'no',
    );
    foreach ($classes as $search => $class) {
      if (strpos($vars['element']['#value'], $search) !== FALSE) {
        $vars['element']['#attributes']['class'][] = 'button-' . $class;
        break;
      }
    }
  }
}

/**
 * Preprocessor for theme('help').
 */
function rubik_preprocess_help(&$vars) {
  $vars['hook'] = 'help';
  $vars['attr']['id'] = 'help-text';
  $class = 'path-admin-help clear-block toggleable';
  $vars['attr']['class'] = isset($vars['attr']['class']) ? "{$vars['attr']['class']} $class" : $class;
  $help = menu_get_active_help();
  if (($test = strip_tags($help)) && !empty($help)) {
    // Thankfully this is static cached.
    $vars['attr']['class'] .= menu_secondary_local_tasks() ? ' with-tabs' : '';

    $vars['is_prose'] = TRUE;
    $vars['layout'] = TRUE;
    $vars['content'] = "<span class='icon'></span>" . $help;

    // Link to help section.
    $item = menu_get_item('admin/help');
    if ($item && $item['path'] === 'admin/help' && $item['access']) {
      $vars['links'] = l(t('More help topics'), 'admin/help');
    }
  }
}

/**
 * Preprocessor for theme('help_page').
 */
function rubik_preprocess_help_page(&$vars) {
  $vars['hook'] = 'help-page';

  $vars['title_attributes_array']['class'][] = 'help-page-title';
  $vars['title_attributes_array']['class'][] = 'clearfix';

  $vars['content_attributes_array']['class'][] = 'help-page-content';
  $vars['content_attributes_array']['class'][] = 'clearfix';
  $vars['content_attributes_array']['class'][] = 'prose';

  $vars['layout'] = TRUE;

  // Truly hackish way to navigate help pages.
  $module_info = system_rebuild_module_data();
  $empty_arg = drupal_help_arg();
  $modules = array();
  foreach (module_implements('help', TRUE) as $module) {
    if (module_invoke($module, 'help', "admin/help#$module", $empty_arg)) {
      $modules[$module] = $module_info[$module]->info['name'];
    }
  }
  asort($modules);

  $links = array();
  foreach ($modules as $module => $name) {
    $links[] = array('title' => $name, 'href' => "admin/help/{$module}");
  }
  $vars['links'] = theme('links', array('links' => $links));
}

/**
 * Preprocessor for theme('node').
 */
function rubik_preprocess_node(&$vars) {
  $vars['layout'] = TRUE;
  if ($vars['display_submitted']) {
    $vars['submitted'] = _rubik_submitted($vars['node']);
  }
}

/**
 * Preprocessor for theme('comment').
 */
function rubik_preprocess_comment(&$vars) {
  $vars['layout'] = TRUE;
  $vars['submitted'] = _rubik_submitted($vars['comment']);
}

/**
 * Preprocessor for theme('comment_wrapper').
 */
function rubik_preprocess_comment_wrapper(&$vars) {
  $vars['hook'] = 'box';
  $vars['layout'] = FALSE;
  $vars['title'] = t('Comments');

  $vars['attributes_array']['id'] = 'comments';

  $vars['title_attributes_array']['class'][] = 'box-title';
  $vars['title_attributes_array']['class'][] = 'clearfix';

  $vars['content_attributes_array']['class'][] = 'box-content';
  $vars['content_attributes_array']['class'][] = 'clearfix';
  $vars['content_attributes_array']['class'][] = 'prose';

  $vars['content'] = drupal_render_children($vars['content']);
}

/**
 * Preprocessor for theme('admin_block').
 */
function rubik_preprocess_admin_block(&$vars) {
  // Add icon and classes to admin block titles.
  if (isset($vars['block']['href'])) {
    $vars['block']['localized_options']['attributes']['class'] =  _rubik_icon_classes($vars['block']['href']);
  }
  $vars['block']['localized_options']['html'] = TRUE;
  if (isset($vars['block']['link_title'])) {
    $vars['block']['title'] = l("<span class='icon'></span>" . filter_xss_admin($vars['block']['title']), $vars['block']['href'], $vars['block']['localized_options']);
  }

  if (empty($vars['block']['content'])) {
    $vars['block']['content'] = "<div class='admin-block-description description'>{$vars['block']['description']}</div>";
  }
}

/**
 * Override of theme('breadcrumb').
 */
function rubik_breadcrumb($vars) {
  $output = '';

  // Add current page onto the end.
  if (!drupal_is_front_page()) {
    $item = menu_get_item();
    $end = end($vars['breadcrumb']);
    if ($end && strip_tags($end) !== $item['title']) {
      $vars['breadcrumb'][] = check_plain($item['title']);
    }
  }

  // Optional: Add the site name to the front of the stack.
  if (!empty($vars['prepend'])) {
    $site_name = empty($vars['breadcrumb']) ? "<strong>". check_plain(variable_get('site_name', '')) ."</strong>" : l(variable_get('site_name', ''), '<front>', array('purl' => array('disabled' => TRUE)));
    array_unshift($vars['breadcrumb'], $site_name);
  }

  $depth = 0;
  foreach ($vars['breadcrumb'] as $link) {

    // If the item isn't a link, surround it with a strong tag to format it like
    // one.
    if (!preg_match('/^<a/', $link) && !preg_match('/^<strong/', $link)) {
      $link = '<strong>' . $link . '</strong>';
    }

    $output .= "<span class='breadcrumb-link breadcrumb-depth-{$depth}'>{$link}</span>";
    $depth++;
  }
  return $output;
}

/**
 * Override of theme('filter_guidelines').
 */
function rubik_filter_guidelines($variables) {
  return '';
}

/**
 * Override of theme('node_add_list').
 */
function rubik_node_add_list($vars) {
  $content = $vars['content'];

  $output = "<ul class='admin-list'>";
  if ($content) {
    foreach ($content as $item) {
      $item['title'] = "<span class='icon'></span>" . filter_xss_admin($item['title']);
      if (isset($item['localized_options']['attributes']['class'])) {
        $item['localized_options']['attributes']['class'] += _rubik_icon_classes($item['href']);
      }
      else {
        $item['localized_options']['attributes']['class'] = _rubik_icon_classes($item['href']);
      }
      $item['localized_options']['html'] = TRUE;
      $output .= "<li>";
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      $output .= '<div class="description">'. filter_xss_admin($item['description']) .'</div>';
      $output .= "</li>";
    }
  }
  $output .= "</ul>";
  return $output;
}

/**
 * Override of theme_admin_block_content().
 */
function rubik_admin_block_content($vars) {
  $content = $vars['content'];

  $output = '';
  if (!empty($content)) {

    foreach ($content as $k => $item) {

      //-- Safety check for invalid clients of the function
      if (empty($content[$k]['localized_options']['attributes']['class'])) {
        $content[$k]['localized_options']['attributes']['class'] = array();
      }
      if (!is_array($content[$k]['localized_options']['attributes']['class'])) {
        $content[$k]['localized_options']['attributes']['class'] = array($content[$k]['localized_options']['attributes']['class']);
      }

      $content[$k]['title'] = "<span class='icon'></span>" . filter_xss_admin($item['title']);
      $content[$k]['localized_options']['html'] = TRUE;
      if (!empty($content[$k]['localized_options']['attributes']['class'])) {
        $content[$k]['localized_options']['attributes']['class'] += _rubik_icon_classes($item['href']);
      }
      else {
        $content[$k]['localized_options']['attributes']['class'] = _rubik_icon_classes($item['href']);
      }
    }
    $output = system_admin_compact_mode() ? '<ul class="admin-list admin-list-compact">' : '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="leaf">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= "<div class='description'>{$item['description']}</div>";
      }
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  return $output;
}

/**
 * Override of theme('admin_drilldown_menu_item_link').
 */
function rubik_admin_drilldown_menu_item_link($link) {
  $link['localized_options'] = empty($link['localized_options']) ? array() : $link['localized_options'];
  $link['localized_options']['html'] = TRUE;
  if (!isset($link['localized_options']['attributes']['class'])) {
    $link['localized_options']['attributes']['class'] = _rubik_icon_classes($link['href']);
  }
  else {
    $link['localized_options']['attributes']['class'] += _rubik_icon_classes($link['href']);
  }
  $link['description'] = check_plain(truncate_utf8(strip_tags($link['description']), 150, TRUE, TRUE));
  $link['description'] = "<span class='icon'></span>" . $link['description'];
  $link['title'] .= !empty($link['description']) ? "<span class='menu-description'>{$link['description']}</span>" : '';
  $link['title'] = filter_xss_admin($link['title']);
  return l($link['title'], $link['href'], $link['localized_options']);
}

/**
 * Preprocessor for theme('textfield').
 */
function rubik_preprocess_textfield(&$vars) {
  if ($vars['element']['#size'] >= 30 && empty($vars['element']['#field_prefix']) && empty($vars['element']['#field_suffix'])) {
    $vars['element']['#size'] = '';
    if (!isset($vars['element']['#attributes']['class'])
      || !is_array($vars['element']['#attributes']['class'])) {
       $vars['element']['#attributes']['class'] = array();
    }
    $vars['element']['#attributes']['class'][] = 'fluid';
  }
}

/**
 * Override of theme('menu_local_task').
 */
function rubik_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  // Render child tasks if available.
  $children = '';
  if (element_children($variables['element'])) {
    $children = drupal_render_children($variables['element']);
    $children = "<ul class='secondary-tabs links clearfix'>{$children}</ul>";
  }

  return '<li' . (!empty($variables['element']['#active']) ? ' class="active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . $children . "</li>\n";
}

/**
 * Helper function for cloning and drupal_render()'ing elements.
 */
function rubik_render_clone($elements) {
  static $instance;
  if (!isset($instance)) {
    $instance = 1;
  }
  foreach (element_children($elements) as $key) {
    if (isset($elements[$key]['#id'])) {
      $elements[$key]['#id'] = "{$elements[$key]['#id']}-{$instance}";
    }
  }
  $instance++;
  return drupal_render($elements);
}

function rubik_form_field_ui_field_edit_form_alter(&$form, &$form_state) { 
  $rubik_sidebar_field_ui = theme_get_setting('rubik_sidebar_field_ui', 'rubik');
  $rubik_disable_sidebar_in_form = theme_get_setting('rubik_disable_sidebar_in_form', 'rubik');
    if ($rubik_sidebar_field_ui == 1 && $rubik_disable_sidebar_in_form == 0) {
      $options = array(
        'default' => t('Default'),
        'rubik_sidebar_field' => t('Sidebar'),
      );
      $default = (isset($form_state['build_info']['args'][0]['rubik_edit_field_display'])) ? $form_state['build_info']['args'][0]['rubik_edit_field_display'] : 'default';
      $form['instance']['rubik_edit_field_display'] = array(
        '#type' => 'radios',
        '#title' => t('Set field display location'),
        '#description' => t('Choose where this field should be displayed.'),
        '#default_value' => $default,
        '#options' => $options,
      );
    }
  }

  function rubik_form_node_form_alter(&$form, $form_state) {
    $rubik_sidebar_field_ui = theme_get_setting('rubik_sidebar_field_ui', 'rubik');
    if ($rubik_sidebar_field_ui == TRUE) {
      if (isset($form_state['field']) && is_array($form_state['field'])) {
        foreach ($form_state['field'] AS $name => $field) {
          if (!isset($field[LANGUAGE_NONE]['instance'])) {
            continue;
          }
          if (isset($field[LANGUAGE_NONE]['instance']['rubik_edit_field_display'])) {
            $display = $field[LANGUAGE_NONE]['instance']['rubik_edit_field_display'];
            if ($display == 'rubik_sidebar_field') {
              $form[$name]['#attributes']['class'][] = 'rubik_sidebar_field';
            }
          }
        }
      }
    }
  }

/**
 * Helper function to submitted info theming functions.
 */
function _rubik_submitted($node) {
  $byline = t('Posted by !username', array('!username' => theme('username', array('account' => $node))));
  $date = format_date($node->created, 'small');
  return "<div class='byline'>{$byline}</div><div class='date'>$date</div>";
}

/**
 * Generate an icon class from a path.
 */
function _rubik_icon_classes($path) {
  $classes = array();
  $args = explode('/', $path);
  if ($args[0] === 'admin' || (count($args) > 1 && $args[0] === 'node' && $args[1] === 'add')) {
    // Add a class specifically for the current path that allows non-cascading
    // style targeting.
    $classes[] = 'path-'. str_replace('/', '-', implode('/', $args)) . '-';
    while (count($args)) {
      $classes[] = drupal_html_class('path-'. str_replace('/', '-', implode('/', $args)));
      array_pop($args);
    }
    return $classes;
  }
  return array();
}

function _rubik_local_tasks(&$vars) {
  if (!empty($vars['secondary_local_tasks']) && is_array($vars['primary_local_tasks'])) {
    foreach ($vars['primary_local_tasks'] as $key => $element) {
      if (!empty($element['#active'])) {
        $vars['primary_local_tasks'][$key] = $vars['primary_local_tasks'][$key] + $vars['secondary_local_tasks'];
        break;
      }
    }
  }
}

