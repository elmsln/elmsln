<?php

/**
 * @file
 *
 */

/**
 * Page callback for arguments configuration in path.
 */
function path_breadcrumbs_ui_configure_arguments_page($path_name, $keyword) {

  // Include ctools modal plugin.
  ctools_include('modal');

  // Set form state values for context selections.
  $form_state = array(
    'storage' => array(
      'path_name' => $path_name,
      'keyword' => $keyword,
    ),
  );

  // Load context selections form.
  $form = drupal_build_form('path_breadcrumbs_ui_argument_context_form', $form_state);

  // Wrap form into ctools modal.
  $commands = ctools_modal_form_render(array('title' => t('Choose argument')), $form);
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Page callback for settings form for arguments.
 *
 * @param $path_name
 * @param $keyword
 * @return array
 */
function path_breadcrumbs_ui_change_arguments_page($path_name, $keyword) {
  // Include ctools modal plugin.
  ctools_include('modal');

  $breadcrumb = path_breadcrumbs_object_cache_get($path_name);

  // Set form values for second step of context settings form.
  $form_state = array(
    'storage' => array(
      'step' => 2,
      'path_name' => $path_name,
      'keyword' => $keyword,
      'argument' => $breadcrumb->arguments[$keyword]['argument'],
    ),
  );

  $form = drupal_build_form('path_breadcrumbs_ui_argument_context_form', $form_state);
  $commands = ctools_modal_form_render(array('title' => t('Choose argument')), $form);
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Form for editing path breadcrumbs.
 */
function path_breadcrumbs_ui_edit_page($path_breadcrumb) {

  $page['content']['#prefix'] = '<div id="path-breadcrumbs-ui-wrapper" class="clearfix">';
  $page['content']['#suffix'] = '</div>';

  // Save form in cache.
  path_breadcrumbs_object_cache_set($path_breadcrumb->machine_name, $path_breadcrumb);

  $links[] = array(
    '#type' => 'link',
    '#title' => t('Basic'),
    '#href' => 'admin/structure/path-breadcrumbs/edit/' . $path_breadcrumb->machine_name . '/ajax/1',
    '#attributes' => array('class' => array('use-ajax', 'active')),
  );

  $links[] = array(
    '#type' => 'link',
    '#title' => t('Arguments'),
    '#href' => 'admin/structure/path-breadcrumbs/edit/' . $path_breadcrumb->machine_name . '/ajax/2',
    '#attributes' => array('class' => array('use-ajax')),
  );

  $links[] = array(
    '#type' => 'link',
    '#title' => t('Selection rules'),
    '#href' => 'admin/structure/path-breadcrumbs/edit/' . $path_breadcrumb->machine_name . '/ajax/3',
    '#attributes' => array('class' => array('use-ajax')),
  );

  $links[] = array(
    '#type' => 'link',
    '#title' => t('Breadcrumbs'),
    '#href' => 'admin/structure/path-breadcrumbs/edit/' . $path_breadcrumb->machine_name . '/ajax/4',
    '#attributes' => array('class' => array('use-ajax')),
  );

  $rendered_links = array();
  foreach ($links as $link) {
    $rendered_links[] = render($link);
  }

  $page['content']['menu'] = array(
    '#markup' => '<div id="path-breadcrumbs-ui-menu">' . theme('item_list', array('items' => $rendered_links)) . '</div>',
  );

  $form_state = array(
    'storage' => array(
      'machine_name' => $path_breadcrumb->machine_name,
      'step' => 1,
    ),
  );

  $form = drupal_build_form('path_breadcrumbs_ui_edit_form', $form_state);
  $page['content']['edit_form'] = array(
    '#markup' => render($form),
  );

  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module', 'path_breadcrumbs_ui') . '/css/path_breadcrumbs_ui.css');

  return $page;
}

/**
 * Ajax callback for path_breadcrumbs EDIT links.
 */
function path_breadcrumbs_ui_edit_form_ajax_links($breadcrumb, $step) {

  $form_state = array(
    'storage' => array(
      'machine_name' => $breadcrumb->machine_name,
      'step' => $step,
    ),
  );

  $form = drupal_build_form('path_breadcrumbs_ui_edit_form', $form_state);
  $commands = array();
  $commands[] = ajax_command_replace('#path-breadcrumbs-ui-form-wrapper', render($form));
  $commands[] = ajax_command_invoke('#path-breadcrumbs-ui-menu li a', 'removeClass', array('active'));
  $commands[] = ajax_command_invoke('#path-breadcrumbs-ui-menu li a:eq(' . --$step . ')', 'addClass', array('active'));
  $commands[] = ajax_command_prepend('#path-breadcrumbs-ui-form-wrapper', theme('status_messages'));
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Disables path breadcrumb.
 */
function path_breadcrumbs_ui_disable_breadcrumbs_page($path_breadcrumbs) {
  ctools_include('export');
  ctools_export_crud_disable('path_breadcrumbs', $path_breadcrumbs);
  cache_clear_all('path_breadcrumbs', 'cache', TRUE);

  drupal_set_message(t('Breadcrumb %name was disabled', array('%name' => $path_breadcrumbs->name)));

  drupal_goto('admin/structure/path-breadcrumbs');
}

/**
 * Enables path breadcrumb.
 */
function path_breadcrumbs_ui_enable_breadcrumbs_page($path_breadcrumbs) {

  // Update breadcrumb in database.
  ctools_include('export');
  ctools_export_crud_enable('path_breadcrumbs', $path_breadcrumbs);
  cache_clear_all('path_breadcrumbs', 'cache', TRUE);

  drupal_set_message(t('Breadcrumb %name was enabled', array('%name' => $path_breadcrumbs->name)));

  drupal_goto('admin/structure/path-breadcrumbs');
}

/**
 * AJAX callback for tokens autocomplete.
 */
function path_breadcrumbs_ui_tokens_ajax_autocomplete($path_breadcrumbs, $string) {

  // Check if path breadcrumbs object is loaded.
  if (empty($path_breadcrumbs)) {
    return;
  }

  // Build context substitutions.
  $contexts = array();
  if (!empty($path_breadcrumbs->arguments)) {

    // Include ctools library for contexts.
    ctools_include('context');

    foreach ($path_breadcrumbs->arguments as $keyword => $arg) {

      // Load argument plugin with its settings.
      $argument = ctools_get_argument($arg['argument']);
      if (isset($arg['settings'])) {
        $argument += $arg['settings'];
        $argument['id'] = 1;
      }

      // Load entity context.
      $contexts[$keyword] = ctools_context_get_context_from_argument($argument, $keyword, TRUE);
    }
  }

  $context_keywords = array();
  $raw_keywords = array();
  foreach ($contexts as $keyword => $context) {
    if ($context && $context->type) {
      $type = is_array($context->type) ? array_pop($context->type) : $context->type;
      $context_keywords[$context->original_argument] = $type;
    }
    else {
      $raw_keywords[$keyword] = array(
        'label' => t('Raw argument "@arg"', array('@arg' => $keyword)),
        'description' => $context->original_argument,
        'selector_sign' => '!',
      );
    }
  }

  // Default raw tokens.
  $raw_keywords['page_title'] = array('label' => t('Current page title'), 'description' => t('Current page title'), 'selector_sign' => '!');
  $raw_keywords['<front>'] = array('label' => t('Link to front page'), 'description' => t('Link to front page'), 'selector_sign' => '');
  $raw_keywords['<none>'] = array('label' => t('Empty value'), 'description' => t('Empty value'), 'selector_sign' => '');

  // Load class for autocomplete ui.
  $matches = PathBreadcrumbsUIAutocomplete::processAutocomplete($string, $context_keywords, $raw_keywords);

  drupal_json_output($matches);
}
