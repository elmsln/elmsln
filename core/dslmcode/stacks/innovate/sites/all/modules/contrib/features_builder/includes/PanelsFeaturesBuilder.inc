<?php

class PanelsFeaturesBuilder extends FeaturesBuilderBase {

  public static function listFeatures() {
    return array('panels' => t('Panels'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'CTools';
  }

  protected function setComponents() {
    // Standard Panels.
    if (module_exists('panels')) {
      $this->setNamedComponents('dependencies', array('panels'));
      $this->setAllComponents('panels_renderer_pipeline');
    }

    // Page Manager.
    if (module_exists('page_manager')) {
      $this->setNamedComponents('dependencies', array('page_manager'));
      $this->setAllComponents('page_manager_handlers');
      $this->setAllComponents('page_manager_pages');
      $this->setNamedComponents('variable', array('default_page_manager_handlers', 'default_page_manager_pages'));
      $this->setRegexComponents('variable', '/page_manager_[a-z0-9_]+_disabled/');
    }

    // Panelizer.
    if (module_exists('panelizer')) {
      $this->setNamedComponents('dependencies', array('panelizer'));
      $this->setAllComponents('panelizer_defaults');
      $this->setRegexComponents('variable', '/panelizer_.+/');
    }

    // Panels everywhere.
    if (module_exists('panels_everywhere')) {
      $this->setRegexComponents('variable', '/panels_everywhere_.+/');
      $this->setNamedComponents('dependencies', array('panels_everywhere'));
    }

    // PM Existing Pages.
    if (module_exists('pm_existing_pages')) {
      $this->setNamedComponents('dependencies', array('pm_existing_pages'));
      $this->setAllComponents('page_manager_existing_pages');
      $this->setRegexComponents('variable', '/pm_existing_pages.+/');
    }

    // Custom content panes.
    $this->setAllComponents('ctools_custom_content');
    if (!empty($this->components['ctools_custom_content'])) {
      $this->setNamedComponents('dependencies', array('ctools_custom_content'));
    }

    // Mini panels.
    $this->setAllComponents('panels_mini');
    if (!empty($this->components['panels_mini'])) {
      $this->setNamedComponents('dependencies', array('panels_mini'));
    }

  }

}
