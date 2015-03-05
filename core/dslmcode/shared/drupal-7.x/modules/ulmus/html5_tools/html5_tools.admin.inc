<?php

/**
 * @file
 * Admin page callbacks for the html5_tools module.
 */

/**
 * HTML5 Tools configuration page.
 */
function html5_tools_admin_settings() {
  $form['html5_tools_forms'] = array(
    '#type' => 'fieldset',
    '#title' => t("Override Drupal's forms with their HTML5 counterparts"),
    '#collapsible' => FALSE,
  );
  $form['html5_tools_forms']['html5_tools_override_system_site_information_form'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_system_site_information_form', 1),
    '#title' => t('Site information'),
    '#description' => t('Modify the site configuration email textfield to an email field.'),
  );
  $form['html5_tools_forms']['html5_tools_override_search_block_form'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_search_block_form', 1),
    '#title' => t('Search block'),
    '#description' => t('Modify the search block textfield to a search field.'),
  );
  $form['html5_tools_forms']['html5_tools_override_search_form'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_search_form', 1),
    '#title' => t('Search form'),
    '#description' => t('Modify the search form textfield to a search field.'),
  );
  $form['html5_tools_forms']['html5_tools_override_user_register_form'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_user_register_form', 1),
    '#title' => t('User registration'),
    '#description' => t('Modify the user registration textfield to an email field.'),
  );
  $form['html5_tools_forms']['html5_tools_override_contact_forms'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_contact_forms', 1),
    '#title' => t('Contact forms'),
    '#description' => t("Modify contact form's textfields to email fields."),
  );

  $form['html5_tools_head_markup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Simplify &lt;head&gt; markup'),
    '#collapsible' => FALSE,
  );
  $form['html5_tools_head_markup']['html5_tools_override_doctype'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_doctype', 1),
    '#title' => t('Simplify doctype'),
    '#description' => t('Replaces html.tpl.php with a custom html.tpl.php which has the proper html5 doctype. This settings will not take effect if your theme has its own html.tpl.php.'),
  );
  $form['html5_tools_head_markup']['html5_tools_override_style_tags'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_style_tags', 1),
    '#title' => t('Simplify style tags'),
    '#description' => t('Removes the type attribute from links to stylesheets. The format for HTML5 is <em>&lt;link rel="stylesheet" href="file.css" /&gt;</em>. The <em>type="text/css"</em> is unnecessary.'),
  );
  $form['html5_tools_head_markup']['html5_tools_override_script_tags'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_script_tags', 1),
    '#title' => t('Simplify javascript tags'),
    '#description' => t('Removes the type attribute from the &lt;script&gt; tag. The format for HTML5 is <em>&lt;script src="file.js"&gt;&lt;/script&gt;</em>. The <em>type="text/javascript"</em> is unnecessary. All browsers will assume it is javascript.'),
  );
  $form['html5_tools_head_markup']['html5_tools_override_meta_tags'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_meta_tags', 1),
    '#title' => t('Simplify meta tags'),
    '#description' => t('Alters the <em>http-equiv="content-type"</em> meta tag to make it shorter, removing the http-equiv and content attributes. They are unnecessary.'),
  );
  $form['html5_tools_head_markup']['html5_tools_add_chrome_frame_header'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_add_chrome_frame_header', 1),
    '#title' => t('Add Google Chrome Frame headers'),
    '#description' => t('Adds the X-UA-Compatible: IE=Edge,chrome=1 headers for IE browsers. This will not prompt the user to install !gcf, it\'ll just use it if available.', array(
      '!gcf' => l('Google Chrome Frame', 'http://code.google.com/chrome/chromeframe/'),
    )),
  );

  $form['html5_tools_overrides'] = array(
    '#type' => 'fieldset',
    '#title' => t('Convert other variables'),
    '#collapsible' => FALSE,
  );
  $form['html5_tools_overrides']['html5_tools_override_submitted'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('html5_tools_override_submitted', 1),
    '#title' => t('Alter publication date markup'),
    '#description' => t('Implements the new &lt;time&gt; element and it\'s <em>pubdate</em> attribute, altering content and comment publication dates with the new HTML5 format by overriding the <em>$submitted</em> variable.'),
  );
  
  if (module_exists('views')) {
    $form['html5_tools_overrides']['html5_tools_override_views_field_rewrite_elements'] = array(
      '#type' => 'checkbox',
      '#default_value' => variable_get('html5_tools_override_views_field_rewrite_elements', 0),
      '#title' => t('Make new Elements available in the Views UI'),
      '#description' => t('This will allow you to use new elements such as <em>&lt;article&gt;</em>, <em>&lt;aside&gt;</em>, etc from views when choosing the custom HTML field'),
    );
  }
  $form['html5_tools_help_text'] = array(
    '#markup' => t("If one of these is not working, it might be because your theme is overriding what is specified here. Themes always get the last say in how something is outputted. Check your theme's template.php file."),
  );

  $form['#submit'][] = 'html5_tools_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Handle submission of the html5_tools configuration page.
 */
function html5_tools_admin_settings_submit($form, &$form_state) {
  if (!empty($form_state['values']['html5_tools_override_views_field_rewrite_elements'])) {
    variable_set('views_field_rewrite_elements', array(
      '' => t('- Use default -'),
      '0' => t('- None -'),
      'div' => t('DIV'),
      'span' => t('SPAN'),
      'h1' => t('H1'),
      'h2' => t('H2'),
      'h3' => t('H3'),
      'h4' => t('H4'),
      'h5' => t('H5'),
      'h6' => t('H6'),
      'p' => t('P'),
      'strong' => t('STRONG'),
      'em' => t('EM'),
      'article' => t('Article'),
      'aside' => t('Aside'),
      'footer' => t('Footer'),
      'header' => t('Header'),
      'menu' => t('Menu'),
      'nav' => t('Nav'),
    ));
  }
  else {
    variable_del('views_field_rewrite_elements');
  }

  drupal_theme_rebuild();
}
