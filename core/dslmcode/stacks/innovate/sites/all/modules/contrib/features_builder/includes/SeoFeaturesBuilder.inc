<?php

class SeoFeaturesBuilder extends FeaturesBuilderBase {

  protected $dependencies = array(
    'globalredirect',
    'metatag',
    'pathauto',
    'trailing_slash',
    'xmlsitemap',
    'xmlsitemap_custom',
    'xmlsitemap_engines',
    'xmlsitemap_menu',
    'xmlsitemap_node',
    'xmlsitemap_taxonomy',
    'xmlsitemap_user',
  );

  // Variables are included in bulk, we'll pluck these out afterwards.
  protected $exclude = array(
    'xmlsitemap_generated_last',
    'xmlsitemap_rebuild_needed',
    'xmlsitemap_regenerate_needed',
    'xmlsitemap_engines_submit_last',
  );

  public static function listFeatures() {
    return array('seo' => t('SEO'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {
    // Filter out dependencies which are not enabled.
    $dependencies = array();
    foreach ($this->dependencies as $dependency) {
      if (module_exists($dependency)) {
        $dependencies[] = $dependency;
      }
    }
    $this->setNamedComponents('dependencies', $dependencies);

    $this->setAllComponents('metatag');
    $this->setRegexComponents('variable', '/^globalredirect_settings$/');
    $this->setRegexComponents('variable', '/^pathauto_/');
    $this->setRegexComponents('variable', '/^trailing_slash/');
    $this->setRegexComponents('variable', '/^xmlsitemap_.*/');
    if (!empty($this->components['variable'])) {
      $this->components['variable'] = array_diff($this->components['variable'], $this->exclude);
    }
  }

}
