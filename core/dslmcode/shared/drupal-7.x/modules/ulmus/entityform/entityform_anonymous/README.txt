Drupal entityform_anonymous.module README.txt
================================================================================
***Warning***
Anonymous tracking has not be fully tested yet.

It may allow expose the Entityform Submissions to other users.
Please test throughly.

See: https://drupal.org/node/2181691

@todo add more detailed warning
================================================================================
** Anonymous Links **
================================================================================
This functionality allows for accessing anonymous submissions via anonymous links
with access keys.

This links are available via tokens.

**Anonymous Submission Edit Link
[entityform:anonymous_submission_edit_link]
Link to allow editing anonymous submission.
**Anonymous Submission Submit Link
[entityform:anonymous_submission_submit_link]
Link to allow resubmitting anonymous submission, used when resubmit action is edit old submission.
**Anonymous Submission View Link
[entityform:anonymous_submission_view_link]
Link to allow viewing anonymous submission.

================================================================================
** Anonymous Submission in Browser Sessions **
================================================================================
This functionality allows for tracking anonymous submission through the current
browser sessions.
