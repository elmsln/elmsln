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
    'weight' => 19,
    'fid' => 0,
    'body' => '<p><a class="button" href="#">Default Button</a> <a class="button success" href="#">Success Button</a> <a class="button secondary" href="#">Secondary Button</a> <a class="button alert" href="#">Alert Button</a> <a class="button info" href="#">Info Button</a> <a class="button disabled" href="#">Disabled Button</a></p>',
    'format' => 'textbook_editor',
    'name' => 'buttons',
    'content_types' => array(),
  );
  $templates['callout_panel'] = array(
    'title' => 'Callout Panel',
    'description' => 'Call attention to an item',
    'weight' => 11,
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
    'weight' => 9,
    'fid' => 0,
    'body' => '<div class="row">
  <div class="s10 push-s1 col">
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
    'weight' => 14,
    'fid' => 0,
    'body' => '<table class="responsive-table"><thead><tr><th>Table Header</th><th>Table Header</th><th>Table Header</th><th>Table Header</th></tr></thead><tbody><tr><td>Content Goes Here</td><td>This is longer content Donec id elit non mi porta gravida at eget metus.</td><td>Content Goes Here</td><td>Content Goes Here</td></tr><tr><td>Content Goes Here</td><td>This is longer Content Goes Here Donec id elit non mi porta gravida at eget metus.</td><td>Content Goes Here</td><td>Content Goes Here</td></tr><tr><td>Content Goes Here</td><td>This is longer Content Goes Here Donec id elit non mi porta gravida at eget metus.</td><td>Content Goes Here</td><td>Content Goes Here</td></tr></tbody></table>',
    'format' => 'textbook_editor',
    'name' => 'clean_table',
    'content_types' => array(),
  );
  $templates['flex_video'] = array(
    'title' => 'Flex Video',
    'description' => 'Flexible video template for embedding youtube / other sources',
    'weight' => 13,
    'fid' => 0,
    'body' => '<div class="video-container"><iframe allowfullscreen frameborder="0" height="225" mozallowfullscreen src="//www.youtube.com/embed/4oZaA5BOjNI" webkitallowfullscreen width="400"></iframe></div>',
    'format' => 'textbook_editor',
    'name' => 'flex_video',
    'content_types' => array(),
  );
  $templates['grid_of_video'] = array(
    'title' => 'Grid of Video',
    'description' => 'a grid of three videos in a row that scale correctly',
    'weight' => 10,
    'fid' => 0,
    'body' => '<ul class="small-block-grid-3"><li><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" title="advisory title here" webkitallowfullscreen="" width="200"></iframe></div></li><li><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" title="advisory title here" webkitallowfullscreen="" width="200"></iframe></div></li><li><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" title="advisory title here" webkitallowfullscreen="" width="200"></iframe></div></li></ul>',
    'format' => 'textbook_editor',
    'name' => 'grid_of_video',
    'content_types' => array(),
  );
  $templates['heading_solid_bar'] = array(
    'title' => 'Heading solid bar',
    'description' => 'A simple heading on a solid bar.',
    'weight' => 5,
    'fid' => 0,
    'body' => '<h3 class="solid-bar-heading grey lighten-3 black-text">Heading 3
</h3>',
    'format' => 'textbook_editor',
    'name' => 'heading_solid_bar',
    'content_types' => array(),
  );
  $templates['icon_header'] = array(
    'title' => 'Icon header',
    'description' => 'Head name with an icon leading it',
    'weight' => 1,
    'fid' => 0,
    'body' => '<h3 class="hrlines"><span><i class="material-icons black white-text circle">assignment</i> Assignment directions</span></h3>',
    'format' => 'textbook_editor',
    'name' => 'icon_header',
    'content_types' => array(),
  );
  $templates['line_header'] = array(
    'title' => 'Line header',
    'description' => 'Header centered with a line breaking the content up.',
    'weight' => 2,
    'fid' => 0,
    'body' => '<h3 class="headinglines"><span>Heading 4</span></h3>',
    'format' => 'textbook_editor',
    'name' => 'line_header',
    'content_types' => array(),
  );
  $templates['lorem_ipsum'] = array(
    'title' => 'Lorem ipsum',
    'description' => 'Sample random latin to simulate paragraphs',
    'weight' => 20,
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
  $templates['materialize_card'] = array(
    'title' => 'Materialize Card',
    'description' => 'Design element to present information as a card',
    'weight' => 6,
    'fid' => 0,
    'body' => '<div class="materialize-card-wrapper col s4"><div class="card"><div class="card-image waves-effect waves-block waves-light"><img class="activator" src="//materializecss.com/images/office.jpg"></div>
<div class="card-content"><span class="card-title activator grey-text text-darken-4">Card Title<i class="material-icons right">more_vert</i></span>
<p><a href="#">This is a link</a></p></div>
<div class="card-reveal"><span class="card-title grey-text text-darken-4">Card Title<i class="material-icons right">close</i></span>
<p>Here is some more information about this product that is only revealed once clicked on.</p></div></div></div>',
    'format' => 'textbook_editor',
    'name' => 'materialize_card',
    'content_types' => array(),
  );
  $templates['materialize_collapsible'] = array(
    'title' => 'Materialize Collapsible',
    'description' => 'implements materialize style collapse',
    'weight' => 7,
    'fid' => 0,
    'body' => '<ul class="collapsible popout" data-collapsible="accordion" role="tablist">
    <li class="collapsible-li">
    	<a href="#" class="collapsible-header vibrate cis-lmsless-background black-text"><i class="material-icons">directions_walk</i>1. Take action</a>
  		<div class="collapsible-body cis-lmsless-background">
		    <div class="elmsln-collapsible-body">
		      <p>Content</p>
		    </div>
	  	</div>
  	</li>
    <li class="collapsible-li">
    	<a href="#" class="collapsible-header vibrate cis-lmsless-background black-text"><i class="material-icons">forward</i>2. Move forward</a>
  		<div class="collapsible-body cis-lmsless-background">
		    <div class="elmsln-collapsible-body">
		      <p>Content</p>
		    </div>
	  	</div>
  	</li>
    <li class="collapsible-li">
    	<a href="#" class="collapsible-header vibrate cis-lmsless-background black-text"><i class="material-icons">slow_motion_video</i>3. Ignore detractors</a>
  		<div class="collapsible-body cis-lmsless-background">
		    <div class="elmsln-collapsible-body">
		      <p>Content</p>
		    </div>
	  	</div>
  	</li>
    <li class="collapsible-li">
    	<a href="#" class="collapsible-header vibrate cis-lmsless-background black-text"><i class="material-icons">payment</i>4. Pay forward Process</a>
  		<div class="collapsible-body cis-lmsless-background">
		    <div class="elmsln-collapsible-body">
		      <p>Content</p>
		    </div>
	  	</div>
  	</li>
    <li class="collapsible-li">
    	<a href="#" class="collapsible-header vibrate cis-lmsless-background black-text"><i class="material-icons">account_balance</i>5. Change industry</a>
  		<div class="collapsible-body cis-lmsless-background">
		    <div class="elmsln-collapsible-body">
		      <p>Content</p>
		    </div>
	  	</div>
  	</li>
</ul>',
    'format' => 'textbook_editor',
    'name' => 'materialize_collapsible',
    'content_types' => array(),
  );
  $templates['paperstack'] = array(
    'title' => 'Paperstack',
    'description' => 'A stack of papers, good for examples / callouts.',
    'weight' => 5,
    'fid' => 0,
    'body' => '<div class="egletter">
  <h3><i class="material-icons circle black white-text">directions_walk</i><span>Example</span></h3>
  <p>This is a great example, one of the best example I\'ve ever seen. In fact, it\'s the best example ever produced and it says a lot about your content that you are about to see here.
  </p>
</div>',
    'format' => 'textbook_editor',
    'name' => 'paperstack',
    'content_types' => array(),
  );
  $templates['quote'] = array(
    'title' => 'Quote',
    'description' => 'Block quote, offset left with a border',
    'weight' => 8,
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
    'weight' => 12,
    'fid' => 0,
    'body' => '<div class="panel"><h5>This is a regular panel.</h5><p>It has an easy to override visual style, and is appropriately subdued.</p></div>',
    'format' => 'textbook_editor',
    'name' => 'regular_panel',
    'content_types' => array(),
  );
  $templates['secondary_sources_list'] = array(
    'title' => 'secondary sources list',
    'description' => 'A collection of secondary sources / external links.',
    'weight' => 4,
    'fid' => 0,
    'body' => '<ul class="collection">
  <li class="collection-item">
    <a target="_blank" href="https://youtube.com/">Youtube video 1</a><a target="_blank" class="secondary-content" href="https://youtube.com/"><i class="material-icons">play_circle_outlined</i></a>
  </li>
  <li class="collection-item">
    <a target="_blank" href="https://youtube.com/">Youtube video 2</a><a target="_blank" class="secondary-content" href="https://youtube.com/"><i class="material-icons">play_circle_outlined</i></a>
  </li>
  <li class="collection-item">
    <a target="_blank" href="https://youtube.com/">Youtube video 3</a><a target="_blank" class="secondary-content" href="https://youtube.com/"><i class="material-icons">play_circle_outlined</i></a>
  </li>
  <li class="collection-item">
    <a target="_blank" href="https://youtube.com/">Youtube video 4</a><a target="_blank" class="secondary-content" href="https://youtube.com/"><i class="material-icons">play_circle_outlined</i></a>
  </li>
</ul>',
    'format' => 'textbook_editor',
    'name' => 'secondary_sources_list',
    'content_types' => array(),
  );
  $templates['table_of_terms'] = array(
    'title' => 'Table of terms',
    'description' => 'A cleanly formatted table of terms',
    'weight' => 15,
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
    'weight' => 16,
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
    'weight' => 3,
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
    'weight' => 17,
    'fid' => 0,
    'body' => '<div class="panel callout radius row">
  <div class="s6 col">
    <ul><li>Item 1</li><li>Item 2</li><li>Item 3</li><li>Item 4</li>
    </ul>
  </div>
  <div class="s6 col"><img height="100px" src="https://marlaongtao.files.wordpress.com/2013/11/plato-cave.jpg" width="100%">
  </div>
</div>',
    'format' => 'textbook_editor',
    'name' => 'two_column_list_image',
    'content_types' => array(),
  );
  $templates['two_column_list_video'] = array(
    'title' => 'Two column list video',
    'description' => 'A two column template with a bulleted list and video to the right of it',
    'weight' => 18,
    'fid' => 0,
    'body' => '<div class="panel callout radius row"><div class="s6 col"><ul><li>Item 1</li><li>Item 2</li><li>Item 3</li><li>Item 4</li></ul></div><div class="s6 col"><div class="flex-video widescreen"><iframe allowfullscreen="" frameborder="1" height="100" mozallowfullscreen="" name="name here" scrolling="yes" src="https://www.youtube-nocookie.com/embed/4oZaA5BOjNI?rel=0" webkitallowfullscreen="" width="200"></iframe></div></div></div>',
    'format' => 'textbook_editor',
    'name' => 'two_column_list_video',
    'content_types' => array(),
  );
  $templates['vocab_term'] = array(
    'title' => 'Vocab term',
    'description' => 'A single Vocabulary term',
    'weight' => 5,
    'fid' => 0,
    'body' => '<div class="card">
  <div class="card-content card-panel light-blue darken-3"><span class="card-title activator white-text">Vocab term<a href="#reveal-info" class="white-text"><i class="material-icons right">more_vert</i></a></span>
  </div>
  <div class="card-reveal white black-text"><span class="card-title">Leading<a href="#close-more-info" class="black-text"><i class="material-icons right">close</i></a></span>
    <p>The definition of the term.
    </p>
  </div>
</div>',
    'format' => 'textbook_editor',
    'name' => 'vocab_term',
    'content_types' => array(),
  );
  return $templates;
}
