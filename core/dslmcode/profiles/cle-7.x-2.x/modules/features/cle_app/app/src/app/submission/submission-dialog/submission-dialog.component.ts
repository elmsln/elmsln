import { Component, OnInit, ElementRef, OnDestroy } from '@angular/core';
import {Observable} from 'rxjs/Observable';
import { Router, ActivatedRoute } from '@angular/router';
import { Submission } from '../submission';
import { SubmissionService } from '../submission.service';
declare const jQuery:any;

@Component({
  selector: 'app-submission-dialog',
  templateUrl: './submission-dialog.component.html',
  styleUrls: ['./submission-dialog.component.css']
})
export class SubmissionDialogComponent implements OnInit, OnDestroy {
  submission$:Observable<Submission>;

  constructor(
    private el:ElementRef,
    private router:Router,
    private route: ActivatedRoute,
    private submissionService:SubmissionService
  ) { }

  ngOnInit() {
    this.route.params
      .map((params:any) => {
        if (typeof params['submissionId']) {
          this.submission$ = this.submissionService.getSubmissionFromStore(params['submissionId']);
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
    jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close')
  }

  onCancel() {
    this.router.navigate([{outlets: {dialog: null}}]);
  }

  onSave() {
  }
}
