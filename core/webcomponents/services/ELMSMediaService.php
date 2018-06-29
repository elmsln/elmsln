<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(dirname(__FILE__))));
require_once('ELMSRestService.php');

class ELMSMediaService extends ELMSRestService {

  /**
   * Define all of the possible media types.
   * @todo this should be configurable
   */
  public $media_types = array('elmsmedia_image', 'external_video', 'svg', 'h5p_content', 'document', 'video', 'audio');

  /**
   * Get a list of projects
   */
  public function getMedia(array $options = NULL) {
    $return = array();
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');

    // check if there was a media type specified
    // if not, display all media types.
    if (isset($options['media_type'])) {
      // convert media into an array so that we can possibly use multiple media types
      $filter_list = explode(',', $options['media_type']);
      // security check to make sure that the specified media types are in the master list
      $verified_media_types = array_intersect($this->media_types, $filter_list);
      if (count($verified_media_types) > 0) {
        $query->entityCondition('bundle', $verified_media_types);
      }
      else {
        // if there was no valid media types then set the bundle to none
        // which will effectively return the correct empty results set along
        // with the necessary pager information.
        $query->entityCondition('bundle', 'none');
      }
    }
    else {
      $query->entityCondition('bundle', $this->media_types);
    }

    // Use the ELMS Rest Service to execute the query
    $return = $this->executeQuery($query, $options);


    // loop through the nids and pull out the full nodes
    $_list = array();
    if (isset($return['list']['node'])) {
      foreach ($return['list']['node'] as $item) {
        // load the node object
        $_item = node_load($item->nid);
        // run it through the formatter
        $_item = $this->encodeMediaItem($_item);
        $_list[] = $_item;
      }
    }
    $return['list'] = $_list;
    return $return;
  }

  /**
   * Get the gizmo type
   * 
   * This will attempt to find the equivilent gizmo type
   * based on the content type.
   * 
   * @param string $content_type
   * @return string
   */
  public function getGizmoType($content_type) {
    // 'data','video','audio','text','link','file','pdf','image','csv','doc';
    switch ($content_type) {
      case 'elmsmedia_image':
        return 'image';
        break;
      case 'external_video':
        return 'video';
        break;
      case 'video':
        return 'video';
        break;
      case 'svg':
        return 'image';
        break;
      case 'document':
        return 'doc';
        break;
      case 'audio':
        return 'audio';
        break;
      
      default:
        return 'doc';
        break;
    }
  }

  /**
   * Prepare a list of projects to be outputed in json
   *
   * @param array mediaitems
   *  An array of media node objects
   *
   * @return array
   */
  protected function encodeMediaItems($items) {
    if (is_array($items)) {
      foreach ($items as &$item) {
        $item = $this->encodeMediaItem($item);
      }
      return $items;
    }
    else {
      return NULL;
    }
  }

  /**
   * Prepare a single project to be outputed in json
   *
   * @param object media item
   *  A media node object
   *
   * @return Object
   */
  protected function encodeMediaItem($item) {
    global $user;
    $account = $user;
    $encoded_item = new stdClass();
    if (is_object($item)) {
      $encoded_item->type = $item->type;
      $encoded_item->id = $item->nid;
      // Attributes
      $encoded_item->attributes = new stdClass();
      $encoded_item->attributes->title = $item->title;
      $encoded_item->attributes->body = $item->field_project_description[LANGUAGE_NONE][0]['safe_value'];

      // Images
      $encoded_item->attributes->images = NULL;
      if (isset($item->field_image[LANGUAGE_NONE])) {
        foreach ($item->field_image[LANGUAGE_NONE] as $file) {
          $file_output = _elmsln_api_v1_file_output($file);
          $file_output['originalurl'] = $file_output['url'];
          $file_output['thumbnail'] = $file_output['url'];
          // fix things that aren't gif since it might be animated
          if ($file_output['filemime'] != 'image/gif') {
            $file_output['url'] = $file_output['image_styles']['elmsln_normalize'];
            $file_output['thumbnail'] = $file_output['image_styles']['elmsln_small'];
          }
          $encoded_item->attributes->images[] = $file_output;
        }
      }
      $images = $encoded_item->attributes->images;
      if ($images) {
        $image = array_pop($images);
        $encoded_item->display = new stdClass();
        $encoded_item->display->image = $image['url'];
      }

      // Meta Info
      $encoded_item->meta = new stdClass();
      $encoded_item->meta->created = Date('c', $item->created);
      $encoded_item->meta->changed = Date('c', $item->changed);
      $encoded_item->meta->humandate = Date("F j, Y, g:i a", $item->changed);
      $encoded_item->meta->revision_timestamp = Date('c', $item->revision_timestamp);
      $encoded_item->meta->canUpdate = 0;
      $encoded_item->meta->canDelete = 0;

      // see the operations they can perform here
      if (entity_access('update', 'node', $item)) {
        $encoded_item->meta->canUpdate = 1;
      }
      if (entity_access('delete', 'node', $item)) {
        $encoded_item->meta->canDelete = 1;
      }
      // Relationships
      $encoded_item->relationships = new stdClass();
      // group
      $encoded_item->relationships->group = new stdClass();
      $encoded_item->relationships->group->data = new stdClass();
      $encoded_item->relationships->group->data->id = $item->og_group_ref[LANGUAGE_NONE][0]['target_id'];
      // author
      $encoded_item->relationships->author = new stdClass();
      $encoded_item->relationships->author->data = new stdClass();
      $encoded_item->relationships->author->data->type = 'user';
      $encoded_item->relationships->author->data->id = $item->uid;
      $encoded_item->relationships->author->data->name = $item->name;
      // // Actions
      // $encoded_item->actions = null;
      drupal_alter('elms_media_service_encode_media_item', $encoded_item);
      return $encoded_item;
    }
    return NULL;
  }
}