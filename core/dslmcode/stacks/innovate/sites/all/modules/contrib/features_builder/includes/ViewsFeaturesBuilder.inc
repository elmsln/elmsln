<?php

class ViewsFeaturesBuilder extends FeaturesBuilderBase {

  protected $variables = array(
    'views_devel_output',
    'views_devel_region',
    'views_exposed_filter_any_label',
    'views_localization_plugin',
    'views_no_javascript',
    'views_show_additional_queries',
    'views_skip_cache',
    'views_sql_signature',
  );

  public static function listFeatures() {
    return array('views' => t('Views'));
  }

  public function package() {
    return 'CTools';
  }

  protected function setComponents() {
    $this->setAllComponents('views_view');
    $this->setNamedComponents('variable', $this->variables);

    if (module_exists('admin_views')) {
      $this->setNamedComponents('dependencies', array('admin_views'));
    }
  }

}
