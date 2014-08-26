<?php

/**
 * @file
 * Admin page callbacks for the advanced CSS/JS aggregation module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function css_emimage_admin_info_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: CSS Embedded Images'));

  $form = array();
  $form['css_emimage'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS Embedded Images'),
  );
  $form['css_emimage']['css_emimage_files'] = array(
    '#type' => 'checkbox',
    '#title' => t('Files: Enable CSS Embedded Images'),
    '#default_value' => variable_get('css_emimage_files', CSS_EMIMAGE_FILES),
  );
  $form['css_emimage']['css_emimage_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Inline: Enable CSS Embedded Images'),
    '#default_value' => variable_get('css_emimage_inline', CSS_EMIMAGE_INLINE),
  );
  $form['css_emimage']['css_emimage_force_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always inline embedded images'),
    '#description' => t('By default CSS Embedded Images places image data exceeding !limit in a CSS file separate from the rest of the site styles. This allows for parallel rendering of site styles while the relatively large image data is in transit, providing an improved user experience (especially for visitors with slow connections). Enabling this option will force images to always be embedded inline, similar to the 6.x-1.x behavior; however, this is not recommended.', array('!limit' => format_size(variable_get('css_emimage_inline_datauri_limit', CSS_EMIMAGE_INLINE_DATAURI_LIMIT)))),
    '#default_value' => variable_get('css_emimage_force_inline', 0),
  );
  $form['css_emimage']['css_emimage_ielimit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only embed images less than 32KB'),
    '#description' => t('Internet Explorer does not support embedded images larger than 32KB. If you are not concerned about IE support you can ignore this limitation; otherwise, it is best to leave this checked.'),
    '#default_value' => variable_get('css_emimage_ielimit', 1),
  );

  return system_settings_form($form);
}
