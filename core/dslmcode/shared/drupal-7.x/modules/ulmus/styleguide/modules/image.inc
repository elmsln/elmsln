<?php

/**
 * @file
 * Style Guide plugin file for the Image module.
 */

/**
 * Implements hook_styleguide().
 */
function image_styleguide() {
  $items = array();

  // Get the sample file provided by the module.
  if (file_destination('public://styleguide-preview.jpg', FILE_EXISTS_ERROR) !== FALSE) {
    // Move the image so that styles may be applied.
    file_unmanaged_copy(styleguide_image('vertical'), 'public://styleguide-preview.jpg', FILE_EXISTS_ERROR);
  }

  // Iterate through the image styles on the site.
  foreach (image_style_options(FALSE) as $stylename => $style) {
    $items['image_' . $stylename] = array(
      'title' => t('Image style, @stylename', array('@stylename' => $stylename)),
      'content' => theme('image_style', array('path' => 'public://styleguide-preview.jpg', 'style_name' => $stylename)),
      'group' => t('Media')
    );
  }

  return $items;
}
