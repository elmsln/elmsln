<?php

class UserFeaturesBuilder extends EntityFeaturesBuilder {

  protected $variables = array('anonymous');

  /**
   * {@inheritdoc}
   */
  public static function listFeatures() {
    return array('users' => t('Users'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  /**
   * {@inheritdoc}
   */
  protected function setComponents() {
    $this->setAllComponents('user_role');
    $this->setAllComponents('user_permission');
    $this->setFields('user', 'user');
    $this->setNamedComponents('variable', $this->variables);
    $this->setRegexComponents('variable', '/^user_.*/');

  }

}
