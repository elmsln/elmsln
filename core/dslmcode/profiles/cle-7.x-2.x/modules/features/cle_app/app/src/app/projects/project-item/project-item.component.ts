import { Component, OnInit, Input, ElementRef, ContentChildren, AfterContentInit, EventEmitter, Output } from '@angular/core';
import { Project } from '../../project';
import { ProjectService } from '../../project.service';

@Component({
  selector: 'app-project-item',
  templateUrl: './project-item.component.html',
  styleUrls: ['./project-item.component.css']
})
export class ProjectItemComponent implements OnInit {
  @Input() project: Project;
  @Output() delete: EventEmitter<any> = new EventEmitter();
  
  constructor(
    private projectService:ProjectService,
    private el:ElementRef
  ) { 
  }

  ngOnInit() {
    (<any>$('#modal1')).modal();
    (<any>$(this.el.nativeElement.getElementsByClassName('tooltipped'))).tooltip({delay:40});
  }

  createAssignment() {
    (<any>$('#modal1')).modal('open');
  }

  assignmentCreated($event) {
    (<any>$('#modal1')).modal('close');
  }

  deleteProject() {
    let project = this.project;
    this.projectService.deleteProject(project)
      .subscribe(data => {
        this.delete.emit();
      });
  }
}
