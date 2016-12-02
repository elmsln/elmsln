<?php
  // render an iframe based on passed in values
  // Variables
  //  $id - content id
  //  $class - classes to apply
  //  $link - link to what the frame is pointing to
  //  $width - width of the frame
  //  $height - height of the frame
  //  $hypothesis - possible xAPI hypothesis
  //  $response - the full response object from the CIS object request
  $attributes = array();
  // special support for video
  if (isset($response['field_video']) && isset($response['field_video']['metadata']) && isset($response['field_video']['metadata']['duration'])) {
    $attributes = array('data-duration' => $response['field_video']['metadata']['duration']);
  }
  // special support for audio
  if (isset($response['field_audio']) && isset($response['field_audio']['metadata']) && isset($response['field_audio']['metadata']['duration'])) {
    $attributes = array('data-duration' => $response['field_audio']['metadata']['duration']);
  }
?>
<iframe <?php print drupal_attributes($attributes); ?> id="<?php print $id; ?>" class="<?php print $class; ?>" src="<?php print $link; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" data-xapi-hypothesis="<?php print $hypothesis; ?>" data-course-competency="<?php print $competency; ?>"></iframe>
