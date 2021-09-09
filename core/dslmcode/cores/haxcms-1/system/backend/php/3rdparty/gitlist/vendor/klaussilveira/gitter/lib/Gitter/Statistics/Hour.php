<?php

namespace Gitter\Statistics;

use Gitter\Model\Commit\Commit;
use Gitter\Util\Collection;

/**
 * Aggregate statistics based on hour.
 */
class Hour extends Collection implements StatisticsInterface
{
    /**
     * @param Commit $commit
     */
    public function addCommit(Commit $commit)
    {
        $hour = $commit->getCommiterDate()->format('H');

        $this->items[$hour][] = $commit;
    }

    public function sortCommits()
    {
        ksort($this->items);
    }
}
