<?php

/**
 * @file
 * Default theme implementation for an achievement notification popup.
 *
 * Available variables:
 * - $achievement: The achievement being displayed, as an array.
 * - $unlock: An array of unlocked 'rank' and 'timestamp', if applicable.
 * - $unlocked_date: A renderable string of the user's unlock timestamp.
 * - $unlocked_rank: A renderable string of the user's unlock ranking.
 * - $image: The renderable achievement's linked image (default or otherwise).
 * - $image_path: The raw path to the context-aware achievement image.
 * - $achievement_url: Direct URL of the current achievement.
 * - $achievement_title: The renderable and linked achievement title.
 * - $achievement_points: A renderable string of "$n points".
 * - $state: The 'unlocked', 'locked', or 'secret' achievement state.
 * - $classes: String of classes for this achievement.
 */
?>
<div class="<?php print $classes; ?>">
  <div class="achievement-image"><?php print render($image); ?></div>

  <div class="achievement-points-box">
    <div class="achievement-points"><?php print $achievement['points']; ?></div>
    <div class="achievement-unlocked-stats">
      <div class="achievement-unlocked-rank"><?php print render($unlocked_rank); ?></div>
    </div>
  </div>

  <div class="achievement-body">
    <div class="achievement-header"><?php print t('Achievement Unlocked'); ?></div>
    <div class="achievement-title"><?php print render($achievement_title); ?></div>
  </div>
</div>
