<?php
namespace Grav\Plugin;

use Grav\Common\Grav;
use Grav\Common\Page\Collection;
use Grav\Common\Page\Page;
use Grav\Common\Plugin;
use RocketTheme\Toolbox\Event\Event;
use Grav\Common\Uri;

class PaginationPlugin extends Plugin
{
    /**
     * @var PaginationHelper
     */
    protected $pagination;

    /**
     * @return array
     */
    public static function getSubscribedEvents()
    {
        return [
            'onPluginsInitialized' => ['onPluginsInitialized', 0]
        ];
    }

    /**
     * Initialize configuration
     */
    public function onPluginsInitialized()
    {
        if ($this->isAdmin()) {
            $this->active = false;
            return;
        }

        $this->enable([
            'onTwigTemplatePaths' => ['onTwigTemplatePaths', 0],
            'onPageInitialized' => ['onPageInitialized', 0],
            'onTwigExtensions' => ['onTwigExtensions', 0]
        ]);
    }

    /**
     * Add current directory to twig lookup paths.
     */
    public function onTwigTemplatePaths()
    {
        $this->grav['twig']->twig_paths[] = __DIR__ . '/templates';
    }

    /**
     * Add Twig Extensions
     */
    public function onTwigExtensions()
    {
        require_once(__DIR__.'/twig/PaginationTwigExtension.php');
        $this->grav['twig']->twig->addExtension(new PaginationTwigExtension());
    }

    /**
     * Enable pagination if page has params.pagination = true.
     */
    public function onPageInitialized()
    {
        /** @var Page $page */
        $page = $this->grav['page'];

        if ($page && ($page->value('header.content.pagination') || $page->value('header.pagination'))) {
            $this->enable([
                'onCollectionProcessed' => ['onCollectionProcessed', 0],
                'onTwigSiteVariables' => ['onTwigSiteVariables', 0]
            ]);

            $template = $this->grav['uri']->param('tmpl');
            if ($template) {
                $page->template($template);
            }
        }
    }

    /**
     * Create pagination object for the page.
     *
     * @param Event $event
     */
    public function onCollectionProcessed(Event $event)
    {
        /** @var Collection $collection */
        $collection = $event['collection'];
        $params = $collection->params();

        // Only add pagination if it has been enabled for the collection.
        if (empty($params['pagination'])) {
            return;
        }

        if (!empty($params['limit']) && $collection->count() > $params['limit']) {
            require_once __DIR__ . '/classes/paginationhelper.php';
            $this->pagination = new PaginationHelper($collection);
            $collection->setParams(['pagination' => $this->pagination]);
        }
    }

    /**
     * Set needed variables to display pagination.
     */
    public function onTwigSiteVariables()
    {
        if ($this->config->get('plugins.pagination.built_in_css')) {
            $this->grav['assets']->add('plugin://pagination/css/pagination.css');
        }
    }

    /**
     * pagination
     *
     * @param collection $collection
     * @param $limit
     * @param $ignore_param_array      url parameters to be ignored in page links
     */
    public function paginateCollection( $collection, $limit, $ignore_param_array = [])
    {
        $collection->setParams(['pagination' => 'true']);
        $collection->setParams(['limit' => $limit]);
        $collection->setParams(['ignore_params' => $ignore_param_array]);

        if ($collection->count() > $limit) {
            require_once __DIR__ . '/classes/paginationhelper.php';
            $this->pagination = new PaginationHelper($collection);
            $collection->setParams(['pagination' => $this->pagination]);

            $uri = $this->grav['uri'];
            $start = ($uri->currentPage() - 1) * $limit;

            if ($limit && $collection->count() > $limit) {
                $collection->slice($start, $limit);
            }
        }
    }
}
