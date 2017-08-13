var glob = require("glob");
var fs = require("fs");
var replace = require("replace-in-file");
var options = {
	files: [
		'../**/*.html'
	],
	from: [
    /<link .*polymer.html\W>/g,
    /<link .*lrn-icons.html\W>/g,
    /<link .*lrn-icon.html\W>/g,
    /<link .*lrndesign-card.html\W>/g,
    /<link .*lrndesign-drawer.html\W>/g,
    /<link .*contentsequencer-components.html\W>/g,
    /<link .*lrndesign-blockquote.html\W>/g,
    /<link .*lrndesign-contentsequencer.html\W>/g,
    /<link .*lrndesign-panelcard.html\W>/g,
    /<link .*lrn-vocab.html\W>/g,
    /<link .*lrn-aside.html\W>/g,
    /<link .*lrn-content.html\W>/g,
    /<link .*lrn-page.html\W>/g,
    /<link .*oer-schema.html\W>/g,
    /<link .*lrndesign-avatar.html\W>/g,
    /<link .*materializecss-styles.html\W>/g,
    /<link .*iron-pages.html\W>/g,
    /<link .*iron-iconset.html\W>/g,
    /<link .*iron-list.html\W>/g,
    /<link .*iron-icons.html\W>/g,
    /<link .*iron-iconset-svg.html\W>/g,
    /<link .*paper-card.html\W>/g,
    /<link .*google-webfont-loader.html\W>/g,
    /<link .*lrndesign-dialog.html\W>/g,
    /<link .*paper-menu-button.html\W>/g,
    /<link .*hax-behaviors.html\W>/g,
    /<link .*paper-dialog-scrollable.html\W>/g,
    /<link .*neon-animation.html\W>/g,
    /<link .*iron-scroll-threshold.html\W>/g,
    /<link .*wikipedia-query.html\W>/g,
    /<link .*lrndesign-abbreviation.html\W>/g,
    /<link .*lrndesign-buttondialog.html\W>/g,
    /<link .*lrndesign-comment.html\W>/g,
    /<link .*lrndesign-contactcard.html\W>/g,
    /<link .*lrndesign-contentblock.html\W>/g,
    /<link .*lrndesign-paperstack.html\W>/g,
    /<link .*lrn-assignment.html\W>/g,
    /<link .*paper-icon-button.html\W>/g,
    /<link .*hax-editbar.html\W>/g,
    /<link .*vaadin-upload.html\W>/g,
    /<link .*lrnapp-fab-menu.html\W>/g,
    /<link .*csv-render.html\W>/g,
    /<link .*lrndesign-stepper.html\W>/g,
    /<link .*time-elements.html\W>/g,
    /<link .*lrn-table.html\W>/g,
    /<link .*app-route.html\W>/g,
    /<link .*elmsln-loading.html\W>/g,
    /<link .*iron-resizable-behavior.html\W>/g,
    /<link .*lrnsys-layout.html\W>/g,
    /<link .*lrnsys-button.html\W>/g,
		/<link .*paper-toast.html\W>/g,
		/<link .*paper-input.html\W>/g,
		/<link .*paper-input-error.html\W>/g,
		/<link .*paper-tooltip.html\W>/g,
		/<link .*paper-button.html\W>/g,
		/<link .*iron-request.html\W>/g,
		/<link .*lrnsys-button.html\W>/g,
		/<link .*iron-icon.html\W>/g,
		/<link .*iron-ajax.html\W>/g,
		/<link .*paper-input-container.html\W>/g,
    /<link .*paper-input-char-counter.html\W>/g,
    /<link .*paper-ripple.html\W>/g,
    /<link .*iron-meta.html\W>/g,
    /<link .*iron-autogrow-textarea.html\W>/g,
    /<link .*paper-textarea.html\W>/g
	],
	to: ' '
};

replace(options)
  .then(changedFiles => {
    console.log('Modified files:', changedFiles.join(', '));
  })
  .catch(error => {
    console.error('Error occurred:', error);
  });
