import { Component, OnInit, OnDestroy, ElementRef, ViewChild } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { Assignment } from '../../assignment'
import { AssignmentService } from '../../assignment.service';
import { AssignmentFormComponent } from '../assignment-form/assignment-form.component';
import { Observable } from 'rxjs';
import { Store } from '@ngrx/store';
import { createAssignment, updateAssignment, deleteAssignment } from '../../app.actions';
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
  action:string;

  constructor(
    private route:ActivatedRoute,
    private router:Router,
    private assignmentService:AssignmentService,
    private el:ElementRef,
    private store:Store<{}>
  ) { }

  ngOnInit() {
    this.route.params
      .subscribe(params => {
        if (typeof params['assignmentId'] !== 'undefined') {
          this.action = 'update';
          this.assignmentService.getAssignment(params['assignmentId'])
            .subscribe(data => {
              this.assignment = data;
            });
        }
        else if (typeof params['projectId'] !== 'undefined') {
          let a:Assignment = new Assignment();
          this.action = 'create';
          a.project = Number(params['projectId']);
          this.assignment = a;
        }
        else if (typeof params['deleteAssignmentId'] !== 'undefined') {
          this.action = 'delete';
          let a:Assignment = new Assignment();
          a.id = Number(params['deleteAssignmentId']);
          this.assignment = a;
        }
      })
    
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal({
      dismissible: false,
      ready: function(modal, trigger) { // Callback for Modal open. Modal and trigger parameters available.
        /**
         * @todo: Hack to solve z-index issues when embeded in the Drupal site.
         */
        jQuery('.modal-overlay').appendTo('app-root');
      },
    });
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('open');
  }

  ngOnDestroy() {
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close');
  }

  onAssignmentSave($event) {
    if ($event.id) {
      this.store.dispatch(updateAssignment($event));
    }
    else {
      this.store.dispatch(createAssignment($event));
    }
    this.router.navigate([{outlets: {dialog: null}}]);
  }

  onCancel() {
    this.router.navigate([{outlets: {dialog: null}}]);
  }

  onSave() {
    this.assignmentFormComponent.save();
  }

  onDelete() {
    this.store.dispatch(deleteAssignment(this.assignment));
    this.router.navigate([{outlets: {dialog: null}}]);
  }
}
