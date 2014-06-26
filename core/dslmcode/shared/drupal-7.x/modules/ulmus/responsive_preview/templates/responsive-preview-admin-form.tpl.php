<?php

/**
 * @file
 * Default theme implementation to configure responsive preview devices.
 *
 * Available variables:
 * - $devices: An array of device details keyed by device name.
 * - $form_submit: Form submit button.
 *
 * Each $data in $block_listing[$region] contains:
 * - $data->region_title: Region title for the listed block.
 *
 * @see template_preprocess_responsive_preview_admin_form()
 * @see theme_responsive_preview_admin_form()
 *
 * @ingroup themeable
 */
?>
<?php
  // // Add table javascript.
  // drupal_add_js('misc/tableheader.js');
  // foreach ($block_regions as $region => $title) {
  //   drupal_add_tabledrag('blocks', 'match', 'sibling', 'block-region-select', 'block-region-' . $region, NULL, FALSE);
  //   drupal_add_tabledrag('blocks', 'order', 'sibling', 'block-weight', 'block-weight-' . $region);
  // }
?>
<?php if (empty($devices)) : ?>
<?php print t('No devices to display'); ?>
<?php else : ?>
  <table id="responsive-preview-devices-list" class="sticky-enabled">
    <thead>
      <tr>
        <th><?php print t('Name'); ?></th>
        <th><?php print t('Show in list'); ?></th>
        <th><?php print t('Dimensions'); ?></th>
        <th><?php print t('Weight'); ?></th>
        <th colspan="2"><?php print t('Operations'); ?></th>
      </tr>
    </thead>
    <tbody>
      <?php foreach ($devices as $device): ?>
        <tr class="draggable">
          <td><?php print $device['label']; ?></td>
          <td><?php print $device['status']; ?></td>
          <td><?php print $device['dimensions']; ?></td>
          <td><?php print $device['weight']; ?></td>
          <td><?php print $device['edit_link']; ?></td>
          <td><?php print $device['delete_link']; ?></td>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>

  <?php print $form_submit; ?>
<?php endif; ?>
