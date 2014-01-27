<?php
/**
 * @file
 * Drupal Field Hidden module administration
 */

/**
 * Defines configuration form fields.
 *
 * Implements drupal_get_form().
 *
 * @param array $form
 * @param array &$form_state
 * @return array
 *   - the return value of system_settings_form()
 */
function _field_hidden_admin_form($form, &$form_state) {
  $form['field_hidden_help'] = array(
    '#type' => 'markup',
    '#markup' => '<p>' . l(t('Help/Readme'), 'admin/help/field_hidden') . '</p><p><hr/></p>',
  );
  $form['field_hidden_instance_settings_hide_defval'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not display default value field in instance setting form'),
    '#decription' => t('If checked, controlling/setting the default value in the field instance setting dialogue gets kind of hard.'),
    '#default_value' => variable_get('field_hidden_instance_settings_hide_defval', FALSE),
    '#required' => FALSE,
  );
  return system_settings_form($form);
}

/**
 * Helper for field_hidden_help(), which implements hook_help().
 *
 * @param string $path
 * @param unknown $arg
 *   - default: NULL
 * @return string|void
 */
function _field_hidden_help($path, $arg = NULL) {
  $css = str_replace('_', '-', $module = 'field_hidden');
  if ($path != 'admin/help#' . $module) {
    return;
  }
  $module_path = drupal_get_path('module', $module);
  $primary_function = FALSE; //$module;

  $content_main = '<h3>' . t('About') . '</h3>'
    . '<p>' . t('The Field Hidden module defines five hidden field types - text, long text, integer, decimal, and floating-point.', array('@field-help' => url('admin/help/field')))
    . '</p>'
    . '<h5>' . t('Hidden field types reflect data types') . '</h5>'
    . '<p>' . t('The only difference between text and long text is the database data type used - varchar versus text (MySQL: longtext).')
    . '<br/>' . t('Neither allow HTML nor PHP, only plain text.')
    . '</p>'
    . '<p>' . t('The numeric types correspond to the data types integer, decimal and float.')
    . '<br/>' . t('Decimal is often the better choice when it comes to decimal/floating numbers because it usually allows for a higher number of precise digits (typically 14) than float/double database fields do.')
    . '</p>'
    . '<h5>' . t('Hidden - in what sense?') . '</h5>'
    . '<p>' . t('A hidden field will always be hidden when editing a node/entity - an &lt;input type=&quot;hidden&quot; /&gt; form element.')
    . '<br/>' . t('When a node/entity is displayed on a page, these hidden fields default to be fully hidden (kept out the page\'s HTML output entirely).')
    . '<br/>' . t('The value of a hidden field may however be displayed in output, if another format than &lt;Hidden&gt; is selected in the content type\'s \'@manage_display\' section.', array('@manage_display' => t('Manage Display')))
    . '</p>';

  drupal_add_css(
    $module_path . '/' . $module . '.admin.css',
    array('type' => 'file', 'group' => CSS_DEFAULT, 'preprocess' => FALSE, 'every_page' => FALSE)
  );

  $out = '<div><div class="admin-help-module-' . $css . '-pane-first">'
    . $content_main;

  //  Read primary function's documentation.
  if ($primary_function && strlen($read_source = @file_get_contents($module_path . '/' . $module . '.module'))) {
    $pos_end = strpos($read_source, "\nfunction " . $primary_function . '(');
    $s_start = substr($read_source, 0, $pos_end);
    $s_start = substr($s_start, strrpos($s_start, '/**'));
    $s_end = substr($read_source, $pos_end);
    $pos_end = strpos($s_end, ')');
    $s = str_replace("\r", '', $s_start . substr($s_end, 0, $pos_end + 1) );
    $s = preg_replace('/\n([^\n]+)$/', "\n" . '<strong>$1 {...}</strong>',
      preg_replace('/^([^\n]+)\n/', '<strong>$1</strong>' . "\n",
      str_replace("\n- ", "\n&bull; ", // hyphen to bullet
      str_replace("\n/", "\n", // comment end
      preg_replace('/\n \*[ \t]*/', "\n", // comment line *
      str_replace('/**', '', // comment start
    $s))))));
    $out .= '<p>'
      . nl2br(
        preg_replace('/\n\n/', '</p><p>', $s)
      ) . '</p>';
  }

  $out .= '</div><div class="admin-help-module-' . $css . '-pane-second">';
  //  Parse README.txt to html.
  $out .= '<a name="readme"></a><h3>Readme</h3>';
  $readme = @file_get_contents(
    substr(dirname(__FILE__), 0, -1 * (1 + strlen($module_path)))
    . '/' . $module_path
    . '/README.txt'
  );
  $func = '_' . $module . '_readme2html';
  $out .= $func($readme)
    . '</div></div><hr/>';
  return $out;
}

/**
 * Parse README.txt to html.
 *
 *   Replacements:
 *   - formats headlines; line with no hyphens followed by all hyphens line
 *   - hyphen to bullet; newline+space+*+space becomes newline+space+bullet+space
 *   - emphasizes underscore fragments; _what ever_ becomes <em>what ever</em>
 *   - turns url into link, and http://your-drupal-site.tld/some-path becomes internal link to /some-path
 *   - turns mail address into mailto link
 *
 * Some replacements (like emphasizing) only works for ascii letters, not for letters line like ñ or ö.
 * @param string $readme_txt
 * @param string $headline_tag
 *   - default: h5
 * @return string
 */
function _field_hidden_readme2html($readme_txt, $headline_tag = 'h5') {
  if (!strlen($readme_txt)) {
    return 'empty readme';
  }
  $ndls = array(
    '/</',
    '/>/',
    '/\r\n|\r/', // CR -> NL
    '/[\x20\t]+\n/', // trailing spaces (in lines)
    '/\n{3,}/', // 3 or more newlines to double
    '/<([^>@]+@[^>@]+)>/', // mail addresses
    '/([\n\x20])_([a-zA-Z\d][^\.,;\:\n\x20]*[a-zA-Z\d])_([\n\x20\.,;\:])/', // _emphasize_ -> <em>emphasize</em>
  );
  $rplcs = array(
    '&lt;',
    '&gt;',
    "\n",
    "\n",
    "\n\n",
    '<a href="mailto:$1">&#60;$1&#62;</a>',
    '$1<em>$2</em>$3',
  );
  $s = preg_replace($ndls, $rplcs, $readme_txt);

  //  Insert links in CONTENTS OF THIS FILE.
  if (strpos($s, 'CONTENTS OF THIS FILE') !== FALSE) {
    $pos_start = strpos($s, ' * ');
    $pos_end = strpos($s, "\n\n", $pos_start);
    $s_toc = preg_replace('/[ ]+\n/', "\n", substr($s, $pos_start, ($pos_end - $pos_start) + 1) ); // remove trailing space(s)
    //echo $s_toc; exit;
    $s_toc = preg_replace_callback(
      '/ \* ([^\n]+)\n/',
      create_function(
        '$ms',
        '
        return \' * <a href="#\' .
            strtolower( preg_replace(\'/[^a-zA-Z_\-]/\', \'_\', $ms[1]) )
            . \'">\' . $ms[1] . \'</a>\' . "\n";
        '
      ),
      $s_toc
    );
    $s_start = substr($s, 0, $pos_start);
    $s_end = substr($s, $pos_end);
    $s = str_replace('CONTENTS OF THIS FILE', 'CONTENTS', $s_start) . $s_toc . $s_end;
  }

  //  Format headlines, and insert anchor.
  $s = preg_replace_callback(
    '/\n([^\n\-])([^\n]*[^\n\-])\n[\-]{2,}\n+/',
    create_function(
      '$ms',
      '
      return \'</p><a name="\'
        . strtolower( preg_replace(\'/[^a-zA-Z_\-]/\', \'_\', $ms[1] . $ms[2]) )
        . \'"></a><headlineTag style="margin-top:20px;">\'
        . $ms[1]
        . \'<span style="text-transform:lowercase;">\' . $ms[2] . \'</span></headlineTag><p>\';
      '
    ),
    $s
  );
  $s = str_replace('headlineTag', $headline_tag, $s);

  $ndls = array(
    '/^[^\n]*\n/', // remove first line
    //'//',
  );
  $rplcs = array(
    '',
    //'',
  );
  $s = preg_replace($ndls, $rplcs, $s);
  //  Links may be followed by a punctuation marker, hard to detect without a callback.
  //  And http://your-drupal-site.tld/path should become /path
  $s = preg_replace_callback(
    '/(https?\:\/\/)(\S+)([\x20\t\n])/',
    create_function(
      '$ms',
      '
      $protocol = $ms[1];
      $le = strlen($addr = $ms[2]);
      $dot = \'\';
      if (!preg_match(\'/[\/a-zA-Z\d]/\', $addr{$le - 1})) {
        $dot = $addr{$le - 1};
        $addr = substr($addr, 0, $le - 1);
      }
      if (strpos($addr, \'your-drupal-site.tld/\') === 0) {
        $protocol = \'/\';
        $addr = str_replace(\'your-drupal-site.tld/\', \'\', $addr);
      }
      return \'<a href="\' . $protocol . $addr . \'">\' . $addr . \'</a>\' . $dot . $ms[3];
      '
    ),
    $s
  );
  $ndls = array(
    '/([\n>]) \* /', // \n *  to \n bullet
    '/^\n?<\/p>/', // first ending <p> added by headline (in total)
    '/\n?$/', // trailing newlines (in total)
    '/\n{2,}/',
    //'//',
  );
  $rplcs = array(
    '$1 &bull; ',
    '',
    '',
    '</p><p>',
    //'',
  );
  return nl2br( preg_replace($ndls, $rplcs, $s) ) . '</p>';
}