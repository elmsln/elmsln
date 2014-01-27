<?php

/**
 * @file
 * Descriptions of hooks provided by the accessibility module.
 */

/**
 * A simple hook that is called when the accessibility module
 * is being used on a page. You can use this to load additional 
 * javascript files.
 */
function hook_accessibility_load() {
	drupal_add_js(drupal_get_path('module', 'my_module') . '/my_module.js');
}

/**
 * Allows modules to define their own accessibility tests, as well as
 * default translations and additional javascript files to load.
 */
function hook_accessibility_tests($get_translation) {
	return array('my_test' => array(
			'title' => t('My accessibility test'),
			'subject' => t('Make sure you have accessible content'),
			'description' => t('Accessibility is a legal obligation and a moral responsibility.'),
			'severity' => ACCESSIBILITY_TEST_SEVERE,
			'type' => 'selector',
			'selector' => '.myclass',
			'js' => array(
					drupal_get_path('module', 'my_module') .'/my_module.js',
				),
			'css' => array(
					drupal_get_path('module', 'my_module') .'/my_module.css',
				)
			),
		);
}

/**
 * Returns the human-readable translation (used for subject, description) of a test.
 */
function hook_accessibility_get_test_translation($test) {
	return array('title' => t('Title of my test'),
							 'body' => t('Description of my test'),
							 );
}

/**
 * Returns a list of machine names of tests that are associated with a guideline.
 */
function hook_accessibility_guidelines($tests = FALSE) {
	return array('guideline_key' => array('title' => t('My Guideline')));
}