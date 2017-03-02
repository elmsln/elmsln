import { Critique } from '../critique';
import { Action } from '@ngrx/store';
import { Assignment } from './assignment';
import { Response } from '@angular/http';

export const ActionTypes = {
  CREATE_ASSIGNMENT: 'CREATE_ASSIGNMENT',
  CREATE_ASSIGNMENT_SUCCESS: 'CREATE_ASSIGNMENT_SUCCESS',
  CREATE_CRITIQUE_ASSIGNMENT: 'CREATE_CRITIQUE_ASSIGNMENT',
  CREATE_CRITIQUE_ASSIGNMENT_SUCCESS: 'CREATE_CRITIQUE_ASSIGNMENT_SUCCESS',
  UPDATE_ASSIGNMENT: 'UPDATE_ASSIGNMENT',
  UPDATE_ASSIGNMENT_SUCCESS: 'UPDATE_ASSIGNMENT_SUCCESS',
  DELETE_ASSIGNMENT: 'DELETE_ASSIGNMENT',
  LOAD_ASSIGNMENTS: 'LOAD_ASSIGNMENTS',
  LOAD_ASSIGNMENTS_SUCCESS: 'LOAD_ASSIGNMENTS_SUCCESS',
  LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
  LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS',
  START_CRITQUE: 'START_CRITQUE',
  START_CRITQUE_SUCCESS: 'START_CRITQUE_SUCCESS',
  START_CRITQUE_FAILURE: 'START_CRITQUE_FAILURE',
}

export function createAssignment(assignment): Action {
  return {
    type: ActionTypes.CREATE_ASSIGNMENT,
    payload: assignment
  }
}

export function createAssignmentSuccess(assignment): Action {
  return {
    type: ActionTypes.CREATE_ASSIGNMENT_SUCCESS,
    payload: assignment
  }
}

export function createCritiqueAssignment(assignment): Action {
  let newAssignment = Object.assign(new Assignment, {
    title: assignment.title + ' critique',
    hierarchy: {
      dependencies: [assignment.id],
      project: assignment.project
    },
    critiqueMethod: 'random',
    startDate: assignment.startDate,
    endDate: assignment.endDate
  });
  return {
    type: ActionTypes.CREATE_CRITIQUE_ASSIGNMENT,
    payload: newAssignment
  }
}

export function createCritiqueAssignmentSuccess(assignment): Action {
  return {
    type: ActionTypes.CREATE_CRITIQUE_ASSIGNMENT_SUCCESS,
    payload: assignment
  }
}

export function updateAssignment(assignment): Action {
  return {
    type: ActionTypes.UPDATE_ASSIGNMENT,
    payload: assignment
  }
}

export function updateAssignmentSuccess(assignment): Action {
  return {
    type: ActionTypes.UPDATE_ASSIGNMENT_SUCCESS,
    payload: assignment
  }
}

export function deleteAssignment(assignment): Action {
  return {
    type: ActionTypes.DELETE_ASSIGNMENT,
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

export function loadPermissions(): Action {
  return {
    type: ActionTypes.LOAD_PERMISSIONS,
    payload: {}
  }
}

export function loadPermissionsSuccess(permissions, token, uid): Action {
  return {
    type: ActionTypes.LOAD_PERMISSIONS_SUCCESS,
    payload: {permissions: permissions, token: token, uid: uid}
  }
}

export function startCritque(assignment:Assignment): Action {
  return {
    type: ActionTypes.START_CRITQUE,
    payload: assignment
  }
}

export function startCritqueSuccess(assignment:Assignment): Action {
  return {
    type: ActionTypes.START_CRITQUE_SUCCESS,
    payload: assignment
  }
}

export function startCritqueFailure(res:Response): Action {
  return {
    type: ActionTypes.START_CRITQUE_FAILURE,
    payload: res
  }
}