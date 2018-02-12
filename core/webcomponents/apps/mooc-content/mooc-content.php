<?php
/**
 * @file
 * Code for MOOC content app
 */
// hook up the book service
define('__ROOT__', dirname(dirname(dirname(__FILE__))));
require_once(__ROOT__.'/services/LRNAppBookService.php');

/**
 * Callback for apps/mooc-content/data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _mooc_content_data($machine_name, $app_route, $params, $args) {
  $status = 404;
  $return = array();
  $node = _mooc_content_get_active();
  if (isset($node->nid)) {
    $navigation = _mooc_content_render_navigation();
    // render content
    $content = _mooc_content_render_content();
    // render outline w/ array
    $outline = _mooc_nav_block_mooc_nav_block($node);
    // pull together the right side options
    $options = _mooc_content_render_options();
    $return = array(
      'title' => _mooc_content_get_title(),
      'topNavigation' => $navigation,
      'content' => $content,
      'bookOutline' => $outline,
      'options' => $options,
    );
    $status = 200;
  }
  return array(
    'status' => $status,
    'data' => $return
  );
}

/**
 * Return all aliases for comparison in the event of them being clicked
 * in the app so we know that routing should actually trigger a node id to load
 */
function _mooc_content_get_aliases() {
  $aliases = &drupal_static(__FUNCTION__);
  if (!$aliases) {
    $result = db_query("SELECT source, alias FROM {url_alias} WHERE source LIKE 'node/%' AND language='und' ORDER BY pid ASC");
    $aliases = $result->fetchAllKeyed();
    // flip for easier front end targetting of the array keys
    $aliases = array_flip($aliases);
  }
  return drupal_json_encode($aliases);
}

function _mooc_content_get_title() {
  $node = _mooc_content_get_active();
  return $node->title;
}

function _mooc_content_render_outline(){
  $node = _mooc_content_get_active();
  $tmp = _mooc_nav_block_mooc_nav_block($node);
  return $tmp['content'];
}

function _mooc_content_outline_title(){
  $node = _mooc_content_get_active();
  $tmp = _mooc_nav_block_get_nav($node);
  return $tmp['label'];
}

function _mooc_content_render_navigation() {
  $node = _mooc_content_get_active();
  // render navigation
  $vars = _mooc_helper_book_nav_build($node);
  // output contents by passing through the wrapper theme function
  $tmp = theme('book_sibling_nav_wrapper', $vars);
  return render($tmp);
}

/**
 * Get the page options based on this user / path.
 */
function _mooc_content_render_options() {
  $node = _mooc_content_get_active();
  $edit_path = base_path() . 'node/' . $node->nid . '/edit';
  $cis_lmsless = _cis_lmsless_get_distro_classes();
  $distro = elmsln_core_get_profile_key();
  // support for cis_shortcodes
  if (module_exists('cis_shortcodes')) {
    $shortblock = cis_shortcodes_block_view('cis_shortcodes_block');
    if (!empty($shortblock['content'])) {
      $cis_shortcodes = $shortblock['content'];
    }
    else {
      $cis_shortcodes = '';
    }
  }
  else {
    $cis_shortcodes = '';
  }
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
  $a11y = drupal_render($a11y);
  // ok, get all that ugly content together
  $content = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>
  <ul class="elmsln--page--operations">';
  if (isset($edit_path)) {
    $content .= '
    <li class="page-op-button">
      <lrnsys-button id="edit-tip" href="' . $edit_path . '" class="r-header__icon elmsln-edit-button" data-jwerty-key="e" data-voicecommand="edit" hover-class="' . $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'] . '" icon="editor:mode-edit" alt="' . t('Edit content') . '">
      </lrnsys-button>
    </li>';
  }
  if (!empty($cis_shortcodes)) {
    $content .= '
    <li class="page-op-button">
      <lrnsys-drawer hover-class="' . $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'] . '" align="right" alt="' . t('Embed this content') . '" icon="share" header="' . t('Embed this content') . '" data-jwerty-key="s" data-voicecommand="open embed (menu)">
        ' . $cis_shortcodes . '
      </lrnsys-drawer>
    </li>';
  }
  if (!empty($a11y)) {
    $content .= '
    <li class="page-op-button">
      <lrnsys-drawer hover-class="' . $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'] . '" align="right" alt="' . t('Your preferences') . '" icon="accessibility" header="' . t('Preferences') . '" data-jwerty-key="a" data-voicecommand="open preferences (menu)">
        ' . $a11y . '
      </lrnsys-drawer>
    </li>';
  }
  // @todo this whole tabs area needs to be loaded correctly ahead of time
  $content .= '<li class="page-op-button">';
  if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)) {
    $content .= '<lrnsys-button id="more-options-tip" class="r-header__icon elmsln-more-button elmsln-dropdown-button" data-activates="elmsln-more-menu" aria-controls="elmsln-more-menu" aria-expanded="false" data-jwerty-key="m" data-voicecommand="open more (menu)" hover-class="' . $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'] . '" icon="more-vert" alt="'. t('Less common operations') . '">
    </lrnsys-button>
    <ul id="elmsln-more-menu" class="dropdown-content" aria-hidden="true" tabindex="-1">';
    if (!empty($tabs)) {
      $content .= render($tabs);
      if (!empty($tabs2)) {
        $content .= render($tabs2);
      }
    }
    if (!empty($action_links)) {
      $content .= render($action_links);
    }
    if (isset($tabs_extras)) {
      $content .= ksort($tabs_extras);
      foreach ($tabs_extras as $group) {
        foreach ($group as $button) {
          $content .= '<li class="elmsln-more-menu-option">' . $button . '</li>';
        }
      }
    }
    $content .= '</ul>
    <paper-button disabled class="disabled elmsln-more-menu-button">
      <iron-icon icon="more-vert"></iron-icon>
    </paper-button>';
  }
  $content .= '</li></ul>';
  return $content;
}

/**
 * Render content; stinking weird but basically the entire page.tpl.php
 */
function _mooc_content_render_content() {
  $node = _mooc_content_get_active();
  return drupal_render(node_view($node));
}

/**
 * Simple fast node load.
 */
function _mooc_content_get_active() {
  $node = &drupal_static(__FUNCTION__);
  if (!$node) {
    if (isset($GLOBALS['moocappbook'])) {
      $node = $GLOBALS['moocappbook'];
    }
    else {
      $service = new LRNAppBookService();
      $node = $service->loadActiveNode();
      $GLOBALS['moocappbook'] = $node;
    }
  }
  return $node;
}