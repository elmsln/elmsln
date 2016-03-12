<?php

class MessageFeaturesBuilder extends EntityFeaturesBuilder {

  protected $dependencies = array(
    'message',
    'entity',
    'strongarm',
  );
  protected $variables = array(
  );

  public static function listFeatures() {
    $features = array();

    if (!module_exists('message')) {
      return $features;
    }

    $messages = message_type_load();
    // Provides a feature module for each message.
    foreach ($messages as $name => $message) {
      $features["message_$name"] = $message->description;
    }
    return $features;
  }
  
  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Messages';
  }

  protected function setComponents() {
    $message_name = substr($this->name, strlen('message_'));

    $this->variables[] = 'field_bundle_settings_message__' . $message_name;

    $this->setNamedComponents('variable', $this->variables);
    $this->setNamedComponents('message_type', array($message_name));
    $this->setFields('message', $message_name);
    $this->setNamedComponents('dependencies', array_filter($this->dependencies));
  }

}
