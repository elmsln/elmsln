<?php
/**
 * @file
 * Defines fragment for blocks.
 */

/**
 * Fragment handler for blocks.
 *
 * @see block.module
 */
class AuthcacheBlockFragment implements AuthcacheP13nFragmentInterface, AuthcacheP13nFragmentLoaderInterface {
  protected $blockId;
  protected $module;
  protected $delta;

  /**
   * Construct new personalized block fragment.
   */
  public function __construct($block_id, $module, $delta) {
    $this->blockId = $block_id;
    $this->module = $module;
    $this->delta = $delta;
  }

  /**
   * {@inheritdoc}
   */
  public function load($keys, $context) {
    $block = block_load($this->module, $this->delta);

    if (!$block) {
      throw new AuthcacheP13nRequestNotFound();
    }

    return array(
      $this->blockId => $block,
    );
  }

  /**
   * {@inheritdoc}
   */
  public function render($block_id, $block, $context) {
    $build = _block_get_renderable_array(_block_render_blocks(array(
      $block_id => $block,
    )));

    return render($build);
  }
}
