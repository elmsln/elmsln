import { Action } from '@ngrx/store';
import { ActionTypes } from './submission.actions';
import { Submission } from './submission';
import { ActionTypes as AppActionTypes } from '../assignment/assignment.actions';

export interface SubmissionState {
  saving: boolean;
  savingImage: boolean;
  submissions: Submission[]
}

const initialState: SubmissionState = {
  saving: false,
  savingImage: false,
  submissions: []
}

export function submissionReducer(state: SubmissionState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_SUBMISSION: {
      return {
        saving: true,
        savingImage: state.savingImage,
        submissions: [...state.submissions, action.payload]
      }
    }

    case ActionTypes.CREATE_SUBMISSION_SUCCESS: {
      return {
        saving: false,
        savingImage: state.savingImage,
        submissions: state.submissions.map((submission:Submission) => {
          if (!submission.id && action.payload.id) {
            return Object.assign({}, submission, action.payload)
          }
          return submission;
        })
      }
    }

    case ActionTypes.UPDATE_SUBMISSION: {
      return {
        saving: true,
        savingImage: state.savingImage,
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
        savingImage: state.savingImage,
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
        savingImage: state.savingImage,
        submissions: state.submissions.filter(submission => submission.id !== action.payload.id)
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS: {
      return {
        saving: state.saving,
        savingImage: state.savingImage,
        submissions: []
      }
    }

    case ActionTypes.LOAD_SUBMISSIONS_SUCCESS: {
      return {
        saving: state.saving,
        savingImage: state.savingImage,
        submissions: action.payload ? action.payload : []
      }
    }

    case ActionTypes.CREATE_SUBMISSION_IMAGE: {
      return {
        saving: state.saving,
        savingImage: true,
        submissions: state.submissions
      }
    }

    case ActionTypes.CREATE_SUBMISSION_IMAGE_SUCCESS: {
      return {
        saving: state.saving,
        savingImage: false,
        submissions: state.submissions
      }
    }

    case ActionTypes.CREATE_SUBMISSION_IMAGE_FAILURE: {
      return {
        saving: state.saving,
        savingImage: false,
        submissions: state.submissions
      }
    }
    
    default:  {
      return state;
    }
  }
}

export const getAll = (state:SubmissionState) => state.submissions;
export const getIsSaving = (state:SubmissionState) => state.saving;
export const getImageIsSaving = (state:SubmissionState) => state.savingImage;