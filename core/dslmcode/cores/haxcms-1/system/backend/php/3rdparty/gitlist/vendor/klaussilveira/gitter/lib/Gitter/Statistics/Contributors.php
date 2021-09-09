<?php

namespace Gitter\Statistics;

use Gitter\Model\Commit\Commit;
use Gitter\Util\Collection;

/**
 * Aggregate statistics based on contributor.
 */
class Contributors extends Collection implements StatisticsInterface
{
    /**
     * @param Commit $commit
     */
    public function addCommit(Commit $commit)
    {
        $email = $commit->getAuthor()->getEmail();
        $commitDate = $commit->getCommiterDate()->format('Y-m-d');

        if (!isset($this->items[$email])) {
            $this->items[$email] = new Collection();
        }

        $this->items[$email]->items[$commitDate][] = $commit;
        ksort($this->items[$email]->items);
    }

    public function sortCommits()
    {
        uasort($this->items, function ($sortA, $sortB) {
            if (count($sortA) === count($sortB)) {
                return 0;
            }

            return count($sortA) > count($sortB) ? -1 : 1;
        });
    }
}
