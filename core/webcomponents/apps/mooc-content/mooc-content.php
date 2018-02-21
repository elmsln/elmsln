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
    // we allow the left to have blocks so place them there
    $blocks = block_get_blocks_by_region('sidebar_first');
    $blocks = drupal_render($blocks);
    // pull together the right side options
    $options = _mooc_content_render_options();
    // support custom colors / system level styling
    if (module_exists('cis_lmsless')) {
      $colors = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
      $css = _foundation_access_contextual_colors($colors);
    }
    $return = array(
      'title' => _mooc_content_get_title(),
      'topNavigation' => $navigation,
      'content' => $content,
      'bookOutline' => $outline,
      'blocks' => $blocks,
      'styles' => $css,
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
 * in the app so we know that routing should actually trigger a node id to load.
 */
function _mooc_content_get_aliases() {
  $aliases = &drupal_static(__FUNCTION__);
  if (!$aliases) {
    $result = db_query("SELECT alias,source FROM {url_alias} WHERE source LIKE 'node/%' AND language='und' ORDER BY pid ASC");
    $aliases = $result->fetchAllKeyed();
    $front = variable_get('site_frontpage', 'node');
    // special case for homepage that points to a node
    if (strpos($front, 'node/') === 0) {
      $aliases['/'] = $front;
      $aliases[''] = $front;
      $aliases[base_path()] = $front;
    }
  }
  return $aliases;
}

/**
 * Get active title
 */
function _mooc_content_get_title() {
  $node = _mooc_content_get_active();
  return $node->title;
}
/**
 * Get active nid
 */
function _mooc_content_get_nid() {
  $node = _mooc_content_get_active();
  return $node->nid;
}
/**
 * Get a single alias
 */
function _mooc_content_get_alias() {
  $node = _mooc_content_get_active();
  $aliases = array(drupal_get_path_alias('node/' . $node->nid) => 'node/' . $node->nid);
  return drupal_json_encode($aliases);
}

/**
 * Get the outline area title
 */
function _mooc_content_outline_title(){
  $node = _mooc_content_get_active();
  $tmp = _mooc_nav_block_get_nav($node);
  return $tmp['label'];
}

/**
 * Top navigation
 */
function _mooc_content_render_navigation() {
  $node = _mooc_content_get_active();
  // render navigation
  $vars = _mooc_helper_book_nav_build($node);
  // output contents by passing through the wrapper theme function
  $tmp = theme('book_sibling_nav_wrapper', $vars);
  return render($tmp);
}

/**
 * Oddly specific I know but it's one of the heaviest calls
 * in the entire system.
 */
function _mooc_content_get_outline_data() {
  $bookoutline = _mooc_helper_book_outline(TRUE);
  return array(
    'status' => 200,
    'data' => array(
      'outline' => drupal_render($bookoutline),
      'aliases' => _mooc_content_get_aliases(),
    )
  );
}

/**
 * Get the page options based on this user / path.
 */
function _mooc_content_render_options() {
  $node = _mooc_content_get_active();
  if (node_access('update', $node)) {
    $edit_path = base_path() . 'node/' . $node->nid . '/edit';
  }
  $cis_lmsless = _cis_lmsless_get_distro_classes();
  $distro = elmsln_core_get_profile_key();
  // ok, get all that ugly content together
  $content = '';
  if (isset($edit_path)) {
    $content .= '
      <lrnsys-button id="edit-tip" href="' . $edit_path . '" class="r-header__icon elmsln-edit-button" data-jwerty-key="e" data-voicecommand="edit" hover-class="' . $cis_lmsless[$distro]['text'] . '" inner-class="no-padding" icon="editor:mode-edit" icon-class="blue-text" alt="' . t('Edit page') . '"><span class="element-invisible">' . t('Edit page') . '</span>
      </lrnsys-button>';
  }
  $content .= '<paper-menu-button dynamic-align>
    <paper-icon-button id="printoptions" icon="print" slot="dropdown-trigger" alt="' . t('Print options') . '"></paper-icon-button>
    <paper-listbox slot="dropdown-content">
      <a target="_blank" href="' . base_path() . 'book/export/html/' . $node->nid . '" class="accessible-grey-text"><paper-item>' . t('Page') . '</paper-item></a>';
  // support print / book printing
  if (user_access('access printer-friendly version')) {
    $bid = $node->book['bid'];
    if ($bid) {
      $content .= '<a tabindex="-1" target="_blank" href="' . base_path() . 'book/export/html/' . $bid . '" class="accessible-grey-text"><paper-item>' . t('Outline') . '</paper-item></a>';
    }
  }
  // print to pdf
  if (user_access('access PDF version')) {
    $content .= '<a tabindex="-1" target="_blank" href="' . base_path() . 'printpdf/' . $node->nid . '" class="accessible-grey-text"><paper-item>' . t('PDF') . '</paper-item></a>';
  }
  $content .='</paper-listbox></paper-menu-button><paper-tooltip for="printoptions" animation-delay="200">' . t('Print options') . '</paper-tooltip>';
  return $content;
}

/**
 * Render content; stinking weird but basically the entire page.tpl.php
 */
function _mooc_content_render_content() {
  $node = _mooc_content_get_active();
  $content = '';
  // support for banner block
  if (module_exists('mooc_content_theming')) {
    $content .= _mooc_content_theming_banner_block($node);
  }
  $content .= drupal_render(node_view($node));
  return $content;
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