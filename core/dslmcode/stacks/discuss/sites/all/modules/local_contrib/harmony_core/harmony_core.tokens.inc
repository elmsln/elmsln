<?php
/**
 * @file
 * harmony_core.tokens.inc
 */

/**
 * Implements hook_token_info().
 */
function harmony_core_token_info() {
  // Just tack an extra token in, entity_token will be doing the rest.
  return array(
    'tokens' => array(
      'harmony_thread' => array(
        'summary' => array(
          'name' => t('Summary'),
          'description' => t("The summary of the thread's first post text."),
        ),
      ),
    ),
  );
}

/**
 * Implements hook_tokens().
 */
function harmony_core_tokens($type, $tokens, array $data = array(), array $options = array()) {
  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }
  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  if ($type == 'harmony_thread' && !empty($data['harmony_thread'])) {
    $thread = $data['harmony_thread'];
    $wrapper = entity_metadata_wrapper($type, $thread);

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'summary':
          if ($wrapper->field_harmony_first_post->value() && $wrapper->field_harmony_first_post->field_harmony_text->value()) {
            $text = $wrapper->field_harmony_first_post->field_harmony_text->raw();

            if ($sanitize) {
              $sanitised_text = check_plain($text['value']);
              $trimmed_text = truncate_utf8($sanitised_text, variable_get('harmony_core_meta_summary_max_length', 200), FALSE, TRUE);
              $replacements[$original] = $trimmed_text;
            }
            else {
              $replacements[$original] = $text['value'];
            }
          }
          break;
      }
    }
  }

  return $replacements;
}
