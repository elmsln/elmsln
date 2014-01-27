<?php

/**
 * Use this hook to define a list of paths that should be checked
 * for accessibility using TestSwarm.
 */
function hook_accessibility_testswarm_test() {
  return array('my/path',
               'another/path',
               'my/amazing/path'
               );
}