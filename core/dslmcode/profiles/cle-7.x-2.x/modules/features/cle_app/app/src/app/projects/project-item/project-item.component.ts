import { Component, OnInit, Input, ElementRef, ContentChildren, AfterContentInit, EventEmitter, Output, ViewChild, OnDestroy, ChangeDetectionStrategy } from '@angular/core';
import { Router } from '@angular/router';
import { Project } from '../project';
import { ProjectService } from '../project.service';
import { AssignmentService } from '../../assignment/assignment.service';
import { AssignmentListComponent } from '../../assignment/assignment-list/assignment-list.component';
import { Assignment } from '../../assignment/assignment';
import { Store } from '@ngrx/store';
import { ActionTypes, loadAssignments } from '../../assignment/assignment.actions';
import { deleteProject, updateProject } from '../project.actions';
import * as fromRoot from '../../app.reducer';
import { Observable } from 'rxjs';

declare const Materialize:any;
declare const jQuery:any;

@Component({
  selector: 'app-project-item',
  templateUrl: './project-item.component.html',
  styleUrls: ['./project-item.component.css'],
  providers: [AssignmentService],
  changeDetection: ChangeDetectionStrategy.OnPush
})
export class ProjectItemComponent implements OnInit, OnDestroy {
  @Input() project: Project;
  @Output() delete: EventEmitter<any> = new EventEmitter();
  assignments:Observable<any>;
  permissions$:Observable<any>
  userCanEdit$:Observable<any> = this.projectService.userCanEdit;
  
  constructor(
    private projectService:ProjectService,
    private assignmentService: AssignmentService,
    private el:ElementRef,
    private router:Router,
    private store:Store<fromRoot.State>
  ) {
  }

  ngOnInit() {
    jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal({
      ready: function(modal, trigger) { // Callback for Modal open. Modal and trigger parameters available.
        /**
         * @todo: Hack to solve z-index issues when embeded in the Drupal site.
         */
        jQuery('.modal-overlay').appendTo('app-root');
      },
    });
    jQuery(this.el.nativeElement.getElementsByClassName('tooltipped')).tooltip({delay:40});

    // get the assignments
    this.assignments = this.assignmentService.pluckAssignmentsByProject(this.project.id);
  }

  ngOnDestroy() {
    jQuery(this.el.nativeElement.getElementsByClassName('tooltipped')).tooltip('remove');
  }


  onCreateAssignment() {
    const url = 'assignment-create/' + this.project.id;
    this.router.navigate([{outlets: {dialog: url}}]);
  }

  onDeleteProject() {
    jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal('open');
  }

  confirmDelete(confirm:boolean) {
    if (confirm) {
      let project = this.project;
      this.store.dispatch(deleteProject(project));
    }
    else {
      jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal('close');
    }
  }

  updateTitle($event) {
    let newProject = Object.assign({}, this.project, { title: $event });
    this.store.dispatch(updateProject(newProject));
  }
}
