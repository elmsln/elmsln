<?php
/**
 * Drupal_Sniffs_Strings_ConcatenationSpacingSniff.
 *
 * PHP version 5
 *
 * @category  PHP
 * @package   PHP_CodeSniffer
 * @author    Peter Philipp <peter.philipp@cando-image.com>
 * @link      http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Drupal_Sniffs_Strings_ConcatenationSpacingSniff.
 *
 * Makes sure there are the needed spaces between the concatenation operator (.) and
 * the strings being concatenated.
 *
 * @category  PHP
 * @package   PHP_CodeSniffer
 * @author    Peter Philipp <peter.philipp@cando-image.com>
 * @link      http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_Strings_ConcatenationSpacingSniff implements PHP_CodeSniffer_Sniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(T_STRING_CONCAT);

    }//end register()


    /**
     * Processes this test, when one of its tokens is encountered.
     */
    public function process(PHP_CodeSniffer_File $phpcsFile, $stackPtr)
    {
        $tokens = $phpcsFile->getTokens();
        if ($tokens[($stackPtr - 1)]['code'] !== T_WHITESPACE || $tokens[($stackPtr + 1)]['code'] !== T_WHITESPACE) {
            $message = 'Concat operator must be surrounded by spaces';
            $phpcsFile->addError($message, $stackPtr, 'Missing');
        }
    }
}//end class

?>
