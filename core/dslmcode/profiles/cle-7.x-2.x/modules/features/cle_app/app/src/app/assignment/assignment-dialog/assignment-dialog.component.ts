import { Component, OnInit, OnDestroy, ElementRef, ViewChild } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { Assignment } from '../../assignment'
import { AssignmentService } from '../../assignment.service';
import { AssignmentFormComponent } from '../assignment-form/assignment-form.component';
import { Observable } from 'rxjs';
declare const jQuery:any;

@Component({
  selector: 'app-assignment-dialog',
  templateUrl: './assignment-dialog.component.html',
  styleUrls: ['./assignment-dialog.component.css'],
  providers: [AssignmentService]
})
export class AssignmentDialogComponent implements OnInit, OnDestroy {
  @ViewChild(AssignmentFormComponent) assignmentFormComponent:AssignmentFormComponent;
  assignment:Assignment = new Assignment();

  constructor(
    private route:ActivatedRoute,
    private router:Router,
    private assignmentService:AssignmentService,
    private el:ElementRef
  ) { }

  ngOnInit() {
    this.route.params
      .subscribe(params => {
        if (typeof params['assignmentId'] !== 'undefined') {
          this.assignmentService.getAssignment(params['assignmentId'])
            .subscribe(data => {
              this.assignment = data;
            });
        }
        else if (typeof params['projectId'] !== 'undefined') {
          let a:Assignment = new Assignment();
          a.project = params['projectId'];
          this.assignment = a;
        }
      })
    
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal({
      dismissible: false,
    });
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('open');
  }

  ngOnDestroy() {
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close');
  }

  onAssignmentSave($event) {
    this.router.navigate([{outlets: {dialog: null}}]);
  }

  onCancel() {
    this.router.navigate([{outlets: {dialog: null}}]);
  }

  onSave() {
    this.assignmentFormComponent.save();
  }
}
