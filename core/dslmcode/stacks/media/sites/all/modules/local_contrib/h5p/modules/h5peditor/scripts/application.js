/* global Drupal */

var H5PEditor = H5PEditor || {};
var ns = H5PEditor;
(function ($) {
  ns.init = function () {
    var h5peditor;
    var $upload = $('input[name="files[h5p]"]').parents('.form-item');
    var $editor = $('.h5p-editor');
    var $create = $('#edit-h5p-editor').hide();
    var $type = $('input[name="h5p_type"]');
    var $params = $('input[name="json_content"]');
    var $library = $('input[name="h5p_library"]');
    var $maxscore = $('input[name="max_score"]');
    var titleFormElement = document.getElementById('h5p-plugin-form-title');
    var library = $library.val();

    ns.$ = H5P.jQuery;
    ns.basePath = Drupal.settings.basePath + Drupal.settings.h5peditor.modulePath + '/h5peditor/';
    ns.contentId = Drupal.settings.h5peditor.nodeVersionId;
    ns.fileIcon = Drupal.settings.h5peditor.fileIcon;
    ns.ajaxPath = Drupal.settings.h5peditor.ajaxPath;
    ns.filesPath = Drupal.settings.h5peditor.filesPath;
    ns.relativeUrl = Drupal.settings.h5peditor.relativeUrl;
    ns.contentRelUrl = Drupal.settings.h5peditor.contentRelUrl;
    ns.editorRelUrl = Drupal.settings.h5peditor.editorRelUrl;
    ns.apiVersion = Drupal.settings.h5peditor.apiVersion;
    ns.contentLanguage = Drupal.settings.h5peditor.language;

    // Semantics describing what copyright information can be stored for media.
    ns.copyrightSemantics = Drupal.settings.h5peditor.copyrightSemantics;
    ns.metadataSemantics = Drupal.settings.h5peditor.metadataSemantics;

    // Required styles and scripts for the editor
    ns.assets = Drupal.settings.h5peditor.assets;

    // Required for assets
    ns.baseUrl = Drupal.settings.basePath;
    ns.enableContentHub = Drupal.settings.h5peditor.enableContentHub;

    H5PIntegration.Hub = {
      contentSearchUrl: Drupal.settings.h5peditor.hub.contentSearchUrl
    };

    $type.change(function () {
      if ($type.filter(':checked').val() === 'upload') {
        $create.hide();
        $upload.show();
      }
      else {
        $upload.hide();
        if (h5peditor === undefined) {
          h5peditor = new ns.Editor(library, $params.val(), $editor[0]);
        }
        $create.show();
      }
    }).change();

    const $form = $('#h5p-content-node-form');

    // Keep track of button used to submit the form
    // We need to do this since the submit handler is run using an async callback,
    // which makes the button element not being set on the post (i.e: op=Save,
    // op=Delete and so on)
    var $submitter = $('<input type="hidden" name="op"/>').appendTo($form);
    const submitters = document.getElementsByName('op');
    for (let i = 0; i < submitters.length; i++) {
      submitters[i].addEventListener('click', function () {
        $submitter.val(this.value);
      });
    }

    let formIsUpdated = false;
    $form.submit(function (event) {
      if ($type.length && $type.filter(':checked').val() === 'upload') {
        return; // Old file upload
      }

      if (h5peditor !== undefined && !formIsUpdated) {

        // Get content from editor
        h5peditor.getContent(function (content) {

          // Set Drupal 7's title field
          titleFormElement.value = content.title

          // Set main library
          $library.val(content.library);

          // Set params
          $params.val(content.params);

          // Calculate & set max score
          //$maxscore.val(h5peditor.getMaxScore(params.params)); TODO: Return as part of content

          // Submit form data
          formIsUpdated = true;
          $form.submit();
        });

        // Stop default submit
        event.preventDefault();
      }
    });

  };

  ns.getAjaxUrl = function (action, parameters) {
    var url = Drupal.settings.h5peditor.ajaxPath + action;

    if (parameters !== undefined) {
      for (var key in parameters) {
        url += '/' + parameters[key];
      }
    }

    return url;
  };

  $(document).ready(ns.init);
})(H5P.jQuery);
