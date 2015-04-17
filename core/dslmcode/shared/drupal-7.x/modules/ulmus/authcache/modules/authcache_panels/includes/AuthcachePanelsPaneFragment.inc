<?php
/**
 * @file
 * Defines personalization fragment for panel pane.
 */

/**
 * Personalization fragment for panel pane.
 */
class AuthcachePanelsPaneFragment implements AuthcacheP13nFragmentInterface, AuthcacheP13nFragmentAccessInterface {
  /**
   * {@inheritdoc}
   *
   * @see panels_renderer_standard::prepare_panes()
   */
  public function check($account, $pane_id, $display, $context) {
    $pane = $display->content[$pane_id];

    return panels_pane_access($pane, $display);
  }

  /**
   * {@inheritdoc}
   *
   * @see panels_renderer_standard::render_pane()
   */
  public function render($pane_id, $display, $context) {
    $result = '';

    $renderer = panels_get_renderer_handler($display->renderer, $display);
    if ($renderer) {
      $pane = $display->content[$pane_id];

      if ($pane->shown) {
        $content = $renderer->render_pane_content($pane);
        $result = render($content->content);
      }
    }

    return $result;
  }
}
