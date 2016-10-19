<h2><?php print $datatitle;?></h2>
<ul class="collection">
<?php foreach ($aggregates['counts'] as $verb => $count) : ?>
 <li class="collection-item avatar">
    <p>
      <i class="material-icons circle <?php print $aggregates['colors'][$verb];?>">
      <?php print $aggregates['icons'][$verb];?></i><?php print l($verb, $aggregates['verb_data_links'][$verb]);?>
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
                  <div class="collapsible-header">
                    <?php
                      if (empty($statement['statement']['object']['definition']['name'])) {
                        $title = $statement['statement']['object']['objectType'];
                      }
                      else {
                        $title = $statement['statement']['object']['definition']['name']['en-US'];
                      }
                      print ($index+1) . '. ' . $title . ' ' . t('by') . ' ' . $statement['statement']['actor']['name'];
                      if (!is_null($aggregates['user_list'][$statement['statement']['actor']['name']])) {
                        print '<span class="collapsible-action-link">' . l(t('user'), 'user/' . $aggregates['user_list'][$statement['statement']['actor']['name']] . '/data/' . $verb, array('attributes' => array('class' => array('red-text', 'text-darken-4')))) . '</span>';
                      }
                      if (!is_null($statement['_item_link'])) {
                        print '<span class="collapsible-action-link">' . l(t('data'), $statement['_item_link'] . '/data/' . $verb, array('attributes' => array('class' => array('green-text', 'text-darken-4')))) . '</span>';
                      }
                    ?>
                    <span class="collapsible-action-link"><?php print l(t('view content'), $statement['statement']['object']['id'], array('attributes' => array('class' => array('blue-text', 'text-darken-4'))));?></span>
                  </div>
                  <div class="collapsible-body">
                    <p><pre><?php print json_encode($statement, JSON_PRETTY_PRINT);?></pre></p>
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
                  <?php print $username;?>
                </div>
                <div class="collapsible-body">
                  <p>
                    <ul class="collection">
                      <li class="collection-item"><?php print t('@count statements', array('@count' => $ucount)); ?></li>
                      <?php
                        if (!is_null($aggregates['user_list'][$username])) {
                          print l(t('view user data'), 'user/' . $aggregates['user_list'][$username] . '/data/' . $verb, array('attributes' => array('class' => array('collection-item'))));
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
</ul>