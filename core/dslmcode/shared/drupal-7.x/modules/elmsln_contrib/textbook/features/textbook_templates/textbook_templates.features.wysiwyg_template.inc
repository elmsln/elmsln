<?php
/**
 * @file
 * textbook_templates.features.wysiwyg_template.inc
 */

/**
 * Implements hook_wysiwyg_template_default_templates().
 */
function textbook_templates_wysiwyg_template_default_templates() {
  $templates = array();
  $templates['buttons'] = array(
    'title' => 'Buttons',
    'description' => 'Some example buttons that are links, styled to look like buttons to improve accessibility.',
    'weight' => 0,
    'fid' => 0,
    'body' => '<p><a class="button" href="#">Default Button</a> <a class="button success" href="#">Success Button</a> <a class="button secondary" href="#">Secondary Button</a> <a class="button alert" href="#">Alert Button</a> <a class="button info" href="#">Info Button</a> <a class="button disabled" href="#">Disabled Button</a></p>',
    'format' => 'textbook_editor',
    'name' => 'buttons',
    'content_types' => array(),
  );
  $templates['callout_panel'] = array(
    'title' => 'Callout Panel',
    'description' => 'Call attention to an item',
    'weight' => 0,
    'fid' => 0,
    'body' => '<div class="panel callout radius">
  <h4>This is a callout panel.</h4>
  <p>It\'s a little ostentatious, but useful for important content.</p>
</div>',
    'format' => 'textbook_editor',
    'name' => 'callout_panel',
    'content_types' => array(),
  );
  $templates['case_study'] = array(
    'title' => 'Case Study',
    'description' => 'Call out area for case studies, icon and slight mark up.',
    'weight' => 0,
    'fid' => 0,
    'body' => '<div class="row">
  <div class="small-10 small-push-1 columns">
    <div class="icon-online-black etb-modal-icons" style="width: 8rem;height: 6rem;">
    </div>
    <h4>Case Study
    </h4>
    <p>Things Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry\'s standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type <a href="#" target="_blank">specimen</a> book.
    </p>
    <p>
    </p>
  </div>
</div>',
    'format' => 'textbook_editor',
    'name' => 'case_study',
    'content_types' => array(),
  );
  $templates['clean_table'] = array(
    'title' => 'Clean Table',
    'description' => 'A Clean example tabl',
    'weight' => 7,
    'fid' => 0,
    'body' => '<table class="responsive-table"><thead><tr><th>Table Header</th><th>Table Header</th><th>Table Header</th><th>Table Header</th></tr></thead><tbody><tr><td>Content Goes Here</td><td>This is longer content Donec id elit non mi porta gravida at eget metus.</td><td>Content Goes Here</td><td>Content Goes Here</td></tr><tr><td>Content Goes Here</td><td>This is longer Content Goes Here Donec id elit non mi porta gravida at eget metus.</td><td>Content Goes Here</td><td>Content Goes Here</td></tr><tr><td>Content Goes Here</td><td>This is longer Content Goes Here Donec id elit non mi porta gravida at eget metus.</td><td>Content Goes Here</td><td>Content Goes Here</td></tr></tbody></table>',
    'format' => 'textbook_editor',
    'name' => 'clean_table',
    'content_types' => array(),
  );
  $templates['flex_video'] = array(
    'title' => 'Flex Video',
    'description' => 'Flexible video template for embedding youtube / other sources',
    'weight' => 5,
    'fid' => 0,
    'body' => '<div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="0" height="225" mozallowfullscreen="" src="//www.youtube.com/embed/4oZaA5BOjNI" webkitallowfullscreen="" width="400"></iframe></div>',
    'format' => 'textbook_editor',
    'name' => 'flex_video',
    'content_types' => array(),
  );
  $templates['grid_of_video'] = array(
    'title' => 'Grid of Video',
    'description' => 'a grid of three videos in a row that scale correctly',
    'weight' => -5,
    'fid' => 0,
    'body' => '<ul class="small-block-grid-3"><li><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" title="advisory title here" webkitallowfullscreen="" width="200"></iframe></div></li><li><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" title="advisory title here" webkitallowfullscreen="" width="200"></iframe></div></li><li><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" title="advisory title here" webkitallowfullscreen="" width="200"></iframe></div></li></ul>',
    'format' => 'textbook_editor',
    'name' => 'grid_of_video',
    'content_types' => array(),
  );
  $templates['lorem_ipsum'] = array(
    'title' => 'Lorem ipsum',
    'description' => 'Sample random latin to simulate paragraphs',
    'weight' => 6,
    'fid' => 0,
    'body' => '<p></p>
<p>Lorem ipsum dolor sit amet, elit fusce erat, arcu pretium et ultricies velit, parturient faucibus sit dignissim varius, dui nibh ut tellus mauris dolor. Cursus vulputate erat dolore arcu sit egestas, suspendilacus vel in fringilla elit. Fusce tempus ante congue faucibus odio sed, gravida eu libero, elit gravida pede a id varius tempus. Aut massa vel sagittis sed vel donec, et eros. Amet nunc vivamus, gravida suspendisse integer vivamus ligula. Ultrices sociosqu ornare duis, eget tempor quisque.</p>
<p>Vestibulum ut est, wisi velit, nulla sollicitudin morbi. Fermentum non wisi. Magna nec id sit consectetuer vel, montes mauris, scelerisque erat purus etiam nisl erat. Sit ut pulvinar quisque quisque. A ante, odio pharetra urna suspendisse nascetur metus. Dignissim dui nullam adipiscing amet, tincidunt tincidunt turpis. Duis a ipsum aliquam purus orci, in nec vel libero fusce, imperdiet quisque sem, in ac aenean ut, ac dolor scelerisque nibh nam.</p>
<p>Sapien vestibulum turpis, commodo arcu tortor massa faucibus molestie. Litora suspendisse etiam a tortor in. Ultricies fringilla. Hac vulputate donec auctor. Viverra at ultrices et mattis volutpat, aenean interdum nec. Condimentum a et amet quia, mi feugiat in suscipit, aliquet parhendrerit fames hymenaeos vel, quam bibendum et massa donec nunc.</p>
',
    'format' => 'plain_text',
    'name' => 'lorem_ipsum',
    'content_types' => array(),
  );
  $templates['magellan_navigation'] = array(
    'title' => 'Magellan navigation item',
    'description' => 'If you have magellan navigation active this is the way to define a heading in the page.',
    'weight' => 10,
    'fid' => 0,
    'body' => '<a name="machinename"></a><h2 data-magellan-destination="machinename">Title</h2>',
    'format' => 'plain_text',
    'name' => 'magellan_navigation',
    'content_types' => array(),
  );
  $templates['quote'] = array(
    'title' => 'Quote',
    'description' => 'Block quote, offset left with a border',
    'weight' => 5,
    'fid' => 0,
    'body' => '<p class="txtbk-pullquote">Above all was the sense of hearing acute. I heard all things in the heaven and in the earth. I heard many things in hell. How, then, am I mad?</p>
',
    'format' => 'plain_text',
    'name' => 'quote',
    'content_types' => array(),
  );
  $templates['regular_panel'] = array(
    'title' => 'Regular Panel',
    'description' => 'Regular panel of content',
    'weight' => 0,
    'fid' => 0,
    'body' => '<div class="panel"><h5>This is a regular panel.</h5><p>It has an easy to override visual style, and is appropriately subdued.</p></div>',
    'format' => 'textbook_editor',
    'name' => 'regular_panel',
    'content_types' => array(),
  );
  $templates['table_of_terms'] = array(
    'title' => 'Table of terms',
    'description' => 'A cleanly formatted table of terms',
    'weight' => 8,
    'fid' => 0,
    'body' => '<table border="1" cellpadding="0" cellspacing="0" class="textbook_table_1" summary="You can print this study sheet and use it to take notes.">
  <caption>Lesson x.x Terms Study Sheet</caption>
  <thead>
    <tr>
      <th scope="row">Terms</th>
      <th scope="col">Description/Notes</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th scope="row">The Term</th>
      <td>
        <p></p>
      </td>
    </tr>
    <tr>
      <th scope="row">The Term</th>
      <td>
        <p></p>
      </td>
    </tr>
    <tr>
      <th scope="row">The Term</th>
      <td>
        <p></p>
      </td>
    </tr>
    <tr>
      <th scope="row">The Term</th>
      <td>
        <p></p>
      </td>
    </tr>
  </tbody>
</table>
<p></p>
',
    'format' => 'plain_text',
    'name' => 'table_of_terms',
    'content_types' => array(),
  );
  $templates['table_style_2'] = array(
    'title' => 'Table style 2',
    'description' => 'A well made table for presenting figures of data with a left column heading',
    'weight' => 9,
    'fid' => 0,
    'body' => '<table border="1" cellpadding="0" cellspacing="0" class="textbook_table_2" summary="Figure 1-A">
  <caption>Figure 1-A</caption>
  <tbody>
    <tr>
      <th scope="row">Item</th>
      <td>Property 1</td>
      <td>Property&nbsp;2</td>
      <td>Property&nbsp;3</td>
    </tr>
    <tr>
      <th scope="row">Item</th>
      <td>Property&nbsp;1</td>
      <td>Property&nbsp;2</td>
      <td>Property&nbsp;3</td>
    </tr>
    <tr>
      <th scope="row">Item</th>
      <td>Property&nbsp;1</td>
      <td>Property&nbsp;2</td>
      <td>Property&nbsp;3</td>
    </tr>
    <tr>
      <th scope="row">Item</th>
      <td>Property&nbsp;1</td>
      <td>Property&nbsp;2</td>
      <td>Property&nbsp;3</td>
    </tr>
  </tbody>
</table>
<p></p>
',
    'format' => 'plain_text',
    'name' => 'table_style_2',
    'content_types' => array(),
  );
  $templates['topic_reading'] = array(
    'title' => 'Topic Reading',
    'description' => 'Use this for communicating Reading to students',
    'weight' => 4,
    'fid' => 0,
    'body' => '<h2>Step X: Complete the Topic Readings</h2>
<p>This topic uses one or more required readings and one or more optional readings. By completing these readings before studying the lecture, you will make the most effective use of both. As you read, remember to take good notes using your study sheets.</p>
<div class="textbook_box textbook_box_required">
  <h3>Required</h3>
  <ol class="list-colorluminance" data-colorluminance="#ff8888">
    <li>&quot;<a href="link">Linked page title</a>&quot; (Source: The source you are linking to)</li>
  </ol>
</div>
<div class="textbook_box textbook_box_optional">
  <h3>Optional</h3>
  <ol class="list-colorluminance" data-colorluminance="#80c0e0">
    <li>&quot;<a href="link">Linked page title</a>&quot; (Source: The source you are linking to)</li>
    <li>&quot;<a href="link">Linked page title</a>&quot; (Note: A note about what you should pay attention to)</li>
  </ol>
</div>
',
    'format' => 'plain_text',
    'name' => 'topic_reading',
    'content_types' => array(),
  );
  $templates['two_column_list_image'] = array(
    'title' => 'Two column list image',
    'description' => 'A two column layout of a bulleted list with an image to the right',
    'weight' => 0,
    'fid' => 0,
    'body' => '<div class="panel callout radius row">
  <div class="small-6 columns">
    <ul><li>Item 1</li><li>Item 2</li><li>Item 3</li><li>Item 4</li>
    </ul>
  </div>
  <div class="small-6 columns"><img height="100px" src="https://marlaongtao.files.wordpress.com/2013/11/plato-cave.jpg" width="100%">
  </div>
</div>',
    'format' => 'textbook_editor',
    'name' => 'two_column_list_image',
    'content_types' => array(),
  );
  $templates['two_column_list_video'] = array(
    'title' => 'Two column list video',
    'description' => 'A two column template with a bulleted list and video to the right of it',
    'weight' => 0,
    'fid' => 0,
    'body' => '<div class="panel callout radius row"><div class="small-6 columns"><ul><li>Item 1</li><li>Item 2</li><li>Item 3</li><li>Item 4</li></ul></div><div class="small-6 columns"><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" webkitallowfullscreen="" width="200"></iframe></div></div></div>',
    'format' => 'textbook_editor',
    'name' => 'two_column_list_video',
    'content_types' => array(),
  );
  return $templates;
}
