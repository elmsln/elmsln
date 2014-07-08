<?php

/**
 * @file
 * Theme implementation file.
 */

/**
 * Theme function for listing environments.
 */
function theme_environment_indicator_switches($variables) {
  $items = $variables['switches'];
  $output = '<div class="item-list"><ul class="environment-switcher-container">';
  if (!empty($items)) {
    foreach ($items as $item) {
      $output .= '<li class="environment-switcher">' . $item['data'] . "</li>\n";
    }
  }
  $output .= '</ul></div>';
  return $output;
}


/**
 * Theme function for the indicator name.
 */
function theme_environment_indicator_indicator_name($variables) {
  $title = t('You are seeing the @name environment', array('@name' => t($variables['name'])));
  $branch_html = '';
  if (!empty($variables['git_branch'])) {
    $branch_html = '<span class="git-branch"> - ' . $variables['git_branch'] . '</span>';
    $title = t('GIT is running @branch branch in this environment.', array('@branch' => $variables['git_branch']));
  }
  $output = '<div class="environment-indicator-name" title="' . $title . '">' . t($variables['name']) . $branch_html . '</div>';
  $environments = environment_indicator_get_all(TRUE);
  if (!empty($environments)) {
    foreach ($environments as $environment) {
      $items[] = array(
        'data' => l(t('Open in %name', array('%name' => t($environment->name))), 'http://' . $environment->regexurl . '/' . current_path(), array('html' => TRUE)),
      );
    }
    $switcher = theme('environment_indicator_switches', array(
      'switches' => $items,
    ));
    $output .= $switcher;
  }
  return $output;
}

/**
 * Theme function for the indicator bar.
 */
function theme_environment_indicator_indicator_bar($variables) {
  $info = $variables['info'];
  $output = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        drupal_html_class('environment-indicator-' . $info['machine']),
        'position-' . $info['position'],
        'fixed-' . ($info['fixed'] ? 'yes' : 'no'),
      ),
      'id' => 'environment-indicator',
      'style' => 'background-color: ' . $info['color'] . '; color: ' . $info['text_color'],
    ),
    'name' => array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => theme('environment_indicator_indicator_name', $info),
      '#attributes' => array(
        'class' => array('gradient-bar'),
      ),
    ),
  );
  return drupal_render($output);
}

/**
 * Theme function for overriden environment indicator in the header of the list.
 */
function theme_environment_indicator_overwritten_header($variables) {
  $header = '<div class="overriden-indicator"><h2 class="label">' . t('Overriden indicator.') . '</h2>';
  $header .= '<div class="description">' . t('This indicator is in your settings.php file and will take precedence over any other indicator that matches a hostname. To properly set an indicator in your settings.php file, please visit the !help.', array('!help' => l(t('help pages'), 'admin/help/environment_indicator'))) . '</div></div>';
  $table = '<p>' . t('There is no overriden environment indicator in your settings.php file. You only need one in case you want your indicator to be stored in your settings.php file instead of matching against the hostname. The environment switcher is not supported for overriden environments.') . '</p>';
  if (_environment_indicator_is_overwritten()) {
    $headers = array(
      t('Enabled'),
      t('Name'),
      t('Color'),
      t('Text color'),
      t('Position'),
      t('Fixed'),
    );
    $env = _environment_indicator_load_overwritten();
    $color = $env['color'];
    $text_color = $env['text_color'];
    if (strpos($color, '#') !== 0) {
      $color .= ' <span class="error">(' . t('Invalid color definition') . ')</span>';
    }
    if (strpos($text_color, '#') !== 0) {
      $text_color .= ' <span class="error">(' . t('Invalid color definition') . ')</span>';
    }
    $rows[] = array(
      _environment_indicator_is_overwritten() ? 'TRUE' : 'FALSE',
      $env['name'],
      $color,
      $text_color,
      $env['position'],
      $env['fixed'] ? 'TRUE' : 'FALSE',
    );
    $table = theme('table', array('rows' => $rows, 'header' => $headers));
  }
  return $header . $table . '<h2 class="label">' . t('Hostname indicators') . '</h2>';
}
