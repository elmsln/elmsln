<?php

// Print out exported items.
foreach ($themed_rows as $count => $item_row):
  print implode($separator, $item_row) . "\r\n";
endforeach;