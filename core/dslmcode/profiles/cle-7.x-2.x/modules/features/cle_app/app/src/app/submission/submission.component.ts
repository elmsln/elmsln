import { Component, OnInit, OnDestroy } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { Location } from '@angular/common';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs';
import { Submission } from './submission';
import { ElmslnService } from '../elmsln.service';
import { SubmissionService } from './submission.service';
import { Assignment } from '../assignment/assignment';
import * as fromRoot from '../app.reducer';

@Component({
  selector: 'app-submission',
  templateUrl: './submission.component.html',
  styleUrls: ['./submission.component.css']
})
export class SubmissionComponent implements OnInit {
  submissionId:number;
  submission$:Observable<Submission>;
  assignmentId: number;
  userCanEdit$:Observable<boolean>;
  submissionType$:Observable<string>;

  constructor(
    private route:ActivatedRoute,
    private store:Store<fromRoot.State>,
    private router:Router,
    private location:Location,
    private elmslnService:ElmslnService,
    private submissionService:SubmissionService
  ) { 
  }

  ngOnInit() {
    this.route.params
      .subscribe((params:Params) => {
        if (params['submissionId']) {
          this.submissionId = Number(params['submissionId']);

      }})

    // get the submission
    this.submission$ = this.store.select(fromRoot.getAllSubmissions)
      .map(s => s.find((i) => i.id === this.submissionId))
    // get the assignmentId
    this.submission$
      .filter(s => typeof s !== 'undefined')
      .subscribe(s => this.assignmentId = s.assignment);
    // check if the user can edit the submission
    this.userCanEdit$ = this.submission$
      .map((state:any) => {
        if (state) {
          if (typeof state.metadata !== 'undefined') {
            if (typeof state.metadata.canUpdate !== 'undefined') {
              return state.metadata.canUpdate;
            }
          }
        }
        return false;
      })
    // get the submission type
    this.submissionType$ = this.submissionService.getSubmissionType(this.submission$);
  }

  onClickBack() {
    this.router.navigate(['/assignments/' + this.assignmentId]);
  }

  editSubmission() {
    this.router.navigate(['/submissions/' + this.submissionId + '/edit']);
  }
}