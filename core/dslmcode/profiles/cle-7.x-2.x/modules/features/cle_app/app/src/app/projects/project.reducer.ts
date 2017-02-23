import { Action } from '@ngrx/store';
import { ActionTypes } from './project.actions';
import { Project } from './project';

export interface ProjectState {
  projects: Project[]
}

const initialState: ProjectState = {
  projects: []
}

export function projectReducer(state: ProjectState = initialState, action: Action) {
  switch (action.type) {
    case ActionTypes.CREATE_PROJECT: {
      return {
        projects: [...state.projects, action.payload]
      }
    }

    case ActionTypes.CREATE_PROJECT_SUCCESS: {
      return {
        projects: state.projects.map((project:Project) => {
          if (!project.id && action.payload.id) {
            return Object.assign({}, project, action.payload)
          }
          return project;
        })
      }
    }

    case ActionTypes.UPDATE_PROJECT: {
      return {
        projects: state.projects.map((project:Project) => {
          // check if the updated project has the same id as the current assignemnt
          if (project.id === action.payload.id) {
            return Object.assign({}, project, action.payload)
          }
          return project;
        })
      }
    }

    // just return the same projects for now since we already updated the store
    case ActionTypes.UPDATE_PROJECT_SUCCESS: {
      return {
        projects: state.projects.map((project:Project) => {
          if (project.id === action.payload.id) {
            return Object.assign({}, project, action.payload);
          }
          return project;
        })
      }
    }

    case ActionTypes.DELETE_PROJECT: {
      return {
        projects: state.projects.filter(project => project.id !== action.payload.id)
      }
    }

    case ActionTypes.LOAD_PROJECTS: {
      return {
        projects: []
      }
    }

    case ActionTypes.LOAD_PROJECTS_SUCCESS: {
      return {
        projects: action.payload ? action.payload : []
      }
    }

    case ActionTypes.MOVE_PROJECT_ASSIGNMENT: {
      return {
        projects: state.projects.map((project:Project) => {
          if (project.id === action.payload.newProjectId) {
          }
        })
      }
    }

    default:  {
      return state;
    }
  }
}

export const getAll = (state:ProjectState) => state.projects;
export const getCount = (state:ProjectState) => state.projects.length;