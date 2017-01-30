import { Action } from '@ngrx/store';

export const ActionTypes = {
  CREATE_IMAGE: 'CREATE_IMAGE',
  CREATE_IMAGE_SUCCESS: 'CREATE_IMAGE_SUCCESS',
  CREATE_IMAGE_FAILURE: 'CREATE_IMAGE_FAILURE'
}

export function createImage(): Action {
  return {
    type: ActionTypes.CREATE_IMAGE,
    payload: {}
  }
}

export function createImageSuccess(): Action {
  return {
    type: ActionTypes.CREATE_IMAGE_SUCCESS,
    payload: {}
  }
}

export function createImageFailure(): Action {
  return {
    type: ActionTypes.CREATE_IMAGE_FAILURE,
    payload: {}
  }
}
