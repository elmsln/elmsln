<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class ModuleBuildDependencies {

  /**
   * @see _module_build_dependencies()
   *
   * @param object[] $files
   *
   * @return object[]
   */
  public function moduleBuildDependencies($files) {
    foreach ($files as $file) {
      $graph[$file->name]['edges'] = array();
      if (isset($file->info['dependencies']) && is_array($file->info['dependencies'])) {
        foreach ($file->info['dependencies'] as $dependency) {
          $dependency_data = $this->drupalParseDependency($dependency);
          $graph[$file->name]['edges'][$dependency_data['name']] = $dependency_data;
        }
      }
    }
    $this->drupalDepthFirstSearch($graph);
    foreach ($graph as $module => $data) {
      $files[$module]->required_by = isset($data['reverse_paths'])
        ? $data['reverse_paths']
        : array();
      $files[$module]->requires = isset($data['paths'])
        ? $data['paths']
        : array();
      $files[$module]->sort = $data['weight'];
    }
    return $files;
  }

  /**
   * @see drupal_depth_first_search()
   *
   * @param $graph
   */
  private function drupalDepthFirstSearch(&$graph) {
    $state = array(
      // The order of last visit of the depth first search. This is the reverse
      // of the topological order if the graph is acyclic.
      'last_visit_order' => array(),
      // The components of the graph.
      'components' => array(),
    );
    // Perform the actual search.
    foreach ($graph as $start => $data) {
      $this->drupalDepthFirstSearchRec($graph, $state, $start);
    }

    // We do such a numbering that every component starts with 0. This is useful
    // for module installs as we can install every 0 weighted module in one
    // request, and then every 1 weighted etc.
    $component_weights = array();

    foreach ($state['last_visit_order'] as $vertex) {
      $component = $graph[$vertex]['component'];
      if (!isset($component_weights[$component])) {
        $component_weights[$component] = 0;
      }
      $graph[$vertex]['weight'] = $component_weights[$component]--;
    }
  }

  /**
   * Performs a depth-first search on a graph.
   *
   * @see _drupal_depth_first_search()
   *
   * @param array $graph
   *   A three dimensional associated graph array.
   * @param array $state
   *   An associative array. The key 'last_visit_order' stores a list of the
   *   vertices visited. The key components stores list of vertices belonging
   *   to the same the component.
   * @param string $start
   *   An arbitrary vertex where we started traversing the graph.
   * @param $component
   *   The component of the last vertex.
   */
  function drupalDepthFirstSearchRec(&$graph, &$state, $start, &$component = NULL) {
    // Assign new component for each new vertex, i.e. when not called recursively.
    if (!isset($component)) {
      $component = $start;
    }
    // Nothing to do, if we already visited this vertex.
    if (isset($graph[$start]['paths'])) {
      return;
    }
    // Mark $start as visited.
    $graph[$start]['paths'] = array();

    // Assign $start to the current component.
    $graph[$start]['component'] = $component;
    $state['components'][$component][] = $start;

    // Visit edges of $start.
    if (isset($graph[$start]['edges'])) {
      foreach ($graph[$start]['edges'] as $end => $v) {
        // Mark that $start can reach $end.
        $graph[$start]['paths'][$end] = $v;

        if (isset($graph[$end]['component']) && $component != $graph[$end]['component']) {
          // This vertex already has a component, use that from now on and
          // reassign all the previously explored vertices.
          $new_component = $graph[$end]['component'];
          foreach ($state['components'][$component] as $vertex) {
            $graph[$vertex]['component'] = $new_component;
            $state['components'][$new_component][] = $vertex;
          }
          unset($state['components'][$component]);
          $component = $new_component;
        }
        // Only visit existing vertices.
        if (isset($graph[$end])) {
          // Visit the connected vertex.
          $this->drupalDepthFirstSearchRec($graph, $state, $end, $component);

          // All vertices reachable by $end are also reachable by $start.
          $graph[$start]['paths'] += $graph[$end]['paths'];
        }
      }
    }

    // Now that any other subgraph has been explored, add $start to all reverse
    // paths.
    foreach ($graph[$start]['paths'] as $end => $v) {
      if (isset($graph[$end])) {
        $graph[$end]['reverse_paths'][$start] = $v;
      }
    }

    // Record the order of the last visit. This is the reverse of the
    // topological order if the graph is acyclic.
    $state['last_visit_order'][] = $start;
  }

  /**
   * @see drupal_parse_dependency()
   *
   * @param $dependency
   *
   * @return array
   */
  private function drupalParseDependency($dependency) {
    // We use named subpatterns and support every op that version_compare
    // supports. Also, op is optional and defaults to equals.
    $p_op = '(?P<operation>!=|==|=|<|<=|>|>=|<>)?';
    // Core version is always optional: 7.x-2.x and 2.x is treated the same.
    $p_core = '(?:' . preg_quote('7.x') . '-)?';
    $p_major = '(?P<major>\d+)';
    // By setting the minor version to x, branches can be matched.
    $p_minor = '(?P<minor>(?:\d+|x)(?:-[A-Za-z]+\d+)?)';
    $value = array();
    $parts = explode('(', $dependency, 2);
    $value['name'] = trim($parts[0]);
    if (isset($parts[1])) {
      $value['original_version'] = ' (' . $parts[1];
      foreach (explode(',', $parts[1]) as $version) {
        if (preg_match("/^\s*$p_op\s*$p_core$p_major\.$p_minor/", $version, $matches)) {
          $op = !empty($matches['operation']) ? $matches['operation'] : '=';
          if ($matches['minor'] == 'x') {
            // Drupal considers "2.x" to mean any version that begins with
            // "2" (e.g. 2.0, 2.9 are all "2.x"). PHP's version_compare(),
            // on the other hand, treats "x" as a string; so to
            // version_compare(), "2.x" is considered less than 2.0. This
            // means that >=2.x and <2.x are handled by version_compare()
            // as we need, but > and <= are not.
            if ($op == '>' || $op == '<=') {
              $matches['major']++;
            }
            // Equivalence can be checked by adding two restrictions.
            if ($op == '=' || $op == '==') {
              $value['versions'][] = array('op' => '<', 'version' => ($matches['major'] + 1) . '.x');
              $op = '>=';
            }
          }
          $value['versions'][] = array('op' => $op, 'version' => $matches['major'] . '.' . $matches['minor']);
        }
      }
    }
    return $value;
  }
}
