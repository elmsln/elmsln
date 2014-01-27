<?php
/**
 * @file
 * Base field handler for views_xml_backend.
 */

class views_xml_backend_handler_field extends views_handler_field {

  function render($values) {
    if (!isset($values->{$this->field_alias})) {
      return;
    }
    $values = $values->{$this->field_alias};
    if ($this->options['multiple']) {
      foreach ($values as $i => $value) {
        $values[$i] = $this->render_field($value);
      }
      if ($this->options['list_type'] == 'other') {
        return implode(check_plain($this->options['custom_separator']), $values);
      }
      if ($this->options['list_type'] == 'br') {
        return implode('<br />', $values);
      }
      return theme('item_list', array(
        'items' => $values,
        'type' => $this->options['list_type'],
      ));
    }
    return $this->render_field($values);
  }

  function render_field($value) {
    return check_plain(decode_entities($value));
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['xpath_selector'] = array('default' => '');
    $options['multiple'] = array('default' => FALSE);
    $options['list_type'] = array('default' => 'ul');
    $options['custom_separator'] = array('default' => ', ');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['xpath_selector'] = array(
      '#title' => t('XPath selector'),
      '#description' => t('The xpath selector'),
      '#type' => 'textfield',
      '#default_value' => $this->options['xpath_selector'],
      '#required' => TRUE,
    );
    $form['multiple'] = array(
      '#title' => t('Allow multiple'),
      '#description' => t('Treat this field as multi-valued.'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['multiple'],
    );
    $form['list_options'] = array(
      '#type' => 'fieldset',
      '#states' => array(
        'visible' => array(
          ':input[name="options[multiple]"]' => array(
            'checked' => TRUE,
          ),
        ),
      ),
    );
    $form['list_type'] = array(
      '#title' => t('List type'),
      '#description' => t('The type of list.'),
      '#type' => 'radios',
      '#default_value' => $this->options['list_type'],
      '#options' => array(
        'ul' => t('Unordered list'),
        'ol' => t('Ordered list'),
        'br' => check_plain('<br />'),
        'other' => t('Custom separator'),
      ),
      '#fieldset' => 'list_options',
    );
    $form['custom_separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#default_value' => $this->options['custom_separator'],
      '#states' => array(
        'visible' => array(
          ':input[name="options[list_type]"]' => array(
            'value' => 'other',
          ),
        ),
      ),
      '#fieldset' => 'list_options',
    );
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    // Add the field.
    $this->table_alias = 'xml';

    $this->field_alias = $this->query->add_field(
      $this->table_alias,
      $this->options['xpath_selector'],
      '',
      $this->options
    );
  }

  function ui_name($short = FALSE) {
    if (!empty($this->options['ui_name'])) {
      $title = check_plain($this->options['ui_name']);
      return $title;
    }
    $title = $this->definition['title'];

    if ($short && isset($this->definition['title short'])) {
      $title = $this->definition['title short'];
    }

    return t('!xpath: !title', array(
      '!xpath' => $this->options['xpath_selector'],
      '!title' => $title
    ));
  }

  /**
   * Called to determine what to tell the clicksorter.
   */
  function click_sort($order) {
    if (isset($this->field_alias)) {

      // @todo: Figure out a better way to do this. ewww.
      if ($this->field == 'date') {
        $sort  = new views_xml_backend_handler_sort_date();
      }
      else if ($this->field == 'numeric') {
        $sort  = new views_xml_backend_handler_sort_numeric();
      }
      else {
        $sort  = new views_xml_backend_handler_sort();
      }

      // Re-use the field options as options for the sort handler.
      $options = $this->options + array('order' => $order);
      $sort->init($this->view, $options);
      $this->query->add_orderby($sort);
    }
  }
}
