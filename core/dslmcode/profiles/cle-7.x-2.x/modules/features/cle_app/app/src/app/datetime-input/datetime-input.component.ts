import { Component, Input, forwardRef } from '@angular/core';
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
export class DatetimeInputComponent implements ControlValueAccessor {
  @Input() date:any;
  day:string;
  time:string;

  constructor() { 
  }

  // this series of functions enable the ControlValueAccessor to work.
  // see http://blog.thoughtram.io/angular/2016/07/27/custom-form-controls-in-angular-2.html
  writeValue(value:any) {
    if (value) {
      // if we do have a date set then we need to split out the day and the time
      let d = new Date(value);
      // convert it to an ISO string
      let dString = d.toISOString();
      // split the string at the time(T)
      let dSplit = dString.split("T");
      // split the string starting at the seconds(.)
      let tSplit = dSplit[1].split('.');
      // set the day and time values
      this.day = dSplit[0];
      this.time = tSplit[0];
    }
    else {
      // if there isn't a date value we are going
      this.day = '';
      this.time = '';
    }
    // Update the @Input
    this.date = value;
  }
  propagateChange = (_: any) => {};
  registerOnChange(fn) {
    this.propagateChange = fn;
  }
  registerOnTouched() { 
  }


  // convert day and time into a date and uptdate the date property
  updateDatetime() {
    if (typeof this.day !== 'undefined') {
      let d:string;
      d = this.day;

      // if there is a time then add that to the string
      if (typeof this.time !== 'undefined') {
        d = d + ' ' + this.time;
      }

      // convert string into date
      let date = new Date(d);
      this.date = date;
      this.propagateChange(this.date);
    }
  }
}
