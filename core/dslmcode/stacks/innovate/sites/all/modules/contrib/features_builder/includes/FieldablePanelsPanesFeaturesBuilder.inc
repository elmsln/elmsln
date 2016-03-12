<?php

class FieldablePanelsPanesFeaturesBuilder extends EntityFeaturesBuilder {

  public static function listFeatures() {
    return array('fieldable_panels_panes' => t('Fieldable Panels Panes'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'CTools';
  }

  protected function setComponents() {

    $this->setAllComponents('fieldable_panels_pane_type');

    if (empty($this->components['fieldable_panels_pane_type'])) {
      return;
    }

    $this->setNamedComponents('dependencies', array('fieldable_panels_panes'));

    foreach ($this->components['fieldable_panels_pane_type'] as $bundle => $bundle_label) {
      $this->setFields('fieldable_panels_pane', $bundle);
    }

    $dependencies = array();
    if (field_info_bundles('fieldable_panels_pane')) {
      $dependencies[] = $this->prefix . '_fields';
    }
  }
}
