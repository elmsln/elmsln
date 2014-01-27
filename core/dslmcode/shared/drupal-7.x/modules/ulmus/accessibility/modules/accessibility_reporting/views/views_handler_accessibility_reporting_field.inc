<?php

/**
 * @file
 * Views handler to display real field label in accessiiblity report.
 */
class views_handler_accessibility_reporting_field extends views_handler_field {
	
	function render($values) {
		$alias = $this->table_alias;
		$field = field_info_instance($values->{$alias .'_entity_type'}, $values->{$alias .'_field'}, $values->{$alias .'_bundle'});
		return $field['label'];
	}

	function query() {
		parent::query();
    $this->query->add_field($this->table_alias, 'entity_type');
    $this->query->add_field($this->table_alias, 'bundle');
	}
}