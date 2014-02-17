<?php

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'vef_video_styles',  // As defined in hook_schema().
  'access' => 'administer video styles',  // Define a permission users must have to access these pages.

  // Define the menu item.
  'menu' => array(
    'menu prefix' => 'admin/config/media',
    'menu item' => 'vef_video_styles',
    'menu title' => 'Configure Video Embed Styles',
    'menu description' => 'Administer Video Embed Field\'s video styles.',
  ),

  // Define user interface texts.
  'title singular' => t('video style'),
  'title plural' => t('video styles'),
  'title singular proper' => t('Video Styles'),
  'title plural proper' => t('Video Styles'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'video_embed_field_video_style_form',
    // 'submit' and 'validate' are also valid callbacks.
  ),
);