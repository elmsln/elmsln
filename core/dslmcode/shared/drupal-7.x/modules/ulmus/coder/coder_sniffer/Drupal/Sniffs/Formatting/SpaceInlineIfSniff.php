<?php
/**
 * Drupal_Sniffs_Formatting_SpaceInlineIfSniff.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Checks short if caluses with "?" and ":" operator spacing.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_Formatting_SpaceInlineIfSniff implements PHP_CodeSniffer_Sniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(
                T_INLINE_THEN,
                T_INLINE_ELSE,
               );

    }//end register()


    /**
     * Processes this test, when one of its tokens is encountered.
     *
     * @param PHP_CodeSniffer_File $phpcsFile The file being scanned.
     * @param int                  $stackPtr  The position of the current token in
     *                                        the stack passed in $tokens.
     *
     * @return void
     */
    public function process(PHP_CodeSniffer_File $phpcsFile, $stackPtr)
    {
        $tokens   = $phpcsFile->getTokens();
        $operator = $tokens[$stackPtr]['content'];

        // Handle the short ternary operator (?:) introduced in PHP 5.3.
        $previous = $phpcsFile->findPrevious(T_WHITESPACE, ($stackPtr - 1), null, true);
        if ($tokens[$previous]['code'] === T_INLINE_THEN) {
            if ($previous !== ($stackPtr - 1)) {
                $error = 'There must be no space between ? and :';
                $phpcsFile->addError($error, $stackPtr, 'SpaceInlineElse');
            }

            if ($tokens[($stackPtr + 1)]['code'] !== T_WHITESPACE) {
                $error = "Expected 1 space after \"$operator\"; 0 found";
                $phpcsFile->addError($error, $stackPtr, 'NoSpaceAfter');
            } else if (strlen($tokens[($stackPtr + 1)]['content']) !== 1) {
                $found = strlen($tokens[($stackPtr + 1)]['content']);
                $error = 'Expected 1 space after "%s"; %s found';
                $data  = array(
                          $operator,
                          $found,
                         );
                $phpcsFile->addError($error, $stackPtr, 'SpacingAfter', $data);
            }

            return;
        }//end if

        $next = $phpcsFile->findNext(T_WHITESPACE, ($stackPtr + 1), null, true);
        if ($tokens[$next]['code'] === T_INLINE_ELSE) {
            if ($tokens[($stackPtr - 1)]['code'] !== T_WHITESPACE) {
                $error = "Expected 1 space before \"$operator\"; 0 found";
                $phpcsFile->addError($error, $stackPtr, 'NoSpaceBefore');
            } else if (strlen($tokens[($stackPtr - 1)]['content']) !== 1) {
                $found = strlen($tokens[($stackPtr - 1)]['content']);
                $error = 'Expected 1 space before "%s"; %s found';
                $data  = array(
                          $operator,
                          $found,
                         );
                $phpcsFile->addError($error, $stackPtr, 'SpacingBefore', $data);
            }

            return;
        }

        // Reuse the standard operator sniff now.
        $sniff = new Squiz_Sniffs_WhiteSpace_OperatorSpacingSniff();
        $sniff->process($phpcsFile, $stackPtr);

    }//end process()


}//end class

?>
