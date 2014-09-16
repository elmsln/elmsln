<?php

/**
 * A handler for achievement images.
 *
 */
abstract class achievements_views_handler_field_achievements_image extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['image_style'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    if (module_exists('image')) {
      $styles = image_styles();
      $style_options = array('' => t('Default'));
      foreach ($styles as $style) {
        $style_options[$style['name']] = $style['name'];
      }

      $form['image_style'] = array(
        '#title' => t('Image style'),
        '#description' => t('Using <em>Default</em> will use the site-wide image style for user pictures set in the <a href="!account-settings">Account settings</a>.', array('!account-settings' => url('admin/config/people/accounts', array('fragment' => 'edit-personalization')))),
        '#type' => 'select',
        '#options' => $style_options,
        '#default_value' => $this->options['image_style'],
      );
    }
  }

  function query() {
    $this->ensure_my_table();
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
    $this->field_alias = $this->query->add_field($this->table_alias, 'achievement_id', NULL, $params);

    $this->add_additional_fields();
  }

  function render_image_style($filepath) {
      if ($this->options['image_style'] && module_exists('image')) {
          $public_path = variable_get('file_public_path', 'sites/default/files');
          $private_path = variable_get('file_public_path', '');

          if (!empty($public_path) && preg_match('#^/?' . $public_path . '/(.+)$#i', $filepath, $match)) {
              $image_filepath = 'public://' . $match[1];
          } else if (!empty($private_path) && preg_match('#^/?' . $private_path . '/(.+)$#i', $filepath, $match)) {
              $image_filepath = 'private://' . $match[1];
          }

          if (!empty($image_filepath) && file_valid_uri($image_filepath)) {
              return theme('image_style', array('style_name' => $this->options['image_style'], 'path' => $image_filepath));
          }
      }
  }

  function render($values) {
      $field_name = $this->table_alias . '_achievement_id';
      $achievement_id = $values->$field_name;
      if (empty($achievement_id))
        return '';

      if (!($achievement = achievements_views_achievement_load($achievement_id))) {
        return '';
      }

      if (!isset($achievement['images'])) {
        return '';
      }

      if (!($filepath = $achievement['images'][$this->image_type()]))
        return '';

      if ($image_style = $this->render_image_style($filepath)) {
        return $image_style;
      }

      return theme('image', array('path' => $filepath));
  }
}

class achievements_views_handler_field_achievements_locked_image extends achievements_views_handler_field_achievements_image {
    function image_type() {
        return 'locked'; 
    }
}

class achievements_views_handler_field_achievements_unlocked_image extends achievements_views_handler_field_achievements_image {
    function image_type() {
        return 'unlocked'; 
    }
}
