import { Component, OnInit } from '@angular/core';
import { Project } from '../../project';
import { ProjectService } from '../../project.service';
import { Router } from '@angular/router';
import { Observable } from 'rxjs';
declare const $:JQueryStatic;

@Component({
  selector: 'app-projects-list',
  templateUrl: './projects-list.component.html',
  styleUrls: ['./projects-list.component.css'],
  providers: [ProjectService]
})
export class ProjectsListComponent implements OnInit {
  loading: boolean;
  projects: Project[] = [];

  constructor(
    private projectService:ProjectService,
    private router:Router
  ) {
    this.loading = true;
  }

  ngOnInit() {
    this.projectService.getProjects()
      .subscribe((data) => {
        this.projects = data;
        this.loading = false;
      });
  }

  createNewProject(title) {
    console.log('Create Project');
    this.projectService.createProject({
        title: title ? title : "New Project",
      })
      .subscribe(data => {
        // we will receive the newley created projects id
        // we will use that id to request the full project and add it to the
        // array of projects
        this.projectService.getProject(data.id)
          .subscribe((project:Project) => {
            this.projects.push(project);
          })
      })
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