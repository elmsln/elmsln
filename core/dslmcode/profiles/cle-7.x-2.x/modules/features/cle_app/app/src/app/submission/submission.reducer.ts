import { Action } from '@ngrx/store';
import { ActionTypes } from './submission.actions';
import { Submission } from './submission';

export interface SubmissionState {
  saving: boolean;
  submissions: Submission[]
}

const initialState: SubmissionState = {
  saving: false,
  submissions: []
}

export function submissionReducer(state: SubmissionState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_SUBMISSION: {
      return {
        saving: true,
        submissions: [...state.submissions, action.payload]
      }
    }

    case ActionTypes.CREATE_SUBMISSION_SUCCESS: {
      return {
        saving: false,
        submissions: state.submissions.map((submission:Submission) => {
          if (!submission.id && action.payload.id) {
            return Object.assign({}, submission, { id: action.payload.id })
          }
          return submission;
        })
      }
    }

    case ActionTypes.UPDATE_SUBMISSION: {
      return {
        saving: true,
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
        saving: false,
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
        saving: state.saving,
        submissions: state.submissions.filter(submission => submission.id !== action.payload.id)
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS: {
      return {
        saving: state.saving,
        submissions: []
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS_SUCCESS: {
      return {
        saving: state.saving,
        submissions: action.payload ? action.payload : []
      }
    }

    default:  {
      return state;
    }
  }
}
