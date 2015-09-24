<?php
/**
 * Piwik - free/libre analytics platform
 *
 * @link http://piwik.org
 * @license http://www.gnu.org/licenses/lgpl-3.0.html LGPL v3 or later
 *
 */
namespace Piwik\Cache\Backend;

use Piwik\Cache\Backend;

class Factory
{
    public function buildArrayCache()
    {
        return new ArrayCache();
    }

    public function buildFileCache($options)
    {
        return new File($options['directory']);
    }

    public function buildNullCache()
    {
        return new NullCache();
    }

    public function buildChainedCache($options)
    {
        $backends = array();

        foreach ($options['backends'] as $backendToBuild) {

            $backendOptions = array();
            if (array_key_exists($backendToBuild, $options)) {
                $backendOptions = $options[$backendToBuild];
            }

            $backends[] = $this->buildBackend($backendToBuild, $backendOptions);
        }

        return new Chained($backends);
    }

    public function buildRedisCache($options)
    {
        if (empty($options['host']) || empty($options['port'])) {
            throw new \InvalidArgumentException('RedisCache is not configured. Please provide at least a host and a port');
        }

        $timeout = 0.0;
        if (array_key_exists('timeout', $options)) {
            $timeout = $options['timeout'];
        }

        $redis = new \Redis();
        $redis->connect($options['host'], $options['port'], $timeout);

        if (!empty($options['password'])) {
            $redis->auth($options['password']);
        }

        if (array_key_exists('database', $options)) {
            $redis->select((int) $options['database']);
        }

        $redisCache = new Redis();
        $redisCache->setRedis($redis);

        return $redisCache;
    }

    /**
     * Build a specific backend instance.
     *
     * @param string $type The type of backend you want to create. Eg 'array', 'file', 'chained', 'null', 'redis'.
     * @param array $options An array of options for the backend you want to create.
     * @return Backend
     * @throws Factory\BackendNotFoundException In case the given type was not found.
     */
    public function buildBackend($type, array $options)
    {
        switch ($type) {
            case 'array':

                return $this->buildArrayCache();

            case 'file':

                return $this->buildFileCache($options);

            case 'chained':

                return $this->buildChainedCache($options);

            case 'null':

                return $this->buildNullCache();

            case 'redis':

                return $this->buildRedisCache($options);

            default:

                throw new Factory\BackendNotFoundException("Cache backend $type not valid");
        }
    }
}