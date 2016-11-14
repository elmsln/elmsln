import {
  Component, ElementRef, OnDestroy, Input, OnInit, EventEmitter, Output
} from '@angular/core';
import {Observable, Subject, BehaviorSubject} from "rxjs/Rx";
declare const jQuery: any;

@Component({
  selector: 'trumbowyg',
  templateUrl: './trumbowyg.component.html',
  styleUrls: ['./trumbowyg.component.css']
})
export class TrumbowygComponent implements OnInit {
  private loaded$: Observable<boolean>;
  private content$: Subject<string> = new BehaviorSubject("");
  private loadedSubscription: any;
  private updateSubscription: any;

  @Input('initialContent')
  set initialContent(value: string) {
    if(value) {
      this.content$.next(value);
    }
  }

    constructor(
    private el: ElementRef
  ) {}

  ngOnInit() {
    let el = jQuery(this.el.nativeElement).find('.ng-trumbowyg:first');
    console.log(el);
  }

}
