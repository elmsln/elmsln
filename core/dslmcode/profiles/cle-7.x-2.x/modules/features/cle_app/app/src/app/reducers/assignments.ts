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

    case ActionTypes.CREATE_CRITIQUE_ASSIGNMENT: {
      return state;
    }

    case ActionTypes.CREATE_CRITIQUE_ASSIGNMENT_SUCCESS: {
      return {
        loading: state.loading,
        assignments: [...state.assignments, action.payload]
      };
    }

    case ActionTypes.UPDATE_ASSIGNMENT: {
      return {
        loading: state.loading,
        assignments: state.assignments.map((assignment:Assignment) => {
          // check if the updated assignment has the same id as the current assignemnt
          if (assignment.id === action.payload.id) {
            return Object.assign({}, assignment, action.payload)
          }
          return assignment;
        })
      }
    }

    // just return the same assignments for now since we already updated the store
    case ActionTypes.UPDATE_ASSIGNMENT_SUCCESS: {
      return {
        loading: state.loading,
        assignments: state.assignments.map((assignment:Assignment) => {
          if (assignment.id === action.payload.id) {
            return Object.assign({}, assignment, action.payload);
          }
          return assignment;
        })
      }
    }

    case ActionTypes.DELETE_ASSIGNMENT: {
      return {
        loading: false,
        assignments: state.assignments.filter(assignment => assignment.id !== action.payload.id)
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
