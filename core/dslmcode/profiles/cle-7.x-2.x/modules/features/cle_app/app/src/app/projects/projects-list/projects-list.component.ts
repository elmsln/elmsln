import { Component, OnInit } from '@angular/core';
import { Project } from '../project';
import { ProjectService } from '../project.service';
import { Router } from '@angular/router';
import { Observable } from 'rxjs';
import { Store } from '@ngrx/store';
import { loadAssignments, loadPermissions } from '../../assignment/assignment.actions';
import { loadProjects, createProject } from '../project.actions';
import * as fromRoot from '../../app.reducer';
declare const $:any;
declare const Materialize:any;

@Component({
  selector: 'app-projects-list',
  templateUrl: './projects-list.component.html',
  styleUrls: ['./projects-list.component.css'],
  providers: [ProjectService]
})
export class ProjectsListComponent implements OnInit {
  projects: Project[] = [];
  projects$: Observable<Project[]>;
  userCanEdit$: Observable<boolean> = this.projectService.userCanEdit;

  constructor(
    private projectService:ProjectService,
    private router: Router,
    private store: Store<{}>
  ) {
  }

  ngOnInit() {
    this.projects$ = this.store.select(fromRoot.getProjects);
  }

  createNewProject(title) {
    const newProj = new Project();
    newProj.title = "New Project";
    this.store.dispatch(createProject(newProj));
  }

  projectDeleted(deletedProject) {
    let _this = this;
    this.projects.forEach(function(project, index) {
      if (project.id == deletedProject.id) {
        _this.projects.splice(index, 1)
      }
    })
  }
}