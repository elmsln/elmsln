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
    .map((submissionInfo:any) => {
      Materialize.toast('Submission created', 1500);
      return createSubmissionSuccess(submissionInfo.id)
    });

  // Update the submission on the server
  @Effect() updateSubmission$ = this.actions$
    .ofType(ActionTypes.UPDATE_SUBMISSION)
    .mergeMap(action => {
      return this.submissionService.updateSubmission(action.payload)
        .mergeMap((data) => this.submissionService.getSubmission(action.payload.id));
    })
    .map((submission) => {
      Materialize.toast('Submission updated', 1500);
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
}
