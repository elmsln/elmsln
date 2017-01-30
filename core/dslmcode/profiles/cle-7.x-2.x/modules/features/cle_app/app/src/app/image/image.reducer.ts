import { Action } from '@ngrx/store';
import { ActionTypes } from './image.actions';
import { Image } from './image';

export interface ImageState {
  status: ImageStatusState;
}

export interface ImageStatusState {
  type: string,
  message: string
}

const initialState: ImageState = {
  status: {
    type: 'default',
    message: ''
  }
}

export function imageReducer(state: ImageState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_IMAGE: {
      return {
        status: {
          type: 'saving',
          message: ''
        }
      }
    }

    case ActionTypes.CREATE_IMAGE_SUCCESS: {
      return {
        status: {
          type: 'saved',
          message: 'Image created'
        }
      }
    }

    case ActionTypes.CREATE_IMAGE_FAILURE: {
      return {
        status: {
          type: 'error',
          message: 'There was an error creating the image.'
        }
      }
    }
    
    default:  {
      return state;
    }
  }
}
