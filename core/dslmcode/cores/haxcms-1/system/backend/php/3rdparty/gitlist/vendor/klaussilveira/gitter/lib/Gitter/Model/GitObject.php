<?php

/*
 * This file is part of the Gitter library.
 *
 * (c) Klaus Silveira <klaussilveira@php.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Gitter\Model;

class GitObject extends AbstractModel
{
    protected $hash;

    public function isBlob()
    {
        return false;
    }

    public function isTag()
    {
        return false;
    }

    public function isCommit()
    {
        return false;
    }

    public function isTree()
    {
        return false;
    }

    public function getHash()
    {
        return $this->hash;
    }

    public function setHash($hash)
    {
        $this->hash = $hash;

        return $this;
    }
}
