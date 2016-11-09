<?php

/**
 * @file
 * Class for Checklist API checklists.
 */

/**
 * Defines the checklist class.
 */
class ChecklistapiChecklist {

  /**
   * The checklist ID.
   *
   * @var string
   */
  public $id;

  /**
   * The checklist title.
   *
   * @var string
   */
  public $title;

  /**
   * The menu item description.
   *
   * @var string
   */
  public $description;

  /**
   * The checklist path.
   *
   * @var string
   */
  public $path;

  /**
   * The checklist help.
   *
   * @var string
   */
  public $help;

  /**
   * The name of the menu to put the menu item in.
   *
   * @var string
   */
  public $menuName;

  /**
   * The checklist weight.
   *
   * @var float
   */
  public $weight;

  /**
   * The number of list items in the checklist.
   *
   * @var int
   */
  public $numberOfItems = 0;

  /**
   * The checklist groups and items.
   *
   * @var array
   */
  public $items = array();

  /**
   * The saved progress data.
   *
   * @var array
   */
  public $savedProgress;

  /**
   * Constructs a ChecklistapiChecklist object.
   *
   * @param array $definition
   *   A checklist definition, as returned by checklistapi_get_checklist_info().
   */
  public function __construct(array $definition) {
    foreach (element_children($definition) as $group_key) {
      $this->numberOfItems += count(element_children($definition[$group_key]));
      $this->items[$group_key] = $definition[$group_key];
      unset($definition[$group_key]);
    }
    foreach ($definition as $property_key => $value) {
      $property_name = checklistapi_strtolowercamel(drupal_substr($property_key, 1));
      $this->$property_name = $value;
    }
    $this->savedProgress = variable_get($this->getSavedProgressVariableName(), array());
  }

  /**
   * Gets the total number of completed items.
   *
   * @return int
   *   The number of completed items.
   */
  public function getNumberCompleted() {
    return (!empty($this->savedProgress['#completed_items'])) ? $this->savedProgress['#completed_items'] : 0;
  }

  /**
   * Gets the total number of items.
   *
   * @return int
   *   The number of items.
   */
  public function getNumberOfItems() {
    return $this->numberOfItems;
  }

  /**
   * Gets the name of the last user to update the checklist.
   *
   * @return string
   *   The themed name of the last user to update the checklist, or 'n/a' if
   *   there is no record of such a user.
   */
  public function getLastUpdatedUser() {
    if (isset($this->savedProgress['#changed_by'])) {
      $last_updated_user = user_load($this->savedProgress['#changed_by']);
      return theme('username', array('account' => $last_updated_user));
    }
    else {
      return t('n/a');
    }
  }

  /**
   * Gets the last updated date.
   *
   * @return string
   *   The last updated date formatted with format_date(), or 'n/a' if there is
   *   no saved progress.
   */
  public function getLastUpdatedDate() {
    return (!empty($this->savedProgress['#changed'])) ? format_date($this->savedProgress['#changed']) : t('n/a');
  }

  /**
   * Gets the percentage of items complete.
   *
   * @return float
   *   The percent complete.
   */
  public function getPercentComplete() {
    if ($this->getNumberOfItems() == 0) {
      return 100;
    }
    return ($this->getNumberCompleted() / $this->getNumberOfItems()) * 100;
  }

  /**
   * Clears the saved progress for the checklist.
   *
   * Deletes the Drupal variable containing the checklist's saved progress.
   */
  public function clearSavedProgress() {
    variable_del($this->getSavedProgressVariableName());
    drupal_set_message(t('%title saved progress has been cleared.', array(
      '%title' => $this->title,
    )));
  }

  /**
   * Gets the name of the Drupal variable for the checklist's saved progress.
   *
   * @return string
   *   The Drupal variable name.
   */
  public function getSavedProgressVariableName() {
    return "checklistapi_checklist_{$this->id}";
  }

  /**
   * Determines whether the checklist has saved progress.
   *
   * @return bool
   *   TRUE if the checklist has saved progress, or FALSE if it doesn't.
   */
  public function hasSavedProgress() {
    return (bool) variable_get($this->getSavedProgressVariableName(), FALSE);
  }

  /**
   * Saves checklist progress to a Drupal variable.
   *
   * @param array $values
   *   A multidimensional array of form state checklist values.
   *
   * @see checklistapi_checklist_form_submit()
   */
  public function saveProgress(array $values) {
    global $user;
    $time = time();
    $num_changed_items = 0;
    $progress = array(
      '#changed' => $time,
      '#changed_by' => $user->uid,
      '#completed_items' => 0,
    );

    // Loop through groups.
    foreach ($values as $group_key => $group) {
      if (!is_array($group)) {
        continue;
      }
      // Loop through items.
      foreach ($group as $item_key => $item) {
        $definition = checklistapi_get_checklist_info($this->id);
        if (!in_array($item_key, array_keys($definition[$group_key]))) {
          // This item wasn't in the checklist definition. Don't include it with
          // saved progress.
          continue;
        }
        $old_item = (!empty($this->savedProgress[$item_key])) ? $this->savedProgress[$item_key] : 0;
        if ($item == 1) {
          // Item is checked.
          $progress['#completed_items']++;
          if ($old_item) {
            // Item was previously checked. Use saved value.
            $new_item = $old_item;
          }
          else {
            // Item is newly checked. Set new value.
            $new_item = array(
              '#completed' => $time,
              '#uid' => $user->uid,
            );
            $num_changed_items++;
          }
        }
        else {
          // Item is unchecked.
          $new_item = 0;
          if ($old_item) {
            // Item was previously checked.
            $num_changed_items++;
          }
        }
        $progress[$item_key] = $new_item;
      }
    }

    // Sort array elements alphabetically so changes to the order of items in
    // checklist definitions over time don't affect the order of elements in the
    // saved progress variable. This simplifies use with Strongarm.
    ksort($progress);

    variable_set($this->getSavedProgressVariableName(), $progress);
    drupal_set_message(format_plural(
      $num_changed_items,
      '%title progress has been saved. 1 item changed.',
      '%title progress has been saved. @count items changed.',
      array('%title' => $this->title)
    ));
  }

  /**
   * Determines whether the current user has access to the checklist.
   *
   * @param string $operation
   *   The operation to test access for. Possible values are "view", "edit", and
   *   "any". Defaults to "any".
   *
   * @return bool
   *   Returns TRUE if the user has access, or FALSE if not.
   */
  public function userHasAccess($operation = 'any') {
    return checklistapi_checklist_access($this->id, $operation);
  }

}
