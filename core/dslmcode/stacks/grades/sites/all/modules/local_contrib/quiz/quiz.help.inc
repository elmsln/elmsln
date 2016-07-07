<?php
/**
 * Help text.
 *
 * @file
 * quiz help function
 */

/**
 * Handle help calls.
 * @see hook_help()
 */
function _quiz_help($path, $arg) {
  switch ($path) {
    case 'admin/help#quiz':
      return t('

<p>The quiz module allows users to administer a quiz, as a sequence of questions, and track the answers given. It allows for the creation of questions (and their answers), and organizes these questions into a quiz. Its target audience includes educational institutions, online training programs, employers, and people who just want to add a fun activity for their visitors to their Drupal site.</p>

<p>The quiz module has a plethora of permission options. Unless you take care setting your permissions, the quiz module might not do everything you want it to do.</p>

<p>For more information about quiz, and resources on how to use quiz, see the <a href="http://drupal.org/project/quiz">Quiz project website</a></p>

    ', array('@quiz' => QUIZ_NAME, '@admin-access' => url('admin/user/permissions'), '@admin-modules' => url('admin/modules'), '@admin-taxonomy' => url('admin/structure/taxonomy'), '@create-content' => url('node/add'), '@multichoice' => url('node/add/multichoice'), '@create-quiz' => url('node/add/quiz')));
    case 'node/add#quiz':
      return t('A collection of questions designed to create interactive tests');
    default:
      break;
  }
}
