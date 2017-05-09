import 'rxjs/add/operator/mergeMap';
import 'rxjs/add/operator/catch';
import { Response } from '@angular/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Action } from '@ngrx/store'
import { Effect, Actions } from '@ngrx/effects';
import {
  ActionTypes,
  loadAssignmentsSuccess,
  createAssignment,
  createAssignmentSuccess,
  createCritiqueAssignment,
  createCritiqueAssignmentSuccess,
  updateAssignmentSuccess,
  deleteAssignment,
  loadPermissions,
  loadPermissionsSuccess,
  startCritque,
  startCritqueSuccess,
  startCritqueFailure
} from './assignment.actions';
import { loadSubmissions } from '../submission/submission.actions';
import { AssignmentService } from './assignment.service';
import { ElmslnService } from '../elmsln.service';
import { Assignment } from './assignment';
declare const Materialize:any;

@Injectable()
export class AssignmentEffects {
  constructor(
    private actions$: Actions,
    private assignmentService:AssignmentService,
    private elmslnService: ElmslnService
  ) { }

  @Effect() createAssignment$ = this.actions$
    .ofType(ActionTypes.CREATE_ASSIGNMENT)
    .mergeMap(action => this.assignmentService.createAssignment(action.payload))
    .map(assignment => createAssignmentSuccess(assignment));
  
  @Effect() createCritiqueAssignment$ = this.actions$
    .ofType(ActionTypes.CREATE_CRITIQUE_ASSIGNMENT)
    .mergeMap(action => {
      return this.assignmentService.createAssignment(action.payload)
        .mergeMap((assignment:Assignment) => this.assignmentService.getAssignment(assignment.id));
    })
    .map(assignment => createCritiqueAssignmentSuccess(assignment));

  // Update the assignment on the server
  @Effect() updateAssignment$ = this.actions$
    .ofType(ActionTypes.UPDATE_ASSIGNMENT)
    .mergeMap(action => {
      return this.assignmentService.updateAssignment(action.payload)
        .mergeMap((data) => this.assignmentService.getAssignment(action.payload.id));
    })
    .map((assignment) => updateAssignmentSuccess(assignment));

  @Effect() loadAssignments$ = this.actions$
    .ofType(ActionTypes.LOAD_ASSIGNMENTS)
    .mergeMap(() => this.assignmentService.loadAssignments())
    // Dispatch action to load assignment success
    .map(assignments => loadAssignmentsSuccess(assignments))
  
  // Populate the user.permissions store when the user profile returns
  @Effect() loadPermissions$ = this.actions$
    .ofType(ActionTypes.LOAD_PERMISSIONS)
    .mergeMap(() => this.elmslnService.getUserProfile())
    .map(profile => {
      if (typeof profile.user.permissions !== 'undefined') {
        return loadPermissionsSuccess(profile.user.permissions, profile.user['csrf-token'], Number(profile.user['uid']));
      }
      else {
        return loadPermissionsSuccess([], null, null);
      }
    })

  @Effect({dispatch: false}) deleteAssignment$ = this.actions$
    .ofType(ActionTypes.DELETE_ASSIGNMENT)
    .mergeMap(action => this.assignmentService.deleteAssignment(action.payload))
    .map(info => {
      Materialize.toast('Assignment deleted', 1000);
    })

  @Effect() startCritique$ = this.actions$
    .ofType(ActionTypes.START_CRITQUE)
    .switchMap(action => this.assignmentService.startCritique(action.payload)
      .map(res => startCritqueSuccess(res.node))
      .catch(res => Observable.of(startCritqueFailure(res))))
  
  @Effect() startCritqueSuccess$ = this.actions$
    .ofType(ActionTypes.START_CRITQUE_SUCCESS)
    .map(action => loadSubmissions());
  
  @Effect({dispatch: false}) startCritiqueFailure$ = this.actions$
    .ofType(ActionTypes.START_CRITQUE_FAILURE)
    .map((state:any) => state.payload)
    .map((res:Response) => {
      // get the reason from the Response & convert to json
      let text = JSON.parse(res.text());
      let reason = text.detail ? text.detail : '';
      Materialize.toast('Could not start critique. ' + reason, 2500);
    })
}
