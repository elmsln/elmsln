<?php

/**
 * @file
 * Display Suite example layout configuration.
 */

function ds_example_layout() {
  return array(
    'label' => t('Example layout'),
    'regions' => array(
      'left' => t('Left'),
      'right' => t('Right'),
    ),
    // Uncomment if you want to include a CSS file for this layout (example_layout.css)
    // 'css' => TRUE,
    // Uncomment if you want to include a preview for this layout (example_layout.png)
    // 'image' => TRUE,
  );
}
