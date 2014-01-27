<?php
/**
 * @file
 * Help module integration.
 */

/**
 * Implements hook_help().
 */
function custom_formatters_help($path, $arg) {
  switch ($path) {
    case 'admin/help#custom_formatters':
      $output =  '<h3>' . t('Table of Contents') . "</h3>\n"
               . '<a href="#about">' . t('About') . '</a> | <a href="#create">' . t('Creating a Formatter') . '</a> | <a href="#test">' . t('Testing a Formatter') . '</a> | <a href="#use">' . t('Using a Formatter') . '</a> | <a href="#cfcom">' . t('CustomFormatters.com') . "</a>\n"
               . "<p>&nbsp;</p>\n"
               . '<h3><a name="about"></a>' . t('About') . "</h3>\n"
               . "<p>\n"
               . '  ' . t('The Custom Formatters module is a utility to simplify the creation of Field Formatters, which can be used to theme the output of a Field via the Field UI, Views, Display Suite, Wysiwyg Fields and many other modules.') . "\n"
               . "</p>\n"
               . "<p>\n"
               . '  ' . t('Field Formatters created within the Custom Formatters interface can be used as is or exported as either a standard Drupal API Field Formatter or as a Custom Formatters CTools Exportable.')
               . "</p>\n"
               . "<p>&nbsp;</p>\n"
               . '<h3><a name="create"></a>' . t('Creating a Formatter') . "</h3>\n"
               . "<p>\n"
               . '  ' . t('Formatters can be created via the Formatters interface (!cfui) by clicking the !add button.', array('!cfui' => l(t('Administration &raquo; Structure &raquo; Formatters'), 'admin/structure/formatters', array('html' => TRUE)), '!add' => l(t('Add'), 'admin/structure/formatters/add'))) . "<br />\n"
               . "</p>\n"
               . "<p>\n"
               . '  ' . t('The Formatter add/edit form may vary based on the Format you choose, but in general all Formatters should consist of the following:') . "\n"
               . "</p>\n"
               . "<dl>\n"
               . '  <dt><strong>' . t('Formatter name / Machine name') . "</strong></dt>\n"
               . '  <dd>' . t('The Formatter name and the Machine name, in general generated via the same field, are the Human readable name and the unique identifier for the Formatter.') . "</dd>\n"
               . '  <dt><strong>' . t('Description') . "</strong></dt>\n"
               . '  <dd>' . t('Used purely for administration purposes, displays as a tooltip on the Formatters UI and in the Formatter add/edit form only.') . "</dd>\n"
               . '  <dt><strong>' . t('Format') . "</strong></dt>\n"
               . "  <dd>\n"
               . '    ' . t('The format that the Formatter is to be created in, may change the Formatters add/edit form.') . "<br />\n"
               . '    ' . t('Two format engines are supplied out of the box, <strong>PHP</strong> and <strong>HTML + Tokens</strong>.') . "\n"
               . "  </dd>\n"
               . '  <dt><strong>' . t('Field type(s)') . "</strong></dt>\n"
               . "  <dd>\n"
               . '    ' . t('Which field type(s) the Formatter will apply to (file, image, text, etc).') . "<br />\n"
               . '    ' . t('The value of this field should be the machine name of the field type, not the name of a field you have created on a Content type, available values will be auto-completed as you type.') . "\n"
               . "  </dd>\n"
               . '  <dt><strong>' . t('Formatter') . "</strong></dt>\n"
               . "  <dd>\n"
               . '    ' . t('The actual value of the Formatter, style depending on the chosen Format:') . "<br /><br />\n";

      $items = array();
      $engines = module_invoke_all('custom_formatters_engine_info');
      foreach ($engines as $engine) {
        if (isset($engine['file']) && file_exists($engine['file'])) {
          require_once $engine['file'];
        }
        if (isset($engine['callbacks']['help']) && function_exists($engine['callbacks']['help'])) {
          $items[] = '        <strong>' . $engine['label'] . "</strong><br />\n"
                   . '        ' . $engine['callbacks']['help']()
                   . "<br /><br />\n";
        }
      }
      if (count($items) > 0) {
        $output .= theme('item_list', array('items' => $items));
      }

      $output .= "  </dd>\n"
               . '  <dt><strong>' . t('Formatter Settings') . "</strong></dt>\n"
               . "  <dd>\n"
               . "    <p>\n"
               . '      ' . t('As of Custom Formatters 7.x-2.1, the PHP format now supports Formatter Settings, which allow you PHP formatters to be configured on each instance of use (Display settings per content type, etc).') . "\n"
               . "    </p>\n"
               . "    <p>\n"
               . '      ' . t('To enable the Formatter Settings functionality uou need to download and enable the <a href="http://drupal.org/project/form_builder">Form Builder</a> module, once enabled, you will be able to drag and drop fields to create your settings form, and then access the settings inside of your Formatter.') . "\n"
               . "    </p>\n"
               . "    <p>\n"
               . '      ' . t('The <a href="!url">Example: Image (PHP)</a> Formatter demonstrates how Formatter Settings can be used.', array('!url' => url('admin/structure/formatters/list/example_php_image/edit'))) . "\n"
               . "    </p>\n"
               . "  </dd>\n"
               . "</dl>\n"
               . "<p>&nbsp;</p>\n"
               . '<h3><a name="test"></a>' . t('Testing a Formatter') . "</h3>\n"
               . "<p>\n"
               . '  ' . t('The Formatter add/edit form includes a Preview tool allowing quick testing of the Formatter on live content.') . "\n"
               . "</p>\n"
               . "<p>\n"
               . '  ' . t('To do so all you need to do is expand the Preview fieldset and select a populated Entity type (Node, Comment, etc), Bundle (Article, Basic page, etc) and Field (Image, Tags, etc) combination, select the desired Entity for testing and hit the <strong>Preview</strong> button.') . "\n"
               . "</p>\n"
               . "<p>\n"
               . '  ' . t('Enabling the <a href="http://drupal.org/project/devel">Devel</a> and Devel Generate module (packaged with the Devel module) adds additional debugging information into your Formatter preview.') . "\n"
               . "</p>\n"
               . "<p>&nbsp;</p>\n"
               . '<h3><a name="use"></a>' . t('Using a Formatter') . "</h3>\n"
               . "<p>\n"
               . '  ' . t('Formatters can be used on a variety of different modules, including, but not limited to, Drupal Core Field UI, Views, Display Suite and Insert modules.') . "\n"
               . "</p>\n"
               . "<p>\n"
               . '  ' . t('Instructions on how to apply Formatters to Fields varies from module to module, but in general there will be a Format or Formatter field with the Field configuton within said module.') . "\n"
               . "</p>\n"
               . "<p>&nbsp;</p>\n"
               . '<h3><a name="cfcom"></a>' . t('<a href="http://customformatters.com">CustomFormatters.com</a>') . "</h3>\n"
               . "<p>\n"
               . '  ' . t('<a href="http://customformatters.com">CustomFormatters.com</a> is a Custom Formatters repository, containing a every growing list of reusable Custom Formatters available as raw code snippets, exportables and as Drupal API field formatters, it\'s a useful resouce to see examples of how to create Formatters.') . "\n"
               . "</p>\n"
               . "<p>&nbsp;</p>\n"
               . "<p>&nbsp;</p>\n";

      return $output;
  }
}
