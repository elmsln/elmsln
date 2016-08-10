## Introduction

**[Able Player](https://github.com/ableplayer/ableplayer)** is a fully
accessible cross-browser media player created by accessibility specialist
Terrill Thompson. It uses the HTML5 <audio> or <video> element for browsers that
support them. The Able Player module integrates the jQuery Able Player plugin as
a file formatter with support for captions, transcripts, and audio description.

## Dependencies

### Modules

*   [Libraries API](https://www.drupal.org/project/libraries)
*   [jQuery Update](https://www.drupal.org/project/jquery_update)
*   [Modernizr](https://www.drupal.org/project/modernizr)
*   [File Entity](https://www.drupal.org/project/file_entity)

#### Recommended

*   [Media](https://www.drupal.org/project/media)

#### Internationalization

*   [Entity Translation](https://www.drupal.org/project/entity_translation)

### Libraries

*   [Able Player](https://github.com/ableplayer/ableplayer)
*   jQuery
*   Modernizr

## Installation

1.  Download and enable this module and the required dependencies.
2.  Download the latest release of Able Player from the GitHub project [releases
    page](https://github.com/ableplayer/ableplayer/releases).
3.  Extract the archive to the libraries directory (usually
    **sites/all/libraries**).
4.  Rename the extracted directory to **ableplayer** if it is not already. The
    final installation path should be **sites/all/libraries/ableplayer**.
5.  Navigate to **admin/config/development/modernizr**. Click the **Download
    your Modernizr production build** button. This will open the Modernizr build
    webpage.
6.  Click the **Download** button and save the file to
    **sites/all/libraries/modernizr**.
7.  Rename the file to **modernizr.custom.js**.
8.  Navigate to **admin/config/development/jquery_update**. Ensure that the
    jQuery version is at least 1.7.

Navigate to **Administration > Reports > Status report**. On successful
installation, the **Able Player** and **Modernizr Tests** entries will report no
issues.

## Configuration

Able Player releases include minified production code as well as the
human-readable source. To use the source code for debugging purposes, navigate
to **Configuration > Media > Able Player** and select the **Development**
option.

## Usage

### Rendered File Display

The Able Player module provides file displays for supported audio and video
mimetypes. Your site must be configured to handle these mimetypes and set to use
Able Player as the primary display.

1.  Navigate to **File Types > Audio > Manage File Display**.
2.  Check Able Player.
3.  Uncheck any undesired displays.
4.  Below the display selection list, there is a draggable list of enabled
    displays. Ensure that Able Player is first in this list.
5.  Click **Save settings**.

Repeat these steps for the video file type. Once these steps are completed,
follow the next set of instructions to display the contents of a file field with
Able Player.

### File Field Display

1.  Add a field of type **File** to any content type. Set the widget type to
    **File**.
2.  Navigate to **Structure > Content Types > YOUR_CONTENT_TYPE > Manage
    Display**. This page shows a list of fields attached to a content type as
    well as their visibility and format.
3.  Find the row for the File field created in step 1\. Under the **Format**
    column, select **Rendered File** from the drop-down.
4.  Click **Save**.

Provided that Able Player has been enabled as the default file display for the
appropriate file types, the file field should now be formatted with Able Player.

### Captions, Descriptions, and Chapters

Field instances for captions, descriptions, and chapters are attached to the
video and audio file bundles upon installation of the Able Player module. When
a valid WebVTT file is uploaded to this field, it will be displayed by Able
Player automatically. You can add transcripts to audio and video uploaded via
the file field on a content type as well:

*   Upload a file via the file field on any node.
*   Navigate to **admin/content/file** and find the transcript file you just
    upload. Click the **Edit** link for that file.
*   Upload transcript files to the appropriate fields.
*   Click **Save**.

**Tip:** install **Media** to streamline this process. With Media installed,
set all file field widgets to **Media Browser** and you will be able to
directly edit the files attached to any file field instance.

#### Multilingual Transcripts

The [Entity Translation](https://drupal.org/project/entity_translation) module
is **required** for support of transcripts in multiple languages.

##### Part 1: Enable and configure Entity Translation

1.  Download and install the **Entity Translation** module
2.  Navigate to **admin/config/regional/entity_translation**
3.  Expand the **Translatable entity types** fieldset and check **File**
4.  Click **Save configuration**
5.  A tabbed fieldset should appear at the bottom of the page. Click on **File**
6.  Expand the **Document** fieldset. Uncheck **Hide language selector**.
7.  Click **Save configuration**

##### Part 2: Configure multilingual support on your Drupal site

1.  Enable the core **Locale** module.
2.  Navigate to **admin/config/regional/language.**
3.  Click on **Add language**. Select the language that you want to add from the
    select box and click **Save**.
4.  Repeat for each language that you want to support.

##### Part 3: Set the language of transcript files

1.  Navigate to an existing transcript file, or first attach a new one to a
    video or audio file. Click the **Edit** administration tab.
2.  There should be a **Language** select box available. Choose the appropriate
    language for the transcript from this form element.
3.  Click **Save**.

With the language set on each transcript file, Able Player will display a
language selection interface for captions and transcripts. Users will be able to
choose their language at playback time.

### Fallback Player

Able Player can use JWPlayer as a fallback for older browsers that do not
support HTML5 media elements. Currently, JWPlayer is the only supported
fallback. Note that JWPlayer only supports mp4 video and mp3 audio.

JWPlayer is licensed and distributed separately from Able Player. Production
self-hosting assets may be aquired at [jwplayer.com](http://www.jwplayer.com/).

You do **not** need to install the JW Player Drupal module. While Able Player
and JW Player may be installed at the same time, Able Player will directly load
the JWPlayer library files in the event that a fallback is necessary.

*   Download the JWPlayer 6.x release archive from jwplayer.com and extract the
    contents (**jwplayer.js**, **jwplayer.html5.js**, and
    **jwplayer.flash.swf**) to **sites/all/libraries/jwplayer**.
*   Test your installation of JWPlayer by navigating to
    **admin/config/media/ableplayer** and checking **Test Fallback**.
*   Navigate to any existing mp4 or mp3 file on your site set to the Able
    Player file display. You should see the "jwplayer" watermark overlaid on the
    video.

### Supported File Types

Details on the usage of the Able Player library, including up-to-date support
for filetypes and third-party media hosts, may be found at the [**Able Player
  GitHub page**](https://github.com/ableplayer/ableplayer).

## Known Issues

*   Able player settings cannot be set on a per-field (or per-file) basis at
    this time.

## Future Enhancements

*   Allow multiple file sources to be displayed by Able Player for a file
    instance, for maximum browser compatibility.
