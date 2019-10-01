<?php

/**
 * Implements template_preprocess_user_profile.
 */
function foundation_access_preprocess_user_profile(&$vars) {
  $elmsln_global_profile = variable_get('elmsln_global_profile', 'cpr');
  if (arg(0) == 'user') {
    // make sure this isn't the global profile providing distro, no reason to remote load in this case
    if (elmsln_core_get_profile_key() != $elmsln_global_profile) {
      $response = _cis_connector_request('user.json?deep-load-refs=file&name=' . $GLOBALS['user']->name, array(), $elmsln_global_profile, TRUE);
      // ensure we have response data
      if (isset($response->data)) {
        $data = drupal_json_decode($response->data);
        // ensure their name exists there though it would be weird not to
        if (isset($data['list'][0])) {
          $user_data_name = $data['list'][0];
          // run through and if the key we found IS NOT in local, add to local
          foreach ($user_data_name as $key => $value) {
            if (!isset($vars[$key])) {
              $vars[$key] = $value;
            }
          }
        }
      }
    }
    // make a display name
    $vars['displayname'] = '';
    // add in first name
    if (isset($vars['field_first_name'][0]['safe_value'])) {
      $vars['displayname'] .= $vars['field_first_name'][0]['safe_value'] . ' ';
    }
    elseif (isset($vars['field_first_name']) && is_string($vars['field_first_name'])) {
      $vars['displayname'] .= $vars['field_first_name'] . ' ';
    }
    // add in last name
    if (isset($vars['field_last_name'][0]['safe_value'])) {
      $vars['displayname'] .= $vars['field_last_name'][0]['safe_value'];
    }
    elseif (isset($vars['field_last_name']) && is_string($vars['field_last_name'])) {
      $vars['displayname'] .= $vars['field_last_name'] . ' ';
    }
    // add in display name the user wants to be called
    if (isset($vars['field_display_name'][0]['safe_value'])) {
      $vars['displayname'] .= ' | ' . $vars['field_display_name'][0]['safe_value'];
    }
    elseif (isset($vars['field_display_name']) && is_string($vars['field_display_name'])) {
      $vars['displayname'] .= ' | ' . $vars['field_display_name'];
    }
    // if nothing default to screen name
    if (empty($vars['displayname'])) {
      if (isset($vars['user_name'])) {
        $vars['displayname'] = $vars['user_name'];
      }
      else {
        $vars['displayname'] = $vars['name'];
      }
    }
    // add in user profile photo if there is one
    if (isset($vars['field_user_photo'][0]) && !empty($vars['field_user_photo'])) {
      $vars['field_user_photo'][0]['attributes'] = array(
        'class' => array('circle', 'ferpa-protect'),
      );
      $vars['field_user_photo'][0]['alt'] = t('Picture of @name', array('@name' => $vars['displayname']));
      $vars['field_user_photo'][0]['path'] = $vars['field_user_photo'][0]['uri'];
      $vars['photo'] = theme('image', $vars['field_user_photo'][0]);
    }
    elseif (isset($vars['field_user_photo']['file'])) {
      $vars['field_user_photo']['file']['attributes'] = array(
        'class' => array('circle', 'ferpa-protect'),
      );
      $vars['field_user_photo']['file']['alt'] = t('Picture of @name', array('@name' => $vars['displayname']));
      $vars['field_user_photo']['file']['path'] = str_replace('public://', 'elmslnauthority://cpr/', $vars['field_user_photo']['file']['uri']);
      $vars['photo'] = theme('image', $vars['field_user_photo']['file']);
    }
    else {
      // fallback on user profile fallback image
      $photolink = url(drupal_get_path('theme', 'foundation_access') . '/img/user.png', array('absolute' => TRUE));
      $vars['photo'] = '<img src="' . $photolink . '" class="ferpa-protect circle" alt="" />';
    }
    // set a banner if we have it
    if (isset($vars['field_user_banner'][0]) && !empty($vars['field_user_banner'])) {
      $vars['banner'] = $vars['user_profile']['field_user_banner'][0];
    }
    elseif (isset($vars['field_user_banner']['file'])) {
      $vars['banner'] = '<img class="background" src="' . $vars['field_user_banner']['file']['url'] . '" alt="" />';
    }
    else {
      // default fallback of design office image
      $vars['banner'] = '<img class="background" src="' . base_path() . drupal_get_path('theme', 'foundation_access') . '/materialize_unwinding/images/office.jpg" alt="" />';
    }
    // load up related user data
    //$blockObject = block_load('elmsln_core', 'elmsln_core_user_xapi_data');
    //$vars['user_data'] = _block_get_renderable_array(_block_render_blocks(array($blockObject)));
    // load bio info into "about" tab
    $bio = '';
    if (isset($vars['user_profile']['field_bio'])) {
      $bio = $vars['user_profile']['field_bio'];
    }
    elseif (isset($vars['field_bio'])) {
      $bio = check_markup($vars['field_bio']['value'], $vars['field_bio']['format']);
      // fallback in case this input filter doesn't exist
      if (empty($bio)) {
        $bio = check_markup($vars['field_bio']['value'], 'textbook_editor');
      }
    }
    // list tabs for rendering
    $vars['tabs'] = array(
      'bio' => t('About'),
      //'xapidata' => t('Activity data'),
    );
    // list content for those tabs to match on key names
    $vars['tabs_content'] = array(
      'bio' => $bio,
      //'xapidata' => $vars['user_data'],
    );
  }
  else {
    // list tabs for rendering
    $vars['tabs'] = array(
    );
    // list content for those tabs to match on key names
    $vars['tabs_content'] = array(
    );
  }
}

/**
 * Adds CSS classes based on user roles
 * Implements template_preprocess_html().
 */
function foundation_access_preprocess_html(&$variables) {
  // find the name of the install profile
  $variables['install_profile'] = elmsln_core_get_profile_key();
  $settings = _cis_connector_build_registry($variables['install_profile']);
  $address = explode('.', $settings['address']);
  $variables['iconsizes'] = array('16', '32', '64', '96', '160', '192', '310');
  $variables['appleiconsizes'] = array('60', '72', '76', '114', '120', '144', '152', '180');
  $variables['system_icon'] = $settings['icon'];
  $variables['lmsless_classes'] = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
  $variables['system_title'] = (isset($settings['default_title']) ? $settings['default_title'] : $variables['distro']);
  $variables['course'] = _cis_connector_course_context();
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'foundation_access');
  // add in all styles / js
  _foundation_access_add_cssjs();
  // theme path shorthand should be handled here
  foreach ($variables['user']->roles as $role){
    $variables['classes_array'][] = 'role-' . drupal_html_class($role);
  }
  // support for class to render in a modal
  if (isset($_GET['modal'])) {
    $variables['classes_array'][] = 'modal-rendered';
  }
  // add page level variables into scope for the html tpl file
  $variables['site_name'] = check_plain(variable_get('site_name', 'ELMSLN'));
  $variables['logo'] = theme_get_setting('logo');
  $variables['favicon_path'] = theme_get_setting('favicon_path');
  if (theme_get_setting('favicon') && !empty($variables['favicon_path'])) {
    $variables['favicon_path'] = file_create_url($variables['favicon_path']);
  }
  else {
    $variables['favicon_path'] = $variables['theme_path'] . '/icons/elmsicons/elmsln.ico';
  }
  $variables['banner_image'] = '';
  // build the remote banner URI, this is the best solution for an image
  $uri = 'elmslnauthority://cis/banners/' . _cis_connector_course_context() .'.jpg';
  if (file_exists(_elmsln_core_realpath($uri))) {
    $variables['banner_image'] = theme('image', array(
      'path' => $uri,
      'alt' => '',
      'attributes' => array(
        'class' => array('logo__img'),
      ),
    ));
  }
  // make sure we have a logo before trying to render a real one to screen
  elseif (!empty($variables['logo']) && !empty(theme_get_setting('logo_path'))) {
    $variables['banner_image'] = theme('image', array(
      'path' => theme_get_setting('logo_path'),
      'alt' => '',
      'attributes' => array(
        'class' => array('logo__img'),
      ),
    ));
  }
  else {
    $logopath = drupal_get_path('theme', 'foundation_access') . '/logo.jpg';
    $variables['banner_image'] = theme('image', array(
      'path' => $logopath,
      'alt' => '',
      'attributes' => array(
        'class' => array('logo__img'),
      ),
    ));
  }
}

/**
 * Add css / js to the page so we have it all in one block to manage.
 */
function _foundation_access_add_cssjs() {
  // add css for admin pages
  if (user_access('access administration menu')) {
    drupal_add_css(drupal_get_path('theme', 'foundation_access') . '/css/admin.css', array('group' => CSS_THEME, 'weight' => 999));
  }
  $libraries = libraries_get_libraries();
  if (!_entity_iframe_mode_enabled()) {
    // gifs need to be done as a player for accessibility reasons
    if (isset($libraries['freezeframe.js'])) {
      drupal_add_js($libraries['freezeframe.js'] .'/src/js/vendor/imagesloaded.pkgd.js');
      drupal_add_js($libraries['freezeframe.js'] .'/build/js/freezeframe.js');
      drupal_add_css($libraries['freezeframe.js'] .'/build/css/freezeframe_styles.min.css');
      drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/js/freezeframe-enable.js');
    }
  }
  drupal_add_css(drupal_get_path('theme', 'foundation_access') . '/materialize_unwinding/css/materialize.css', array('weight' => -1000));
  drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/materialize_unwinding/js/materialize.js', array('scope' => 'footer', 'weight' => 1000));
  // support for legacy, stock materializeCSS implementation
  if (variable_get('materializecss_legacy', FALSE)) {
    drupal_add_css($libraries['materialize'] . '/css/materialize.css', array('weight' => -1000));
    drupal_add_js($libraries['materialize'] . '/js/materialize.js', array('scope' => 'footer', 'weight' => 1000));
  }
  // support for our legacy; adding in css/js for foundation; this requires a forcible override in shared_settings.php
  if (variable_get('foundation_access_legacy', FALSE)) {
    drupal_add_css(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/css/foundation.min.css', array('weight' => -1000));
    drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/js/modernizr.js', array('scope' => 'footer', 'weight' => 1000));
    drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/js/foundation.min.js', array('scope' => 'footer', 'weight' => 1001));
    drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/js/enable-foundation.js', array('scope' => 'footer', 'weight' => 2000));
  }
}

/**
 * Style for fieldsets
 */
function foundation_access_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));
  
  // allow for materialization if it exists, otherwise serve default
  if (isset($element['#materialize'])) {
    switch ($element['#materialize']['type']) {
      case 'collapsible_wrapper':
        $output = '<ul' . drupal_attributes($element['#attributes']) .' role="tablist">' . $element['#children'] . '</ul>';
      break;
      case 'collapsible':
        $collapse = '';
        $icon = '';
        $body = '';
        if (isset($element['#collapsed']) && !$element['#collapsed']) {
          $collapse = ' active';
        }
        // support icons in the headings of collapsed fieldsets
        if (isset($element['#materialize']['icon'])) {
          $icon = '<iron-icon icon="' . $element['#materialize']['icon'] . '"></iron-icon>';
        }
        // support descriptions / form the body
        if (isset($element['#description'])) {
          $body .= '<p>' . $element['#description'] . '</p>';
        }
        // apply the value if it exists
        if (isset($element['#value'])) {
          $body .= $element['#value'];
        }
        // apply markup if it was pre-rendered
        if (isset($element['#markup'])) {
          $body .= $element['#markup'];
        }
        // drive down into the child elements if they exist
        $body .= $element['#children'];
        // make a nice anchor link
        $anchor = str_replace(' ', '', drupal_strtolower(preg_replace("/[^a-zA-Z_\s]+/", "", $element['#title'])));
        // form the fieldset as a collapse element
        $output = '
        <li class="collapsible-li">
          <lrnsys-collapselist-item>
              <div slot="label">
                ' . $icon . '
                <span>' . $element['#title'] . '</span>
              </div>
            <div slot="content"> ' . $body . ' </div>
          </lrnsys-collapselist-item>
          <div class="divider"></div>
        </li>';
      break;
    }
  }
  else {
    $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
    if (!empty($element['#title'])) {
      // Always wrap fieldset legends in a SPAN for CSS positioning.
      $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
    }
    $output .= '<div class="fieldset-wrapper">';
    if (!empty($element['#description'])) {
      $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
    }
    $output .= $element['#children'];
    if (isset($element['#value'])) {
      $output .= $element['#value'];
    }
    $output .= '</div>';
    $output .= "</fieldset>\n";
  }
  return $output;
}

/**
 * Implements template_preprocess_page.
 */
function foundation_access_preprocess_page(&$variables) {
  $element = array(
    '#tag' => 'link',
    '#attributes' => array(
      'href' => '//fonts.googleapis.com/icon?family=Material+Icons', 
      'rel' => 'stylesheet',
      'type' => 'text/css',
    ),
  );
  drupal_add_html_head($element, 'google_material_icons');
  $variables['contentwrappers'] = _elmsln_core_path_is_wrapped(current_path());
  $menu_item = menu_get_item();
  // sniff out if this is a view
  if ($menu_item['page_callback'] == 'views_page') {
    // try and auto append exposed filters to our local_subheader region
    $bid = '-exp-' . $menu_item['page_arguments'][0] . '-' . (is_array($menu_item['page_arguments'][1]) ? $menu_item['page_arguments'][1][0] : $menu_item['page_arguments'][1]);
    $block = module_invoke('views', 'block_view', $bid);
    $variables['page']['local_subheader'][$bid] = $block['content'];
  }
  $variables['distro'] = elmsln_core_get_profile_key();
  // make sure we have lmsless enabled so we don't WSOD
  $variables['cis_lmsless'] = array('active' => array('title' => ''));
  // support for lmsless since we don't require it
  if (module_exists('cis_lmsless')) {
    $variables['page']['content']['system_main']['main']['#markup'] = $css . $variables['page']['content']['system_main']['main']['#markup'];
  }
  // support for cis_shortcodes
  if (module_exists('cis_shortcodes')) {
    $block = cis_shortcodes_block_view('cis_shortcodes_block');
    if (!empty($block['content'])) {
      $variables['cis_shortcodes'] = $block['content'];
    }
    else {
      $variables['cis_shortcodes'] = '';
    }
  }
  else {
    $variables['cis_shortcodes'] = '';
  }
  // wrap non-node content in an article tag
  if (isset($variables['page']['content']['system_main']['main']) && arg(1) != 'mooc-content') {
    $variables['page']['content']['system_main']['main']['#markup'] = '<article class="view-mode-full">' . $variables['page']['content']['system_main']['main']['#markup'] . '</article>';
  }
  /**
   * @todo Get rid of this logic and put it somewhere else
   *       based on the new design.
   */
  // add a sharing url to view the specific section
  if (module_exists('cis_connector')) {
    $url_options = array(
      'absolute' => TRUE,
    );
    // check for setting section context
    $current_section = _cis_connector_section_context();
    if (isset($current_section) && $current_section) {
      $url_options['query']['elmsln_active_section'] = $current_section;
    }
    // check for setting course context
    $current_course = _cis_connector_course_context();
    if (isset($current_course) && $current_course) {
      $url_options['query']['elmsln_active_course'] = $current_course;
    }
    $current_page = url(current_path(), $url_options);

    // establish the fieldset container for shortcodes
    $field['cis_section_share'] = array(
      '#type' => 'fieldset',
      '#collapsed' => FALSE,
      '#collapsible' => TRUE,
      '#title' => t('Share this page'),
    );
    $field['cis_section_share']['cis_section_share_link'] = array(
      '#title' => t('Page URL'),
      '#value' => $current_page,
      '#type' => 'textfield',
      '#weight' => 0,
    );
    $variables['cis_section_share'] = $field;
  }
  // attempt to find an edit path for the current page
  if (isset($variables['tabs']) && is_array($variables['tabs']['#primary'])) {
    $edit_path = arg(0) . '/' . arg(1) . '/edit';
    foreach ($variables['tabs']['#primary'] as $key => $tab) {
      // edit path
      if (isset($tab['#link']['href']) && $tab['#link']['href'] == $edit_path) {
        $variables['edit_path'] = base_path() . $edit_path;
        // hide the edit tab cause our on canvas pencil does this
        unset($variables['tabs']['#primary'][$key]);
      }
    }
    // duplicate these for local header if its empty
    // do this everywhere except mooc since it has its own way of doing this
    if (empty($variables['page']['local_header']) && elmsln_core_get_profile_key() != 'mooc') {
      $variables['page']['local_header'] = array('#primary' => $variables['tabs']['#primary']);
      $variables['page']['local_header']['#theme_wrappers'] = array(0 => 'menu_local_tasks');
      foreach ($variables['page']['local_header']['#primary'] as $key => $tab) {
        // allow for shifting less common tasks off to the ... menu
        if (in_array($tab['#link']['path'], _foundation_access_move_tabs())) {
          unset($variables['page']['local_header']['#primary'][$key]);
        }
        else {
          unset($variables['tabs']['#primary'][$key]);
          $variables['page']['local_header']['#primary'][$key]['#attributes']['class'][] = 'leaf';
          $variables['page']['local_header']['#primary'][$key]['#attributes']['class'][] = 'tab';
          $variables['page']['local_header']['#primary'][$key]['#link']['localized_options']['attributes']['class'][] = $variables['cis_lmsless']['lmsless_classes'][elmsln_core_get_profile_key()]['text'];
          $variables['page']['local_header']['#primary'][$key]['#link']['localized_options']['attributes']['target'] = '_self';
        }
      }
      $primary = array();
      foreach ($variables['page']['local_header']['#primary'] as $key => $tab) {
        $primary[] = $tab;
      }
      $variables['page']['local_header']['#primary'] = $primary;
      // wrap this in tabs if we have things in here in the first place
      if (count($variables['page']['local_header']['#primary']) > 0) {
        $variables['page']['local_header']['#primary'][0]['#prefix'] = '<ul class="elmsln-tabs tabs">';
        $variables['page']['local_header']['#primary'][count($variables['page']['local_header']['#primary'])]['#suffix'] = '</ul>';
      }
    }
  }
}

/**
 * Implements hook_preprocess_block().
 */
function foundation_access_preprocess_block(&$variables) {
  // get color classes
  $variables['lmsless_classes'] = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
  // Convenience variable for block headers.
  $title_class = &$variables['title_attributes_array']['class'];

  // Generic block header class.
  $title_class[] = 'block-title';

  // In the header region visually hide block titles.
  if ($variables['block']->region == 'header') {
    $title_class[] = 'element-invisible';
  }

  // Add a unique class for each block for styling.
  $variables['classes_array'][] = $variables['block_html_id'];
}

/**
 * Implementation of hook_preprocess_node().
 */
function foundation_access_preprocess_node(&$variables) {
  $type = 'node';
  $bundle = $variables['type'];
  $viewmode = $variables['view_mode'];

  // add the view mode name to the classes array.
  if (isset($viewmode)) {
    $variables['classes_array'][] = str_replace('_', '-', $viewmode);
  }
  // hook on the iframe mode stuff
  if (module_exists('cis_connector') && module_exists('entity_iframe')) {
    $settings = _cis_connector_build_registry(elmsln_core_get_profile_key());
    $variables['iframe_path'] = _cis_connector_format_address($settings, '/', 'front') . 'entity_iframe/node/' . $variables['nid'];
  }

  // create inheritance templates and preprocess functions for this entity
  if (module_exists('display_inherit')) {
    display_inherit_inheritance_factory($type, $bundle, $viewmode, 'foundation_access', $variables);
  }
}

/**
 * Implements theme_field().
 *
 * Changes to the default field output.
 */
function foundation_access_field($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div ' . $variables['title_attributes'] . '>' . $variables['label'] . '</div>';
  }

  // Quick Edit module requires some extra wrappers to work.
  if (module_exists('quickedit')) {
    $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
    foreach ($variables['items'] as $delta => $item) {
      $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
      $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
    }
    $output .= '</div>';
  }
  else {
    foreach ($variables['items'] as $item) {
      $output .= drupal_render($item);
    }
  }

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Implements theme_file().
 */
function foundation_access_file($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'file';
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-file', 'elmsln-file-input'));
  // apply classes and wrappers needed for materializecss
  return '<div class="col s12 m8 file-field input-field">
      <div class="elmsln-file-btn-trigger">
        <span>' . $element['#title'] . '</span>
        <input' . drupal_attributes($element['#attributes']) . ' />
      </div>
      <div class="file-path-wrapper">
        <input class="file-path validate" type="text">
      </div>
    </div>';
}

/**
 * Implements hook_css_alter().
 */
function foundation_access_css_alter(&$css) {
  // Remove Drupal core CSS except system base
  foreach ($css as $path => $values) {
    if (strpos($path, 'modules/') === 0 && !in_array($path, array('modules/contextual/contextual.css'))) {
      unset($css[$path]);
    }
    // remove admin menu css without hacking that project
    $admin = drupal_get_path('module', 'adminimal_admin_menu');
    if ($path == $admin . '/adminimal_admin_menu.css') {
      unset($css[$path]);
    }
  }
}

/**
 * Implements theme_button().
 */
function foundation_access_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  $colors = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
  element_set_attributes($element, array('id', 'name', 'value'));
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }
  $element['#attributes']['class'][] = 'blue darken-2 white-text';
  // wrap classes on an upload button
  if ($variables['element']['#value'] == 'Upload') {
    return '
    <div class="col s12 m4 input-field">
      <button ' . drupal_attributes($element['#attributes']) . '><paper-button>' . $element['#value'] . '</paper-button></button>
    </div>';
  }
  else {
    $lrnsys = $element['#attributes'];
    if (is_array($lrnsys['class'])) {
      $lrnsys['button-class'] = implode(' ', $lrnsys['class']);
    }
    if (!isset($lrnsys['hover-class'])) {
      $lrnsys['hover-class'] = $colors['color'] . ' ' . $colors['dark'];
    }
    // hate doing it this way but makes it easier to skip webcomponents issues
    // w/ route grabbing
    $js = ' ';
    if ($element['#value'] == 'Emulate') {
      $js = ' onclick="document.getElementById(\'masquerade-block-1\').submit();" ';
    }
    else if ($element['#value'] == 'Switch section' || $element['#value'] == 'Reset section') {
      $js = ' onclick="document.getElementById(\'cis-service-connection-block-section-context-changer-form\').submit();" ';
    }
    unset($lrnsys['id']);
    return '<button' . $js . drupal_attributes($element['#attributes']) . '><paper-button ' . drupal_attributes($lrnsys) . '>' . $element['#value'] . '</paper-button></button>';
  }
}

/**
 * Implements theme_textfield().
 */
function foundation_access_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Implements theme_form_element().
 */
function foundation_access_form_element($variables) {
  $element = &$variables['element'];
  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (isset($element['#type']) && ($element['#type'] == 'textfield' || $element['#type'] == 'password')) {
    $attributes['class'][] = 'input-field';
  }
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Implements theme_select().
 */
function foundation_access_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  return '<select' . drupal_attributes($element['#attributes']) . '>' . _foundation_access_form_select_options($element) . '</select>';
}

/**
 * Fork of core form_select_options.
 */
function _foundation_access_form_select_options($element, $choices = NULL) {
  if (!isset($choices)) {
    $choices = $element['#options'];
  }
  // array_key_exists() accommodates the rare event where $element['#value'] is NULL.
  // isset() fails in this situation.
  $value_valid = isset($element['#value']) || array_key_exists('#value', $element);
  $value_is_array = $value_valid && is_array($element['#value']);
  $options = '';
  foreach ($choices as $key => $choice) {
    if (is_array($choice)) {
      $options .= '<optgroup label="' . check_plain($key) . '">';
      $options .= form_select_options($element, $choice);
      $options .= '</optgroup>';
    }
    elseif (is_object($choice)) {
      $options .= form_select_options($element, $choice->option);
    }
    else {
      $key = (string) $key;
      if ($value_valid && (!$value_is_array && (string) $element['#value'] === $key || ($value_is_array && in_array($key, $element['#value'])))) {
        $selected = ' selected="selected"';
      }
      else {
        $selected = '';
      }
      $extra = '';
      // support for materialize options
      if (isset($element['#materialize']) && $key != '_none') {
        $extra = 'class="' . $element['#materialize']['class'] . '"';
        // add in the path to the images w/ the option being part of the
        // name of the file. This is very specific to how we want to structure
        // choice options to have an icon_path counterpart but it's not
        // that hard to do so whatever.
        if (isset($element['#materialize']['icon_path'])) {
          $extra .= ' data-icon="' . base_path() . $element['#materialize']['icon_path'] . drupal_strtolower(str_replace('/', '-', str_replace(' ', '', check_plain($choice)))) . '.png"';
        }
      }
      $options .= '<option ' . $extra . ' value="' . check_plain($key) . '"' . $selected . '>' . check_plain($choice) . '</option>';
    }
  }
  return $options;
}

/**
 * Implements theme_field__taxonomy_term_reference().
 */
function foundation_access_field__taxonomy_term_reference($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h3 class="field-label">' . $variables['label'] . '</h3>';
  }

  // Render the items.
  $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<li class="chip taxonomy-term-reference taxonomy-term-reference-' . $delta . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }
  $output .= '</ul>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '">' . $output . '</div>';

  return $output;
}

/**
 * Implements theme_field__taxonomy_term_reference().
 */
function foundation_access_field__field_cis_course_ref($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h3 ' . $variables['title_attributes'] . '>' . $variables['label'] . '</h3>';
  }

  foreach ($variables['items'] as $item) {
    $output .= drupal_render($item);
  }
  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Calculate and display duration for external videos when we can.
 */
function foundation_access_preprocess_node__inherit__external_video(&$variables) {
  $elements = &$variables['elements'];
  // see if we have a usable duration value
  if (isset($elements['#node']->field_external_media['und'][0]['video_data'])) {
    // load it up and search
    $video_data = unserialize($elements['#node']->field_external_media['und'][0]['video_data']);
    // not everything has an actual duration so double-check
    if (isset($video_data['duration'])) {
      $time = ($video_data['duration'] / 60);
      // convert into hours / minutes
      $hours = floor($time / 60);
      $minutes = ceil(fmod($time, 60));
      $hour_suffix = t('hour');
      $min_suffix = t('minute');
      $minute_format = format_plural($minutes, '1 ' . $min_suffix, '@count ' . $min_suffix . 's');
      if (!empty($hours)) {
        $hour_format = format_plural($hours, '1 ' . $hour_suffix, '@count ' . $hour_suffix . 's');
        $duration = format_string('@h, @m', array('@h' => $hour_format, '@m' => $minute_format));
      }
      else {
        $duration = $minute_format;
      }
      $variables['duration'] = '<i class="material-icons text-black">access_time</i><em>' . $duration . '</em>';
    }
  }
}

/**
 * Display Inherit External Video
 */
function foundation_access_preprocess_node__inherit__external_video__mediavideo(&$variables) {
  $variables['poster'] = FALSE;
  $variables['video_url'] = FALSE;
  $variables['thumbnail'] = FALSE;
  $poster_image_uri = '';
  $elements = &$variables['elements'];
  // Assign Poster
  // if the poster field is available use that for the poster imgage
  if (isset($elements['#node']->field_poster['und'][0]['uri'])) {
    $poster_image_uri = $elements['#node']->field_poster['und'][0]['uri'];
  }
  // see if this entity has our standard competency field associated to it
  if (isset($elements['#node']->field_elmsln_competency) && !empty($elements['#node']->field_elmsln_competency)) {
    $variables['competency'] = $elements['#node']->field_elmsln_competency['und'][0]['safe_value'];
  }
  // if poster still blank AND thumbnail is available, then set poster to thumbnail
  if ($poster_image_uri == '' && isset($variables['content']['field_external_media']['#items'][0]['thumbnail_path'])) {
    $poster_image_uri = $variables['content']['field_external_media']['#items'][0]['thumbnail_path'];
  }
  // if we have found a poster then assign it
  if ($poster_image_uri) {
    $variables['poster'] = image_style_url('mediavideo_poster', $poster_image_uri);
  }
  // Set the video url
  if (isset($elements['field_external_media']['#items'][0]['video_url']) && $elements['field_external_media']['#items'][0]['video_url']) {
    $variables['video_url'] = $elements['field_external_media']['#items'][0]['video_url'];
  }

  // Unset the poster if on the Mediavideo viewmode
  // mediavideo should not have a poster, there is a viewmode for that
  // called mediavideo__poster
  if ($variables['view_mode'] == 'mediavideo') {
    $variables['poster'] = NULL;
  }
}

function foundation_access_preprocess_node__inherit__external_video__mediavideo__thumbnail(&$variables) {
  $variables['thumbnail'] = true;
}

/**
 * Display Inherit Image.
 */
function foundation_access_preprocess_node__inherit__elmsmedia_image__image(&$variables) {
  $variables['image'] = array();
  $variables['image_caption'] = '';
  $variables['image_cite'] = '';
  $variables['image_lightbox_url'] = '';

  // Assign Image
  if (isset($variables['elements']['field_image'][0])) {
    $variables['image'] = $variables['elements']['field_image'][0];
    // if the image is a .gif then just use the original file
    // so that it doesn't break the animation
    if (isset($variables['image']['#item']['filemime']) && $variables['image']['#item']['filemime'] == 'image/gif') {
      $variables['image']['#image_style'] = '';
      $variables['image']['#item']['attributes']['class'][] = 'animatedgif';
      $variables['image']['#item']['attributes']['class'][] = 'freezeframe-responsive';
      $variables['is_gif'] = TRUE;
      $variables['gif_buttons'] = '
      <div class="container">
        <button class="start col s3 blue push-s2"><i class="material-icons left">play_arrow</i>' . t('start') . '</button>
        <button class="stop col s3 red pull-s2 right"><i class="material-icons left">stop</i>' . t('stop') . '</button>
      </div>';
    }
    // alt/title info
    if (empty($variables['image']['#item']['alt'])) {
      $variables['image']['#item']['alt'] = $variables['elements']['#node']->title;
    }
    if (empty($variables['image']['#item']['title'])) {
      $variables['image']['#item']['title'] = $variables['elements']['#node']->title;
    }
    $variables['image']['#item']['attributes']['class'][] = 'image__img';
    $variables['image']['#item']['attributes']['class'][] = 'responsive-img';
  }
  $tmp = explode('__', $variables['view_mode']);
  // inherrit class structure from deep structures
  if (count($tmp) > 1) {
    // build the base from the 1st two items
    $base = array_shift($tmp);
    // loop through what's left to add as classes
    foreach ($tmp as $part) {
      $class = $base . '--' . $part;
      $variables['classes_array'][] = $class;
    }
  }

  // Assign Caption
  if (isset($variables['elements']['field_image_caption'][0]['#markup'])) {
    $variables['image_caption'] = $variables['elements']['field_image_caption'][0]['#markup'];
  }
  // Assign Cite
  if (isset($variables['elements']['field_citation'][0]['#markup'])) {
    $variables['image_cite'] = $variables['elements']['field_citation'][0]['#markup'];
  }
  // If the viewmode contains "lightbox" then enable the lightbox option
  if (strpos($variables['view_mode'], 'lightboxed')) {
    if (isset($variables['image']['#item']['filemime']) && $variables['image']['#item']['filemime'] == 'image/gif') {
      $variables['image_lightbox_url'] = file_create_url($variables['image']['#item']['uri']);
    }
    else {
      $variables['image_lightbox_url'] = image_style_url('image_lightboxed', $variables['image']['#item']['uri']);
    }
  }
  // account for card size
  if (strpos($variables['view_mode'], 'card')) {
    if (strpos($variables['view_mode'], 'small')) {
      $variables['card_size'] = 'small';
    }
    elseif (strpos($variables['view_mode'], 'large')) {
      $variables['card_size'] = 'large';
    }
    else {
      $variables['card_size'] = 'medium';
    }
  }
  // special class applied to the image itself to make it a circle
  if (strpos($variables['view_mode'], 'circle')) {
    $variables['image']['#item']['attributes']['class'][] = 'circle';
  }
}

/**
 * Display Inherit Image gallery
 */
function foundation_access_preprocess_node__inherit__image_gallery(&$variables) {
  $variables['images'] = array();

  // Assign Image
  if (isset($variables['elements']['field_images'])) {
    $variables['featured_image_id'] = 'elmsln-featured-image-' . rand(0, 300);
    $tmpimages = $variables['elements']['field_images']['#items'];
    // append classes to images for rendering
    foreach ($tmpimages as $key => $image) {
      $variables['images'][$key] = array(
        '#theme' => 'image_formatter',
        '#item' => $tmpimages[$key]['entity']->field_image[LANGUAGE_NONE][0],
        '#image_style' => 'image_gallery_square',
        '#path' => '',
        'entity' => $tmpimages[$key]['entity'],
      );
      // alt/title info
      if (empty($variables['images'][$key]['#item']['alt'])) {
        $variables['images'][$key]['#item']['alt'] = $image['entity']->title;
      }
      if (empty($variables['images'][$key]['#item']['title'])) {
        $variables['images'][$key]['#item']['title'] = $image['entity']->title;
      }
      // special class applied to the image itself to make it a circle
      if (strpos($variables['view_mode'], 'circle')) {
        $variables['images'][$key]['#item']['attributes']['class'][] = 'circle';
      }
      $variables['image_lightbox_url'][$key] = image_style_url('image_lightboxed', $tmpimages[$key]['entity']->field_image[LANGUAGE_NONE][0]['uri']);
    }
  }
  $tmp = explode('__', $variables['view_mode']);
  // inherrit class structure from deep structures
  if (count($tmp) > 1) {
    // build the base from the 1st two items
    $base = array_shift($tmp);
    // loop through what's left to add as classes
    foreach ($tmp as $part) {
      $class = $base . '--' . $part;
      $variables['classes_array'][] = $class;
    }
  }
}

/**
 * Display Inherit Image gallery
 */
function foundation_access_preprocess_node__inherit__image_gallery__image(&$variables) {
  $variables['images'] = array();
  $variables['image_caption'] = '';
  $variables['image_cite'] = '';
  $variables['image_lightbox_urls'] = '';

  // Assign Image
  if (isset($variables['elements']['field_images'])) {
    $tmpimages = $variables['elements']['field_images']['#items'];
    // append classes to images for rendering
    foreach ($tmpimages as $key => $image) {
      $variables['images'][$key] = array(
        '#theme' => 'image_formatter',
        '#item' => $tmpimages[$key]['entity']->field_image[LANGUAGE_NONE][0],
        '#image_style' => 'image_gallery_square',
        '#path' => '',
      );
      // alt/title info
      if (empty($variables['images'][$key]['#item']['alt'])) {
        $variables['images'][$key]['#item']['alt'] = $image['entity']->title;
      }
      if (empty($variables['images'][$key]['#item']['title'])) {
        $variables['images'][$key]['#item']['title'] = $image['entity']->title;
      }
      $variables['images'][$key]['#item']['attributes']['class'][] = 'image__img';
      $variables['images'][$key]['#item']['attributes']['class'][] = 'responsive-img';
      // special class applied to the image itself to make it a circle
      if (strpos($variables['view_mode'], 'circle')) {
        $variables['images'][$key]['#item']['attributes']['class'][] = 'circle';
      }
      // If the viewmode contains "lightbox" then enable the lightbox option
      if (strpos($variables['view_mode'], 'lightboxed')) {
        $variables['image_lightbox_url'][$key] = image_style_url('image_lightboxed', $tmpimages[$key]['entity']->field_image[LANGUAGE_NONE][0]['uri']);
      }
    }
  }
  $tmp = explode('__', $variables['view_mode']);
  // inherrit class structure from deep structures
  if (count($tmp) > 1) {
    // build the base from the 1st two items
    $base = array_shift($tmp);
    // loop through what's left to add as classes
    foreach ($tmp as $part) {
      $class = $base . '--' . $part;
      $variables['classes_array'][] = $class;
    }
  }

  // Assign Caption
  if (isset($variables['elements']['field_image_caption'][0]['#markup'])) {
    $variables['image_caption'] = $variables['elements']['field_image_caption'][0]['#markup'];
  }
  // Assign Cite
  if (isset($variables['elements']['field_citation'][0]['#markup'])) {
    $variables['image_cite'] = $variables['elements']['field_citation'][0]['#markup'];
  }
  // account for card size
  if (strpos($variables['view_mode'], 'card')) {
    if (strpos($variables['view_mode'], 'small')) {
      $variables['card_size'] = 'small';
    }
    elseif (strpos($variables['view_mode'], 'large')) {
      $variables['card_size'] = 'large';
    }
    else {
      $variables['card_size'] = 'medium';
    }
  }
}

/**
 * Display Inherit Image
 */
function foundation_access_preprocess_node__inherit__svg(&$variables) {
  $variables['svg_aria_hidden'] = 'false';
  $variables['svg_alttext'] = NULL;
  $variables['svg_lightbox_url'] = '';
  // support lightboxing this if mode looks for it
  if (strpos($variables['view_mode'], 'lightboxed')) {
    $variables['svg_lightbox_url'] = file_create_url($variables['field_svg'][0]['uri']);
  }
  $node_wrapper = entity_metadata_wrapper('node', $variables['node']);
  try {
    // if there is an accessbile text alternative then set the svg to aria-hidden
    if ($node_wrapper->field_svg_alttext->value()) {
      $variables['svg_aria_hidden'] = 'true';
      $variables['svg_alttext'] = $node_wrapper->field_svg_alttext->value();
    }
  }
  catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'foundation_access',
      'EntityMetadataWrapper exception in %function() <pre>@trace</pre>',
      array('%function' => __FUNCTION__, '@trace' => $exc->getTraceAsString()),
      WATCHDOG_ERROR
    );
  }
}

/**
 * Implements hook_theme_registry_alter().
 */
function foundation_access_theme_registry_alter(&$theme_registry) {
  // Add a template file for clipboardjs
  $theme_registry['clipboardjs']['template'] = 'clipboardjs';
  $theme_registry['clipboardjs']['preprocess functions'][] = 'template_preprocess_clipboardjs';
}

function foundation_access_preprocess_clipboardjs(&$variables) {
  $variables['content'] = array();
  $uniqid = uniqid('clipboardjs-');

  $variables['content']['text'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => $uniqid,
    ),
  );

  $variables['content']['text']['markup'] = array(
    '#markup' => $variables['text'],
  );
  $variables['content']['button'] = array(
    '#markup' => '<button title="' . t('Copy content') . '" class="clipboardjs-button" data-clipboard-alert="toast" data-clipboard-alert-text="' . $variables['alert_text'] . '" data-clipboard-target="#' . $uniqid . '" onclick="return false;"><iron-icon icon="content-copy" style="display:block;"></iron-icon></button>',
  );
}

/**
 * Implements theme_menu_local_tasks().
 */
function foundation_access_menu_local_tasks(&$variables) {
  $output = '';
  if (!empty($variables['primary'])) {
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $output .= drupal_render($variables['secondary']);
  }
  return $output;
}

/**
 * Implements template_link.
 */
function foundation_access_link(&$variables) {
  $path = $variables['path'];
  $text = $variables['text'];
  $options = $variables['options'];
  // support for lrn icon
  if (isset($variables['options']['fa_icon']) && $variables['options']['fa_icon'] && !isset($variables['options']['identifier'])) {
    $options['html'] = TRUE;
    $text = '<lrn-icon icon="' . $variables['options']['fa_icon'] . '"></lrn-icon>' . $text;
  }
  // support for has-children chevron
  if (isset($variables['options']['has-children']) && $variables['options']['has-children']) {
    $options['attributes']['icon'] = 'chevron-right';
  }
  // account for admin menu link and don't bother styling it w/ custom elements
  if ($text != 'Edit network links' && isset($options['attributes']['class'][0]) && $options['attributes']['class'][0] == 'admin-menu-destination' || (!isset($variables['options']['identifier']) && (strpos($variables['path'], 'admin') === 0 || strpos($variables['path'], 'devel') === 0 || strpos($variables['path'], 'node/add') === 0 || strpos($variables['path'], 'http://drupal.org') === 0 || strpos($variables['path'], 'update.php') === 0))) {
    return '<a href="' . check_plain(url($path, $options)) . '"' . drupal_attributes($options['attributes']) . '>' . ($options['html'] ? $text : check_plain($text)) . '</a>';
  }
  else {
    return _foundation_access_lrnsys_button($text, $path, $options);
  }
}

/**
 * Shortcut to correctly render a lrnsys-button tag.
 * @param  string $label   button label
 * @param  string $path    href / location
 * @param  array $options  array of options typically passed into l()
 * @return string          a rendered button
 */
function _foundation_access_lrnsys_button($label, $path, $options) {
  // good thing for static caching
  if (!isset($options['attributes']['hover-class'])) {
    $colors = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
    $options['attributes']['hover-class'] = $colors['color'] . ' ' . $colors['dark'] . ' white-text';
  }
  if (strpos($path, 'apps/') === 0) {
    $options['attributes']['prefetch'] = true;  
  }
  // support links without a path
  if ($path != NULL) {
    $options['attributes']['href'] = check_plain(url($path, $options));
  }
  // if HTML is set to true then we can't handle this at the moment, stuff in light dom
  if ($options['html']) {
    return '<lrnsys-button ' . drupal_attributes($options['attributes']) . '>' . $label . '</lrnsys-button>';
  }
  else {
    return '<lrnsys-button label="' . check_plain($label) . '" ' . drupal_attributes($options['attributes']) . '></lrnsys-button>';
  }
}

/**
 * Implements template_menu_link.
 */
function foundation_access_menu_link(&$variables) {
  static $book_active;
  $element = $variables['element'];
  $sub_menu = '';
  $title = check_plain($element['#title']);
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  // special handling for node based menu items
  if ($element['#original_link']['router_path'] == 'node/%') {
    $element['#localized_options']['html'] = TRUE;

    if ($element['#below']) {
      $element['#localized_options']['attributes']['class'][] = 'has-children';
    }
  }
  // support for add menu to get floating classes
  if ($element['#original_link']['menu_name'] == 'menu-elmsln-add') {
    // support for passing section context as to what they are looking at currently
    if (_cis_connector_system_type() != 'service' && $element['#original_link']['router_path'] != 'cis-quick-setup') {
      $element['#localized_options']['query']['elmsln_course'] = _cis_connector_course_context();
      $element['#localized_options']['query']['elmsln_section'] = _cis_connector_section_context();
    }
    // set destination to bounce back here when done
    if (_cis_connector_system_type() != 'service') {
      $element['#localized_options']['query']['destination'] = current_path();
    }
    // load up a map of icons and color associations
    $icon_map = _elmsln_core_icon_map();
    $icon = str_replace(' ', '_', drupal_strtolower($title));
    // see if we have an icon
    if (isset($icon_map[$icon])) {
      // see if this is being sent externally
      if (strpos($element['#href'], 'elmsln/redirect') === 0) {
        $element['#localized_options']['attributes']['class'][] = 'elmsln-core-external-context-apply';
      }
      if (isset($icon_map[$icon]['text'])) {
        $textcolor = $icon_map[$icon]['text'];
      }
      else {
        $textcolor = 'white-text';
      }
      $title = '<lrnapp-fab-speed-dial-action icon="' . $icon_map[$icon]['icon'] . '" color="' . $icon_map[$icon]['color'] . '">' . $title . '</lrnapp-fab-speed-dial-action>';
      $element['#localized_options']['html'] = TRUE;
    }
    else {
      $lmsless_classes = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
      $element['#localized_options']['attributes']['class'][] = $lmsless_classes['color'];
      $element['#localized_options']['attributes']['class'][] = 'white-text';
      $element['#localized_options']['attributes']['class'][] = $lmsless_classes['dark'];
    }
  }
  elseif ($element['#original_link']['menu_name'] == 'menu-elmsln-navigation') {
    $lmsless_classes = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
    $element['#attributes']['class'][] = 'tab';
    $element['#localized_options']['attributes']['class'][] = $lmsless_classes['text'];
    $element['#localized_options']['attributes']['target'] = '_self';
  }
  elseif (strpos($element['#original_link']['menu_name'], 'book-toc-') === 0) {
    $element['#attributes']['class'][] = 'elmsln-book-item';
    if ($element['#original_link']['has_children'] == 1) {
      $element['#localized_options']['has-children'] = TRUE;
      $element['#localized_options']['attributes']['class'][] = 'has-children';
    }
    elseif (isset($element['#original_link']['options']['fa_icon']) && !empty($element['#original_link']['options']['fa_icon'])) {
      // overview page renders differently for full screen mode
      if (current_path() == 'mooc/book-toc') {
        $element['#localized_options']['attributes']['class'][] = 'icon-' . $element['#original_link']['options']['fa_icon'];
        $element['#localized_options']['attributes']['class'][] = 'elmsln-icon';
      }
      else {
        $element['#attributes']['class'][] = 'icon-' . $element['#original_link']['options']['fa_icon'];
        $element['#attributes']['class'][] = 'elmsln-icon';
      }
    }
    // look for active trail being hit in a book
    if (array_search('active-trail', $element['#attributes']['class'])) {
      $book_active = TRUE;
    }
    // if we haven't set an active page yet then keep claiming we past it
    if (!isset($book_active)) {
      $element['#attributes']['class'][] = 'past-page';
    }
  }
  $output = l($title, $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements a generic hook_menu_tree callback.
 */
function foundation_access_menu_tree($variables) {
  return '<ul class="menu">' . $variables['tree'] . '</ul>';
}

/**
 * Implements menu_tree__menu_elmsln_settings.
 */
function foundation_access_menu_tree__menu_elmsln_settings($variables) {
  return '<ul class="has-submenu">' . $variables['tree'] . '</ul>';
}

/**
 * Implements menu_tree__menu_elmsln_navigation.
 */
function foundation_access_menu_tree__menu_elmsln_navigation($variables) {
  return '<ul class="elmsln-tabs tabs">' . $variables['tree'] . '</ul>';
}

/**
 * Implements menu_tree__menu_elmsln_add.
 */
function foundation_access_menu_tree__menu_elmsln_add($variables) {
  return '<ul role="menu" aria-hidden="false" tabindex="-1" class="elmsln-add-menu-items">' . $variables['tree'] . '</ul>';
}

function foundation_access_preprocess_book_sibling_nav(&$variables) {
  // Outline Labeling theme setting
  $variables['outline_labeling'] = theme_get_setting('mooc_foundation_access_outline_labeling');
  // Outline Label theme setting
  if ($labeling = $variables['outline_labeling']) {
    if ($labeling == 'auto_both' || $labeling == 'auto_text') {
      $variables['outline_label'] = theme_get_setting('mooc_foundation_access_outline_label');
    }
    else {
      $variables['outline_label'] = '';
    }
  }
}

/**
 * Callback to do most of the work for rendering a nested slide out menu
 * @return string             rendered html structure for this menu
 */
function _foundation_access_menu_outline($variables, $word = FALSE, $number = FALSE) {
  static $counter = 1;
  $element = $variables['element'];
  $sub_menu = '';
  $return = '';
  $title = check_plain($element['#title']);
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $id = 'menu-panel-' . $element['#original_link']['mlid'];
  // account for no link'ed items
  if ($element['#href'] == '<nolink>') {
    $output = '<a href="#menu-no-link-' . hash('md5', 'mnl' . $title) . '">' . $title . '</a>';
  }
  $options = $element['#localized_options'];
  $options['html'] = TRUE;
  // ensure class array is at least set
  if (empty($element['#attributes']['class'])) {
    $element['#attributes']['class'] = array();
  }
  $classes = implode(' ', $element['#attributes']['class']);
  $options['attributes']['class'] = $element['#attributes']['class'];
  return '<li>' . l($title, $element['#href'], $options) . '</li>';
}

/**
 * Generate an auto labeled element correctly
 * @param  string $word     word for the high level organizer
 * @param  int    $number   whether to show the counter
 * @param  int    $counter  position in the counter for the high level
 * @return string           assembled label for this level
 */
function _foundation_access_auto_label_build($word, $number, $counter) {
  $labeltmp = '';
  if ($word) {
    $labeltmp = $word;
    if ($number) {
      $labeltmp .= ' ' . $counter;
    }
  }
  else {
    if ($number) {
      $labeltmp = $counter;
    }
  }
  return $labeltmp;
}

/**
 * Implements theme_menu_local_task().
 */
function foundation_access_menu_local_task(&$variables) {
  $link = $variables['element']['#link'];
  $link_text = check_plain($link['title']);
  if (!empty($variables['element']['#active'])) {
    $variables['element']['#attributes']['class'][] = 'active';
  }
  if (empty($variables['element']['#attributes'])) {
    $variables['element']['#attributes'] = array();
  }
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
  $output = '<li ' . drupal_attributes($variables['element']['#attributes']) . '>';
  $output .= l($link_text, $link['href'], $link['localized_options']);
  $output .= "</li>\n";
  return  $output;
}

/**
 * Implements theme_preprocess_book_export_html().
 */
function foundation_access_preprocess_book_export_html(&$variables) {
  global $base_url, $language;
  $var = array();
  @module_invoke_all('page_init', $var);
  @drupal_alter('page_init', $var);
  @module_invoke_all('page_build', $var);
  @drupal_alter('page_build', $var);
  @module_invoke_all('preprocess_html', $var);
  $js = drupal_get_js() . drupal_get_js('footer');
  $variables['title'] = check_plain($variables['title']);
  $variables['base_url'] = $base_url;
  $variables['language'] = $language;
  $variables['language_rtl'] = ($language->direction == LANGUAGE_RTL);
  $variables['head'] = drupal_get_html_head();
  $variables['scripts'] = $js;
  $variables['styles'] = drupal_get_css();
  $variables['dir'] = $language->direction ? 'rtl' : 'ltr';
}

/**
 * Implements hook_html_head_alter()
 */
function foundation_access_html_head_alter(&$head_elements) {
  // remove notice that this is drupal
  unset($head_elements['system_meta_generator']);
  // remove shortcut icon default loading
  foreach ($head_elements as $key => $value) {
    if (strpos($key, 'drupal_add_html_head_link:shortcut icon:') === 0) {
      unset($head_elements[$key]);
    }
  }
}

/**
 * Implements theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function foundation_access_breadcrumb($variables) {
}

/**
 * Implements hook_form_alter().
 */
function foundation_access_form_alter(&$form, &$form_state, $form_id) {
  // drop core class stuff
  if (!empty($form['actions']) && !empty($form['actions']['submit'])) {
    unset($form['actions']['submit']['#attributes']['class']);
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function foundation_access_form_page_node_form_alter(&$form, &$form_state) {
  $form['hidden_nodes']['#group'] = 'group_advanced';
  $form['hidden_nodes']['#type'] = 'div';
  $form['#groups']['group_advanced']->children[] = 'hidden_nodes';

  $form['book']['#group'] = 'group_advanced';
  $form['book']['#type'] = 'div';
  $form['#groups']['group_advanced']->children[] = 'book';

  $form['options']['#group'] = 'group_advanced';
  $form['options']['#type'] = 'div';
  $form['#groups']['group_advanced']->children[] = 'options';

  $form['author']['#group'] = 'group_advanced';
  $form['author']['#type'] = 'div';
  $form['#groups']['group_advanced']->children[] = 'author';

  $form['revision_information']['#group'] = 'group_advanced';
  $form['revision_information']['#type'] = 'div';
  $form['#groups']['group_advanced']->children[] = 'revision_information';

  // support for images in significance dropdown
  $form['field_instructional_significance']['und']['#materialize'] = array(
    'class' => 'left',
    'icon_path' => drupal_get_path('theme', 'foundation_access') . '/icons/pedagogy/',
  );
}

/**
 * Implements theme_pager().
 */
function foundation_access_pager($variables) {
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re-quantify).
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re-quantify)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number.
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array(
    'text' => array('html' => TRUE, 'text' => '<i class="material-icons black-text">first_page</i><span class="element-invisible">' . t('First page') . '</span>'),
    'element' => $element,
    'parameters' => $parameters,
  ));
  $li_previous = theme('pager_previous', array(
    'text' => array('html' => TRUE, 'text' => '<i class="material-icons black-text">chevron_left</i><span class="element-invisible">' . t('Previous page') . '</span>'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_next = theme('pager_next', array(
    'text' => array('html' => TRUE, 'text' => '<i class="material-icons black-text">chevron_right</i><span class="element-invisible">' . t('Next page') . '</span>'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_last = theme('pager_last', array(
    'text' => array('html' => TRUE, 'text' => '<i class="material-icons black-text">last_page</i><span class="element-invisible">' . t('Last page') . '</span>'),
    'element' => $element,
    'parameters' => $parameters,
  ));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('unavailable'),
          'data' => '<a class="black-text" href="">&hellip;</a>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'data' => theme('pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters,
            )),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('active'),
            'data' => '<a class="black-text" href=""><paper-button>' . $i . '</paper-button></a>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'data' => theme('pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters,
            )),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('unavailable'),
          'data' => '<a class="black-text" href="">&hellip;</a>',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_last,
      );
    }

    $pager_links = array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#attributes' => array('class' => array('pagination', 'col', 's12', 'center-align')),
    );

    $pager_links['#prefix'] = '<div class="row">';
    $pager_links['#suffix'] = '</div>';
    $pager_links = drupal_render($pager_links);
    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . $pager_links;
  }
}

/**
 *  Themes status messages
 */
function foundation_access_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_mapping = array(
    'error' => array(
      'icon' => 'error',
      'color' => 'white-text',
      'heading' => t('Errors'),
    ),
    'warning' => array(
      'icon' => 'warning',
      'color' => 'white-text',
      'heading' => t('Warnings'),
    ),
    'status' => array(
      'icon' => 'info',
      'color' => 'white-text',
      'heading' => t('Notifications'),
    ),
    'toast' => array(
      'icon' => 'info',
      'color' => 'black white-text',
      'heading' => '',
    ),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    if (!empty($status_mapping[$type])) {
      $output .= '<h2 class="alert-heading ' . $status_mapping[$type]['color'] . '"><iron-icon icon="' . $status_mapping[$type]['icon'] . '" class="status-icon"></iron-icon>' . $status_mapping[$type]['heading'] . '</h2>';
    }
    $output .= "<div role=\"alert\" aria-live=\"assertive\" data-alert class=\"alert-box\">";
    if (count($messages) > 1) {
      $output .= " <ul class=\"no-bullet top-level\">\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      // special case, single toast message
      if ($type == 'toast') {
        return '<paper-toast opened><div class="toast-content-container">' . $messages[0] . '</div></paper-toast>';
      }
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  if (!empty($output)) {
    return _foundation_access_make_toast($output);
  }
}

/**
 * Helper function to create a materialize toast notification.
 */
function _foundation_access_make_toast($message, $display_length = 4000, $class_name = NULL, $callback = NULL) {
  return '<paper-toast id="toastdrawer" class="fit-bottom" opened duration="0"><div class="paper-toast-label">' . t('Message center') . '<paper-button onclick="toastdrawer.toggle()" class="red darken-4 white-text close-button">' . t('Close') . '</paper-button></div><div class="toast-content-container">' . $message . '</div></paper-toast>';
}

/**
 * Implements theme_pager_link().
 */
function foundation_access_pager_link($variables) {
  $text = $variables['text'];
  $is_html = FALSE;
  if (is_array($text) && isset($text['html'])) {
    $is_html = $text['html'];
  }
  if (is_array($text) && isset($text['text'])) {
    $text = $text['text'];
  }
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];

  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    $attributes['class'] = 'black-text';
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  // @todo l() cannot be used here, since it adds an 'active' class based on the
  //   path only (which is always the current path for pager links). Apparently,
  //   none of the pager links is active at any time - but it should still be
  //   possible to use l() here.
  // @see http://drupal.org/node/1410574
  $attributes['href'] = url($_GET['q'], array('query' => $query));
  if ($is_html) {
    $output = filter_xss($text, array('i', 'em', 'strong', 'div', 'span'));
  }
  else {
    $output = check_plain($text);
  }
  return '<a tabindex="-1" ' . drupal_attributes($attributes) . '><paper-button>' . $output . '</paper-button></a>';
}

/**
 * Helper function for return a whitelist of allowed tags that can be
 * present in an SVG file.
 */
function _foundation_access_svg_whitelist_tags() {
  $allowed_tags = array(
    'animate',
    'animateColor',
    'animateMotion',
    'animateTransform',
    'mpath',
    'set',
    'circle',
    'ellipse',
    'line',
    'polygon',
    'polyline',
    'rect',
    'a',
    'defs',
    'glyph',
    'g',
    'marker',
    'mask',
    'missing-glyph',
    'pattern',
    'svg',
    'switch',
    'symbol',
    'desc',
    'metadata',
    'title',
    'feBlend',
    'feColorMatrix',
    'feComponentTransfer',
    'feComposite',
    'feConvolveMatrix',
    'feDiffuseLighting',
    'feDisplacementMap',
    'feFlood',
    'feFuncA',
    'feFuncB',
    'feFuncG',
    'feFuncR',
    'feGaussianBlur',
    'feImage',
    'feMerge',
    'feMergeNode',
    'feMorphology',
    'feOffset',
    'feSpecularLighting',
    'feTile',
    'feTurbulence',
    'font',
    'font-face',
    'font-face-format',
    'font-face-name',
    'font-face-src',
    'font-face-uri',
    'hkern',
    'vkern',
    'linearGradient',
    'radialGradient',
    'stop',
    'image',
    'path',
    'text',
    'use',
    'feDistantLight',
    'fePointLight',
    'feSpotLight',
    'altGlyph',
    'altGlyphDef',
    'altGlyphItem',
    'glyphRef',
    'textPath',
    'tref',
    'tspan',
    'clipPath',
    'color-profile',
    'cursor',
    'filter',
    'foreignObject',
    'script',
    'style',
    'view',
  );

  return $allowed_tags;
}

/**
 * Implementation of hook_wysiwyg_editor_settings_alter().
 */
function foundation_access_wysiwyg_editor_settings_alter(&$settings, $context) {
  // bring in materialize
  $settings['contentsCss'][] = base_path() . drupal_get_path('theme', 'foundation_access') . '/materialize_unwinding/css/materialize.css';
  $lmsless_classes = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
  $css = _foundation_access_contextual_colors($lmsless_classes);
  $settings['contentsCss'][] = $css;
  if (!isset($settings['bodyClass'])) {
    $settings['bodyClass'] = '';
  }
  $settings['bodyClass'] .= ' inner-wrap main-section etb-book elmsln-content-wrap node node node-page node-view-mode-full full html not-front logged-in no-sidebars page-node node-type-page ckeditor-edit-body';
  foreach ($GLOBALS['user']->roles as $role) {
    $settings['bodyClass'] .= ' role-' . drupal_html_class($role);
  }
  // Specify the custom config file that defines our font styles
  $settings['customConfig'] = base_path() . drupal_get_path('theme', 'foundation_access') . '/ckeditor_custom_config.js';
  // @todo figure out how to make ckeditor wrap this in w/ content editiable to be more accurate CSS application
  /* cke_editable cke_editable_themed cke_contents_ltr cke_show_borders">
    <main id="etb-tool-nav" data-offcanvas>
      <div class="inner-wrap">
        <section class="main-section etb-book">
          <div class="row">
            <div class="s12 m12 push-l1 l10 col" role="main">
              <div contenteditable="true" class="cke_editable_themed';
  */
}

/**
 * Generate CSS specific to this environment's colorset.
 */
function _foundation_access_contextual_colors($lmsless_classes) {
  // loop through our system specific colors
  $colors = array('primary', 'secondary', 'required', 'optional');
  $css = '';
  foreach ($colors as $current) {
    $color = theme_get_setting('foundation_access_' . $current . '_color');
    // allow other projects to override the FA colors
    drupal_alter('foundation_access_colors', $color, $current);
    // see if we have something that could be valid hex
    if (strlen($color) == 6 || strlen($color) == 3) {
      $color = '#' . $color;
      $css .= '.foundation_access-' . $current . "_color{color:$color;}";
      // specialized additions for each wheel value
      switch ($current) {
        case 'primary':
          $css .= ".etb-book h1,.etb-book h2,h1#page-title,h2#page-title {color: $color;}";
        break;
        case 'secondary':
          $css .= ".etb-book h3,.etb-book h4,.etb-book h5 {color: $color;}";
        break;
        case 'required':
          $css .= "div.textbook_box_required li:hover:before{border-color: $color;} div.textbook_box_required li:before {background: $color;} div.textbook_box_required { border: 2px solid $color;} .textbook_box_required h3 {color: $color;}";
        break;
        case 'optional':
          $css .= "div.textbook_box_optional li:hover:before{border-color: $color;} div.textbook_box_optional li:before {background: $color;} div.textbook_box_optional { border: 2px solid $color;} .textbook_box_optional h3 {color: $color;}";
        break;
      }
    }
  }
  return $css;
}

/**
 * Remove white space from what's returned
 */
function _foundation_access_drop_whitespace($content) {
  // don't do it for user 1
  if ($GLOBALS['user']->uid == 1) {
    return $content;
  }
  return preg_replace('~>\s+<~', '><', $content);
}

/**
 * Return the tabbed items to shift items into the ... menu.
 */
function _foundation_access_move_tabs() {
  $tabs = array(
    'node/%/display',
    'node/%/replicate',
    'node/%/addanother',
    'node/%/revisions',
    'node/%/devel',
    'user/%/devel',
    'user/%/imce',
    'user/%/view',
    'user/%/display',
    'user/%/replicate',
    'user/%/data',
    'file/%/devel',
    'file/%/delete',
  );
  // allow modules to dictate what to remove
  drupal_alter('foundation_access_tabs', $tabs);
  return $tabs;
}
