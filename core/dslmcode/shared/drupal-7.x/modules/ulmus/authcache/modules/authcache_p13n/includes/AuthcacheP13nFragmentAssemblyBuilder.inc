<?php
/**
 * @file
 * Defines AuthcacheP13nFragmentAssemblyBuilder.
 */

/**
 * Content builder for personalized fragment assemblies.
 */
class AuthcacheP13nFragmentAssemblyBuilder implements AuthcacheP13nContentBuilderInterface, AuthcacheP13nRequestValidatorInterface {
  /**
   * A list of partial fragments indexed by parameter name.
   */
  protected $partials;

  /**
   * Construct new instance.
   *
   * @param array $partials
   *   List of key-value pairs where the key is a partial-id and the value a
   *   record with the following entries:
   *   - renderer: A AuthcacheP13nFragment instance
   *   - validator: (optional) an AuthcacheP13nFragmentValidator instance
   *   - loader: (optional) an AuthcacheP13nFragmentLoader instance
   *   - access: (optional) an AuthcacheP13nFragmentAccess instance
   */
  public function __construct($partials) {
    $this->partials = $partials;
  }

  /**
   * {@inheritdoc}
   */
  public function validate($req) {
    // Normalize request parameters.
    foreach ($req['a'] as $paramname => $params) {
      $params = empty($params) ? array() : static::mapAssoc($params);

      // Run validators.
      if (!empty($this->partials[$paramname]['validator'])) {
        $params = $this->partials[$paramname]['validator']->validate($params);
      }

      $req['a'][$paramname] = $params;
    }

    return $req;
  }

  /**
   * {@inheritdoc}
   */
  public function build($req, $context) {
    global $user;

    $result = array();

    foreach ($req['a'] as $paramname => $params) {
      // Skip when there is no handler present.
      if (empty($this->partials[$paramname]['renderer'])) {
        continue;
      }

      $partial = $this->partials[$paramname];

      // Run loader.
      if (!empty($partial['loader'])) {
        $params = $partial['loader']->load($params, $context);
      }

      foreach ($params as $key => $subject) {
        // Run access check.
        if (!empty($partial['access']) && !$partial['access']->check($user, $key, $subject, $context)) {
          throw new AuthcacheP13nRequestAccessDenied();
        }
        else {
          $result[$paramname][$key] = $partial['renderer']->render($key, $subject, $context);
        }
      }
    }

    return $result;
  }

  /**
   * Private helper method implementing drupal_map_assoc().
   */
  protected static function mapAssoc($array) {
    // array_combine() fails with empty arrays:
    // http://bugs.php.net/bug.php?id=34857.
    return !empty($array) ? array_combine($array, $array) : array();
  }
}
