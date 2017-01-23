import { Component, OnInit, Input, Output } from '@angular/core';
import { Submission } from '../submission';

@Component({
  selector: 'app-submission-edit-states',
  templateUrl: './submission-edit-states.component.html',
  styleUrls: ['./submission-edit-states.component.css']
})
export class SubmissionEditStatesComponent implements OnInit {
  @Input() submission:Submission;
  constructor(
  ) { }

  ngOnInit() {
  }
}
