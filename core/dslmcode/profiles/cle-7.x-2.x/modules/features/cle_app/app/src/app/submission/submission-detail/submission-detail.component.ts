import { Component, OnInit, Input } from '@angular/core';
import { ActivatedRoute, Router, Params } from '@angular/router';
import { Store } from '@ngrx/store';
import { loadSubmissions } from '../submission.actions';
import { Submission } from '../submission';

@Component({
  selector: 'app-submission-detail',
  templateUrl: './submission-detail.component.html',
  styleUrls: ['./submission-detail.component.css']
})
export class SubmissionDetailComponent implements OnInit {
  @Input() submission:Submission;

  constructor(
  ) { 
  }

  ngOnInit() {
  }
}