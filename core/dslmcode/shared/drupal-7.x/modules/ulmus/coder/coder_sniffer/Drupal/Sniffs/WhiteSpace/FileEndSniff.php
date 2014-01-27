<?php
/**
 * Drupal_Sniffs_WhiteSpace_FileEndSniff.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @author   Klaus Purer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Drupal_Sniffs_WhiteSpace_FileEndSniff.
 *
 * Checks that a file ends in exactly one single new line character.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @author   Klaus Purer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_WhiteSpace_FileEndSniff implements PHP_CodeSniffer_Sniff
{

    /**
     * A list of tokenizers this sniff supports.
     *
     * @var array
     */
    public $supportedTokenizers = array(
                                   'PHP',
                                   'JS',
                                   'CSS',
                                  );


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(
                T_OPEN_TAG,
                T_INLINE_HTML,
               );

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
        // We want to run this method only once per file, so we remember if this has
        // been called already.
        static $called = array();
        if (isset($called[$phpcsFile->getFilename()]) === false) {
            $called[$phpcsFile->getFilename()] = true;
            // Retrieve the raw file content, as the tokens do not work consistently
            // for different file types (CSS and javascript files have additional
            // artifical tokens at the end for example).
            $filename = $phpcsFile->getFilename();

            // file_get_contents requires a file path, but some programs will pass
            // in info via STDIN. Change the filename to something file_get_contents
            // will understand.
            if ($filename == 'STDIN') {
                $filename = 'php://stdin';
            }
            $content = file_get_contents($filename);
            $error = false;
            $lastChar = substr($content, -1);
            // There must be a \n character at the end of the last token.
            if ($lastChar !== $phpcsFile->eolChar) {
                $error = true;
            }
            // There must be only one \n character at the end of the file.
            else if (substr($content, -2, 1) === $phpcsFile->eolChar) {
                $error = true;
            }

            if ($error === true) {
                $error = 'Files must end in a single new line character';
                $phpcsFile->addError($error, $phpcsFile->numTokens - 1, 'FileEnd');
            }
        }//end if

    }//end process()


}//end class

?>
