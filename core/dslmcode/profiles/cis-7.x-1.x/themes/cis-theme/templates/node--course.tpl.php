<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node 1's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $display_submitted: whether submission information should be displayed.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
  $author = NULL;
  $author_name = '';
  // verify that author exists
  if (isset($node->field_course_author['und'])) {
     $author = node_load($node->field_course_author['und'][0]['target_id']);
    $author_name = $author->field_display_name['und'][0]['safe_value'];
  }
  $course_abrev = $node->title;
  $course_number = '';
  // this is looking for a nice NAME NUM split in the title
  // example: art 100
  $parts = explode(' ', $node->title);
  if (count($parts) == 2) {
    $course_abrev = $parts[0];
    $course_number = $parts[1];
  }
?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="row course_top_container">
    <div class="row course_flag_row">
      <div class="large-1 columns course_flag unit-bg-color">
        <div class="course_flag_name"><?php print $course_abrev; ?></div>
        <div class="course_flag_number"><?php print $course_number; ?></div>
      </div>
      <div class="large-11 columns">
        <?php if (isset($node->field_course_title['und'])) : ?>
          <h1 id="page-title" class="title"><?php print check_markup($node->field_course_title['und'][0]['value'], 'textbook_editor'); ?></h1>
        <?php endif;?>
      </div>
    </div>
    <div class="row course_overview_row">
      <div class="large-3 columns">
        <?php if (isset($author_name)) : ?><h3 class="course_author_name"><?php print $author_name; ?></h3><?php endif; ?>
        <?php if (isset($content['field_academic_home'])) : ?><div class="unit-color"><?php print render($content['field_academic_home']); ?></div><?php endif; ?>
        <?php if (isset($content['field_program_classification'])) : ?><div class="course_program"><?php print render($content['field_program_classification']); ?></div><?php endif; ?>
        <?php if (isset($content['field_credits'])) : ?><div class="course_credits"><?php print format_plural($content['field_credits'][0]['#markup'], '1 Credit', '@count Credits'); ?></div><?php endif; ?>
        <?php if (isset($content['field_special_classification'])) : ?><div class="course_special_classification"><?php print render($content['field_special_classification']); ?></div><?php endif; ?>
        <?php if (isset($content['field_first_offered'])) : ?><div class="course_first_offered"><?php print render($content['field_first_offered']); ?></div><?php endif; ?>
        <?php //<div class="course_last_offered"><div class="field field-type-datetime field-label-inline clearfix field-wrapper"><div class="field-label">Last Offered:&nbsp;</div><span>Calculated</span></div></div>?>
        <?php if (isset($content['field_sample_syllabus'])) : ?><div class="course_sample_syllabus"><a title="<?php print $node->title . ' Sample syllabus'; ?>" alt="<?php print $node->title . ' Sample syllabus'; ?>" href="<?php print $content['field_sample_syllabus'][0]['#markup']; ?>" rel="shadowbox"><button class="button unit-bg-color">Sample Syllabus</button></a></div><?php endif; ?>
        <?php //<div class="course_button_enroll"><button class="button unit-bg-color">Enroll</button></div> ?>
        <?php //<div class="course_button_question"><button class="button gray-button">Ask a Question</button></div> ?>
      </div>
      <div class="large-9 columns">
        <?php if (isset($content['field_author_video'])) : print '<div class="course_video_container unit-color">' . render($content['field_author_video']) . '</div>'; endif; ?>
        <h2 class="course_overview"><?php print t('Overview'); ?></h2>
        <?php print render($content['body']); ?>
      </div>
    </div>
  </div>
  <div class="dark-triangle-down border-step-1"></div>
  <div class="row course_info">
  <div class="large-3 columns course_info_images">
  <?php if (isset($content['field_screenshot'])) : print render($content['field_screenshot']); endif; ?>
  </div>
  <?php if (isset($node->field_long_description['und'])) : ?>
  <div class="large-9 columns course_info_about">
  <?php if (!is_null($author)) : ?>
    <div class="course_author_block">
      <h4 class="course_author_name">
        <?php print $author->field_display_name['und'][0]['safe_value']; ?>
      </h4>
      <div class="unit-color course_author_pro_title">
        <?php print $author->field_professional_title['und'][0]['safe_value']; ?>
      </div>
      <div class="course_author_profile">
      <?php
        if (isset($author->field_headshot['und'])) {
          $headshot = $author->field_headshot['und'][0];
          $hero_image = array(
            'style_name' => 'course_author_thumb',
            'path' => $headshot['uri'],
            'width' => '95px',
            'height' => '95px',
            'alt' => $headshot['alt'],
            'title' => $headshot['title'],
          );
          print theme('image_style',$hero_image);
        }
      ?>
        <?php print $author->body['und'][0]['summary']; ?>
      </div>
      <div class="course_author_view_profile">
        <?php print l(t('View profile'), 'node/' . $author->nid, array('attributes' => array('class' => 'cis_dark_text'))); ?>
       </div>
    </div>
  <?php endif; ?>
  <div class="cis_text_on_white"><?php print $node->field_long_description['und'][0]['safe_value']; ?></div>
  </div>
  <?php endif; ?>
</div>
<div class="row course_topics">
<?php if (isset($node->field_topics_covered_text['und'])) : ?>
  <h2 class="course_topics_heading"><?php print t("Topics we'll cover"); ?></h2>
  <div class="large-6 columns course_info_about">
  <?php print $node->field_topics_covered_text['und'][0]['safe_value']; ?>
  </div>
  <?php endif; ?>
</div>
<div class="row course_readings">
<?php if (isset($node->field_course_readings['und'])) : ?>
  <h2 class="course_readings_heading"><?php print t("Readings"); ?></h2>
  <div class="large-6 columns course_info_about">
  <?php print $node->field_course_readings['und'][0]['safe_value']; ?>
  </div>
  <?php endif; ?>
</div>
<div class="light-triangle-down border-step-3 triangle-overflow"></div>
</article>
