import { Action } from '@ngrx/store';
import { ActionTypes } from '../app.actions';

export interface UserState {
  permissions: string[]
}

const initialState: UserState = {
  permissions: []
}

export function reducer(state: UserState = initialState, action: Action) {
  switch(action.type) {
    case ActionTypes.LOAD_PERMISSIONS: {
      return state;
    }

    case ActionTypes.LOAD_PERMISSIONS_SUCCESS: {
      return {
        permissions: action.payload ? action.payload : []
      }
    }

    default: {
      return state;
    }
  }
}