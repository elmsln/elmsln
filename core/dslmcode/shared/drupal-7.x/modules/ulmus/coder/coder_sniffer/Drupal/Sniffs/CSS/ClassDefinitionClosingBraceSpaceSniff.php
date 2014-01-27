<?php
/**
 * Drupal_Sniffs_CSS_ClassDefinitionClosingBraceSpaceSniff.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Ensure that there is exactly one new line before a class closing brace.
 * Copied from Squiz_Sniffs_CSS_ClassDefinitionClosingBraceSpaceSniff because of a
 * bug: https://pear.php.net/bugs/bug.php?id=19283
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_CSS_ClassDefinitionClosingBraceSpaceSniff implements PHP_CodeSniffer_Sniff
{

    /**
     * A list of tokenizers this sniff supports.
     *
     * @var array
     */
    public $supportedTokenizers = array('CSS');


    /**
     * Returns the token types that this sniff is interested in.
     *
     * @return array(int)
     */
    public function register()
    {
        return array(T_CLOSE_CURLY_BRACKET);

    }//end register()


    /**
     * Processes the tokens that this sniff is interested in.
     *
     * @param PHP_CodeSniffer_File $phpcsFile The file where the token was found.
     * @param int                  $stackPtr  The position in the stack where
     *                                        the token was found.
     *
     * @return void
     */
    public function process(PHP_CodeSniffer_File $phpcsFile, $stackPtr)
    {
        $tokens = $phpcsFile->getTokens();

        // Do not check nested style definitions as, for example, in @media style rules.
        $start = $tokens[$stackPtr]['bracket_opener'];
        $nested = $phpcsFile->findPrevious(T_CLOSE_CURLY_BRACKET, ($stackPtr - 1), $start);
        if ($nested !== false) {
            return;
        }

        $prev = $phpcsFile->findPrevious(PHP_CodeSniffer_Tokens::$emptyTokens, ($stackPtr - 1), null, true);
        if ($prev !== false && $tokens[$prev]['line'] !== ($tokens[$stackPtr]['line'] - 1)) {
            $error = 'Expected exactly one new line before closing brace of class definition';
            $phpcsFile->addError($error, $stackPtr, 'SpacingBeforeClose');
        }

    }//end process()


}//end class

?>
