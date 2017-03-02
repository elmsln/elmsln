import 'rxjs/add/operator/mergeMap';
import { Injectable } from '@angular/core';
import { Response } from '@angular/http';
import { Observable } from 'rxjs/Observable';
import { Action } from '@ngrx/store'
import { Submission } from './submission';
import { Effect, Actions } from '@ngrx/effects';
import {
  ActionTypes,
  loadSubmissionsSuccess,
  createSubmission,
  createSubmissionSuccess,
  createSubmissionFailure,
  updateSubmissionSuccess,
  deleteSubmission,
  loadPermissions,
  loadPermissionsSuccess,
} from './submission.actions';
import { loadAssignments } from '../assignment/assignment.actions';
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
    .switchMap(action => this.submissionService.createSubmission(action.payload)
      .switchMap((sub:Submission) => this.submissionService.getSubmission(sub.id)
        .map((sub:Submission) => createSubmissionSuccess(sub)))
      .catch((res:Response) => Observable.of(createSubmissionFailure(res)))
    )
  
  @Effect() createSubmissionFailure$ = this.actions$
    .ofType(ActionTypes.CREATE_SUBMISSION_FAILURE)
    // get the response from the action payload
    .map((action:Action) => action.payload)
    .map((res:Response) => {
      Materialize.toast('Something went wrong saving your submission! Please copy your work and contact an administrator.', 10000, 'create-submission-failure')
    })

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
