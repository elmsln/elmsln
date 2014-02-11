<?php

/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 */



/**
 * Implementation of hook_image_effect_info().
 */
function imagefield_focus_image_effect_info() {
  $effects = array(
    'imagefield_focus_scale_and_crop' => array(
      'label' => t('Focus Scale And Crop'),
      'help' => t('Scale and crop based on data provided by <em>ImageField Focus</em>.'),
      'effect callback' => 'imagefield_focus_scale_and_crop_effect',
      'form callback' => 'imagefield_focus_scale_and_crop_form',
      'summary theme' => 'imagefield_focus_scale_and_crop_summary',
    ),
    'imagefield_focus_crop' => array(
      'label' => t('Focus Crop'),
      'help' => t('Crop based on data provided by <em>ImageField Focus</em>.'),
      'effect callback' => 'imagefield_focus_crop_effect',
      'form callback' => 'imagefield_focus_crop_form',
      'summary theme' => 'imagefield_focus_crop_summary',
    ),
  );

  return $effects;
}



/**
 * Implementation of hook_theme().
 */
function imagefield_focus_theme() {
  $theme = array(
    'imagefield_focus_scale_and_crop_summary' => array(
      'variables' => array('data' => NULL),
    ),
    'imagefield_focus_crop_summary' => array(
      'variables' => array('data' => NULL),
    ),
  );

  return $theme;
}



/**
 * Focus Scale and Crop.
 */
function imagefield_focus_scale_and_crop_form($data = array()) {
  $form = image_resize_form($data);

  $form['strength'] = array(
    '#type' => 'radios',
    '#title' => t('Focus strength'),
    '#options' => array(
      'high'   => t('High'),
      'medium' => t('Medium'),
      'low'    => t('Low'),
    ),
    '#default_value' => isset($data['strength']) ? $data['strength'] : 'high',
  );

  if (module_exists('smartcrop')) {
    $form['fallback'] = array(
      '#type' => 'radios',
      '#title' => t('Fallback effect'),
      '#options' => array(
        'image'      => t('!module: !effect', array('!module' => 'Image',     '!effect' => t('Scale And Crop'))),
        'smartcrop'  => t('!module: !effect', array('!module' => 'SmartCrop', '!effect' => t('Scale and Smart Crop'))),
      ),
      '#default_value' => isset($data['fallback']) ? $data['fallback'] : 'image',
      '#description' => t('The effect to apply when no focus data is available.'),
    );
  }

  return $form;
}

function theme_imagefield_focus_scale_and_crop_summary($variables) {
  $data = $variables['data'];
  return theme('image_resize_summary', array('data' => $data)) .' '. t('!strength strength', array('!strength' => t($data['strength'])));
}

function imagefield_focus_scale_and_crop_effect(&$image, $data) {
  $files = file_load_multiple(array(), array('uri' => $image->source));
  if (count($files)) {
    $file = reset($files);
    $xoffset = 0;
    $yoffset = 0;

    if (($rect = $file->crop_rect) && ($rect = imagefield_focus_parse($rect))) {
      if (!image_crop_effect($image, $rect)) {
        return FALSE;
      }
      $xoffset = $rect['xoffset'];
      $yoffset = $rect['yoffset'];
    }

    if (($rect = $file->focus_rect) && ($rect = imagefield_focus_parse($rect))) {
      $rect['xoffset'] -= $xoffset;
      $rect['yoffset'] -= $yoffset;

      $scale = min(1, $data['width'] / $rect['width'], $data['height'] / $rect['height']);
      $scale_low = min($scale, max($data['width'] / $image->info['width'], $data['height'] / $image->info['height']));
      if ($data['strength'] == 'medium') {
        $scale = ($scale + $scale_low) / 2;
      }
      elseif ($data['strength'] == 'low') {
        $scale = $scale_low;
      }

      $width0 = $image->info['width'] * $scale;
      $height0 = $image->info['height'] * $scale;
      if (($scale < 1) && !image_resize_effect($image, array('width' => $width0, 'height' => $height0))) {
        return FALSE;
      }

      foreach ($rect as $key => $value) {
        $rect[$key] = $value * $scale;
      }
      $width = min($width0, $data['width']);
      $height = min($height0, $data['height']);
      $xoffset = min($width0 - $width, max(0, $rect['xoffset'] + ($rect['width'] - $width) / 2));
      $yoffset = min($height0 - $height, max(0, $rect['yoffset'] + ($rect['height'] - $height) / 2));
      return image_crop_effect($image, array('width' => $width, 'height' => $height, 'anchor' => $xoffset .'-'. $yoffset));
    }
  }

  if ((@$data['fallback'] == 'smartcrop') && module_exists('smartcrop')) {
    return smartcrop_scale_effect($image, $data);
  }

  return image_scale_and_crop_effect($image, $data);
}



/**
 * Focus Crop.
 */
function imagefield_focus_crop_form($data = array()) {
  $form['target'] = array(
    '#type' => 'radios',
    '#title' => t('Crop based on'),
    '#options' => array(
      'crop_rect only'   => t('Crop rectangle only'),
      'focus_rect only'  => t('Focus rectangle only'),
      'crop_rect first'  => t('Crop rectangle if available, Focus rectangle otherwise'),
      'focus_rect first' => t('Focus rectangle if available, Crop rectangle otherwise'),
    ),
    '#default_value' => isset($data['target']) ? $data['target'] : 'crop_rect only',
  );

  return $form;
}

function theme_imagefield_focus_crop_summary($variables) {
  $form = imagefield_focus_crop_form();
  return t('based on !target', array('!target' => $form['target']['#options'][$variables['data']['target']]));
}

function imagefield_focus_crop_effect(&$image, $data) {
  $files = file_load_multiple(array(), array('uri' => $image->source));
  if (count($files)) {
    $file = reset($files);
    ($crop_rect = $file->crop_rect) && ($crop_rect = imagefield_focus_parse($crop_rect));
    ($focus_rect = $file->focus_rect) && ($focus_rect = imagefield_focus_parse($focus_rect));

    $target = $data['target'];
    if ($crop_rect && ($target == 'crop_rect only' || $target == 'crop_rect first' || $target == 'focus_rect first' && !$focus_rect)) {
      return image_crop_effect($image, $crop_rect);
    }
    if ($focus_rect && ($target == 'focus_rect only' || $target == 'focus_rect first' || $target == 'crop_rect first' && !$crop_rect)) {
      return image_crop_effect($image, $focus_rect);
    }
  }

  return TRUE;
}
