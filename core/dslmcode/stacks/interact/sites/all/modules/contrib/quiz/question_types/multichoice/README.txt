
/**
 * @file
 * README file for Quiz Multichoice.
 */

Quiz Multichoice
Allows quiz creators to make a multiple choice question type.

Sponsored by: Norwegian Centre for Telemedicine
Code: falcon


CONTENTS
--------

1.  Introduction
2.  Installation
3.  Configuration

----
1. Introduction
This module is an attempt to make it easy to multiple choice questions using the quiz module.

The multichoice module lets the user create single answer questions and multiple answer questions.
Advanced feedback and scoring options are also available.

The multichoice module is based on the OO framework of the quiz project.

----
2. Installation

To install, unpack the module to your modules folder, and simply enable the module at Admin > Build > Modules.

Several database tables prefixed with quiz_multichoice are installed to have a separate storage for this module.

----
3.  Configuration
Settings are to be found here: admin/quiz/questions_settings

The only available setting is the number of default alternatives. This decides how many alternatives
will be shown on the node-form by default. The question creator can add more by pushing the
add more alternatives button, and he can always leave some alternatives blank if not all the shown
alternatives are needed.

