<?php

/**
 * @file
 * Implement a video field.
 */

/**
 * Implements of hook_field_info().
 */
function video_embed_field_field_info() {
  return array(
    'video_embed_field' => array(
      'label' => 'Video Embed',
      'description' => 'Embed videos from youtube or vimeo',
      'settings' => array(),
      'instance_settings' => array(
        'description_field' => 0,
      ),
      'default_widget' => 'video_embed_field_video',
      'default_formatter' => 'video_embed_field',
    )
  );
}

/**
 * Implements hook_field_instance_settings_form().
 */
function video_embed_field_field_instance_settings_form($field, $instance) {
  $settings = $instance['settings'];
  
  $form['description_field'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable <em>Description</em> field'),
    '#default_value' => isset($settings['description_field']) ? $settings['description_field'] : '',
    '#description' => t('The description field allows users to enter a description about the video.'),
    '#parents' => array('instance', 'settings', 'description_field'),
    '#weight' => 11,
  );
  
  return $form;
}

/**
 * Implements hook_field_widget_info().
 */
function video_embed_field_field_widget_info() {
  return array(
    'video_embed_field_video' => array(
      'label' => 'Video',
      'description' => 'Provides a video embed field',
      'field types' => array('video_embed_field'),
      'settings' => array(),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_DEFAULT
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function video_embed_field_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  // Don't need to check the type right now because we're only defining one
  $element += array(
    '#type' => 'fieldset'
  );
  
  $element['video_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Video URL'),
    '#attributes' => array('class' => array('video_embed_url')),
    '#attached' => array( 
      'css' => array( 
        drupal_get_path('module', 'video_embed_field') .'/video_embed_field.form.css'
      )
    ),
    '#default_value' => isset($items[$delta]['video_url'])?$items[$delta]['video_url']:'',
    '#required' => $element['#required']
  );
  
  // Add the description field if enabled.
  if (!empty($instance['settings']['description_field'])) {
    $element['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#default_value' => isset($items[$delta]['description']) ? $items[$delta]['description'] : '',
      '#description' => t('The description which may be used as a label.'),
    );
  }

  return $element;
}

/**
 * Validates video URL.
 */
function video_embed_field_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  foreach ($items as $delta => $item) {
    if (!empty($item['video_url'])) {
      $item['video_url'] = trim($item['video_url']);
      if (stristr($item['video_url'], '.') && !stristr($item['video_url'], 'http://') && !stristr($item['video_url'], 'https://')) {
        $item['video_url'] = 'http://' . $item['video_url'];
      }
      
      $parts = parse_url($item['video_url']);
      if (!$parts || !isset($parts['host'])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error' => t('Invalid Url'), 
          'message' => t('Video: Invalid Video URL.', array('%name' => $instance['label'])),
        );
      }
      else {
        $host = $parts['host'];
        if (stripos($host, 'www.') > -1) {
          $host = substr($host, 4);
        }
        $domains = _video_embed_field_get_provider_domains();
        if (!array_key_exists($host, $domains)) {
          $errors[$field['field_name']][$langcode][$delta][] = array(
            'error' => t('Unsupported Video Provider'), 
            'message' => t('%name: This video provider is not currently supported.', array('%name' => $instance['label'])),
          );
        }
      }
    }
  }
}

/**
 * Implementation of hook_field_prepare_view().
 *
 * Download and save the thumbnail if it hasn't already been stored.
 * Get video data.
 */
function video_embed_field_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  foreach($items as $delta => $item){

    // Try to load thumbnail URL
    $info = video_embed_field_thumbnail_url($item['video_url']);  
    if (isset($info['url']) && $info['url']) {
      $thumb_url = $info['url'];
      $local_path = 'public://video_embed_field_thumbnails/' . $info['handler'] . '/' . $info['id'] . '.jpg';

      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

      $response = drupal_http_request($thumb_url);
      if (!isset($response->error)) {
         file_save_data($response->data, $local_path, TRUE);
      }
      else{
         @copy($thumb_url, $local_path);
      }
    

      $items[$delta]['thumbnail_path'] = $local_path;
    } //couldn't get the thumbnail for whatever reason
    else {
      $items[$delta]['thumbnail_path'] = ''; 
    }

    // Try to load video data
    $data = video_embed_field_get_video_data($item['video_url']);
    if (is_array($data) && !empty($data)) {
      $items[$delta]['video_data'] = serialize($data);
    }
    else {
      $items[$delta]['video_data'] = NULL;
    }

  }
}

/**
 * Implements of hook_field_is_empty().
 */
function video_embed_field_field_is_empty($item, $field){
  return empty($item) || empty($item['video_url']) || $item['video_url'] === '';
}

/**
 * Implements hook_field_formatter_info().
 */
function video_embed_field_field_formatter_info() {
  $info = array(
    'video_embed_field' => array(
      'label' => t('Video Player'),
      'field types' => array('video_embed_field'),
      'settings' => array('video_style' => 'normal', 'description' => 1),
    ),
    'video_embed_field_thumbnail' => array(
      'label' => t('Thumbnail Preview'),
      'field types' => array('video_embed_field'),
      'settings' => array(
        'image_style' => 'none',
        'description' => 1,
        'image_link' => 'none',
      ),
    ),
  );
  if( module_exists('colorbox')  ) {
    $info['video_embed_field_thumbnail_colorbox'] = array(
      'label' => t('Thumbnail Preview w/Colorbox'),
      'field types' => array('video_embed_field'),
      'settings' => array('video_style' => 'normal', 'image_style' => 'none', 'description' => 1),
    );
  }
  return $info;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function video_embed_field_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();
  
  if ($display['type'] == 'video_embed_field' || $display['type'] == 'video_embed_field_thumbnail_colorbox') {
    $video_styles = video_embed_field_video_style_options(FALSE);
    $element['video_style'] = array(
      '#title' => t('Video style'),
      '#type' => 'select',
      '#default_value' => $settings['video_style'],
      '#options' => $video_styles,
    );
  } 
  if ($display['type'] == 'video_embed_field_thumbnail' || $display['type'] == 'video_embed_field_thumbnail_colorbox') {
    $element['image_style'] = array(
      '#title' => t('Image style'),
      '#type' => 'select',
      '#options' => image_style_options(FALSE),
      '#default_value' => $settings['image_style'],
      '#empty_option' => t('None (original image)'),
    ); 
  }
  
  if($display['type'] == 'video_embed_field_thumbnail'){
    $link_types = array(
      'node' => t('Node'),
      'source' => t('Video Source'),
    );
    $element['image_link'] = array(
      '#title' => t('Link thumbnail to'),
      '#type' => 'select',
      '#default_value' => $settings['image_link'],
      '#empty_option' => t('Nothing'),
      '#options' => $link_types,
    );
  }
  
  if ($instance['settings']['description_field']) {
    $element['description'] = array(
      '#title' => t('Show description'),
      '#type' => 'checkbox',
      '#default_value' => $settings['description'],
    );
  }
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function video_embed_field_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();
  if($display['type'] == 'video_embed_field' || $display['type'] == 'video_embed_field_thumbnail_colorbox'){
    $video_styles = video_embed_field_video_style_options(FALSE);
    // Styles could be lost because of enabled/disabled modules that defines
    // their styles in code.
    if (isset($video_styles[$settings['video_style']])) {
      $summary[] = t('Video style: @style', array('@style' => $video_styles[$settings['video_style']]));
    }
  } 
  if ($display['type'] == 'video_embed_field_thumbnail' || $display['type'] == 'video_embed_field_thumbnail_colorbox') {
    $image_styles = image_style_options(FALSE);
    if (isset($image_styles[$settings['image_style']])) {
      $summary[] = t('Image style: @style', array('@style' => $image_styles[$settings['image_style']]));
    } //No Image style (original image)  
    else {
      $summary[] = t('Original Image.');
    }
    if(isset($settings['image_link'])){
      $summary[] = t('Image link: ' . $settings['image_link']);
    }
    else{
      $summary[] = t('Image link: none');
    }
  }

  if ($settings['description'] && $instance['settings']['description_field']) {
    $summary[] = t('Show description');
  }
  else if ($instance['settings']['description_field']) {
    $summary[] = t('Hide description');
  }
  
  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function video_embed_field_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display){
  $element = array();
  
  foreach ($items as $delta => $item) {
    //create the render array for the description
    if (isset($item['description']) && $item['description'] && $display['settings']['description'] && $instance['settings']['description_field']) {
      $description = array(
        '#prefix' => '<div class="video-embed-description">',
        '#markup' => $item['description'],
        '#suffix' => '</div>',
      );
    }
    else {
      $description = array();
    }

    //Render the field
    if ($display['type'] == 'video_embed_field') {
      $element[$delta] = array(
        array(
          '#theme' => 'video_embed_field_embed_code',
          '#url' => $item['video_url'],
          '#style' => $display['settings']['video_style'],
          '#video_data' => !empty($item['video_data']) ? unserialize($item['video_data']) : array(),
        ),
      );
    }
    else if ($display['type'] == 'video_embed_field_thumbnail') {
      if (isset($item['thumbnail_path'])) {
        if(empty($display['settings']['image_style']) || $display['settings']['image_style'] == 'none'){
          $element[$delta] = array(
            array(
              '#theme' => 'image',
              '#path' => $item['thumbnail_path'],
            ),
          );
        }
        else {
          $element[$delta] = array(
            array(
              '#theme' => 'image_style',
              '#path' => $item['thumbnail_path'],
              '#style_name' => $display['settings']['image_style'],
            ),
          );
        }
        if($display['settings']['image_link'] == 'source'){
          $link = explode('|||', l('|||', $item['video_url']));
          $element[$delta]['#prefix'] = $link[0];
          $element[$delta]['#suffix'] = $link[1];
        }
        else if($display['settings']['image_link'] == 'node'){
          $nid = $entity->nid;
          $link = explode('|||', l('|||', 'node/'. $nid));
          $element[$delta]['#prefix'] = $link[0];
          $element[$delta]['#suffix'] = $link[1];
        }
      } //incase no thumbnail was downloaded / provider doesn't support thumbnails
      else {
        $element[$delta] = array(
        );    
      }
    }
    else if ($display['type'] == 'video_embed_field_thumbnail_colorbox') {
      if (isset($item['thumbnail_path'])) {
        $element[$delta] = array(          
          array(
            '#theme' => 'video_embed_field_colorbox_code',
            '#image_url' => $item['thumbnail_path'],
            '#image_style' => $display['settings']['image_style'],
            '#video_url' => $item['video_url'],
            '#video_style' => $display['settings']['video_style'],
            '#video_data' => unserialize($item['video_data']),
          ),
        );      
      }//incase no thumbnail was downloaded / provider doesn't support thumbnails
      else {
        $element[$delta] = array(
        );    
      }
    }
    //Get the HTML instead of the array, because we append it to the suffix.
    //This way, the thumbnail link wrapper doesn't make the description a link as well.
    $description_html = drupal_render($description);
    
    //No need to check to add, as we set it to blank above if it's set to not display.
    //The if/else is so that it doesn't show an error in case there's no suffix.
    if(isset($element[$delta]['#suffix'])){
      $element[$delta]['#suffix'] .= $description_html;
    }
    else{
      $element[$delta]['#suffix'] = $description_html;
    }
  }
  
  
  return $element;
}