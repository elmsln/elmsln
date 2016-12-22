import { Action } from '@ngrx/store';

export const ActionTypes = {
  CREATE_ASSIGNMENT: 'CREATE_ASSIGNMENT',
  UPDATE_ASSIGNMENT: 'UPDATE_ASSIGNMENT',
  DELETE_ASSIGNMENT: 'DELETE_ASSIGNMENT',
  LOAD_ASSIGNMENTS: 'LOAD_ASSIGNMENTS',
  LOAD_ASSIGNMENTS_SUCCESS: 'LOAD_ASSIGNMENTS_SUCCESS'
}

export function createAssignment(assignment): Action {
  return {
    type: ActionTypes.CREATE_ASSIGNMENT,
    payload: assignment
  }
}

export function loadAssignments(): Action {
  return {
    type: ActionTypes.LOAD_ASSIGNMENTS,
    payload: { }
  }
}

export function loadAssignmentsSuccess(assignments): Action {
  return {
    type: ActionTypes.LOAD_ASSIGNMENTS_SUCCESS,
    payload: assignments
  }
}