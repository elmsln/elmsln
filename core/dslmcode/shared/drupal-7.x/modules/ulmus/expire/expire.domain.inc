<?php

/**
 * Get domains the node is currently published to
 *
 * @param $node
 *   node object
 * @return array
 *   array('$gid' => $gid)
 */
function expire_get_domains(&$node) {
  $domains = array();
  if ($node->nid) {
    $result = db_query("SELECT gid FROM {domain_access} WHERE nid = :nid", array(':nid' => $node->nid));
    foreach ($result as $row) {
      $domains[$gid] = $row->gid;
    }
  }
  elseif ($node->mail && $node->name) {
    $result = db_query("SELECT domain_id FROM {domain_editor} WHERE uid = :uid", array(':uid' => $node->uid));
    foreach ($result as $row) {
      $domains[$gid] = $row->domain_id;
    }
  }
  return $domains;
}

/**
 * Get all base url's where this node can appear.
 *
 * @param $node
 *   node object
 * @return array
 *   array(0 => array($base_url . '/'))
 */
function expire_get_base_urls($node) {
  global $base_url, $base_path;

  // Get list of URL's if using domain access
  $base_urls = array();
  $domains = array();
  // Get domains from node/user object
  foreach ($node->domains as $key => $domain_id) {
    if ($key != $domain_id) {
      continue;
    }
    $domains[$domain_id] = $domain_id;
  }
  // Get domains from database
  foreach (expire_get_domains($node) as $domain_id) {
    $domains[$domain_id] = $domain_id;
  }
  // Get aliases and set base url
  foreach ($domains as $domain_id) {
    $domain = domain_lookup($domain_id);
    if ($domain['valid'] == 1) {
      if (isset($domain['path'])) {
        $base_urls[$domain_id][] = $domain['path'];
      }
      if (is_array($domain['aliases'])) {
        foreach ($domain['aliases'] as $alias) {
          if ($alias['redirect'] != 1) {
            $temp_domain = array('scheme' => $domain['scheme'], 'subdomain' => $alias['pattern']);
            $base_urls[$domain_id][] = domain_get_path($temp_domain);
          }
        }
      }
    }
  }
  return $base_urls;
}

