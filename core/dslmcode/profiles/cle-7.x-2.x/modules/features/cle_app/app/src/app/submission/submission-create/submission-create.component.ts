import { Component, OnInit, ViewChild } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs';
import { Submission } from '../submission';
import { createSubmission } from '../submission.actions';
import { SubmissionFormComponent } from '../submission-form/submission-form.component';
import * as fromRoot from '../../app.reducer';
import { SubmissionStates } from '../submission.reducer';
declare const Materialize:any;
declare const jQuery:any

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
  isSaving:boolean = false;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private store: Store<fromRoot.State>
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
    this.userCanEdit$ = this.store.select(fromRoot.getUserPermissions)
      .map((state:any) => state.includes('edit own cle_submission content'));
    
    this.store.select(fromRoot.getSubmissionCurrentState)
      .subscribe((state:SubmissionStates) => {
        // saving is happening
        if (state === SubmissionStates.saving && !this.isSaving) {
          this.isSaving = true;
          Materialize.toast('Creating submission...', 30000, 'toast-submission-create');
        }
        else if (state === SubmissionStates.default && this.isSaving) {
          jQuery('.toast-submission-create').remove();
          Materialize.toast('Submission created', 1500);
          this.router.navigate(['/assignments/' + this.assignmentId]);
        }
      })
  }

  onSubmissionSave($event) {
    this.store.dispatch(createSubmission($event));
  }

  onSubmissionCancel($event) {
    this.router.navigate(['/assignments/' + this.assignmentId]);
    this.submissionFormComponent.form.reset();
  }
}
