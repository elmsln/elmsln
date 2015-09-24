<?php
/**
 * Piwik - free/libre analytics platform
 *
 * @link http://piwik.org
 * @license http://www.gnu.org/licenses/lgpl-3.0.html LGPL v3 or later
 *
 */
namespace Piwik\Cache;

use Piwik\Cache\Backend;

/**
 * This class is used to cache data during one request.
 *
 * Compared to the lazy cache it does not support setting any lifetime. To be a fast cache it does
 * not validate any cache id etc.
 */
class Transient implements Cache
{
    /**
     * @var Backend
     */
    private $backend;

    public function __construct()
    {
        $this->backend = new Backend\ArrayCache();
    }

    /**
     * Fetches an entry from the cache.
     *
     * Make sure to call the method {@link has()} to verify whether there is actually any content set under this
     * cache id.
     *
     * @param string $id The cache id.
     * @return mixed
     */
    public function fetch($id)
    {
        return $this->backend->doFetch($id);
    }

    /**
     * {@inheritdoc}
     */
    public function contains($id)
    {
        return $this->backend->doContains($id);
    }

    /**
     * Puts data into the cache.
     *
     * @param string $id The cache id.
     * @param mixed $content
     * @param int $lifeTime Setting a lifetime is not supported by this cache and the parameter will be ignored.
     * @return boolean
     */
    public function save($id, $content, $lifeTime = 0)
    {
        return $this->backend->doSave($id, $content);
    }

    /**
     * {@inheritdoc}
     */
    public function delete($id)
    {
        return $this->backend->doDelete($id);
    }

    /**
     * {@inheritdoc}
     */
    public function flushAll()
    {
        return $this->backend->doFlush();
    }

}
