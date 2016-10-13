<h2><?php print $datatitle;?></h2>
<ul class="collection">
<?php foreach ($aggregates['counts'] as $verb => $count) : ?>
 <li class="collection-item avatar">
    <i class="material-icons circle <?php print $aggregates['colors'][$verb];?>"><?php print $aggregates['icons'][$verb];?></i>
    <span class="title"><?php print $verb;?></span>
    <p><?php print format_plural($count, '1 statement', '@count statements');?><br/>
       <?php print t('from') . ' ' . format_plural(count($aggregates['users'][$verb]), '1 unique user', '@count unique users');?>
      <div class="progress <?php print $aggregates['colors'][$verb];?> lighten-4">
        <div class="determinate <?php print $aggregates['colors'][$verb];?> darken-2 white-text" style="width: <?php print $aggregates['percent_used'][$verb]; ?>%">
          <?php print t('@amount of @total users', array('@amount' => count($aggregates['users'][$verb]), '@total' => count($aggregates['user_list'])));?>
        </div>
      </div>
    </p>
  </li>
<?php endforeach; ?>
</ul>