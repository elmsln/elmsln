<?php

/*
 * This file is part of the Gitter library.
 *
 * (c) Klaus Silveira <klaussilveira@php.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Gitter;

use Symfony\Component\Process\ExecutableFinder;
use Symfony\Component\Process\Process;

class Client
{
    protected $path;

    public function __construct($path = null)
    {
        if (!$path) {
            $finder = new ExecutableFinder();
            $path = $finder->find('git', '/usr/bin/git');
        }

        $this->setPath($path);
    }

    /**
     * Creates a new repository on the specified path.
     *
     * @param  string     $path Path where the new repository will be created
     *
     * @return Repository Instance of Repository
     */
    public function createRepository($path, $bare = null)
    {
        if (file_exists($path . '/.git/HEAD') && !file_exists($path . '/HEAD')) {
            throw new \RuntimeException('A GIT repository already exists at ' . $path);
        }

        $repository = new Repository($path, $this);

        return $repository->create($bare);
    }

    /**
     * Opens a repository at the specified path.
     *
     * @param  string     $path Path where the repository is located
     *
     * @return Repository Instance of Repository
     */
    public function getRepository($path)
    {
        if (!file_exists($path) || !file_exists($path . '/.git/HEAD') && !file_exists($path . '/HEAD')) {
            throw new \RuntimeException('There is no GIT repository at ' . $path);
        }

        return new Repository($path, $this);
    }

    public function run($repository, $command)
    {
        if (version_compare($this->getVersion(), '1.7.2', '>=')) {
            $command = '-c "color.ui"=false ' . $command;
        }

        $process = new Process($this->getPath() . ' ' . $command, $repository->getPath());
        $process->setTimeout(180);
        $process->run();

        if (!$process->isSuccessful()) {
            throw new \RuntimeException($process->getErrorOutput());
        }

        return $process->getOutput();
    }

    public function getVersion()
    {
        static $version;

        if (null !== $version) {
            return $version;
        }

        $process = new Process($this->getPath() . ' --version');
        $process->run();

        if (!$process->isSuccessful()) {
            throw new \RuntimeException($process->getErrorOutput());
        }

        $version = trim(substr($process->getOutput(), 12));

        return $version;
    }

    /**
     * Get the current Git binary path.
     *
     * @return string Path where the Git binary is located
     */
    protected function getPath()
    {
        return escapeshellarg($this->path);
    }

    /**
     * Set the current Git binary path.
     *
     * @param string $path Path where the Git binary is located
     */
    protected function setPath($path)
    {
        $this->path = $path;

        return $this;
    }
}
