<?php
/**
 * @file
 * Implement a youtube_upload field, based on the file module's file field.
 * but that never hit the Drupal file system
 * the upload is done directly to Youtube in ajax
 * @link https://developers.google.com/youtube/v3 for implementation. @endlink
 * @see js/yu.js
 */

/**
 * Implements hook_field_info().
 */
function youtube_uploader_field_info() {

  return array(
    // We name our field as the associative name of the array.
    'youtube_upload' => array(
      'label' => t('Youtube Uploader'),
      'description' => t('Hidden field to be populated.'),
      'instance_settings' => array(
        'file_directory' => '',
      ),
      'settings' => array(
        'uri_scheme' => variable_get('file_default_scheme', 'public'),
        'display_field' => 0,
        'display_default' => 0,
      ),
      'default_widget' => 'youtube_uploader_widget',
      'default_formatter' => 'youtube_uploader_video',
    ),
  );
}

/**
 * Implements hook_field_widget_info().
 */
function youtube_uploader_field_widget_info() {

  return array(
    'youtube_uploader_widget' => array(
      'label' => t('Video'),
      'field types' => array('youtube_upload'),
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function youtube_uploader_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  $token = variable_get('youtube_uploader_token', array());

  if (!isset($token['refresh_token'])) {
    drupal_set_message(t('Google refresh token not found. Please configure YouTube uploader !here', array(
      '!here' => l(t('here'), 'admin/config/media/youtube_uploader'))), 'error');
  }

  $defaults = array(
    'thumb_fid' => 0,
    'display' => !empty($field['settings']['display_default']),
    'video_title' => '',
    'youtube_hidden_id' => '',
  );
  // @TODO try to use file_field_widget_form.
  // Load the items for form rebuilds from the field state as they might not be
  // in $form_state['values'] because of validation limitations. Also, they are
  // only passed in as $items when editing existing entities.
  $field_state = field_form_get_state($element['#field_parents'], $field['field_name'], $langcode, $form_state);
  // Don't know why the items are not populated... ?
  $field_state['items'] = !empty($form_state['values'][$field['field_name']][$langcode]) ? $form_state['values'][$field['field_name']][$langcode] : array();
  foreach ($field_state['items'] as $key => $itm) {
    if (empty($itm['fid'])) {
      unset($field_state['items'][$key]);
    }
  }
  if (!empty($field_state['items'])) {
    $items = $field_state['items'];
  }
  elseif (isset($form_state['values'][$field['field_name']])) {
    $items = array();
  }

  $element += array(
    '#type' => 'hidden',
    '#input' => TRUE,
    '#process' => array('youtube_uploader_field_widget_process'),
    '#pre_render' => array('file_managed_file_pre_render'),
    '#extended' => TRUE,
  );

  if ($field['cardinality'] == 1) {
    // Set the default value.
    $element['#default_value'] = !empty($items) ? $items[0] : $defaults;

    $elements = array($element);
  }
  else {
    // If there are multiple values, add an element for each existing one.
    foreach ($items as $item) {
      $elements[$delta] = $element;
      $elements[$delta]['#default_value'] = $item;
      $elements[$delta]['#weight'] = $delta;
      $delta++;
    }
    // And then add one more empty row for new uploads except when this is a
    // programmed form as it is not necessary.
    if (($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED || $delta < $field['cardinality']) && empty($form_state['programmed'])) {
      $elements[$delta] = $element;
      $elements[$delta]['#default_value'] = $defaults;
      $elements[$delta]['#weight'] = $delta;
      $elements[$delta]['#required'] = ($element['#required'] && $delta == 0);
    }

    // The group of elements all-together need some extra functionality
    // after building up the full list (like draggable table rows).
    $elements['#file_upload_delta'] = $delta;
    $elements['#theme'] = 'file_widget_multiple';
    $elements['#theme_wrappers'] = array('fieldset');
    $elements['#process'] = array('file_field_widget_process_multiple');
    $elements['#title'] = $element['#title'];
    $elements['#description'] = $element['#description'];
    $elements['#field_name'] = $element['#field_name'];
    $elements['#language'] = $element['#language'];
    $elements['#display_field'] = $field['settings']['display_field'];

    // Add some properties that will eventually be added to the file upload
    // field. These are added here so that they may be referenced easily through
    // a hook_form_alter().
    $elements['#file_upload_title'] = t('Add a new video');
    $elements['#file_upload_description'] = theme('file_upload_help', array('description' => '', 'upload_validators' => ''));
  }

  return $elements;
}

/**
 * Extra processing for our field.
 */
function youtube_uploader_field_widget_process($element, &$form_state, $form) {

  /* @TODO try to add an additionnal _process to existing
   * file_managed_file_process and file_field_widget_process
  */
  $item = $element['#value'];
  $ytid = isset($item['fid']) ? $item['fid'] : 0;

  $field = field_widget_field($element, $form_state);
  $instance = field_widget_instance($element, $form_state);
  $settings = $instance['widget']['settings'];

  // Set some default element properties.
  $element['#file'] = $ytid ? $ytid : FALSE;
  $element['#tree'] = TRUE;

  $element['#theme'] = 'youtube_uploader_field_widget';

  $cors_path = _youtube_uploader_get_cors_upload();
  if (!$cors_path) {
    drupal_set_message(t('cors_upload.js file not found, check the !status-report section "Google CORS Upload" for more information. Videos shall not be uploaded', array('!status-report' => l(t('Status Report'), 'admin/reports/status'))), 'error', FALSE);
  }
  // Attach library JS, module custom JS and setting to get video title as node title
  $element['#attached']['js'] = array(
    $cors_path,
    drupal_get_path('module', 'youtube_uploader') . '/js/yu.js',
    array(
          'data' => array('youtube_uploader' => array('autotitle' => variable_get('youtube_uploader_autotitle', FALSE))),
          'type' => 'setting',
      )
  );
  $element['#attached']['css'] = array(
    drupal_get_path('module', 'youtube_uploader') . '/css/yu.css',
  );

  // Add the display field if enabled.
  if (!empty($field['settings']['display_field']) && $ytid) {
    $element['display'] = array(
      '#type' => !$ytid ? 'hidden' : 'checkbox',
      '#title' => t('Include video in display'),
      '#value' => isset($item['display']) ? $item['display'] : $field['settings']['display_default'],
      '#attributes' => array('class' => array('file-display')),
      '#weight' => -7,
    );
  }
  else {
    $element['display'] = array(
      '#type' => 'hidden',
      '#value' => '1',
    );
  }

  $element['fid'] = array(
    '#type' => 'hidden',
    '#value' => $ytid,
    '#weight' => -17,
    '#attributes' => array('class' => array('youtube_hidden_id')),
  );

  // If thumb doesn't exist, try to get one.
  if (!empty($item['thumb_fid'])) {
    $thumb = $item['thumb_fid'];
  }
  else {
    $nthumb = _youtube_uploader_get_default_image($ytid);
    $thumb = !empty($nthumb['file']->fid) ? $nthumb['file']->fid : 0;
  }

  $element['thumb_fid'] = array(
    '#type' => 'hidden',
    '#value' => $thumb,
    '#weight' => -18,
    '#attributes' => array('class' => array('thumb_fid')),
  );

  $element['video_title'] = array(
    '#type' => $ytid ? 'hidden' : 'textfield',
    '#title' => t('Title'),
    '#size' => 20,
    '#weight' => -15,
    '#value' => isset($item['video_title']) ? $item['video_title'] : '',
    '#attributes' => array('class' => array('video_title')),
  );

  $ajax_settings = array(
    'path' => 'file/ajax/' . implode('/', $element['#array_parents']) . '/' . $form['form_build_id']['#value'],
    'wrapper' => $element['#id'] . '-ajax-wrapper',
    'effect' => 'fade',
  );

  $element['upload_button'] = array(
    '#name' => implode('_', $element['#parents']) . '_upload_button',
    '#type' => 'submit',
    '#value' => t('Upload - hidden'),
    '#validate' => array(),
    '#submit' => array('youtube_uploader_field_widget_submit'),
    '#limit_validation_errors' => array($element['#parents']),
    '#ajax' => $ajax_settings,
    '#weight' => -5,
    // Hide the upload button to replace it
    // by the javascript upload to youtube (see js/yu.js).
    '#attributes' => array(
      'class' => array('upload-video element-hidden'),
      'style' => array('display:none')),
  );

  $element['remove_button'] = array(
    '#name' => implode('_', $element['#parents']) . '_remove_button',
    '#type' => 'submit',
    '#value' => t('Remove'),
    '#validate' => array(),
    '#submit' => array('youtube_uploader_field_widget_submit'),
    '#limit_validation_errors' => array($element['#parents']),
    '#ajax' => $ajax_settings,
    '#weight' => -5,
  );

  // The file upload field itself.
  $element['upload'] = array(
    '#name' => 'files[' . implode('_', $element['#parents']) . ']',
    '#type' => 'file',
    '#title' => t('Choose a file'),
    '#size' => 20,
    '#weight' => -10,
    '#suffix' => '<div class="during-upload" style="display: none"> <progress id="upload-progress" max="1" value="0"></progress> <span id="percent-transferred"></span>% <span id="seconds-left"></span>sec left </div>',
    '#attributes' => array(
      'class' => array('youtube-uploader-file')),
  );

  // Need to add a reference to the field to get video properties
  // from field settings later via ajax.
  $element['youtube_uploader_field_ref'] = array(
    '#type' => 'hidden',
    '#value' => $element['#entity_type'] . '|' . $element['#field_name'] . '|' . $element['#bundle'],
  );

  if ($ytid && $element['#file']) {
    $thumb_url = ($thumbn = file_load($thumb)) ? $thumbn->uri : "";
    $element['filename'] = array(
      '#type' => 'markup',
      '#markup' => theme('youtube_uploader_form_preview', array(
        'video_id' => $ytid,
        'title' => $item['video_title'],
        'thumb' => $thumb_url)
      ) ,
      '#weight' => -10,
    );
  }

  // Prefix and suffix used for Ajax replacement.
  $element['#prefix'] = '<div id="' . $element['#id'] . '-ajax-wrapper">';

  $element['#suffix'] = '</div>';

  $field = field_widget_field($element, $form_state);

  // Adjust the Ajax settings so that on upload and remove of any individual
  // file, the entire group of file fields is updated together.
  if ($field['cardinality'] != 1) {
    $parents = array_slice($element['#array_parents'], 0, -1);
    $new_path = 'file/ajax/' . implode('/', $parents) . '/' . $form['form_build_id']['#value'];
    $field_element = drupal_array_get_nested_value($form, $parents);
    $new_wrapper = $field_element['#id'] . '-ajax-wrapper';
    foreach (element_children($element) as $key) {
      if (isset($element[$key]['#ajax'])) {
        $element[$key]['#ajax']['path'] = $new_path;
        $element[$key]['#ajax']['wrapper'] = $new_wrapper;
      }
    }
    unset($element['#prefix'], $element['#suffix']);
  }

  foreach (array('upload_button', 'remove_button') as $key) {
    $element[$key]['#submit'][] = 'file_field_widget_submit';
    $element[$key]['#limit_validation_errors'] = array(
      array_slice($element['#parents'], 0, -1),
    );
  }

  return $element;
}

/**
 * Form submission handler for upload / remove buttons.
 * 
 * @see file_managed_file_submit()
 */
function youtube_uploader_field_widget_submit($form, &$form_state) {

  $parents = $form_state['triggering_element']['#array_parents'];
  $button_key = array_pop($parents);
  $element = drupal_array_get_nested_value($form, $parents);

  if ($button_key == 'remove_button') {
    // Need to get field settings.
    $field_info = field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle']);
    $field_settings = $field_info['settings']['youtube_settings'];

    // Remove the thumb.
    if ($thumb = file_load($element['thumb_fid']['#value'])) {
      file_delete($thumb);
    }

    // Remove the video from Youtube.
    if (isset($element['fid']['#value']) && $field_settings['youtube_uploader_delete'] == 1) {
      $ytapi = new youtubeUploaderYtapi();
      $ytapi->deleteVideo($element['fid']['#value']);
    }

    $values_element = $element['#extended'] ? $element['fid'] : $element;

    form_set_value($values_element, NULL, $form_state);
    drupal_array_set_nested_value($form_state['input'], $values_element['#parents'], NULL);
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_field_delete().
 */
function youtube_uploader_field_delete($entity_type, $entity, $field, $instance, $langcode, &$items) {
  // Need to get field settings.
  $field_info = field_info_instance($entity_type, $field['field_name'], $instance['bundle']);
  $field_settings = $field_info['settings']['youtube_settings'];

  // Delete all video usages within this entity.
  foreach ($items as $delta => $item) {
    // Remove the thumb.
    if ($thumb = file_load($item['thumb_fid'])) {
      file_delete($thumb);
    }
    // Remove the video from youtube.
    if (isset($item['fid']) && $field_settings['youtube_uploader_delete'] == 1) {
      $ytapi = new youtubeUploaderYtapi();
      $ytapi->deleteVideo($item['fid']);
    }
  }
}

/**
 * Implements hook_field_is_empty().
 *
 * hook_field_is_emtpy() is where Drupal asks us if this field is empty.
 * Return TRUE if it does not contain data, FALSE if it does. This lets
 * the form API flag an error when required fields are empty.
 */
function youtube_uploader_field_is_empty($item, $field) {

  return empty($item['fid']);
}


/**
 * Implements hook_field_settings_form().
 */
function youtube_uploader_field_settings_form($field, $instance, $has_data) {
  $defaults = field_info_field_settings($field['type']);
  $settings = array_merge($defaults, $field['settings']);

  $form['display_field'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable <em>Display</em> field'),
    '#default_value' => $settings['display_field'],
    '#description' => t('The display option allows users to choose if a file should be shown when viewing the content.'),
  );

  return $form;
}

/**
 * Implements hook_field_instance_settings_form().
 */
function youtube_uploader_field_instance_settings_form($field, $instance) {

  $settings = isset($instance['settings']['youtube_settings']) ? $instance['settings']['youtube_settings'] : $instance['settings'];

  $yt_settings = youtube_uploader_get_settings_form();
  unset($yt_settings['#description']);

  // Set the default value of the field or get it at the module level.
  if (isset($settings['youtube_uploader_tags'])) {
    $yt_settings['youtube_uploader_delete']['#default_value'] = $settings['youtube_uploader_delete'];
  }
  if (isset($settings['youtube_uploader_publishing_options'])) {
    $yt_settings['youtube_uploader_publishing_options']['#default_value'] = $settings['youtube_uploader_publishing_options'];
  }
  if (isset($settings['youtube_uploader_category'])) {
    $yt_settings['youtube_uploader_category']['#default_value'] = $settings['youtube_uploader_category'];
  }
  if (isset($settings['youtube_uploader_description'])) {
    $yt_settings['youtube_uploader_description']['#default_value'] = $settings['youtube_uploader_description'];
  }
  if (isset($settings['youtube_uploader_tags'])) {
    $yt_settings['youtube_uploader_tags']['#default_value'] = $settings['youtube_uploader_tags'];
  }

  $form['youtube_settings'] = $yt_settings;

  return $form;
}

/**
 * Implements hook_field_prepare_view().
 */
function youtube_uploader_field_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items) {
  file_field_prepare_view($entity_type, $entities, $field, $instances, $langcode, $items);
}

/**
 * Implements hook_field_prepare_view().
 * 
 * check if the field is required.
 */
function youtube_uploader_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  if ($instance['required'] == 1 && $items[0]['fid'] === "0") {
    form_set_error($field['field_name'], $instance['label'] . ' field is required. ');
  }
}

/**
 * formatter
 * 
 * mostly taken from youtube module so credit to them 
 * http://drupal.org/project/youtube
 */

/**
 * Implements hook_field_formatter_info().
 */
function youtube_uploader_field_formatter_info() {
  $formatters = array(
    // This formatter displays the youtube video.
    'youtube_uploader_video' => array(
      'label' => t('Video'),
      'field types' => array('youtube_upload'),
      'settings' => array(
        'youtube_video_size' => '420x315',
        'youtube_video_width' => NULL,
        'youtube_video_height' => NULL,
      ),
    ),
    // This formatter displays the youtube thumb.
    'youtube_uploader_thumb' => array(
      'label' => t('Thumbnail'),
      'field types' => array('youtube_upload'),
      'settings' => array(
        'image_style' => 'thumbnail',
        'display_title' => 1,
      ),
    ),
  );

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function youtube_uploader_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {

  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  if ($display['type'] == 'youtube_uploader_video') {
    $element['youtube_video_size'] = array(
      '#type' => 'select',
      '#title' => t('YouTube video size'),
      '#options' => array(
        '420x315' => '420px by 315px',
        '480x360' => '480px by 360px',
        '640x480' => '640px by 480px',
        '960x720' => '960px by 720px',
        'custom' => 'custom',
      ),
      '#default_value' => $settings['youtube_video_size'],
    );
    $element['youtube_video_width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#size' => 10,
      '#default_value' => $settings['youtube_video_width'],
      '#states' => array(
        'visible' => array(
          ':input[name="fields[' . $field['field_name'] . '][settings_edit_form][settings][youtube_video_size]"]' => array('value' => 'custom'),
        ),
      ),
    );
    $element['youtube_video_height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#size' => 10,
      '#default_value' => $settings['youtube_video_height'],
      '#states' => array(
        'visible' => array(
          ':input[name="fields[' . $field['field_name'] . '][settings_edit_form][settings][youtube_video_size]"]' => array('value' => 'custom'),
        ),
      ),
    );
  }

  if ($display['type'] == 'youtube_uploader_thumb') {
    $element['image_style'] = array(
      '#type' => 'select',
      '#title' => t('Image style'),
      '#options' => image_style_options(FALSE),
      '#default_value' => $settings['image_style'],
      '#empty_option' => t('None (original image)'),
    );
    $element['display_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display title'),
      '#default_value' => $settings['display_title'],
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function youtube_uploader_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  // Summary for the video style.
  if ($display['type'] == 'youtube_uploader_video') {
    $video_sizes = array(
      '420x315' => '420px by 315px',
      '480x360' => '480px by 360px',
      '640x480' => '640px by 480px',
      '960x720' => '960px by 720px',
      'custom' => 'custom',
    );
    if (isset($video_sizes[$settings['youtube_video_size']])) {
      $summary = t('YouTube video: @size', array('@size' => $video_sizes[$settings['youtube_video_size']]));
    }
    else {
      $summary = t('YouTube video: 420px by 315px');
    }

    return $summary;
  }

  // Summary for the thumbnail style.
  if ($display['type'] == 'youtube_uploader_thumb') {
    $image_styles = image_style_options(FALSE);
    // Unset possible 'No defined styles' option.
    unset($image_styles['']);
    if (isset($image_styles[$settings['image_style']])) {
      $summary = t('Image style: @style', array('@style' => $image_styles[$settings['image_style']]));
    }
    else {
      $summary = t('Original image');
    }

    return $summary;
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function youtube_uploader_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {

    // This formatter outputs the youtube embed code.
    case 'youtube_uploader_video':
      $video_size = $display['settings']['youtube_video_size'] == 'custom' ? $display['settings']['youtube_video_width'] . 'x' . $display['settings']['youtube_video_height'] : $display['settings']['youtube_video_size'];
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'youtube_uploader_video',
          '#video_id' => $item['fid'],
          '#title' => $item['video_title'],
          '#player_size' => $video_size,
        );
      }
      break;

    // This formatter uses an imagecache preset to generate a thumbnail.
    case 'youtube_uploader_thumb':
      foreach ($items as $delta => $item) {
        // If thumb doesn't exist, try to get one.
        if ($item['thumb_fid'] > 0) {
          $thumb = $item['thumb_fid'];
        }
        else {
          $nthumb = _youtube_uploader_get_default_image($item['fid']);
          $thumb = !empty($nthumb['file']->fid) ? $nthumb['file']->fid : FALSE;
        }

        // Output image.
        if (!$thumb) {
          // Need to style the default message.
          drupal_add_css(drupal_get_path('module', 'youtube_uploader') . '/css/yu.css');
        }
        else {
          $file = file_load($thumb);
          $thumb = theme('image_style', array(
            'path' => $file->uri,
            'style_name' => $display['settings']['image_style'],
            'title' => $item['video_title'],
          ));
        }

        $element[$delta] = array(
          '#theme' => 'youtube_uploader_thumbnail',
          '#video_id' => $item['fid'],
          '#title' => $display['settings']['display_title'] ?
          $item['video_title'] : '',
          '#image' => $thumb,
        );
      }
      break;

  }

  return $element;
}
