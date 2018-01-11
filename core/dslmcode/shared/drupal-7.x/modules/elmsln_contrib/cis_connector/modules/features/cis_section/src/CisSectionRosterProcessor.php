<?php

/**
 * Process a roster, creating and updating accounts accordingly.
 *
 * This provides support for deferred, batched processing via Drupal cron. This
 * is disabled by default to preserve existing behavior and can be enabled by
 * providing a batch size using the \CisSectionRosterProcessor::BATCH_VARIABLE
 * variable.
 */
class CisSectionRosterProcessor {

  /**
   * The variable name for the default roster batch size.
   */
  const BATCH_VARIABLE = 'cis_section_roster_processor_batch_size';

  /**
   * Unlimited batch size, used to disable cron based processing.
   */
  const BATCH_UNLIMITED = FALSE;

  /**
   * Default batch size, use the batch size in the
   * \CisSectionRosterProcessor::BATCH_VARIABLE variable.
   */
  const BATCH_DEFAULT = TRUE;

  /**
   * The name for the Drupal queue.
   */
  const QUEUE_NAME = 'cis_section_roster_process';

  /**
   * The roster being processed.
   *
   * Outer keys are sections, inner keys are usernames. Values are either a role
   * name or an array containing:
   * - role: The role name.
   * - mail: The account email address.
   * - pass: (Optional) The account password.
   *
   * @var array
   */
  protected $roster;

  /**
   * The number of items to process in a batch.
   *
   * @var int
   */
  protected $batchSize;

  /**
   * How many items we have already processed in this batch.
   *
   * @var int
   */
  protected $processed = 0;

  /**
   * An array of cached role data.
   *
   * Keys are the role name. Values are an array of:
   * - role_id: The ID of the role.
   * - group_id: The ID of the group role.
   *
   * @var array
   */
  protected $roleCache = array();

  /**
   * The user IDs for students still on the roster for the current section.
   *
   * @var int[]
   */
  protected $actualStudents = array();

  /**
   * The user IDs for students to be archived across all sections.
   *
   * @var int[]
   */
  protected $archiveStudents = array();

  /**
   * Construct the roster processor object.
   *
   * @param array $roster
   *   The roster to process.
   * @param int|bool $batch_size
   *   How many items to process in a batch. Once we hit the batch limit, we
   *   will queue up the next task in the cron. Alternatively, you can provide:
   *   - \CisSectionRosterProcessor::BATCH_UNLIMITED: (Default) Unlimited
   *     batch size to disable batching and process all immediately.
   *   - \CisSectionRosterProcessor::BATCH_DEFAULT: Use the site's default batch
   *     size, definined by the \CisSectionRosterProcessor::BATCH_VARIABLE
   *     variable, defaulting to disabled for backwards compatibility.
   */
  public function __construct(array $roster, $batch_size = self::BATCH_UNLIMITED) {
    $this->roster = $roster;

    // If the default is requested, retrieve it from settings.
    if ($batch_size = self::BATCH_DEFAULT) {
      $this->batchSize = variable_get(self::BATCH_VARIABLE, self::BATCH_UNLIMITED);
    }
    // Otherwise we can just set it.
    else {
      $this->batchSize = $batch_size;
    }
  }

  /**
   * Only serialize the parts we want to preserve.
   */
  function __sleep() {
    return array(
      'roster',
      'batchSize',
      'actualStudents',
      'archiveStudents',
      'roleCache',
    );
  }

  /**
   * Process a batch of the roster.
   */
  public function process() {
    // Reset everything so we start from the beginning.
    $this->processed = 0;
    reset($this->roster);

    // Process items until we have to stop.
    while ($this->batchSize == self::BATCH_UNLIMITED || $this->processed < $this->batchSize) {
      if (!$this->processItem()) {
        break;
      }
      $this->processed++;
    }

    // If we are not finished, queue ourselves.
    if (!$this->isFinished()) {
      $this->queue();
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Put this processor into the queue to be continued later.
   *
   * We'll also clear ourselves down to we don't double process.
   */
  public function queue() {
    /* @var \DrupalQueueInterface $queue */
    $queue = \DrupalQueue::get(static::QUEUE_NAME);
    $queue->createQueue();

    // Add ourselves to the queue.
    $queue->createItem($this);

    // Clear down our data to prevent double processing.
    $this->roster = array();
    $this->actualStudents = array();
  }

  /**
   * Process one item from the roster, doing any necessary clean up.
   *
   * Clean up means that this method can be called again and it will process the
   * next item.
   *
   * @return bool
   *   Whether we have processed an item.
   */
  protected function processItem() {
    // If the roster is not empty, continue to process it.
    if (!empty($this->roster)) {
      // Get the section and group.
      reset($this->roster);
      $section = key($this->roster);
      $gid = $this->getSectionGroup($section);

      // Figure out what is next to process.
      // If we have members, process the next one.
      if (!empty($this->roster[$section])) {
        reset($this->roster[$section]);
        $name = key($this->roster[$section]);
        $user_data = array_shift($this->roster[$section]);
        $this->processStudent($gid, $name, $user_data, $this->actualStudents);
      }
      // Otherwise, we have finished this section, so clean up and move on.
      else {
        $this->completeSection($section, $gid);
      }
    }
    // Otherwise, if there are any students to archive, process them.
    elseif (!empty($this->archiveStudents)) {
      $this->archiveStudent(array_shift($this->archiveStudents));
    }
    // Otherwise it looks like there's nothing to do.
    else {
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Process an individual student from the roster.
   *
   * This creates the account, if necessary, and ensures it has the right roles.
   *
   * @param int $gid
   *   The ID of the section group.
   * @param string $name
   *   The account name.
   * @param string|array $user_data
   *   Either the role name or an array containing:
   *   - role: The role name.
   *   - mail: The account email address.
   *   - pass: (Optional) The account password.
   */
  protected function processStudent($gid, $name, $user_data, &$actual) {
    // Separate role name from user data.
    if (is_string($user_data)) {
      $role_name = $user_data;
      $user_data = array('role' => $role_name);
    }
    else {
      $role_name = $user_data['role'];
    }

    // Get our role IDs from the cache.
    extract($this->getRoleIds($role_name));
    /* @var $role_id int */
    /* @var $group_id int */

    // Attempt to load the account.
    $account = user_load_by_name($name);

    // If it doesn't exist, create it.
    if (!$account) {
      $values = array(
        'name' => $name,
        'status' => 1,
        'roles' => array($role_id => $role_name),
      ) + $user_data;
      unset($values['role']);

      // Generate a random password if we don't have one.
      if (!isset($values['pass'])) {
        $values['pass'] = user_password(20);
      }

      // allow other projects to update part of the user
      drupal_alter('cis_section_user_insert', $fields, $userdata);

      // the first parameter is left blank so a new user is created
      $account = user_save('', $values);
    }
    // Otherwise, check our sync details.
    else {
      $save_user = FALSE;
      $edit = array();
      // Add the role if it doesn't already exist.
      if (!isset($account->roles[$role_id])) {
        $account->roles[$role_id] = $role_name;
        $save_user = TRUE;
      }

      // If we were given an email or password and they differ, update them.
      if (isset($user_data['mail']) && $account->mail != $user_data['mail']) {
        $account->mail = $user_data['mail'];
        $save_user = TRUE;
      }
      if (isset($user_data['pass']) && $account->pass != $user_data['pass']) {
        $account->pass = $user_data['pass'];
        $save_user = TRUE;
      }

      // Update the data, if provided.
      if (isset($user_data['data']) && $account->data != $user_data['data']) {
        $edit['data'] = $user_data['data'];
        $save_user = TRUE;
      }

      if ($save_user) {
        user_save($account, $edit);
      }
    }

    // add group membership
    $values = array(
      'entity_type' => 'user',
      'entity' => $account,
      'field_name' => 'og_user_node',
    );
    og_group('node', $gid, $values);
    // give them the special staff role if it exists
    if ($group_id) {
      _cis_section_og_role_grant('node', $gid, $account->uid, $group_id, 'update');
    }

    // Store our ID so we can archive inactive students.
    $actual[] = $account->uid;

    // allow other things to react to an account being processed
    // via this job
    drupal_alter('cis_section_account_processed', $account, $userdata);
  }

  /**
   * Get the IDs of students to be archived.
   *
   * @param int $gid
   *   The group ID for the section we are processing.
   * @param int[]
   *   An array of actually enrolled student user IDs.
   *
   * @return array
   *   An array of students to archive.
   */
  protected function getStudentsToArchive($gid, $actual) {
    // see if developer variable exists to prevent drop of access
    // if we no longer see the account come across
    if (!variable_get('cis_section_strict_access', CIS_SECTION_STRICT_ACCESS)) {
      return array();
    }

    // compare members that just came across to members currently (that are students)
    // anyone currently that didn't just come across, gets role dropped
    // they gain past student
    $student = user_role_load_by_name(CIS_SECTION_STUDENT);
    if (isset($gid)) {
      $current = _cis_section_load_users_by_gid($gid, $student->rid);
    }
    else {
      $current = array();
    }

    // find users that no longer came across
    return array_diff($current, $actual);
  }

  /**
   * Archive a student who is no longer enrolled.
   *
   * @param int $uid
   *   User ID of the student to archive.
   */
  protected function archiveStudent($uid) {
    // compare members that just came across to members currently (that are students)
    // anyone currently that didn't just come across, gets role dropped
    // they gain past student
    $student = user_role_load_by_name(CIS_SECTION_STUDENT);
    $past = user_role_load_by_name(CIS_SECTION_PAST_STUDENT);

    $account = user_load($uid);
    // drop student role
    unset($account->roles[$student->rid]);
    // gain past student role
    $account->roles[$past->rid] = $past->name;
    user_save($account);
  }

  /**
   * Reset variables when we complete a section.
   *
   * @param int $section
   *   The section ID.
   * @param int $gid
   *   The group ID for the section we are processing.
   */
  protected function completeSection($section, $gid) {
    // Remove the section from the roster.
    unset($this->roster[$section]);

    // compare members that just came across to members currently (that are students)
    // anyone currently that didn't just come across, gets role dropped
    // they gain past student
    $student = user_role_load_by_name(CIS_SECTION_STUDENT);
    $current = _cis_section_load_users_by_gid($gid, $student->rid);

    // find users that no longer came across
    $diff = array_diff($current, $this->actualStudents);
    $this->archiveStudents = array_merge($this->archiveStudents, $diff);
  }

  /**
   * Get the group for a section, creating if necessary.
   *
   * @param int $section
   *   The section node ID.
   *
   * @return int
   *   The group ID.
   */
  protected function getSectionGroup($section) {
    // load group by section
    $gid = _cis_section_load_section_by_id($section);

    // false returned if this group doesn't exist
    if (!$gid) {
      // we need to create the group as this is a new one
      // possibly produced at run time of the sync
      $group = new stdClass();
      $group->type = 'section';
      $group->status = 1;
      $group->uid = 1;
      $group->title = $section;
      $group->promote = 0;
      $group->revision = 1;
      $group->field_section_id = array(
        'und' => array(
          0 => array(
            'value' => $section,
          ),
        ),
      );
      node_save($group);
      $gid = $group->nid;
    }

    // Return the group ID.
    return $gid;
  }

  /**
   * Get the role and OG role IDs for a given role name.
   *
   * This caches the values to avoid excessive lookups.
   *
   * @param string $role_name
   *   The name of our role to look up.
   *
   * @return array
   *   An array containing:
   *   - role_id: The ID of the role.
   *   - group_id: The ID of the group role.
   */
  protected function getRoleIds($role_name) {
    if (!isset($this->roleCache[$role_name])) {
      $role = user_role_load_by_name($role_name);

      // If we have no role, use the authenticated user role.
      if (!isset($role->rid) || empty($role->rid) || $role->rid == 0) {
        $role->rid = 2;
        $role->name = 'authenticated user';
        $og_role = FALSE;
      }
      // Otherwise fine the corresponding OG Role.
      else {
        $og_role = _cis_section_og_role_load_by_name($role_name);
      }

      $this->roleCache[$role_name] = array(
        'role_id' => $role->rid,
        'group_id' => $og_role ? $og_role->rid : NULL,
      );
    }

    return $this->roleCache[$role_name];
  }

  /**
   * Check whether we have finished processing this roster.
   *
   * @return bool
   *   Whether we have finished.
   */
  public function isFinished() {
    // If there is anything in the roster or archive students, we haven't
    // finished.
    return empty($this->roster) && empty($this->archiveStudents);
  }

}