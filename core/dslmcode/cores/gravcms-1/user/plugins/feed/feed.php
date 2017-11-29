<?php
namespace Grav\Plugin;

use Grav\Common\Data;
use Grav\Common\Page\Collection;
use Grav\Common\Plugin;
use Grav\Common\Uri;
use Grav\Common\Page\Page;
use RocketTheme\Toolbox\Event\Event;

class FeedPlugin extends Plugin
{
    /**
     * @var bool
     */
    protected $active = false;

    /**
     * @var string
     */
    protected $type;

    /**
     * @var array
     */
    protected $feed_config;

    /**
     * @var array
     */
    protected $valid_types = array('rss','atom');

    /**
     * @return array
     */
    public static function getSubscribedEvents()
    {
        return [
            'onPluginsInitialized' => ['onPluginsInitialized', 0],
            'onBlueprintCreated' => ['onBlueprintCreated', 0]
        ];
    }

    /**
     * Activate feed plugin only if feed was requested for the current page.
     *
     * Also disables debugger.
     */
    public function onPluginsInitialized()
    {
        if ($this->isAdmin()) {
            $this->active = false;
            return;
        }

        $this->feed_config = (array) $this->config->get('plugins.feed');

        if ($this->feed_config['enable_json_feed']) {
            $this->valid_types[] = 'json';
        }

        /** @var Uri $uri */
        $uri = $this->grav['uri'];
        $this->type = $uri->extension();

        if ($this->type && in_array($this->type, $this->valid_types)) {
            $this->active = true;

            $this->enable([
                'onPageInitialized' => ['onPageInitialized', 0],
                'onCollectionProcessed' => ['onCollectionProcessed', 0],
                'onTwigTemplatePaths' => ['onTwigTemplatePaths', 0],
                'onTwigSiteVariables' => ['onTwigSiteVariables', 0]
            ]);
        }
    }

    /**
     * Initialize feed configuration.
     */
    public function onPageInitialized()
    {
        /** @var Page $page */
        $page = $this->grav['page'];
        if (isset($page->header()->feed)) {
            $this->feed_config = array_merge($this->feed_config, $page->header()->feed);
        }

        // Overwrite regular content with feed config, so you can influence the collection processing with feed config
        if (property_exists($page->header(), 'content')) {
            $page->header()->content = array_merge($page->header()->content, $this->feed_config);
        }
    }

    /**
     * Feed consists of all sub-pages.
     *
     * @param Event $event
     */
    public function onCollectionProcessed(Event $event)
    {
        /** @var Collection $collection */
        $collection = $event['collection'];

        foreach ($collection as $slug => $page) {
            $header = $page->header();
            if (isset($header->feed) && !empty($header->feed['skip'])) {
                $collection->remove($page);
            }
        }
    }

    /**
     * Set feed template as current twig template
     */
    public function onTwigSiteVariables()
    {
        $this->grav['twig']->template = 'feed.' . $this->type . '.twig';
    }

    /**
     * Add current directory to twig lookup paths.
     */
    public function onTwigTemplatePaths()
    {
        $this->grav['twig']->twig_paths[] = __DIR__ . '/templates';
    }


    /**
     * Extend page blueprints with feed configuration options.
     *
     * @param Event $event
     */
    public function onBlueprintCreated(Event $event)
    {
        static $inEvent = false;

        /** @var Data\Blueprint $blueprint */
        $blueprint = $event['blueprint'];
        if (!$inEvent && $blueprint->name == 'blog_list') {
            $inEvent = true;
            $blueprints = new Data\Blueprints(__DIR__ . '/blueprints/');
            $extends = $blueprints->get('feed');
            $blueprint->extend($extends, true);
            $inEvent = false;
        }
    }
}