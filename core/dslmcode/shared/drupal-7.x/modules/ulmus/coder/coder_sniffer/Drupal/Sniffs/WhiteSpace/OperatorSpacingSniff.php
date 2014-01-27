<?php
/**
 * Drupal_Sniffs_WhiteSpace_OperatorSpacingSniff.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Overrides Squiz_Sniffs_WhiteSpace_OperatorSpacingSniff to not check inline if/then
 * statements because those are handled by
 * Drupal_Sniffs_Formatting_SpaceInlineIfSniff.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_WhiteSpace_OperatorSpacingSniff extends Squiz_Sniffs_WhiteSpace_OperatorSpacingSniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        $comparison = PHP_CodeSniffer_Tokens::$comparisonTokens;
        $operators  = PHP_CodeSniffer_Tokens::$operators;
        $assignment = PHP_CodeSniffer_Tokens::$assignmentTokens;

        return array_unique(
            array_merge($comparison, $operators, $assignment)
        );

    }//end register()


}//end class

?>
