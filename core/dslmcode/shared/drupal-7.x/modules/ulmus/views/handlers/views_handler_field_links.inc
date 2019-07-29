<?php

/**
 * @file
 * Definition of views_handler_field_links.
 */

/**
 * A abstract handler which provides a collection of links.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_links extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['fields'] = array('default' => array());
    $options['check_access'] = array('default' => FALSE);
    $options['destination'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $all_fields = $this->view->display_handler->get_field_labels();
    // Offer to include only those fields that follow this one.
    $field_options = array_slice($all_fields, 0, array_search($this->options['id'], array_keys($all_fields)));
    $form['fields'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Fields'),
      '#description' => t('Fields to be included as links.'),
      '#options' => $field_options,
      '#default_value' => $this->options['fields'],
      '#required' => TRUE,
    );

    $form['check_access'] = array(
      '#type' => 'checkbox',
      '#title' => t('Evaluate router path for access'),
      '#default_value' => $this->options['check_access'],
      '#description' => t('Will check if the path exists and is accessible for the current user. Might be useful, might be slow.'),
    );

    $form['destination'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include destination'),
      '#description' => t('Include a "destination" parameter in the link to return the user to the original view upon completing the link action.'),
      '#default_value' => $this->options['destination'],
    );
  }

  /**
   * {@inheritdoc}
   */
  public function options_submit(&$form, &$form_state) {
    // Remove unselected options.
    $form_state['values']['options']['fields'] = array_filter($form_state['values']['options']['fields']);
    parent::options_submit($form, $form_state);
  }

  /**
   * Return the list of links of this field.
   *
   * @return array
   *   The links which are used by the render function.
   */
  public function get_links() {
    $links = array();
    foreach ($this->options['fields'] as $field) {
      if (empty($this->view->field[$field]->last_render_text)) {
        continue;
      }

      $title = $this->view->field[$field]->last_render_text;
      // Use the alter settings for the link field source not this links field.
      $alter = $this->view->field[$field]->options['alter'];
      $url = array('query' => array());

      // Copy code from views_handler_field::render_as_link().
      $path = $alter['path'];
      if (!empty($path) && $path != '<front>') {
        // Leave path alone on <front> as strip_tags() would remove this.
        // Replace tokens and strip any HTML tags in the path.
        $tokens = $this->get_render_tokens(array());
        $path = strip_tags(decode_entities(strtr($path, $tokens)));

        if (!empty($alter['path_case']) && $alter['path_case'] != 'none') {
          $path = $this->case_transform($path, $alter['path_case']);
        }

        if (!empty($alter['replace_spaces'])) {
          $path = str_replace(' ', '-', $path);
        }

        $url = drupal_parse_url($path);
        if (empty($url)) {
          // Seriously malformed URLs may return FALSE or empty arrays.
          continue;
        }
        $path = $url['path'];

        // Check router menu item access for the current user.
        if ($this->options['check_access']) {
          $menu_item = menu_get_item($path);
          if (!$menu_item || empty($menu_item['access'])) {
            continue;
          }
        }

        if (!empty($this->options['destination']) && empty($alter['external'])) {
          // Override any destination argument included in URL.
          $url['query'] = array_merge($url['query'], drupal_get_destination());
        }

        // Omit tweaks of query, fragment, and link_class.
        $alt = strtr($alter['alt'], $tokens);
        if ($alt && $alt != $title) {
          // Set the title attribute only if it improves accessibility.
          $url['attributes']['title'] = decode_entities($alt);
        }

        if (!empty($alter['rel']) && $rel = strtr($alter['rel'], $tokens)) {
          $url['attributes']['rel'] = $rel;
        }

        $target = check_plain(trim(strtr($alter['target'], $tokens)));
        if (!empty($target)) {
          $url['attributes']['target'] = $target;
        }
      }

      $links[$field] = array(
        'href' => $path,
        'title' => $title,
      ) + $url;
    }

    return $links;
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
  }

}
