/**
 * Custom editor config for options wysiwyg api doesn't provide.
 */
CKEDITOR.editorConfig = function( config ) {
  // MaterializeCSS color codes / class names
  config.colorButton_colors = 'red/f44336,pink/e91e63,purple/9c27b0,deep-purple/673ab7,indigo/3f51b5,blue/2196f3,light-blue/03a9f4,cyan/00bcd4,teal/009688,green/4caf50,light-green/8bc34a,lime/cddc39,yellow/ffeb3b,amber/ffc107,orange/ff9800,deep-orange/ff5722,brown/795548,grey/9e9e9e,blue-grey/607d8b,black/000000,white/ffffff';
  // apply this as a class for text color
  config.colorButton_foreStyle = {
    element: 'span',
    attributes: { class: '#(color)-text' }
  };
  // apply this as a class for backgrounds
  config.colorButton_backStyle = {
    element: 'span',
    attributes: { class: '#(color)' }
  };
  // this helps ensure there's no conflict with made up elements
  // and automatical <p> wrapping
  config.autoParagraph = false;
  // protected source
  config.protectedSource = [<(!-{2,}|(\S*?)-(\S*?)\s*>)[\s\S]*?(<\/(\S*?)-(\S*?)|(-{2,}))>/g];
  // config.styleSet is an array of objects that define each style available
  // in the font styles tool in the ckeditor toolbar
  config.disableNativeSpellChecker = false;
  // disable ability to use spellcheck inline
  config.removePlugins = 'scayt';
  // hitting control, they'll be able to use browser native spellchecker
  config.browserContextMenuOnCtrl = true;
  config.mathJaxLib = '//cdn.mathjax.org/mathjax/2.2-latest/MathJax.js?config=TeX-AMS_HTML';
  // activate codemirror as UI won't allow it
  config.extraPlugins = 'codemirror';
  // add codemirror settings
  config.codemirror = {
    // Set this to the theme you wish to use (codemirror themes)
    theme: 'default',
    // Whether or not you want to show line numbers
    lineNumbers: true,
    // Whether or not you want to use line wrapping
    lineWrapping: true,
    // Whether or not you want to highlight matching braces
    matchBrackets: true,
    // Whether or not you want tags to automatically close themselves
    autoCloseTags: true,
    // Whether or not you want Brackets to automatically close themselves
    autoCloseBrackets: true,
    // Whether or not to enable search tools, CTRL+F (Find), CTRL+SHIFT+F (Replace), CTRL+SHIFT+R (Replace All), CTRL+G (Find Next), CTRL+SHIFT+G (Find Previous)
    enableSearchTools: true,
    // Whether or not you wish to enable code folding (requires 'lineNumbers' to be set to 'true')
    enableCodeFolding: true,
    // Whether or not to enable code formatting
    enableCodeFormatting: true,
    // Whether or not to automatically format code should be done when the editor is loaded
    autoFormatOnStart: true,
    // Whether or not to automatically format code should be done every time the source view is opened
    autoFormatOnModeChange: true,
    // Whether or not to automatically format code which has just been uncommented
    autoFormatOnUncomment: true,
    // Whether or not to highlight the currently active line
    highlightActiveLine: true,
    // Define the language specific mode 'htmlmixed' for html including (css, xml, javascript), 'application/x-httpd-php' for php mode including html, or 'text/javascript' for using java script only
    mode: 'htmlmixed',
    // Whether or not to show the search Code button on the toolbar
    showSearchButton: true,
    // Whether or not to show Trailing Spaces
    showTrailingSpace: true,
    // Whether or not to highlight all matches of current word/selection
    highlightMatches: true,
    // Whether or not to show the format button on the toolbar
    showFormatButton: true,
    // Whether or not to show the comment button on the toolbar
    showCommentButton: true,
    // Whether or not to show the uncomment button on the toolbar
    showUncommentButton: true,
    // Whether or not to show the showAutoCompleteButton button on the toolbar
    showAutoCompleteButton: true,
    // extra setting from Nikki
    showTabs: true,
  };
}
