<?php

/**
 * @file
 *   SCO Node module SCO table of contents functions.
 */

function sco_node_toc_tree($node) {

  // get default organization
  $org = sco_node_get_organization($node->sco_manifest);
  
  $html = '<div id="sco-node-toc-title">' . t($org->title) . '</div>';
  
  $html .= '<div id="sco-node-toc">';
  
  $html .= sco_node_toc_tree_items($node, $org->items);
  
  $html .= '</div>';
  
  return $html;
}

function sco_node_toc_tree_items($node, $items) {

  $html = '<ul>';
  
  foreach($items as $item) {
    $markup = '<span>' . t($item->title) . '</span>';
    if ($item->res_id) {
      $res = sco_node_get_resource($node->sco_manifest, $item->res_id);
      if ($res && $res->href) {
        $url = sco_node_content_url($node, $res->href . $item->parms);
        $markup = '<a id="sco-node-toc-link-' . $item->id . '" href="javascript:sco_node_nav_to(\''. $item->id . '\',\'' . $url . '\');">' . $markup . '</a>';
      }
    }
    $html .= '<li>' . $markup;
    if (count($item->items) > 0) {
      $html .= sco_node_toc_tree_items($node, $item->items);
    }
    $html .= '</li>';
  }

  $html .= '</ul>';
  
  return $html;
}

