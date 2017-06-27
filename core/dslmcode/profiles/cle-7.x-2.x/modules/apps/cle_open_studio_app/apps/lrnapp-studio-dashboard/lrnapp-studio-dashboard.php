<?php

/**
 * Callback for apps/lrnapp-studio-dashboard/data.
 */
function _cle_open_studio_app_dashboard_data($machine_name, $app_route, $params, $args) {
  $return = array();
  $data = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', '_entity');
  foreach ($data as $item) {
    $return[$item->nid] = new stdClass();
    $return[$item->nid]->title = $item->title;
    $return[$item->nid]->comments = $item->comment_count;
    $return[$item->nid]->author = $item->name;
    $return[$item->nid]->body = strip_tags($item->field_submission_text['und'][0]['safe_value']);
    $return[$item->nid]->url = base_path() . $app_route . '/data?nid=' . $item->nid . '&token=' . drupal_get_token('webcomponentapp');
    $return[$item->nid]->edit_url = base_path() . 'node/' . $item->nid . '/edit?destination=' . $app_route;
    if (!empty($item->field_images)) {
      $images = array();
      foreach ($item->field_images['und'] as $image) {
        $images[$image['fid']] = file_create_url($image['uri']);
      }
      if (count($images) == 1) {
        $return[$item->nid]->image = array_pop($images);
      }
      else if (count($images) > 1) {
        $return[$item->nid]->images = $images;
      }
    }
    if (!empty($item->field_files)) {
      foreach ($item->field_files['und'] as $file) {
        $return[$item->nid]->file = file_create_url($file['uri']);
      }
    }
    if (!empty($item->field_video)) {
      foreach ($item->field_video['und'] as $video) {
        $return[$item->nid]->video = $video['video_url'];
      }
    }
    if (!empty($item->field_links)) {
      foreach ($item->field_links['und'] as $link) {
        $return[$item->nid]->link = $link['url'];
      }
    }
  }
  return array(
    'status' => 200,
    'data' => $return
  );
}