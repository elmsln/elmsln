import { Action } from '@ngrx/store';

export const ActionTypes = {
  CREATE_PROJECT: 'CREATE_PROJECT',
  CREATE_PROJECT_SUCCESS: 'CREATE_PROJECT_SUCCESS',
  UPDATE_PROJECT: 'UPDATE_PROJECT',
  UPDATE_PROJECT_SUCCESS: 'UPDATE_PROJECT_SUCCESS',
  DELETE_PROJECT: 'DELETE_PROJECT',
  LOAD_PROJECTS: 'LOAD_PROJECTS',
  LOAD_PROJECTS_SUCCESS: 'LOAD_PROJECTS_SUCCESS',
  LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
  LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS'
}

export function createProject(project): Action {
  return {
    type: ActionTypes.CREATE_PROJECT,
    payload: project
  }
}

export function createProjectSuccess(projectId): Action {
  return {
    type: ActionTypes.CREATE_PROJECT_SUCCESS,
    payload: { id: projectId }
  }
}

export function updateProject(project): Action {
  return {
    type: ActionTypes.UPDATE_PROJECT,
    payload: project
  }
}

export function updateProjectSuccess(project): Action {
  return {
    type: ActionTypes.UPDATE_PROJECT_SUCCESS,
    payload: project
  }
}

export function deleteProject(project): Action {
  return {
    type: ActionTypes.DELETE_PROJECT,
    payload: project
  }
}

export function loadProjects(): Action {
  return {
    type: ActionTypes.LOAD_PROJECTS,
    payload: { }
  }
}

export function loadProjectsSuccess(projects): Action {
  return {
    type: ActionTypes.LOAD_PROJECTS_SUCCESS,
    payload: projects
  }
}

export function loadPermissions(): Action {
  return {
    type: ActionTypes.LOAD_PERMISSIONS,
    payload: {}
  }
}

export function loadPermissionsSuccess(permissions): Action {
  return {
    type: ActionTypes.LOAD_PERMISSIONS_SUCCESS,
    payload: permissions
  }
}