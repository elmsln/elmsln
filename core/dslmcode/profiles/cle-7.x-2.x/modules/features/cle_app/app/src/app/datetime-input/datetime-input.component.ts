import { Component, OnInit, ElementRef } from '@angular/core';

@Component({
  selector: 'app-datetime-input',
  templateUrl: './datetime-input.component.html',
  styleUrls: ['./datetime-input.component.css']
})
export class DatetimeInputComponent implements OnInit {

  constructor(
    private el:ElementRef
  ) { 
  }

  ngOnInit() {
  }

}
