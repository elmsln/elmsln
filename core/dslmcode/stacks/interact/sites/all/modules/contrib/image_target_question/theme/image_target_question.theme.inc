<?php

/**
 * @file
 * Theming functions for the image_target_question question type.
 */

/**
 * Preprocess the alternative answers to the creation form
 */
function theme_image_target_question_creation_form(&$vars) {
  $form = &$vars['form'];

  $path = drupal_get_path('module', 'image_target_question');
  drupal_add_library('system', 'ui.draggable');
  drupal_add_library('system', 'ui.droppable');
  drupal_add_library('system', 'ui.sortable');
  drupal_add_js($path . '/js/image_target_question_creation.js');

  $output = '';

  $output .= drupal_render($form['upload']);
  $output .= drupal_render($form['upload_now']);
  $output .= '<div style="clear: both; padding-bottom: 20px;"></div>';
  $output .= drupal_render($form['image_target_question_image']);

  if (isset($form['targets'])) {
    $rows = array();
    foreach ($form['targets'] as $identifier => $target) {
      if (intval($identifier) > 0) {
        $row = array();
        $row[] = drupal_render($target['selected_region']) . drupal_render($target['region']);
        $row[] = drupal_render($target['targettext']);
        $row[] = drupal_render($target['score_if_correct']);
        $row[] = drupal_render($target['score_if_not_correct']);
        $rows[] = $row;
      }
    }
    $header[] = array('data' => t('Region'));
    $header[] = array('data' => t('Description'));
    $header[] = array('data' => t('Score if correct'));
    $header[] = array('data' => t('Score if not correct'));
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }

  $output .= drupal_render($form['feedback']);

  // TODO : Add alternatives functionality.
  return $output;
}

/**
 * Theme the answer part of the node view.
 *
 * @param array &$vars
 *   - 'alternatives' an array of regions.
 *   - 'show_correct' boolean true to display the solution.
 *   - 'fid' int the file fid of the image file to display.
 */
function theme_image_target_question_answer_node_view(&$vars) {

  $path = drupal_get_path('module', 'image_target_question');
  drupal_add_css($path . '/theme/image_target_question.css');

  $alternatives = &$vars['alternatives'];
  $show_correct = &$vars['show_correct'];
  $fid = &$vars['fid'];

  $header = array('');
  $rows = array();
  $answers = array();

  if ($show_correct) {
    foreach ($alternatives as $i => $short) {
      if ($show_correct) {
        $answers[$i] = array(
          'region' => $short,
        );
      }

      $rows[] = array(
        $i . '. ' . check_plain($short['targettext']),
      );
    }
  }

  $output = theme('image_target_question_image',
    array(
      'fid' => $fid,
      'answers' => $answers,
      'showcorrect' => $show_correct,
    ));
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}

/**
 * Theme function for the image_target_question report.
 * This appears at the end of a quiz and shows the user what they got right
 * and wrong
 *
 * @param array $vars
 *   'fid' int the file fid of the image_target_question image.
 *   'answers' array containing details of the target and region positions.
 *   'feedback' string the general feedback for the user.
 *   'showcorrect' boolean TRUE displays the regions.
 *   'showfeedback' boolean TRUE to display the feedbck text.
 */
function theme_image_target_question_response(&$vars) {
  $fid = &$vars['fid'];
  $answers = &$vars['answers'];
  $feedback = &$vars['feedback'];
  $showcorrect = &$vars['showcorrect'];
  $showfeedback = &$vars['showfeedback'];

  $rows = array();
  $path = drupal_get_path('module', 'image_target_question');
  $img_path = $path . '/theme/images';
  drupal_add_css($path . '/theme/image_target_question.css');

  foreach ($answers as $identifier => $answer) {
    $cols = array();

    $cols[] = array(
      'data' => "<span>{$identifier}. </span>",
      'width' => 35,
    );

    if ($showcorrect) {
      $info = $answer['correct']
        ? theme('image', array(
            'path' => "{$img_path}/correct.png",
            'title' => t('Correct'),
            'alt' => t('This answer is correct'),
            'attributes' => array('class' => 'feedback-icon'),
          ))
        : theme('image', array(
          'path' => "{$img_path}/wrong.png",
          'title' => t('Wrong'),
          'alt' => t('This answer is wrong'),
          'attributes' => array('class' => 'feedback-icon'),
          ));

      $cols[] = array(
        'data' => $info,
        'width' => 35,
        'rowspan' => 1,
        'class' => 'selector-td',
      );
    }

    $cols[] = array(
      'data' => $answer['targettext'],
    );

    $rows[] = $cols;
  }

  if ($showfeedback) {
    $rows[] = array(array('colspan' => 3, 'data' => '<strong>' . t('Feedback:') . '</strong><br />' . $feedback));
  }

  $table = theme('table', array('rows' => $rows));
  $img = is_numeric($fid) ? theme('image_target_question_image',
    array(
      'fid' => $fid,
      'answers' => $answers,
      'showcorrect' => $showcorrect,
      'showfeedback' => $showfeedback,
    )) : '';
  return $img . $table;
}

/**
 * Theme the img tag for the image_target_question image.
 *
 * @param array &$vars
 *   'fid' int the fid of the actual uploaded image. If an image style is
 *             defined the img returned will be the derivative.
 *   'answers' array one element for each answer with the following keys
 *             'region' array position of a region on the image with keys:
 *               'leftpx' int left position in px.
 *               'width' int width in px.
 *               'top' int top position in px.
 *               'height' int height in px.
 *             'target' array (optional) position of the target marker
 *               'top' int top position of target in px.
 *               'leftpx' int left most position of target in px.
 *   'showcorrect' boolean TRUE to display the answer regions.
 *   'showfeedback' boolean TRUE to display the feedback.
 *
 * @return string
 *   HTML displaying the image_target_question image and (optionally) answer
 *   regions and user targets.
 */
function theme_image_target_question_image(&$vars) {

  $fid = &$vars['fid'];
  $answers = &$vars['answers'];
  $showcorrect = &$vars['showcorrect'];
  $showfeedback = &$vars['showfeedback'];

  if (is_numeric($fid) && $fid > 0) {
    $file = file_load($fid);
    $url = '';
    if (image_target_question_get_image_style()) {
      $url = image_style_url(image_target_question_get_image_style()->name, $file->uri);
    }
    else {
      $scheme = file_uri_scheme($file->uri);
      $wrapper = file_stream_wrapper_get_instance_by_scheme($scheme);
      $url = url($wrapper->getDirectoryPath() . '/' . file_uri_target($file->uri));
    }

    $output = '<div id="image_target_question_image" style="position: relative; height: ' . image_target_question_get_image_height($fid) . 'px;">';
    $output .= theme('image', array(
      'path' => $url,
      'title' => 'Image target',
      'alt' => 'Drag and drop image target.',
      'attributes' => array('style' => 'position: absolute;'),
    ));

    foreach ($answers as $identifier => $answer) {
      // Region.
      if ($showcorrect) {
        $region = $answer['region'];
        $output .= theme('image_target_question_region',
          array(
            'top' => $region['top'],
            'leftpx' => $region['leftpx'],
            'width' => $region['width'],
            'height' => $region['height'],
            'identifier' => $identifier,
          ));
      }

      // Target.
      if (isset($answer['target'])) {
        $target = $answer['target'];
        $output .= theme('image_target_question_target',
          array(
            'top' => $target['top'],
            'leftpx' => $target['leftpx'],
            'identifier' => $identifier,
          ));
      }
    }
    $output .= '</div>';
    return $output;
  }
  return '';
}

/**
 * Theme template preprocess for the targets that get dragged onto the form
 * Override this function in your template if you want to change the targets
 * Be sure to offset the top and left co-ordinates by half the width or height
 * of the target image so it gets centered on the area the drag onto
 * e.g. The default target used by the module is 32px x 32px so top and left
 * co-ordinates are reduced by 16
 */
function template_preprocess_image_target_question_target(&$vars) {
  $path = drupal_get_path('module', 'image_target_question') . '/theme/images';
  $vars['top'] = $vars['top'] - 16;
  $vars['left'] = $vars['leftpx'] - 16;
  $vars['width'] = 32;
  $vars['height'] = 32;
  $vars['imgurl'] = url($path . '/target.png');
}

/**
 * Theme function - describe output of the answering page for the
 * image_target_question
 */
function theme_image_target_question_answering_form(&$vars) {
  $form = &$vars['form'];
  $path = drupal_get_path('module', 'image_target_question');
  drupal_add_library('system', 'ui.draggable');
  drupal_add_library('system', 'ui.droppable');
  drupal_add_library('system', 'ui.sortable');
  drupal_add_js($path . '/js/image_target_question_answer.js');
  drupal_add_css($path . '/theme/image_target_question.css');

  $header = array(
    array('data' => t('Target Number')),
    array('data' => t('Drag Target')),
    array('data' => t('Description')),
  );
  $rows = array();

  foreach ($form['targets'] as $identifier => $target) {
    if (intval($identifier) > 0) {
      $target_div = '<div style="position:relative;"><div class="image_target_question-target" id="image_target_question-target-' . $identifier . '" style="position: absolute; width: 32px; height: 32px; top: -14px; z-index:200; background: url(' . url($path . '/theme/images/target.png') . ') no-repeat scroll 0 0 transparent;">' . $identifier . '</div></div>';
      $row = array();
      $row[] = array(
        'data' => "<span>{$identifier}. </span>",
        'width' => 35,
      );
      $row[] = array(
        'class' => 'drag-' . $identifier,
        'data' => $target_div,
        'width' => 35,
      );
      $row[] = drupal_render($target['targettext']);
      $rows[] = $row;
    }
  }

  $output = drupal_render($form['question']);
  $question_position = variable_get('image_target_question_question_position');
  if ($question_position == '1'){
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    $output .= drupal_render($form['image_target_question_image']);
    $output .= drupal_render($form['tries[answer]']);
    $output .= drupal_render($form['navigation']);
  }
  else{
    $output .= drupal_render($form['image_target_question_image']);
    $output .= drupal_render($form['tries[answer]']);
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    $output .= drupal_render($form['navigation']);
  }

  return $output;
}
