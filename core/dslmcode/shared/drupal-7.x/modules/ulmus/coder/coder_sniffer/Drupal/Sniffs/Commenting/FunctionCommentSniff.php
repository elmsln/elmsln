<?php
/**
 * Parses and verifies the doc comments for functions.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Parses and verifies the doc comments for functions. Largely copied from
 * Squiz_Sniffs_Commenting_FunctionCommentSniff.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_Sniffs_Commenting_FunctionCommentSniff implements PHP_CodeSniffer_Sniff
{

    /**
     * The name of the method that we are currently processing.
     *
     * @var string
     */
    private $_methodName = '';

    /**
     * The position in the stack where the fucntion token was found.
     *
     * @var int
     */
    private $_functionToken = null;

    /**
     * The position in the stack where the class token was found.
     *
     * @var int
     */
    private $_classToken = null;

    /**
     * The function comment parser for the current method.
     *
     * @var Drupal_CommentParser_FunctionCommentParser
     */
    protected $commentParser = null;

    /**
     * The current PHP_CodeSniffer_File object we are processing.
     *
     * @var PHP_CodeSniffer_File
     */
    protected $currentFile = null;

    /**
     * A map of invalid data types to valid ones for param and return documentation.
     *
     * @var array
     */
    protected $invalidTypes = array(
                               'Array' => 'array',
                               'boolean' => 'bool',
                               'integer' => 'int',
                               'str' => 'string',
                              );


    /**
     * Returns an array of tokens this test wants to listen for.
     *
     * @return array
     */
    public function register()
    {
        return array(T_FUNCTION);

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
        $this->currentFile = $phpcsFile;

        $tokens = $phpcsFile->getTokens();

        $find = array(
                 T_COMMENT,
                 T_DOC_COMMENT,
                 T_CLASS,
                 T_FUNCTION,
                 T_OPEN_TAG,
                );

        $commentEnd = $phpcsFile->findPrevious($find, ($stackPtr - 1));

        if ($commentEnd === false) {
            return;
        }

        // If the token that we found was a class or a function, then this
        // function has no doc comment.
        $code = $tokens[$commentEnd]['code'];

        if ($code === T_COMMENT) {
            // The function might actually be missing a comment, and this last comment
            // found is just commenting a bit of code on a line. So if it is not the
            // only thing on the line, assume we found nothing.
            $prevContent = $phpcsFile->findPrevious(PHP_CodeSniffer_Tokens::$emptyTokens, $commentEnd);
            if ($tokens[$commentEnd]['line'] === $tokens[$commentEnd]['line']) {
                $error = 'Missing function doc comment';
                $phpcsFile->addError($error, $stackPtr, 'Missing');
            } else {
                $error = 'You must use "/**" style comments for a function comment';
                $phpcsFile->addError($error, $stackPtr, 'WrongStyle');
            }
            return;
        } else if ($code !== T_DOC_COMMENT) {
            $error = 'Missing function doc comment';
            $phpcsFile->addError($error, $stackPtr, 'Missing');
            return;
        } else if (trim($tokens[$commentEnd]['content']) !== '*/') {
            $error = 'Wrong function doc comment end; expected "*/", found "%s"';
            $phpcsFile->addError($error, $commentEnd, 'WrongEnd', array(trim($tokens[$commentEnd]['content'])));
            return;
        }

        // If there is any code between the function keyword and the doc block
        // then the doc block is not for us.
        $ignore    = PHP_CodeSniffer_Tokens::$scopeModifiers;
        $ignore[]  = T_STATIC;
        $ignore[]  = T_WHITESPACE;
        $ignore[]  = T_ABSTRACT;
        $ignore[]  = T_FINAL;
        $prevToken = $phpcsFile->findPrevious($ignore, ($stackPtr - 1), null, true);
        if ($prevToken !== $commentEnd) {
            $phpcsFile->addError('Missing function doc comment', $stackPtr, 'Missing');
            return;
        }

        $this->_functionToken = $stackPtr;

        $this->_classToken = null;
        foreach ($tokens[$stackPtr]['conditions'] as $condPtr => $condition) {
            if ($condition === T_CLASS || $condition === T_INTERFACE) {
                $this->_classToken = $condPtr;
                break;
            }
        }

        // If the first T_OPEN_TAG is right before the comment and does not immediately precede the function
        // probably a file comment.
        $commentStart = ($phpcsFile->findPrevious(T_DOC_COMMENT, ($commentEnd - 1), null, true) + 1);
        $prevToken    = $phpcsFile->findPrevious(T_WHITESPACE, ($commentStart - 1), null, true);
        if ($tokens[$prevToken]['code'] === T_OPEN_TAG) {
            // Is this the first open tag
            if (($stackPtr === 0 || $phpcsFile->findPrevious(T_OPEN_TAG, ($prevToken - 1)) === false)
                && (($tokens[$commentEnd]['line'] + 1) !== $tokens[$stackPtr]['line'])) {
                $phpcsFile->addError('Missing function doc comment', $stackPtr, 'Missing');
                return;
            }
        }

        $commentString     = $phpcsFile->getTokensAsString($commentStart, ($commentEnd - $commentStart + 1));
        $this->_methodName = $phpcsFile->getDeclarationName($stackPtr);

        try {
            $this->commentParser = new Drupal_CommentParser_FunctionCommentParser($commentString, $phpcsFile);
            $this->commentParser->parse();
        } catch (PHP_CodeSniffer_CommentParser_ParserException $e) {
            $line = ($e->getLineWithinComment() + $commentStart);
            $phpcsFile->addError($e->getMessage(), $line, 'FailedParse');
            return;
        }

        $comment = $this->commentParser->getComment();
        if (is_null($comment) === true) {
            $error = 'Function doc comment is empty';
            $phpcsFile->addError($error, $commentStart, 'Empty');
            return;
        }

        // The first line of the comment should just be the /** code.
        $eolPos    = strpos($commentString, $phpcsFile->eolChar);
        $firstLine = substr($commentString, 0, $eolPos);
        if ($firstLine !== '/**') {
            $error = 'The open comment tag must be the only content on the line';
            $phpcsFile->addError($error, $commentStart, 'ContentAfterOpen');
        }

        // Check that the comment is imidiately before the function definition.
        if (($tokens[$commentEnd]['line'] + 1) !== $tokens[$stackPtr]['line']) {
            $error = 'Function doc comment must end on the line before the function definition';
            $phpcsFile->addError($error, $commentEnd, 'EmptyLinesAfterDoc');
        }

        $this->processParams($commentStart);
        $this->processReturn($commentStart, $commentEnd);
        $this->processThrows($commentStart);
        $this->processSees($commentStart);

        // Check if hook implementation doc is formated correctly.
        if (preg_match('/^[\s]*Implement[^\n]+?hook_[^\n]+/i', $comment->getShortComment(), $matches)) {
            $formattingIssue = 0;
            if (!strstr($matches[0], 'Implements ')) {
                $formattingIssue++;
            }
            if (!preg_match('/ hook_[a-zA-Z0-9_]+\(\)( for [a-z0-9_]+(\(\)|\.tpl\.php))?\.$/', $matches[0])) {
                $formattingIssue++;
            }
            if ($formattingIssue) {
                $phpcsFile->addWarning('Format should be "* Implements hook_foo().", "* Implements hook_foo_BAR_ID_bar() for xyz_bar().", or "* Implements hook_foo_BAR_ID_bar() for xyz_bar.tpl.php.".', $commentStart + 1);
            } else {
                // Check that a hook implementation does not duplicate @param and
                // @return documentation.
                $params = $this->commentParser->getParams();
                if (empty($params) === false) {
                    $param    = array_shift($params);
                    $errorPos = ($param->getLine() + $commentStart);
                    $warn     = 'Hook implementations should not duplicate @param documentation';
                    $phpcsFile->addWarning($warn, $errorPos, 'HookParamDoc');
                }

                $return = $this->commentParser->getReturn();
                if ($return !== null) {
                    $errorPos = ($commentStart + $this->commentParser->getReturn()->getLine());
                    $warn     = 'Hook implementations should not duplicate @return documentation';
                    $phpcsFile->addWarning($warn, $errorPos, 'HookReturnDoc');
                }
            }//end if
        }//end if

        // Check for a comment description.
        $short = $comment->getShortComment();
        if (trim($short) === '') {
            $error = 'Missing short description in function doc comment';
            $phpcsFile->addError($error, $commentStart, 'MissingShort');
            return;
        }

        // No extra newline before short description.
        $newlineCount = 0;
        $newlineSpan  = strspn($short, $phpcsFile->eolChar);
        if ($short !== '' && $newlineSpan > 0) {
            $line  = ($newlineSpan > 1) ? 'newlines' : 'newline';
            $error = "Extra $line found before function comment short description";
            $phpcsFile->addError($error, ($commentStart + 1));
            return;
        }

        $newlineCount = (substr_count($short, $phpcsFile->eolChar) + 1);

        // Exactly one blank line between short and long description.
        $long = $comment->getLongComment();
        if (empty($long) === false) {
            $between        = $comment->getWhiteSpaceBetween();
            $newlineBetween = substr_count($between, $phpcsFile->eolChar);
            if ($newlineBetween !== 2) {
                $error = 'There must be exactly one blank line between descriptions in function comment';
                $phpcsFile->addError($error, ($commentStart + $newlineCount + 1), 'SpacingAfterShort');
            }

            $newlineCount += $newlineBetween;
        }

        // Short description must be single line and end with a full stop.
        $testShort = trim($short);
        $lastChar  = $testShort[(strlen($testShort) - 1)];
        if (substr_count($testShort, $phpcsFile->eolChar) !== 0) {
            $error = 'Function comment short description must be on a single line';
            $phpcsFile->addError($error, ($commentStart + 1), 'ShortSingleLine');
        }

        if (strpos($short, $testShort) !== 1) {
            $error = 'Function comment short description must start with exactly one space';
            $phpcsFile->addError($error, ($commentStart + 1), 'ShortStartSpace');
        }

        if ($testShort !== '{@inheritdoc}') {
            if (preg_match('|[A-Z]|', $testShort[0]) === 0) {
                $error = 'Function comment short description must start with a capital letter';
                $phpcsFile->addError($error, ($commentStart + 1), 'ShortNotCapital');
            }

            if ($lastChar !== '.') {
                $error = 'Function comment short description must end with a full stop';
                $phpcsFile->addError($error, ($commentStart + 1), 'ShortFullStop');
            }
        }

    }//end process()


    /**
     * Process any throw tags that this function comment has.
     *
     * @param int $commentStart The position in the stack where the
     *                          comment started.
     *
     * @return void
     */
    protected function processThrows($commentStart)
    {
        if (count($this->commentParser->getThrows()) === 0) {
            return;
        }

        foreach ($this->commentParser->getThrows() as $throw) {

            $exception = $throw->getValue();
            $errorPos  = ($commentStart + $throw->getLine());

            if ($exception === '') {
                $error = '@throws tag must contain the exception class name';
                $this->currentFile->addError($error, $errorPos, 'EmptyThrows');
            }
        }

    }//end processThrows()


    /**
     * Process the return comment of this function comment.
     *
     * @param int $commentStart The position in the stack where the comment started.
     * @param int $commentEnd   The position in the stack where the comment ended.
     *
     * @return void
     */
    protected function processReturn($commentStart, $commentEnd)
    {
        // Skip constructor and destructor.
        $className = '';
        if ($this->_classToken !== null) {
            $className = $this->currentFile->getDeclarationName($this->_classToken);
            $className = strtolower(ltrim($className, '_'));
        }

        $methodName      = strtolower(ltrim($this->_methodName, '_'));
        $isSpecialMethod = ($this->_methodName === '__construct' || $this->_methodName === '__destruct');

        if ($isSpecialMethod === false && $methodName !== $className) {
            $return = $this->commentParser->getReturn();
            if ($return !== null) {
                $errorPos = ($commentStart + $this->commentParser->getReturn()->getLine());
                if (trim($return->getRawContent()) === '') {
                    $error = '@return tag is empty in function comment';
                    $this->currentFile->addError($error, $errorPos, 'EmptyReturn');
                    return;
                }

                $comment = $return->getComment();
                $commentWhitespace = $return->getWhitespaceBeforeComment();
                if (substr_count($return->getWhitespaceBeforeValue(), $this->currentFile->eolChar) > 0) {
                    $error = 'Data type of return value is missing';
                    $this->currentFile->addError($error, $errorPos, 'MissingReturnType');
                    // Treat the value as part of the comment.
                    $comment = $return->getValue().' '.$comment;
                    $commentWhitespace = $return->getWhitespaceBeforeValue();
                } else if ($return->getWhitespaceBeforeValue() !== ' ') {
                    $error = 'Expected 1 space before return type';
                    $this->currentFile->addError($error, $errorPos, 'SpacingBeforeReturnType');
                }

                if (strpos($return->getValue(), '$') !== false) {
                    $error = '@return data type must not contain "$"';
                    $this->currentFile->addError($error, $errorPos, '$InReturnType');
                }

                if (in_array($return->getValue(), array('unknown_type', '<type>', 'type')) === true) {
                    $error = 'Expected a valid @return data type, but found %s';
                    $data = array($return->getValue());
                    $this->currentFile->addError($error, $errorPos, 'InvalidReturnType', $data);
                }

                if (isset($this->invalidTypes[$return->getValue()]) === true) {
                    $error = 'Invalid @return data type, expected %s but found %s';
                    $data = array($this->invalidTypes[$return->getValue()], $return->getValue());
                    $this->currentFile->addError($error, $errorPos, 'InvalidReturnTypeName', $data);
                }

                if (trim($comment) === '') {
                    $error = 'Missing comment for @return statement';
                    $this->currentFile->addError($error, $errorPos, 'MissingReturnComment');
                } else if (substr_count($commentWhitespace, $this->currentFile->eolChar) !== 1) {
                    $error = 'Return comment must be on the next line';
                    $this->currentFile->addError($error, $errorPos, 'ReturnCommentNewLine');
                } else if (substr_count($commentWhitespace, ' ') !== 3) {
                    $error = 'Return comment indentation must be 2 additional spaces';
                    $this->currentFile->addError($error, $errorPos + 1, 'ParamCommentIndentation');
                }
            }
        }

    }//end processReturn()


    /**
     * Process the function parameter comments.
     *
     * @param int $commentStart The position in the stack where
     *                          the comment started.
     *
     * @return void
     */
    protected function processParams($commentStart)
    {
        $realParams = $this->currentFile->getMethodParameters($this->_functionToken);

        $params      = $this->commentParser->getParams();
        $foundParams = array();

        if (empty($params) === false) {
            // There must be an empty line before the parameter block.
            if (substr_count($params[0]->getWhitespaceBefore(), $this->currentFile->eolChar) < 2) {
                $error    = 'There must be an empty line before the parameter block';
                $errorPos = ($params[0]->getLine() + $commentStart);
                $this->currentFile->addError($error, $errorPos, 'SpacingBeforeParams');
            }

            $lastParm = (count($params) - 1);
            if (substr_count($params[$lastParm]->getWhitespaceAfter(), $this->currentFile->eolChar) !== 2) {
                $error    = 'Last parameter comment requires a blank newline after it';
                $errorPos = ($params[$lastParm]->getLine() + $commentStart);
                $this->currentFile->addError($error, $errorPos, 'SpacingAfterParams');
            }

            $checkPos = 0;
            foreach ($params as $param) {
                $paramComment = trim($param->getComment());
                $errorPos     = ($param->getLine() + $commentStart);

                // Make sure that there is only one space before the var type.
                if ($param->getWhitespaceBeforeType() !== ' ') {
                    $error = 'Expected 1 space before variable type';
                    $this->currentFile->addError($error, $errorPos, 'SpacingBeforeParamType');
                }

                // Make sure they are in the correct order,
                // and have the correct name.
                $pos = $param->getPosition();

                $paramName = '[ UNKNOWN ]';
                if ($param->getVarName() !== '') {
                    $paramName = $param->getVarName();
                }

                // Make sure the names of the parameter comment matches the
                // actual parameter.
                $matched = false;
                // Parameter documentation can be ommitted for some parameters, so
                // we have to search the rest for a match.
                while (isset($realParams[($checkPos)]) === true) {
                    $realName          = $realParams[($checkPos)]['name'];
                    $expectedParamName = $realName;
                    $isReference       = $realParams[($checkPos)]['pass_by_reference'];

                    // Append ampersand to name if passing by reference.
                    if ($isReference === true && substr($paramName, 0, 1) === '&') {
                        $expectedParamName = '&'.$realName;
                    }

                    if ($expectedParamName === $paramName) {
                        $matched = true;
                        break;
                    }

                    $checkPos++;
                }

                if ($matched === false && $paramName !== '...') {
                    if ($checkPos >= $pos) {
                        $code  = 'ParamNameNoMatch';
                        $data  = array(
                                  $paramName,
                                  $realParams[($pos - 1)]['name'],
                                  $pos,
                                 );
                        $error = 'Doc comment for var %s does not match ';
                        if (strtolower($paramName) === strtolower($realParams[($pos - 1)]['name'])) {
                            $error .= 'case of ';
                            $code   = 'ParamNameNoCaseMatch';
                        }

                        $error .= 'actual variable name %s at position %s';
                        $this->currentFile->addError($error, $errorPos, $code, $data);
                        // Reset the parameter position to check for following
                        // parameters.
                        $checkPos = ($pos - 1);
                    } else {
                        // We must have an extra parameter comment.
                        $error = 'Superfluous doc comment at position '.$pos;
                        $this->currentFile->addError($error, $errorPos, 'ExtraParamComment');
                    }//end if
                }//end if

                $checkPos++;

                if ($param->getVarName() === '') {
                    $error = 'Missing parameter name at position '.$pos;
                    $this->currentFile->addError($error, $errorPos, 'MissingParamName');
                }

                if ($param->getType() === '') {
                    $error = 'Missing parameter type at position '.$pos;
                    $this->currentFile->addError($error, $errorPos, 'MissingParamType');
                }

                if (in_array($param->getType(), array('unknown_type', '<type>', 'type')) === true) {
                    $error = 'Expected a valid @param data type, but found %s';
                    $data = array($param->getType());
                    $this->currentFile->addError($error, $errorPos, 'InvalidParamType', $data);
                }

                if (isset($this->invalidTypes[$param->getType()]) === true) {
                    $error = 'Invalid @param data type, expected %s but found %s';
                    $data = array($this->invalidTypes[$param->getType()], $param->getType());
                    $this->currentFile->addError($error, $errorPos, 'InvalidParamTypeName', $data);
                }

                if ($paramComment === '') {
                    $error = 'Missing comment for param "%s" at position %s';
                    $data  = array(
                              $paramName,
                              $pos,
                             );
                    $this->currentFile->addError($error, $errorPos, 'MissingParamComment', $data);
                } else if (substr_count($param->getWhitespaceBeforeComment(), $this->currentFile->eolChar) !== 1) {
                    $error = 'Parameter comment must be on the next line at position '.$pos;
                    $this->currentFile->addError($error, $errorPos, 'ParamCommentNewLine');
                } else if (substr_count($param->getWhitespaceBeforeComment(), ' ') !== 3) {
                    $error = 'Parameter comment indentation must be 2 additional spaces at position '.$pos;
                    $this->currentFile->addError($error, ($errorPos + 1), 'ParamCommentIndentation');
                }
            }//end foreach
        }//end if

        $realNames = array();
        foreach ($realParams as $realParam) {
            $realNames[] = $realParam['name'];
        }

    }//end processParams()


    /**
     * Process the function "see" comments.
     *
     * @return void
     */
    protected function processSees($commentStart)
    {
        $sees = $this->commentParser->getSees();
        foreach ($sees as $see) {
            $errorPos = $see->getLine() + $commentStart;
            if ($see->getWhitespaceBeforeContent() !== ' ') {
                $error = 'Expected 1 space before see reference';
                $this->currentFile->addError($error, $errorPos, 'SpacingBeforeSee');
            }

            $comment = trim($see->getContent());
            if (strpos($comment, ' ') !== false) {
                $error = 'The @see reference should not contain any additional text';
                $this->currentFile->addError($error, $errorPos, 'SeeAdditionalText');
                continue;
            }
            if (preg_match('/[\.!\?]$/', $comment) === 1) {
                $error = 'Trailing punctuation for @see references is not allowed.';
                $this->currentFile->addError($error, $errorPos, 'SeePunctuation');
            }

        }

    }//end processSees()


}//end class

?>
