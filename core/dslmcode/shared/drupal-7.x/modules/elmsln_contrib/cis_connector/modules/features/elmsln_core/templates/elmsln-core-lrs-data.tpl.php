<div class="elmsln-core-lrs-data-display col s12">
<ul class="collection">
<?php foreach ($aggregates['counts'] as $charttitle => $item) : ?>
  <?php foreach ($item as $data) : ?>
    <?php
      $verb = $data['verb'];
      $count = $data['value'];
    ?>
   <li class="collection-item avatar">
      <p>
        <i class="material-icons circle <?php print $aggregates['colors'][$verb];?>">
        <?php print $aggregates['icons'][$verb];?></i><?php print l($aggregates['descriptions'][$verb]['title'], $aggregates['verb_data_links'][$verb],
        array(
          'query' => array('verb' => $verb),
          'attributes' => array(
            'class' => array('tooltipped'),
            'data-position' => 'top',
            'data-delay' => '50',
            'data-tooltip' => $aggregates['descriptions'][$verb]['description']
          )
        )
      );?>
        <div class="progress <?php print $aggregates['colors'][$verb];?> lighten-4">
          <div class="determinate <?php print $aggregates['colors'][$verb];?> darken-2 white-text" style="width: <?php print $aggregates['percent_used'][$verb]; ?>%">
            <?php print t('@amount of @total users', array('@amount' => count($aggregates['users'][$verb]), '@total' => count($aggregates['user_list'])));?>
          </div>
        </div>
        <ul class="collapsible" data-collapsible="accordion">
        <li>
            <div class="collapsible-header"><i class="material-icons">data_usage</i><?php print format_plural($count, '1 statement', '@count statements');?></div>
            <div class="collapsible-body">
              <p>
                <ul class="collapsible" data-collapsible="accordion">
                <?php foreach ($aggregates['statements'][$verb] as $index => $statement) : ?>
                  <li>
                    <div class="collapsible-header xapi-statement-raw">
                      <?php
                        if (empty($statement['statement']['object']['definition']['name'])) {
                          $title = $statement['statement']['object']['objectType'];
                        }
                        else {
                          $title = $statement['statement']['object']['definition']['name']['en-US'];
                        }
                        print ($index+1) . '. ' . $title . ' ' . t('by') . ' <span class="ferpa-protect">' . $statement['statement']['actor']['name'] . '</span>';
                        if (!is_null($aggregates['user_list'][$statement['statement']['actor']['name']])) {
                          print '<span class="collapsible-action-link">' . l(t('user'), 'user/' . $aggregates['user_list'][$statement['statement']['actor']['name']] . '/data', array('query' => array('verb' => $verb), 'attributes' => array('class' => array('red-text', 'text-darken-4')))) . '</span>';
                        }
                        if (!is_null($statement['_item_link'])) {
                          print '<span class="collapsible-action-link">' . l(t('data'), $statement['_item_link'] . '/data', array('query' => array('verb' => $verb), 'attributes' => array('class' => array('green-text', 'text-darken-4')))) . '</span>';
                        }
                      ?>
                      <span class="collapsible-action-link"><?php print l(t('view content'), $statement['statement']['object']['id'], array('attributes' => array('class' => array('blue-text', 'text-darken-4'))));?></span>
                    </div>
                    <div class="collapsible-body">
                      <pre class="ferpa-protect"><?php print json_encode($statement, JSON_PRETTY_PRINT);?></pre>
                    </div>
                  </li>
                <?php endforeach; ?>
                </ul>
              </p>
            </div>
          </li>
          <li>
            <div class="collapsible-header"><i class="material-icons">person</i><?php print t('from') . ' ' . format_plural(count($aggregates['users'][$verb]), '1 unique user', '@count unique users');?></div>
            <div class="collapsible-body"><p>
              <ul class="collapsible" data-collapsible="accordion">
              <?php foreach ($aggregates['users'][$verb] as $username => $ucount) : ?>
                <li>
                  <div class="collapsible-header">
                    <span class="ferpa-protect"><?php print $username;?></span>
                  </div>
                  <div class="collapsible-body">
                    <p>
                      <ul class="collection">
                        <li class="collection-item"><?php print t('@count statements', array('@count' => $ucount)); ?></li>
                        <?php
                          if (!is_null($aggregates['user_list'][$username])) {
                            print l(t('view user data'), 'user/' . $aggregates['user_list'][$username] . '/data', array('query' => array('verb' => $verb), 'attributes' => array('class' => array('collection-item'))));
                          }
                        ?>
                      </ul>
                    </p>
                  </div>
                </li>
              <?php endforeach; ?>
              </ul>
            </p></div>
          </li>
        </ul>
      </p>
    </li>
  <?php endforeach; ?>
<?php endforeach; ?>
</ul>
</div>