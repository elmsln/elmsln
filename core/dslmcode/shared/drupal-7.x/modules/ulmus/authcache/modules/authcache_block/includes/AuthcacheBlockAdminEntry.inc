<?php
/**
 * @file
 * Defines the block admin entry class.
 */

/**
 * Block admin entry class.
 */
class AuthcacheBlockAdminEntry {

  /**
   * Construct a new block admin entry.
   */
  public function __construct($block_id, $config, $defaults) {
    // Copy over defaults.
    foreach ($defaults as $key => $value) {
      $this->{$key} = $value;
    }

    // Specify group.
    $this->group = t('Blocks');

    // Add name, description, adminPath and clients properties.
    $blocks_by_id = static::blocksById();
    $block = $blocks_by_id[$block_id];

    $this->name = $block['info'];
    $this->description = t('Block in region %region', array('%region' => $block['region name']));
    $this->clients = isset($config['clients']) ? $config['clients'] : array();
    $this->adminPath = 'admin/structure/block/manage/' . $block['module'] . '/' . $block['delta'] . '/configure';
  }

  /**
   * Helper method: Return a list of blocks used in the default theme.
   */
  protected static function blocksById() {
    $blocks_by_id = &drupal_static(__CLASS__);

    if (!isset($blocks_by_id)) {
      // Figure out region.
      $default_theme = variable_get('theme_default');
      $regions = system_region_list($default_theme);
      foreach (_block_rehash($default_theme) as $block) {
        $block_id = "{$block['module']}-{$block['delta']}";
        $block['region name'] = (!empty($regions[$block['region']])) ? $regions[$block['region']] : '';
        $blocks_by_id[$block_id] = $block;
      }
    }

    return $blocks_by_id;
  }
}
