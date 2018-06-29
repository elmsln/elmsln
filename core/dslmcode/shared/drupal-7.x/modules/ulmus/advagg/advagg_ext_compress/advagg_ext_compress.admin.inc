<?php

/**
 * @file
 * Admin page callbacks for the advagg external compression module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup advagg_forms
 *
 * @see system_settings_form()
 */
function advagg_ext_compress_admin_settings_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: External Compressor'));
  advagg_display_message_if_requirements_not_met();

  $form = array();
  // CSS command line.
  advagg_ext_compress_admin_cmd_generate($form, array('css', t('CSS')));
  // JS command line.
  advagg_ext_compress_admin_cmd_generate($form, array('js', t('JavaScript')));

  return system_settings_form($form);
}

/**
 * Generate a form for css or js depending on the input.
 *
 * @param array $form
 *   The form array to add to.
 * @param array $params
 *   An array where key 0 is the machine name and key 1 is the title.
 */
function advagg_ext_compress_admin_cmd_generate(array &$form, array $params) {
  $form[$params[0]] = array(
    '#type' => 'fieldset',
    '#title' => t('@title', array('@title' => $params[1])),
  );
  $form[$params[0]]['cmd'] = array(
    '#type' => 'fieldset',
    '#title' => t('Command Line'),
  );

  $description = t('{%CWD%} = DRUPAL_ROOT. <br /> {%IN%} = input file. <br /> {%IN_URL_ENC%} = url pointing to the input file that has been url encoded. <br /> {%OUT%} = output file. <br /><br />');
  if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') {
    $description .= ' ' . t('Example using the <a href="@link1">Microsoft Ajax Minifier</a>. <p><code>@code1</code></p>', array(
      '@link1' => 'http://ajaxmin.codeplex.com/',
      '@code1' => 'AjaxMinifier {%IN%} -o {%OUT%}',
    ));
  }

  if ($params[0] === 'js') {
    $description .= ' ' . t('Example using the <a href="@link1">Google Closure Compiler</a>. <p><code>@code1</code></p>', array(
      '@link1' => 'https://developers.google.com/closure/compiler/docs/gettingstarted_app',
      '@code1' => 'java -jar compiler.jar --js {%CWD%}/{%IN%} --js_output_file {%OUT%}',
    ));

    $description .= ' ' . t('Example using curl to compress via the <a href="@link1">Online Google Closure Compiler</a>. <p><code>@code1</code></p>', array(
      '@link1' => 'https://developers.google.com/closure/compiler/docs/api-ref',
      '@code1' => 'curl -o {%OUT%} -d output_info=compiled_code -d code_url={%IN_URL_ENC%} http://closure-compiler.appspot.com/compile',
    ));
  }
  if ($params[0] === 'css') {
    $description .= ' ' . t('Example using the <a href="@link1">YUI Compressor</a>. <p><code>@code1</code></p>', array(
      '@link1' => 'http://yui.github.io/yuicompressor/',
      '@code1' => 'java -jar yuicompressor-x.y.z.jar --type css --line-break 4096 {%CWD%}/{%IN%} -o {%OUT%}',
    ));

    $description .= ' ' . t('Example using curl to compress via an online <a href="@link1">CSS Compressor</a>. <p><code>@code1</code></p>', array(
      '@link1' => 'http://cnvyr.io/',
      '@code1' => 'curl -o {%OUT%} -F \'files0=@{%IN%}\' http://srv.cnvyr.io/v1?min=css',
    ));
  }

  $form[$params[0]]['cmd']['advagg_ext_compress_' . $params[0] . '_cmd'] = array(
    '#type' => 'textfield',
    '#title' => t('Command to run'),
    '#default_value' => variable_get('advagg_ext_compress_' . $params[0] . '_cmd', ''),
    '#description' => $description,
  );
}
