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
  $info = array(
    'tokens' => array(
      'harmony_thread' => array(
        'summary' => array(
          'name' => t('Summary'),
          'description' => t("The summary of the thread's first post text."),
        ),
        'summary-pt' => array(
          'name' => t('Summary plain text'),
          'description' => t("The summary of the thread's first post text stripped of any markup."),
        ),
      ),
    ),
  );

  // Integrate with the profanity module.
  if (module_exists('profanity')) {
    $wordlists = profanity_get_lists_flat();
    if (!empty($wordlists)) {
      $lists = array();
      foreach ($wordlists as $name => $label) {
        $lists[] = check_plain("$label ($name)");
      }
      $lists_replacement = t('Possible lists: !lists', array('!lists' => implode(', ', $lists)));

      $info['tokens']['harmony_thread']['summary-pt-profanity'] = array(
        'name' => t('Summary plain text profanity filtered'),
        'description' => t("The summary of the thread's first post text stripped of markup and processed by a specified profanity word list. Use with the word list machine name. !replacements", array('!replacements' => $lists_replacement)),
        'dynamic' => TRUE,
      );
      $info['tokens']['harmony_thread']['summary-profanity'] = array(
        'name' => t('Summary profanity filtered'),
        'description' => t("The summary of the thread's first post text processed by a specified profanity word list. Use with the word list machine name. !replacements", array('!replacements' => $lists_replacement)),
        'dynamic' => TRUE,
      );
    }
  }

  return $info;
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
      // Summary token.
      if ($name === 'summary' || $name === 'summary-pt' || strpos($name, 'summary-pt-profanity') === 0 || strpos($name, 'summary-profanity') === 0) {
        if ($wrapper->field_harmony_first_post->value() && $wrapper->field_harmony_first_post->field_harmony_text->value()) {
          $text = $wrapper->field_harmony_first_post->field_harmony_text->raw();

          // Strip tags if supplying the plain text version of the token.
          if ($name === 'summary-pt' || strpos($name, 'summary-pt-profanity') === 0) {
            if ($sanitize) {
              $text['safe_value'] = strip_tags($text['safe_value']);
            }
            else {
              $text['value'] = strip_tags($text['value']);
            }
          }

          $replacements[$original] = $sanitize ? text_summary($text['safe_value'], $text['format'], variable_get('harmony_core_meta_summary_max_length', 200)) : $text['value'];
        }
      }

      // Profanity filtered summary token, just alter the summary generated
      // text.
      if (strpos($name, 'summary-pt-profanity') === 0 || strpos($name, 'summary-profanity') === 0) {
        if (module_exists('profanity') && $replacements[$original] != '') {
          $name_parts = explode(':', $name);

          // Profanity filter the content.
          if (!empty($name_parts[1])) {
            $replacements[$original] = profanity_list_execute($name_parts[1], $replacements[$original]);
          }
        }
      }
    }
  }

  return $replacements;
}
