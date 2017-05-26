<?php

/**
 * @file
 * Media translation handler for the entity translation module.
 */


/**
 * Media translation handler.
 */
class MediaEntityTranslationHandler extends EntityTranslationDefaultHandler {

  /**
   * Constructor function.
   */
  public function __construct($entity_type, $entity_info, $entity) {
    parent::__construct('file', $entity_info, $entity);
  }

  /**
   * Entity form handler.
   *
   * @see EntityTranslationDefaultHandler::entityForm()
   */
  public function entityForm(&$form, &$form_state) {
    parent::entityForm($form, $form_state);

    if (isset($form['actions']['delete_translation'])) {
      $form['actions']['delete_translation']['#weight'] = 10;
    }

    // The "Source language" element is unsupported on modal forms.
    if (!empty($form_state['ajax'])) {
      $form['source_language']['#access'] = FALSE;
    }

    if ($this->getPathScheme() == 'media') {
      $language = $GLOBALS[LANGUAGE_TYPE_CONTENT];
      $form_langcode = $this->getActiveLanguage();
      $source_langcode = $this->getSourceLanguage();
      $translations = $this->getTranslations();

      // If a translation in the current content language is missing we display
      // a link to create it, unless we are not already doing it.
      if ($language->language != $form_langcode && empty($source_langcode) && !isset($translations->data[$language->language])) {
        $link = array(
          'title' => t('Add @language translation', array('@language' => $language->name)),
          'href' => $this->getEditPath() . '/add/' . $form_langcode . '/' . $language->language,
          'localized_options' => array('attributes' => array('class' => array('ctools-use-modal'))),
        );
        $form['media_add_translation'] = array(
          '#theme' => 'menu_local_action',
          '#link' => $link,
          '#weight' => -110,
          '#prefix' => '<ul class="action-links">',
          '#suffix' => '</ul>',
        );
      }

      // Hide unsupported elements.
      $form['source_language']['#access'] = FALSE;
      if (isset($form['actions']['delete_translation'])) {
        $form['actions']['delete_translation']['#access'] = FALSE;
      }
    }
  }
}
