<?php
// Comment template file
// convert threading to something more visually appealing
$thread = explode('.', str_replace('/', '', $comment->thread));
foreach ($thread as $key => $part) {
	$thread[$key]++;
	// silly but converts 01, 02, etc into 1, 2
	if ($key == 0) {
		$thread[$key]--;
	}
}
$comment_thread = implode('-', $thread);
?>
<div class="comment" <?php print $attributes; ?>>
  <div class="comment-number grey-text"><?php print $comment_thread; ?></div>
  <div class="comment-top-container">
    <div class="comment-title ferpa-protect">
      <?php print $title ?>
    </div>
    <div class="author ferpa-protect"><?php print $author; ?></div>
    <div class="submitted">
      <?php print t('Date: !datetime', array('!datetime' => $created)); ?>
    </div>
  </div>
  <?php if ($new): ?>
  <div class="new"><?php print $new ?></div>
  <?php endif; ?>
  <div class="comment_body_container ferpa-protect">
    <?php hide($content['links']); ?>
    <?php hide($content['rate_evoke']); ?>
  <?php print render($content); ?>
  </div>
  <?php if (!empty($content['rate_evoke'])): ?>
  <div class="comment_rating emotion_rating"><?php print render($content['rate_evoke']); ?></div>
  <?php endif; ?>
  <?php if (!empty($content['links'])): ?>
  <?php print render($content['links']); ?>
  <?php endif; ?>
  <div class="picture ferpa-protect">
  <?php print $picture; ?>
  </div>
</div>