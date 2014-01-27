<?php
/**
 * Drupal_Sniffs_Semantics_FunctionTSniff
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Check the usage of the t() function to not escape translateable strings with back
 * slashes. Also checks that the first argument does not use string concatenation.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_Semantics_FunctionTSniff extends Drupal_Sniffs_Semantics_FunctionCall
{


    /**
     * Returns an array of function names this test wants to listen for.
     *
     * @return array
     */
    public function registerFunctionNames()
    {
        return array('t');

    }//end registerFunctionNames()


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
    public function processFunctionCall(
        PHP_CodeSniffer_File $phpcsFile,
        $stackPtr,
        $openBracket,
        $closeBracket,
        Drupal_Sniffs_Semantics_FunctionCallSniff $sniff
    ) {
        $tokens   = $phpcsFile->getTokens();
        $argument = $sniff->getArgument(1);

        if ($argument === false) {
            $error = 'Empty calls to t() are not allowed';
            $phpcsFile->addError($error, $stackPtr, 'EmptyT');
            return;
        }

        if ($tokens[$argument['start']]['code'] !== T_CONSTANT_ENCAPSED_STRING) {
            // Not a translatable string literal.
            $warning = 'Only string literals should be passed to t() where possible';
            $phpcsFile->addWarning($warning, $argument['start'], 'NotLiteralString');
            return;
        }

        if ($tokens[$argument['start']]['content'] === '""' || $tokens[$argument['start']]['content'] === "''") {
            $warning = 'Do not pass empty strings to t()';
            $phpcsFile->addWarning($warning, $argument['start'], 'EmptyString');
            return;
        }

        $concatFound = $phpcsFile->findNext(T_STRING_CONCAT, $argument['start'], $argument['end']);
        if ($concatFound !== false) {
            $error = 'Concatenating translatable strings is not allowed, use placeholders instead and only one string literal';
            $phpcsFile->addError($error, $concatFound, 'Concat');
        }

        $string = $tokens[$argument['start']]['content'];
        // Check if there is a backslash escaped single quote in the string and
        // if the string makes use of double quotes.
        if ($string{0} === "'" && strpos($string, "\'") !== false
            && strpos($string, '"') === false
        ) {
            $warn = 'Avoid backslash escaping in translatable strings when possible, use "" quotes instead';
            $phpcsFile->addWarning($warn, $argument['start'], 'BackslashSingleQuote');
            return;
        }

        if ($string{0} === '"' && strpos($string, '\"') !== false
            && strpos($string, "'") === false
        ) {
            $warn = "Avoid backslash escaping in translatable strings when possible, use '' quotes instead";
            $phpcsFile->addWarning($warn, $argument['start'], 'BackslashDoubleQuote');
        }

    }//end processFunctionCall()


}//end class

?>
