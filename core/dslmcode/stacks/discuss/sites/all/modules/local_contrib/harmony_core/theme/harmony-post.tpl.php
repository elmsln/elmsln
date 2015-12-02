<?php

/**
 * @file
 * Default theme implementation to display a Harmony Post entity.
 *
 * Available variables:
 *
 * - $post: The post entity itself.
 * - $is_page: If on a standalone page and not on a thread page.
 *
 * Template suggestions available, listed from the most specific template to
 * the least. Drupal will use the most specific template it finds:
 * - harmony-post.tpl.php
 * - harmony-post__[view_mode].tpl.php
 * - harmony-post__[post_id].tpl.php
 *
 */

hide($content['links']);
$links = render($content['links']);
?>
<div id="post-<?php print $post->post_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <a name="post-<?php print $post->post_id; ?>"></a>
  <div class="post-header post-left-offset clearfix text-small">
    <?php if ($direct_reply): ?>
    <div class="pull-left">
      <span class="post-is-reply-to">
        <?php print $direct_reply; ?>
      </span>
    </div>
    <?php endif; ?>
    <div class="pull-right">
      <span class="post-created">
        <?php if ($link_created): ?>
        <a href="<?php print $thread_post_url; ?>" title="<?php print t('Permalink to this post'); ?>"><?php print $created; ?></a>
        <?php else: ?>
        <?php print $created; ?>
        <?php endif; ?>
      </span>
      <?php if ($revisions): ?>
       <span class="post-revisions"><?php print $revisions; ?></span>
      <?php endif; ?>
    </div>
  </div>
  <div class="clearfix">
    <div class="post-left post-user-profile text-center">
      <?php print $user_profile; ?>
    </div>
    <div class="post-content post-left-offset">
      <?php print render($content); ?>

      <?php if ($links): ?>
      <div class="clearfix">
        <?php print $links; ?>
      </div>
      <?php endif; ?>
      <?php if ($view_mode != 'inline_reply'): ?>
      <div id="post-<?php print $post->post_id; ?>-replies" class="post-replies clearfix"></div>
    <?php endif; ?>
    </div>
  </div>
</div>
<?php if ($is_page && $belongs_to_thread): ?>
<div class="post-return">
  <a href="<?php print $thread_post_url; ?>"><?php print t('Return to thread'); ?></a>
</div>
<?php endif; ?>
