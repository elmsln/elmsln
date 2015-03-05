<?php

/**
 * @file
 * Definition of views_plugin_argument_default_taxonomy_tid.
 */

/**
 * Taxonomy tid default argument.
 */
class harmony_core_views_plugin_argument_default_taxonomy_tid extends views_plugin_argument_default_taxonomy_tid {
  function option_definition() {
    $options = parent::option_definition();

    $options['limit'] = array('default' => FALSE, 'bool' => TRUE);
    $options['vocabularies'] = array('default' => array());
    $options['anyall'] = array('default' => ',');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['limit'] = array(
      '#type' => 'checkbox',
      '#title' => t('Limit terms by vocabulary'),
      '#default_value'=> $this->options['limit'],
      '#process' => array('form_process_checkbox', 'ctools_dependent_process'),
    );

    $options = array();
    $vocabularies = taxonomy_get_vocabularies();
    foreach ($vocabularies as $voc) {
      $options[$voc->machine_name] = check_plain($voc->name);
    }

    $form['vocabularies'] = array(
      '#prefix' => '<div><div id="edit-options-vids">',
      '#suffix' => '</div></div>',
      '#type' => 'checkboxes',
      '#title' => t('Vocabularies'),
      '#options' => $options,
      '#default_value' => $this->options['vocabularies'],
      '#process' => array('form_process_checkboxes', 'ctools_dependent_process'),
      '#dependency' => array(
        'edit-options-argument-default-harmony-thread-taxonomy-tid-limit' => array(TRUE),
      ),
    );

    $form['anyall'] = array(
      '#type' => 'radios',
      '#title' => t('Multiple-value handling'),
      '#default_value'=> $this->options['anyall'],
      '#process' => array('form_process_radios', 'ctools_dependent_process'),
      '#options' => array(
        ',' => t('Filter to items that share all terms'),
        '+' => t('Filter to items that share any term'),
      ),
    );
  }

  function get_argument() {
    // Load default argument from thread page.
    foreach (range(1, 3) as $i) {
      $thread = menu_get_object('harmony_thread', $i);
      if (!empty($thread)) {
        break;
      }
    }

    // Check if a thread could be detected.
    if ($thread) {
      $taxonomy = array();
      $fields = field_info_instances('harmony_thread', $thread->type);
      foreach ($fields as $name => $info) {
        $field_info = field_info_field($name);
        if ($field_info['type'] == 'taxonomy_term_reference') {
          $items = field_get_items('harmony_thread', $thread, $name);
          if (is_array($items)) {
            foreach ($items as $item) {
              $taxonomy[$item['tid']] = $field_info['settings']['allowed_values'][0]['vocabulary'];
            }
          }
        }
      }
      if (!empty($this->options['limit'])) {
        $tids = array();
        // Filter by vocabulary.
        foreach ($taxonomy as $tid => $vocab) {
          if (!empty($this->options['vocabularies'][$vocab])) {
            $tids[] = $tid;
          }
        }
        return implode($this->options['anyall'], $tids);
      }
      // Return all tids.
      else {
        return implode($this->options['anyall'], array_keys($taxonomy));
      }
    }

    // If the current page is a view that takes tid as an argument,
    // find the tid argument and return it.
    $views_page = views_get_page_view();
    if ($views_page && isset($views_page->argument['tid'])) {
      return $views_page->argument['tid']->argument;
    }
  }
}
