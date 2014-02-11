# Media: YouTube

Media: YouTube integrates with the Media module to make YouTube videos
available as file entities. Users can insert YouTube videos with file fields
 or directly into into WYSIWYG text areas with the Media module insert button.


## File fields

- Add a new "file" type field to your content type or entity. Choose the widget
  type "Multimedia browser". You can also select an existing file field.
- While setting up the field (or after selecting "edit" on an existing field)
  enable:
    - Enabled browser plugins: "Web"
    - Allowed remote media types: "Video"
    - Allowed URI schemes: "youtube:// (YouTube videos)"

- On "Manage display" for the file field's content or entity type, choose
  "Rendered file" and a view mode.
- Set up YouTube video formatter options for each view mode in Structure ->
  File types -> Manage file display. This is where you can choose size, autoplay,
  appearance, and special JS API integration options.
- When using the file field while creating or editing content, paste a YouTube
  video url into the Web tab.

ProTip: You can use multiple providers (e.g., Media: YouTube and Media: Vimeo)
on the same file field.


## WYSIWYG inserts

- Enable the Media module "Media insert" button on your WYSIWYG profile.
- Enable "Convert Media tags to markup" filter in the appropriate text formats.
- Configure any desired settings in Configuration -> Media -> "Media browser
  settings"
- Set up YouTube video formatter options in Structure -> File types -> Manage
  file display. **Note:** for any view mode that will be used in a WYSIWYG,
  enable both the YouTube video and preview image formatter. Arrange the Video
  formatter on top. This allows the video to be used when the content is viewed,
  and the preview when the content is being edited.

- When editing a text area with your WYSIWYG, click the "Media insert" button,
  and paste a YouTube video url into the Web tab of the media browser.


## Upgrading from 7.x-1.x or 7.x-2.0-alpha-2 to 7.x-2.0

There are some important changes between the older recommended versions of
Media: YouTube and the new stable release that may require manual updating.

- 2.0 uses the YouTube iframe embed with the currently supported player
  parameters. If you were relying on parameters that no longer work with
  the iframe player, you may see some minor differences in player appearance.
  Please review your formatter settings after you update.

- **The markup for the player embed has changed.** The 2.0 and 2.x-dev versions
  use simplified and updated markup that integrates better with responsive
  video techniques. There is a tpl provided at /includes/themes/media-youtube-
  video.legacy-example.tpl.php that duplicates the old markup. To use it, copy
  it to your theme folder and rename it to media-youtube-video.tpl.php. It is
  recommended that you revise any css or javascript that requires the old
  markup and then delete the legacy markup tpl file.


## Further Reading

- Media 2.x Overview, including file entities and view modes:
  http://drupal.stackexchange.com/questions/40229/how-to-set-media-styles-in-media-7-1-2-media-7-2-x/40685#40685
- Media 2.x Walkthrough: http://drupal.org/node/1699054
- YouTube player parameters and explanation. Media: YouTube uses only iframe
  player parameters:
  https://developers.google.com/youtube/player_parameters#Parameters
- YouTube JS API example:
  http://stackoverflow.com/questions/7443578/youtube-iframe-api-how-do-i-control-a-iframe-player-thats-already-in-the-html/7513356#7513356
