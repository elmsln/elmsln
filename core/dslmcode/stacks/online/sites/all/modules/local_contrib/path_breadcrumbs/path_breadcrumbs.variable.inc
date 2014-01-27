<?php

/**
 * @file
 * Variable integration for Path Breadcrumbs module.
 */

/**
 * Implements hook_variable_info().
 */
function path_breadcrumbs_variable_info($options) {

  $variables['path_breadcrumbs_home_link_enabled'] = array(
    'type' => 'boolean',
    'title' => t('Prepend breadcrumbs with a home link by default', array(), $options),
    'description' => t('This value does not changes current breadcrumbs navigation. It is just set default value for new path breadcrumbs.'),
    'default' => TRUE,
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_home_link_title'] = array(
    'type' => 'string',
    'title' => t('Home link title', array(), $options),
    'description' => t('Title of the link that points to the front page.'),
    'default' => 'Home',
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_delimiter'] = array(
    'type' => 'string',
    'title' => t('Delimiter', array(), $options),
    'description' => t('Symbol that separates breadcrumbs.'),
    'default' => '»',
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_rich_snippets'] = array(
    'type' => 'select',
    'title' => t('Rich snippets support', array(), $options),
    'description' => t('Provides rich snippets support for breadcrumbs. It is important to build a structure of a site in the SERP.'),
    'options' => array(
      PATH_BREADCRUMBS_RICH_SNIPPETS_DISABLED => t('Disabled', array(), $options),
      PATH_BREADCRUMBS_RICH_SNIPPETS_RDFA => t('RDFa', array(), $options),
      PATH_BREADCRUMBS_RICH_SNIPPETS_MICRODATA => t('Microdata', array(), $options),
    ),
    'default' => 0,
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_hide_single_breadcrumb'] = array(
    'type' => 'boolean',
    'title' => t('Hide breadcrumbs navigation for single breadcrumb', array(), $options),
    'description' => t('If breacrumbs navigation contains only one breadcrumb then breadcrumb navigation will be hidden.'),
    'default' => FALSE,
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_decode_entities'] = array(
    'type' => 'boolean',
    'title' => t('Decode HTML entities'),
    'description' => t('Converts quotes in the breadcrumbs to their applicable characters.'),
    'default' => TRUE,
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_internal_render'] = array(
    'type' => 'boolean',
    'title' => t('Use module breadcrumbs render function', array(), $options),
    'description' => t("If this value checked module will replace system or theme breadcrumb render function by module's one.<br/>Note that if this checkbox is unchecked module will not be able to implement settings below."),
    'default' => TRUE,
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_internal_render_themes'] = array(
    'type' => 'options',
    'title' => t('Use internal Path Breadcrumbs rendering only for specific themes', array(), $options),
    'description' => t('If you select no themes, there will be no specific limitation for Path Breadcrumbs render function.'),
    'options callback' => '_path_breadcrumbs_themes_option_list',
    'default' => array(),
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_url_cleaning_method'] = array(
    'type' => 'select',
    'title' => t('URL path cleaning method', array(), $options),
    'description' => t('Choose the path cleaning method to be applied when rendering Path Breadcrumbs.'),
    'options' => array(
      'none' => t('Disabled', array(), $options),
      'ctools' => t('CTools', array(), $options),
      'pathauto' => t('Pathauto', array(), $options),
    ),
    'default' => 'none',
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );
  if (!module_exists('pathauto')) {
    unset($variables['path_breadcrumbs_url_cleaning_method']['options']['pathauto']);
  }

  $variables['path_breadcrumbs_truncate_title_length'] = array(
    'type' => 'number',
    'title' => t('Maximum title length', array(), $options),
    'description' => t('An upper limit of symbols in the Path Breadcrumbs title. Title over the limit will be truncated with adding ellipsis at the end. Leave blank to disable truncating.'),
    'default' => '',
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_cache_enabled'] = array(
    'type' => 'boolean',
    'title' => t('Enable cache for the breadcrumbs', array(), $options),
    'description' => t("Enables caching of breadcrumb's navigations. Use only on production sites."),
    'default' => FALSE,
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  $variables['path_breadcrumbs_cache_lifetime'] = array(
    'type' => 'select',
    'title' => t('Cache lifetime', array(), $options),
    'options' => array(
      CACHE_PERMANENT => t('Permanent', array(), $options),
      CACHE_TEMPORARY => t('Temporary', array(), $options),
      60 * 5 => t('@amount minutes', array('@amount' => 5), array(), $options),
      60 * 15 => t('@amount minutes', array('@amount' => 15), array(), $options),
      60 * 30 => t('@amount minutes', array('@amount' => 30), array(), $options),
      60 * 60 => t('@amount minutes', array('@amount' => 60), array(), $options),
      60 * 60 * 2 => t('@amount hours', array('@amount' => 2), array(), $options),
      60 * 60 * 4 => t('@amount hours', array('@amount' => 4), array(), $options),
      60 * 60 * 8 => t('@amount hours', array('@amount' => 8), array(), $options),
      60 * 60 * 12 => t('@amount hours', array('@amount' => 12), array(), $options),
      60 * 60 * 24 => t('@amount hours', array('@amount' => 24), array(), $options),
      60 * 60 * 24 * 3 => t('@amount days', array('@amount' => 3), array(), $options),
      60 * 60 * 24 * 7 => t('@amount days', array('@amount' => 7), array(), $options),
    ),
    'default' => CACHE_PERMANENT,
    'localize' => TRUE,
    'group' => 'path_breadcrumbs',
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function path_breadcrumbs_variable_group_info() {

  $groups['path_breadcrumbs'] = array(
    'title' => t('Path Breadcrumbs'),
    'description' => t('Variables for Path Breadcrumbs configuration.'),
    'access' => 'administer path breadcrumbs',
    'path' => array('admin/structure/path-breadcrumbs/settings'),
  );

  return $groups;
}
