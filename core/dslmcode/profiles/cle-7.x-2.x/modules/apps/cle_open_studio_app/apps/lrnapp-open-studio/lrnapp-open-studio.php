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
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    $field_conditions = array(
      'og_group_ref' => array('target_id', $section, '='),
    );
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    $orderby = array('property' => array(array('changed', 'DESC')));
    $data = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
    foreach ($data as $item) {
      $key = 'node-' . $item->nid;
      $return[$key] = new stdClass();
      $return[$key]->image = NULL;
      $return[$key]->icon = FALSE;
      $return[$key]->images = array();
      $return[$key]->files = array();
      $return[$key]->videos = array();
      $return[$key]->links = array();
      $return[$key]->id = $item->nid;
      $return[$key]->changed = Date("F j, Y, g:i a", $item->changed);
      $return[$key]->title = $item->title;
      $return[$key]->comments = (!empty($item->comment_count) ? $item->comment_count : 0);
      $return[$key]->author = $item->name;
      $return[$key]->body = strip_tags($item->field_submission_text['und'][0]['safe_value']);
      if (!empty($return[$item->nid]->body)) {
        $return[$key]->icon = 'subject';
      }
      // append specific data about each output type
      if (isset($item->field_files['und'])) {
        foreach ($item->field_files['und'] as $file) {
          $return[$key]->files[] = file_create_url($file['uri']);
        }
        $return[$key]->icon = 'file-download';
      }
      if (isset($item->field_links['und'])) {
        foreach ($item->field_links['und'] as $link) {
          $return[$key]->links[] = $link['url'];
        }
        $return[$key]->icon = 'link';
      }
      if (isset($item->field_video['und'])) {
        foreach ($item->field_video['und'] as $video) {
          $return[$key]->videos[] = $video['video_url'];
        }
        $return[$key]->icon = 'av:video-library';
      }
      if (isset($item->field_images['und'])) {
        $images = array();
        foreach ($item->field_images['und'] as $image) {
          $images[] = file_create_url($image['uri']);
        }
        $return[$key]->images = $images;
        $return[$key]->image = array_pop($images);
        $return[$key]->icon = FALSE;
      }
    }
  }
  return array(
    'status' => 200,
    'data' => $return
  );
}