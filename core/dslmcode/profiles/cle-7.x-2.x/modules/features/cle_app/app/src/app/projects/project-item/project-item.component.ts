import { Component, OnInit, Input, ElementRef, ContentChildren, AfterContentInit } from '@angular/core';
import { Project } from '../../project';

@Component({
  selector: 'app-project-item',
  templateUrl: './project-item.component.html',
  styleUrls: ['./project-item.component.css']
})
export class ProjectItemComponent implements OnInit {
  @Input() project: Project;
  
  constructor(
    private el: ElementRef
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
}
