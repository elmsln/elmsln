<?php
/**
 * Drupal_Sniffs_Array_ArraySniff.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Drupal_Sniffs_Array_ArraySniff.
 *
 * Checks if the array's are styled in the Drupal way.
 * - Comma after the last array element
 * - Indentation is 2 spaces for multi line array definitions
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_Array_ArraySniff implements PHP_CodeSniffer_Sniff
{


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(T_ARRAY);

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
        $lastItem = $phpcsFile->findPrevious(
            PHP_CodeSniffer_Tokens::$emptyTokens,
            ($tokens[$stackPtr]['parenthesis_closer'] - 1),
            $stackPtr,
            true
        );

        // Empty array.
        if ($lastItem === $tokens[$stackPtr]['parenthesis_opener']) {
            return;
        }

        // Inline array.
        $isInlineArray = $tokens[$tokens[$stackPtr]['parenthesis_opener']]['line'] == $tokens[$tokens[$stackPtr]['parenthesis_closer']]['line'];

        // Check if the last item in a multiline array has a "closing" comma.
        if ($tokens[$lastItem]['code'] !== T_COMMA && $isInlineArray === false
            && $tokens[($lastItem + 1)]['code'] !== T_CLOSE_PARENTHESIS
        ) {
            $phpcsFile->addWarning('A comma should follow the last multiline array item. Found: '.$tokens[$lastItem]['content'], $lastItem);
            return;
        }

        if ($tokens[$lastItem]['code'] === T_COMMA && $isInlineArray === true) {
            $phpcsFile->addWarning('Last item of an inline array must not be followed by a comma', $lastItem);
        }

        if ($isInlineArray === true) {
            // Check if this array contains at least 3 elements and exceeds the 80
            // character line length.
            if ($tokens[$tokens[$stackPtr]['parenthesis_closer']]['column'] > 80) {
                $comma1 = $phpcsFile->findNext(T_COMMA, ($stackPtr + 1), $tokens[$stackPtr]['parenthesis_closer']);
                if ($comma1 !== false) {
                    $comma2 = $phpcsFile->findNext(T_COMMA, ($comma1 + 1), $tokens[$stackPtr]['parenthesis_closer']);
                    if ($comma2 !== false) {
                        $error = 'If the line declaring an array spans longer than 80 characters, each element should be broken into its own line';
                        $phpcsFile->addError($error, $stackPtr, 'LongLineDeclaration');
                    }
                }
            }

            // Only continue for multi line arrays.
            return;
        }

        // Special case: Opening two multi line structures in one line is ugly.
        if (isset($tokens[$stackPtr]['nested_parenthesis']) === true) {
            end($tokens[$stackPtr]['nested_parenthesis']);
            $outerNesting = key($tokens[$stackPtr]['nested_parenthesis']);
            if ($tokens[$outerNesting]['line'] === $tokens[$stackPtr]['line']) {
                // We could throw a warning here that the start of the array
                // definition should be on a new line by itself, but we just ignore
                // it for now as this is not defined as standard.
                return;
            }
        }

        // Find the first token on this line.
        $firstLineColumn = $tokens[$stackPtr]['column'];
        for ($i = $stackPtr; $i >= 0; $i--) {
            // Record the first code token on the line.
            if ($tokens[$i]['code'] !== T_WHITESPACE) {
                $firstLineColumn = $tokens[$i]['column'];
                // This could be a multi line string or comment beginning with white
                // spaces.
                $trimmed = ltrim($tokens[$i]['content']);
                if ($trimmed !== $tokens[$i]['content']) {
                    $firstLineColumn = ($firstLineColumn + strpos($tokens[$i]['content'], $trimmed));
                }
            }

            // It's the start of the line, so we've found our first php token.
            if ($tokens[$i]['column'] === 1) {
                break;
            }
        }

        $lineStart = $stackPtr;
        // Iterate over all lines of this array.
        while ($lineStart < $tokens[$stackPtr]['parenthesis_closer']) {
            // Find next line start.
            $newLineStart = $lineStart;
            while ($tokens[$newLineStart]['line'] == $tokens[$lineStart]['line']) {
                $newLineStart = $phpcsFile->findNext(
                    PHP_CodeSniffer_Tokens::$emptyTokens,
                    ($newLineStart + 1),
                    ($tokens[$stackPtr]['parenthesis_closer'] + 1),
                    true
                );
                if ($newLineStart === false) {
                    break 2;
                }
            }

            if ($newLineStart === $tokens[$stackPtr]['parenthesis_closer']) {
                // End of the array reached.
                if ($tokens[$newLineStart]['column'] !== $firstLineColumn) {
                    $error = 'Array closing indentation error, expected %s spaces but found %s';
                    $data  = array(
                              $firstLineColumn - 1,
                              $tokens[$newLineStart]['column'] - 1,
                             );
                    $phpcsFile->addError($error, $newLineStart, 'ArrayClosingIndentation', $data);
                }

                break;
            }

            // Skip lines in nested structures.
            $innerNesting = end($tokens[$newLineStart]['nested_parenthesis']);
            if ($innerNesting === $tokens[$stackPtr]['parenthesis_closer']
                && $tokens[$newLineStart]['column'] !== ($firstLineColumn + 2)
            ) {
                $error = 'Array indentation error, expected %s spaces but found %s';
                $data  = array(
                          $firstLineColumn + 1,
                          $tokens[$newLineStart]['column'] - 1,
                         );
                $phpcsFile->addError($error, $newLineStart, 'ArrayIndentation', $data);
            }

            $lineStart = $newLineStart;
        }//end while

    }//end process()


}//end class

?>
