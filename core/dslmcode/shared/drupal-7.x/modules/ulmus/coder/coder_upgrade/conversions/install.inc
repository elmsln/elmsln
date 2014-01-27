<?php
/**
 * @file
 * Provides conversion routines applied to install files.
 *
 * These routines use the grammar parser.
 *
 * The functions in this conversion routine file correspond to topics in the
 * category roadmap at http://drupal.org/node/394070 that are marked with a
 * green check mark in the Upgrade column.
 *
 * Copyright 2009-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * The upgrades to these functions are documented at the following urls.
 *
 * Module Info / Install
 * http://drupal.org/node/224333#afile
 * http://drupal.org/node/224333#info_core_7 (this anchor does not exist on the chronological page)
 */

/**
 * Implements hook_upgrade_parser_install_alter().
 *
 * Applies finishing touches to the install file.
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_upgrade_parser_install_alter(&$reader) {
  coder_upgrade_convert_install_file_comment($reader);
}

/**
 * Adds a Doxygen style comment to install files.
 *
 * Install files must include a Doxygen style file comment.
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_convert_install_file_comment(&$reader) {
  cdp("inside " . __FUNCTION__);

  $comments = &$reader->getComments();
  foreach ($comments as &$comment) {
    if (is_array($comment) && !empty($comment)) {
      if (preg_match('#\*\s*@file#', $comment['value'])) {
        // The file already includes a file comment.
        return;
      }
    }
  }

  /*
   * A standards-compliant Drupal php file would begin with:
   * <?php
   * // $\Id: .. username Exp $ (slash added to prevent CVS from changing this line)
   *
   * ... rest of file
   *
   * Look for these types of statements in this order. Insert the file
   * comment after the Id line or the open tag (if no Id line).
   */

  $statements = &$reader->getStatements();
  if (is_null($statements)) {
    // Currently, the file must begin with an open tag.
    return;
  }
/*
  $statement = $statements->getElement(0);
  if (!is_array($statement) || empty($statement) || $statement['type'] != T_OPEN_TAG) {
    clp('ERROR: file does not begin with an open tag');
    return;
  }
*/
  $statement = $statements->getElement(1);
  if (!is_array($statement) || empty($statement) || $statement['type'] != T_COMMENT || strpos($statement['value'], '// $Id:') !== 0) {
    $position = 1;
    coder_upgrade_add_install_file_comment($reader, $position);
    return;
  }

  $statement = $statements->getElement(2);
  if (!is_array($statement) || empty($statement) || $statement['type'] != T_WHITESPACE) {
    $position = 2;
    coder_upgrade_add_install_file_comment($reader, $position);
    return;
  }

  $position = 3;
  coder_upgrade_add_install_file_comment($reader, $position);
}

function coder_upgrade_add_install_file_comment(&$reader, $position) {
  cdp("inside " . __FUNCTION__);
  global $_coder_upgrade_module_name;

  $statements = &$reader->getStatements();

  // Insert a blank line.
  $whitespace = array(
    'type' => T_WHITESPACE,
    'value' => 1,
  );
  $statements->insertElement($position, $whitespace);

  // Insert file document comment.
  $comment = array(
    'type' => T_DOC_COMMENT,
    'value' => "/**\n * @file\n * Install, update and uninstall functions for the $_coder_upgrade_module_name module.\n *\n */",
  );
  $statements->insertElement($position, $comment);
}
