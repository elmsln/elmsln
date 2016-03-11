<?php

/**
 * Build user details for provider
 */
class BuildUser {

  protected $userObject;
  public $mentoredUsers = [];
  public $lisSourceID;
  protected $p2user;

  /**
   * @global type $user
   */
  public function __construct() {
    global $user;
    $this->userObject = user_load($user->uid);
  }

  /**
   * This sets the LTI equivilant roles based on mappings.
   * @return array
   */
  protected function buildRoles() {
    $roles = $this->userObject->roles;
    $mapping = array_flip(variable_get('ltic_global_role_array'));
    $rtn = [];
    foreach (array_keys($roles) as $role) {
      if (isset($mapping[$role])) {
        $rtn[] = $mapping[$role];
      }
    }
    return $rtn;
  }

  /**
   * @return array
   */
  protected function getMappings() {
    return variable_get('ltic_user_attribute_mapping', []);
  }

  /**
   * @return array
   */
  public function getDetails() {
    $rtn = [
      'user_id' => $this->userObject->uid,
      'roles' => implode(',', $this->buildRoles()),
    ];
    if (!variable_get('ltic_tool_supress_ui_details', FALSE)) {
      $rtn = $this->setMappings($rtn);
      if (!variable_get('ltic_tool_supress_email', FALSE)) {
        $rtn['lis_person_contact_email_primary'] = $this->userObject->mail;
      }
    }
    //Call in hooks
    $this->addMentoredUsers();
    $rtn['role_scope_mentor'] = empty($this->mentoredUsers) ? '' : implode(',', $this->mentoredUsers);
    $this->addLISPersonSourcedid();
    $rtn['lis_person_sourcedid'] = $this->lisSourceID ? $this->lisSourceID : '';
    return $rtn;
  }

  /**
   * this grabs the profile 2 stuff if were using it
   */
  protected function setProfile2Details() {
    $profile = profile2_load_by_user($this->userObject);
    $this->p2user = reset($profile);
  }

  /**
   * @param array $rtn
   * @return array
   */
  protected function setMappings($rtn) {
    $mappings = $this->getMappings();
    $p2 = false;
    if (variable_get('ltic_user_attribute_entity_type', 'user:user') == 'profile2:main') {
      //we should use p2
      $p2 = true;
      $this->setProfile2Details();
    }

    $rtn['lis_person_name_family'] = $p2 ? $this->p2user->{$mappings['lis_person_name_family']}[LANGUAGE_NONE][0]['safe_value'] : $this->userObject->{$mappings['lis_person_name_family']}[LANGUAGE_NONE][0]['safe_value'];
    $rtn['lis_person_name_given'] = $p2 ? $this->p2user->{$mappings['lis_person_name_given']}[LANGUAGE_NONE][0]['safe_value'] : $this->userObject->{$mappings['lis_person_name_given']}[LANGUAGE_NONE][0]['safe_value'];
    $rtn['lis_person_name_full'] = '';
    $rtn['lis_person_sourcedid'] = '';
    return $rtn;
  }

  /**
   * Add a alter hook for $this->mentoredUsers.
   */
  protected function addMentoredUsers() {
    drupal_alter('lti_mentored_users', $this->mentoredUsers);
  }

  /**
   * Add a alter hook for $this->lisSourceID.
   */
  protected function addLISPersonSourcedid() {
    drupal_alter('lti_lis_person_sourcedid', $this->lisSourceID);
  }

}
