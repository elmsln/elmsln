import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { ElmslnService } from './elmsln.service';
import { AppSettings } from './app-settings';
import { Project } from './project';

@Injectable()
export class ProjectService {

  constructor(
    private elmsln: ElmslnService
  ) { }

  getProjects() {
    return this.elmsln.get(AppSettings.BASE_PATH + 'node.json?type=cle_project')
      .map(data => data.json().list)
      .map(data => this.formatProjects(data))
  }

  getProject(projectId:number) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'node/' + projectId + '.json')
      .map(data => data.json())
      .map(data => this.formatProject(data))
  }

  createProject(project:any) {
    // first we need to prepare the object for Drupal
    let body = this.prepareForDrupal(project);
    return this.elmsln.post(AppSettings.BASE_PATH + 'node', body)
      .map(data => data.json())
  }

  updateProject(project:Project) {
    console.log('updateProject', project);
    // first we need to prepare the object for Drupal
    let body = this.prepareForDrupal(project);
    console.log('updateProject: Ready to send', body);
    return this.elmsln.put(AppSettings.BASE_PATH + 'node/'+ project.id, body)
      .map(data => data.json())
  }

  deleteProject(project:Project) {
    return this.elmsln.delete(AppSettings.BASE_PATH + 'node/' + project.id)
      .map(data => data.json())
  }


  private formatProjects(projects: any[]) {
    let _this = this;
    let newProjects: any[] = [];
    projects.forEach(function(project) {
      newProjects.push(_this.formatProject(project));
    });

    return newProjects;
  }

  private formatProject(project: any) {
    let newProject: Project = {
      title: project.title ? project.title : null,
      id: project.nid ? project.nid : null
      // author: project.author.id ? project.author.id : null,
      // startDate: project.field_project_due_date.value ? project.field_project_due_date.value : null,
      // endDate: project.field_project_due_date.value2 ? project.field_project_due_date.value2 : null,
      // description: project.field_project_description.value ? project.field_project_description.value : null
    };

    // Convert date fields
    let dateFields = ['startDate', 'endDate'];
    dateFields.forEach(function(field) {
      if (newProject[field]) {
        newProject[field] = new Date(newProject[field] * 1000);
      }
    });


    return newProject;
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
}
