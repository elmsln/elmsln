<?php

/**
 * @file
 * Advanced aggregation bundler module.
 */

/**
 * @addtogroup advagg_hooks
 * @{
 */

/**
 * Implements hook_advagg_build_aggregate_plans_alter().
 */
function advagg_bundler_advagg_build_aggregate_plans_alter(&$files, &$modified, $type) {
  // Get max number of sub aggregates to create.
  if ($type === 'css') {
    $max = variable_get('advagg_bundler_max_css', ADVAGG_BUNDLER_MAX_CSS);
  }
  if ($type === 'js') {
    $max = variable_get('advagg_bundler_max_js', ADVAGG_BUNDLER_MAX_JS);
  }
  // If bundles are disabled then do not do any more processing.
  if (empty($max)) {
    return;
  }
  // If bundler is disabled then do not do any more processing.
  if (!advagg_bundler_enabled()) {
    return;
  }

  $final_groupings = array();
  $total_count = 0;
  foreach ($files as $data) {
    // Preserve the order while grouping.
    $last_group = '';
    $counter = 0;
    $groupings = array();
    foreach ($data['files'] as $fileinfo) {
      // Assign each file to their group.
      $group = advagg_bundler_analysis($fileinfo['data']);
      $fileinfo['bundler'] = $group;

      // Set $last_group if this is the first run of this foreach loop.
      if (empty($last_group)) {
        $last_group = $group['group_hash'];
      }

      if ($last_group != $group['group_hash']) {
        // Bump Counter if group has changed from the last one.
        ++$counter;
        $last_group = $group['group_hash'];
        $modified = TRUE;
      }
      $groupings[$counter][] = $fileinfo;
    }
    // Make sure we didn't go over the max; if we did merge the smallest bundles
    // together.
    advagg_bundler_merge($groupings, $max);
    $total_count += count($groupings);
    // Add to the final groupings array.
    $final_groupings[] = $groupings;
  }

  // Try to shrink bundles if they are still too big.
  while ($total_count > $max) {
    $remerge_candidate = NULL;
    $remerge_key = NULL;
    $total_count = 0;
    foreach ($final_groupings as $key => $groupings) {
      if (count($groupings) > 1) {
        if (is_null($remerge_candidate)) {
          $remerge_candidate = $groupings;
          $remerge_key = $key;
        }
        elseif (count($remerge_candidate) > count($groupings)) {
          $remerge_candidate = $groupings;
          $remerge_key = $key;
        }
      }
    }
    if (is_null($remerge_candidate)) {
      break;
    }
    advagg_bundler_merge($remerge_candidate, count($remerge_candidate) - 1);
    $final_groupings[$remerge_key] = $remerge_candidate;

    $total_count = 0;
    foreach ($final_groupings as $key => $groupings) {
      $total_count += count($groupings);
    }
  }

  // Replace $files array with new aggregate filenames.
  $files = advagg_generate_filenames($final_groupings, $type);
}

/**
 * @} End of "addtogroup advagg_hooks".
 */

/**
 * Merge bundles together if too many where created.
 *
 * This preserves the order.
 *
 * @param array $groupings
 *   Array of requested groups.
 * @param int $max
 *   Max number of grouping.
 */
function advagg_bundler_merge(array &$groupings, $max) {
  $group_count = count($groupings);

  if (!empty($max)) {
    // Keep going till array has been merged to the desired size.
    while ($group_count > $max) {
      // Get array sizes.
      // Counts the number of files that are placed into each bundle.
      $counts = array();
      $group_hash_counts = array();
      foreach ($groupings as $key => $values) {
        // Get the group hash counts.
        $file_size = 0;
        $group_hash_counts[$key] = 0;
        foreach ($values as $data) {
          $file_size += empty($data['bundler']['filesize_processed']) ? $data['bundler']['filesize'] : $data['bundler']['filesize_processed'];
          $group_hash_counts[$key] += intval(substr($data['bundler']['group_hash'], 0, 8));
        }
        if (variable_get('advagg_bundler_grouping_logic', ADVAGG_BUNDLER_GROUPING_LOGIC) == 0) {
          $counts[$key] = count($values);
        }
        elseif (variable_get('advagg_bundler_grouping_logic', ADVAGG_BUNDLER_GROUPING_LOGIC) == 1) {
          $counts[$key] = $file_size;
        }
      }

      // Create mapping.
      // Calculates the file count of potential merges. It only merges with
      // neighbors in order to preserve execution order.
      $map = array();
      $prev_key = NULL;
      foreach ($counts as $key => $val) {
        // First run of the foreach loop; populate prev key/values and continue.
        // We can't merge with the previous group in this case.
        if (is_null($prev_key)) {
          $prev_key = $key;
          $prev_val = $val;
          continue;
        }

        // Array key ($prev_val + $val) is the file count of this new group if
        // these 2 groups ($prev_key, $key) where to be merged together.
        $map[] = array(
          ($prev_val + $val) => array($prev_key, $key),
        );

        // Prep for next run.
        $prev_key = $key;
        $prev_val = $val;
      }

      $group_hash_map = array();
      $prev_key = NULL;
      foreach ($group_hash_counts as $key => $val) {
        // First run of the foreach loop; populate prev key/values and continue.
        // We can't merge with the previous group in this case.
        if (is_null($prev_key)) {
          $prev_key = $key;
          $prev_val = $val;
          continue;
        }

        // Array value ($prev_val + $val) is the hash count of this new group if
        // these 2 groups where to be merged together.
        $group_hash_map[$prev_key . ' ' . $key] = $prev_val + $val;

        // Prep for next run.
        $prev_key = $key;
        $prev_val = $val;
      }

      // Get best merge candidate.
      // We are looking for the smallest file count. $min is populated with a
      // large number (15 bits) so it won't be selected in this process.
      $min = PHP_INT_MAX;
      $first = NULL;
      $last = NULL;
      $last_min = NULL;
      foreach ($map as $v) {
        foreach ($v as $key => $values) {
          $min = min($min, $key);
          // If the min value (number of files in the proposed merged bundle) is
          // the same as the key, then get the 2 bundle keys that generated this
          // new min value.
          if ($min == $key) {
            if ($last_min == $min && !is_null($first) && !is_null($last)) {
              list($new_first, $new_last) = $values;
              // All things being equal pick the smaller count on the hash.
              if ($group_hash_map[$first . ' ' . $last] > $group_hash_map[$new_first . ' ' . $new_last]) {
                $first = $new_first;
                $last = $new_last;
              }
            }
            else {
              list($first, $last) = $values;
            }
            $last_min = $min;
          }
        }
      }

      // Create the new merged set.
      $a = $groupings[$first];
      $b = $groupings[$last];
      $new_set = array_merge($a, $b);

      // Rebuild the array with the new set in the correct place.
      $new_groupings = array();
      foreach ($groupings as $key => $files) {
        if ($key == $first) {
          $new_groupings[$first . ' ' . $last] = $new_set;
        }
        elseif ($key != $last) {
          $new_groupings[$key] = $files;
        }
      }
      $groupings = $new_groupings;
      --$group_count;
    }
  }

  // Error prevention below.
  // Make sure there isn't a group that has all files that don't exist or empty.
  $bad_groups = array();
  foreach ($groupings as $key => $group) {
    $missing_counter = 0;
    foreach ($group as $data) {
      if (empty($data['bundler']['filesize'])) {
        ++$missing_counter;
      }
    }

    // If all files are missing/empty in this group then it is a bad set.
    if ($missing_counter == count($group)) {
      $bad_groups[$key] = TRUE;
    }
  }

  // Add the bad groups to the smallest grouping in this set.
  if (!empty($bad_groups)) {
    $merge_candidate_key = '';
    $merge_candidate_count = PHP_INT_MAX;
    $bad_group = array();
    foreach ($groupings as $key => $group) {
      if (isset($bad_groups[$key])) {
        // Merge all bad groups into one.
        $bad_group = array_merge($bad_group, $group);

        // Delete the bad group from the master set.
        unset($groupings[$key]);
        continue;
      }

      // Find the smallest good grouping.
      $min = min($merge_candidate_count, count($group));
      if ($min < $merge_candidate_count) {
        $merge_candidate_key = $key;
        $merge_candidate_count = $min;
      }
    }

    // Move the bad files into the smallest good group.
    $new_set = isset($groupings[$merge_candidate_key]) ? $groupings[$merge_candidate_key] : array();
    $new_set = array_merge($new_set, $bad_group);
    $groupings[$merge_candidate_key] = $new_set;
  }
}
