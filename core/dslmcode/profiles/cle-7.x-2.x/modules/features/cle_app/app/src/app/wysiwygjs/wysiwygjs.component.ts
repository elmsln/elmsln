import { Component, OnInit, ElementRef, AfterViewInit, Input, Output, EventEmitter, OnDestroy, forwardRef } from '@angular/core';
import { ControlValueAccessor, NG_VALUE_ACCESSOR } from '@angular/forms'
import { Observable, Subject } from 'rxjs/Rx';
import { ElmslnService } from '../elmsln.service';
import { AppSettings } from '../app-settings';

// non-typescript definitions
declare var jQuery:any;
declare var Materialize:any;

@Component({
  selector: 'wysiwygjs',
  templateUrl: './wysiwygjs.component.html',
  styleUrls: ['./wysiwygjs.component.css'],
  providers:[
    {
      provide:NG_VALUE_ACCESSOR,
      useExisting: forwardRef(() => WysiwygjsComponent),
      multi: true
    }
  ]
})

export class WysiwygjsComponent implements OnInit, ControlValueAccessor {
  @Input() content:string;
  @Output() onContentUpdate: EventEmitter<any> = new EventEmitter();

  constructor(
    private el: ElementRef,
    private elmslnService: ElmslnService
  ) { }

  //ControlValueAccessor
  writeValue(value:any) {
    this.content = value;
    this.updateContent();
  }
  propagateChange = (_: any) => {};
  registerOnChange(fn) {
    this.propagateChange = fn;
  }
  registerOnTouched() { 
  }

  ngOnInit() {
      let newThis = this;
      jQuery(this.el.nativeElement.firstElementChild).each(function (index, element) {
        let wysiwygEditor = jQuery(element).wysiwyg({
              // 'selection'|'top'|'top-selection'|'bottom'|'bottom-selection'
              toolbar: 'top',
              buttons: {
                  insertimage: {
                      title: 'Insert image',
                      image: '\uf030', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      //showstatic: true,    // wanted on the toolbar
                      showselection: false    // wanted on selection
                  },
                  insertvideo: {
                      title: 'Insert video',
                      image: '\uf03d', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      //showstatic: true,    // wanted on the toolbar
                      showselection: false    // wanted on selection
                  },
                  insertlink: {
                      title: 'Insert link',
                      image: '\uf08e' // <img src="path/to/image.png" width="16" height="16" alt="" />
                  },
                  // Fontname plugin
                //   fontname: {
                //       title: 'Font',
                //       image: '\uf031', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       popup: function ($popup, $button) {
                //           var list_fontnames = {
                //               // Name : Font
                //               'Arial, Helvetica': 'Arial,Helvetica',
                //               'Verdana': 'Verdana,Geneva',
                //               'Georgia': 'Georgia',
                //               'Courier New': 'Courier New,Courier',
                //               'Times New Roman': 'Times New Roman,Times'
                //           };
                //           var $list = $('<div/>').addClass('wysiwyg-plugin-list')
                //               .attr('unselectable', 'on');
                //           $.each(list_fontnames, function (name, font) {
                //               var $link = $('<a/>').attr('href', '#')
                //                   .css('font-family', font)
                //                   .html(name)
                //                   .click(function (event) {
                //                       (<any>$(element)).wysiwyg('shell').fontName(font).closePopup();
                //                       // prevent link-href-#
                //                       event.stopPropagation();
                //                       event.preventDefault();
                //                       return false;
                //                   });
                //               $list.append($link);
                //           });
                //           $popup.append($list);
                //       },
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: index == 0 ? true : false    // wanted on selection
                //   },
                //   // Fontsize plugin
                //   fontsize: {
                //       title: 'Size',
                //       image: '\uf034', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       popup: function ($popup, $button) {
                //           // Hack: http://stackoverflow.com/questions/5868295/document-execcommand-fontsize-in-pixels/5870603#5870603
                //           var list_fontsizes = [];
                //           for (var i = 8; i <= 11; ++i)
                //               list_fontsizes.push(i + 'px');
                //           for (var i = 12; i <= 28; i += 2)
                //               list_fontsizes.push(i + 'px');
                //           list_fontsizes.push('36px');
                //           list_fontsizes.push('48px');
                //           list_fontsizes.push('72px');
                //           var $list = $('<div/>').addClass('wysiwyg-plugin-list')
                //               .attr('unselectable', 'on');
                //           $.each(list_fontsizes, function (index, size) {
                //               var $link = $('<a/>').attr('href', '#')
                //                   .html(size)
                //                   .click(function (event) {
                //                       (<any>$(element)).wysiwyg('shell').fontSize(7).closePopup();
                //                       (<any>$(element)).wysiwyg('container')
                //                           .find('font[size=7]')
                //                           .removeAttr("size")
                //                           .css("font-size", size);
                //                       // prevent link-href-#
                //                       event.stopPropagation();
                //                       event.preventDefault();
                //                       return false;
                //                   });
                //               $list.append($link);
                //           });
                //           $popup.append($list);
                //       },
                //       showselection: true    // wanted on selection
                //   },
                  // Header plugin
                  header: {
                      title: 'Header',
                      image: '\uf1dc', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      popup: function ($popup, $button) {
                          var list_headers = {
                              // Name : Font
                              'Header 1': '<h1>',
                              'Header 2': '<h2>',
                              'Header 3': '<h3>',
                              'Header 4': '<h4>',
                              'Header 5': '<h5>',
                              'Header 6': '<h6>',
                              'Code': '<pre>'
                          };
                          var $list = jQuery('<div/>').addClass('wysiwyg-plugin-list')
                              .attr('unselectable', 'on');
                          jQuery.each(list_headers, function (name, format) {
                              var $link = jQuery('<a/>').attr('href', '#')
                                  .css('font-family', format)
                                  .html(name)
                                  .click(function (event) {
                                      jQuery(element).wysiwyg('shell').format(format).closePopup();
                                      // prevent link-href-#
                                      event.stopPropagation();
                                      event.preventDefault();
                                      return false;
                                  });
                              $list.append($link);
                          });
                          $popup.append($list);
                      }
                      //showstatic: true,    // wanted on the toolbar
                      //showselection: false    // wanted on selection
                  },
                  bold: {
                      title: 'Bold (Ctrl+B)',
                      image: '\uf032', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      hotkey: 'b'
                  },
                  italic: {
                      title: 'Italic (Ctrl+I)',
                      image: '\uf033', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      hotkey: 'i'
                  },
                  underline: {
                      title: 'Underline (Ctrl+U)',
                      image: '\uf0cd', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      hotkey: 'u'
                  },
                  strikethrough: {
                      title: 'Strikethrough (Ctrl+S)',
                      image: '\uf0cc', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      hotkey: 's'
                  },
                //   forecolor: {
                //       title: 'Text color',
                //       image: '\uf1fc' // <img src="path/to/image.png" width="16" height="16" alt="" />
                //   },
                //   highlight: {
                //       title: 'Background color',
                //       image: '\uf043' // <img src="path/to/image.png" width="16" height="16" alt="" />
                //   },
                //   alignleft: index != 0 ? false : {
                //       title: 'Left',
                //       image: '\uf036', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: false    // wanted on selection
                //   },
                //   aligncenter: index != 0 ? false : {
                //       title: 'Center',
                //       image: '\uf037', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: false    // wanted on selection
                //   },
                //   alignright: index != 0 ? false : {
                //       title: 'Right',
                //       image: '\uf038', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: false    // wanted on selection
                //   },
                //   alignjustify: index != 0 ? false : {
                //       title: 'Justify',
                //       image: '\uf039', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: false    // wanted on selection
                //   },
                //   subscript: index == 1 ? false : {
                //       title: 'Subscript',
                //       image: '\uf12c', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: true    // wanted on selection
                //   },
                //   superscript: index == 1 ? false : {
                //       title: 'Superscript',
                //       image: '\uf12b', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: true    // wanted on selection
                //   },
                //   indent: index != 0 ? false : {
                //       title: 'Indent',
                //       image: '\uf03c', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: false    // wanted on selection
                //   },
                //   outdent: index != 0 ? false : {
                //       title: 'Outdent',
                //       image: '\uf03b', // <img src="path/to/image.png" width="16" height="16" alt="" />
                //       //showstatic: true,    // wanted on the toolbar
                //       showselection: false    // wanted on selection
                //   },
                  orderedList: index != 0 ? false : {
                      title: 'Ordered list',
                      image: '\uf0cb', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      //showstatic: true,    // wanted on the toolbar
                      showselection: false    // wanted on selection
                  },
                  unorderedList: index != 0 ? false : {
                      title: 'Unordered list',
                      image: '\uf0ca', // <img src="path/to/image.png" width="16" height="16" alt="" />
                      //showstatic: true,    // wanted on the toolbar
                      showselection: false    // wanted on selection
                  },
                  removeformat: {
                      title: 'Remove format',
                      image: '\uf12d' // <img src="path/to/image.png" width="16" height="16" alt="" />
                  }
              },
              // Other properties
              selectImage: 'Click to upload image',
              placeholderUrl: 'www.example.com',
              placeholderEmbed: '<embed/>',
              maxImageSize: [600, 200],
              onImageUpload: function (insert_image) {
              },
              forceImageUpload: false,    // upload images even if File-API is present
              videoFromUrl: function (url) {
                  // Contributions are welcome :-)

                  // youtube - http://stackoverflow.com/questions/3392993/php-regex-to-get-youtube-video-id
                  var youtube_match = url.match(/^(?:http(?:s)?:\/\/)?(?:[a-z0-9.]+\.)?(?:youtu\.be|youtube\.com)\/(?:(?:watch)?\?(?:.*&)?v(?:i)?=|(?:embed|v|vi|user)\/)([^\?&\"'>]+)/);
                  if (youtube_match && youtube_match[1].length == 11)
                      return '<iframe src="//www.youtube.com/embed/' + youtube_match[1] + '" width="640" height="360" frameborder="0" allowfullscreen></iframe>';

                  // vimeo - http://embedresponsively.com/
                  var vimeo_match = url.match(/^(?:http(?:s)?:\/\/)?(?:[a-z0-9.]+\.)?vimeo\.com\/([0-9]+)$/);
                  if (vimeo_match)
                      return '<iframe src="//player.vimeo.com/video/' + vimeo_match[1] + '" width="640" height="360" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen></iframe>';

                  // dailymotion - http://embedresponsively.com/
                  var dailymotion_match = url.match(/^(?:http(?:s)?:\/\/)?(?:[a-z0-9.]+\.)?dailymotion\.com\/video\/([0-9a-z]+)$/);
                  if (dailymotion_match)
                      return '<iframe src="//www.dailymotion.com/embed/video/' + dailymotion_match[1] + '" width="640" height="360" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen></iframe>';

                  // undefined -> create '<video/>' tag
              }
          });
      })
    

    .change(function () {
      // Assign the wysiwyg get contents to the content Observable
      // emit the change
      const target = jQuery(newThis.el.nativeElement).find('.wysiwyg-editor');
      target.find('img:not(.processed)').each(function(index,value) {
          let base64 = jQuery(this).attr('src');
          newThis.uploadImage(base64)
            .subscribe(
                url => {
                    jQuery(this).attr('src', url);
                    jQuery(this).addClass('processed');
                },
                error => {
                    jQuery(this).remove();
                    Materialize.toast('Image too big. Please resize and try again.', 1500);
                }
            )
            // .subscribe(url => {
            //     jQuery(this).attr('src', url).addClass('processed');
            //     console.log(url);
            //     return;
            // })
      });
      // Update content
      newThis.content = target.html();
      newThis.propagateChange(newThis.content);
      newThis.onContentUpdate.emit();
    })
  }

  updateContent() {
    jQuery(this.el.nativeElement).find('.wysiwyg-editor').html(this.content);
  }


  /**
   * @todo: not ready yet
   */
  resizeImage(data) {
    let image = new Image();
    image.src = data;
    let resize_canvas = document.createElement('canvas');
    resize_canvas.width = 800;
    resize_canvas.height = 800;
    resize_canvas.getContext('2d').drawImage(image, 0, 0, 800, 800);   
    return resize_canvas.toDataURL("image/jpg");
  }

  uploadImage(base64):Observable<string> {
    /**
     * @todo: need to actually upload this to the server
     */
    return this.elmslnService.createImage(base64)
        .map(data => data.url)
  }
}