<?php

/**
 * @file
 * Generate form elments for the Modify Output settings.
 */
function at_core_modify_output_form(&$form) {
  $form['at']['modify-output'] = array(
    '#type' => 'fieldset',
    '#title' => t('Markup Overrides'),
    '#weight' => 40,
  );

  // Design
  $form['at']['modify-output']['design'] = array(
    '#type' => 'fieldset',
    '#title' => t('Design'),
    '#description' => t('<h3>Design</h3>'),
  );
  // Adjust gutter width
  $form['at']['modify-output']['design']['global_gutter_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Set gutter width:'),
    '#size' => 2,
    '#maxlength' => 2,
    '#field_suffix' => 'px',
    '#description' => t('Gutters are set using margin-left and margin-right. This will override the default 10px margins set in <code>global.page.css</code>.'),
    '#default_value' => check_plain(at_get_setting('global_gutter_width')),
  );
  // Use the page full width wrappers template
  $form['at']['modify-output']['design']['page_full_width_wrappers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use page--full-width-wrappers.tpl.php by default'),
    '#description' => t('This setting will load a page template will full width DIV wrappers - perfect for designs with 100% width sections, header or footer. Note that if you choose to use other page template suggestions you should use copies of page--full-width-wrappers.tpl.php, you will find this in adaptivetheme/at-core/templates.'),
    '#default_value' => at_get_setting('page_full_width_wrappers'),
  );
  // Add page-[content-type] suggestions, all suggestions carry a performance
  // overhead, so allow the user to choose this rather than doing to by default
  $form['at']['modify-output']['design']['page_content_type_suggestions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable page--[content-type].tpl.php suggestions'),
    '#description' => t('If the node type is "blog" the template suggestion will be "page--blog.tpl.php". The content type suggestions are weak and can be overridden by single page--node.tpl.php template or standard page--node-[nid] templates.'),
    '#default_value' => at_get_setting('page_content_type_suggestions'),
  );
  // Add spans to theme_links
  $form['at']['modify-output']['design']['menu_item_span_elements'] = array(
    '#type' => 'checkbox',
    '#title' => t('Wrap menu item text in SPAN tags - useful for certain theme or design related techniques'),
    '#description' => t('Note: this does not work for <a href="!link" target="_blank">Superfish menus</a>, which includes its own feature for doing this.', array('!link' => 'http://drupal.org/project/superfish')),
    '#default_value' => at_get_setting('menu_item_span_elements'),
  );

  // Breadcrumb settings
  $form['at']['modify-output']['breadcrumb'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumbs'),
    '#description' => t('<h3>Breadcrumb Settings</h3>'),
  );
  $form['at']['modify-output']['breadcrumb']['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumbs'),
  );
  // Display?
  $form['at']['modify-output']['breadcrumb']['wrapper']['breadcrumb_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumbs'),
    '#default_value' => at_get_setting('breadcrumb_display'),
  );
  // Home link?
  $form['at']['modify-output']['breadcrumb']['wrapper']['breadcrumb_home'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the homepage link'),
    '#default_value' => at_get_setting('breadcrumb_home'),
    '#states' => array(
      'visible' => array('input[name="breadcrumb_display"]' => array('checked' => TRUE)),
    ),
  );
  // Label?
  $form['at']['modify-output']['breadcrumb']['wrapper']['breadcrumb_label'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the "You are here" label'),
    '#default_value' => at_get_setting('breadcrumb_label'),
    '#states' => array(
      'visible' => array('input[name="breadcrumb_display"]' => array('checked' => TRUE)),
    ),
  );
  // Page title?
  $form['at']['modify-output']['breadcrumb']['wrapper']['breadcrumb_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append the page title to the breadcrumb trail'),
    '#default_value' => at_get_setting('breadcrumb_title'),
    '#states' => array(
      'visible' => array('input[name="breadcrumb_display"]' => array('checked' => TRUE)),
    ),
  );
  // Seperator
  $form['at']['modify-output']['breadcrumb']['wrapper']['breadcrumb_separator'] = array(
    '#type'  => 'textfield',
    '#title' => t('Separator'),
    '#description' => t('Text, basic markup and html entities only. Dont forget to include spaces.'),
    '#default_value' => filter_xss_admin(at_get_setting('breadcrumb_separator')),
    '#size' => 25,
    '#maxlength' => 60,
    '#states' => array(
      'visible' => array('input[name="breadcrumb_display"]' => array('checked' => TRUE)),
    ),
  );

  // Login block options. There is also a slide-down block option, but I have never added it.
  if (at_get_setting('horizontal_login_block_enable') === 'on') {
    $form['at']['modify-output']['login-block'] = array(
      '#type' => 'fieldset',
      '#title' => t('Login Block'),
      '#description' => t('<h3>Login Block Options</h3>'),
    );
    // Login block links
    $form['at']['modify-output']['login-block']['login_block_remove_links'] = array(
      '#type' => 'checkbox',
      '#title' => t('Remove links'),
      '#default_value' => at_get_setting('login_block_remove_links'),
      '#description' => t('Remove the <em>Create new account</em> and <em>Request new password</em> links from the login block.'),
    );
    // Login block OpenID
    $form['at']['modify-output']['login-block']['login_block_remove_openid'] = array(
      '#type' => 'checkbox',
      '#title' => t('Remove OpenID elements'),
      '#default_value' => at_get_setting('login_block_remove_openid'),
      '#description' => t('Remove the OpenID links and form elements from the login block.'),
    );
    // Horizontal login block
    $form['at']['modify-output']['login-block']['horizontal_login_block'] = array(
      '#type' => 'checkbox',
      '#title' => t('Horizontal login block'),
      '#default_value' => at_get_setting('horizontal_login_block'),
      '#description' => t('Enable a horizontal style login block (all elements on one line). This does not work so well with OpenID and you should probably check the setting to remove OpendID elements.'),
    );
  }

  // User block
  $form['at']['modify-output']['user_block'] = array(
    '#type' => 'fieldset',
    '#title' => t('User block'),
    '#description' => t('<h3>User block</h3>'),
  );
  // Use extra fieldsets in advanced serach form
  $form['at']['modify-output']['user_block']['user_block_user_name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the "user name" as the User menu block title.'),
    '#default_value' => at_get_setting('user_block_user_name'),
    '#description' => t('This will override the block title setting (in block configuration) and use the users "user name" as the block title for the "User menu" block.'),
  );

  // Hide or Remove
  $form['at']['modify-output']['hide-remove'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hide or Remove'),
    '#description' => t('<h3>Hide or Remove</h3>'),
  );
  // Hide front page title
  $form['at']['modify-output']['hide-remove']['frontpage_remove_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove the frontpage title'),
    '#default_value' => at_get_setting('frontpage_remove_title'),
    '#description' => t('Checking this setting will remove the page title from the front page, for example if you set a node to be the front page content you may want to hide the title.'),
  );
  // Unset block system main front
  $form['at']['modify-output']['hide-remove']['unset_block_system_main_front'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not display the Main content block on the front page'),
    '#default_value' => at_get_setting('unset_block_system_main_front'),
    '#description' => t('Checking this setting will remove the Main content block from the front page only - useful for removing the welcome message and allowing use of another block.'),
  );
  // Hide RSS icons
  $form['at']['modify-output']['hide-remove']['feed_icons_hide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove RSS feed icons'),
    '#default_value' => at_get_setting('feed_icons_hide'),
    '#description' => t('Checking this setting will remove RSS feed icons. This will not affect the Syndicate block icon.'),
  );
  // Hide comment title
  $form['at']['modify-output']['hide-remove']['comments_hide_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide comment titles'),
    '#default_value' => at_get_setting('comments_hide_title'),
    '#description' => t('Checking this setting will hide comment titles using element-invisible. Hiding rather than removing titles maintains accessibility and semantic structure while not showing titles to sighted users.'),
  );
  // Remove menu link titles
  $form['at']['modify-output']['hide-remove']['unset_menu_titles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove menu link titles'),
    '#default_value' => at_get_setting('unset_menu_titles'),
    '#description' => t('Checking this setting will remove all menu link titles (tool tips). This only works for menu blocks.'),
  );

  // Accessibility
  $form['at']['modify-output']['a11y'] = array(
    '#type' => 'fieldset',
    '#title' => t('Accessibility'),
    '#description' => t('<h3>Accessibility</h3>'),
  );
  // Use extra fieldsets in advanced serach form
  $form['at']['modify-output']['a11y']['adv_search_extra_fieldsets'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use extra fieldset wrappers in the advanced search form'),
    '#default_value' => at_get_setting('adv_search_extra_fieldsets'),
    '#description' => t('The problem with Drupals standard Advanced search form is that each criterion group is wrapped in a DIV, whereas it should use fieldsets. Turning this on may cause issues with modules that modify the search form such as Search Config.'),
  );
  // Skip link target
  $form['at']['modify-output']['a11y']['skip_link_target'] = array(
    '#type' => 'textfield',
    '#title' => t('Skip to navigation target ID'),
    '#description' => t('If your main content is not in the Main Content region you can change the skip link target ID to match.'),
    '#default_value' => check_plain(at_get_setting('skip_link_target')),
  );

  // SEO/Authorship
  $form['at']['modify-output']['seo'] = array(
    '#type' => 'fieldset',
    '#title' => t('SEO'),
    '#description' => t('<h3>SEO</h3>'),
  );
  // Use extra fieldsets in advanced serach form
  $form['at']['modify-output']['seo']['rel_author'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add rel=author to user names.'),
    '#default_value' => at_get_setting('rel_author'),
    '#description' => t('Add rel author to user names to support Googles <a href="!authorhship" target="_blank">Authorship</a> feature.', array('!authorhship' => 'http://support.google.com/webmasters/bin/answer.py?hl=en&answer=1408986')),
  );
  // Change Logo title
  $form['at']['modify-output']['seo']['logo_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the Site Name for the logo title (tool tip).'),
    '#default_value' => at_get_setting('logo_title'),
    '#description' => t('By default the text "Home page" is used for the tool tip. This option overrides this with the site name.'),
  );

  // Extra CSS Classes
  $form['at']['modify-output']['extra-classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Classes'),
    '#description' => t('<h3>Extra CSS Classes</h3>'),
  );
  // Page
  $form['at']['modify-output']['extra-classes']['extra_page_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Page classes'),
    '#description' => t('page-path, add/edit/delete (for workflow states), content type classes, section classes, site name class (useful for multisites) and a language class (i18n)'),
    '#default_value' => at_get_setting('extra_page_classes'),
  );
  // Node
  $form['at']['modify-output']['extra-classes']['extra_article_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Node classes'),
    '#description' => t('promoted, sticky, preview, language, odd/even classes, user picture handling, and build mode classes'),
    '#default_value' => at_get_setting('extra_article_classes'),
  );
  // Comment
  $form['at']['modify-output']['extra-classes']['extra_comment_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Comment classes'),
    '#description' => t('anonymous, author, viewer, new, odd/even classes and classes for hidden titles, user picture and signature handling'),
    '#default_value' => at_get_setting('extra_comment_classes'),
  );
  // Block
  $form['at']['modify-output']['extra-classes']['extra_block_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Blocks classes'),
    '#description' => t('odd/even (zebra classes), block region, delta and block count classes'),
    '#default_value' => at_get_setting('extra_block_classes'),
  );
  // Menu
  $form['at']['modify-output']['extra-classes']['extra_menu_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Menus classes'),
    '#description' =>  t('menu link ID (mlid) and menu level (depth)'),
    '#default_value' => at_get_setting('extra_menu_classes'),
  );
  // Item lists
  $form['at']['modify-output']['extra-classes']['extra_item_list_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Item-lists classes'),
    '#description' => t('first, last and odd/even (zebra classes)'),
    '#default_value' => at_get_setting('extra_item_list_classes'),
  );

  // Attribution
  $form['at']['modify-output']['attribution'] = array(
    '#type' => 'fieldset',
    '#title' => t('Attribution'),
    '#description' => t('<h3>Attribution</h3>'),
  );
  $form['at']['modify-output']['attribution']['attribution_toggle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show attribution message'),
    '#description' => t('Displays a message and link for Adaptivethemes.com'),
    '#default_value' => at_get_setting('attribution_toggle'),
  );
}
