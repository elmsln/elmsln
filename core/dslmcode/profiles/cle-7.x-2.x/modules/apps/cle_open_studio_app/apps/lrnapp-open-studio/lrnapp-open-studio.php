<?php

/**
 * Callback for apps/open-studio/data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_app_data($machine_name, $app_route, $params, $args) {
  $return = array();
  // @todo need a better render method then this as this is lazy for now
  if (isset($params['nid']) && is_numeric($params['nid'])) {
    $node = node_load($params['nid']);
    $node_view = node_view($node);
    $rendered_node = drupal_render($node_view);
    $return = $rendered_node;
  }
  else {
    // @todo need to pull just the most recent submissions, 1 per project
    // which might be too complex of logic for this efq to express
    // get all submissions
    // unique per project
    // sort by most recent
    // ... ugh... this is more complex then this
    // pull together all the submissions they should be seeing
    $data = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', '_entity');
    foreach ($data as $item) {
      $return[$item->nid] = new stdClass();
      $return[$item->nid]->title = $item->title;
      $return[$item->nid]->comments = $item->comment_count;
      $return[$item->nid]->author = $item->name;
      $return[$item->nid]->body = strip_tags($item->field_submission_text['und'][0]['safe_value']);
      $return[$item->nid]->id = $item->nid;
      if (!empty($item->field_images)) {
        $images = array();
        foreach ($item->field_images['und'] as $image) {
          $images[] = file_create_url($image['uri']);
        }
        $return[$item->nid]->images = $images;
      }
      if (!empty($item->field_files)) {
        foreach ($item->field_files['und'] as $file) {
          $return[$item->nid]->files[] = file_create_url($file['uri']);
        }
      }
      if (!empty($item->field_video)) {
        foreach ($item->field_video['und'] as $video) {
          $return[$item->nid]->videos[] = $video['video_url'];
        }
      }
      if (!empty($item->field_links)) {
        foreach ($item->field_links['und'] as $link) {
          $return[$item->nid]->links[] = $link['url'];
        }
      }
    }
  }
  return array(
    'status' => 200,
    'data' => $return
  );
}