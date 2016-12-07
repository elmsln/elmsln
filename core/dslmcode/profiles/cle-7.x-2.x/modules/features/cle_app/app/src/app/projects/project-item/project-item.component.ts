import { Component, OnInit, Input, ElementRef, ContentChildren, AfterContentInit, EventEmitter, Output, ViewChild, OnDestroy } from '@angular/core';
import { Project } from '../../project';
import { ProjectService } from '../../project.service';
import { AssignmentListComponent } from '../../assignment/assignment-list/assignment-list.component';
declare const jQuery:any;
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
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal();
    jQuery(this.el.nativeElement.getElementsByClassName('tooltipped')).tooltip({delay:40});
  }

  ngOnDestroy() {
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close');
    jQuery(this.el.nativeElement.getElementsByClassName('tooltipped')).tooltip('remove');
  }

  createAssignment() {
    jQuery(this.el.nativeElement.getElementsByClassName('assignment-form')).modal('open');
  }

  assignmentCreated(event) {
    jQuery(this.el.nativeElement.getElementsByClassName('assignment-form')).modal('close');
    Materialize.toast('Assignment created!', 1000);
    this.assignmentListComponent.getAssignments();
  }

  deleteProject() {
    jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal('open');
  }

  confirmDelete(confirm:boolean) {
    if (confirm) {
      let project = this.project;
      this.projectService.deleteProject(project)
        .subscribe(data => {
          this.delete.emit();
          Materialize.toast('Project deleted', 1000);
        });
    }
    else {
      jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal('close');
    }
  }

  updateTitle(event) {
    // remember the old title in case the update fails
    let oldTitle = this.project.title;
    // update the project title on the page
    this.project.title = event;

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
