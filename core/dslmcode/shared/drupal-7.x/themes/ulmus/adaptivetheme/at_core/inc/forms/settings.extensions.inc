<?php

/**
 * @file
 * Generate settings for the Extensions form.
 */
function at_core_extensions_form(&$form) {
  // Enable Extensions
  $form['at-settings']['extend'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extensions'),
    '#description' => t('<h3>Enable Additional Features</h3><p>Extensions include many extras for configuring and styling your site. Enabled extensions will appear in new vertical tabs below the main setting. Extensions can be enabled or disabled individually, so you only load what you need. Disabling the global setting will globally disable most extensions, but not enable them.</p><p>Once you have enabled an extension you will need to configure its settings, then save the theme settings again (to save its configuration).</p>'),
  );

  // Enable extensions, the extension settings are hidden by default to ease the
  // the UI clutter, this setting is also used as a global enable/disable for any
  // extension in other logical operations.
  $form['at-settings']['extend']['enable_extensions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable extensions <small>(global setting)</small>'),
    '#default_value' => at_get_setting('enable_extensions'),
  );

  $form['at-settings']['extend']['enable'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extensions'),
    '#states' => array(
      'visible' => array('input[name="enable_extensions"]' => array('checked' => TRUE)),
    ),
  );

  // Fonts
  $form['at-settings']['extend']['enable']['enable_font_settings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fonts'),
    '#default_value' => at_get_setting('enable_font_settings'),
    '#description' => t('Apply fonts to site elements (page, titles, headings, menus and custom selectors). Supports websafe, custom and Google fonts, and <a href="!link" target="_blank">@font-your-face</a> integration.', array('!link' => 'http://drupal.org/project/fontyourface')),
  );

  // Title styles
  $form['at-settings']['extend']['enable']['enable_heading_settings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Title styles'),
    '#default_value' => at_get_setting('enable_heading_settings'),
    '#description' => t('Fine grain control over case, weight, alignment and CSS3 text shadows for page title, node, comment and block titles.'),
  );

  // Image alignment and captions
  $form['at-settings']['extend']['enable']['enable_image_settings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Image alignment and captions'),
    '#default_value' => at_get_setting('enable_image_settings'),
    '#description' => t('Set default image alignment, image captions and teaser image view.'),
  );

  // Apple touch icons
  $form['at-settings']['extend']['enable']['enable_apple_touch_icons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apple touch icons'),
    '#description' => t('Check this setting if you want to use touch icons for iOS, Android and Nokia devices.'),
    '#default_value' => at_get_setting('enable_apple_touch_icons'),
  );

  // Unset CSS
  $form['at-settings']['extend']['enable']['enable_exclude_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unset CSS Files'),
    '#description' => t('Options to unset (exclude) CSS files from loading in your theme - includes settings for Core modules, CSS added by Libaries and your own declared exclusions (see your themes info file under "Stylesheets").'),
    '#default_value' => at_get_setting('enable_exclude_css'),
  );

  // Custom CSS
  $form['at-settings']['extend']['enable']['enable_custom_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom CSS'),
    '#description' => t('Enter custom CSS rules for minor adjustment to your theme. Useful if you do not want to build a sub-theme and need modifications to survive theme upgrades if required.'),
    '#default_value' => at_get_setting('enable_custom_css'),
  );

  // Mobile regions and blocks
  $form['at-settings']['extend']['enable']['enable_context_regions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Mobile Regions and Blocks'),
    '#description' => t('Unset regions or move blocks to another region in mobile devices. Requires either <a href="!browscap_module" target="_blank">Browscap</a> or <a href="!mobiledetect_module" target="_blank">Mobile Detect</a> for mobile device detection.', array('!browscap_module' => 'http://drupal.org/project/browscap', '!mobiledetect_module' => 'http://drupal.org/project/mobile_detect')),
    '#default_value' => at_get_setting('enable_context_regions'),
  );

  // Menu Toggle
  $form['at-settings']['extend']['enable']['enable_menu_toggle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Mobile Menu Toggle'),
    '#description' => t('Collapse the Main menu (or menu block in Menu Bar region) into a clickable link/button. This is a new feature and may not work perfectly with older sub-themes.'),
    '#default_value' => at_get_setting('enable_menu_toggle'),
  );

  // Float Region blocks
  $form['at-settings']['extend']['enable']['enable_float_region_blocks'] = array(
    '#type' => 'checkbox',
    '#title' => t('Float Region blocks'),
    '#description' => t('Float blocks in any region - this allows blocks to line up horizontally within a region, similar to a CSS grid or columns.'),
    '#default_value' => at_get_setting('enable_float_region_blocks'),
  );

  // Markup overrides
  $form['at-settings']['extend']['enable']['enable_markup_overides'] = array(
    '#type' => 'checkbox',
    '#title' => t('Markup overrides'),
    '#description' => t('Many additional options for adding, removing, hiding and changing site elements and markup - includes:
      <ul>
        <li>Set the gutter width</li>
        <li>Use page--full-width-wrappers.tpl.php for 100% width header and footer designs</li>
        <li>Enable page--[content-type].tpl.php suggestions</li>
        <li>Wrap menu item text in SPAN tags</li>
        <li>Breadcrumb Settings - hide, hide the home link, configure seperator, append the page title</li>
        <li>Login Block - hide links, hide OpenID links, horizontal login block</li>
        <li>Remove the frontpage title</li>
        <li>Do not display the Main content block on the front page</li>
        <li>Remove RSS feed icons</li>
        <li>Hide comment titles</li>
        <li>Remove menu link titles (tool tips)</li>
        <li>Accessibility settings - set the skip navigation target ID, use extra fieldsets in the advanced search form</li>
        <li>Add rel=author to user names</li>
        <li>Add or remove CSS classes for pages, nodes, blocks, comments, menus and item lists</li>
      </ul>
      '),
    '#default_value' => at_get_setting('enable_markup_overides'),
  );
}
