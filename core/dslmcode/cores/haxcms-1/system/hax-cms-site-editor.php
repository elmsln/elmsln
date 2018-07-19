<?php
  include_once 'lib/bootstrapHAX.php';
  include_once $HAXCMS->configDirectory . '/config.php';
?>
<link rel="import" href="../webcomponents/bower_components/polymer/polymer.html">
<link rel="import" href="../webcomponents/bower_components/iron-ajax/iron-ajax.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-store.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-body.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-autoloader.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-manager.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-app-picker.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-app.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-panel.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-export-dialog.html">
<link rel="import" href="../webcomponents/bower_components/hax-body/hax-toolbar.html">
<link rel="import" href="../webcomponents/bower_components/paper-fab/paper-fab.html">
<link rel="import" href="../webcomponents/bower_components/paper-tooltip/paper-tooltip.html">
<link rel="import" href="../webcomponents/bower_components/iron-icons/editor-icons.html">
<!--
`jwt-login`
a simple element to check for and fetch JWTs

@demo demo/index.html

@microcopy - the mental model for this element
- jwt - a json web token which is an encrypted security token to talk

-->

<dom-module id="hax-cms-site-editor">
  <template>
    <style>
      :host {
        display: block;
      }
      #editbutton {
        position: fixed;
        bottom: 0;
        right: 0;
        margin: 16px;
        padding: 8px;
        width: 40px;
        height: 40px;
        visibility: visible;
        opacity: 1;
        transition: all .4s ease;
      }
      :host[edit-mode] #editbutton {
        width: 100%;
        z-index: 100;
        right: 0;
        bottom: 0;
        border-radius: 0;
        height: 80px;
        margin: 0;
        padding: 8px;
        background-color: var(--paper-blue-500) !important;
      }
      hax-body {
        padding: 1em;
        max-width: 65em;
        margin: auto;
        display: none;
      }
      :host[edit-mode] hax-body {
        display: block;
      }
    </style>
    <iron-ajax
     headers='{"Authorization": "Bearer [[jwt]]"}'
     id="pageupdateajax"
     url="<?php print $HAXCMS->basePath . 'system/savePage.php';?>"
     method="POST"
     body="[[updatePageData]]"
     content-type="application/json"
     handle-as="json"
     on-response="_handlePageResponse"></iron-ajax>
    <iron-ajax
     headers='{"Authorization": "Bearer [[jwt]]"}'
     id="outlineupdateajax"
     url="<?php print $HAXCMS->basePath . 'system/saveOutline.php';?>"
     method="POST"
     body="[[updateOutlineData]]"
     content-type="application/json"
     handle-as="json"
     on-response="_handleOutlineResponse"></iron-ajax>
    <hax-store app-store='<?php print json_encode($HAXCMS->appStoreConnection());?>'></hax-store>
    <hax-app-picker></hax-app-picker>
    <hax-body></hax-body>
    <hax-autoloader hidden></hax-autoloader>
    <hax-panel align="left" hide-panel-ops></hax-panel>
    <hax-manager></hax-manager>
    <hax-export-dialog></hax-export-dialog>
    <paper-fab id="editbutton" icon="[[__editIcon]]"></paper-fab>
    <paper-tooltip for="editbutton" position="bottom" offset="14">[[__editText]]</paper-tooltip>
    </template>
  <script>
    Polymer.haxCmsSiteEditor = Polymer({
      is: 'hax-cms-site-editor',
      listeners: {
        'editbutton.click': '_editButtonTap',
      },
      properties: {
        /**
         * JSON Web token, it'll come from a global call if it's available
         */
        jwt: {
          type: String,
        },
        /**
         * if the page is in an edit state or not
         */
        editMode: {
          type: String,
          reflectToAttribute: true,
          observer: '_editModeChanged',
          value: false,
        },
        /**
         * data as part of the POST to the backend
         */
        updatePageData: {
          type: Object,
          value: {},
        },
        /**
         * data as part of the POST to the backend
         */
        updateOutlineData: {
          type: Object,
          value: {},
        },
        /**
         * Active item of the page being worked on, JSON outline schema item format
         */
        activeItem: {
          type: Object,
          value: {},
        },
        /**
         * element that's controlling this one effectively and supplying the design
         */
        appElement: {
          type: Object,
        },
      },
      /**
       * Reaady life cycle
       */
      ready: function () {
        document.body.addEventListener('outline-player-active-item-changed', this._newActiveItem.bind(this));      
        document.body.addEventListener('haxcms-body-changed', this._bodyChanged.bind(this));      
      },
      /**
       * Attached life cycle
       */
      attached: function () {
        this.jwt = localStorage.getItem('jwt');
      },
      /**
       * Items has changed, these items live in lrnsys-outline
       */
       _itemsChanged: function (e) {
         console.log(e);
       },
      /**
       * update the internal active item
       */
       _newActiveItem: function (e) {
         this.set('activeItem', e.detail);
       },
      /**
       * toggle state on button tap
       */
      _editButtonTap: function (e) {
        this.editMode = !this.editMode;
      },
      /**
       * handle update responses for pages and outlines
       */
       _handlePageResponse: function (e) {

       },
       _handleOutlineResponse: function (e) {
         // trigger a refresh of the data in page
         this.appElement.haxCMSRefesh();
       },
      /**
       * Edit state has changed.
       */
      _editModeChanged: function (newValue, oldValue) {
        if (newValue) {
          // enable it some how
          this.__editIcon = 'icons:save';
          this.__editText = 'Save';
        }
        else {
          // disable it some how
          this.__editIcon = 'editor:mode-edit';
          this.__editText = 'Edit';
        }
        this.fire('edit-mode-changed', newValue);
        Polymer.HaxStore.write('editMode', newValue, this);
        // was on, now off
        if (!newValue && oldValue) {
          let parts = window.location.pathname.split('/');
          parts.pop();
          let site = parts.pop();
          this.set('updatePageData.siteName', site);
          this.set('updatePageData.body', Polymer.HaxStore.instance.activeHaxBody.haxToContent());
          this.set('updatePageData.page', this.activeItem.id);
          this.set('updatePageData.jwt', this.jwt);
          // send the request
          this.$.pageupdateajax.generateRequest();
          // now let's work on the outline
          this.set('updateOutlineData.siteName', site);
          this.set('updateOutlineData.items', this.appElement.outline);
          this.set('updateOutlineData.jwt', this.jwt);
          this.$.outlineupdateajax.generateRequest();
        }
      },
      /**
       * Notice body of content has changed and import into HAX
       */
      _bodyChanged: function (e) {
        Polymer.HaxStore.instance.activeHaxBody.importContent(e.detail);
      },
    });
    // store reference to the instance as a global
    Polymer.haxCmsSiteEditor.instance = null;
    // self append if anyone calls us into action
    Polymer.haxCmsSiteEditor.requestAvailability = function (location = document.body, app = null) {
      if (!Polymer.haxCmsSiteEditor.instance) {
        Polymer.haxCmsSiteEditor.instance = document.createElement('hax-cms-site-editor');
        Polymer.haxCmsSiteEditor.instance.appElement = app;
      }
      location.appendChild(Polymer.haxCmsSiteEditor.instance);
    };
  </script>
</dom-module>