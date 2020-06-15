<video-player
crossorigin="anonymous"
accent-color="indigo"
source="<?php print file_create_url($referencing_entity->field_audio['und'][0]['uri']); ?>"
<?php if (isset($referencing_entity->field_poster['und'][0]['uri'])): ?>
  thumbnail-src="<?php print file_create_url($referencing_entity->field_poster['und'][0]['uri']); ?>"
<?php endif;?>
<?php
if (isset($referencing_entity->field_caption['und'][0]['uri'])) {
  $json = new stdClass();
  $json->kind = "subtitles";
  $json->srclang = "en";
  $json->label = "English";
  $json->src = file_create_url($referencing_entity->field_caption['und'][0]['uri']);
  print "tracks='[" . json_encode($json) . "]'";
}?>
>
</video-player>
