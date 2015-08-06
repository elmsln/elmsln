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
          'allowed_html' => '<div> <h2> <fn> <object> <embed> <param> <h3> <h4> <h5> <h6> <em> <iframe> <video> <strong> <img> <blockquote> <cite> <sup> <sub> <p> <ul> <ol> <li> <dl> <dt> <dd> <a> <table> <tr> <td> <th> <tbody> <thead> <tfoot> <colgroup> <caption> <hr>',
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
            '-&gt;&gt;' => 0,
            '&lt;&lt;-' => 0,
            '-&gt;|' => 0,
            '|&lt;-' => 0,
            '&lt;-&gt;' => 0,
            '-&gt;' => 0,
            '&lt;-' => 0,
            '&lt;=&gt;' => 0,
            '=&gt;' => 0,
            '&lt;=' => 0,
          ),
          'fractions' => array(
            '1/4' => 0,
            '1/2' => 0,
            '3/4' => 0,
            '1/3' => 0,
            '2/3' => 0,
            '1/5' => 0,
            '2/5' => 0,
            '3/5' => 0,
            '4/5' => 0,
            '1/6' => 0,
            '5/6' => 0,
            '1/8' => 0,
            '3/8' => 0,
            '5/8' => 0,
            '7/8' => 0,
          ),
          'quotes' => array(
            ',,' => ',,',
            '\'\'' => '\'\'',
            '&lt;&lt;' => 0,
            '&gt;&gt;' => 0,
          ),
          'space_to_nbsp' => 1,
        ),
      ),
    ),
  );

  return $formats;
}
