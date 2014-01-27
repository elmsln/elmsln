<?php
/**
 * Checks that else/elseif/catch statements start on a new line.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Checks that else/elseif/catch statements start on a new line.
 *
 * Unfortunately we need this sniff because
 * Drupal_Sniffs_ControlStructures_ControlSignatureSniff does not detect this.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_ControlStructures_ElseCatchNewlineSniff implements PHP_CodeSniffer_Sniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(
                T_ELSE,
                T_ELSEIF,
                T_CATCH,
               );

    }//end register()


    /**
     * Processes this test, when one of its tokens is encountered.
     *
     * @param PHP_CodeSniffer_File $phpcsFile The file being scanned.
     * @param int                  $stackPtr  The position of the current token in the
     *                                        stack passed in $tokens.
     *
     * @return void
     */
    public function process(PHP_CodeSniffer_File $phpcsFile, $stackPtr)
    {
        $tokens = $phpcsFile->getTokens();
        $prevNonWhiteSpace = $phpcsFile->findPrevious(
            PHP_CodeSniffer_Tokens::$emptyTokens,
            ($stackPtr - 1),
            null,
            true
        );

        if ($tokens[$prevNonWhiteSpace]['line'] === $tokens[$stackPtr]['line']) {
            $error = '%s must start on a new line';
            $data  = array($tokens[$stackPtr]['content']);
            $phpcsFile->addError($error, $stackPtr, 'ElseNewline', $data);
        }

    }//end process()


}//end class

?>
