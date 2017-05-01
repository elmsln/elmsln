<?php

/**
 * @file
 * Common pages for the Media module.
 */

/**
 * CTools modal callback for editing a file.
 */
function media_file_edit_modal($form, &$form_state, $file, $js) {
  ctools_include('modal');
  ctools_include('ajax');

  // If entity translation is enabled for the file entities and we have parent
  // entity form/source langcodes, use them for the currently edited file.
  if (!empty($_GET['media_parent_entity_form_langcode']) && is_string($_GET['media_parent_entity_form_langcode']) && module_invoke('entity_translation', 'enabled', 'file', $file)) {
    $languages = language_list();
    if (isset($languages[$_GET['media_parent_entity_form_langcode']])) {
      $langcode = $_GET['media_parent_entity_form_langcode'];
      $translation_handler = entity_translation_get_handler('file', $file);
      $translation_handler->setActiveLanguage($langcode);
      $translations = $translation_handler->getTranslations();
      if (!isset($translations->data[$langcode])) {
        if (!empty($_GET['media_parent_entity_source_langcode']) && is_string($_GET['media_parent_entity_source_langcode']) && isset($translations->data[$_GET['media_parent_entity_source_langcode']])) {
          $source_langcode = $_GET['media_parent_entity_source_langcode'];
        }
        else {
          $source_langcode = $translation_handler->getLanguage();
        }
        $translation_handler->setSourceLanguage($source_langcode);
      }
    }
  }

  $form_state['ajax'] = $js;
  form_load_include($form_state, 'inc', 'file_entity', 'file_entity.pages');

  $output = ctools_modal_form_wrapper('file_entity_edit', $form_state);

  if ($js) {
    $commands = $output;

    if ($form_state['executed']) {
      $commands = array(ctools_modal_command_dismiss(t('File saved')));
      $preview = media_get_thumbnail_preview($file);
      $commands[] = ajax_command_replace('.media-item[data-fid=' . $file->fid . ']', render($preview));
    }

    print ajax_render($commands);
    exit();
  }

  // Otherwise, just return the output.
  return $output;
}
