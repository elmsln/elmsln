
<a11y-media-player
accent-color="indigo"
audio-only
<?php if (isset($node->field_poster['und'][0]['uri'])): ?> thumbnail-src="<?php print file_create_url($node->field_poster['und'][0]['uri']); ?>"<?php endif;?>
>
  <source src="<?php print file_create_url($node->field_audio['und'][0]['uri']); ?>" type="audio/mp3">
  <?php if (isset($node->field_caption['und'][0]['uri'])): ?>
    <track label="English" kind="subtitles" srclang="en" src="<?php print file_create_url($node->field_caption['und'][0]['uri']); ?>" default>
  <?php endif;?>
</a11y-media-player>


