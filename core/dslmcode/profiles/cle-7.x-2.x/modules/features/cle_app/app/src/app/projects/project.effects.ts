import 'rxjs/add/operator/mergeMap';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/Observable';
import { Action } from '@ngrx/store'
import { Effect, Actions } from '@ngrx/effects';
import {
  ActionTypes,
  loadProjectsSuccess,
  createProject,
  createProjectSuccess,
  updateProjectSuccess,
  deleteProject,
  loadPermissions,
  loadPermissionsSuccess,
} from './project.actions';
import { ProjectService } from '../project.service';
import { Project } from '../project';
declare const Materialize:any;

@Injectable()
export class ProjectEffects {
  constructor(
    private actions$: Actions,
    private projectService:ProjectService
  ) { }

  @Effect() createProject$ = this.actions$
    .ofType(ActionTypes.CREATE_PROJECT)
    .mergeMap(action => this.projectService.createProject(action.payload))
    .mergeMap((project:Project) => this.projectService.getProject(project.id))
    .map((project:Project) => createProjectSuccess(project));

  // Update the project on the server
  @Effect() updateProject$ = this.actions$
    .ofType(ActionTypes.UPDATE_PROJECT)
    .mergeMap(action => {
      return this.projectService.updateProject(action.payload)
        .mergeMap((data) => this.projectService.getProject(action.payload.id));
    })
    .map((project) => {
      Materialize.toast('Project updated', 1500);
      return updateProjectSuccess(project)
    });

  @Effect() loadProjects$ = this.actions$
    .ofType(ActionTypes.LOAD_PROJECTS)
    .mergeMap(() => this.projectService.getProjects())
    // Dispatch action to load project success
    .map(projects => loadProjectsSuccess(projects))

  @Effect({dispatch: false}) deleteProject$ = this.actions$
    .ofType(ActionTypes.DELETE_PROJECT)
    .mergeMap(action => this.projectService.deleteProject(action.payload))
    .map(info => {
      if (info.status === '200') {
        Materialize.toast('Project deleted', 1000);
      }
    })
}
