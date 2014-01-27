<?php
/**
 * Drupal_Sniffs_ControlStructures_TemplateControlStructureSniff.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Checks that control structures in template files use the alternative syntax with
 * ":" and end statements.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_ControlStructures_TemplateControlStructureSniff implements PHP_CodeSniffer_Sniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(
                T_IF,
                T_WHILE,
                T_SWITCH,
                T_ELSE,
                T_ELSEIF,
                T_FOR,
                T_FOREACH,
               );

    }//end register()


    /**
     * Processes this test, when one of its tokens is encountered.
     *
     * @param PHP_CodeSniffer_File $phpcsFile The file being scanned.
     * @param int                  $stackPtr  The position of the current token
     *                                        in the stack passed in $tokens.
     *
     * @return void
     */
    public function process(PHP_CodeSniffer_File $phpcsFile, $stackPtr)
    {
        // Only process this sniff for template files.
        $fileExtension = strtolower(substr($phpcsFile->getFilename(), -8));
        if ($fileExtension !== '.tpl.php') {
            return;
        }

        $tokens = $phpcsFile->getTokens();

        // If there is a scope opener, then there is a opening curly brace.
        if (isset($tokens[$stackPtr]['scope_opener']) === true
            && $tokens[$tokens[$stackPtr]['scope_opener']]['code'] !== T_COLON
        ) {
            $error = 'The control statement should use the ":" alternative syntax instead of curly braces in template files';
            $phpcsFile->addError($error, $stackPtr, 'CurlyBracket');
        }

    }//end process()


}//end class

?>
