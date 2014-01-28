<?php
/**
 * @file
 * textbook_wcag20aa.accessibility_test.inc
 */

/**
 * Implements hook_accessibility_test_default().
 */
function textbook_wcag20aa_accessibility_test_default() {
$accessibility_tests = array();
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
return $accessibility_tests;
}
