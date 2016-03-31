<?php
/**
 * @file
 * foundation_access_templates.features.wysiwyg_template.inc
 */

/**
 * Implements hook_wysiwyg_template_default_templates().
 */
function foundation_access_templates_wysiwyg_template_default_templates() {
  $templates = array();
  $templates['image'] = array(
    'title' => 'Image',
    'description' => 'This is an inline image that can be used in any rich text area.',
    'weight' => 5,
    'fid' => 7,
    'body' => '<figure class="image">
  <img alt="This is the images alt info." class="image__img" src="https://unsplash.it/1200/600">
  <cite class="image__cite">Here is the citation or photo credit for the image.</cite>
    <figcaption class="image__caption">
        <p>This is the caption for the image.</p>
    </figcaption>
</figure>',
    'format' => 'textbook_editor',
    'name' => 'image',
    'content_types' => array(),
  );
  $templates['image_boxed'] = array(
    'title' => 'Image Boxed',
    'description' => '',
    'weight' => 8,
    'fid' => 10,
    'body' => '<figure class="image image--boxed">
  <img alt="This is the images alt info." class="image__img" src="https://unsplash.it/1200/800/">
  <cite class="image__cite">Here is the citation or photo credit for the image.</cite>
    <figcaption class="image__caption">
        <p>This is the caption for the image.</p>
    </figcaption>
</figure>',
    'format' => 'textbook_editor',
    'name' => 'image_boxed',
    'content_types' => array(),
  );
  $templates['image_left'] = array(
    'title' => 'Image Left',
    'description' => '',
    'weight' => 6,
    'fid' => 8,
    'body' => '<figure class="image image--left">
  <img alt="This is the images alt info." class="image__img" src="https://unsplash.it/1200/600">
  <cite class="image__cite">Here is the citation or photo credit for the image.</cite>
    <figcaption class="image__caption">
        <p>This is the caption for the image.</p>
    </figcaption>
</figure>',
    'format' => 'textbook_editor',
    'name' => 'image_left',
    'content_types' => array(),
  );
  $templates['image_lightboxed'] = array(
    'title' => 'Image Lightboxed',
    'description' => 'This is an example of how to use the imagelightbox widget in conjuction with the image component.',
    'weight' => 9,
    'fid' => 11,
    'body' => '<figure class="image image--left">
  <a data-imagelightbox href="https://unsplash.it/1200/800/"><img alt="This is the images alt info." class="image__img" src="https://unsplash.it/1200/800/"></a>
  <cite class="image__cite">Here is the citation or photo credit for the image.</cite>
    <figcaption class="image__caption">
        <p>This is the caption for the image.</p>
    </figcaption>
</figure>',
    'format' => 'textbook_editor',
    'name' => 'image_lightboxed',
    'content_types' => array(),
  );
  $templates['image_right'] = array(
    'title' => 'Image Right',
    'description' => '',
    'weight' => 7,
    'fid' => 9,
    'body' => '<figure class="image image--right">
  <img alt="This is the images alt info." class="image__img" src="https://unsplash.it/1200/600/">
  <cite class="image__cite">Here is the citation or photo credit for the image.</cite>
    <figcaption class="image__caption">
        <p>This is the caption for the image.</p>
    </figcaption>
</figure>',
    'format' => 'textbook_editor',
    'name' => 'image_right',
    'content_types' => array(),
  );
  $templates['media_video'] = array(
    'title' => 'Media Video',
    'description' => 'Description',
    'weight' => 1,
    'fid' => 3,
    'body' => '<figure class="mediavideo"><div class="mediavideo__video-wrapper"><iframe frameborder="0" src="https://www.youtube.com/embed/UvEiSa6_EPA?rel=0&amp;showinfo=0"></iframe><script src="https://platform.vine.co/static/scripts/embed.js"></script></div></figure>',
    'format' => 'textbook_editor',
    'name' => 'media_video',
    'content_types' => array(),
  );
  $templates['media_video_thumbnail'] = array(
    'title' => 'Media Video Thumbnail',
    'description' => 'Description',
    'weight' => 2,
    'fid' => 0,
    'body' => '<figure class="mediavideo mediavideo--thumbnail"><a class="mediavideo__close icon-close-black" href="#" title="Click to stop and close video.">&nbsp;</a><div class="mediavideo__video-wrapper"><iframe allowfullscreen="" data-mediavideo-src="https://www.youtube.com/embed/UvEiSa6_EPA?rel=0&amp;showinfo=0" frameborder="0"></iframe></div><aside class="mediavideo__poster"><img src="https://unsplash.it/1200/800/"> <a class="mediavideo__open icon-play-black" href="#" title="Click to view video.">&nbsp;</a></aside></figure>',
    'format' => 'textbook_editor',
    'name' => 'media_video_thumbnail',
    'content_types' => array(),
  );
  $templates['media_video_thumbnail_right'] = array(
    'title' => 'Media Video Thumbnail Right',
    'description' => 'Description',
    'weight' => 3,
    'fid' => 5,
    'body' => '<figure class="mediavideo mediavideo--thumbnail-right"><a class="mediavideo__close icon-close-black" href="#" title="Click to stop and close video.">&nbsp;</a>
  <div class="mediavideo__video-wrapper">
    <iframe allowfullscreen="" data-mediavideo-src="https://www.youtube.com/embed/UvEiSa6_EPA?rel=0&amp;showinfo=0" frameborder="0">
    </iframe>
  </div>
  <aside class="mediavideo__poster"><img src="https://unsplash.it/1200/800/"> <a class="mediavideo__open icon-play-black" href="#" title="Click to view video.">&nbsp;</a>
  </aside>
</figure>',
    'format' => 'textbook_editor',
    'name' => 'media_video_thumbnail_right',
    'content_types' => array(),
  );
  $templates['media_video_with_poster'] = array(
    'title' => 'Media Video With Poster',
    'description' => 'STILL IN DEVELOPMENT. This uses a psudo lazy load technique to allow the play button to start the video.',
    'weight' => 4,
    'fid' => 6,
    'body' => '<figure class="mediavideo mediavideo--poster">
  <div class="mediavideo__video-wrapper">
    <iframe allowfullscreen="" data-mediavideo-src="https://www.youtube.com/embed/CKZLuYOnPCk?rel=0&amp;showinfo=0" frameborder="0">
    </iframe>
  </div>
  <aside class="mediavideo__poster"><img src="https://unsplash.it/1200/800/"> <a class="mediavideo__open icon-play-black" href="#" title="Click to view video.">&nbsp;</a>
  </aside>
</figure>',
    'format' => 'textbook_editor',
    'name' => 'media_video_with_poster',
    'content_types' => array(),
  );
  $templates['quote_left'] = array(
    'title' => 'Quote Left',
    'description' => '',
    'weight' => 11,
    'fid' => 13,
    'body' => '<p class="quote quote--left">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam ex nisl, congue id vehicula vel, malesuada at eros. Donec eu mi venenatis felis euismod gravida.</p>',
    'format' => 'textbook_editor',
    'name' => 'quote_left',
    'content_types' => array(),
  );
  $templates['quote_right'] = array(
    'title' => 'Quote Right',
    'description' => '',
    'weight' => 12,
    'fid' => 14,
    'body' => '<p class="quote quote--right">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam ex nisl, congue id vehicula vel, malesuada at eros. Donec eu mi venenatis felis euismod gravida.
</p>',
    'format' => 'textbook_editor',
    'name' => 'quote_right',
    'content_types' => array(),
  );
  return $templates;
}
