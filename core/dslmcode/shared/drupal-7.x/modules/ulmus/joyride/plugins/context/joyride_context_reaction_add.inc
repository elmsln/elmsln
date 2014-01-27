<?php

class joyride_context_reaction_add extends context_reaction {
  function options_form($context) {
    $context_values = $this->fetch_from_context($context, 'values');

    return array(
      'joyride_auto_start' => array(
        '#type' => 'checkbox',
        '#title' => t('Start tour automatically'),
        '#description' => t('Whatever to start Joyride on page load. If you disable this be sure to add <em>joyride start</em> link to the page.
          This could be done via adding a "Joyride Start Tour" block, or by invoking <code>print theme(\'joyride_start_link\')</code> in your theme.'),
        '#default_value' => isset($context_values['joyride_auto_start']) ? $context_values['joyride_auto_start'] : FALSE,
      ),
      'joyride_play_once' => array(
        '#type' => 'checkbox',
        '#title' => t('Play tour only once'),
        '#description' => t('Check this to play the tour only once'),
        '#default_value' => isset($context_values['joyride_play_once']) ? $context_values['joyride_play_once'] : FALSE,
        '#states' => array(
          'visible' => array(
            ':input[type="checkbox"]#edit-reactions-plugins-joyride-add-joyride-auto-start' => array(
              'checked' => TRUE,
            )
          ),
        ),
      ),
      'joyride_tour_content' => array(
        '#type' => 'textarea',
        '#title' => t('Joyride Tour Tips'),
        '#description' => t('Please enter Joyride Tips content. These tips will be used to initialize Joyride plugin on selected page.'),
        '#default_value' => isset($context_values['joyride_tour_content']) ? $context_values['joyride_tour_content'] : NULL,
        '#rows' => 24,
      ),
    );
  }

  function options_form_submit($values) {
    if(!isset($values['joyride_play_once'])) $values['joyride_play_once'] = FALSE;
    $values['joyride_play_once'] = empty($values['joyride_auto_start']) ? FALSE : $values['joyride_play_once'];
    return $values;
  }

  function execute(&$vars = NULL) {
    $contexts = $this->get_contexts();

    foreach ($contexts as $context) {
      if (!empty($context->reactions[$this->plugin])) {
        $library = libraries_load('joyride');
        $library_loaded = $library && !empty($library['loaded']);

        drupal_add_library('system', 'jquery.cookie');

        $js_name = 'jquery.joyride.js';
        $base_path = 'sites/all/libraries/joyride';

        if (!$library_loaded) {
          drupal_set_message(t('Can\'t load Joyride library. Please download !url jQuery plugin and extract it to @path, so @js can be found at @full_path. Also please purge version info from Joyride file names (both .js and .css)', array(
            '!url' => l(t('Zurb Joyride'), 'https://github.com/zurb/joyride'),
            '@path' => $base_path,
            '@js' => $js_name,
            '@full_path' => $base_path . '/' . $js_name,
          )), 'error');
          return FALSE;
        }

        drupal_add_js(drupal_get_path('module', 'joyride') . '/inc/js/joyride_context.js');

        $tips_content = $context->reactions[$this->plugin]['joyride_tour_content'];
        if(empty($tips_content)) return FALSE;

        $js_settings = array(
          'joyrideContext' => array(
            'tips_content' => theme('joyride_tips', array('tips_content' => $tips_content)),
            'auto_start' => (boolean)$context->reactions[$this->plugin]['joyride_auto_start'],
            'play_once' => (boolean)$context->reactions[$this->plugin]['joyride_play_once'],
          ),
        );
        drupal_add_js($js_settings, 'setting');
      }
    }
  }
}