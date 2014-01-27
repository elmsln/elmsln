<?php
/**
 * Drupal_Sniffs_CSS_IndentationSniff.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Copied from Squiz_Sniffs_CSS_IndentationSniff. Unfortunately we cannot use that
 * class directly because it has the 4 spaces condition hardcoded.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_CSS_IndentationSniff implements PHP_CodeSniffer_Sniff
{

    /**
     * A list of tokenizers this sniff supports.
     *
     * @var array
     */
    public $supportedTokenizers = array('CSS');

    /**
     * Number of white spaces that should be used as indentation level.
     *
     * @var int
     */
    public $indent = 2;


    /**
     * Returns the token types that this sniff is interested in.
     *
     * @return array(int)
     */
    public function register()
    {
        return array(T_OPEN_TAG);

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

        $numTokens   = (count($tokens) - 2);
        $currentLine = 0;
        $indentLevel = 0;
        $nested = false;
        for ($i = 1; $i < $numTokens; $i++) {
            if ($tokens[$i]['code'] === T_COMMENT) {
                // Dont check the indent of comments.
                continue;
            }

            if ($tokens[$i]['code'] === T_OPEN_CURLY_BRACKET) {
                $indentLevel++;
                // Check for nested style definitions as, for example, in @media style rules.
                $end = $tokens[$i]['bracket_closer'];
                $nested = $phpcsFile->findNext(T_OPEN_CURLY_BRACKET, ($stackPtr + 1), $end);
            } else if ($tokens[$i + 1]['code'] === T_CLOSE_CURLY_BRACKET) {
                $indentLevel--;
            }

            if ($tokens[$i]['line'] === $currentLine) {
                continue;
            }

            // We started a new line, so check indent.
            if ($tokens[$i]['code'] === T_WHITESPACE) {
                $content     = str_replace($phpcsFile->eolChar, '', $tokens[$i]['content']);
                $foundIndent = strlen($content);
            } else {
                $foundIndent = 0;
            }

            $expectedIndent = ($indentLevel * $this->indent);
            if ($expectedIndent > 0 && strpos($tokens[$i]['content'], $phpcsFile->eolChar) !== false) {
                if ($nested === false) {
                    $error = 'Blank lines are not allowed in class definitions';
                    $phpcsFile->addError($error, $i, 'BlankLine');
                }
            } else if ($foundIndent !== $expectedIndent) {
                $error = 'Line indented incorrectly; expected %s spaces, found %s';
                $data  = array(
                          $expectedIndent,
                          $foundIndent,
                         );
                $phpcsFile->addError($error, $i, 'Incorrect', $data);
            }

            $currentLine = $tokens[$i]['line'];
        }//end foreach

    }//end process()

}//end class
?>
