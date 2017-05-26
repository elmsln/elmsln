import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { ElmslnService } from '../elmsln.service';
import { AppSettings } from '../app.settings';
import { Project } from './project';
import { Store } from '@ngrx/store';

@Injectable()
export class ProjectService {
  constructor(
    private elmsln: ElmslnService,
    private store: Store<{}>
  ) { }

  getProjects() {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/projects')
      .map(data => data.json())
      .map(data => typeof data.data !== 'undefined' ? data.data : [])
      .map((projects:any[]) => projects.map(p => this.convertToProject(p)));
  }

  getProject(projectId:number) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/projects/' + projectId)
      .map(data => data.json().data[0])
      .map(project => this.convertToProject(project))
  }

  createProject(project:any) {
    // first we need to prepare the object for Drupal
    return this.elmsln.post(AppSettings.BASE_PATH + 'api/v1/cle/projects/create', project)
      .map(data => data.json().node) 
      .map(node => this.convertToProject(node))
  }

  updateProject(project:Project) {
    return this.elmsln.put(AppSettings.BASE_PATH + 'api/v1/cle/projects/' + project.id + '/update', project)
      .map(data => data.json().node)
      .map(node => this.convertToProject(node))
  }

  deleteProject(project:Project) {
    return this.elmsln.delete(AppSettings.BASE_PATH + 'api/v1/cle/projects/' + project.id + '/delete')
      .map(data => data.json())
  }


  private formatProjects(projects: any[]) {
    let _this = this;
    let newProjects: any[] = [];
    projects.forEach(function(project) {
      newProjects.push(_this.convertToProject(project));
    });

    return newProjects;
  }

  private convertToProject(data:any) {
    let converted:Project = new Project();
    for(var propertyName in converted) {
      if (data[propertyName]) {
        converted[propertyName] = data[propertyName];
      }
    }
    if (data.id) {
      converted.id = Number(data.id);
    }
    if (data.nid) {
      converted.id = Number(data.nid);
    }
    if (data.title) {
      converted.title = data.title;
    }
    
    // Convert date fields
    let dateFields = ['startDate', 'endDate'];
    dateFields.forEach(function(field) {
      if (converted[field]) {
        converted[field] = new Date(converted[field] * 1000);
      }
    });

    return converted;
  }

  private prepareForDrupal(project:Project) {
    let ufProject:any = {};

    // always specify as cle_project
    ufProject['type'] = "cle_project";

    if (project.title) {
      ufProject['title'] = project.title;
    }
    if (project.author) {
      ufProject['author'] = project.author;
    }
    if (project.description) {
      ufProject['field_project_due_date'] = project.description;
    }
    if (project.startDate) {
      ufProject['field_project_due_date']['value2'] = project.startDate;
    }
    if (project.endDate) {
      ufProject['field_project_due_date']['value'] = project.endDate;
    }

    return ufProject;
  }

  // Return if the user should be able to edit a project
  get userCanEdit():Observable<boolean> {
    return this.store.select('user')
      .map((state:any) => state.permissions.includes('edit own cle_project content'));
  }
}
