<?php
/**
 * @file
 * Helper functions that utilize Canvas' User APIs
 *
 * See @link https://canvas.instructure.com/doc/api/users.html @endlink
 *
 */

/**
 * {@inheritdoc}
 */
class CanvasUsers extends Canvas{

  function __construct(){
    parent::__construct();
  }

  /**
   * Create a Canvas user
   *
   * See @link https://canvas.instructure.com/doc/api/users.html#method.users.create @endlink
   *
   * Example:
   *
   *    $canvas_api = canvas_api('users');
   *    $canvas_api->params = array(
   *       'user' => array(
   *          'name' => 'John Doe',
   *       ),
   *       'pseudonym' => array(
   *          'unique_id' => 'jdoe',
   *          'sis_user_id' => 'DOE123',
   *        ),
   *    );
   *    $user = $canvas_api->createUser(1);
   *
   * @param $rootAccountID
   *  The Canvas account this user should be created under
   * @return array
   */
  public function createUser($rootAccountID){
    $this->path = "accounts/$rootAccountID/users";
    return $this->post();
  }

  /**
   * Get a Canvas user
   *
   * See @link https://canvas.instructure.com/doc/api/users.html#method.users.api_show @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('users');
   *    $sisUserID = 'sis_user_id:DOE123';
   *    $user = $canvas_api->getUser($sisUserID);
   *
   * @param $userID
   * @return array
   */
  public function getUser($userID){
    $this->path = "users/$userID";
    return $this->get();
  }

  /**
   * Edit a Canvas user
   *
   * See @link https://canvas.instructure.com/doc/api/users.html#method.users.update @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('users');
   *    $userID = 2811;
   *    $canvas_api->params = array(
   *        'user' => array(
   *            'name' => 'Johnathan Doe',
   *        ),
   *    );
   *    $user = $canvas_api->editUser($userID);
   *
   * @param $userID
   * @return array
   */
  public function editUser($userID){
    $this->path = "users/$userID";
    return $this->put();
  }

  /**
   * Delete a Canvas user
   *
   * @TODO This API does not appear to exist.
   *
   */

  /**
   * List all Canvas Users.
   *
   * See @link https://canvas.instructure.com/doc/api/users.html#method.users.index @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('users');
   *    $canvas_api->params['search_term'] = 'baz'; //(Optional) limit to names with 'baz'
   *    $users = $canvas_api->users(1);
   *
   * @param string $rootAccountID
   * @return array
   *   An array of Users
   */
  public function users($rootAccountID){
    $this->path = "accounts/$rootAccountID/users";
    return $this->get();
  }



}
