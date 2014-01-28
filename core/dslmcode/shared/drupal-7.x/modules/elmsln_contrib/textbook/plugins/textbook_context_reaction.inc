<?php
/**
 * @file
 * The Context reaction plugin to add asset files
 *
 * Contextually add asset files to any page on your site.
 */

/**
 * Expose themes as context reactions.
 */
class textbook_context_reaction extends context_reaction {

  function __construct($plugin, $info) {
    parent::__construct($plugin, $info);
    $this->title = t('Textbook Style');
  }
  
  /**
   * Prepare formatted form array showing grouped assets
   *  grouped by location and show as checkboxes
   */
  function options_form($context) {
    $values = $this->fetch_from_context($context);
    $styles = _textbook_load_styles();
    foreach ($styles as $key => $style) {
      $textbook_styles[$key] = $style['name'];
    }
    $form = array(
      '#tree' => TRUE,
      '#title' => t('Textbook Style'),
      '#description' => t('What textbook style should be used when this context is active.'),
    );
    // set default to global active if none-set
    if (isset($context->reactions['textbook']['textbook_active'])) {
      $default_style = $context->reactions['textbook']['textbook_active'];
    }
    else {
      $default_style = _textbook_active_style();
    }
    $form['textbook_active'] = array(
      '#type' => 'select',
      '#title' => t('Textbook style'),
      '#description' => t('Style to use'),
      '#default_value' => $default_style,
      '#options' => $textbook_styles,
    );
    
    return $form;
  }

  /**
   * Implementation of the built-in context plugin class execution
   */
  function execute() {
    $contexts = context_active_contexts();
    $classes = array();
    // if this reaction is active in an active context
    foreach ($contexts as $key => $value) {
      // set the global textbook style value
      if (!empty($value->reactions[$this->plugin])) {
        global $active_textbook_style;
        $active_textbook_style = $value->reactions[$this->plugin]['textbook_active'];
      }
    }
  }
}