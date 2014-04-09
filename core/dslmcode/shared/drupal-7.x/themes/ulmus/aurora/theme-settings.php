<?php
/**
 * Implements hook_form_system_theme_settings_alter() function.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function aurora_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  // From the always awesome Zen
  if (isset($form_id)) {
   return;
  }
  drupal_add_css(drupal_get_path('theme', 'aurora') . '/css/settings.css');

  $theme = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : '';

  //////////////////////////////
  // Recomended modules
  //////////////////////////////

  $recomended_modules = aurora_recomended_modules();

  if (!empty($recomended_modules)) {
    $hide = theme_get_setting('hide_recomended_modules');

    $form['recomended_modules'] = array(
      '#type' => 'fieldset',
      '#title' => t('Recommended Modules'),
      '#collapsible' => TRUE,
      '#collapsed' => $hide,
      '#description' => t('Aurora was build in conjunction with several other modules to help streamline development. Some of these modules are not downloaded or enabled on your site. For maximum Aurora awesomesauce, you should take a look at the following modules. Modules marked as required should be download and enabled in order to get the most out of Aurora.'),
      '#weight' => -1000,
      '#attributes' => array('class' => array('aurora-recommended-modules')),
      '#prefix' => '<div class="messages warning aurora">',
      '#suffix' => '</div>'
    );

    $form['recomended_modules']['hide_recomended_modules'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide this warning by default.'),
      '#ajax' => array(
        'callback' => 'aurora_ajax_settings_save'
       ),
      '#default_value' => $hide,
    );

    foreach($recomended_modules as $id => $module) {
      $form['recomended_modules'][$id] = array(
        '#type' => 'item',
        '#title' => l($module['name'], 'http://drupal.org/project/' . $id, array('attributes' => array('target' => '_blank'))),
        '#description' => $module['description'],
        '#required' => $module['required'],
      );
    }
  }


  //////////////////////////////
  // Chrome Frame
  //////////////////////////////

  $form['chromeframe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Internet Explorer Support'),
    '#weight' => -100,
    '#attributes' => array('class' => array('aurora-row-left')),
    '#prefix' => '<span class="aurora-settigns-row">',
    '#parents' => array('vtb'),
  );

  $form['chromeframe']['aurora_min_ie_support'] = array(
    '#type' => 'select',
    '#title' => t('Minimum supported Internet Explorer version'),
    '#options' => array(
      11 => t('Internet Explorer 11'),
      10 => t('Internet Explorer 10'),
      9 => t('Internet Explorer 9'),
      8 => t('Internet Explorer 8'),
      7 => t('Internet Explorer 7'),
      6 => t('Internet Explorer 6'),
    ),
    '#default_value' => theme_get_setting('aurora_min_ie_support'),
    '#description' => t('The minimum version number of Internet Explorer that you actively support. The Chrome Frame prompt will display for any version below this version number.'),
    '#prefix' => '<span id="cf-settings">',
    '#suffix' => '</span>',
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
     ),
  );

  //////////////////////////////
  // Miscelaneous
  //////////////////////////////

  $form['misc'] = array(
   '#type' => 'fieldset',
   '#title' => t('Miscellaneous'),
   '#description' => t('Various little bits and bobs for your theme.'),
   '#weight' => -99,
   '#attributes' => array('class' => array('aurora-row-right')),
   '#suffix' => '</span>',
  );

  $form['misc']['aurora_html_tags'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prune HTML Tags'),
    '#default_value' => theme_get_setting('aurora_html_tags'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Prunes your <pre>style</pre>, <pre>link</pre>, and <pre>script</pre> tags as <a href="!link" target="_blank"> suggested by Nathan Smith</a>.', array('!link' => 'http://sonspring.com/journal/html5-in-drupal-7#_pruning')),
  );

  $form['misc']['aurora_typekit_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Typekit Kit ID'),
    '#default_value' => theme_get_setting('aurora_typekit_id'),
    '#size' => 7,
    '#maxlength' => 7,
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('If you are using <a href="!link" target="_blank">Typekit</a> to serve webfonts, put your Typekit Kit ID here', array('!link' => 'https://typekit.com/')),
  );

  if (module_exists('blockify') && user_access('administer blockify')) {

    $form['misc']['blockify'] = array(
      '#markup' => l('+ Configure Blockify', 'admin/config/user-interface/blockify', array('query' => array(drupal_get_destination()))),
    );
  }



  //////////////////////////////
  // Development
  //////////////////////////////

  if (!module_exists('magic_dev')) {
    $form['development'] = array(
      '#type' => 'fieldset',
      '#title' => t('Development'),
      '#description' => t('Theme like you\'ve never themed before! <div class="messages warning"><strong>WARNING:</strong> These options incur huge performance penalties and <em>must</em> be turned off on production websites.</div>'),
      '#weight' => 52
    );

    $form['development'] = array_merge(_aurora_live_reload_settings($theme), $form['development']);

  }

  //////////////////////////////
  // Remove a bunch of useless theme settings
  //////////////////////////////
  unset($form['theme_settings']['toggle_main_menu']);
  unset($form['theme_settings']['toggle_secondary_menu']);

  unset($form['theme_settings']['toggle_logo']);
  unset($form['theme_settings']['toggle_name']);
  unset($form['theme_settings']['toggle_slogan']);

  unset($form['theme_settings']['toggle_favicon']);
  unset($form['theme_settings']['toggle_breadcrumbs']);

  //////////////////////////////
  // Rename Toggle Display to Core Display
  //////////////////////////////
  $form['theme_settings']['#title'] = t('Miscellaneous display settings');
  $form['theme_settings']['#description'] = t('Enable or disable various miscellaneous display options.');
  $form['theme_settings']['#weight'] = 11;

  $form['theme_settings']['toggle_node_user_picture']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_comment_user_picture']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_comment_user_verification']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');



  //////////////////////////////
  // Logo and Favicon
  //////////////////////////////
  $form['logo']['#weight'] = 9;
  $form['logo']['#attributes']['class'][] = 'aurora-row-left';
  $form['logo']['#prefix'] = '<span class="aurora-settigns-row">';
  $form['logo']['default_logo']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');

  $form['favicon']['#weight'] = 10;
  $form['favicon']['#attributes']['class'][] = 'aurora-row-right';
  $form['favicon']['#suffix'] = '</span>';
  $form['favicon']['default_favicon']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
}

function aurora_chromeframe_options($form, $form_state) {
  $theme = $form_state['build_info']['args'][0];
  $theme_settings = variable_get('theme_' . $theme . '_settings', array());

  $theme_settings['aurora_enable_chrome_frame'] = $form_state['input']['aurora_enable_chrome_frame'];
  variable_set('theme_' . $theme . '_settings', $theme_settings);

  if ($form_state['input']['aurora_enable_chrome_frame'] == 1) {
    $form['chromeframe']['aurora_min_ie_support']['#disabled'] = false;
    return drupal_render($form['chromeframe']['aurora_min_ie_support']);
  }
  else {
    $form['chromeframe']['aurora_min_ie_support']['#disabled'] = true;
    return drupal_render($form['chromeframe']['aurora_min_ie_support']);
  }
  return '';
}

function aurora_ajax_settings_save($form, $form_state) {
  $theme = $form_state['build_info']['args'][0];
  $theme_settings = variable_get('theme_' . $theme . '_settings', array());
  $trigger = $form_state['triggering_element'] ['#name'];

  $theme_settings[$trigger] = $form_state['input'][$trigger];

  if (empty($theme_settings[$trigger])) {
    $theme_settings[$trigger] = 0;
  }
  variable_set('theme_' . $theme . '_settings', $theme_settings);
}

/**
 * A function to return an array of modules that should be enabled alongside
 * Aurora for maximum front-end awesomesauce.
 */
function aurora_recomended_modules() {
  $return = array();

  if (!module_exists('magic')) {
    $return['magic'] = array(
      'name' => t('Magic Module'),
      'description' => t('The Magic module provides advanced CSS and JavaScript handling for themes. It provides additional handling for CSS and JavaScript, as well as allows you to selectively remove files. It also provides development enhancements to make theming easier.'),
      'required' => TRUE,
    );
  }

  if (!module_exists('html5_tools')) {
    $return['html5_tools'] = array(
      'name' => t('HTML5 Tools'),
      'description' => t('HTML5 Tools is a module that allows Drupal sites to be built using HTML5 ... smartly. It includes features for creating cleaner and leaner markup, providing HTML5 elements for use in fields, and streamlining CSS and JavaScript tags, amongst many other improvements.'),
      'required' => TRUE,
    );
  }

  if (!module_exists('jquery_update')) {
    $return['jquery_update'] = array(
      'name' => t('jQuery Update'),
      'description' => t('jQuery Update will update the jQuery code base on your site from Drupal\'s base version 1.4. It will also allow jQuery to be loaded from a CDN, for added performance.'),
      'required' => FALSE,
    );
  }

  if (!module_exists('modernizr')) {
    $return['modernizr'] = array(
      'name' => t('Modernizr Module'),
      'description' => t('The Modernizr module will add in the !modernizr library of code to better help theme development and provide hooks for your theme and modules to define their dependencies.', array('!modernizr' => l('Modernizr', "http://modernizr.com/", array('attributes' => array('target' => '_blank'))))),
      'required' => FALSE,
    );
  }

  if (!module_exists('blockify')) {
    $return['blockify'] = array(
      'name' => t('Blockify Module'),
      'description' => t('Blockify allows you to use system information traditionally kept in page.tpl.php, such as Site Name, Tabs, Messages, Logo, etc…, as blocks. Aurora does not include these items in its page.tpl.php, so if you would like to use them, you should use this module.'),
      'required' => FALSE,
    );
  }

  if (!module_exists('borealis')) {
    $return['borealis'] = array(
      'name' => t('Borealis Suite'),
      'description' => t('Borealis provides two modules that make building responsive sites better. Borealis Responsive Images is an innovative, Drupal centric approach to responsive images. Borealis Semantic Blocks allows you to choose the semantics of blocks, making their output CSS much nicer.'),
      'required' => FALSE,
    );
  }

  if (!module_exists('fences')) {
    $return['fences'] = array(
      'name' => t('Fences Module'),
      'description' => t("The Fences Module is a an easy-to-use tool to specify an HTML element for each field. This element choice will propagate everywhere the field is used, such as teasers, RSS feeds and Views. You don't have to keep re-configuring the same HTML element over and over again every time you display the field. Best of all, Fences provides leaner markup than Drupal 7 core! And can get rid of the extraneous classes too!"),
      'required' => FALSE,
    );
  }

  if (!module_exists('panels')) {
    $return['panels'] = array(
      'name' => t('Panels Module'),
      'description' => t("The Panels module, especially when coupled with <a href=\"http://drupal.org/project/ctools\">CTool's</a> Page Manager module and Aurora's HTML5 Sections Panels layout, provides an excellent combination of tools for working with source order for the content area of your site."),
      'required' => FALSE,
    );
  }

  return $return;
}

/**
 * Implements hook_magic_alter.
 */
function aurora_magic_alter(&$magic_settings, $theme) {
  if (module_exists('magic_dev')) {
    $magic_settings['dev'] = array_merge(_aurora_live_reload_settings($theme), $magic_settings['dev']);
  }
}

/**
 * Since we use these settings in two places, we just leave them here.
 */
function _aurora_live_reload_settings($theme) {
  $array = array();

  $array['aurora_livereload'] = array(
    '#title' => t('Enable Livereload'),
    '#type' => 'select',
    '#options' => array(
      0 => t('Disabled'),
      35729 => t('Livereload Default Port'),
      9001 => t('Aurora Default Port'),
      'snugug' => t('Custom Port'),
    ),
    '#weight' => 100,
    '#default_value' => theme_get_setting('aurora_livereload', $theme),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Enable <a href="!link" target="_blank">LiveReload</a> to refresh your browser without you needing to. Awesome for designing in browser.', array('!link' => 'http://livereload.com/')),
  );

  $array['aurora_livereload_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Livereload port'),
    '#description' => t(''),
    '#size' => 4,
    '#weight' => 101,
    '#maxlength' => 5,
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#default_value' => theme_get_setting('aurora_livereload_port', $theme),
    '#states' => array(
      'visible' => array(
        ':input[name="aurora_livereload"]' => array('value' => 'snugug'),
      ),
    ),
  );

  return $array;
}
