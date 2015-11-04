<?php

// Print out header row, if option was selected.
if ($options['header']) {
  print implode($separator, $header) . "\r\n";
}
