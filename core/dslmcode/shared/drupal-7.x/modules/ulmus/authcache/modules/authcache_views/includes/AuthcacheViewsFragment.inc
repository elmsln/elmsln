<?php
/**
 * @file
 * Defines personalization fragment for views
 */

/**
 * Personalization fragment for rendered views.
 */
class AuthcacheViewsFragment implements AuthcacheP13nFragmentInterface, AuthcacheP13nFragmentLoaderInterface, AuthcacheP13nFragmentAccessInterface {
  protected $viewName;
  protected $displayName;

  /**
   * Construct new view fragment.
   *
   * @param string $view_name
   *   The view name.
   * @param string $display_name
   *   The name of the display of the specified view.
   */
  public function __construct($view_name, $display_name) {
    $this->viewName = $view_name;
    $this->displayName = $display_name;
  }

  /**
   * {@inheritdoc}
   */
  public function load($params, $context) {
    $view = views_get_view($this->viewName);

    if (!$view) {
      throw new AuthcacheP13nRequestNotFound();
    }

    if (!$view->set_display($this->displayName)) {
      throw new AuthcacheP13nRequestNotFound();
    }

    if (!empty($context['views arguments'])) {
      $view->set_arguments($context['views arguments']);
    }

    return array(
      $this->viewName => $view,
    );
  }

  /**
   * {@inheritdoc}
   */
  public function check($account, $view_name, $view, $context) {
    return $view->access(array($view->current_display), $account);
  }

  /**
   * {@inheritdoc}
   *
   * @see views_embed_view()
   */
  public function render($view_name, $view, $context) {
    return $view->preview();
  }
}
