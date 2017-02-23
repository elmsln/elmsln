import { Action } from '@ngrx/store';
import { ActionTypes } from '../assignment/assignment.actions';

export interface UserState {
  permissions: string[],
  token: string
  uid: number
}

const initialState: UserState = {
  permissions: [],
  token: null,
  uid: null
}

export function reducer(state: UserState = initialState, action: Action) {
  switch(action.type) {
    case ActionTypes.LOAD_PERMISSIONS: {
      return state;
    }

    case ActionTypes.LOAD_PERMISSIONS_SUCCESS: {
      return {
        permissions: action.payload.permissions ? action.payload.permissions : [],
        token: action.payload.token ? action.payload.token : null,
        uid: action.payload.uid ? action.payload.uid : null
      }
    }

    default: {
      return state;
    }
  }
}