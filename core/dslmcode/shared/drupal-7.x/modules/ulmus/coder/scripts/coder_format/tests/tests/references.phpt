<?php
TEST: Assignments by reference

--INPUT--
function &foo() {
  return;
}

--INPUT--
function foo(&$node, $bar, $baz) {
  return;
}

--INPUT--
function foo() {
  $bar = &$baz;
  return;
}

--INPUT--
function foo($foo, $bar) {
  if ($foo & $bar) {
    return $bar = $baz;
  }
}

