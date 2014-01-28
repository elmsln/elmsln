<?php
/**
 * @file
 * textbook_section_508.accessibility_test.inc
 */

/**
 * Implements hook_accessibility_test_default().
 */
function textbook_section_508_accessibility_test_default() {
$accessibility_tests = array();
$accessibility_tests['aAdjacentWithSameResourceShouldBeCombined'] = (object)array(
  'language' => 'en',
  'name' => 'Adjacent links that point to the same location should be merged',
  'quail_name' => 'aAdjacentWithSameResourceShouldBeCombined',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Because many users of screen-readers use links to navigate the page, providing two links right next to eachother that points to the same location can be confusing. Try combining the links.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aImgAltNotRepetative'] = (object)array(
  'language' => 'en',
  'name' => 'When an image is in a link, its "alt" attribute should not repeat other text in the link',
  'quail_name' => 'aImgAltNotRepetative',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Images within a link should not have an alt attribute that simply repeats the text found in the link. This will cause screen readers to simply repeat the text twice.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aLinkTextDoesNotBeginWithRedundantWord'] = (object)array(
  'language' => 'en',
  'name' => 'Link text should not begin with redundant text',
  'quail_name' => 'aLinkTextDoesNotBeginWithRedundantWord',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Link text should not begin with redundant words or phrases like "link',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aLinksAreSeperatedByPrintableCharacters'] = (object)array(
  'language' => 'en',
  'name' => 'Lists of links should be seperated by printable characters',
  'quail_name' => 'aLinksAreSeperatedByPrintableCharacters',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a list of links is provided within the same element, those links should be seperated by a non-linked, printable character. Structures like lists are not included in this.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aLinksDontOpenNewWindow'] = (object)array(
  'language' => 'en',
  'name' => 'Links should not open a new window without warning',
  'quail_name' => 'aLinksDontOpenNewWindow',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Links which open a new window using the "target" attribute should warn users.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aLinksToMultiMediaRequireTranscript'] = (object)array(
  'language' => 'en',
  'name' => 'Any links to a multimedia file should also include a link to a transcript',
  'quail_name' => 'aLinksToMultiMediaRequireTranscript',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Links to a multimedia file should be followed by a link to a transcript of the file.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aLinksToSoundFilesNeedTranscripts'] = (object)array(
  'language' => 'en',
  'name' => 'Any links to a sound file should also include a link to a transcript',
  'quail_name' => 'aLinksToSoundFilesNeedTranscripts',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Links to a sound file should be followed by a link to a transcript of the file.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aMultimediaTextAlternative'] = (object)array(
  'language' => 'en',
  'name' => 'aMultimediaTextAlternative',
  'quail_name' => 'aMultimediaTextAlternative',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aMustContainText'] = (object)array(
  'language' => 'en',
  'name' => 'Links should contain text',
  'quail_name' => 'aMustContainText',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Because many users of screen-readers use links to navigate the page, providing links with no text (or with images that have empty "alt" attributes and no other readable text) hinders these users.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aMustHaveTitle'] = (object)array(
  'language' => 'en',
  'name' => 'All links must have a "title" attribute',
  'quail_name' => 'aMustHaveTitle',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Every link must have a "title" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aMustNotHaveJavascriptHref'] = (object)array(
  'language' => 'en',
  'name' => 'Links should not use "javascript" in their location',
  'quail_name' => 'aMustNotHaveJavascriptHref',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Anchor (<code>a</code>.  elements may not use the "javascript" protocol in their "href" attributes.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aSuspiciousLinkText'] = (object)array(
  'language' => 'en',
  'name' => 'Link text should be useful',
  'quail_name' => 'aSuspiciousLinkText',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Because many users of screen-readers use links to navigate the page, providing links with text that simply read "click here" gives no hint of the function of the link',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['aTitleDescribesDestination'] = (object)array(
  'language' => 'en',
  'name' => 'The title attribute of all source a (anchor) elements describes the link destination.',
  'quail_name' => 'aTitleDescribesDestination',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Every link must have a "title" attribute which describes the purpose or destination of the link.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['addressForAuthor'] = (object)array(
  'language' => 'en',
  'name' => 'The document should contain an address for the author',
  'quail_name' => 'addressForAuthor',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Documents should provide a valid email address within an <code>address</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['addressForAuthorMustBeValid'] = (object)array(
  'language' => 'en',
  'name' => 'The document should contain a valid email address for the author',
  'quail_name' => 'addressForAuthorMustBeValid',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Documents should provide a valid email address within an <code>address</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['appletContainsTextEquivalent'] = (object)array(
  'language' => 'en',
  'name' => 'All applets should contain the same content within the body of the applet',
  'quail_name' => 'appletContainsTextEquivalent',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Applets should contain their text equivalents or description within the <code>applet</code>. /code> tag itself.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['appletContainsTextEquivalentInAlt'] = (object)array(
  'language' => 'en',
  'name' => 'All applets should contain a text equivalent in the "alt" attribute',
  'quail_name' => 'appletContainsTextEquivalentInAlt',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Applets should contain their text equivalents or description in an "alt" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['appletProvidesMechanismToReturnToParent'] = (object)array(
  'language' => 'en',
  'name' => 'All applets should provide a way for keyboard users to escape',
  'quail_name' => 'appletProvidesMechanismToReturnToParent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Ensure that a user who has only a keyboard as an input device can escape an <code>applet</code>. /code> element. This requires manual confirmation.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['appletTextEquivalentsGetUpdated'] = (object)array(
  'language' => 'en',
  'name' => 'appletTextEquivalentsGetUpdated',
  'quail_name' => 'appletTextEquivalentsGetUpdated',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['appletUIMustBeAccessible'] = (object)array(
  'language' => 'en',
  'name' => 'Any user interface in an applet must be accessible',
  'quail_name' => 'appletUIMustBeAccessible',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Applet content should be assessed for accessibility.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['appletsDoNotFlicker'] = (object)array(
  'language' => 'en',
  'name' => 'All applets do not flicker',
  'quail_name' => 'appletsDoNotFlicker',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Applets should not flicker.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['appletsDoneUseColorAlone'] = (object)array(
  'language' => 'en',
  'name' => 'Applets should not use color alone to communicate content',
  'quail_name' => 'appletsDoneUseColorAlone',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Applets should contain content that makes sense without color and is accessible to users who are color blind.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['areaAltIdentifiesDestination'] = (object)array(
  'language' => 'en',
  'name' => 'All "area" elements must have an "alt" attribute which describes the link destination',
  'quail_name' => 'areaAltIdentifiesDestination',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>area</code>. /code> elements within a <code>map</code>. /code> must have an "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['areaAltRefersToText'] = (object)array(
  'language' => 'en',
  'name' => 'Alt text for "area" elements should replicate the text found in the image',
  'quail_name' => 'areaAltRefersToText',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If an image is being used as a map, and an <code>area</code>. /code> encompasses text within the image, then the "alt" attribute of that <code>area</code>. /code> element should be the same as the text found in the image.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['areaDontOpenNewWindow'] = (object)array(
  'language' => 'en',
  'name' => 'No "area" elements should open a new window without warning',
  'quail_name' => 'areaDontOpenNewWindow',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'No <code>area</code>. /code> elements should open a new window without warning.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['areaHasAltValue'] = (object)array(
  'language' => 'en',
  'name' => 'All "area" elements must have an "alt" attribute',
  'quail_name' => 'areaHasAltValue',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>area</code>. /code> elements within a <code>map</code>. /code> must have an "alt" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['areaLinksToSoundFile'] = (object)array(
  'language' => 'en',
  'name' => 'All "area" elements which link to a sound file should also provide a link to a transcript',
  'quail_name' => 'areaLinksToSoundFile',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>area</code>. /code> elements which link to a sound file should have a text transcript',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['ariaOrphanedContent'] = (object)array(
  'language' => 'en',
  'name' => 'Pages using ARIA roles should not have orphaned content',
  'quail_name' => 'ariaOrphanedContent',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a page makes use of ARIA roles, then there should not be any content on the page which is not within an element that exposes a role, as it could cause that content to be rendreed inaccessible to users with screen readers.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['basefontIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'Basefont" should not be used',
  'quail_name' => 'basefontIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>basefont</code>. /code> tag is deprecated and should not be used. Investigate using stylesheets instead.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['blinkIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'The "blink" tag should not be used',
  'quail_name' => 'blinkIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>blink</code>. /code> tag should not be used. Ever.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['blockquoteNotUsedForIndentation'] = (object)array(
  'language' => 'en',
  'name' => 'The "blockquote" tag should not be used just for indentation',
  'quail_name' => 'blockquoteNotUsedForIndentation',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['blockquoteUseForQuotations'] = (object)array(
  'language' => 'en',
  'name' => 'If long quotes are in the document, use the "blockquote" element to mark them',
  'quail_name' => 'blockquoteUseForQuotations',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['bodyActiveLinkColorContrast'] = (object)array(
  'language' => 'en',
  'name' => 'Contrast between active link text and background should be 5:1',
  'quail_name' => 'bodyActiveLinkColorContrast',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The contrast ratio of active link text should be at lest 5:1 between the foreground text and the background. <a href="http://www.w3.org/TR/WCAG20/#contrast-ratiodef">Learn more about color contrast and how to measure it.</a>',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['bodyColorContrast'] = (object)array(
  'language' => 'en',
  'name' => 'Contrast between text and background should be 5:1',
  'quail_name' => 'bodyColorContrast',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The contrast ratio of text should be at lest 5:1 between the foreground text and the background. <a href="http://www.w3.org/TR/WCAG20/#contrast-ratiodef">Learn more about color contrast and how to measure it.</a>',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['bodyLinkColorContrast'] = (object)array(
  'language' => 'en',
  'name' => 'Contrast between link text and background should be 5:1',
  'quail_name' => 'bodyLinkColorContrast',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The contrast ratio of link text should be at lest 5:1 between the foreground text and the background. <a href="http://www.w3.org/TR/WCAG20/#contrast-ratiodef">Learn more about color contrast and how to measure it.</a>',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['bodyMustNotHaveBackground'] = (object)array(
  'language' => 'en',
  'name' => 'Body elements do not use a background image',
  'quail_name' => 'bodyMustNotHaveBackground',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>body</code>. /code> element for the page may not have a "background" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['bodyVisitedLinkColorContrast'] = (object)array(
  'language' => 'en',
  'name' => 'Contrast between visited link text and background should be 5:1',
  'quail_name' => 'bodyVisitedLinkColorContrast',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The contrast ratio of visited link text should be at lest 5:1 between the foreground text and the background. <a href="http://www.w3.org/TR/WCAG20/#contrast-ratiodef">Learn more about color contrast and how to measure it.</a>',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['boldIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'The "b" (bold) element is not used',
  'quail_name' => 'boldIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>b</code>. /code> (bold) element provides no emphasis for non-sighted readers. Use the <code>strong</code>. /code> tag instead.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['checkboxHasLabel'] = (object)array(
  'language' => 'en',
  'name' => 'All checkboxes must have a corresponding label',
  'quail_name' => 'checkboxHasLabel',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "checkbox" should have a corresponding <code>label</code>. /code> element. Screen readers often enter a "form mode" where only label text is read aloud to the user',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['checkboxLabelIsNearby'] = (object)array(
  'language' => 'en',
  'name' => 'All "checkbox" input elements have a label that is close',
  'quail_name' => 'checkboxLabelIsNearby',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All input elements of type "checkbox" must have a corresponding label that is close to the form element. Users of screen magnification or with reduced spatial skills are hampered in using a form element if the label for that element is located far away.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['cssDocumentMakesSenseStyleTurnedOff'] = (object)array(
  'language' => 'en',
  'name' => 'The document must be readable with styles turned off',
  'quail_name' => 'cssDocumentMakesSenseStyleTurnedOff',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'With all the styles for a page turned off, the content of the page should still make sense. Try to turn styles off in the browser and see if the page content is readable and clear.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['cssTextHasContrast'] = (object)array(
  'language' => 'en',
  'name' => 'All elements should have appropriate color contrast',
  'quail_name' => 'cssTextHasContrast',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'For users who have color blindness, all text or other elements should have a color contrast of 5:1.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['doctypeProvided'] = (object)array(
  'language' => 'en',
  'name' => 'The document should contain a valid "doctype" declaration',
  'quail_name' => 'doctypeProvided',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Each document must contain a valid doctype declaration..',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentAbbrIsUsed'] = (object)array(
  'language' => 'en',
  'name' => 'Abbreviations must be marked with an "abbr" element',
  'quail_name' => 'documentAbbrIsUsed',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Abbreviations should be marked with an <code>abbr</code>. /code> element, at least once on the page for each abbreviation.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentAcronymsHaveElement'] = (object)array(
  'language' => 'en',
  'name' => 'Acronyms must be marked with an "acronym" element',
  'quail_name' => 'documentAcronymsHaveElement',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Abbreviations should be marked with an <code>acronym</code>. /code> element, at least once on the page for each abbreviation.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentAllColorsAreSet'] = (object)array(
  'language' => 'en',
  'name' => 'All the document colors must be set',
  'quail_name' => 'documentAllColorsAreSet',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If any colors for text or the background are set in the <code>body</code>. /code> element, then all colors must be set.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentAutoRedirectNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'Auto-redirect with "meta" elements must not be used',
  'quail_name' => 'documentAutoRedirectNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Because different users have different speeds and abilities when it comes to parsing the content of a page, a "meta-refresh" method to redirect users can prevent users from fully understanding the document before being redirected. If a pure redirect is needed',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentColorWaiActiveLinkAlgorithm'] = (object)array(
  'language' => 'en',
  'name' => 'documentColorWaiActiveLinkAlgorithm',
  'quail_name' => 'documentColorWaiActiveLinkAlgorithm',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentColorWaiAlgorithm'] = (object)array(
  'language' => 'en',
  'name' => 'documentColorWaiAlgorithm',
  'quail_name' => 'documentColorWaiAlgorithm',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentColorWaiLinkAlgorithm'] = (object)array(
  'language' => 'en',
  'name' => 'documentColorWaiLinkAlgorithm',
  'quail_name' => 'documentColorWaiLinkAlgorithm',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentColorWaiVisitedLinkAlgorithm'] = (object)array(
  'language' => 'en',
  'name' => 'documentColorWaiVisitedLinkAlgorithm',
  'quail_name' => 'documentColorWaiVisitedLinkAlgorithm',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentContentReadableWithoutStylesheets'] = (object)array(
  'language' => 'en',
  'name' => 'Content should be readable without style sheets',
  'quail_name' => 'documentContentReadableWithoutStylesheets',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'With all the styles for a page turned off, the content of the page should still make sense. Try to turn styles off in the browser and see if the page content is readable and clear.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentHasTitleElement'] = (object)array(
  'language' => 'en',
  'name' => 'The document should have a title element',
  'quail_name' => 'documentHasTitleElement',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document should have a title element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentIDsMustBeUnique'] = (object)array(
  'language' => 'en',
  'name' => 'All element "id" attributes must be unique',
  'quail_name' => 'documentIDsMustBeUnique',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Element "id" attributes must be unique.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentIsWrittenClearly'] = (object)array(
  'language' => 'en',
  'name' => 'The document should be written to the target audience and read clearly',
  'quail_name' => 'documentIsWrittenClearly',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a document is beyond a 10th grade level, then a summary or other guide should also be provided to guide the user through the content.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentLangIsISO639Standard'] = (object)array(
  'language' => 'en',
  'name' => 'The document\'s language attribute should be a standard code',
  'quail_name' => 'documentLangIsISO639Standard',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document should have a default langauge, and that language should use the valid 2 or 3 letter language code according to ISO specification 639.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentLangNotIdentified'] = (object)array(
  'language' => 'en',
  'name' => 'The document must have a "lang" attribute',
  'quail_name' => 'documentLangNotIdentified',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document should have a default langauge, by setting the "lang" attribute in the <code>html</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentMetaNotUsedWithTimeout'] = (object)array(
  'language' => 'en',
  'name' => 'Meta" elements must not be used to refresh the content of a page',
  'quail_name' => 'documentMetaNotUsedWithTimeout',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Because different users have different speeds and abilities when it comes to parsing the content of a page, a "meta-refresh" method to reload the content of the page can prevent users from having full access to the content. Try to use a "refresh this" link instead..',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentReadingDirection'] = (object)array(
  'language' => 'en',
  'name' => 'Reading direction of text is correctly marked',
  'quail_name' => 'documentReadingDirection',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Where required, the reading direction of the document (for language that read in different directions), or portions of the text, must be declared.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentStrictDocType'] = (object)array(
  'language' => 'en',
  'name' => 'The page uses a strict doctype',
  'quail_name' => 'documentStrictDocType',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The doctype of the page or document should be either an HTML or XHTML strict doctype.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentTitleDescribesDocument'] = (object)array(
  'language' => 'en',
  'name' => 'The title describes the document',
  'quail_name' => 'documentTitleDescribesDocument',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document title should actually describe the page. Often, screen readers use the title to navigate from one window to another.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentTitleIsNotPlaceholder'] = (object)array(
  'language' => 'en',
  'name' => 'The document title should not be placeholder text',
  'quail_name' => 'documentTitleIsNotPlaceholder',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document title should not be wasted placeholder text which does not describe the page.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentTitleIsShort'] = (object)array(
  'language' => 'en',
  'name' => 'The document title should be short',
  'quail_name' => 'documentTitleIsShort',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document title should be short and succinct. This test fails at 150 characters, but authors should consider this to be a suggestion.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentTitleNotEmpty'] = (object)array(
  'language' => 'en',
  'name' => 'The document should not have an empty title',
  'quail_name' => 'documentTitleNotEmpty',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document should have a title element that is not white space',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentValidatesToDocType'] = (object)array(
  'language' => 'en',
  'name' => 'Document must validate to the doctype',
  'quail_name' => 'documentValidatesToDocType',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The document must validate to the declared doctype.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentVisualListsAreMarkedUp'] = (object)array(
  'language' => 'en',
  'name' => 'Visual lists of items are marked using ordered or unordered lists',
  'quail_name' => 'documentVisualListsAreMarkedUp',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Use the ordered (<code>ol</code>.  or unordered (<code>ul</code>.  elements for lists of items, instead of just using new lines which start with numbers or characters to create a visual list.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['documentWordsNotInLanguageAreMarked'] = (object)array(
  'language' => 'en',
  'name' => 'Any words or phrases which are not the document\'s primary language should be marked',
  'quail_name' => 'documentWordsNotInLanguageAreMarked',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a document has words or phrases which are not in the document\'s primary language, those words or phrases should be properly marked. This helps indicate which language or voice a screen-reader should use to read the text.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['embedHasAssociatedNoEmbed'] = (object)array(
  'language' => 'en',
  'name' => 'All "embed" elements have an associated "noembed" element',
  'quail_name' => 'embedHasAssociatedNoEmbed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Because some users cannot use the <code>embed</code>. /code> element, provide alternative content in a <code>noembed</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['embedMustHaveAltAttribute'] = (object)array(
  'language' => 'en',
  'name' => 'Embed" elements must have an "alt" attribute',
  'quail_name' => 'embedMustHaveAltAttribute',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>embed</code>. /code> elements must have an "alt" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['embedMustNotHaveEmptyAlt'] = (object)array(
  'language' => 'en',
  'name' => 'Embed" elements cannot have an empty "alt" attribute',
  'quail_name' => 'embedMustNotHaveEmptyAlt',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>embed</code>. /code> elements must have an "alt" attribute that is not empty.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['embedProvidesMechanismToReturnToParent'] = (object)array(
  'language' => 'en',
  'name' => 'All embed elements should provide a way for keyboard users to escape',
  'quail_name' => 'embedProvidesMechanismToReturnToParent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Ensure that a user who has only a keyboard as an input device can escape an <code>embed</code>. /code> element. This requires manual confirmation.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['emoticonsExcessiveUse'] = (object)array(
  'language' => 'en',
  'name' => 'Emoticons should not be used excessively',
  'quail_name' => 'emoticonsExcessiveUse',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Emoticons should not be used excessively to communicate feelings or content. Try to rewrite the document to have more textual meaning, or wrapping the emoticons in an <code>abbr</code>. /code> element as outlined below. Emoticons are not read by screen-readers, and are often used to communicate feelings or other things which are relevant to the content of the document.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['emoticonsMissingAbbr'] = (object)array(
  'language' => 'en',
  'name' => 'Emoticons should have abbreviations',
  'quail_name' => 'emoticonsMissingAbbr',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Emoticons are not read by screen-readers, and are often used to communicate feelings or other things which are relevant to the content of the document. If this emoticon is important content, mark it up with an "abbr" or "acronym" tag.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['fileHasLabel'] = (object)array(
  'language' => 'en',
  'name' => 'All "file" input elements have a corresponding label',
  'quail_name' => 'fileHasLabel',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements of type "file" should have a corresponding <code>label</code>. /code> element. Screen readers often enter a "form mode" where only label text is read aloud to the user',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['fileLabelIsNearby'] = (object)array(
  'language' => 'en',
  'name' => 'All "file" input elements have a label that is close',
  'quail_name' => 'fileLabelIsNearby',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All input elements of type "file" must have a corresponding label that is close to the form element. Users of screen magnification or with reduced spatial skills are hampered in using a form element if the label for that element is located far away.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['fontIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'Font" elements should not be used',
  'quail_name' => 'fontIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>basefont</code>. /code> tag is deprecated and should not be used. Investigate using stylesheets instead.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['formAllowsCheckIfIrreversable'] = (object)array(
  'language' => 'en',
  'name' => 'formAllowsCheckIfIrreversable',
  'quail_name' => 'formAllowsCheckIfIrreversable',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['formDeleteIsReversable'] = (object)array(
  'language' => 'en',
  'name' => 'Deleting items using a form should be reversable',
  'quail_name' => 'formDeleteIsReversable',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Check that, if a form has the option to delete an item, that the user has a chance to either reverse the delete process, or is asked for confirmation before the item is deleted. This is not something that can be checked through automated testing and requires manual confirmation.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['formErrorMessageHelpsUser'] = (object)array(
  'language' => 'en',
  'name' => 'Forms offer the user a way to check the results of their form before performing an irrevokable action',
  'quail_name' => 'formErrorMessageHelpsUser',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If the form allows users to perform some irrevokable action, like ordreing a product, ensure that users have the ability to review the contents of the form they submitted first. This is not something that can be checked through automated testing and requires manual confirmation.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['formHasGoodErrorMessage'] = (object)array(
  'language' => 'en',
  'name' => 'Form error messages should assist in solving errors',
  'quail_name' => 'formHasGoodErrorMessage',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If the form has some required fields or other ways in which the user can commit an error, check that the reply is accessible. Use the words "required" or "error" within the <code>label</code>. /code> element of input items where the errors happened',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['formWithRequiredLabel'] = (object)array(
  'language' => 'en',
  'name' => 'Input items which are required are marked as so in the label element',
  'quail_name' => 'formWithRequiredLabel',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a form element is required, it should marked as so. This should not be a mere red asterisk, but instead either a \'required\' image with alt text of "required" or the actual text "required." The indicator that an item is required should be included in the input element\'s <code>label</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['frameIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'Frames are not used',
  'quail_name' => 'frameIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['frameRelationshipsMustBeDescribed'] = (object)array(
  'language' => 'en',
  'name' => 'Complex framesets should contain a "longdesc" attribute',
  'quail_name' => 'frameRelationshipsMustBeDescribed',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a <code>frameset</code>. /code> contains three or more frames, use a "longdesc" attribute to help describe the purpose of the frames.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['frameSrcIsAccessible'] = (object)array(
  'language' => 'en',
  'name' => 'The source for each frame is accessible content.',
  'quail_name' => 'frameSrcIsAccessible',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Each frame should contain accessible content, and contain content accessible to screen readers, like HTML as opposed to an image.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['frameTitlesDescribeFunction'] = (object)array(
  'language' => 'en',
  'name' => 'All "frame" elemetns should have a "title" attribute that describes the purpose of the frame',
  'quail_name' => 'frameTitlesDescribeFunction',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Each <code>frame</code>. /code> elements should have a "title" attribute which describes the purpose or function of the frame.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['frameTitlesNotEmpty'] = (object)array(
  'language' => 'en',
  'name' => 'Frames cannot have empty "title" attributes',
  'quail_name' => 'frameTitlesNotEmpty',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>frame</code>. /code> elements must have a valid "title" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['frameTitlesNotPlaceholder'] = (object)array(
  'language' => 'en',
  'name' => 'Frames cannot have "title" attributes that are just placeholder text',
  'quail_name' => 'frameTitlesNotPlaceholder',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Frame "title" attributes should not be simple placeholder text like "frame',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['framesHaveATitle'] = (object)array(
  'language' => 'en',
  'name' => 'All "frame" elements should have a "title" attribute',
  'quail_name' => 'framesHaveATitle',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Each <code>frame</code>. /code> elements should have a "title" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['framesetIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'The "frameset" element should not be used',
  'quail_name' => 'framesetIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['framesetMustHaveNoFramesSection'] = (object)array(
  'language' => 'en',
  'name' => 'All framesets should contain a noframes section',
  'quail_name' => 'framesetMustHaveNoFramesSection',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a <code>frameset</code>. /code> contains three or more frames, use a "longdesc" attribute to help describe the purpose of the frames.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH1'] = (object)array(
  'language' => 'en',
  'name' => 'The header following an h1 is h1 or h2',
  'quail_name' => 'headerH1',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The header following an <code>h1</code>. /code> element should either be an <code>h2</code>. /code> or another <code>h1</code>. ',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH1Format'] = (object)array(
  'language' => 'en',
  'name' => 'All h1 elements are not used for formatting',
  'quail_name' => 'headerH1Format',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'An <code>h1</code>. /code> element may not be used purely for formatting.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH2'] = (object)array(
  'language' => 'en',
  'name' => 'The header following an h2 is h1, h2 or h3',
  'quail_name' => 'headerH2',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The header following an <code>h2</code>. /code> element should either be an <code>h3</code>. /code>,  <code>h1</code>. /code> or another <code>h2</code>. ',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH2Format'] = (object)array(
  'language' => 'en',
  'name' => 'All h2 elements are not used for formatting',
  'quail_name' => 'headerH2Format',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'An <code>h2</code>. /code> element may not be used purely for formatting.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH3'] = (object)array(
  'language' => 'en',
  'name' => 'The header following an h3 is h1, h2, h3 or h4',
  'quail_name' => 'headerH3',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The header following an <code>h3</code>. /code> element should either be an <code>h4</code>. /code>,  <code>h2</code>. /code>,  <code>h1</code>. /code> or another <code>h3</code>. ',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH3Format'] = (object)array(
  'language' => 'en',
  'name' => 'All h3 elements are not used for formatting',
  'quail_name' => 'headerH3Format',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'An <code>h3</code>. /code> element may not be used purely for formatting.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH4'] = (object)array(
  'language' => 'en',
  'name' => 'The header following an h4 is h1, h2, h3, h4 or h5',
  'quail_name' => 'headerH4',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The header following an <code>h4</code>. /code> element should either be an <code>h5</code>. /code>,  <code>h3</code>. /code>,  <code>h2</code>. /code>,  <code>h1</code>. /code>,  or another <code>h4</code>. ',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH4Format'] = (object)array(
  'language' => 'en',
  'name' => 'All h4 elements are not used for formatting',
  'quail_name' => 'headerH4Format',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'An <code>h4</code>. /code> element may not be used purely for formatting.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH5'] = (object)array(
  'language' => 'en',
  'name' => 'The header following an h5 is h6 or any header less than h6',
  'quail_name' => 'headerH5',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The header following an <code>h5</code>. /code> element should either be an <code>h6</code>. /code>,   <code>h3</code>. /code>,  <code>h2</code>. /code>,  <code>h1</code>. /code>,  or another <code>h5</code>. ',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH5Format'] = (object)array(
  'language' => 'en',
  'name' => 'All h5 elements are not used for formatting',
  'quail_name' => 'headerH5Format',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'An <code>h5</code>. /code> element may not be used purely for formatting.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headerH6Format'] = (object)array(
  'language' => 'en',
  'name' => 'All h6 elements are not used for formatting',
  'quail_name' => 'headerH6Format',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'An <code>h6</code>. /code> element may not be used purely for formatting.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headersHaveText'] = (object)array(
  'language' => 'en',
  'name' => 'All headers should contain readable text',
  'quail_name' => 'headersHaveText',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Users with screen readers use headings like the tabs <em>h1</em> to navigate the structure of a page. All headings should contain either text, or images with appropriate <em>alt</em> attributes.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['headersUseToMarkSections'] = (object)array(
  'language' => 'en',
  'name' => 'Use headers to mark the beginning of each section',
  'quail_name' => 'headersUseToMarkSections',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Check that each logical section of the page is broken or introduced with a header (<code></code>. h1-h6>) element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['iIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'The "i" (italic) element is not used',
  'quail_name' => 'iIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>i</code>. /code> (italic) element provides no emphasis for non-sighted readers. Use the <code>em</code>. /code> tag instead.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['iframeMustNotHaveLongdesc'] = (object)array(
  'language' => 'en',
  'name' => 'Inline frames ("iframes") should not have a "longdesc" attribute',
  'quail_name' => 'iframeMustNotHaveLongdesc',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imageMapServerSide'] = (object)array(
  'language' => 'en',
  'name' => 'All links in a server-side map should have duplicate links available in the document',
  'quail_name' => 'imageMapServerSide',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image with an "usemap" attribute for a server-side image map should have the available links duplicated elsewhere.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltEmptyForDecorativeImages'] = (object)array(
  'language' => 'en',
  'name' => 'If an image is purely decorative, the "alt" text must be empty',
  'quail_name' => 'imgAltEmptyForDecorativeImages',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that is only decorative (serves no function or adds to the purpose of the page content) should have an "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltIdentifiesLinkDestination'] = (object)array(
  'language' => 'en',
  'name' => 'Any image within a link must have "alt" text the describes the link destination',
  'quail_name' => 'imgAltIdentifiesLinkDestination',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that is within a link should have an "alt" attribute which identifies the destination or purpose of the link.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltIsDifferent'] = (object)array(
  'language' => 'en',
  'name' => 'Image "alt" attributes should not be the same as the filename',
  'quail_name' => 'imgAltIsDifferent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>img</code>. /code> elements should have an "alt" attribute that is not just the name of the file',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltIsSameInText'] = (object)array(
  'language' => 'en',
  'name' => 'Check that any text within an image is also in the "alt" attribute',
  'quail_name' => 'imgAltIsSameInText',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If an image has text within it, that text should be repeated in the "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltIsTooLong'] = (object)array(
  'language' => 'en',
  'name' => 'Image Alt text is short',
  'quail_name' => 'imgAltIsTooLong',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All "alt" attributes for <code>img</code>. /code> elements should be clear and concise. "Alt" attributes over 100 characters long should be reviewed to see if they are too long.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltNotEmptyInAnchor'] = (object)array(
  'language' => 'en',
  'name' => 'An image within a link cannot have an empty "alt" attribute if there is no other text within the link',
  'quail_name' => 'imgAltNotEmptyInAnchor',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that is within a link (an <code>a</code>. /code> element) that has no other text cannot have an empty or missing "alt" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltNotPlaceHolder'] = (object)array(
  'language' => 'en',
  'name' => 'Images should not have a simple placeholder text as an "alt" attribute',
  'quail_name' => 'imgAltNotPlaceHolder',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that is not used decorativey or which is purely for layout purposes cannot have an "alt" attribute that consists solely of placeholders. Placeholders include:',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgAltTextNotRedundant'] = (object)array(
  'language' => 'en',
  'name' => 'Unless the image files are the same, no image should contain redundant alt text',
  'quail_name' => 'imgAltTextNotRedundant',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Every distinct image on a page should have it\'s own <em>alt</em> text which is different than all the others on the page to avoid redundancy and confusion.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgGifNoFlicker'] = (object)array(
  'language' => 'en',
  'name' => 'Any animated GIF should not flicker',
  'quail_name' => 'imgGifNoFlicker',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Animated GIF files should not flicker with a frequency over 2 Hz and lower than 55 Hz. You can check the flicker rate of this GIF <a href="http://tools.webaccessibile.org/test/check.aspx">using an online tool</a>.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgHasAlt'] = (object)array(
  'language' => 'en',
  'name' => 'Image elements must have an "alt" attribute',
  'quail_name' => 'imgHasAlt',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>img</code>. /code> elements must have an alt attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgHasLongDesc'] = (object)array(
  'language' => 'en',
  'name' => 'A "longdesc" attribute is required for any image where additional information not in the "alt" attribute is required',
  'quail_name' => 'imgHasLongDesc',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that has an "alt" attribute that does not fully convey the meaning of the image must have a "longdesc" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgImportantNoSpacerAlt'] = (object)array(
  'language' => 'en',
  'name' => 'Images that are important should not have a purely white-space "alt" attribute',
  'quail_name' => 'imgImportantNoSpacerAlt',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that is not used decorativey or which is purely for layout purposes cannot have an "alt" attribute that consists solely of white space (i.e. a space',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgMapAreasHaveDuplicateLink'] = (object)array(
  'language' => 'en',
  'name' => 'All links within a client-side image are duplicated elsewhere in the document',
  'quail_name' => 'imgMapAreasHaveDuplicateLink',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that has a "usemap" attribute must have links replicated somewhere else in the document.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgNonDecorativeHasAlt'] = (object)array(
  'language' => 'en',
  'name' => 'Any non-decorative images should have a non-empty "alt" attribute',
  'quail_name' => 'imgNonDecorativeHasAlt',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any image that is not used decorativey or which is purely for layout purposes cannot have an empty "alt" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgNotReferredToByColorAlone'] = (object)array(
  'language' => 'en',
  'name' => 'For any image, the "alt" text cannot refer to color alone',
  'quail_name' => 'imgNotReferredToByColorAlone',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The "alt" text or content text for any image should not refer to the image by color alone. This is often fixed by changing the "alt" text to the meaning of the image',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgServerSideMapNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'Server-side image maps should not be used',
  'quail_name' => 'imgServerSideMapNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Server-side image maps should not be used.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgShouldNotHaveTitle'] = (object)array(
  'language' => 'en',
  'name' => 'Images should not have a "title" attribute',
  'quail_name' => 'imgShouldNotHaveTitle',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Images should not contain a "title" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgWithMapHasUseMap'] = (object)array(
  'language' => 'en',
  'name' => 'Any image with an "ismap" attribute have a valid "usemap" attribute',
  'quail_name' => 'imgWithMapHasUseMap',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If an image has an "ismap" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['imgWithMathShouldHaveMathEquivalent'] = (object)array(
  'language' => 'en',
  'name' => 'Images which contain math equations should provide equivalent MathML',
  'quail_name' => 'imgWithMathShouldHaveMathEquivalent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Images which contain math equations should be accompanied or link to a document with the equivalent equation marked up with <a href="http://www.w3.org/Math/">MathML</a>.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputCheckboxHasTabIndex'] = (object)array(
  'language' => 'en',
  'name' => 'All "checkbox" input elements require a valid "tabindex" attribute',
  'quail_name' => 'inputCheckboxHasTabIndex',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements of type "checkbox" should have a "tabindex" attribute to help navigate the form with a keyboard alone.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputCheckboxRequiresFieldset'] = (object)array(
  'language' => 'en',
  'name' => 'Logical groups of check boxes should be grouped with a "fieldset',
  'quail_name' => 'inputCheckboxRequiresFieldset',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Related "checkbox" input fields should be grouped together using a <code>fieldset</code>.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputDoesNotUseColorAlone'] = (object)array(
  'language' => 'en',
  'name' => 'An "input" element should not use color alone',
  'quail_name' => 'inputDoesNotUseColorAlone',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All input elements should not refer to content by color alone.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputElementsDontHaveAlt'] = (object)array(
  'language' => 'en',
  'name' => 'Input elements which are not images should not have an "alt" attribute',
  'quail_name' => 'inputElementsDontHaveAlt',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Because of inconsistencies in how user agents use the "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputFileHasTabIndex'] = (object)array(
  'language' => 'en',
  'name' => 'All "file" input elements require a valid "tabindex" attribute',
  'quail_name' => 'inputFileHasTabIndex',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements of type "file" should have a "tabindex" attribute to help navigate the form with a keyboard alone.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputImageAltIdentifiesPurpose'] = (object)array(
  'language' => 'en',
  'name' => 'All "input" elements with a type of "image" must have an "alt" attribute that describes the function of the input',
  'quail_name' => 'inputImageAltIdentifiesPurpose',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "image" should have an "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputImageAltIsNotFileName'] = (object)array(
  'language' => 'en',
  'name' => 'All "input" elements with a type of "image" must have an "alt" attribute which is not the same as the filename',
  'quail_name' => 'inputImageAltIsNotFileName',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "image" should have an "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputImageAltIsNotPlaceholder'] = (object)array(
  'language' => 'en',
  'name' => 'All "input" elements with a type of "image" must have an "alt" attribute which is not placeholder text',
  'quail_name' => 'inputImageAltIsNotPlaceholder',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "image" should have an "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputImageAltIsShort'] = (object)array(
  'language' => 'en',
  'name' => 'All "input" elements with a type of "image" must have an "alt" attribute which is as short as possible',
  'quail_name' => 'inputImageAltIsShort',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "image" should have an "alt" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputImageAltNotRedundant'] = (object)array(
  'language' => 'en',
  'name' => 'The "alt" text for input "image" submit buttons must not be filler text',
  'quail_name' => 'inputImageAltNotRedundant',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Every form image button should not simply use filler text like "button" or "submit" as the "alt" text.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputImageHasAlt'] = (object)array(
  'language' => 'en',
  'name' => 'All "input" elements with a type of "image" must have an "alt" attribute',
  'quail_name' => 'inputImageHasAlt',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "image" should have an "alt" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputImageNotDecorative'] = (object)array(
  'language' => 'en',
  'name' => 'The "alt" text for input "image" buttons must be the same as text inside the image',
  'quail_name' => 'inputImageNotDecorative',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Every form image button which has text within the image (say, a picture of the word "Search" in a special font)',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputPasswordHasTabIndex'] = (object)array(
  'language' => 'en',
  'name' => 'All "password" input elements require a valid "tabindex" attribute',
  'quail_name' => 'inputPasswordHasTabIndex',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements of type "password" should have a "tabindex" attribute to help navigate the form with a keyboard alone.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputRadioHasTabIndex'] = (object)array(
  'language' => 'en',
  'name' => 'All "radio" input elements require a valid "tabindex" attribute',
  'quail_name' => 'inputRadioHasTabIndex',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements of type "radio" should have a "tabindex" attribute to help navigate the form with a keyboard alone.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputSubmitHasTabIndex'] = (object)array(
  'language' => 'en',
  'name' => 'All input elements, type of "submit',
  'quail_name' => 'inputSubmitHasTabIndex',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'have a valid tab index.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputTextHasLabel'] = (object)array(
  'language' => 'en',
  'name' => 'All "input" elements should have a corresponding "label',
  'quail_name' => 'inputTextHasLabel',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements should have a corresponding <code>label</code>. /code> element. Screen readers often enter a "form mode" where only label text is read aloud to the user',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputTextHasTabIndex'] = (object)array(
  'language' => 'en',
  'name' => 'All "text" input elements require a valid "tabindex" attribute',
  'quail_name' => 'inputTextHasTabIndex',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements of type "text" should have a "tabindex" attribute to help navigate the form with a keyboard alone.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputTextHasValue'] = (object)array(
  'language' => 'en',
  'name' => 'All "input" elements of type "text" must have a default text',
  'quail_name' => 'inputTextHasValue',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "text" should have a default text.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['inputTextValueNotEmpty'] = (object)array(
  'language' => 'en',
  'name' => 'Text" input elements require a non-whitespace default text',
  'quail_name' => 'inputTextValueNotEmpty',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "text" should have a default text which is not empty.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['labelDoesNotContainInput'] = (object)array(
  'language' => 'en',
  'name' => 'Label" elements should not contain an input element',
  'quail_name' => 'labelDoesNotContainInput',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['labelMustBeUnique'] = (object)array(
  'language' => 'en',
  'name' => 'Every form input must have only one label',
  'quail_name' => 'labelMustBeUnique',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Each form input should have only one <code>label</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['labelMustNotBeEmpty'] = (object)array(
  'language' => 'en',
  'name' => 'Labels must contain text',
  'quail_name' => 'labelMustNotBeEmpty',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['labelsAreAssignedToAnInput'] = (object)array(
  'language' => 'en',
  'name' => 'All labels should be associated with an input',
  'quail_name' => 'labelsAreAssignedToAnInput',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>label</code>. /code> elements should be assigned to an input item, and should have a <em>for</em> attribute which equals the <em>id</em> attribute of a form element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['legendDescribesListOfChoices'] = (object)array(
  'language' => 'en',
  'name' => 'All "legend" elements must describe the group of choices',
  'quail_name' => 'legendDescribesListOfChoices',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a <code>legend</code>. /code> element is used in a fieldset, the <code>legend</code>. /code> content must describe the group of choices.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['legendTextNotEmpty'] = (object)array(
  'language' => 'en',
  'name' => 'Legend" text must not contain just whitespace',
  'quail_name' => 'legendTextNotEmpty',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a <code>legend</code>. /code> element is used in a fieldset, the <code>legend</code>. /code> should not contain empty text.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['legendTextNotPlaceholder'] = (object)array(
  'language' => 'en',
  'name' => 'Legend" text must not contain placeholder text like "form" or "field',
  'quail_name' => 'legendTextNotPlaceholder',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a <code>legend</code>. /code> element is used in a fieldset, the <code>legend</code>. /code> should not contain useless placeholder text.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['liDontUseImageForBullet'] = (object)array(
  'language' => 'en',
  'name' => 'liDontUseImageForBullet',
  'quail_name' => 'liDontUseImageForBullet',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['linkUsedForAlternateContent'] = (object)array(
  'language' => 'en',
  'name' => 'Use a "link" element for alternate content',
  'quail_name' => 'linkUsedForAlternateContent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Documents which contain things like videos, sound, or other forms of media that are not accessible, should provide a <code>link</code>. /code> element with a "rel" attribute of "alternate" in the document header.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['linkUsedToDescribeNavigation'] = (object)array(
  'language' => 'en',
  'name' => 'Document uses link element to describe navigation if it is within a collection.',
  'quail_name' => 'linkUsedToDescribeNavigation',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The link element can provide metadata about the position of an HTML page within a set of Web units or can assist in locating content with a set of Web units.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['listNotUsedForFormatting'] = (object)array(
  'language' => 'en',
  'name' => 'Lists should not be used for formatting',
  'quail_name' => 'listNotUsedForFormatting',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Lists like <code>ul</code>. /code> and <code>ol</code>. /code> are to provide a structured list, and should not be used to format text. This test views any list with just one item as suspicious, but should be manually reviewed.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['marqueeIsNotUsed'] = (object)array(
  'language' => 'en',
  'name' => 'The "marquee" tag should not be used',
  'quail_name' => 'marqueeIsNotUsed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>marquee</code>. /code> element is difficult for users to read and is not a standard HTML element. Try to find another way to convey the importance of this text.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['menuNotUsedToFormatText'] = (object)array(
  'language' => 'en',
  'name' => 'Menu" elements should not be used for formattin',
  'quail_name' => 'menuNotUsedToFormatText',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Menu is a deprecated tag, but is still honored in a transitional DTD. Menu tags are to provide structure for a document and should not be used for formatting. If a menu tag is to be used, it should only contain an ordered or unordered list of links.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['noembedHasEquivalentContent'] = (object)array(
  'language' => 'en',
  'name' => 'Noembed" elements must be the same content as their "embed" element',
  'quail_name' => 'noembedHasEquivalentContent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>noembed</code>. /code> elements must contain or link to an accessible version of their <code>embed</code>. /code> counterparts.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['noframesSectionMustHaveTextEquivalent'] = (object)array(
  'language' => 'en',
  'name' => 'All "noframes" elements should contain the text content from all frames',
  'quail_name' => 'noframesSectionMustHaveTextEquivalent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The <code>noframes</code>. /code> content should either replicate or link to the content visible within the frames.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectContentUsableWhenDisabled'] = (object)array(
  'language' => 'en',
  'name' => 'When objects are disabled, content should still be available',
  'quail_name' => 'objectContentUsableWhenDisabled',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The content within objects should still be available, even if the object is disabled. To do this, place a link to the direct object source within the <code>object</code>. /code> tag.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectDoesNotFlicker'] = (object)array(
  'language' => 'en',
  'name' => 'Objects do not flicker',
  'quail_name' => 'objectDoesNotFlicker',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The content within an <code>object</code>. /code> tag must not flicker.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectDoesNotUseColorAlone'] = (object)array(
  'language' => 'en',
  'name' => 'Objects must not use color to communicate alone',
  'quail_name' => 'objectDoesNotUseColorAlone',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Objects should contain content that makes sense without color and is accessible to users who are color blind.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectInterfaceIsAccessible'] = (object)array(
  'language' => 'en',
  'name' => 'Interfaces within objects must be accessible',
  'quail_name' => 'objectInterfaceIsAccessible',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Object content should be assessed for accessibility.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectLinkToMultimediaHasTextTranscript'] = (object)array(
  'language' => 'en',
  'name' => 'Objects which reference multimedia files should also provide a link to a transcript',
  'quail_name' => 'objectLinkToMultimediaHasTextTranscript',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If an object contains a video, a link to the transcript should be provided near the object.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectMustContainText'] = (object)array(
  'language' => 'en',
  'name' => 'Objects must contain their text equivalents',
  'quail_name' => 'objectMustContainText',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>object</code>. /code> elements should contain a text equivalent if the object cannot be rendered.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectMustHaveEmbed'] = (object)array(
  'language' => 'en',
  'name' => 'Every object should contain an "embed" element',
  'quail_name' => 'objectMustHaveEmbed',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Every <code>object</code>. /code> element must also contain an <code>embed</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectMustHaveTitle'] = (object)array(
  'language' => 'en',
  'name' => 'Objects should have a title attribute',
  'quail_name' => 'objectMustHaveTitle',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>object</code>. /code> elements should contain a "title" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectMustHaveValidTitle'] = (object)array(
  'language' => 'en',
  'name' => 'Objects must not have an empty title attribute',
  'quail_name' => 'objectMustHaveValidTitle',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>object</code>. /code> elements should have a "title" attribute which is not empty.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectProvidesMechanismToReturnToParent'] = (object)array(
  'language' => 'en',
  'name' => 'All objects should provide a way for keyboard users to escape',
  'quail_name' => 'objectProvidesMechanismToReturnToParent',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Ensure that a user who has only a keyboard as an input device can escape a <code>object</code>. /code> element. This requires manual confirmation.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectShouldHaveLongDescription'] = (object)array(
  'language' => 'en',
  'name' => 'An object might require a long description',
  'quail_name' => 'objectShouldHaveLongDescription',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Objects might require a long description, especially if their content is complicated.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectTextUpdatesWhenObjectChanges'] = (object)array(
  'language' => 'en',
  'name' => 'The text equivalents of an object should update if the object changes',
  'quail_name' => 'objectTextUpdatesWhenObjectChanges',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If an object changes, the text equivalent of that object should also change.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectUIMustBeAccessible'] = (object)array(
  'language' => 'en',
  'name' => 'Content within an "object" element should be usable with objects disabled',
  'quail_name' => 'objectUIMustBeAccessible',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Objects who\'s content changes using java, ActiveX, or other similar technologies, should have their default text change when the object\'s content changes.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['objectWithClassIDHasNoText'] = (object)array(
  'language' => 'en',
  'name' => 'Objects with "classid" attributes should change their text if the content of the object changes',
  'quail_name' => 'objectWithClassIDHasNoText',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Objects who\'s content changes using java, ActiveX, or other similar technologies, should have their default text change when the object\'s content changes.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['pNotUsedAsHeader'] = (object)array(
  'language' => 'en',
  'name' => 'Paragraphs must not be used for headers',
  'quail_name' => 'pNotUsedAsHeader',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Headers like <code>h1</code>. h6 are extremely useful for non-sighted users to navigate the structure of the page, and formatting a paragraph to just be big or bold, while it might visually look like a header, does not make it one.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['paragarphIsWrittenClearly'] = (object)array(
  'language' => 'en',
  'name' => 'paragarphIsWrittenClearly',
  'quail_name' => 'paragarphIsWrittenClearly',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['passwordHasLabel'] = (object)array(
  'language' => 'en',
  'name' => 'All password input elements should have a corresponding label',
  'quail_name' => 'passwordHasLabel',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements with a type of "password"should have a corresponding <code>label</code>. /code> element. Screen readers often enter a "form mode" where only label text is read aloud to the user',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['passwordLabelIsNearby'] = (object)array(
  'language' => 'en',
  'name' => 'All "password" input elements have a label that is close',
  'quail_name' => 'passwordLabelIsNearby',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All input elements of type "password" must have a corresponding label that is close to the form element. Users of screen magnification or with reduced spatial skills are hampered in using a form element if the label for that element is located far away.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['preShouldNotBeUsedForTabularLayout'] = (object)array(
  'language' => 'en',
  'name' => 'Pre" elements should not be used for tabular data',
  'quail_name' => 'preShouldNotBeUsedForTabularLayout',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a <code>pre</code>. /code> element is used for tabular data, change the data to use a well-formed table.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['radioHasLabel'] = (object)array(
  'language' => 'en',
  'name' => 'All "radio" input elements have a corresponding label',
  'quail_name' => 'radioHasLabel',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>input</code>. /code> elements of type "radio" should have a corresponding <code>label</code>. /code> element. Screen readers often enter a "form mode" where only label text is read aloud to the user',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['radioLabelIsNearby'] = (object)array(
  'language' => 'en',
  'name' => 'All "radio" input elements have a label that is close',
  'quail_name' => 'radioLabelIsNearby',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All input elements of type "radio" must have a corresponding label that is close to the form element. Users of screen magnification or with reduced spatial skills are hampered in using a form element if the label for that element is located far away.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['radioMarkedWithFieldgroupAndLegend'] = (object)array(
  'language' => 'en',
  'name' => 'All radio button groups are marked using fieldset and legend elements.',
  'quail_name' => 'radioMarkedWithFieldgroupAndLegend',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'form element content must contain both fieldset and legend elements if there are related radio buttons.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptContentAccessibleWithScriptsTurnedOff'] = (object)array(
  'language' => 'en',
  'name' => 'Content on the page should still be available if scripts are disabled',
  'quail_name' => 'scriptContentAccessibleWithScriptsTurnedOff',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All scripts should be assessed to see if, when the user is browing with scrips turned off, the page content is still available.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptInBodyMustHaveNoscript'] = (object)array(
  'language' => 'en',
  'name' => 'Scripts should have a corresponding "noscript" element',
  'quail_name' => 'scriptInBodyMustHaveNoscript',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Scripts should be followed by a <code>noscripts</code>. /code> element to guide the user to content in an alternative way.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptOnclickRequiresOnKeypress'] = (object)array(
  'language' => 'en',
  'name' => 'If an element has an "onclick" attribute',
  'quail_name' => 'scriptOnclickRequiresOnKeypress',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'it should also have an "onkeypress" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptOndblclickRequiresOnKeypress'] = (object)array(
  'language' => 'en',
  'name' => 'Any element with an "ondblclick" attribute shoul have a keyboard-related action as well',
  'quail_name' => 'scriptOndblclickRequiresOnKeypress',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If an element has an "ondblclick" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptOnmousedownRequiresOnKeypress'] = (object)array(
  'language' => 'en',
  'name' => 'If an element has a "mousedown" attribute',
  'quail_name' => 'scriptOnmousedownRequiresOnKeypress',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'it should also have an "onkeydown" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptOnmousemove'] = (object)array(
  'language' => 'en',
  'name' => 'Any element with an "onmousemove" attribute shoul have a keyboard-related action as well',
  'quail_name' => 'scriptOnmousemove',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If an element has an "onmousemove" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptOnmouseoutHasOnmouseblur'] = (object)array(
  'language' => 'en',
  'name' => 'If an element has a "onmouseout" attribute',
  'quail_name' => 'scriptOnmouseoutHasOnmouseblur',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'it should also have an "onblur" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptOnmouseoverHasOnfocus'] = (object)array(
  'language' => 'en',
  'name' => 'If an element has an "onmouseover" attribute',
  'quail_name' => 'scriptOnmouseoverHasOnfocus',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'it should also have an "onfocus" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptOnmouseupHasOnkeyup'] = (object)array(
  'language' => 'en',
  'name' => 'If an element has an "onmouseup" attribute',
  'quail_name' => 'scriptOnmouseupHasOnkeyup',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'it should also have an "onkeyup" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptUIMustBeAccessible'] = (object)array(
  'language' => 'en',
  'name' => 'The user interface for scripts should be accessible',
  'quail_name' => 'scriptUIMustBeAccessible',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All scripts should be assessed to see if their interface is accessible.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptsDoNotFlicker'] = (object)array(
  'language' => 'en',
  'name' => 'Scripts should not cause the screen to flicker',
  'quail_name' => 'scriptsDoNotFlicker',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All scripts should be assessed to see if their interface does not flicker.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['scriptsDoNotUseColorAlone'] = (object)array(
  'language' => 'en',
  'name' => 'The interface in scripts should not use color alone',
  'quail_name' => 'scriptsDoNotUseColorAlone',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All scripts should be assessed to see if their interface does not have an interface which requires distinguishing beteween colors alone.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['selectDoesNotChangeContext'] = (object)array(
  'language' => 'en',
  'name' => 'Select" elemetns must not contain an "onchange" attribute',
  'quail_name' => 'selectDoesNotChangeContext',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Actions like "onchange" can take control away from users who are trying to navigate the page. Using an "onchange" attribute for things like select-list menus should instead be replaced with a drop-down and a button which initiates the action.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['selectHasAssociatedLabel'] = (object)array(
  'language' => 'en',
  'name' => 'All select elements have an explicitly associated label.',
  'quail_name' => 'selectHasAssociatedLabel',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>select</code>. /code> elements should have a corresponding <code>label</code>. /code> element. Screen readers often enter a "form mode" where only label text is read aloud to the user',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['selectJumpMenu'] = (object)array(
  'language' => 'en',
  'name' => 'Select jump menus should jump on button press, not on state change',
  'quail_name' => 'selectJumpMenu',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If you wish to use a \'Jump\' menu with a select item that then redirects users to another page, the jump should occur on the user pressing a button, rather than on the change event of that select eleemnt.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['selectWithOptionsHasOptgroup'] = (object)array(
  'language' => 'en',
  'name' => 'Form select elements should use optgroups for long selections',
  'quail_name' => 'selectWithOptionsHasOptgroup',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '.. code-block:: html',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['siteMap'] = (object)array(
  'language' => 'en',
  'name' => 'Websites must have a site map',
  'quail_name' => 'siteMap',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Every web site should have a page which provides a site map or another method to navigate most of the site from a single page to save time for users of assistive devices.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['skipToContentLinkProvided'] = (object)array(
  'language' => 'en',
  'name' => 'A "skip to content" link should exist as one of the first links on the page',
  'quail_name' => 'skipToContentLinkProvided',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'A link reading "skip to content',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['svgContainsTitle'] = (object)array(
  'language' => 'en',
  'name' => 'Inline SVG should use Title elements',
  'quail_name' => 'svgContainsTitle',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any inline SVG image should have an embedded <code>title</code>. /code> element',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tabIndexFollowsLogicalOrder'] = (object)array(
  'language' => 'en',
  'name' => 'The tab order of a document is logical',
  'quail_name' => 'tabIndexFollowsLogicalOrder',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Check that the tab-order of a page is logical.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableCaptionIdentifiesTable'] = (object)array(
  'language' => 'en',
  'name' => 'Captions should identify their table',
  'quail_name' => 'tableCaptionIdentifiesTable',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Check to make sure that a table\'s caption identifies the table with a name, figure number, etc.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableComplexHasSummary'] = (object)array(
  'language' => 'en',
  'name' => 'Complex tables should have a summary',
  'quail_name' => 'tableComplexHasSummary',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a table is complex (for example, has some cells with "colspan" attributes',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableDataShouldHaveTh'] = (object)array(
  'language' => 'en',
  'name' => 'Data tables should contain "th" elements',
  'quail_name' => 'tableDataShouldHaveTh',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Tables which contain data (as opposed to layout tables) should contain <code>th</code>. /code> elements to mark headers for screen readers and enhance the structure of the document.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableHeaderLabelMustBeTerse'] = (object)array(
  'language' => 'en',
  'name' => 'Table header lables must be terse',
  'quail_name' => 'tableHeaderLabelMustBeTerse',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The "abbr" attribute for table headers must be terse (less than 20 characters long).',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableIsGrouped'] = (object)array(
  'language' => 'en',
  'name' => 'Mark up the areas of tables using "thead',
  'quail_name' => 'tableIsGrouped',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'tbody',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableLayoutDataShouldNotHaveTh'] = (object)array(
  'language' => 'en',
  'name' => 'Layout tables should not contain "th" elements',
  'quail_name' => 'tableLayoutDataShouldNotHaveTh',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Tables which are used purely for layout (as opposed to data tables), <strong>should not</strong> contain <code>th</code>. /code> elements, which would make the table appear to be a data table.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableLayoutHasNoCaption'] = (object)array(
  'language' => 'en',
  'name' => 'All tables used for layout have no "caption" element',
  'quail_name' => 'tableLayoutHasNoCaption',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a table contains no data, and is used simply for layout, then it should not contain a <code>caption</code>. /code> element.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableLayoutHasNoSummary'] = (object)array(
  'language' => 'en',
  'name' => 'All tables used for layout have no summary or an empty summary',
  'quail_name' => 'tableLayoutHasNoSummary',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a table contains no data, and is used simply for layout, then it should not have a "summary" attribute',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableLayoutMakesSenseLinearized'] = (object)array(
  'language' => 'en',
  'name' => 'All tables used for layout should make sense when removed',
  'quail_name' => 'tableLayoutMakesSenseLinearized',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a <code>table</code>. /code> element is used for layout purposes only, then the content of the table should make sense if the table is linearized.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableNotUsedForLayout'] = (object)array(
  'language' => 'en',
  'name' => 'tableNotUsedForLayout',
  'quail_name' => 'tableNotUsedForLayout',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableSummaryDescribesTable'] = (object)array(
  'language' => 'en',
  'name' => 'Table summaries should describe the navigation and structure of the table',
  'quail_name' => 'tableSummaryDescribesTable',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Table <code>summary</code>. /code> elements should describe the navigation tools and structure of the table, as well as provide an overview of what the table describes.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableSummaryDoesNotDuplicateCaption'] = (object)array(
  'language' => 'en',
  'name' => 'Table "summary" elements should not duplicate the "caption" element',
  'quail_name' => 'tableSummaryDoesNotDuplicateCaption',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'The summary and the caption must be different, as both provide different information. A <code>caption</code>. /code element identifies the table., while the "summary" attribute describes the table contents.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableSummaryIsEmpty'] = (object)array(
  'language' => 'en',
  'name' => 'All data tables should have a summary',
  'quail_name' => 'tableSummaryIsEmpty',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a table contains data, it should have a "summary" attribute.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableSummaryIsNotTooLong'] = (object)array(
  'language' => 'en',
  'name' => 'tableSummaryIsNotTooLong',
  'quail_name' => 'tableSummaryIsNotTooLong',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => '',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableSummaryIsSufficient'] = (object)array(
  'language' => 'en',
  'name' => 'All data tables should have an adequate summary',
  'quail_name' => 'tableSummaryIsSufficient',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'If a table contains data, it should have a "summary" attribute that completely communicates the function and use of the table.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableUseColGroup'] = (object)array(
  'language' => 'en',
  'name' => 'Group columns using "colgroup" or "col" elements',
  'quail_name' => 'tableUseColGroup',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'To help complex table headers make sense, use <code>colgroup</code>. /code> or <code>col</code>. /code> to group them together.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableUsesAbbreviationForHeader'] = (object)array(
  'language' => 'en',
  'name' => 'Table headers over 20 characters should provide an "abbr" attribute',
  'quail_name' => 'tableUsesAbbreviationForHeader',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'For long table headers, use an "abbr" attribute that is less than short (less than 20 characters long).',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableUsesCaption'] = (object)array(
  'language' => 'en',
  'name' => 'Data tables should contain a "caption" element if not described elsewhere',
  'quail_name' => 'tableUsesCaption',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Unless otherwise described in the document, tables should contain <code>caption</code>. /code> elements to describe the purpose of the table.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableUsesScopeForRow'] = (object)array(
  'language' => 'en',
  'name' => 'Data tables should use scoped headers for rows with headers',
  'quail_name' => 'tableUsesScopeForRow',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Where there are table headers for both rows and columns, use the "scope" attribute to help relate those headers with their appropriate cells. This test looks for the first and last cells in each row and sees if they differ in layout or font weight.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableWithBothHeadersUseScope'] = (object)array(
  'language' => 'en',
  'name' => 'Data tables with multiple headers should use the "scope" attribute',
  'quail_name' => 'tableWithBothHeadersUseScope',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Where there are table headers for both rows and columns, use the "scope" attribute to help relate those headers with their appropriate cells.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tableWithMoreHeadersUseID'] = (object)array(
  'language' => 'en',
  'name' => 'Complex data tables should provide "id" attributes to headers',
  'quail_name' => 'tableWithMoreHeadersUseID',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'and "headers" attributes for data cells',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['tabularDataIsInTable'] = (object)array(
  'language' => 'en',
  'name' => 'All tabular information should use a table',
  'quail_name' => 'tabularDataIsInTable',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Tables should be used when displaying tabular information.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['textIsNotSmall'] = (object)array(
  'language' => 'en',
  'name' => 'The text size is not less than 9 pixels high',
  'quail_name' => 'textIsNotSmall',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'To help users with difficulty reading small text, ensure text size is no less than 9 pixels high.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['textareaHasAssociatedLabel'] = (object)array(
  'language' => 'en',
  'name' => 'All textareas should have a corresponding label',
  'quail_name' => 'textareaHasAssociatedLabel',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>textarea</code>. /code> elements should have a corresponding <code>label</code>. /code> element. Screen readers often enter a "form mode" where only label text is read aloud to the user',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['textareaLabelPositionedClose'] = (object)array(
  'language' => 'en',
  'name' => 'All textareas should have a label that is close to it',
  'quail_name' => 'textareaLabelPositionedClose',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All <code>textarea</code>. /code> elements should have a corresponding <code>label</code>. /code> element that is close in proximity..',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['videoProvidesCaptions'] = (object)array(
  'language' => 'en',
  'name' => 'All video tags must provide captions',
  'quail_name' => 'videoProvidesCaptions',
  'severity' => 'suggestion',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'All HTML5 video tags must provide captions.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
$accessibility_tests['videosEmbeddedOrLinkedNeedCaptions'] = (object)array(
  'language' => 'en',
  'name' => 'All linked or embedded videos need captions',
  'quail_name' => 'videosEmbeddedOrLinkedNeedCaptions',
  'severity' => 'severe',
  'status' => 1,
  'data' => array(),
  'error_description' => array(
    'und' => array(
      0 => array(
        'value' => 'Any video hosted or otherwise which is linked or embedded must have a caption.',
        'summary' => NULL,
        'format' => 'textbook_editor',
      ),
    ),
  ),
);
return $accessibility_tests;
}
