<?php
/**
 * @file
 * Coder Review module integration.
 */

/**
 * Implements hook_custom_formatters_form_alter_alter() on behalf of
 * coder_review.module.
 */
function coder_review_custom_formatters_form_alter_alter(&$form, &$form_state, $form_id) {
  if (in_array($form_id, array('ctools_export_ui_edit_item_form', 'ctools_export_ui_edit_item_wizard_form')) && isset($form['#formatters']) && 'php' == $form['info']['mode']['#default_value']) {
    drupal_add_css(drupal_get_path('module', 'coder_review') . '/coder_review.css');

    $form['engine']['coder_review'] = array(
      '#type' => 'fieldset',
      '#title' => t('Coder Review'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $reviews = _coder_review_settings_form(_coder_review_get_default_settings('files'), $system = array(), $files = array());
    $form['engine']['coder_review']['reviews'] = array_merge($reviews['coder_reviews_group'], array(
      '#collapsed' => TRUE,
    ));

    $form['engine']['coder_review']['review'] = array(
      '#type' => 'container',
      '#prefix' => '<div id="coder-review-wrapper">',
      '#suffix' => '</div>',
    );

    $form['engine']['coder_review']['button'] = array(
      '#type' => 'button',
      '#value' => t('Review'),
      '#ajax' => array(
        'callback' => 'custom_formatters_coder_review',
        'wrapper' => 'coder-review-wrapper',
      ),
    );
  }
}

/**
 * Ajax callback for Custom Formatters Coder Review integration.
 */
function custom_formatters_coder_review(&$form, $form_state) {
  $directory = 'public://custom_formatters/coder_review';
  if (file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    global $base_url;

    $md5 = md5($form_state['values']['code']);
    file_unmanaged_save_data("<?php\n/**\n * @file\n */\n\n{$form_state['values']['code']}", "{$directory}/{$md5}.php", FILE_EXISTS_REPLACE);
    $file = str_replace($base_url . base_path(), '', file_create_url("{$directory}/{$md5}.php"));

    $form_state = array(
      'storage' => array(
        'coder_reviews' => $form_state['values']['coder_reviews'],
        'coder_severity' => $form_state['values']['coder_severity'],
        'coder_file_list' => $file,
        'coder_files' => 1,
      )
    );
    $review = coder_review_page_form(array(), $form_state, 'files');

    $form['engine']['coder_review']['review'][$file] = $review[$file]['output'];
    foreach ($form['engine']['coder_review']['review'][$file]['#results'] as &$result) {
      // Adjust the line numbering.
      $result = preg_replace('/\/\>Line (\d+):(.*?<pre>)/e', '"/>Line " . ($1 - 5) . ":$2"', $result);
    }
    unset($form['engine']['coder_review']['review'][$file]['#filename']);

    file_unmanaged_delete("{$directory}/{$md5}.php");
  }

  drupal_get_messages(NULL, TRUE);
  return $form['engine']['coder_review']['review'];
}
