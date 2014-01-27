<?php
/**
 * A class to represent return elements. We need this class because
 * PHP_CodeSniffer_CommentParser_PairElement lacks the
 * getWhitespaceBeforeComment()
 * method.
 *
 * PHP version 5
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */

/**
 * A class to represent return elements. We need this class because
 * PHP_CodeSniffer_CommentParser_PairElement lacks the
 * getWhitespaceBeforeComment()
 * method.
 *
 * @category PHP
 * @package  PHP_CodeSniffer
 * @link     http://pear.php.net/package/PHP_CodeSniffer
 */
class Drupal_CommentParser_ReturnElement
  extends PHP_CodeSniffer_CommentParser_PairElement
{

    /**
     * The value of the tag.
     *
     * @var string
     */
    protected $value = '';

    /**
     * The comment of the tag.
     *
     * @var string
     */
    protected $comment = '';

    /**
     * The whitespace that exists before the value elem.
     *
     * @var string
     */
    protected $valueWhitespace = '';

    /**
     * The whitespace that exists before the comment elem.
     *
     * @var string
     */
    protected $commentWhitespace = '';


    /**
     * Processes the sub element with the specified name.
     *
     * @param string $name             The name of the sub element to process.
     * @param string $content          The content of this sub element.
     * @param string $whitespaceBefore The whitespace that exists before the
     *                                 sub element.
     *
     * @return void
     * @see getSubElements()
     */
    protected function processSubElement($name, $content, $whitespaceBefore)
    {
        $element           = $name;
        $whitespace        = $element.'Whitespace';
        $this->$element    = $content;
        $this->$whitespace = $whitespaceBefore;

    }//end processSubElement()


    /**
     * Returns the value of the tag.
     *
     * @return string
     */
    public function getValue()
    {
        return $this->value;

    }//end getValue()


    /**
     * Returns the comment associated with the value of this tag.
     *
     * @return string
     */
    public function getComment()
    {
        return $this->comment;

    }//end getComment()


    /**
     * Returns the witespace before the content of this tag.
     *
     * @return string
     */
    public function getWhitespaceBeforeValue()
    {
        return $this->valueWhitespace;

    }//end getWhitespaceBeforeValue()


    /**
     * Returns the witespace before the content of this tag.
     *
     * @return string
     */
    public function getWhitespaceBeforeComment()
    {
        return $this->commentWhitespace;

    }//end getWhitespaceBeforeComment()


}//end class

?>
