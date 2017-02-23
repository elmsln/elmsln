import { Component, OnInit, Input, AfterViewInit, OnChanges } from '@angular/core';
import { ActivatedRoute, Router, Params } from '@angular/router';
import { Store } from '@ngrx/store';
import { loadSubmissions } from '../submission.actions';
import { Submission } from '../submission';
import { ElmslnService } from '../../elmsln.service';
import { Observable } from 'rxjs/Observable';
import { SubmissionService } from '../submission.service';
import { Assignment } from '../../assignment/assignment';

@Component({
  selector: 'app-submission-detail',
  templateUrl: './submission-detail.component.html',
  styleUrls: ['./submission-detail.component.css']
})
export class SubmissionDetailComponent implements OnInit, AfterViewInit, OnChanges {
  @Input() submission:Submission;
  submissionType$:Observable<string>;
  assignment$:Observable<Assignment>;

  constructor(
    private elmslnService:ElmslnService,
    private submissionService: SubmissionService
  ) { 
  }

  ngOnInit() {
  }

  ngAfterViewInit() {
    this.elmslnService.exportLifecycleHook('submissionDetailComponentInit');
  }

  ngOnChanges() {
    this.submissionType$ = this.submissionService.getSubmissionType(Observable.of(this.submission));
    this.assignment$ = this.submissionService.getSubmissionAssignment(this.submission);
  }
}