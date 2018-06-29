<?php

define('LRNAPP_BOOK_DEFAULT_FORMAT', 'textbook_editor');
define('LRNAPP_BOOK_DEFAULT_ICON', 'description');

class LRNAppBookService {

  /**
   * Try to load active from URL
   */
  public function loadActiveNode() {
    $node = FALSE;
    $arg = arg(3);
    $argfallback = arg(4);
    // check for node expressed directly via URL; less optimal
    if (!empty($_GET['node']) && is_numeric($_GET['node'])) {
      $node = node_load($_GET['node']);
    }
    // check for arg 3 for pattern apps/lrnapp-book/node/{id}
    else if (!empty($arg) && is_numeric($arg) ) {
      $node = node_load($arg);
    }
    // check for arg 4 for pattern apps/lrnapp-book/api/page/{id}
    else if (!empty($argfallback) && is_numeric($argfallback) ) {
      $node = node_load($argfallback);
    }
    else {
      $node = menu_get_object();
    }
    return $node;
  }
  /**
   * Create Stub Page based on book nid
   */
  public function createStubPage($data) {
    global $user;
    $node = new stdClass();
    $node->title = t('New page');
    $node->type = 'page';
    $node->uid = $user->uid;
    $node->status = 1;
    // load parent based on nid
    $parent = $this->getPage($data['pid']);
    $node->book = array(
      'bid' => $data['bid'],
      'plid' => $parent->book['mlid'],
    );
    if (node_access('create', $node)) {
      try {
        node_save($node);
        if (isset($node->nid)) {
          return $this->encodePage($node);
        }
      }
      catch (Exception $e) {
        throw new Exception($e->getMessage(), 1);
      }
    }
    return FALSE;
  }

  /**
   * Get Outline at the currently active item level
   */
  public function getOutline($id = NULL, $book = FALSE) {
    $items = array();
    // support loading off the active or a passed in one
    if (empty($id)) {
      $node = $this->loadActiveNode();
    }
    else {
      $node = node_load($id);
    }
    // sanity check
    if (!empty($node->book)) {
      // if the outline is for the book at the top then we need
      // mlid instead of parent since it's in control of all structure
      if ($book) {
        $book = node_load($node->book['bid']);
        // load everything for this book
        $results = db_select('menu_links', 'ml')
          ->fields('ml')
          ->condition('p1', $book->book['mlid'], '=')
          ->orderBy('weight', 'ASC')
          ->execute()
          ->fetchAll();
      }
      else {
        // see if this is an indie page or not
        if (isset($node->book['has_children']) && $node->book['has_children']) {
          $results = db_select('menu_links', 'ml')
            ->fields('ml')
            ->condition('plid', $node->book['mlid'], '=')
            ->orderBy('weight', 'ASC')
            ->execute()
            ->fetchAll();
          // push the container as the 1st page; this makes downstream UX
          // better in our book player
          $items[$node->nid] = $node;
        }
        else {
          // load all items that share the same parent as the current item
          $results = db_select('menu_links', 'ml')
            ->fields('ml')
            ->condition('plid', $node->book['plid'], '=')
            ->orderBy('weight', 'ASC')
            ->execute()
            ->fetchAll();
        }
      }
      // associate the items that are siblings of the same parent
      $nids = array();
      $tmpary = array();
      foreach ($results as $item) {
        $tmpary[$item->mlid] = (array)$item;
        $nids[str_replace('node/', '', $item->link_path)] = $item->mlid;
      }
      // ensure we have nids, there is a possibility of corruption in
      // the menu_links table where an item that once had children no longer does
      // but that isn't reflected in the items as updated. It's rare but possible
      if (!empty($nids)) {
        // node access check
        $select = db_select('node', 'n');
        $select->addField('n', 'nid');
        $select->condition('n.status', 1);
        $select->condition('n.nid', array_keys($nids), 'IN');
        $select->addTag('node_access');
        $nidslist = $select->execute()->fetchCol();
        // compare against what we are ALLOWED to show so order is maintained
        foreach ($nids as $nid => $mid) {
          // this suggests an item was removed bc of access rights
          // the pulled list doesn't have an item from the original
          if (!in_array($nid, $nidslist)) {
            unset($tmpary[$nids[$nid]]);
          }
        }
        // can skip other stuff cause direct DB query takes into account access
        foreach ($tmpary as $mlink) {
          $nid = str_replace('node/', '', $mlink['link_path']);
          $item = node_load($nid);
          $items[$nid] = $item;
        }
        // encode whatever we just found
        $items = $this->encodePages($items);
      }
    }
    return $items;
  }
  /**
   * Output in a simplified format for rendering which is recursively generated.
   * @param  array  $pages     all encoded pages available for output
   * @param  array  $menu      menu items from drupal; children pass down for recursion
   * @param  string $path      base path to add
   * @param  array  &$output   recursively produced array; by reference
   * @return array             returns $output variable once we have the whole thing
   */
  public function encodeOutline($pages = array(), $menu = array(), $path = '/') {
    if (is_array($menu)) {
      $index = 0;
      foreach ($menu as $menu_item) {
        $menu_link = $menu_item['link'];
        $id = str_replace('node/', '', $menu_link['link_path']);
        $output[$id] = array(
          'title' => $menu_link['link_title'],
          'url' => base_path() . $path . $menu_link['link_path'],
          'status' => ($encoded_page->attributes->hidden ? 'disabled' : 'available'),
          'value' => 0,
          'max' => 100,
          'icon' => $pages[$id]->meta->icon,
          'iconComplete' => 'check',
          'type' => 'node',
          'id' => $id,
          'parentid' => $pages[$id]->relationships->parent->id,
          'children' => array(),
          'number' => $index,
        );
        // if we have to go down, do it now
        if (!empty($menu_item['below'])) {
          $output[$id]['children'] = $this->encodeOutline($pages, $menu_item['below'], $path);
        }
      }
    }
    return $output;
  }

  /**
   * Render the outline that we've been passed in a recursive manner.
   * @param  array  $outline   items that can be rendered
   * @param  string  &$output  part of the outline being rendered
   * @return string            the full output being rendered and returned
   */
  public function renderOutline($outline = array(), $depth = 1) {
    $output = '';
    if (is_array($outline)) {
      $index = 0;
      foreach ($outline as $key => $item) {
        $index++;
        // see if we are a leaf or a branch
        if (empty($item['children'])) {
          $output .= '<lrndesign-mapmenu-item data-book-parent="' . $item['parentid'] . '" title="' . $item['title'] . '" icon="' . $item['icon'] . '" url="' . $item['url'] . '" class="mapmenu-depth-' . $depth . '"></lrndesign-mapmenu-item>';
        }
        else {
          // only do high level w/ the fancy button
          if ($depth === 1) {
            $output .= '<lrndesign-mapmenu-submenu collapsable title="' . $item['title'] . '" avatar-label="' . $index . '" data-book-parent="' . $item['parentid'] . '" class="mapmenu-depth-' . $depth . '" url="' . $item['url'] . '">';
          }
          else if ($depth === 2) {
            $output .= '<lrndesign-mapmenu-submenu collapsable title="' . $item['title'] . '" data-book-parent="' . $item['parentid'] . '" class="mapmenu-depth-' . $depth . '" url="' . $item['url'] . '">';
          }
          else {
            $output .= '<lrndesign-mapmenu-submenu collapsable expand-children label="' . $item['title'] . '" data-book-parent="' . $item['parentid'] . '" class="mapmenu-depth-' . $depth . '" url="' . $item['url'] . '">';
          }
          // step down further
          $output .= $this->renderOutline($item['children'], ($depth+1));
          $output .= '</lrndesign-mapmenu-submenu>';
        }
      }
    }
    return $output;
  }
  /**
   * Get a single page
   * This will take into consideration what section the user is in and what section
   * they have access to.
   *
   * @param string $id
   *    Nid of the page
   * @param array $options
   *    - encode [boolean] Specify whether the page should be encoded.
   *    - uid [string] Specify User
   *
   * @return object
   */
  public function getPage($id, $options = array()) {
    global $user;
    $item = FALSE;
    $encode = (isset($options['encode']) ? $options['encode'] : TRUE);
    $account = (isset($options->uid) ? user_load($options->uid) : $user);
    $item = node_load($id);
    /**
     * @todo add better checks to return status codes based on if none were found or if more than
     *       one was found.
     */
    if (isset($item->nid) && $item->status) {
      // make sure the user has access to see it.
      if (!node_access('view', $item, $account)) {
        return FALSE;
      }
      if ($encode) {
        $item = $this->encodePage($item);
      }
    }
    return $item;
  }


  /**
   * Load a list of pages
   *
   * @param array $pages
   *  An array of page ids.
   *
   * @return array
   */
  protected function getPages($pages) {
    if (is_array($pages)) {
      foreach ($pages as $nid => &$page) {
        $page = $this->getPage($nid);
      }
      return $pages;
    }
    else {
      return NULL;
    }
  }
  /**
   * Generate userData for visualizing progression through the material.
   * @param  int $id         a drupal user ID
   * @param  array $dataset  an array of node ids to query for
   */
  public function getUserData($id, $dataset) {
    $account = user_load($id);
    // author
    $return = new stdClass();
    $return->user = new stdClass();
    $return->user->type = 'user';
    $return->user->id = $account->uid;
    $return->user->name = $account->name;
    $return->user->display_name = _elmsln_core_get_user_name('full', $account->uid);
    $return->user->avatar = _elmsln_core_get_user_picture('full', $account->uid);
    $return->user->sis = _elmsln_core_get_sis_user_data($account->uid);
    // assemble their data from the LRS
    $return->data = new stdClass();
    // @todo query the LRS for relevent data based on the item IDs found
    // in $dataset
    return $return;
  }
  public function updatePage($payload, $id) {
    if ($payload) {
      // make sure we have an id to work with
      if ($id && is_numeric($id)) {
        // load the page from drupal
        $node = node_load($id);
        // make sure the node is actually a page
        if ($node && isset($node->type) && $node->type == 'page' && node_access('update', $node)) {
          // decode the payload page to the drupal node
          $decoded_page = $this->decodePage($payload, $node);
          // save the node
          try {
            // $decoded_page = new stdClass(); #fake error message
            node_save($decoded_page);
            // load the new node that we just saved.
            $new_node = node_load($decoded_page->nid);
            // encode the page to send it back
            $encoded_page = $this->encodePage($new_node);
            return $encoded_page;
          }
          catch (Exception $e) {
            throw new Exception($e->getMessage());
            return;
          }
        }
      }
    }
  }

  public function deletePage($id) {
    if ($id && is_numeric($id)) {
      $node = node_load($id);
      if ($node && isset($node->type) && $node->type == 'page' && node_access('delete', $node)) {
        // unpublish the node
        $node->status = 0;
        try {
          node_save($node);
          return true;
        }
        catch (Exception $e) {
          throw new Exception($e->getMessage());
          return;
        }
      }
    }
  }

  /**
   * Prepare a list of pages to be outputed in json
   *
   * @param array $pages
   *  An array of page node objects
   *
   * @return array
   */
  protected function encodePages($pages) {
    if (is_array($pages)) {
      foreach ($pages as &$page) {
        $page = $this->encodePage($page);
      }
      return $pages;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single page to be outputed in json
   *
   * @param object $page
   *  A page node object
   *
   * @return Object
   */
  protected function encodePage($node) {
    $encoded_page = new stdClass();
    if (is_object($node)) {
      // type / id
      $encoded_page->type = $node->type;
      $encoded_page->id = $node->nid;
      // Attributes
      $encoded_page->attributes = new stdClass();
      // title
      $encoded_page->attributes->title = $node->title;
      // content area
      if (isset($node->body[LANGUAGE_NONE][0]['safe_value'])) {
        $encoded_page->attributes->body = $node->body[LANGUAGE_NONE][0]['safe_value'];
      }
      else {
        $encoded_page->attributes->body = check_markup($node->body['und'][0]['value'], $node->body['und'][0]['format']);
      }
      // banner image
      if (!empty($node->field_mooc_image[LANGUAGE_NONE])) {
        $encoded_page->attributes->image = _elmsln_api_v1_file_output($node->field_mooc_image[LANGUAGE_NONE][0]);
      }
      // instructional significance
      $encoded_page->attributes->instructional_significance = $node->field_instructional_significance[LANGUAGE_NONE][0]['value'];
      // instructional competency
      $encoded_page->attributes->competency = $node->field_elmsln_competency[LANGUAGE_NONE][0]['value'];
      // visibility status though this is actually an attribute of the element
      $encoded_page->attributes->hidden = $node->hidden_nodes;

      // Meta Info
      $encoded_page->meta = new stdClass();
      $encoded_page->meta->created = Date('c', $node->created);
      $encoded_page->meta->changed = Date('c', $node->changed);
      $encoded_page->meta->humandate = Date("F j, Y, g:i a", $node->changed);
      $encoded_page->meta->canUpdate = 0;
      $encoded_page->meta->canDelete = 0;
        // see the operations they can perform here
      if (node_access('update', $node)) {
        $encoded_page->meta->canUpdate = 1;
      }
      if (node_access('delete', $node)) {
        $encoded_page->meta->canDelete = 1;
      }
      // get the icon
      $encoded_page->meta->icon = $this->significanceToIcon($node->field_instructional_significance[LANGUAGE_NONE][0]['value']);
      // link for loading info
      $encoded_page->meta->link = 'node/' . $node->nid;
      // Relationships
      $encoded_page->relationships = new stdClass();
      // outline /book
      $encoded_page->relationships->book = new stdClass();
      //next / prev
      $encoded_page->relationships->next = new stdClass();
      $encoded_page->relationships->prev = new stdClass();
      // parent
      $encoded_page->relationships->parent = new stdClass();
      // load associations from cache if we have a book
      if (isset($node->book['mlid'])) {
        // has_children boolean
        $encoded_page->relationships->has_children = $node->book['has_children'];
        // pass along book data relationships and associations
        $encoded_page->relationships->book->id = $node->book['bid'];
        $book = node_load($node->book['bid']);
        $encoded_page->relationships->book->title = $book->book['link_title'];
        $encoded_page->relationships->book->path = $book->book['link_path'];
        $associations = _book_cache_get_associations($node->book);
        // previous link if we have one
        if (isset($associations['prev'])) {
          $encoded_page->relationships->prev->id = str_replace('node/', '', $associations['prev']['link_path']);
          $encoded_page->relationships->prev->title = $associations['prev']['link_title'];
          $encoded_page->relationships->prev->path = $associations['prev']['link_path'];
        }
        // next link if we have one
        if (isset($associations['next'])) {
          $encoded_page->relationships->next->id = str_replace('node/', '', $associations['next']['link_path']);
          $encoded_page->relationships->next->title = $associations['next']['link_title'];
          $encoded_page->relationships->next->path = $associations['next']['link_path'];
        }
        // parent link if we have one
        if (isset($associations['parent'])) {
          $encoded_page->relationships->parent->id = str_replace('node/', '', $associations['parent']['link_path']);
          $encoded_page->relationships->parent->title = $associations['parent']['link_title'];
          $encoded_page->relationships->parent->path = $associations['parent']['link_path'];
        }
      }
      drupal_alter('lrnapp_book_encode_page', $encoded_page);
      return $encoded_page;
    }
    return NULL;
  }

  protected function decodePage($payload, $node) {
    module_load_include('inc', 'transliteration');
    if ($payload) {
      if ($payload->attributes) {
        if (isset($payload->attributes->title)) {
          $node->title = _transliteration_process(drupal_substr($payload->attributes->title, 0, 255));
        }
        if (isset($payload->attributes->body)) {
          $node->body[LANGUAGE_NONE][0]['value'] = _transliteration_process($payload->attributes->body);
          if (!isset($node->body[LANGUAGE_NONE][0]['format'])) {
            $node->body[LANGUAGE_NONE][0]['format'] = LRNAPP_BOOK_DEFAULT_FORMAT;
          }
        }
        if (isset($payload->attributes->image)) {
          $node->field_mooc_image[LANGUAGE_NONE] = $this->objectToArray($payload->attributes->image);
        }
        if (isset($payload->attributes->competency)) {
          $node->field_elmsln_competency[LANGUAGE_NONE][0]['value'] = _transliteration_process($payload->attributes->competency);
        }
        // can provide the icon though it's not direct 1 to 1 relationship
        if (isset($payload->attributes->instructional_significance)) {
          $node->field_instructional_significance[LANGUAGE_NONE][0]['value'] = _transliteration_process($payload->attributes->instructional_significance);
        }
        // support for hidden nodes
        if (isset($payload->attributes->hidden)) {
          $node->hidden_nodes = $payload->attributes->hidden;
        }
      }
    }
    drupal_alter('lrnapp_book_decode_page', $node, $payload);
    return $node;
  }

  // convert significance to a related icon for output
  private function significanceToIcon($significance) {
    $icon = LRNAPP_BOOK_DEFAULT_ICON;
    switch ($significance) {
      case 'page':
        $icon = LRNAPP_BOOK_DEFAULT_ICON;
      break;

      case 'demonstration':
      case 'interview':
      case 'lecture':
         $icon = 'theaters';
      break;

      case 'exercise':
      case 'assignment':
        $icon = 'assignment';
      break;

      case 'writing':
        $icon = 'subject';
      break;

      case 'groupwork':
      case 'speechballoons':
        $icon = 'communication:forum';
      break;

      case 'finalproject':
        $icon = 'move-to-inbox';
      break;

      case 'recitation':
      case 'seminar':
      case 'workshop':
        $icon = 'social:school';
      break;

      case 'critique':
        $icon = 'speaker-notes';
      break;

      case 'quiz':
      case 'exam':
      case 'final':
        $icon = 'assessment';
      break;
    }
    return $icon;
  }

  // Convert multidimentional Object to arrays
  private function objectToArray($obj) {
    if (is_object($obj)) $obj = (array)$obj;
    if (is_array($obj)) {
        $new = array();
        foreach ($obj as $key => $val) {
            $new[$key] = $this->objectToArray($val);
        }
    } else {
        $new = $obj;
    }
    return $new;
  }
}