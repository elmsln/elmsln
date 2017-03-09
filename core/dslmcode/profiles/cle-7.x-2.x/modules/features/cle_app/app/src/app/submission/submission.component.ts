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
  submissionId$:Observable<number>;
  submission$:Observable<Submission>;
  assignment$:Observable<Assignment>;
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
    this.submissionId$ = this.route.params
      .map((params:Params) => {
        if (params['submissionId']) {
          return Number(params['submissionId']);
        }
        else {
          return null;
        }
      })

    this.submission$ = Observable.combineLatest(
      this.submissionId$,
      this.store.select(fromRoot.getAllSubmissions),
      ((submissionId, submissions:Submission[]) => {
        return submissions.find((s) => s.id === submissionId);
      })
    )

    // get the assignment
    this.assignment$ = Observable.combineLatest(
      this.submission$,
      this.store.select(fromRoot.getAssignments),
      (s:Submission, assignments:Assignment[]) => assignments.find(a => a.id === s.assignment)
    )
    
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
    this.assignment$
      .subscribe(a => {
        if (a) {
          this.router.navigate(['/assignments/' + a.id])
        }
      })
  }

  editSubmission() {
    this.submission$
      .subscribe(s => {
        if (s) {
          this.router.navigate(['/submissions/' + s.id + '/edit']);
        }
      })
  }
}