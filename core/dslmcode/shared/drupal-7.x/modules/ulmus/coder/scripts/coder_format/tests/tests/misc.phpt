<?php
TEST: Miscellaneous (split me!)

--INPUT--
if ($foo) {
  if ($bar) {
    // Trall!
  }
}

--INPUT--
foo(
  $bar
);

