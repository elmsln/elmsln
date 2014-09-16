<?php

/**
 * Extends the views plugin to make the exposed form work when included
 * in an entityreference widget (itself included in an entity form).
 * This is accomplished by using #ajax.
 */
class entityreference_view_widget_plugin_exposed_form extends views_plugin_exposed_form {
  /**
   * Overrides the parent render_exposed_form() method to just build the exposed
   * form, but not render it.
   * The output of this function will end up in $view->exposed_widgets, allowing
   * it to be added to the widget.
   * Unfortunately, the theme function will try to print $view->exposed_widgets,
   * but the preprocess hook in the module will unset that in time.
   */
  function render_exposed_form($block = FALSE) {
    $form_state = array(
      'view' => &$this->view,
      'display' => &$this->display,
      'method' => 'get',
      'rerender' => TRUE,
      'no_redirect' => TRUE,
      'always_process' => TRUE,
      'exposed_form_plugin' => $this,
    );

    // We must build and validate the form. One reason is that some filter
    // handlers (like views_handler_filter_term_node_tid) store internal values
    // at exposed_validate() - so, query results will be incorrect unless
    // views_exposed_form_validate() is run.
    $form = drupal_build_form('views_exposed_form', $form_state);
    // Seed the defaults so that the view renders on first page load.
    if (empty($this->view->exposed_data)) {
      $this->view->exposed_data = $form_state['values'];
    }
    // Now get the actual form structure that the module needs.
    $form = views_exposed_form($form, $form_state);

    // Return only the needed parts of the form.
    $return_form = array(
      '#theme' => $form['#theme'],
      '#info' => $form['#info'],
      // Return a reference to the plugin, for validation / submission.
      '#exposed_form_plugin' => $this,
    );
    foreach (element_get_visible_children($form) as $key) {
      $return_form[$key] = $form[$key];
      // Adjust the element's values to the exposed input used for filtering
      // the view. Set #default_value since we do not return $form_state.
      if (isset($form_state['input'][$key]) && isset($return_form[$key]['#default_value'])) {
        $return_form[$key]['#default_value'] = $form_state['input'][$key];
      }
    }
    return $return_form;
  }

  function exposed_form_alter(&$form, &$form_state) {
    parent::exposed_form_alter($form, $form_state);

    if (!empty($this->options['autosubmit'])) {
      foreach (element_get_visible_children($form) as $key) {
        // Other info will be filled-in by entityreference_view_widget_prepare_filters().
        $form[$key]['#ajax'] = array(
          'method' => 'replace',
          'progress' => array(
            'type' => 'throbber',
            'message' => '',
          ),
        );
      }
    }
    else {
      unset($form['submit']['#id']);
      $form['submit']['#type'] = 'button';
      $form['submit']['#ajax'] = array(
        'method' => 'replace',
        'progress' => array(
          'type' => 'throbber',
          'message' => '',
        ),
      );
    }
    // The button basically doesn't work with JS on or off, without this.
    $form['submit']['#name'] = 'apply';

    // Don't run the default submit handlers, since all that is handled
    // by the widget. (Do run validate handler; see above.)
    $form['#submit'] = array();
  }
}
