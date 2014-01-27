<?php
/**
 * Drupal_Sniffs_Semantics_FunctionCall.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Helper class to sniff for specific function calls.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
abstract class Drupal_Sniffs_Semantics_FunctionCall implements PHP_CodeSniffer_Sniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        // We do not listen for tokens, but for specific function calls.
        Drupal_Sniffs_Semantics_FunctionCallSniff::registerListener($this);
        return array();

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
        // Empty default implementation, because processFunctionCall() is used.

    }//end process()


    /**
     * Processes this function call.
     *
     * @param PHP_CodeSniffer_File $phpcsFile
     *   The file being scanned.
     * @param int $stackPtr
     *   The position of the function call in the stack.
     * @param int $openBracket
     *   The position of the opening parenthesis in the stack.
     * @param int $closeBracket
     *   The position of the closing parenthesis in the stack.
     * @param Drupal_Sniffs_Semantics_FunctionCallSniff $sniff
     *   Can be used to retreive the function's arguments with the getArgument()
     *   method.
     *
     * @return void
     */
    public abstract function processFunctionCall(
        PHP_CodeSniffer_File $phpcsFile,
        $stackPtr,
        $openBracket,
        $closeBracket,
        Drupal_Sniffs_Semantics_FunctionCallSniff $sniff
    );


}//end class

?>
