<?php
namespace Grav\Plugin;

use Grav\Common\Iterator;
use Grav\Common\Page\Collection;
use Grav\Common\GravTrait;
use Grav\Common\Uri;

class PaginationHelper extends Iterator
{
    use GravTrait;

    protected $current;
    protected $items_per_page;
    protected $page_count;

    protected $url_params;

    /**
     * Create and initialize pagination.
     *
     * @param Collection $collection
     */
    public function __construct(Collection $collection)
    {
        require_once __DIR__ . '/paginationpage.php';

        /** @var Uri $uri */
        $uri = self::getGrav()['uri'];
        $config = self::getGrav()['config'];
        $this->current = $uri->currentPage();

        // get params
        $url_params = explode('/', ltrim($uri->params(), '/'));

        $params = $collection->params();

        foreach ($url_params as $key => $value) {
            if (strpos($value, 'page' . $config->get('system.param_sep')) !== false) {
                unset($url_params[$key]);
            }
            if (isset($params['ignore_url_params'])) {
                foreach ((array)$params['ignore_params'] as $ignore_param) {
                    if (strpos($value, $ignore_param . $config->get('system.param_sep')) !== false) {
                        unset($url_params[$key]);
                    }
                }
            }
        }

        $this->url_params = '/'.implode('/', $url_params);

        // check for empty params
        if ($this->url_params == '/') {
            $this->url_params = '';
        }

        $this->items_per_page = $params['limit'];
        $this->page_count = ceil($collection->count() / $this->items_per_page);

        for ($x=1; $x <= $this->page_count; $x++) {
            if ($x === 1) {
                $this->items[$x] = new PaginationPage($x, '');
            } else {
                $this->items[$x] = new PaginationPage($x, '/page' . $config->get('system.param_sep') . $x);
            }
       }
    }

    /**
     * Returns true if current item has previous sibling.
     *
     * @return bool
     */
    public function hasPrev()
    {
        if (array_key_exists($this->current -1, $this->items)) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Returns true if current item has next sibling.
     *
     * @return bool
     */
    public function hasNext()
    {
        if (array_key_exists($this->current +1, $this->items)) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Return previous url.
     *
     * @return string|null
     */
    public function prevUrl()
    {
        if (array_key_exists($this->current -1, $this->items)) {
            return $this->items[$this->current -1]->url;
        }

        return null;
    }

    /**
     * Return next url.
     *
     * @return string|null
     */
    public function nextUrl()
    {
        if (array_key_exists($this->current +1, $this->items)) {
            return $this->items[$this->current +1]->url;
        }

        return null;
    }

    public function params()
    {
        return $this->url_params;
    }
}
