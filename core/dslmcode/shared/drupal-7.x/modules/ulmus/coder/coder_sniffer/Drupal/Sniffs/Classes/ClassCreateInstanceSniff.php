<?php
/**
 * Class create instance Test.
 *
 * PHP version 5
 *
 * @category  PHP
 * @package   PHP_CodeSniffer
 * @author    Peter Philipp <peter.philipp@cando-image.com>
 * @link      http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Class create instance Test.
 *
 * Checks the declaration of the class is correct.
 *
 * @category  PHP
 * @package   PHP_CodeSniffer
 * @author    Peter Philipp <peter.philipp@cando-image.com>
 * @link      http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_Classes_ClassCreateInstanceSniff implements PHP_CodeSniffer_Sniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(
                T_NEW,
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

        $nextParenthesis = $phpcsFile->findNext(array(T_OPEN_PARENTHESIS,T_SEMICOLON), $stackPtr, null, false, null, true);
        if ($tokens[$nextParenthesis]['code'] != T_OPEN_PARENTHESIS || $tokens[$nextParenthesis]['line'] != $tokens[$stackPtr]['line']) {
            $error  = 'Calling class constructors must always include parentheses';
            $phpcsFile->addError($error, $nextParenthesis);
            return;
        }
        
        if ($tokens[$nextParenthesis-1]['code'] == T_WHITESPACE) {
            $error  = 'Between the class name and the opening parenthesis spaces are not welcome';
            $phpcsFile->addError($error, $nextParenthesis-1);
            return;
        }
    }//end process()


}//end class

?>
