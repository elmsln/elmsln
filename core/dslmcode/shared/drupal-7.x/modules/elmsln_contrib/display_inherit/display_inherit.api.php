<?php

/**
 * @file
 * Defines examples for using Display Inherit functions
 */

/**
 * Implements hook_preprocess_node()
 *
 * Example implimentation of using display_inherit_inheritance_factory()
 * for creating inheritance preprocess functions and template files
 */
function mytheme_preprocess_node(&$variables) {
	$type = 'node';
	$bundle = $variables['type'];
	$viewmode = $variables['view_mode'];

	// create inheritance templates and preprocess functions for this entity
	if (module_exists('display_inherit')) {
	  display_inherit_inheritance_factory($type, $bundle, $viewmode, 'mytheme', $variables);
	}
}

/**
 * Example of add your own custom stacks
 * 
 * @param  string $type         entity type
 * @param  string $bundle       bundle machine name
 * @param  string $viewmode     viewmode of the entity
 * @param  string $theme_name   name of the theme that will have access to the preprocess functions
 * @param  array  &$variables   list of attributes and values associated to the entity, found in it's preprocess function
 *
 * @return  an array containing one or more inheritance stack arrays.
 */
function hook_display_inherit_inheritance_stacks($variables) {
	// Add a stack for
	$stacks = array();

	foreach (explode('__', $variables['view_mode']) as $viewmode_name) {
	  $inheritance_stacks['custom_stack'][] = $viewmode_name;
	}
	$inheritance_stacks['custom_stack'][] = $variables['nid'];

	return $stacks;
}

/**
 * Alter the final list of inheritance stacks
 */
function display_inherit_display_inherit_inheritance_stacks_alter(&$inheritance_stacks, $variables) {
}