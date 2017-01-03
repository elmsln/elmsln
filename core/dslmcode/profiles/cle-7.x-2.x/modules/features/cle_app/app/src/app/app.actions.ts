import { Action } from '@ngrx/store';

export const ActionTypes = {
  CREATE_ASSIGNMENT: 'CREATE_ASSIGNMENT',
  CREATE_ASSIGNMENT_SUCCESS: 'CREATE_ASSIGNMENT_SUCCESS',
  UPDATE_ASSIGNMENT: 'UPDATE_ASSIGNMENT',
  UPDATE_ASSIGNMENT_SUCCESS: 'UPDATE_ASSIGNMENT_SUCCESS',
  DELETE_ASSIGNMENT: 'DELETE_ASSIGNMENT',
  LOAD_ASSIGNMENTS: 'LOAD_ASSIGNMENTS',
  LOAD_ASSIGNMENTS_SUCCESS: 'LOAD_ASSIGNMENTS_SUCCESS',
  LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
  LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS'
}

export function createAssignment(assignment): Action {
  return {
    type: ActionTypes.CREATE_ASSIGNMENT,
    payload: assignment
  }
}

export function createAssignmentSuccess(assignmentId): Action {
  return {
    type: ActionTypes.CREATE_ASSIGNMENT_SUCCESS,
    payload: { id: assignmentId }
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

export function loadPermissionsSuccess(permissions): Action {
  return {
    type: ActionTypes.LOAD_PERMISSIONS_SUCCESS,
    payload: permissions
  }
}