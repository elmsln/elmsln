<?php

/*
 * Load settings
 * See if any matches
 * swap out for set variables
 */

class ParseVars {

  /**
   * @var array
   */
  protected $params;

  /**
   * @global stdObject $user
   * @param array $params
   */
  public function __construct(array $params) {
    $this->params = $params;
    global $user;
    $this->loadswaps['User.id'] = $user->uid;
    $this->loadswaps['User.username'] = $user->name;
    $this->loadswaps['ToolConsumerProfile.url'] = url(variable_get('ltic_outcomes_launch_path', 'ltic_outcomes') . '/lp', ['absolute' => TRUE]);
  }

  /**
   * @return array
   */
  public function parseParams() {
    foreach ($this->params as $key => $value) {
      foreach ($this->loadswaps as $key1 => $value1) {
        if ($value == '$' . $key1) {
          $this->params[$key] = $value1;
        }
      }
    }
    return $this->params;
  }

}
