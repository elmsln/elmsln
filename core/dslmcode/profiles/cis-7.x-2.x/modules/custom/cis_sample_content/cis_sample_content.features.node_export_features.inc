<?php
/**
 * @file
 * cis_sample_content.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function cis_sample_content_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  (object) array(
      \'vid\' => \'16\',
      \'uid\' => \'1\',
      \'title\' => \'Guided Tour\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'d7d8c5fd-f098-433a-aa2a-fcd152aa0969\',
      \'nid\' => \'16\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'057d86fa-5240-44bd-8448-d535e3a5480a\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>\\r\\n  Lorem ipsum dolor sit amet, elit fusce erat, arcu pretium et ultricies velit, parturient faucibus sit dignissim varius, dui nibh ut tellus mauris dolor. Cursus vulputate erat dolore arcu sit egestas, suspendilacus vel in fringilla elit. Fusce tempus ante congue faucibus odio sed, gravida eu libero, elit gravida pede a id varius tempus. Aut massa vel sagittis sed vel donec, et eros. Amet nunc vivamus, gravida suspendisse integer vivamus ligula. Ultrices sociosqu ornare duis, eget tempor quisque.\\r\\n</p>\\r\\n<div id=\\"examplecontent\\">\\r\\n  <p>\\r\\n    Vestibulum ut est, wisi velit, nulla sollicitudin morbi. Fermentum non wisi. Magna nec id sit consectetuer vel, montes mauris, scelerisque erat purus etiam nisl erat. Sit ut pulvinar quisque quisque. A ante, odio pharetra urna suspendisse nascetur metus. Dignissim dui nullam adipiscing amet, tincidunt tincidunt turpis. Duis a ipsum aliquam purus orci, in nec vel libero fusce, imperdiet quisque sem, in ac aenean ut, ac dolor scelerisque nibh nam.\\r\\n  </p>\\r\\n</div>\\r\\n<p></p>\\r\\n<div class=\\"textbook_box textbook_box_required\\" id=\\"examplerequired\\">\\r\\n  <h3>\\r\\n    Steps to completion\\r\\n  </h3>\\r\\n  <ol>\\r\\n    <li>Review Sample Lessons and complete their related activities.</li>\\r\\n    <li>Complete Quiz at the end of this lesson</li>\\r\\n    <li><strong>Optional:</strong>&nbsp;Use example external tool to visualize your work.</li>\\r\\n  </ol>\\r\\n</div>\\r\\n<p>\\r\\n  <iframe allowfullscreen=\\"\\" frameborder=\\"0\\" height=\\"480\\" id=\\"youtubeexample\\" src=\\"//www.youtube-nocookie.com/embed/-DUo4StA8tY?rel=0\\" width=\\"100%\\"></iframe>\\r\\n</p>\\r\\n<table align=\\"center\\" border=\\"1\\" cellpadding=\\"1\\" cellspacing=\\"1\\" class=\\"textbook_table_2\\" height=\\"165\\" summary=\\"This table lists the amount of required and optional resources to view for this lesson.  It also includes the amount of lesson activities and the running time of the lectures. \\" width=\\"500\\">\\r\\n  <caption>\\r\\n    Lesson 5 - Budgeting Time\\r\\n  </caption>\\r\\n  <thead>\\r\\n    <tr>\\r\\n      <th scope=\\"row\\">\\r\\n        Lesson\\r\\n      </th>\\r\\n      <th scope=\\"col\\">\\r\\n        Number of Required Resources\\r\\n      </th>\\r\\n      <th scope=\\"col\\">\\r\\n        Number of Optional Resources\\r\\n      </th>\\r\\n      <th scope=\\"col\\">\\r\\n        Number of Lesson Activities\\r\\n      </th>\\r\\n      <th scope=\\"col\\">\\r\\n        Duration of Lectures\\r\\n      </th>\\r\\n    </tr>\\r\\n  </thead>\\r\\n  <tbody>\\r\\n    <tr>\\r\\n      <th scope=\\"row\\">\\r\\n        5.1\\r\\n      </th>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        13\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        3\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        1\\r\\n      </td>\\r\\n      <td style=\\"white-space: nowrap; text-align: right;\\">\\r\\n        (1 hour, 12 minutes) 1:12\\r\\n      </td>\\r\\n    </tr>\\r\\n    <tr>\\r\\n      <th scope=\\"row\\">\\r\\n        5.2\\r\\n      </th>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        12\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        6\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        1\\r\\n      </td>\\r\\n      <td style=\\"white-space: nowrap; text-align: right;\\">\\r\\n        (1 hour, 16 minutes) 1:16\\r\\n      </td>\\r\\n    </tr>\\r\\n    <tr>\\r\\n      <th scope=\\"row\\">\\r\\n        5.3\\r\\n      </th>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        7\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        7\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        1\\r\\n      </td>\\r\\n      <td style=\\"white-space: nowrap; text-align: right;\\">\\r\\n        (1 hour, 06 minutes) 1:06\\r\\n      </td>\\r\\n    </tr>\\r\\n    <tr>\\r\\n      <th scope=\\"rw\\">\\r\\n        5.4\\r\\n      </th>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        11\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        6\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        1\\r\\n      </td>\\r\\n      <td style=\\"white-space: nowrap; text-align: right;\\">\\r\\n        (1 hour, 18 minutes) 1:18\\r\\n      </td>\\r\\n    </tr>\\r\\n    <tr>\\r\\n      <th scope=\\"row\\"></th>\\r\\n      <td style=\\"text-align: right;\\"></td>\\r\\n      <td style=\\"text-align: right;\\"></td>\\r\\n      <td style=\\"text-align: right;\\"></td>\\r\\n      <td style=\\"white-space: nowrap; text-align: right;\\"></td>\\r\\n    </tr>\\r\\n    <tr>\\r\\n      <th scope=\\"row\\">\\r\\n        Totals&nbsp; for Lesson\\r\\n      </th>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        43\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        2\\r\\n      </td>\\r\\n      <td style=\\"text-align: right;\\">\\r\\n        4\\r\\n      </td>\\r\\n      <td style=\\"white-space: nowrap; text-align: right;\\">\\r\\n        (4 hours, 52 minutes) 4:52\\r\\n      </td>\\r\\n    </tr>\\r\\n  </tbody>\\r\\n</table>\\r\\n<p></p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => "<p>\\n  Lorem ipsum dolor sit amet, elit fusce erat, arcu pretium et ultricies velit, parturient faucibus sit dignissim varius, dui nibh ut tellus mauris dolor. Cursus vulputate erat dolore arcu sit egestas, suspendilacus vel in fringilla elit. Fusce tempus ante congue faucibus odio sed, gravida eu libero, elit gravida pede a id varius tempus. Aut massa vel sagittis sed vel donec, et eros. Amet nunc vivamus, gravida suspendisse integer vivamus ligula. Ultrices sociosqu ornare duis, eget tempor&nbsp;quisque.\\n</p>\\n<div id=\\"examplecontent\\">\\n  <p>\\n    Vestibulum ut est, wisi velit, nulla sollicitudin morbi. Fermentum non wisi. Magna nec id sit consectetuer vel, montes mauris, scelerisque erat purus etiam nisl erat. Sit ut pulvinar quisque quisque. A ante, odio pharetra urna suspendisse nascetur metus. Dignissim dui nullam adipiscing amet, tincidunt tincidunt turpis. Duis a ipsum aliquam purus orci, in nec vel libero fusce, imperdiet quisque sem, in ac aenean ut, ac dolor scelerisque nibh&nbsp;nam.\\n  </p>\\n</div>\\n<p></p>\\n<div class=\\"textbook_box textbook_box_required\\" id=\\"examplerequired\\">\\n  <h3>\\n    Steps to&nbsp;completion\\n  </h3>\\n  <ol><li>Review Sample Lessons and complete their related&nbsp;activities.</li>\\n    <li>Complete Quiz at the end of this&nbsp;lesson</li>\\n    <li><strong>Optional:</strong> Use example external tool to visualize your&nbsp;work.</li>\\n  </ol></div>\\n<p>\\n  <iframe allowfullscreen=\\"\\" frameborder=\\"0\\" height=\\"480\\" id=\\"youtubeexample\\" src=\\"//www.youtube-nocookie.com/embed/-DUo4StA8tY?rel=0\\" width=\\"100%\\"></iframe>\\n</p>\\n<table align=\\"center\\" border=\\"1\\" cellpadding=\\"1\\" cellspacing=\\"1\\" class=\\"textbook_table_2\\" height=\\"165\\" summary=\\"This table lists the amount of required and optional resources to view for this lesson.  It also includes the amount of lesson activities and the running time of the lectures. \\" width=\\"500\\"><caption>\\n    Lesson <span class=\\"number\\">5</span> - Budgeting Time\\n  </caption>\\n  <thead><tr><th scope=\\"row\\">\\n        Lesson\\n      </th>\\n      <th scope=\\"col\\">\\n        Number of Required Resources\\n      </th>\\n      <th scope=\\"col\\">\\n        Number of Optional Resources\\n      </th>\\n      <th scope=\\"col\\">\\n        Number of Lesson Activities\\n      </th>\\n      <th scope=\\"col\\">\\n        Duration of Lectures\\n      </th>\\n    </tr></thead><tbody><tr><th scope=\\"row\\">\\n        <span class=\\"number\\">5.1</span>\\n      </th>\\n      <td>\\n        <span class=\\"number\\">13</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">3</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">1</span>\\n      </td>\\n      <td>\\n        (<span class=\\"number\\">1</span> hour, <span class=\\"number\\">12</span> minutes) <span class=\\"number\\">1</span>:<span class=\\"number\\">12</span>\\n      </td>\\n    </tr><tr><th scope=\\"row\\">\\n        <span class=\\"number\\">5.2</span>\\n      </th>\\n      <td>\\n        <span class=\\"number\\">12</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">6</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">1</span>\\n      </td>\\n      <td>\\n        (<span class=\\"number\\">1</span> hour, <span class=\\"number\\">16</span> minutes) <span class=\\"number\\">1</span>:<span class=\\"number\\">16</span>\\n      </td>\\n    </tr><tr><th scope=\\"row\\">\\n        <span class=\\"number\\">5.3</span>\\n      </th>\\n      <td>\\n        <span class=\\"number\\">7</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">7</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">1</span>\\n      </td>\\n      <td>\\n        (<span class=\\"number\\">1</span> hour, 06 minutes) <span class=\\"number\\">1</span>:06\\n      </td>\\n    </tr><tr><th scope=\\"rw\\">\\n        <span class=\\"number\\">5.4</span>\\n      </th>\\n      <td>\\n        <span class=\\"number\\">11</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">6</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">1</span>\\n      </td>\\n      <td>\\n        (<span class=\\"number\\">1</span> hour, <span class=\\"number\\">18</span> minutes) <span class=\\"number\\">1</span>:<span class=\\"number\\">18</span>\\n      </td>\\n    </tr><tr><th scope=\\"row\\"></th>\\n      <td></td>\\n      <td></td>\\n      <td></td>\\n      <td></td>\\n    </tr><tr><th scope=\\"row\\">\\n        Totals  for Lesson\\n      </th>\\n      <td>\\n        <span class=\\"number\\">43</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">2</span>\\n      </td>\\n      <td>\\n        <span class=\\"number\\">4</span>\\n      </td>\\n      <td>\\n        (<span class=\\"number\\">4</span> hours, <span class=\\"number\\">52</span> minutes) <span class=\\"number\\">4</span>:<span class=\\"number\\">52</span>\\n      </td>\\n    </tr></tbody></table><p></p>",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'guided_tour_page\',
            \'format\' => NULL,
            \'safe_value\' => \'guided_tour_page\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'17\',
      \'uid\' => \'1\',
      \'title\' => \'Sing 100\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'92f253fb-077b-4b96-83bc-d3c29042e11d\',
      \'nid\' => \'17\',
      \'type\' => \'course\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'1b0959e4-2226-4e9a-923d-cbdf427e1773\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry&#39;s standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularized in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => \'<p>Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry&#8217;s standard dummy text ever since the <span class="number">1500</span>s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularized in the <span class="number">1960</span>s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem&nbsp;Ipsum.</p>\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_author_video\' => array(
        \'und\' => array(
          array(
            \'video_url\' => \'https://www.youtube.com/watch?v=-DUo4StA8tY\',
            \'thumbnail_path\' => \'public://video_embed_field_thumbnails/youtube/-DUo4StA8tY.jpg\',
            \'video_data\' => \'a:1:{s:7:"handler";s:7:"youtube";}\',
            \'embed_code\' => NULL,
            \'description\' => NULL,
          ),
        ),
      ),
      \'field_banner\' => array(),
      \'field_course_author\' => array(
        \'und\' => array(
          array(
            \'target_id\' => \'14\',
          ),
        ),
      ),
      \'field_course_title\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Introduction to Singularity\',
            \'format\' => NULL,
            \'safe_value\' => \'Introduction to Singularity\',
          ),
        ),
      ),
      \'field_display_in_course_list\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'field_first_offered\' => array(
        \'und\' => array(
          array(
            \'value\' => \'2014-03-01 00:00:00\',
            \'timezone\' => \'UTC\',
            \'timezone_db\' => \'UTC\',
            \'date_type\' => \'datetime\',
          ),
        ),
      ),
      \'field_inst_delivery_guide\' => array(),
      \'field_inst_design_doc\' => array(),
      \'field_inst_instructions\' => array(),
      \'field_inst_other_documents\' => array(),
      \'field_inst_setup_guide\' => array(),
      \'field_instructional_designer\' => array(),
      \'field_lead_instructor\' => array(),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'sing100\',
            \'format\' => NULL,
            \'safe_value\' => \'sing100\',
          ),
        ),
      ),
      \'field_method_of_access\' => array(
        \'und\' => array(
          array(
            \'value\' => \'lms\',
          ),
        ),
      ),
      \'field_offerings\' => array(),
      \'field_related_courses\' => array(),
      \'field_sample_lesson\' => array(
         \'und\' => array(
           array(
           ),
         ),
       ),
       \'field_sample_syllabus\' => array(
         \'und\' => array(
           array(
           ),
         ),
       ),
       \'field_screenshot\' => array(
         \'und\' => array(
           array(
           ),
         ),
       ),
      \'field_ta_documents\' => array(),
      \'field_ta_instructions\' => array(),
      \'field_university_bulletin\' => array(),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
      \'node_export_dependency\' => array(
        array(
          \'type\' => \'node\',
          \'id\' => \'15\',
          \'delta\' => 0,
          \'property\' => \'target_id\',
          \'module\' => \'entityreference\',
          \'field_name\' => \'field_program_classification\',
          \'langcode\' => \'und\',
          \'uuid\' => \'56eac06f-594d-439b-9eff-4455c294a5db\',
        ),
      ),
    ),
  (object) array(
      \'vid\' => \'6\',
      \'uid\' => \'1\',
      \'title\' => \'Resources Page\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'eb9bfdac-d329-4952-9291-07284191b50b\',
      \'nid\' => \'6\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'396a53a4-9b77-4fc1-92d2-615d003f52d6\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>The Resources page will guide you to some of the available services, programs, or information that may help you succeed in this course. Although, you may not need all of these resources that are provided, the course instructor has carefully identified many of these resources to support your learning experience. You are encouraged to take some time to review these resources so you will know what information is available to you during this semester. If you have any difficulty with the items listed here in the resources section, please notify your instructor so the issue may be addressed.</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => \'<p>The Resources page will guide you to some of the available services, programs, or information that may help you succeed in this course. Although, you may not need all of these resources that are provided, the course instructor has carefully identified many of these resources to support your learning experience. You are encouraged to take some time to review these resources so you will know what information is available to you during this semester. If you have any difficulty with the items listed here in the resources section, please notify your instructor so the issue may be&nbsp;addressed.</p>\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'resources_page\',
            \'format\' => NULL,
            \'safe_value\' => \'resources_page\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'15\',
      \'uid\' => \'1\',
      \'title\' => \'ELMSLN\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'241f400a-e372-45fd-a56e-5b1add1c2902\',
      \'nid\' => \'15\',
      \'type\' => \'program\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'56eac06f-594d-439b-9eff-4455c294a5db\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>ELMS is one of our more popular programs of study. &nbsp;It is offered by the School of Singularity and is the primary source of social engagement for the school. &nbsp;In this program you will learn how to develop new tools, lower costs, increase student and faculty engagement through more rich learning environments, and generally be happier.</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => \'<p><span class="caps">ELMS</span> is one of our more popular programs of study.  It is offered by the School of Singularity and is the primary source of social engagement for the school.  In this program you will learn how to develop new tools, lower costs, increase student and faculty engagement through more rich learning environments, and generally be&nbsp;happier.</p>\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_abbreviation\' => array(
        \'und\' => array(
          array(
            \'value\' => \'ELMS\',
            \'format\' => NULL,
            \'safe_value\' => \'ELMS\',
          ),
        ),
      ),
      \'field_facebook\' => array(
        \'und\' => array(
          array(
            \'url\' => \'https://www.facebook.com/psuelms\',
            \'title\' => \'Like us on Facebook\',
            \'attributes\' => array(),
          ),
        ),
      ),
      \'field_program_site\' => array(
        \'und\' => array(
          array(
            \'url\' => \'http://elms.psu.edu\',
            \'title\' => \'ELMS Program home\',
            \'attributes\' => array(),
          ),
        ),
      ),
      \'field_twitter\' => array(
        \'und\' => array(
          array(
            \'url\' => \'https://twitter.com/PSU_ELMS\',
            \'title\' => \'Follow us on Twitter\',
            \'attributes\' => array(),
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
      \'node_export_dependency\' => array(
      ),
    ),
  (object) array(
      \'vid\' => \'7\',
      \'uid\' => \'1\',
      \'title\' => \'Footer language\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'a62cfd1d-4212-485d-adaf-1d57d0f8764d\',
      \'nid\' => \'7\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'6a3853f1-d07e-4fbf-b50b-660d9e9eefc7\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>&copy; Copyright&nbsp;2013&nbsp;-&nbsp;!current&nbsp; All rights&nbsp;reserved.&nbsp;</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => \'<p>© Copyright 2013 - !current  All&nbsp;rights reserved. </p>\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'footer_language\',
            \'format\' => NULL,
            \'safe_value\' => \'footer_language\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'8\',
      \'uid\' => \'1\',
      \'title\' => \'Welcome Language\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'283f7b9b-461d-464a-9840-4cb1fb579792\',
      \'nid\' => \'8\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'6b0e78b3-73ed-407e-9c3b-80e454afc03e\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>Welcome to the course!</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => \'<p>Welcome to the&nbsp;course!</p>\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'welcome_letter\',
            \'format\' => NULL,
            \'safe_value\' => \'welcome_letter\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'9\',
      \'uid\' => \'1\',
      \'title\' => \'LMS Out of Sync language\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'21d36f04-f49d-40f5-8d5d-bcdfcb224960\',
      \'nid\' => \'9\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'845323c3-482d-4974-8b02-edf411e05ad7\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>Hello&nbsp;!name&nbsp;-</p>\\r\\n\\r\\n<p>We just wanted to let you know that our system detected your receiving an &ldquo;access denied&rdquo; message&nbsp;when attempting to reach our course pages. This most often occurs when a student has recently been added to the course roster in&nbsp;our LMS&nbsp;and our course page roster has not yet synchronized with&nbsp;the LMS.</p>\\r\\n\\r\\n<p>You have been added into our roster and now should now be able to access the course pages&nbsp;freely.</p>\\r\\n\\r\\n<p>Thank you,<br />\\r\\n\\tOur team</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => "<p>Hello !name -</p>\\n\\n<p>We just wanted to let you know that our system detected your receiving an “access denied” message when attempting to reach our course pages. This most often occurs when a student has recently been added to the course roster in our <span class=\\"caps\\">LMS</span> and our course page roster has not yet synchronized with the <span class=\\"caps\\">LMS</span>.</p>\\n\\n<p>You have been added into our roster and now should now be able to access the course&nbsp;pages freely.</p>\\n\\n<p>Thank you,\\n\\tOur&nbsp;team</p>",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'lms_out_of_sync\',
            \'format\' => NULL,
            \'safe_value\' => \'lms_out_of_sync\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'10\',
      \'uid\' => \'1\',
      \'title\' => \'Syllabus\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'b8ee6d76-8804-424f-96f7-96269449bc54\',
      \'nid\' => \'10\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'ace2f22c-8828-47d2-9d99-9845ef215095\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>The course syllabus serves as your guide to successfully completing this course. It contains vital information regarding how the course was designed and how your performance in this course will be evaluated. It also serves as a &quot;contract&quot; between you and your instructor and delineates what you can reasonably expect from your instructor.</p>\\r\\n\\r\\n<p>This course is not a self paced course, and it has uncompromising deadlines for all assignments due throughout the semester. To ensure you are keeping pace with the sequence of activities, you should reference the course syllabus at least once per week. Pay particular attention to the course calendar and assignment deadlines as you plan your semester responsibilities and activities.</p>\\r\\n\\r\\n<p>If you are having difficulty opening the PDF file, please <a href=\\"http://get.adobe.com/reader/\\" title=\\"Verify that you have Adobe\'s PDF reader\\">check to make sure you have the most recent version of Adobe Reader</a>.</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => "<p>The course syllabus serves as your guide to successfully completing this course. It contains vital information regarding how the course was designed and how your performance in this course will be evaluated. It also serves as a “contract” between you and your instructor and delineates what you can reasonably expect from your&nbsp;instructor.</p>\\n\\n<p>This course is not a self paced course, and it has uncompromising deadlines for all assignments due throughout the semester. To ensure you are keeping pace with the sequence of activities, you should reference the course syllabus at least once per week. Pay particular attention to the course calendar and assignment deadlines as you plan your semester responsibilities and&nbsp;activities.</p>\\n\\n<p>If you are having difficulty opening the <span class=\\"caps\\">PDF</span> file, please <a href=\\"http://get.adobe.com/reader/\\" title=\\"Verify that you have Adobe\'s PDF reader\\">check to make sure you have the most recent version of Adobe Reader</a>.</p>",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'syllabus\',
            \'format\' => NULL,
            \'safe_value\' => \'syllabus\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'11\',
      \'uid\' => \'1\',
      \'title\' => \'Materials Language\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'3e6f9d73-bf0a-4bf6-9dd3-0c78e70f9fba\',
      \'nid\' => \'11\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'af075e75-e82e-4b2c-b073-f665cf245b0d\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>This is the default language to be used when creating a materials language letter.</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => \'<p>This is the default language to be used when creating a materials language&nbsp;letter.</p>\',
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'materials_letter\',
            \'format\' => NULL,
            \'safe_value\' => \'materials_letter\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'12\',
      \'uid\' => \'1\',
      \'title\' => \'Help language\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'0\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'2e216dc2-82ed-47db-8052-ca99385359bb\',
      \'nid\' => \'12\',
      \'type\' => \'resource\',
      \'language\' => \'und\',
      \'created\' => \'1433709960\',
      \'changed\' => \'1433709960\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'c26d4dfd-ca71-425a-a6e3-ecd247750c03\',
      \'revision_timestamp\' => \'1433709960\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<h2>Course Questions</h2>\\r\\n\\r\\n<p>Any questions and concerns regarding the course should be directed to the instructor. This information is listed on the course syllabus and should be accessed to obtain the instructor&#39;s contact information.</p>\\r\\n\\r\\n<h2>Technical Requirements</h2>\\r\\n\\r\\n<p>The following configuration has been rigorously tested with this course and represents an optimal setup that should cause you the fewest difficulties. This is not to say that other supported devices and browsers will not work; however, you may experience mixed results using other configurations.</p>\\r\\n\\r\\n<p></p>\\r\\n\\r\\n<h3>Recommended System Requirements</h3>\\r\\n\\r\\n<p></p>\\r\\n\\r\\n<ul>\\r\\n\\t<li>Device less than 4 years old</li>\\r\\n\\t<li>Windows PC or Mac OSX</li>\\r\\n\\t<li>Chrome web browser (up to date)</li>\\r\\n\\t<li>Broadband internet connection (cable or DSL)</li>\\r\\n</ul>\\r\\n\\r\\n<p><strong>Note: The latest version of Adobe Flash Player is required.</strong> &nbsp;Cookies and JavaScript must be enabled. Pop-up blockers should be configured to permit new windows from university&nbsp;websites.</p>\\r\\n\\r\\n<p>Any reasonably current browser should work, including the latest versions of Internet Explorer, Firefox and Safari. &nbsp;This course has limited support for Android, iOS and Windows phones and tablets, so it is recommended that you use a PC or Mac.</p>\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'textbook_editor\',
            \'safe_value\' => "<h2>Course&nbsp;Questions</h2>\\n\\n<p>Any questions and concerns regarding the course should be directed to the instructor. This information is listed on the course syllabus and should be accessed to obtain the instructor&#8217;s contact&nbsp;information.</p>\\n\\n<h2>Technical&nbsp;Requirements</h2>\\n\\n<p>The following configuration has been rigorously tested with this course and represents an optimal setup that should cause you the fewest difficulties. This is not to say that other supported devices and browsers will not work; however, you may experience mixed results using other&nbsp;configurations.</p>\\n\\n<p></p>\\n\\n<h3>Recommended System&nbsp;Requirements</h3>\\n\\n<p></p>\\n\\n<ul><li>Device less than <span class=\\"number\\">4</span> years&nbsp;old</li>\\n\\t<li>Windows <span class=\\"caps\\">PC</span> or Mac <span class=\\"caps\\">OSX</span></li>\\n\\t<li>Chrome web browser (up to&nbsp;date)</li>\\n\\t<li>Broadband internet connection (cable or <span class=\\"caps\\">DSL</span>)</li>\\n</ul><p><strong>Note: The latest version of Adobe Flash Player is required.</strong>  Cookies and JavaScript must be enabled. Pop-up blockers should be configured to permit new windows from&nbsp;university websites.</p>\\n\\n<p>Any reasonably current browser should work, including the latest versions of Internet Explorer, Firefox and Safari.  This course has limited support for Android, iOS and Windows phones and tablets, so it is recommended that you use a <span class=\\"caps\\">PC</span> or&nbsp;Mac.</p>",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_machine_name\' => array(
        \'und\' => array(
          array(
            \'value\' => \'help_page\',
            \'format\' => NULL,
            \'safe_value\' => \'help_page\',
          ),
        ),
      ),
      \'field_type\' => array(
        \'und\' => array(
          array(
            \'value\' => \'system\',
          ),
        ),
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'b:0;\',
      \'menu\' => NULL,
      \'path\' => FALSE,
      \'node_export_drupal_version\' => \'7\',
    ),
)',
);
  return $node_export;
}
