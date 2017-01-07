import { Action } from '@ngrx/store';
import { ActionTypes } from '../app.actions';

export interface UserState {
  permissions: string[],
  token: string
}

const initialState: UserState = {
  permissions: [],
  token: null
}

export function reducer(state: UserState = initialState, action: Action) {
  switch(action.type) {
    case ActionTypes.LOAD_PERMISSIONS: {
      return state;
    }

    case ActionTypes.LOAD_PERMISSIONS_SUCCESS: {
      return {
        permissions: action.payload.permissions ? action.payload.permissions : [],
        token: action.payload.token ? action.payload.token : null
      }
    }

    default: {
      return state;
    }
  }
}