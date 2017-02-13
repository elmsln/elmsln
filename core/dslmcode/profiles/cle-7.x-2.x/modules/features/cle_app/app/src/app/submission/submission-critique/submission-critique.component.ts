import { Component, OnInit, Input } from '@angular/core';
import { Submission } from '../submission';

@Component({
  selector: 'app-submission-critique',
  templateUrl: './submission-critique.component.html',
  styleUrls: ['./submission-critique.component.scss']
})
export class SubmissionCritiqueComponent implements OnInit {
  @Input() submission: Submission;

  constructor() { }

  ngOnInit() {
  }

}
