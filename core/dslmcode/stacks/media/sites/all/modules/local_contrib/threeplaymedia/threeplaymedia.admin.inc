<?php

/**
 * Callback for admin settings.
 */
function threeplaymedia_admin_settings() {
	$form = array();
	$form['threeplaymedia_api'] = array(
	  '#type' => 'textfield',
		'#title' => t('3PlayMedia API key'),
		'#default_value' => variable_get('threeplaymedia_api', ''),
		'#required' => TRUE,
	);
	$form['threeplaymedia_secret'] = array(
	  '#type' => 'textfield',
		'#title' => t('3PlayMedia API secret'),
		'#default_value' => variable_get('threeplaymedia_secret', ''),
		'#required' => TRUE,
	);
	$form['threeplaymedia_turnaround_extended'] = array(
	  '#type' => 'checkbox',
		'#title' => t('Extended turn around'),
		'#default_value' => variable_get('threeplaymedia_turnaround_extended', TRUE),
		'#description' => t('This flag will provided the cheapest option ($0.20 less per minute) for processing but may take up to 10 business days to complete. Deselect this if you want a turn around time of 4 business days.'),
	);
	$formats = array(
		'vtt' => 'WebVTT',
		'srt' => 'srt',
		'dfxp' => 'dfxp',
		'smi' => 'smi',
		'stl' => 'stl',
		'qt' => 'Quicktime',
		'qtxml' => 'Quicktime (XML)',
		'cptxml' => 'cptxml',
		'adbe' => 'adbe'
	);
	$form['threeplaymedia_caption_format'] = array(
	  '#type' => 'select',
	  '#options' => $formats,
		'#title' => t('Caption format'),
		'#default_value' => variable_get('threeplaymedia_caption_format', 'vtt'),
		'#description' => t('What caption format do you support? The default is WebVTT which is better aligned with HTMl5 and used by Ableplayer but other formats exist if you need them.'),
	);
	return system_settings_form($form);
}