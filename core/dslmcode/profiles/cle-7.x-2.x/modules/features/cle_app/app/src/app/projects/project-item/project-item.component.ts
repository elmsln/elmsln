import { Component, OnInit, Input, ElementRef, ContentChildren, AfterContentInit, EventEmitter, Output, ViewChild, OnDestroy } from '@angular/core';
import { Project } from '../../project';
import { ProjectService } from '../../project.service';
import { AssignmentListComponent } from '../../assignment/assignment-list/assignment-list.component';

declare const Materialize:any;

@Component({
  selector: 'app-project-item',
  templateUrl: './project-item.component.html',
  styleUrls: ['./project-item.component.css']
})
export class ProjectItemComponent implements OnInit, OnDestroy {
  @Input() project: Project;
  @Output() delete: EventEmitter<any> = new EventEmitter();
  @ViewChild(AssignmentListComponent) assignmentListComponent:AssignmentListComponent;
  
  constructor(
    private projectService:ProjectService,
    private el:ElementRef
  ) { 
  }

  ngOnInit() {
    (<any>$(this.el.nativeElement.getElementsByClassName('modal'))).modal();
    (<any>$(this.el.nativeElement.getElementsByClassName('tooltipped'))).tooltip({delay:40});
  }

  ngOnDestroy() {
    (<any>$(this.el.nativeElement.getElementsByClassName('modal'))).modal('close');
    (<any>$(this.el.nativeElement.getElementsByClassName('tooltipped'))).tooltip('remove');
  }

  createAssignment() {
    (<any>$(this.el.nativeElement.getElementsByClassName('tooltipped'))).modal('open');
  }

  assignmentCreated($event) {
    (<any>$(this.el.nativeElement.getElementsByClassName('modal'))).modal('close');
    this.assignmentListComponent.getAssignments();
  }

  deleteProject() {
    let project = this.project;
    this.projectService.deleteProject(project)
      .subscribe(data => {
        this.delete.emit();
      });
  }

  updateTitle($event) {
    // remember the old title in case the update fails
    let oldTitle = this.project.title;
    // update the project title on the page
    this.project.title = $event;

    // the project object that we are going to save
    let newProject:Project = {
      id: this.project.id,
      title: this.project.title
    }
    // update the project in Drupal
    this.projectService.updateProject(newProject)
      .subscribe(
        data => {
          console.log(data);
        },
        error => {
          // change the title back to the original
          this.project.title = oldTitle;
          Materialize.toast('Could not update title', 5000);
        }
      );
  }
}
