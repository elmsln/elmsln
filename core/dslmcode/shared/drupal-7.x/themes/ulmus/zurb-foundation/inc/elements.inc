<?php
/**
 * Override drupal core messages with zurb foundation alert-box messages.
 * Customize the colors within the _settings.scss file.
 *
 * http://foundation.zurb.com/docs/elements.php#panelEx
 */
function zurb_foundation_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'error' => t('Error message'),
    'status' => t('Status message'),
    'warning' => t('Warning message'),
  );

  $status_mapping = array(
    'error' => 'alert',
    'status' => 'success',
    'warning' => 'secondary'
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    if (isset($status_mapping[$type])) {
      $output .= "<div data-alert class=\"alert-box $status_mapping[$type]\">\n";
    }
    else {
      $output .= "<div data-alert class=\"alert-box\">\n";
    }

    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul class=\"no-bullet\">\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }

    if(!theme_get_setting('zurb_foundation_messages_modal')) 
      $output .= '<a href="#" class="close">&times;</a>';
    
    $output .= "</div>\n";
  }

  if ($output != '' && theme_get_setting('zurb_foundation_messages_modal')) {
    $output = '<div id="status-messages" class="reveal-modal" role="alertdialog">'. $output;
    $output .= '<a class="close-reveal-modal">&#215;</a>';
    $output .= "</div>";
  }

  return $output;
}
