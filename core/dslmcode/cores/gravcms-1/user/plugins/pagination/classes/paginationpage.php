<?php
namespace Grav\Plugin;

use \Grav\Common\GravTrait;

class PaginationPage
{
    use GravTrait;

    /**
     * @var int
     */
    public $number;

    /**
     * @var string
     */
    public $url;

    /**
     * @var int
     */
    protected $delta=0;

    /**
     * Constructor
     *
     * @param int $number
     * @param string $url
     */
    public function __construct($number, $url)
    {
        $this->number = $number;
        $this->url = $url;
        $this->delta = self::getGrav()['config']->get('plugins.pagination.delta');
    }

    /**
     * Returns true if the page is the current one.
     *
     * @return bool
     */
    public function isCurrent()
    {
        if (self::getGrav()['uri']->currentPage() == $this->number) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Returns true if the page is within a configurable delta of the current one
     *
     * @return bool
     */
    public function isInDelta()
    {
        if (!$this->delta) {
            return true;
        } else {
            return abs(self::getGrav()['uri']->currentPage() - $this->number) < $this->delta;
        }
    }

    /**
     * Returns true is this page is the last/first one at the border of the delta range
     * (Used to display a "gap" li element ...)
     *
     * @return bool
     */
    public function isDeltaBorder()
    {
        if (!$this->delta) {
            return false;
        } else {
            return abs(self::getGrav()['uri']->currentPage() - $this->number) == $this->delta;
        }
    }
}
