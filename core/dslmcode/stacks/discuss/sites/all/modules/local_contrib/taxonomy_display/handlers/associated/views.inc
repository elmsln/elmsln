<?php

/**
 * Ajax callback; return just the term display sub-form.
 *
 * @return renderable array
 */
function taxonomy_display_associated_display_handler_views_callback($form, $form_state) {
  $field = taxonomy_display_form_fieldset($form, 'associated');
  if ($field) {
    return $field['display'];
  }
}

/**
 * Add a display handler that will use the Drupal core method of display.
 */
class TaxonomyDisplayAssociatedDisplayHandlerViews extends TaxonomyDisplayAssociatedDisplayHandler {
  /**
   * Build our output to be rendered to the user.
   *
   * @see TaxonomyDisplayAssociatedDisplayHandler::displayAssociated()
   */
  public function displayAssociated($term, $options = NULL) {
    module_load_include('module', 'views');

    $build = array();

    // The code below essentially mimics views_embed_view() but outputs a
    // watchdog error if the view/view display isn't valid.

    $view = views_get_view($options['view']);

    // If view/view display isn't valid.
    if (!$view || !isset($view->display[$options['display']])) {
      watchdog(
        'taxonomy_display',
        'The view and/or view display for %vocab is missing, go to the <a href="!link">full display page</a> and reconfigure the taxonomy term\'s associated content display.',
        array(
          '%vocab' => $term->vocabulary_machine_name,
          '!link' => url('admin/structure/taxonomy/' . $term->vocabulary_machine_name . '/display/full'),
        ),
        WATCHDOG_ERROR
      );
    }
    // Else if the user has access to the view.
    elseif ($view->access($options['display'])) {
      // Ensure links stay on taxonomy term page.
      $view->override_path = 'taxonomy/term/%';

      // Generate the view's output.
      $output = $view->preview($options['display'], array($term->tid));
      if ($output) {
        $build['view'] = array(
          '#markup' => $output,
        );
      }
    }

    return $build;
  }

  /**
   * Build our form for the fieldset.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    module_load_include('module', 'views');

    $form['#description'] = t('Use <em>Views</em> for displaying associated content.');

    // Get options for the view select field.
    $views = views_get_all_views();
    $select_options = array();
    foreach ($views as $view) {
      if (views_view_is_enabled($view)) {
        // #1507632 It has been reported that some views have empty human names,
        // so we add a condition and use the view name if human is unavailable.
        $select_options[$view->name] = empty($view->human_name) ? $view->name : $view->human_name;
      }
    }
    $form['view'] = array(
      '#ajax' => array(
        'callback' => 'taxonomy_display_associated_display_handler_views_callback',
        'wrapper' => 'replace-td-views-display-field',
      ),
      '#default_value' => isset($options['view']) ? $options['view'] : FALSE,
      '#description' => t('Select which view you would like to display the associated content.'),
      '#options' => $select_options,
      '#title' => t('View'),
      '#type' => 'select',
    );

    // Retrieve the views displays to supply as options.
    if (isset($values['view'])) {
      $view = $views[$values['view']];
    }
    elseif (isset($options['view'])) {
      $view = $views[$options['view']];
    }
    else {
      // If the view hasn't been submitted and it's not previously saved then
      // fetch it as the first view field option.
      reset($select_options);
      $view = $views[key($select_options)];
    }

    $select_options = array();
    // Get options for the view's display field.
    foreach ($view->display as $key => $display) {
      $select_options[$key] = $display->display_title;
    }

    $form['display'] = array(
      '#default_value' => isset($options['display']) ? $options['display'] : 'default',
      '#description' => t('The display selected will have the taxonomy term ID supplied as the first argument.'),
      '#options' => $select_options,
      '#prefix' => '<div id="replace-td-views-display-field">',
      '#suffix' => '</div>',
      '#title' => t("View's display"),
      '#type' => 'select',
    );
  }

  /**
   * We store values to access later for rendering and editing.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  public function formSubmit($form, &$values) {
    // We are using the exact keys that our formFieldset() implementation
    // defines and we want all of the values stored, so we have no need to alter
    // them before returning.
    return $values;
  }
}
