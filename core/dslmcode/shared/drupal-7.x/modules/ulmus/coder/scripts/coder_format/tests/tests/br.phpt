<?php
TEST: Blank lines with whitespace

--INPUT--
if ($foo) {
  bar();
  
  baz();
}

--EXPECT--
if ($foo) {
  bar();

  baz();
}

--INPUT--
if ($foo) {
  bar();

  baz();
}

