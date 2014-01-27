<?php
/**
 * Parses function doc comments.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * Parses function doc comments.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_CommentParser_FunctionCommentParser
    extends PHP_CodeSniffer_CommentParser_FunctionCommentParser
{

    /**
     * The parameter elements within this function comment.
     *
     * @var array(Drupal_CommentParser_ParameterElement)
     */
    protected $params = array();

    /**
     * The return element in this function comment.
     *
     * @var Drupal_CommentParser_ReturnElement
     */
    protected $return = null;


    /**
     * Parses parameter elements.
     *
     * @param array(string) $tokens The tokens that conmpise this sub element.
     *
     * @return Drupal_CommentParser_ParameterElement
     */
    protected function parseParam($tokens)
    {
        $param = new Drupal_CommentParser_ParameterElement(
            $this->previousElement,
            $tokens,
            $this->phpcsFile
        );

        $this->params[] = $param;
        return $param;

    }//end parseParam()


    /**
     * Parses return elements.
     *
     * @param array(string) $tokens The tokens that comprise this sub element.
     *
     * @return Drupal_CommentParser_ReturnElement
     */
    protected function parseReturn($tokens)
    {
        $return = new Drupal_CommentParser_ReturnElement(
            $this->previousElement,
            $tokens,
            'return',
            $this->phpcsFile
        );

        $this->return = $return;
        return $return;

    }//end parseReturn()


    /**
     * Returns the parameter elements that this function comment contains.
     *
     * Returns an empty array if no parameter elements are contained within
     * this function comment.
     *
     * @return array(Drupal_CommentParser_ParameterElement)
     */
    public function getParams()
    {
        return $this->params;

    }//end getParams()


    /**
     * Returns the return element in this fucntion comment.
     *
     * Returns null if no return element exists in the comment.
     *
     * @return Drupal_CommentParser_ReturnElement
     */
    public function getReturn()
    {
        return $this->return;

    }//end getReturn()


}//end class

?>
