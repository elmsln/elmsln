import { Action } from '@ngrx/store';
import { ActionTypes } from './image.actions';
import { Image } from './image';

export enum ImageStates {
  default,
  saving,
  error
}

export interface ImageState {
  state: ImageStates;
  message: string;
}

const initialState: ImageState = {
  state: ImageStates.default,
  message: ''
}

export function imageReducer(state: ImageState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_IMAGE: {
      return {
        state: ImageStates.saving,
        message: ''
      }
    }

    case ActionTypes.CREATE_IMAGE_SUCCESS: {
      return {
        state: ImageStates.default,
        message: 'Image created'
      }
    }

    case ActionTypes.CREATE_IMAGE_FAILURE: {
      return {
        state: ImageStates.error,
        message: 'There was an error creating the image.'
      }
    }
    
    default:  {
      return state;
    }
  }
}

export const getCurrentState = (state:ImageState) => state.state;
export const getMessage = (state:ImageState) => state.message;