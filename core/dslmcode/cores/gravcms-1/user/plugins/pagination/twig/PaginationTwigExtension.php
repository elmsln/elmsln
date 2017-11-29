<?php
namespace Grav\Plugin;

use \Grav\Common\Grav;

class PaginationTwigExtension extends \Twig_Extension
{

    protected $config;

    public function __construct()
    {
        $this->config = Grav::instance()['config'];
    }

    /**
     * Returns extension name.
     *
     * @return string
     */
    public function getName()
    {
        return 'PaginationTwigExtension';
    }

    /**
     * Return a list of all functions.
     *
     * @return array
     */
    public function getFunctions()
    {
        return [
            new \Twig_SimpleFunction('paginate', [$this, 'paginateFunc']),
        ];
    }

    public function paginateFunc($collection, $limit, $ignore_url_param_array = []) {
        $pag = new PaginationPlugin($this, Grav::instance(), $this->config);
        $pag->paginateCollection($collection, $limit, $ignore_url_param_array);
    }
}
