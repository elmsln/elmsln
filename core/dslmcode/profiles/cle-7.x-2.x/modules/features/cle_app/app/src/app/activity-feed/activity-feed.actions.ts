import { Action } from '@ngrx/store';
import { Response } from '@angular/http';

export const ActionTypes = {
  OPEN_ACTIVITY_FEED: 'OPEN_ACTIVITY_FEED',
  CLOSE_ACTIVITY_FEED: 'CLOSE_ACTIVITY_FEED',
  TOGGLE_ACTIVITY_FEED: 'TOGGLE_ACTIVITY_FEED'
}

export function openActivityFeed(): Action {
  return {
    type: ActionTypes.OPEN_ACTIVITY_FEED,
    payload: {}
  }
}

export function closeActivityFeed(): Action {
  return {
    type: ActionTypes.CLOSE_ACTIVITY_FEED,
    payload: {}
  }
}

export function toggleActivityFeed(): Action {
  return {
    type: ActionTypes.TOGGLE_ACTIVITY_FEED,
    payload: {}
  }
}