<?php
/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function corolla_form_system_theme_settings_alter(&$form, &$form_state) {

  // Include a hidden form field with the current release information
  $form['at-release'] = array(
    '#type' => 'hidden',
    '#default_value' => '7.x-3.x',
  );

  // Tell the submit function its safe to run the color inc generator
  // if running on AT Core 7.x-3.x
  $form['at-color'] = array(
    '#type' => 'hidden',
    '#default_value' => TRUE,
  );

  $enable_extensions = isset($form_state['values']['enable_extensions']);
  if (($enable_extensions && $form_state['values']['enable_extensions'] == 1) || (!$enable_extensions && $form['at-settings']['extend']['enable_extensions']['#default_value'] == 1)) {

    // Remove option to use full width wrappers
    $form['at']['modify-output']['design']['page_full_width_wrappers'] = array(
      '#access' => FALSE,
      '#default_value' => 0,
    );

    $form['at']['corners'] = array(
      '#type' => 'fieldset',
      '#title' => t('Rounded corners'),
      '#description' => t('<h3>Rounded Corners</h3><p>Rounded corners are implimented using CSS and only work in modern compliant browsers. You can set the radius for both the main content and main menu tabs.</p>'),
    );
    $form['at']['corners']['content_corner_radius'] = array(
      '#type' => 'select',
      '#title' => t('Main content radius'),
      '#default_value' => theme_get_setting('content_corner_radius'),
      '#description' => t('Change the corner radius for the main content area.'),
      '#options' => array(
        'rc-0' => t('none'),
        'rc-4' => t('4px'),
        'rc-6' => t('6px'),
        'rc-8' => t('8px'),
        'rc-10' => t('10px'),
        'rc-12' => t('12px'),
      ),
    );
    $form['at']['corners']['tabs_corner_radius'] = array(
      '#type' => 'select',
      '#title' => t('Menu tabs radius'),
      '#default_value' => theme_get_setting('tabs_corner_radius'),
      '#description' => t('Change the corner radius for the main menu tabs.'),
      '#options' => array(
        'rct-0' => t('none'),
        'rct-4' => t('4px'),
        'rct-6' => t('6px'),
        'rct-8' => t('8px'),
        'rct-10' => t('10px'),
        'rct-12' => t('12px'),
      ),
    );
    $form['at']['pagestyles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Box Shadows and Textures'),
      '#description' => t('<h3>Shadows and Textures</h3><p>The box shadows are implimented using CSS and only work in modern compliant browsers. The textures are small, semi-transparent images that tile to fill the entire background.</p>'),
    );
    $form['at']['pagestyles']['shadows'] = array(
      '#type' => 'fieldset',
      '#title' => t('Box Shadows'),
      '#description' => t('<h3>Box Shadows</h3><p>Box shadows (a drop shadow/glow effect) apply to the main content column and work only in CSS3 compliant browsers such as Firefox, Safari and Chrome.</p>'),
    );
    $form['at']['pagestyles']['shadows']['box_shadows'] = array(
      '#type' => 'radios',
      '#title' => t('<strong>Apply a box shadow to the main content column</strong>'),
      '#default_value' => theme_get_setting('box_shadows'),
      '#options' => array(
        'bs-n' => t('None'),
        'bs-l' => t('Box shadow - light'),
        'bs-d' => t('Box shadow - dark'),
      ),
    );
    $form['at']['pagestyles']['textures'] = array(
      '#type' => 'fieldset',
      '#title' => t('Textures'),
      '#description' => t('<h3>Body Textures</h3><p>This setting adds a texture over the main background color - the darker the background the more these stand out, on light backgrounds the effect is subtle.</p>'),
    );
    $form['at']['pagestyles']['textures']['body_background'] = array(
      '#type' => 'select',
      '#title' => t('Select texture'),
      '#default_value' => theme_get_setting('body_background'),
      '#options' => array(
        'bb-n'  => t('None'),
        'bb-h'  => t('Hatch'),
        'bb-vl' => t('Vertical lines'),
        'bb-hl' => t('Horizontal lines'),
        'bb-g'  => t('Grid'),
        'bb-d'  => t('Dots'),
      ),
    );
    $form['at']['menu_styles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Bullets'),
      '#description' => t('<h3>Menu Bullets</h3><p>This setting allows you to customize the bullet images used on menus items. Bullet images only show on normal vertical block menus.</p>'),
    );
    $form['at']['menu_styles']['menu_bullets'] = array(
      '#type' => 'select',
      '#title' => t('Menu Bullets'),
      '#default_value' => theme_get_setting('menu_bullets'),
      '#options' => array(
        'mb-n' => t('None'),
        'mb-dd' => t('Drupal default'),
        'mb-ah' => t('Arrow head'),
        'mb-ad' => t('Double arrow head'),
        'mb-ca' => t('Circle arrow'),
        'mb-fa' => t('Fat arrow'),
        'mb-sa' => t('Skinny arrow'),
      ),
    );
  }
}
