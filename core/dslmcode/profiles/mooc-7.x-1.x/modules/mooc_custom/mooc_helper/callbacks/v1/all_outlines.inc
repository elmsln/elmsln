<?php

/**
 * Return a list of the books in this site.
 */
function mooc_helper_elmsln_api_callback_all_outlines() {
  global $_elmsln;
  $outlines = book_get_books();
  return array(
    'all_outlines' => TRUE,
    'outlines' => $outlines,
    'message' => "Listing of outlines returned successfully",
  );
}
