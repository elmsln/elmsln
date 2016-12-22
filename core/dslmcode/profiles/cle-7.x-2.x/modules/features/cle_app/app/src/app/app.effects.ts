import 'rxjs/add/operator/mergeMap';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Action } from '@ngrx/store'
import { Effect, Actions } from '@ngrx/effects';
import { ActionTypes, loadAssignmentsSuccess, createAssignment } from './app.actions';
import { AssignmentService } from './assignment.service';

@Injectable()
export class AppEffects {
  constructor(
    private actions$: Actions,
    private assignmentService:AssignmentService
  ) { }

  @Effect() createAssignment$ = this.actions$
    .ofType(ActionTypes.CREATE_ASSIGNMENT)
    .mergeMap(action => this.assignmentService.createAssignment(action.payload))
    .map(assignmentInfo => {
      return {
        type: ActionTypes.CREATE_ASSIGNMENT_SUCCESS,
        payload: { id: Number(assignmentInfo.id) }
      }
    })

  @Effect() loadAssignments$ = this.actions$
    .ofType(ActionTypes.LOAD_ASSIGNMENTS)
    .mergeMap(() => this.assignmentService.loadAssignments())
    // Dispatch action to load assignment success
    .map(assignments => loadAssignmentsSuccess(assignments))
}
