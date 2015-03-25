<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'category' => t('Taxonomy term'),
  'description' => t('Add a taxonomy term from your site as content.'),
  'icon' => 'icon_term.png',
  'required context' => new ctools_context_required(t('Term'), array('term', 'taxonomy_term')),
  'single' => TRUE,
  'title' => t('Term page display'),
);

function taxonomy_display_term_page_display_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" term page display', array('@s' => $context->identifier));
}

function taxonomy_display_term_page_display_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}

function taxonomy_display_term_page_display_content_type_render($subtype, $conf, $panel_args, $context) {
  $term = isset($context->data) ? clone($context->data) : NULL;
  $block = new stdClass();
  $block->module = 'term_page_display';

  if ($term) {
    $block->title = $term->name;
    $block->delta = $term->tid;
    $term_page = taxonomy_display_taxonomy_term_page($term);
    $block->content = drupal_render($term_page);

    if (user_access('administer taxonomy')) {
      $block->admin_links['update'] = array(
        'title' => t('Edit term'),
        'alt' => t('Edit this term'),
        'href' => 'taxonomy/term/' . $term->tid . '/edit',
        'query' => drupal_get_destination(),
      );
    }
  }
  else {
    $block->delta = 'unknown';
  }

  return $block;
}
