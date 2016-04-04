<?php

/**
 * @file
 * Contains a CER field plugin for referencing Profile2 entities. These references
 * are not actually fields at all, so this plugin is really more of a bridge to
 * trick CER into thinking that Profile2 is a reference field.
 */

class CerProfile2Field extends CerField implements CerEntityContainerInterface {

  protected $profileType;

  /**
   * @override CerField::__construct().
   */
  public function __construct(array $plugin) {
    $this->plugin = $plugin;
    list ($this->entityType, $this->bundle, $this->name) = explode(':', $plugin['identifier']);

    $info = entity_get_info($this->entityType);
    // These "fields" can only be instantiated on user accounts, which are
    // normally not bundleable. However, there could be a module in the wild
    // which makes accounts bundleable, so let's not be presumptuous here.
    $this->isBundleable = (boolean) $info['entity keys']['bundle'];
    $this->entityTypeLabel = $info['label'];
    $this->bundleLabel = $info['bundles'][$this->bundle]['label'];
    // An account can only have one profile of this type.
    $this->cardinality = 1;
    $this->fieldTypeLabel = t('Profile');

    // Load the Profile2 type information
    $this->profileType = profile2_get_types(subStr($this->name, 8));
    $this->label = $this->profileType->label;
  }

  /**
   * Implements CerField::getTargetType().
   */
  public function getTargetType() {
    // In effect, this "field" will "point to" Profile2 entities.
    return 'profile2';
  }

  /**
   * @override CerField::getTargetBundles().
   */
  public function getTargetBundles() {
    // This field can only "reference" one type of profile. There'll be
    // a separate instance of this plugin for each Profile2 type.
    return (array) $this->profileType->type;
  }

  /**
   * Implements CerEntityContainerInterface::createInnerEntity().
   */
  public function createInnerEntity(EntityDrupalWrapper $owner) {
    $init = array(
      'user' => $owner->value(),
      'type' => $this->profileType,
    );

    // Create a blank profile for this user, and save it. The "reference" is implied
    // by the existence of the profile.
    $profile = profile2_create($init);
    $profile->save();

    return $profile;
  }

}
