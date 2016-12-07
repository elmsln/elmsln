import { Component, OnInit, Input, forwardRef } from '@angular/core';
import { ControlValueAccessor, NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
  selector: 'app-datetime-input',
  templateUrl: './datetime-input.component.html',
  styleUrls: ['./datetime-input.component.css'],
  providers:[
    {
      provide:NG_VALUE_ACCESSOR,
      useExisting: forwardRef(() => DatetimeInputComponent),
      multi: true
    }]
})
export class DatetimeInputComponent implements OnInit, ControlValueAccessor {
  @Input() date:any;
  day:string;
  time:string;

  constructor() { 
  }

  // this series of functions enable the ControlValueAccessor to work.
  // see http://blog.thoughtram.io/angular/2016/07/27/custom-form-controls-in-angular-2.html
  writeValue(value:any) {
    if (value !== undefined) {
      this.date = value;
    }
  }
  propagateChange = (_: any) => {};
  registerOnChange(fn) {
    this.propagateChange = fn;
  }
  registerOnTouched() { }

  ngOnInit() {
    console.log('Date Time initiated.');
  }

  // convert day and time into a date and uptdate the date property
  updateDatetime($event) {
    // make sure that both date and time have been added
    if (typeof this.day !== 'undefined' && typeof this.time !== 'undefined') {
      // concate day and time into a string
      let d:string;
      d = this.day + ' ' + this.time;
      // convert string into date
      let date = new Date(d);
      this.date = date;
      this.propagateChange(this.date);
    }
  }
}
