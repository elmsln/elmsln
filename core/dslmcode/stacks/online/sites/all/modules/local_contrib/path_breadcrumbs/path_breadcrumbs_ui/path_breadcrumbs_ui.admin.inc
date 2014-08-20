<?php

/**
 * @file
 * Administrative callbacks for PATH BREADCRUMBS UI module.
 */

/**
 * Page callback for module settings page.
 */
function path_breadcrumbs_ui_breadcrumbs_list($form, &$form_state) {

  // Load path breadcrumbs.
  $result = path_breadcrumbs_load_all();

  $form_state['storage']['objects'] = $result;
  $form['#tree'] = TRUE;

  foreach ($result as $path) {
    $form[$path->machine_name]['title']['#markup'] = $path->name;
    // If object is overwritten.
    if ($path->is_overwritten) {
      $form[$path->machine_name]['title']['#markup'] .= '<sup>' . $path->type . '</sup>';
    }
    $form[$path->machine_name]['name']['#markup'] = $path->machine_name;
    $form[$path->machine_name]['path']['#markup'] = $path->path;
    // All paths are in $form_state['values']['paths'].
    $form[$path->machine_name]['#parents'] = array('paths', $path->machine_name);

    // Create operations for current breadcrumb.
    $operations = array();

    if ($path->disabled == TRUE) {
      $operations[] = array(
        'title' => t('Enable'),
        'href' => 'admin/structure/path-breadcrumbs/enable/' . $path->machine_name,
      );
    }

    $operations[] = array(
      'title' => t('Edit'),
      'href' => 'admin/structure/path-breadcrumbs/edit/' . $path->machine_name,
    );
    $operations[] = array(
      'title' => t('Clone'),
      'href' => 'admin/structure/path-breadcrumbs/clone/' . $path->machine_name,
    );
    $operations[] = array(
      'title' => t('Export'),
      'href' => 'admin/structure/path-breadcrumbs/export/' . $path->machine_name,
    );
    if (empty($path->in_code_only)) {
      $operations[] = array(
        'title' => $path->is_overwritten ? t('Revert') : t('Delete'),
        'href' => 'admin/structure/path-breadcrumbs/delete/' . $path->machine_name,
      );
    }

    if ($path->disabled == FALSE) {
      $operations[] = array(
        'title' => t('Disable'),
        'href' => 'admin/structure/path-breadcrumbs/disable/' . $path->machine_name,
      );
    }

    $form[$path->machine_name]['actions'] = array(
      '#theme' => 'links__ctools_dropbutton',
      '#links' => $operations,
      '#attributes' => array('class' => array('links', 'inline')),
    );

    $form[$path->machine_name]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $path->weight,
      '#delta' => 100,
      '#attributes' => array('class' => array('path-breadcrumbs-ui-table-weight')),
    );

    $form[$path->machine_name]['disabled'] = array(
      '#type' => 'value',
      '#value' => $path->disabled,
    );
  }

  $form['actions'] = array(
    '#type' => 'action',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'path_breadcrumbs_ui') . '/css/path_breadcrumbs_ui.css';

  return $form;
}

/**
 * Submit callback for path_breadcrumbs_ui_breadcrumbs_list form.
 */
function path_breadcrumbs_ui_breadcrumbs_list_submit($form, &$form_state) {
  if (!empty($form_state['values']['paths'])) {
    foreach ($form_state['values']['paths'] as $machine_name => $value) {
      if (isset($value['weight'])) {
        $path_breadcrumbs = $form_state['storage']['objects'][$machine_name];
        $path_breadcrumbs->weight = $value['weight'];
        path_breadcrumbs_save($path_breadcrumbs);
      }
    }
  }

  drupal_set_message(t('Path Breadcrumbs was updated.'));
}

/**
 * Path Breadcrumbs settings form.
 */
function path_breadcrumbs_ui_settings($form, $form_state) {

  // Theme settings.
  $form['path_breadcrumbs_theme'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theming settings'),
    '#description' => t('Additional theme settings for all site breadcrumbs. You have to enable option "%option" to use Path Breadcrumbs theming features.', array('%option' => t('Use module breadcrumbs render function'))),
  );

  $form['path_breadcrumbs_theme']['path_breadcrumbs_internal_render'] = array(
    '#type' => 'checkbox',
    '#title' => '<strong>' . t('Use module breadcrumbs render function') . '</strong>',
    '#default_value' => variable_get('path_breadcrumbs_internal_render', 1),
    '#description' => t("If this value checked module will replace system or theme breadcrumb render function by module's one.<br/>Note that if this checkbox is unchecked module will not be able to implement settings below."),
  );

  $form['path_breadcrumbs_theme']['themes_fieldset'] = array(
    '#type' => 'fieldset',
    '#collapsed' => !count(variable_get('path_breadcrumbs_internal_render_themes', array())),
    '#collapsible' => TRUE,
    '#title' => t('Per theme settings'),
  );

  $form['path_breadcrumbs_theme']['themes_fieldset']['path_breadcrumbs_internal_render_themes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Use internal Path Breadcrumbs rendering only for specific themes'),
    '#options' => _path_breadcrumbs_themes_option_list(),
    '#default_value' => variable_get('path_breadcrumbs_internal_render_themes', array()),
    '#description' => t('If you select no themes, there will be no specific limitation for Path Breadcrumbs render function.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="path_breadcrumbs_internal_render"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['path_breadcrumbs_theme']['path_breadcrumbs_delimiter'] = array(
    '#type' => 'textfield',
    '#title' => t('Delimiter'),
    '#default_value' => variable_get('path_breadcrumbs_delimiter', '»'),
    '#size' => 3,
    '#description' => t('Symbol that separates breadcrumbs.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="path_breadcrumbs_internal_render"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['path_breadcrumbs_theme']['path_breadcrumbs_rich_snippets'] = array(
    '#type' => 'select',
    '#title' => t('Rich snippets support'),
    '#options' => array(
      PATH_BREADCRUMBS_RICH_SNIPPETS_DISABLED => t('Disabled'),
      PATH_BREADCRUMBS_RICH_SNIPPETS_RDFA => t('RDFa'),
      PATH_BREADCRUMBS_RICH_SNIPPETS_MICRODATA => t('Microdata'),
    ),
    '#default_value' => variable_get('path_breadcrumbs_rich_snippets', PATH_BREADCRUMBS_RICH_SNIPPETS_DISABLED),
    '#description' => t('Provides rich snippets support for breadcrumbs. It is important to build a structure of a site in the SERP.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="path_breadcrumbs_internal_render"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['path_breadcrumbs_theme']['path_breadcrumbs_hide_single_breadcrumb'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide breadcrumbs navigation for single breadcrumb'),
    '#default_value' => variable_get('path_breadcrumbs_hide_single_breadcrumb', 0),
    '#description' => t('If breacrumbs navigation contains only one breadcrumb then breadcrumb navigation will be hidden.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="path_breadcrumbs_internal_render"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Cache settings.
  $form['path_breadcrumbs_cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Performance settings'),
  );

  $form['path_breadcrumbs_cache']['path_breadcrumbs_cache_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable cache for the breadcrumbs'),
    '#description' => t("Enables caching of breadcrumb's navigations. Use only on production sites."),
    '#default_value' => variable_get('path_breadcrumbs_cache_enabled', FALSE),
  );

  $form['path_breadcrumbs_cache']['path_breadcrumbs_cache_lifetime'] = array(
    '#type' => 'select',
    '#title' => t('Cache lifetime'),
    '#options' => array(
      CACHE_PERMANENT => t('Permanent'),
      CACHE_TEMPORARY => t('Temporary'),
      60 * 5 => t('@amount minutes', array('@amount' => 5)),
      60 * 15 => t('@amount minutes', array('@amount' => 15)),
      60 * 30 => t('@amount minutes', array('@amount' => 30)),
      60 * 60 => t('@amount minutes', array('@amount' => 60)),
      60 * 60 * 2 => t('@amount hours', array('@amount' => 2)),
      60 * 60 * 4 => t('@amount hours', array('@amount' => 4)),
      60 * 60 * 8 => t('@amount hours', array('@amount' => 8)),
      60 * 60 * 12 => t('@amount hours', array('@amount' => 12)),
      60 * 60 * 24 => t('@amount hours', array('@amount' => 24)),
      60 * 60 * 24 * 3 => t('@amount days', array('@amount' => 3)),
      60 * 60 * 24 * 7 => t('@amount days', array('@amount' => 7)),
    ),
    '#description' => t('You can read more information about cache settings <a href="@url">here</a>.', array(
      '@url' => url('http://api.drupal.org/api/drupal/includes!cache.inc/function/cache_set/7', array('external' => TRUE)),
    )),
    '#default_value' => variable_get('path_breadcrumbs_cache_lifetime', CACHE_PERMANENT),
  );

  // Home link settings.
  $form['path_breadcrumbs_home_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Home link settings'),
  );

  $form['path_breadcrumbs_home_link']['path_breadcrumbs_home_link_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prepend breadcrumbs with a home link by default'),
    '#default_value' => variable_get('path_breadcrumbs_home_link_enabled', 1),
    '#description' => t('This value does not changes current breadcrumbs navigation. It is just set default value for new path breadcrumbs.'),
  );

  $form['path_breadcrumbs_home_link']['path_breadcrumbs_home_link_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Home link title'),
    '#default_value' => variable_get('path_breadcrumbs_home_link_title', 'Home'),
    '#description' => t('Title of the link that points to the front page.'),
    '#size' => 30,
  );

  // Other settings.
  $form['path_breadcrumbs_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other settings'),
  );

  $url_cleaning_method_options = array(
    'none' => t('Disabled'),
    'ctools' => t('CTools'),
  );
  $url_cleaning_method_help[] = t('CTools method: transliterate (if <a href="@url">Transliteration</a> enabled), lower case, replace whitespace with "-".', array('@url' => 'https://drupal.org/project/transliteration'));

  if (module_exists('pathauto')) {
    $url_cleaning_method_options['pathauto'] = t('Pathauto');
    $url_cleaning_method_help[] = t('Pathauto method: clean with <a href="@url">Pathauto settings</a>.', array('@url' => url('admin/config/search/path/settings', array( 'query' => array('destination' => current_path()) ))));
  }
  else {
    $url_cleaning_method_help[] = t('Pathauto method (disabled): clean with <a href="@url">Pathauto module</a>.', array('@url' => 'https://drupal.org/project/pathauto'));
  }

  $url_cleaning_method_help = '<p>' . implode('<br />', $url_cleaning_method_help) . '</p>';

  $form['path_breadcrumbs_settings']['path_breadcrumbs_url_cleaning_method'] = array(
    '#type' => 'select',
    '#title' => t('URL path cleaning method'),
    '#default_value' => variable_get('path_breadcrumbs_url_cleaning_method', 'none'),
    '#options' => $url_cleaning_method_options,
    '#description' => $url_cleaning_method_help . t('Choose the path cleaning method to be applied to URLs in Path Breadcrumbs.'),
  );

  $form['path_breadcrumbs_settings']['path_breadcrumbs_truncate_title_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum title length'),
    '#default_value' => variable_get('path_breadcrumbs_truncate_title_length', ''),
    '#element_validate' => array('element_validate_integer_positive'),
    '#size' => 3,
    '#description' => t('An upper limit of symbols in the Path Breadcrumbs title. Title over the limit will be truncated with adding ellipsis at the end. Leave blank to disable truncating.'),
    '#field_suffix' => '<span class="description">' . (variable_get('path_breadcrumbs_truncate_title_length', '') ? t('To disable truncating leave field blank.') : t('Now truncating is disabled.')) . '</span>',
  );

  $form['path_breadcrumbs_settings']['path_breadcrumbs_decode_entities'] = array(
    '#type' => 'checkbox',
    '#title' => t('Decode HTML entities'),
    '#description' => t('Converts quotes in the breadcrumbs to their applicable characters.'),
    '#default_value' => variable_get('path_breadcrumbs_decode_entities', TRUE),
  );

  $form['#submit'][] = 'path_breadcrumbs_ui_settings_submit';

  return system_settings_form($form);
}

/**
 * Submit function for path_breadcrumbs_ui_settings form.
 */
function path_breadcrumbs_ui_settings_submit($form, &$form_state) {
  $values = $form_state['values'];

  // Flush theme registry if internal render was changed to enable/disable system render in theme_breadcrumb() function.
  $internal_render_new_value = $values['path_breadcrumbs_internal_render'];
  $internal_render_old_value = variable_get('path_breadcrumbs_internal_render', 1);

  $themes_new_value = array_filter($values['path_breadcrumbs_internal_render_themes']);
  $themes_old_value = variable_get('path_breadcrumbs_internal_render_themes', array());

  $form_state['values']['path_breadcrumbs_internal_render_themes'] = $themes_new_value;

  if (($internal_render_new_value != $internal_render_old_value) || $themes_new_value != $themes_old_value) {
    drupal_theme_rebuild();
  }

  // Truncate all cached data.
  cache_clear_all('*', PATH_BREADCRUMBS_CACHE_STORAGE, TRUE);
}

/**
 * Form for path breadcrumbs clone.
 */
function path_breadcrumbs_clone_breadcrumb($path_breadcrumb) {
  $path_breadcrumb->clone_from = $path_breadcrumb->machine_name;
  $path_breadcrumb->machine_name .= '_clone';
  $path_breadcrumb->export_type = NULL;
  unset($path_breadcrumb->path_id);
  path_breadcrumbs_object_cache_set($path_breadcrumb->machine_name, $path_breadcrumb);
  $form_state = array('storage' => array('machine_name' => $path_breadcrumb->machine_name));
  return drupal_build_form('path_breadcrumbs_ui_add_form', $form_state);
}

/**
 * Form for object export.
 */
function path_breadcrumbs_export_form($form, $form_state, $path_breadcrumbs) {

  drupal_set_title(t('Export path breadcrumb "!name"', array('!name' => $path_breadcrumbs->name)));

  ctools_include('export');

  $code = ctools_export_crud_export('path_breadcrumbs', $path_breadcrumbs);
  $lines = substr_count($code, "\n");

  $form['export'] = array(
    '#title' => t('Export data'),
    '#type' => 'textarea',
    '#value' => $code,
    '#rows' => $lines,
    '#description' => t('Copy the export text and paste it into import area.'),
  );

  return $form;
}

/**
 * Form for object import.
 */
function path_breadcrumbs_import_form($form, $form_state) {

  $form['import'] = array(
    '#type' => 'textarea',
    '#title' => t('Paste code here to import path breadcrumbs'),
  );

  $form['actions'] = array(
    '#type' => 'action',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Submit callback for path breadcrumbs import form.
 */
function path_breadcrumbs_import_form_submit($form, &$form_state) {
  $code = $form_state['values']['import'];
  ctools_include('export');

  $path_breadcrumbs_raw = ctools_export_crud_import('path_breadcrumbs', $code);
  if (is_string($path_breadcrumbs_raw)) {
    form_error($form['import'], t('Unable to get an import from the code. Errors reported: @errors', array('@errors' => $path_breadcrumbs_raw)));
    $form_state['rebuild'] = TRUE;
    return;
  }
  // Because we get raw object from Ctools we should prepare it before saving.
  $path_breadcrumbs = path_breadcrumbs_load_prepare($path_breadcrumbs_raw);
  $path_breadcrumbs_original = path_breadcrumbs_load_by_name($path_breadcrumbs->machine_name);
  // If there is path breadcrumbs object with the same machine name,
  // delete the original so that this one writes properly.
  if (!empty($path_breadcrumbs_original)) {
    path_breadcrumbs_delete($path_breadcrumbs_original->machine_name);
  }
  if (path_breadcrumbs_save($path_breadcrumbs)) {
    if (!empty($path_breadcrumbs_original)) {
      drupal_set_message(filter_xss(t('Path breadcrumb "!name" was successfully updated.', array('!name' => $path_breadcrumbs->name))));
    }
    else {
      drupal_set_message(filter_xss(t('Path breadcrumb "!name" was successfully imported.', array('!name' => $path_breadcrumbs->name))));
    }
  }
  else {
    form_error($form['import'], t('Could not import path breadcrumb.'));
  }

  $form_state['redirect'] = 'admin/structure/path-breadcrumbs';
}
