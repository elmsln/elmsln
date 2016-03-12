<?php

class MediaFeaturesBuilder extends EntityFeaturesBuilder {

  protected $dependencies = array(
    'ctools',
    'features',
    'filter',
    'image',
    'strongarm',
  );
  protected $variables = array(
    'file_default_scheme',
    'filter_fallback_format',
    'image_jpeg_quality',
    'image_toolkit',
  );

  public static function listFeatures() {
    return array('media' => t('Media'));
  }
  
  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {
    $this->setAllComponents('filter');
    $this->setAllComponents('image');
    $this->setNamedComponents('variable', $this->variables);
    $this->setAllComponents('wysiwyg');

    // Add in modules utilized by any of the filters.
    if (!empty($this->components['filter'])) {
      foreach ($this->components['filter'] as $format_id => $name) {
        if ($format = filter_format_load($format_id)) {
          $filters = filter_list_format($format->format);
          foreach ($filters as $filter) {
            $this->dependencies[] = $filter->module;
          }
        }
      }
    }

    if (!empty($this->components['wysiwyg'])) {
      $this->dependencies[] = 'wysiwyg';
    }

    if (module_exists('flexslider')) {
      $this->dependencies[] = 'flexslider';
      $this->setAllComponents('flexslider_optionset');
    }

    if (module_exists('imce')) {
      $this->dependencies[] = 'imce';
      $this->setRegexComponents('variable', '/imce_.+/');
    }

    if (module_exists('imce_mkdir')) {
      $this->dependencies[] = 'imce_mkdir';
    }

    if (module_exists('imce_wysiwyg')) {
      $this->dependencies[] = 'imce_wysiwyg';
    }

    if (module_exists('linkit')) {
      $this->dependencies[] = 'linkit';
      $this->setAllComponents('linkit_profiles');
    }

    if (module_exists('video_embed_field')) {
      $this->dependencies[] = 'video_embed_field';
      $this->setAllComponents('vef_video_styles');
    }

    if (module_exists('ckeditor')) {
      $this->dependencies[] = 'ckeditor';
      $this->setAllComponents('ckeditor_profile');
    }

    $this->setNamedComponents('dependencies', array_filter($this->dependencies));

    if (module_exists('file_entity')) {
      $this->setFileEntityComponents();
    }
  }

  /**
   * Add file_entity module configuration.
   */
  protected function setFileEntityComponents() {
    // Only applicable to 7.x-2.x release of file_entity.
    $info = system_get_info('module', 'file_entity');
    list($major, $minor) = explode('-', $info['version']);
    if ($major != '7.x' || floor((float) $minor) != 2) {
      return;
    }

    $dependencies[] = 'file_entity';
    $this->setAllComponents('file_display');
    $this->setAllComponents('file_entity');
    $this->setAllComponents('file_type');

    $this->setRegexComponents('variable', '/^file_entity_.+/');

    if ($bundles = field_info_bundles('file')) {
      $dependencies[] = $this->prefix . '_fields';
      foreach (array_keys($bundles) as $bundle) {
        $this->setFields('file', $bundle);
      }
    }

    $this->setNamedComponents('dependencies', $dependencies);
  }

}
