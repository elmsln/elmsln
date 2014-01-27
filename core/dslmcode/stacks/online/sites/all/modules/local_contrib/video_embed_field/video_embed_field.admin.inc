<?php

/**
 * Form builder; Form for editing a video style.
 * Used by CTools export ui
 *
 * @ingroup forms
 * @see video_embed_field_video_style_form_submit()
 */
function video_embed_field_video_style_form(&$form, &$form_state) {
  if(isset($form_state['item'])){
    $style = (array) $form_state['item'];
  } else {
    $style = array();
  }
  $form_state['video_style'] = $style;

  //Grab the settings off the parser form
  $values = isset($style['data']) ? $style['data'] : array();
  $parser_form = video_embed_field_get_form($values);

  //General settings for playback - formerly in the configuration section
  $form['data'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Playback settings'),
    '#tree' => TRUE,
  ) + $parser_form; //add in our extra settings

  return $form;
}