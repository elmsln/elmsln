import { createSelector } from 'reselect';
import { Action } from '@ngrx/store';
import { ActionTypes } from './activity-feed.actions';

export enum ActivityFeedStates {
  open,
  closed
}

export interface ActivityFeedState {
  state: ActivityFeedStates;
}

const initialState: ActivityFeedState = {
  state: ActivityFeedStates.closed
}

export function activityFeedReducer(state: ActivityFeedState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.OPEN_ACTIVITY_FEED: {
      return {
        state: ActivityFeedStates.open,
      }
    }

    case ActionTypes.CLOSE_ACTIVITY_FEED: {
      return {
        state: ActivityFeedStates.closed,
      }
    }

    case ActionTypes.TOGGLE_ACTIVITY_FEED: {
      const currentState = state.state;
      const newState = state.state === ActivityFeedStates.open ? ActivityFeedStates.closed : ActivityFeedStates.open;
      return {
        state: newState,
      }
    }
    
    default:  {
      return state;
    }
  }
}

export const getCurrentState = (state:ActivityFeedState) => state.state;