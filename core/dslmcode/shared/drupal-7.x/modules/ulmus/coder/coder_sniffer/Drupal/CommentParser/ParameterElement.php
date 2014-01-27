<?php
/**
 * A class to represent param tags within a function comment.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * A class to represent param tags within a function comment.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_CommentParser_ParameterElement
    extends PHP_CodeSniffer_CommentParser_ParameterElement
{


    /**
     * Constructs a Drupal_CommentParser_ParameterElement.
     *
     * @param PHP_CodeSniffer_CommentParser_DocElement $previousElement The element
     *                                                                  previous to
     *                                                                  this one.
     * @param array                                    $tokens          The tokens
     *                                                                  that make up
     *                                                                  this element.
     * @param PHP_CodeSniffer_File                     $phpcsFile       The file that
     *                                                                  this element
     *                                                                  is in.
     */
    public function __construct(
        $previousElement,
        $tokens,
        PHP_CodeSniffer_File $phpcsFile
    ) {
        // Handle the case when a parameter type is missing.
        // If the first non-whitespace token starts with "$", then the type is
        // missing.
        if ($tokens[1]{0} === '$') {
            // Insert two fake tokens for the parameter type.
            array_unshift($tokens, 'unknown');
            array_unshift($tokens, ' ');
            parent::__construct($previousElement, $tokens, $phpcsFile);
            // Now empty the type so it will be flagged as invalid.
            $this->processSubElement('type', '', ' ');
        } else if ($tokens[1] === '...') {
            // Insert two fake tokens for the parameter type.
            array_unshift($tokens, 'unknown');
            array_unshift($tokens, ' ');
            parent::__construct($previousElement, $tokens, $phpcsFile);
        } else {
            parent::__construct($previousElement, $tokens, $phpcsFile);
        }

    }//end __construct()


}//end class

?>
