<?php
/**
 * @file
 * Defines AuthcacheP13nFragmentBuilder
 */

/**
 * Content builder for personalized content fragments.
 */
class AuthcacheP13nFragmentBuilder implements AuthcacheP13nContentBuilderInterface, AuthcacheP13nRequestValidatorInterface {
  /**
   * @var AuthcacheP13nFragment
   */
  protected $fragment;

  /**
   * @var AuthcacheP13nFragmentValidator
   */
  protected $validator;

  /**
   * @var AuthcacheP13nFragmentLoader
   */
  protected $loader;

  /**
   * @var AuthcacheP13nFragmentAccess
   */
  protected $access;

  /**
   * Construct new instance.
   *
   * @param AuthcacheP13nFragment $fragment
   *   The fragment object to use.
   * @param AuthcacheP13nFragmentValidator $validator
   *   (optional) The validator object.
   * @param AuthcacheP13nFragmentLoader $loader
   *   The loader object.
   * @param AuthcacheP13nFragmentAccess $access
   *   The access checker.
   */
  public function __construct($fragment, $validator, $loader, $access) {
    $this->fragment = $fragment;
    $this->validator = $validator;
    $this->loader = $loader;
    $this->access = $access;
  }

  /**
   * {@inheritdoc}
   */
  public function validate($req) {
    // Normalize request parameter.
    $param = empty($req['a']) ? array() : array($req['a'] => $req['a']);

    // Run validator.
    if ($this->validator) {
      $param = $this->validator->validate($param);
    }

    $req['a'] = $param;

    return $req;
  }

  /**
   * {@inheritdoc}
   */
  public function build($req, $context) {
    global $user;

    $params = $req['a'];

    // Run loader.
    if ($this->loader) {
      $params = $this->loader->load($params, $context);
    }

    $key = key($params);
    $subject = current($params);

    // Run access check.
    if ($this->access && !$this->access->check($user, $key, $subject, $context)) {
      throw new AuthcacheP13nRequestAccessDenied();
    }
    else {
      return $this->fragment->render($key, $subject, $context);
    }
  }
}
