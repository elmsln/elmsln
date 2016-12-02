import { Component, OnInit, Input, ElementRef, ContentChildren, AfterContentInit, EventEmitter, Output, ViewChild, OnDestroy } from '@angular/core';
import { Project } from '../../project';
import { ProjectService } from '../../project.service';
import { AssignmentListComponent } from '../../assignment/assignment-list/assignment-list.component';

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
}
