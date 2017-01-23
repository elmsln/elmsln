import { Component, OnInit, ElementRef } from '@angular/core';
declare const jQuery:any;

@Component({
  selector: 'app-dialog',
  templateUrl: './dialog.component.html',
  styleUrls: ['./dialog.component.css']
})
export class DialogComponent implements OnInit {

  constructor(
    private el:ElementRef
  ) { }

  ngOnInit() {
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal({
      dismissible: false,
      ready: function(modal, trigger) { // Callback for Modal open. Modal and trigger parameters available.
        /**
         * @todo: Hack to solve z-index issues when embeded in the Drupal site.
         */
        jQuery('.modal-overlay').appendTo('app-root');
      },
    });
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('open');
  }

  ngOnDestroy() {
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close')
  }
}
