import { createSelector } from 'reselect';
import { Action } from '@ngrx/store';
import { ActionTypes } from './submission.actions';
import { Submission } from './submission';
import { ActionTypes as AppActionTypes } from '../assignment/assignment.actions';

export enum SubmissionStates {
  default,
  saving,
  error
}

export interface SubmissionState {
  state: SubmissionStates;
  submissions: Submission[]
}

const initialState: SubmissionState = {
  state: SubmissionStates.default,
  submissions: []
}

export function submissionReducer(state: SubmissionState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_SUBMISSION: {
      return {
        state: SubmissionStates.saving,
        submissions: [...state.submissions, action.payload]
      }
    }

    case ActionTypes.CREATE_SUBMISSION_SUCCESS: {
      return {
        state: SubmissionStates.default,
        submissions: state.submissions.map((submission:Submission) => {
          if (!submission.id && action.payload.id) {
            return Object.assign({}, submission, action.payload)
          }
          return submission;
        })
      }
    }

    case ActionTypes.CREATE_SUBMISSION_FAILURE: {
      return {
        state: SubmissionStates.error,
        submissions: state.submissions
      }
    }

    case ActionTypes.UPDATE_SUBMISSION: {
      return {
        state: SubmissionStates.saving,
        submissions: state.submissions.map((submission:Submission) => {
          // check if the updated submission has the same id as the current assignemnt
          if (submission.id === action.payload.id) {
            return Object.assign({}, submission, action.payload)
          }
          return submission;
        })
      }
    }

    // just return the same submissions for now since we already updated the store
    case ActionTypes.UPDATE_SUBMISSION_SUCCESS: {
      return {
        state: SubmissionStates.default,
        submissions: state.submissions.map((submission:Submission) => {
          if (submission.id === action.payload.id) {
            return Object.assign({}, submission, action.payload);
          }
          return submission;
        })
      }
    }

    case ActionTypes.DELETE_SUBMISSION: {
      console.log(state.submissions, action.payload);
      return {
        state: state.state,
        submissions: state.submissions.filter(submission => submission.id !== action.payload.id)
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS: {
      return {
        state: state.state,
        submissions: []
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS_SUCCESS: {
      return {
        state: state.state,
        submissions: action.payload ? action.payload : []
      }
    }

    case ActionTypes.CREATE_SUBMISSION_IMAGE: {
      return {
        state: state.state,
        submissions: state.submissions
      }
    }

    case ActionTypes.CREATE_SUBMISSION_IMAGE_SUCCESS: {
      return {
        state: state.state,
        submissions: state.submissions
      }
    }

    case ActionTypes.CREATE_SUBMISSION_IMAGE_FAILURE: {
      return {
        state: state.state,
        submissions: state.submissions
      }
    }
    
    default:  {
      return state;
    }
  }
}

export const getAll = (state:SubmissionState) => state.submissions;
export const getCurrentState = (state:SubmissionState) => state.state;