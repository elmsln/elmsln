<?php

class elms_media_browser_views_handler_field_image extends views_handler_field {
  public $filemime;
  public $fid;

  /**
   * Called to add the field to a query.
   */
  function query($use_groupby = FALSE) {
    parent::query($use_groupby);
    $this->filemime = $this->query->add_field($this->table_alias, 'filemime');
    $this->fid = $this->query->add_field($this->table_alias, 'fid');
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['image_style'] = array('default' => 'thumbnail');
    $options['link_to'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Display.
    $styles = image_style_options();
    $form['image_style'] = array(
      '#type' => 'select',
      '#title' => t('Image style'),
      '#options' => $styles,
      '#default_value' => $this->options['image_style'],
    );

    // Link.
    $styles = array('' => '<no link>', '_original' => '<original>') + image_style_options(FALSE);
    $form['link_to'] = array(
      '#type' => 'select',
      '#title' => t('Link to'),
      '#options' => $styles,
      '#default_value' => $this->options['link_to'],
    );
  }

  function render($values) {
    $path = $this->get_value($values);
    $style_name = $this->options['image_style'];
    $vars = compact('path', 'style_name');
    $image = '';

    // With image style.
    if (strpos($values->{$this->filemime}, 'image/') === 0) {
      if ($style_name) {
        $image = theme('image_style', $vars);
      }
      // Original.
      else {
        $image = theme('image', $vars);
      }
    }
    elseif ($file = file_load($values->{$this->fid})) {
      $image = theme('file_icon', array('file' => $file));
    }

    // Link image somewhere.
    $link_to = $this->options['link_to'];
    if ($link_to) {
      $uri = $path;

      // With image style.
      if ($link_to != '_original') {
        $uri = image_style_path($link_to, $path);
      }

      $uri = file_create_url($uri);
      $image = l($image, $uri, array('html' => TRUE));
    }

    return $image;
  }

}
