<?php

namespace Gitter\Statistics;

use Gitter\Model\Commit\Commit;

interface StatisticsInterface
{
    public function addCommit(Commit $commit);

    public function sortCommits();
}
