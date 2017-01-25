import 'rxjs/add/operator/mergeMap';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Action } from '@ngrx/store'
import { Effect, Actions } from '@ngrx/effects';
import {
  ActionTypes,
  loadSubmissionsSuccess,
  createSubmission,
  createSubmissionSuccess,
  updateSubmissionSuccess,
  deleteSubmission,
  loadPermissions,
  loadPermissionsSuccess,
} from './submission.actions';
import { loadAssignments } from '../app.actions';
import { SubmissionService } from './submission.service';
declare const Materialize:any;

@Injectable()
export class SubmissionEffects {
  constructor(
    private actions$: Actions,
    private submissionService:SubmissionService
  ) { }

  @Effect() createSubmission$ = this.actions$
    .ofType(ActionTypes.CREATE_SUBMISSION)
    .mergeMap(action => this.submissionService.createSubmission(action.payload))
    .mergeMap(sub => this.submissionService.getSubmission(sub.id))
    .map((sub:any) => createSubmissionSuccess(sub));

  // Update the submission on the server
  @Effect() updateSubmission$ = this.actions$
    .ofType(ActionTypes.UPDATE_SUBMISSION)
    .mergeMap(action => {
      return this.submissionService.updateSubmission(action.payload)
        .mergeMap((data) => {
          return this.submissionService.getSubmission(action.payload.id)
        });
    })
    .map((submission) => {
      return updateSubmissionSuccess(submission)
    });

  @Effect() loadSubmissions$ = this.actions$
    .ofType(ActionTypes.LOAD_SUBMISSIONS)
    .mergeMap(() => this.submissionService.loadSubmissions())
    // Dispatch action to load submission success
    .map(submissions => loadSubmissionsSuccess(submissions))

  @Effect({dispatch: false}) deleteSubmission$ = this.actions$
    .ofType(ActionTypes.DELETE_SUBMISSION)
    .mergeMap(action => this.submissionService.deleteSubmission(action.payload))
    .map(info => {
      Materialize.toast('Submission deleted', 1000);
    })
    
  @Effect() notifyAssignmentOnChange$ = this.actions$
    .ofType(ActionTypes.CREATE_SUBMISSION_SUCCESS, ActionTypes.UPDATE_SUBMISSION_SUCCESS)
    .map(action => loadAssignments());
}
