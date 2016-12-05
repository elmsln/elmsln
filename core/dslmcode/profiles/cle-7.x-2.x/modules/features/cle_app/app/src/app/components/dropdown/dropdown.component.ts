import { Component, OnInit, ContentChildren, QueryList, ElementRef, Input, Output } from '@angular/core';
declare const $:JQueryStatic;

@Component({
  selector: 'app-dropdown',
  templateUrl: './dropdown.component.html',
  styleUrls: ['./dropdown.component.css']
})
export class DropdownComponent implements OnInit {
  // button title
  @Input('button') button: string;
  // and array of objects whos key value pairs are attributes and values
  @Input('links') links: any[];
  
  constructor(
    private el: ElementRef
  ) { }

  ngOnInit() {
    (<any>$(this.el.nativeElement.firstElementChild)).dropdown();
  }
}
