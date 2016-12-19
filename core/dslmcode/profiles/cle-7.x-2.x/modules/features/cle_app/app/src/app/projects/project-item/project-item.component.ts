import { Component, OnInit, Input, ElementRef, ContentChildren, AfterContentInit, EventEmitter, Output, ViewChild, OnDestroy } from '@angular/core';
import { Router } from '@angular/router';
import { Project } from '../../project';
import { ProjectService } from '../../project.service';
import { AssignmentService } from '../../assignment.service';
import { AssignmentListComponent } from '../../assignment/assignment-list/assignment-list.component';
import { Assignment } from '../../assignment';
import { Store } from '@ngrx/store';
import { AppState } from '../../state';
import { Observable } from 'rxjs'

declare const Materialize:any;
declare const $:any;

@Component({
  selector: 'app-project-item',
  templateUrl: './project-item.component.html',
  styleUrls: ['./project-item.component.css'],
  providers: [AssignmentService]
})
export class ProjectItemComponent implements OnInit, OnDestroy {
  @Input() project: Project;
  @Output() delete: EventEmitter<any> = new EventEmitter();
  assignments:Observable<Assignment[]>;
  
  constructor(
    private projectService:ProjectService,
    private assignmentService: AssignmentService,
    private el:ElementRef,
    private router:Router
  ) {
  }

  ngOnInit() {
    (<any>$(this.el.nativeElement.getElementsByClassName('delete-project-form'))).modal();
    (<any>$(this.el.nativeElement.getElementsByClassName('tooltipped'))).tooltip({delay:40});
    this.assignmentService.getAssignments();

    this.assignments = this.assignmentService.assignments
      .map(assignments => assignments.filter(assignment => {
        console.log(assignment);
        if (assignment.project) {
          console.log(assignment);
          if (assignment.project === this.project.id) {
            return true;
          }
        }

        return false;
      }));
  }

  ngOnDestroy() {
    (<any>$(this.el.nativeElement.getElementsByClassName('tooltipped'))).tooltip('remove');
  }


  onCreateAssignment() {
    const url = 'assignment-create/' + this.project.id;
    this.router.navigate([{outlets: {dialog: url}}]);
  }

  onDeleteProject() {
    (<any>$(this.el.nativeElement.getElementsByClassName('delete-project-form'))).modal('open');
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
      (<any>$(this.el.nativeElement.getElementsByClassName('delete-project-form'))).modal('close');
    }
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
