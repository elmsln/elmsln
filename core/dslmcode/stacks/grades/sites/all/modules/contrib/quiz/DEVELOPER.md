## Notes on developing for Quiz

Hooks for interacting with a quiz:
 - `hook_<entity_type>_<op>`: These hooks are called for any entity operations. See `quiz_entity_info` for all the possible types you can interact with.
 - (DEPRECATED) hook_quiz_begin($quiz, $result_id): This hook is called when a user first begins a quiz.
   - Use `hook_quiz_result_insert($quiz_result)`
 - (DEPRECATED) hook_quiz_finished($quiz, $score, $result_id): This hook is called immediately after a user finishes taking a quiz.
   - Use `hook_quiz_result_update($quiz_result)`
 - (DEPRECATED) hook_quiz_scored($quiz, $score, $result_id): This is called when a quiz score is updated. See http://drupal.org/node/460456
   - Use `hook_quiz_result_update($quiz_result)`


## Developing new question types

You need to create a new module that extends the existing
question type core. The multichoice question type provides a precise example.

Here are the steps:

1. Create a new module
2. Use your module's .install file to create the necessary tables
3. Make sure you module implements `hook_quiz_question_info()`
4. Define classes that extend `QuizQuestion` and `QuizQuestionResponse`.
   For a complete example, see multichoice.classes.inc.
