import { Component, OnInit, ViewChild } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs';
import { Submission } from '../submission';
import { createSubmission } from '../submission.actions';
import { SubmissionFormComponent } from '../submission-form/submission-form.component';

@Component({
  selector: 'app-submission-create',
  templateUrl: './submission-create.component.html',
  styleUrls: ['./submission-create.component.css']
})
export class SubmissionCreateComponent implements OnInit {
  @ViewChild(SubmissionFormComponent) submissionFormComponent:SubmissionFormComponent;
  submission:Submission;
  assignmentId:number;
  userCanEdit$:Observable<boolean>;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private store: Store<{}>
  ) { }

  ngOnInit() {
    this.route.params
      .subscribe(params => {
        if (typeof params['assignmentId'] !== 'undefined') {
          let id = params['assignmentId'];
          this.assignmentId = Number(id);
          this.submission = Object.assign({}, new Submission(), {assignment:this.assignmentId})
        }
      });

    // check the permissions store to see if the user has edit
    this.userCanEdit$ = this.store.select('user')
      .map((state:any) => state.permissions.includes('edit own cle_submission content'));
  }

  onSubmissionSave($event) {
    this.store.dispatch(createSubmission($event));
  }

  onSubmissionCancel($event) {
  }
}
