import { Action } from '@ngrx/store';
import { ActionTypes } from '../app.actions';
import { Assignment } from '../assignment'

export interface AssignmentState {
  loading: boolean,
  assignments: Assignment[]
}

const initialState: AssignmentState = {
  loading: false,
  assignments: []
}

export function reducer(state: AssignmentState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_ASSIGNMENT: {
      return {
        loading: state.loading,
        assignments: [...state.assignments, action.payload]
      }
    }

    case ActionTypes.CREATE_ASSIGNMENT_SUCCESS: {
      const assignmentId = action.payload.id ? Number(action.payload.id) : null;
      return {
        loading: state.loading,
        assignments: state.assignments.map((assignment:Assignment) => {
          if (!assignment.id && assignmentId) {
            return Object.assign({}, assignment, { id: assignmentId })
          }
          return assignment;
        })
      }
    }

    case ActionTypes.LOAD_ASSIGNMENTS: {
      return {
        loading: true,
        assignments: []
      }
    }

    case ActionTypes.LOAD_ASSIGNMENTS_SUCCESS: {
      return {
        loading: false,
        assignments: action.payload ? action.payload : []
      }
    }

    default:  {
      return state;
    }
  }
}
