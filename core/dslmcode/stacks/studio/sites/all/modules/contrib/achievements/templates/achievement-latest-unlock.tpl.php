<?php

/**
 * @file
 * Default theme implementation for a user's latest unlock on the leaderboard.
 *
 * Available variables:
 * - $achievement: The achievement being displayed, as an array.
 * - $unlock: An array of unlocked 'rank' and 'timestamp', if applicable.
 * - $unlocked_date: A renderable string of the user's unlock timestamp.
 * - $image: The renderable achievement's linked image (default or otherwise).
 * - $image_path: The raw path to the context-aware achievement image.
 * - $achievement_url: Direct URL of the current achievement.
 * - $achievement_title: The renderable and linked achievement title.
 * - $achievement_points: A renderable string of "$n points".
 */
?>
<div class="achievement-latest-image">
  <?php print render($image); ?>
</div>

<div class="achievement-details">
  <div class="achievement-latest-title"><?php print render($achievement_title); ?></div>
  <div class="achievement-latest-points"><?php print render($achievement_points); ?></div>
</div>
