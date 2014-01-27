<?php
/**
 * Drupal_Sniffs_Semantics_ConstantNameSniff
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Checks that constants introduced with define() in module files start with the
 * module's name.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_Semantics_ConstantNameSniff extends Drupal_Sniffs_Semantics_FunctionCall
{


    /**
     * Returns an array of function names this test wants to listen for.
     *
     * @return array
     */
    public function registerFunctionNames()
    {
        return array('define');

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
        $fileExtension = strtolower(substr($phpcsFile->getFilename(), -6));
        // Only check in *.module files.
        if ($fileExtension !== 'module') {
            return;
        }

        $tokens   = $phpcsFile->getTokens();
        $argument = $sniff->getArgument(1);
        if ($tokens[$argument['start']]['code'] !== T_CONSTANT_ENCAPSED_STRING) {
            // Not a string literal, so this is some obscure constant that we ignore.
            return;
        }

        $moduleName    = substr(basename($phpcsFile->getFilename()), 0, -7);
        $expectedStart = strtoupper($moduleName);
        // Remove the quotes around the string litral.
        $constant = substr($tokens[$argument['start']]['content'], 1, -1);
        if (strpos($constant, $expectedStart) !== 0) {
            $warning = 'All constants defined by a module must be prefixed with the module\'s name, expected "%s" but found "%s"';
            $data  = array(
                      $expectedStart."_$constant",
                      $constant,
                     );
            $phpcsFile->addWarning($warning, $stackPtr, 'ConstantStart', $data);
        }

    }//end processFunctionCall()


}//end class

?>
