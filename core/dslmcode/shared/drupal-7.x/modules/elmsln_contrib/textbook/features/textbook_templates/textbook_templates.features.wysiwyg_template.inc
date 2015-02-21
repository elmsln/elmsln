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
  $templates['lorem_ipsum'] = array(
    'title' => 'Lorem ipsum',
    'description' => 'Sample random latin to simulate paragraphs',
    'fid' => 0,
    'body' => '<p></p>
<p>Lorem ipsum dolor sit amet, elit fusce erat, arcu pretium et ultricies velit, parturient faucibus sit dignissim varius, dui nibh ut tellus mauris dolor. Cursus vulputate erat dolore arcu sit egestas, suspendilacus vel in fringilla elit. Fusce tempus ante congue faucibus odio sed, gravida eu libero, elit gravida pede a id varius tempus. Aut massa vel sagittis sed vel donec, et eros. Amet nunc vivamus, gravida suspendisse integer vivamus ligula. Ultrices sociosqu ornare duis, eget tempor quisque.</p>
<p>Vestibulum ut est, wisi velit, nulla sollicitudin morbi. Fermentum non wisi. Magna nec id sit consectetuer vel, montes mauris, scelerisque erat purus etiam nisl erat. Sit ut pulvinar quisque quisque. A ante, odio pharetra urna suspendisse nascetur metus. Dignissim dui nullam adipiscing amet, tincidunt tincidunt turpis. Duis a ipsum aliquam purus orci, in nec vel libero fusce, imperdiet quisque sem, in ac aenean ut, ac dolor scelerisque nibh nam.</p>
<p>Sapien vestibulum turpis, commodo arcu tortor massa faucibus molestie. Litora suspendisse etiam a tortor in. Ultricies fringilla. Hac vulputate donec auctor. Viverra at ultrices et mattis volutpat, aenean interdum nec. Condimentum a et amet quia, mi feugiat in suscipit, aliquet parhendrerit fames hymenaeos vel, quam bibendum et massa donec nunc.</p>
',
    'name' => 'lorem_ipsum',
  );
  $templates['magellan_navigation'] = array(
    'title' => 'Magellan navigation',
    'description' => 'This gives you a sticky navigation element that follows you down the page',
    'fid' => 0,
    'body' => '<div class="magellan-wrap">
	<div class="sticky-content-nav" data-magellan-expedition="fixed">
		<dl class="sub-nav">
			<dd data-magellan-arrival="vulture"><a href="#vulture">Vulture\'s Eye</a></dd>
			<dd data-magellan-arrival="terror"><a href="#terror">Terror</a></dd>
			<dd data-magellan-arrival="officers"><a href="#officers">Officers</a></dd>
			<dd data-magellan-arrival="breath"><a href="#breath">I gasped for breath</a></dd>
			<dd data-magellan-arrival="villains"><a href="#villains">Villains</a></dd>
		</dl>
	</div>
</div>
',
    'name' => 'magellan_navigation',
  );
  $templates['quote'] = array(
    'title' => 'Quote',
    'description' => 'Block quote, offset left with a border',
    'fid' => 0,
    'body' => '<p class="txtbk-pullquote">Above all was the sense of hearing acute. I heard all things in the heaven and in the earth. I heard many things in hell. How, then, am I mad?</p>
',
    'name' => 'quote',
  );
  $templates['table_of_terms'] = array(
    'title' => 'Table of terms',
    'description' => 'A cleanly formatted table of terms',
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
    'name' => 'table_of_terms',
  );
  $templates['table_style_2'] = array(
    'title' => 'Table style 2',
    'description' => 'A well made table for presenting figures of data with a left column heading',
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
    'name' => 'table_style_2',
  );
  $templates['topic_reading'] = array(
    'title' => 'Topic Reading',
    'description' => 'Use this for communicating Reading to students',
    'fid' => 0,
    'body' => '<h2>Step X: Complete the Topic Readings</h2>
<p>This topic uses one or more required readings and one or more optional readings. By completing these readings before studying the lecture, you will make the most effective use of both. As you read, remember to take good notes using your study sheets.</p>
<div class="textbook_box textbook_box_required">
  <h3>Required</h3>
  <ol>
    <li>&quot;<a href="link">Linked page title</a>&quot; (Source: The source you are linking to)</li>
  </ol>
</div>
<div class="textbook_box textbook_box_optional">
  <h3>Optional</h3>
  <ol>
    <li>&quot;<a href="link">Linked page title</a>&quot; (Source: The source you are linking to)</li>
    <li>&quot;<a href="link">Linked page title</a>&quot; (Note: A note about what you should pay attention to)</li>
  </ol>
</div>
',
    'name' => 'topic_reading',
  );
  return $templates;
}
