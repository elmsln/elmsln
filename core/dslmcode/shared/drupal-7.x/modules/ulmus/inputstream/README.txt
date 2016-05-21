Provides a stream-wrapper for drupal://input that should be used instead of 
php://input. This module doesn't do anything in itself, but must be used when 
the php://input is accessed by two or more independent modules.

The stream wrappers internal implementation uses a temp stream to store the 
copied php://input stream. Only one temp stream is created regardless of how 
many drupal://input streams that are opened, and it is safe to use the 
multiple drupal://input streams at the same time as the wrapper takes care of 
the per instance consistency.

Development sponsored by Good Old and Mindpark.

