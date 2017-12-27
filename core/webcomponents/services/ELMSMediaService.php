<?php

class ELMSMediaService {
  /**
   * Get a list of projects
   */
  public function getMedia(array $options = NULL) {
    $return = array();
    $list = array();
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', array('elmsmedia_image', 'external_video', 'svg'));

    // order by most recent
    $_order = (isset($options['order']) ? $options['order'] : 'DESC');
    $query->propertyOrderBy('changed', $order);

    // range and pager do half of what we need, but they don't work great in combo with eachother.
    // Range won't tell us how many total items there are and pager won't let us skip to a certain
    // set of results. So we are going to run two queries to get the total count and the correct
    // page range.
    $_limit = (isset($options['limit']) ? $options['limit'] : 10);
    $_page = (isset($options['page']) ? $options['page'] : 1);
    // get the total count
    $query->count = TRUE;
    $totalcount = $query->execute();
    // now unset count and add a range to get our results list
    $query->count = FALSE;
    // the begining of the range will be the limit times targeted page minus one to account
    // for starting at zero.
    $_rangestart = round($_limit * ($_page - 1));
    $query->range($_rangestart, $_limit);
    $results = $query->execute();

    // add the pageing information to the return array in the form of JSON spec
    // http://jsonapi.org/format/#fetching-pagination
    $return['total'] = round($totalcount);
    $return['first'] = round('1');
    $return['last'] = round($totalcount / $_limit);
    $return['current'] = round($_page);

    // loop through the nids and pull out the full nodes
    if (isset($results['node'])) {
      foreach ($results['node'] as $item) {
        $list[] = node_load($item->nid);
      }
    }
    $return['list'] = $this->encodeMediaItems($list);

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
      drupal_alter('cle_open_studio_app_encode_project', $encoded_item);
      return $encoded_item;
    }
    return NULL;
  }
}