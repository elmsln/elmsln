<?php
/**
 * @file
 * textbook_editor.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function textbook_editor_filter_default_formats() {
  $formats = array();

  // Exported format: Textbook.
  $formats['textbook_editor'] = array(
    'format' => 'textbook_editor',
    'name' => 'Textbook',
    'cache' => 1,
    'status' => 1,
    'weight' => -10,
    'filters' => array(
      'filter_html' => array(
        'weight' => -50,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<div> <h2> <object> <embed> <param> <h3> <h4> <h5> <h6> <em> <iframe> <video> <strong> <img> <blockquote> <cite> <sup> <sub> <p> <ul> <ol> <li> <dl> <dt> <dd> <a> <table> <tr> <td> <th> <tbody> <thead> <tfoot> <colgroup> <caption> <hr>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'video_filter' => array(
        'weight' => -48,
        'status' => 1,
        'settings' => array(
          'video_filter_width' => 854,
          'video_filter_height' => 480,
          'video_filter_autoplay' => 0,
          'video_filter_related' => 0,
          'video_filter_html5' => 1,
        ),
      ),
      'ckeditor_link_filter' => array(
        'weight' => -47,
        'status' => 1,
        'settings' => array(),
      ),
      'transliteration' => array(
        'weight' => -46,
        'status' => 1,
        'settings' => array(
          'no_known_transliteration' => '?',
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -45,
        'status' => 1,
        'settings' => array(),
      ),
      'typogrify' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'smartypants_enabled' => 1,
          'smartypants_hyphens' => 2,
          'wrap_ampersand' => 1,
          'widont_enabled' => 1,
          'hyphenate_shy' => 0,
          'wrap_abbr' => 2,
          'wrap_caps' => 1,
          'wrap_initial_quotes' => 1,
          'wrap_numbers' => 2,
          'ligatures' => array(
            'ffi' => 0,
            'ffl' => 0,
            'ff' => 0,
            'fi' => 0,
            'fl' => 0,
            'ij' => 0,
            'IJ' => 0,
            'st' => 0,
            'ss' => 0,
          ),
          'arrows' => array(
            '->>' => '->>',
            '<<-' => '<<-',
            '->|' => '->|',
            '|<-' => '|<-',
            '<->' => '<->',
            '->' => '->',
            '<-' => '<-',
            '<=>' => '<=>',
            '=>' => '=>',
            '<=' => '<=',
          ),
          'fractions' => array(),
          'quotes' => array(
            ',,' => ',,',
            '\'\'' => '\'\'',
            '<<' => '<<',
            '>>' => '>>',
          ),
        ),
      ),
    ),
  );

  return $formats;
}
