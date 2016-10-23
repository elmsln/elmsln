/**
 * @license Copyright (c) 2003-2016, CKSource - Frederico Knabben. All rights reserved.
 * For licensing, see LICENSE.md or http://ckeditor.com/license
 */

( function() {

	CKEDITOR.dialog.add( 'templates', function( editor ) {
		// Constructs the HTML view of the specified templates data.
		function renderTemplatesList( container, templatesDefinitions ) {
			// clear loading wait text.
			container.setHtml( '' );
			for ( var i = 0, totalDefs = templatesDefinitions.length; i < totalDefs; i++ ) {
				var definition = CKEDITOR.getTemplates( templatesDefinitions[ i ] ),
					imagesPath = definition.imagesPath,
					templates = definition.templates,
					count = templates.length;

				for ( var j = 0; j < count; j++ ) {
					var template = templates[ j ],
						item = createTemplateItem( template, imagesPath );
					item.setAttribute( 'aria-posinset', j + 1 );
					item.setAttribute( 'aria-setsize', count );
					container.append( item );
				}
			}
		}

		function createTemplateItem( template, imagesPath ) {
			var item = CKEDITOR.dom.element.createFromHtml( '<div class="col s3 cke_tpl_item_wrapper"><a class="ck-tpl-item-button" href="javascript:void(0)" tabIndex="-1" role="option" >' +
				'<div class="cke_tpl_item"></div>' +
				'</a></div>' );

			// Build the inner HTML of our new item DIV.
			var html = '<div class="cke_tpl_preview_wrapper" role="presentation">';

			if ( template.image && imagesPath ) {
				html += '<div class="cke_tpl_preview"><img class="cke_tpl_preview_img" src="' +
					CKEDITOR.getUrl( imagesPath + template.image ) + '"' +
					( CKEDITOR.env.ie6Compat ? ' onload="this.width=this.width"' : '' ) + ' alt="" title="" />';
			}

			html += '<div class="cke_tpl_title">' + template.title + '</div>';

			if ( template.description )
				html += '<div class="cke_tpl_description">' + template.description + '</div>';

			html += '</div></div>';

			item.getFirst().setHtml( html );

			item.on( 'click', function() {
				insertTemplate( template.html );
			} );

			return item;
		}

		// Insert the specified template content into editor.
		// @param {Number} index
		function insertTemplate( html ) {
			var dialog = CKEDITOR.dialog.getCurrent(),
				isReplace = dialog.getValueOf( 'selectTpl', 'chkInsertOpt' );

			if ( isReplace ) {
				editor.fire( 'saveSnapshot' );
				// Everything should happen after the document is loaded (#4073).
				editor.setData( html, function() {
					dialog.hide();

					// Place the cursor at the first editable place.
					var range = editor.createRange();
					range.moveToElementEditStart( editor.editable() );
					range.select();
					setTimeout( function() {
						editor.fire( 'saveSnapshot' );
					}, 0 );

				} );
			} else {
				editor.insertHtml( html );
				dialog.hide();
			}
		}

		function keyNavigation( evt ) {
			var target = evt.data.getTarget(),
				onList = listContainer.equals( target );

			// Keyboard navigation for template list.
			if ( onList || listContainer.contains( target ) ) {
				var keystroke = evt.data.getKeystroke(),
					items = listContainer.getElementsByTag( 'a' ),
					focusItem;

				if ( items ) {
					// Focus not yet onto list items?
					if ( onList )
						focusItem = items.getItem( 0 );
					else {
						switch ( keystroke ) {
							case 40: // ARROW-DOWN
								focusItem = target.getNext();
								break;

							case 38: // ARROW-UP
								focusItem = target.getPrevious();
								break;

							case 13: // ENTER
							case 32: // SPACE
								target.fire( 'click' );
						}
					}

					if ( focusItem ) {
						focusItem.focus();
						evt.data.preventDefault();
					}
				}
			}
		}

		// Load skin at first.
		var plugin = CKEDITOR.plugins.get( 'templates' );
		CKEDITOR.document.appendStyleSheet( CKEDITOR.getUrl( plugin.path + 'dialogs/templates.css' ) );


		var listContainer;

		var templateListLabelId = 'cke_tpl_list_label_' + CKEDITOR.tools.getNextNumber(),
			lang = editor.lang.templates,
			config = editor.config;
		return {
			title: editor.lang.templates.title,

			minWidth: CKEDITOR.env.ie ? 800 : 800,
			minHeight: 400,

			contents: [ {
				id: 'selectTpl',
				label: lang.title,
				elements: [ {
					type: 'vbox',
					padding: 5,
					children: [ {
						id: 'selectTplText',
						type: 'html',
						html: '<span>' +
							lang.selectPromptMsg +
							'</span>'
					},
					{
						id: 'templatesList',
						type: 'html',
						focus: true,
						html: '<div class="row cke_tpl_list" tabIndex="-1" role="listbox" aria-labelledby="' + templateListLabelId + '">' +
								'<div class="cke_tpl_loading"><span></span></div>' +
							'</div>' +
							'<span class="cke_voice_label" id="' + templateListLabelId + '">' + lang.options + '</span>'
					},
					{
						id: 'chkInsertOpt',
						type: 'checkbox',
						label: lang.insertOption,
						'default': config.templates_replaceContent
					} ]
				} ]
			} ],

			buttons: [ CKEDITOR.dialog.cancelButton ],

			onShow: function() {
				var templatesListField = this.getContentElement( 'selectTpl', 'templatesList' );
				listContainer = templatesListField.getElement();

				CKEDITOR.loadTemplates( config.templates_files, function() {
					var templates = ( config.templates || 'default' ).split( ',' );

					if ( templates.length ) {
						renderTemplatesList( listContainer, templates );
						templatesListField.focus();
					} else {
						listContainer.setHtml( '<div class="cke_tpl_empty">' +
							'<span>' + lang.emptyListMsg + '</span>' +
							'</div>' );
					}
				} );

				this._.element.on( 'keydown', keyNavigation );
			},

			onHide: function() {
				this._.element.removeListener( 'keydown', keyNavigation );
			}
		};
	} );
} )();
