import { Action } from '@ngrx/store';

export const ActionTypes = {
  CREATE_SUBMISSION: 'CREATE_SUBMISSION',
  CREATE_SUBMISSION_SUCCESS: 'CREATE_SUBMISSION_SUCCESS',
  UPDATE_SUBMISSION: 'UPDATE_SUBMISSION',
  UPDATE_SUBMISSION_SUCCESS: 'UPDATE_SUBMISSION_SUCCESS',
  DELETE_SUBMISSION: 'DELETE_SUBMISSION',
  LOAD_SUBMISSIONS: 'LOAD_SUBMISSIONS',
  LOAD_SUBMISSIONS_SUCCESS: 'LOAD_SUBMISSIONS_SUCCESS',
  LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
  LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS',
  CREATE_SUBMISSION_IMAGE: 'CREATE_SUBMISSION_IMAGE',
  CREATE_SUBMISSION_IMAGE_SUCCESS: 'CREATE_SUBMISSION_IMAGE_SUCCESS',
  CREATE_SUBMISSION_IMAGE_FAILURE: 'CREATE_SUBMISSION_IMAGE_FAILURE'
}

export function createSubmission(submission): Action {
  return {
    type: ActionTypes.CREATE_SUBMISSION,
    payload: submission
  }
}

export function createSubmissionSuccess(submission): Action {
  return {
    type: ActionTypes.CREATE_SUBMISSION_SUCCESS,
    payload: submission
  }
}

export function updateSubmission(submission): Action {
  return {
    type: ActionTypes.UPDATE_SUBMISSION,
    payload: submission
  }
}

export function updateSubmissionSuccess(submission): Action {
  return {
    type: ActionTypes.UPDATE_SUBMISSION_SUCCESS,
    payload: submission
  }
}

export function deleteSubmission(submission): Action {
  return {
    type: ActionTypes.DELETE_SUBMISSION,
    payload: submission
  }
}

export function loadSubmissions(): Action {
  return {
    type: ActionTypes.LOAD_SUBMISSIONS,
    payload: { }
  }
}

export function loadSubmissionsSuccess(submissions): Action {
  return {
    type: ActionTypes.LOAD_SUBMISSIONS_SUCCESS,
    payload: submissions
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

export function createSubmissionImage(): Action {
  return {
    type: ActionTypes.CREATE_SUBMISSION_IMAGE,
    payload: {}
  }
}

export function createSubmissionImageSuccess(): Action {
  return {
    type: ActionTypes.CREATE_SUBMISSION_IMAGE_SUCCESS,
    payload: {}
  }
}

export function createSubmissionImageFailure(): Action {
  return {
    type: ActionTypes.CREATE_SUBMISSION_IMAGE_FAILURE,
    payload: {}
  }
}