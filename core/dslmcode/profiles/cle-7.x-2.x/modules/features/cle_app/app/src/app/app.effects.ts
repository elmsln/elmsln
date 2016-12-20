import 'rxjs/add/operator/mergeMap';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Action } from '@ngrx/store'
import { Effect, Actions } from '@ngrx/effects';
import { ActionTypes, loadAssignmentsSuccess } from './app.actions';
import { AssignmentService } from './assignment.service';

@Injectable()
export class AppEffects {
  constructor(
    private actions$: Actions,
    private assignmentService:AssignmentService
  ) { }

  @Effect() loadAssignments$ = this.actions$
    .ofType(ActionTypes.LOAD_ASSIGNMENTS)
    .mergeMap(() => this.assignmentService.loadAssignments())
    // Dispatch action to load assignment success
    .map(assignments => loadAssignmentsSuccess(assignments))
}
