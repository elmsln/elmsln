<?php

/**
 * @file
 * Migrate OGUR(6.x) roles and relations to 7.x-2.x.
 */

class OgMigrateOgur extends Migration {

  /**
   * Override constructor from Migration class.
   */
  public function __construct() {
    parent::__construct();

    $this->description = t('Migrate OGUR content from 6 to 7.x-2.x.');

    $this->dependencies[] = 'OgMigrateOgurRoles';
    $this->dependencies[] = 'OgMigrateUser';

    $this->query = db_select('d6_og_users_roles', 'ogur');
    $this->query->join('role', 'r', 'ogur.rid = r.rid');
    $this->query->join('og_role', 'ogr', 'r.name = ogr.name');

    $this->query->fields('ogur', array('gid', 'uid'))
      ->fields('ogr', array('rid'));

    $source_key = array(
      'gid' => array(
        'alias' => 'ogur',
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'node ID of group.',
      ),
      'uid' => array(
        'alias' => 'ogur',
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'User ID of member.',
      ),
      'rid' => array(
        'alias' => 'ogr',
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Role ID of role.',
      ),
    );

    $this->map = new MigrateSQLMap($this->machineName, $source_key, MigrateDestinationTable::getKeySchema('og_users_roles'));
    $this->source = new MigrateSourceSQL($this->query);
    $this->destination = new MigrateDestinationTable('og_users_roles');

    $field_names = array(
      'gid',
      'uid',
      'rid',
    );
    foreach ($field_names as $field_name) {
      $this->addFieldMapping($field_name, $field_name);
    }
    $this->addFieldMapping('group_type', NULL)->defaultValue('node');
  }

}
