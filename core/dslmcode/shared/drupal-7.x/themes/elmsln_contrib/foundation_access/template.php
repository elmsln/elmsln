<?php
// global cdn materialize version
define('FOUNDATION_ACCESS_MATERIALIZE_VERSION', '0.97.8');
/**
 * Adds CSS classes based on user roles
 * Implements template_preprocess_html().
 *
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
  $css = _foundation_access_contextual_colors($variables['lmsless_classes']);

  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'foundation_access');

  drupal_add_css($css, array('type' => 'inline', 'group' => CSS_THEME, 'weight' => 999));
  // elmsln icons
  drupal_add_css(drupal_get_path('theme', 'foundation_access') . '/fonts/elmsln/elmsln-font-styles.css', array('group' => CSS_THEME, 'weight' => -1000));
  // google font / icons from google
  drupal_add_css('//fonts.googleapis.com/css?family=Material+Icons%7CDroid+Serif:400,700,400italic,700italic%7COpen+Sans:300,600,700', array('type' => 'external', 'group' => CSS_THEME, 'weight' => 1000));
  $libraries = libraries_get_libraries();
  if (!_entity_iframe_mode_enabled()) {
    if (isset($libraries['jquery.vibrate.js'])) {
      drupal_add_js($libraries['jquery.vibrate.js'] .'/jquery.vibrate.min.js');
      drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy/js/vibrate-enable.js');
    }
    // gifs need to be done as a player for accessibility reasons
    if (isset($libraries['jquery.vibrate.js'])) {
      drupal_add_js($libraries['freezeframe.js'] .'/src/js/vendor/imagesloaded.pkgd.js');
      drupal_add_js($libraries['freezeframe.js'] .'/build/js/freezeframe.js');
      drupal_add_css($libraries['freezeframe.js'] .'/build/css/freezeframe_styles.min.css');
      drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy/js/freezeframe-enable.js');
    }
  }
  // see if we have it locally before serviing CDN
  // This allows EASY CDN module to switch to CDN later if that's the intention
  if (isset($libraries['materialize'])) {
    drupal_add_css($libraries['materialize'] .'/css/materialize.css', array('weight' => -1000));
    drupal_add_js($libraries['materialize'] .'/js/materialize.js', array('scope' => 'footer', 'weight' => 1000));
  }
  else {
    drupal_add_css('//cdnjs.cloudflare.com/ajax/libs/materialize/' . FOUNDATION_ACCESS_MATERIALIZE_VERSION . '/css/materialize.min.css', array('type' => 'external', 'weight' => -1000));
    drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/materialize/' . FOUNDATION_ACCESS_MATERIALIZE_VERSION . '/js/materialize.min.js', array('type' => 'external', 'scope' => 'footer', 'weight' => 1000));
  }
  // support for our legacy; adding in css/js for foundation; this requires a forcible override in shared_settings.php
  if (variable_get('foundation_access_legacy', FALSE)) {
    drupal_add_css(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/css/foundation.min.css', array('weight' => -1000));
    drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/js/modernizr.js', array('scope' => 'footer', 'weight' => 1000));
    drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/js/foundation.min.js', array('scope' => 'footer', 'weight' => 1001));
    drupal_add_js(drupal_get_path('theme', 'foundation_access') . '/legacy_zurb/js/enable-foundation.js', array('scope' => 'footer', 'weight' => 2000));
  }
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
    $variables['favicon_path'] = $variables['theme_path'] . '/legacy/icons/elmsicons/elmsln.ico';
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
          $icon = '<i class="material-icons">' . $element['#materialize']['icon'] . '</i>';
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
          <a id="collapse-item-id-' . $anchor . '" href="#collapse-item-' . $anchor . '" class="collapsible-header waves-effect cis-lmsless-waves' . $collapse . '"' . drupal_attributes($element['#attributes']) .'>' .
            $icon . $element['#title'] .
          '
          </a>
          <div class="collapsible-body">
            <div class="elmsln-collapsible-body" aria-labelledby="collapse-item-id-' . $anchor . '" role="tabpanel">
              ' . $body . '
            </div>
            <div class="divider cis-lmsless-background"></div>
          </div>
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
  $variables['contentwrappers'] = _elmsln_core_path_is_wrapped(current_path());
  $menu_item = menu_get_item();
  // allow modules to supply accessibility enhancements to the menu tho not in entity iframe mode
  if (!_entity_iframe_mode_enabled()) {
    $a11y = module_invoke_all('fa_a11y');
    drupal_alter('fa_a11y', $a11y);
    // add in the form api wrapper meta properties to render as materialize collapse
    $a11y['#type'] = 'fieldset';
    $a11y['#materialize'] = array(
      'type' => 'collapsible_wrapper'
    );
    $a11y['#attributes'] = array(
      'class' => array('collapsible'),
      'data-collapsible' => 'accordion',
    );
    $variables['a11y'] = drupal_render($a11y);
  }
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
    $variables['cis_lmsless'] = _cis_lmsless_theme_vars();
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
  // support for entity_iframe
  if (module_exists('entity_iframe')) {
    $block = entity_iframe_block_view('entity_iframe_block');
    if (!empty($block['content'])) {
      $variables['cis_shortcodes'] .= $block['content'];
    }
  }
  // wrap non-node content in an article tag
  if (isset($variables['page']['content']['system_main']['main'])) {
    $variables['page']['content']['system_main']['main']['#markup'] = '<article class="l12 col view-mode-full">' . $variables['page']['content']['system_main']['main']['#markup'] . '</article>';
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
      <div class="elmsln-file-btn-trigger btn">
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
  }
}

/**
 * Implements theme_button().
 */
function foundation_access_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }
  $element['#attributes']['class'][] = 'btn';
  // wrap classes on an upload button
  if ($variables['element']['#value'] == 'Upload') {
    return '
    <div class="col s12 m4 input-field">
      <button ' . drupal_attributes($element['#attributes']) . '>' . $element['#value'] . '</button>
    </div>';
  }
  else {
    return '<button ' . drupal_attributes($element['#attributes']) . '>' . $element['#value'] . '</button>';
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
  // if not, attempt to use the thumbnail created by the video upload field
  elseif (isset($variables['content']['field_external_media']['#items'][0]['thumbnail_path'])) {
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
        <button class="start waves-effect waves-light btn col s3 blue push-s2"><i class="material-icons left">play_arrow</i>' . t('start') . '</button>
        <button class="stop waves-effect waves-light btn col s3 red pull-s2 right"><i class="material-icons left">stop</i>' . t('stop') . '</button>
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
    '#type' => 'button',
    '#value' => check_plain($variables['button_label']),
    '#attributes' => array(
      'class' => array('clipboardjs-button', 'zmdi', 'zmdi-copy'),
      'data-clipboard-alert' => 'toast',
      'data-clipboard-alert-text' => $variables['alert_text'],
      'data-clipboard-target' => '#' . $uniqid,
      'onClick' => 'return false;',
    ),
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
    if (_cis_connector_system_type() != 'service') {
      $element['#localized_options']['query']['elmsln_course'] = _cis_connector_course_context();
      $element['#localized_options']['query']['elmsln_section'] = _cis_connector_section_context();
    }
    $element['#localized_options']['attributes']['class'][] = 'btn-floating';
    $element['#localized_options']['attributes']['class'][] = 'elmsln-btn-floating';
    // load up a map of icons and color associations
    $icon_map = _elmsln_core_icon_map();
    $icon = str_replace(' ', '_', drupal_strtolower($title));
    if (isset($icon_map[$icon])) {
      if (strpos($element['#href'], 'elmsln/redirect') === 0) {
        $element['#localized_options']['attributes']['class'][] = 'elmsln-core-external-context-apply';
      }
      $element['#localized_options']['attributes']['class'][] = $icon_map[$icon]['color'];
      $element['#localized_options']['attributes']['class'][] = 'darken-3';
      $title = '<i class="material-icons white-text left">' . $icon_map[$icon]['icon'] . '</i>' . $title;
      $element['#localized_options']['html'] = TRUE;
    }
    else {
      $lmsless_classes = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
      $element['#localized_options']['attributes']['class'][] = $lmsless_classes['color'];
      $element['#localized_options']['attributes']['class'][] = 'black-text';
      $element['#localized_options']['attributes']['class'][] = $lmsless_classes['light'];
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
      $element['#attributes']['class'][] = 'has-children';
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
 * Implements menu_tree__menu_elmsln_settings.
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
 * Helper to generate a menu link in a consistent way at the bottom.
 */
function _foundation_access_single_menu_link($element) {
  $options = $element['#localized_options'];
  $options['html'] = TRUE;
  $title = check_plain($element['#title']);
  // ensure class array is at least set
  if (empty($element['#attributes']['class'])) {
    $element['#attributes']['class'] = array();
  }
  $classes = implode(' ', $element['#attributes']['class']);
  $options['attributes']['class'] = $element['#attributes']['class'];
  $icon = 'page';
  if (isset($options['fa_icon'])) {
    $icon = $options['fa_icon'];
  }
  return '<li>' . l($title, $element['#href'], $options) . '</li>';
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
  // account for sub menu things being rendered differently
  if (empty($sub_menu)) {
    // ending element
    $return .= _foundation_access_single_menu_link($element);
  }
  else {
    // ensure class array is at least set
    if (empty($element['#attributes']['class'])) {
      $element['#attributes']['class'] = array();
    }
    // active trail set classes based on that since its a core class
    if (in_array('active-trail', $element['#attributes']['class'])) {
      $element['#attributes']['class'][] = 'expanded';
      $element['#attributes']['class'][] = 'active';
    }
    // calculate relative depth
    $depth = $element['#original_link']['depth'] - 2;
    // generate a short name
    $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($title)) . '-' . $element['#original_link']['mlid'];
    // extract nid
    $nid = str_replace('node/', '', $element['#href']);
    // test for active class, meaning this should be expanded by default
    if ($element['#original_link']['p3'] == 0) {
      $return .= '
      <li class="has-submenu level-' . $depth . '-top ' . implode(' ', $element['#attributes']['class']) . '">' . "\n" .
      '<a href="#' . $short . '-panel">' . "\n";
      $labeltmp = _foundation_access_auto_label_build($word, $number, $counter);
      if (!empty($labeltmp)) {
        $return .= '<h2>' . $labeltmp . '</h2>' . "\n";
      }
      $return .= '<h3>' . $title . '</h3>' . "\n" .
      '</a>' . "\n" .
      '<ul class="left-submenu level-' . $depth . '-sub">'  . "\n" .
      '<div>'  . "\n";
      $labeltmp = _foundation_access_auto_label_build($word, $number, $counter);
      if (!empty($labeltmp)) {
        $return .= '<h2>' . $labeltmp . '</h2>' . "\n";
      }
      $return .= '<h3>' . _foundation_access_single_menu_link($element) . '</h3>' . "\n" .
      '</div>'  . "\n" .
      '<li class="back">'  . "\n" .
      '<a href="#fa-back" class="kill-content-before middle-align-wrap center-align-wrap"><div class="icon-arrow-left-black back-arrow-left-btn"></div><span>' . t('Back') . '</span></a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
      $counter++;
    }
    else {
      $return ='<li class="has-submenu level-' . $depth . '-top ' . implode(' ', $element['#attributes']['class']) . '"><a href="#elmsln-menu-sub-level-' . hash('md5', 'emsl' . $title) . '"><span class="outline-nav-text">' . $title . '</span></a>' . "\n" .
      '<ul class="left-submenu level-' . $depth . '-sub">'  . "\n" .
      '<div>'  . "\n";
      $labeltmp = _foundation_access_auto_label_build($word, $number, $counter);
      if (!empty($labeltmp)) {
        $return .= '<h2>' . $labeltmp . '</h2>' . "\n";
      }
      $return .= '<h3>' . _foundation_access_single_menu_link($element) . '</h3>' . "\n" .
      '</div>'  . "\n" .
      '<li class="back">'  . "\n" .
      '<a href="#fa-back" class="kill-content-before middle-align-wrap center-align-wrap"><div class="icon-arrow-left-black back-arrow-left-btn"></div><span>' . t('Back') . '</span></a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
    }
  }
  return $return;
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
  $args = arg();
  // account for print module and book print out
  if ($args[0] == 'book' && $args[1] = 'export' && $args[2] == 'html') {
    $path = base_path() . drupal_get_path('theme', 'foundation_access') . '/';
    $css = array(
      $path . 'legacy/icons/faccess-icons/output/icons.data.svg.css',
      $path . 'legacy/bower_components/material-design-iconic-font/dist/css/material-design-iconic-font.min.css',
      $path . 'legacy/css/system.base.css',
      $path . 'legacy/css/app.css',
      $path . 'legacy/css/normalize.css',
      $path . 'legacy/css/comparison.css',
      $path . 'app/dist/css/styles.css',
      $path . 'css/tweaks.css',
      $path . 'fonts/elmsln/elmsln-font-styles.css',
      '//fonts.googleapis.com/css?family=Material+Icons|Droid+Serif:400,700,400italic,700italic|Open+Sans:300,600,700)',

    );
    $libraries = libraries_get_libraries();
    // see if we have it locally before serviing CDN
    // This allows EASY CDN module to switch to CDN later if that's the intention
    if (isset($libraries['materialize'])) {
      $css[] = base_path() . $libraries['materialize'] . '/css/materialize.css';
    }
    else {
      $css[] = '//cdnjs.cloudflare.com/ajax/libs/materialize/' . FOUNDATION_ACCESS_MATERIALIZE_VERSION . '/css/materialize.min.css';
    }
    // parse returned locations array and manually add to html head
    foreach ($css as $key => $file) {
      $head_elements['fa_print_' . $key] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#attributes' => array(
          'type' => 'text/css',
          'rel' => 'stylesheet',
          'href' => $file,
        ),
      );
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
 * Implements hook_preprocess().
 */
function foundation_access_preprocess_cis_dashbord(&$variables, $hook) {
  $variables['theme_hook_suggestions'][] = 'cis_dashboard';
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
    'icon_path' => drupal_get_path('theme', 'foundation_access') . '/legacy/icons/pedagogy/',
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
            'class' => array('waves-effect', 'cis-lmsless-waves', 'cis-lmsless-background'),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('active'),
            'data' => '<a class="black-text" href="">' . $i . '</a>',
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
            'class' => array('waves-effect', 'cis-lmsless-waves', 'cis-lmsless-background'),
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

  $status_heading = array(
    'error' => t('Error message'),
    'status' => t('Status message'),
    'warning' => t('Warning message'),
  );

  $status_mapping = array(
    'error' => 'alert',
    'status' => 'success',
    'warning' => 'secondary'
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    if (isset($status_mapping[$type])) {
      $output .= "<div role=\"alert\" aria-live=\"assertive\" data-alert class=\"alert-box $status_mapping[$type]\">\n";
    }
    else {
      $output .= "<div role=\"alert\" aria-live=\"assertive\" data-alert class=\"alert-box\">\n";
    }

    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul class=\"no-bullet\">\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= '<a href="#close-dialog" class="close" aria-label="' . t('Hide messages') . '" data-voicecommand="hide messages" data-jwerty-key="Esc">&#215;</a>';
    $output .= "</div>\n";
  }

  return $output;
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
  return '<a' . drupal_attributes($attributes) . '>' . $output . '</a>';
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
 * Converts youtube / vimeo URLs into things we can embed
 * @param  string $video_url a well formed youtube/vimeo direct URL.
 * @return string            the address that's valid for embed codes.
 */
function _foundation_access_video_url($video_url) {
  // account for the broken form of embed code from youtube
  if (strpos($video_url, 'youtube') && !strpos($video_url, 'embed')) {
    $tmp = drupal_parse_url($video_url);
    $yvid = '';
    // check for youtube url vs embed
    if (isset($tmp['query']['v'])) {
      $yvid = $tmp['query']['v'];
      return 'https://www.youtube.com/embed/' . $yvid;
    }
  }
  // account for the broken form of embed code from vimeo
  if (strpos($video_url, 'vimeo') && !strpos($video_url, 'player')) {
    // rip out from embed based url
    $vpath = explode('/', $video_url);
    $part = array_pop($vpath);
    // drop the autoplay property cause it conflicts with what we're doing
    $part = str_replace('autoplay=1', '', $part);
    return 'https://player.vimeo.com/video/' . $part;
  }
  // didn't know what to do or it was already well formed
  return $video_url;
}

/**
 * Implementation of hook_wysiwyg_editor_settings_alter().
 */
function foundation_access_wysiwyg_editor_settings_alter(&$settings, $context) {
  // google font / icons from google
  $settings['contentsCss'][] = '//fonts.googleapis.com/css?family=Material+Icons|Droid+Serif:400,700,400italic,700italic|Open+Sans:300,600,700)';
  // bring in materialize
  $libraries = libraries_get_libraries();
  // see if we have it locally before serviing CDN
  // This allows EASY CDN module to switch to CDN later if that's the intention
  if (isset($libraries['materialize'])) {
    $settings['contentsCss'][] = base_path() . $libraries['materialize'] .'/css/materialize.css';
  }
  else {
    $settings['contentsCss'][] = '//cdnjs.cloudflare.com/ajax/libs/materialize/' . FOUNDATION_ACCESS_MATERIALIZE_VERSION . '/css/materialize.min.css';
  }
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
  $css = '
  .pagination li.active,
  ul.pagination li:hover a, ul.pagination li a:focus, ul.pagination li:hover button, ul.pagination li button:focus {
    color: ' . $lmsless_classes['code_text'] . ';
    background-color: ' . $lmsless_classes['code'] . '
  }
  .btn,
  .btn-large {
    background-color: ' . $lmsless_classes['code_text'] . ';
  }
  .dropdown-content li > a, .dropdown-content li > span,
  form.node-form div.field-group-htabs-wrapper .horizontal-tabs a.fieldset-title,
  a {
    color: ' . $lmsless_classes['code_text'] . ';
  }
  [type="checkbox"]:checked + label:before {
    border-right: 2px solid ' . $lmsless_classes['code_text'] . ';
    border-bottom: 2px solid ' . $lmsless_classes['code_text'] . ';
  }';
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
          $css .= ".etb-book h1,.etb-book h2 {color: $color;}";
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
  return $tabs;
}
