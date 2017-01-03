import { Action } from '@ngrx/store';
import { ActionTypes } from './submission.actions';
import { Submission } from './submission';

export interface SubmissionState {
  submissions: Submission[]
}

const initialState: SubmissionState = {
  submissions: []
}

export function submissionReducer(state: SubmissionState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_SUBMISSION: {
      return {
        submissions: [...state.submissions, action.payload]
      }
    }

    case ActionTypes.CREATE_SUBMISSION_SUCCESS: {
      const submissionId = action.payload.id ? Number(action.payload.id) : null;
      return {
        submissions: state.submissions.map((submission:Submission) => {
          if (!submission.id && submissionId) {
            return Object.assign({}, submission, { id: submissionId })
          }
          return submission;
        })
      }
    }

    case ActionTypes.UPDATE_SUBMISSION: {
      return {
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
        submissions: state.submissions.filter(submission => submission.id !== action.payload.id)
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS: {
      return {
        submissions: []
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS_SUCCESS: {
      return {
        submissions: action.payload ? action.payload : []
      }
    }

    default:  {
      return state;
    }
  }
}
