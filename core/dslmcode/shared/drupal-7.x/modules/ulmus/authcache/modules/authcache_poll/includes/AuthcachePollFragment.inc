<?php
/**
 * @file
 * Defines personalized fragment for polls.
 */

/**
 * Personalized fragment handler for polls.
 */
class AuthcachePollFragment implements AuthcacheP13nFragmentInterface, AuthcacheP13nFragmentLoaderInterface, AuthcacheP13nFragmentAccessInterface {
  protected $forceResults;

  /**
   * Construct new poll fragment.
   *
   * @param bool $force_results
   *   Specify true if the result graph should be returned regardless of
   *   whether the user has voted or not.
   */
  public function __construct($force_results = FALSE) {
    $this->forceResults = $force_results;
  }

  /**
   * Load requested nodes.
   */
  public function load($nids, $context) {
    return node_load_multiple($nids);
  }

  /**
   * Check whether the user has access to the given fragment.
   */
  public function check($account, $key, $subject, $context) {
    return user_access('access content', $account);
  }

  /**
   * Get poll results/form for user.
   *
   * @see poll.module
   */
  public function render($nid, $node, $context) {
    if ($this->forceResults) {
      $node->show_results = TRUE;
    }

    $build = node_view($node);
    if (isset($build['poll_view_voting'])) {
      return render($build['poll_view_voting']);
    }
    elseif (isset($build['poll_view_results'])) {
      return render($build['poll_view_results']);
    }
  }
}
