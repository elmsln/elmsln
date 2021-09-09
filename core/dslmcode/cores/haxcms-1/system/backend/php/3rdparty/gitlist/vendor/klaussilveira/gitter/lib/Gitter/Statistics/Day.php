<?php

namespace Gitter\Statistics;

use Gitter\Model\Commit\Commit;
use Gitter\Util\Collection;

/**
 * Aggregate statistics based on day.
 */
class Day extends Collection implements StatisticsInterface
{
    /**
     * @param Commit $commit
     */
    public function addCommit(Commit $commit)
    {
        $day = $commit->getCommiterDate()->format('N');

        $this->items[$day][] = $commit;
    }

    public function sortCommits()
    {
        ksort($this->items);
    }
}
