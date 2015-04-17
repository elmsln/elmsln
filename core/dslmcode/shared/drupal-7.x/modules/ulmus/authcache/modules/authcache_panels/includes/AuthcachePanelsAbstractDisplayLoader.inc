<?php
/**
 * @file
 * Defines personalization fragment for panel pane.
 */

/**
 * Personalization fragment for panel pane.
 */
abstract class AuthcachePanelsAbstractDisplayLoader implements AuthcacheP13nFragmentLoaderInterface {
  protected $paneId;

  /**
   * Construct new display loader.
   */
  public function __construct($pane_id) {
    $this->paneId = $pane_id;
  }

  /**
   * Load the display object.
   */
  protected abstract function loadDisplay();

  /**
   * {@inheritdoc}
   */
  public function load($params, $context) {
    ctools_include('plugins', 'panels');
    ctools_include('content');

    $display = $this->loadDisplay();

    if (!$display) {
      throw new AuthcacheP13nRequestNotFound();
    }

    if (!isset($display->content[$this->paneId])) {
      throw new AuthcacheP13nRequestNotFound();
    }

    // Assign page manager context and arguments prepared by a context
    // provider.
    $display->context = array();
    if (!empty($context['panels']['context'])) {
      $display->context = $context['panels']['context'];
    }

    $display->args = array();
    if (!empty($context['panels']['arguments'])) {
      $display->args = $context['panels']['arguments'];
    }

    return array(
      $this->paneId => $display,
    );
  }
}
